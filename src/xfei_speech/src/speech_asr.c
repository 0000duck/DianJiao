/*
* 语音听写(iFly Auto Transform)技术能够实时地将语音转换成对应的文字。
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "xfei_speech/qisr.h"
#include "xfei_speech/msp_cmn.h"
#include "xfei_speech/msp_errors.h"
#include "xfei_speech/speech_recognizer.h"

#define FRAME_LEN	640 
#define	BUFFER_SIZE	4096
#define SAMPLE_RATE_16K     (16000)
#define SAMPLE_RATE_8K      (8000)
#define MAX_GRAMMARID_LEN   (32)
#define MAX_PARAMS_LEN      (1024)

const char * ASR_RES_PATH        = "fo|res/asr/common.jet";	//离线语法识别资源路径
const char * GRM_BUILD_PATH      = "res/asr/GrmBuilld";		//构建离线语法识别网络生成数据保存路径
const char * GRM_FILE            = "asr_word.bnf";			//构建离线识别语法网络所用的语法文件

typedef struct _UserData {
	int     build_fini;		//标识语法构建是否完成
	int     update_fini;	//标识更新词典是否完成
	int     errcode;		//记录语法构建或更新词典回调错误码
	char    grammar_id[MAX_GRAMMARID_LEN];	//保存语法构建返回的语法ID
} UserData;

// 构建语法的回调函数
int build_grm_cb(int ecode, const char *info, void *udata)
{
	UserData *grm_data = (UserData *)udata;

	if (NULL != grm_data) {
		grm_data->build_fini = 1;
		grm_data->errcode = ecode;
	}

	if (MSP_SUCCESS == ecode && NULL != info) {
		//printf("构建语法成功！ 语法ID:%s\n", info);
		if (NULL != grm_data)
			snprintf(grm_data->grammar_id, MAX_GRAMMARID_LEN - 1, info, NULL);
	} else
		printf("构建语音命令识别的语法失败！%d\n", ecode);

	return 0;
}

// 读取BNF文件，构建语法
int build_grammar(UserData *udata)
{
	FILE *grm_file                           = NULL;
	char *grm_content                        = NULL;
	unsigned int grm_cnt_len                 = 0;
	char grm_build_params[MAX_PARAMS_LEN]    = {0};
	int ret                                  = 0;

	grm_file = fopen(GRM_FILE, "rb");
	if(NULL == grm_file) {
		printf("打开\"%s\"文件失败！[%s]\n", GRM_FILE, strerror(errno));
		return -1; 
	}

	fseek(grm_file, 0, SEEK_END);
	grm_cnt_len = ftell(grm_file);
	fseek(grm_file, 0, SEEK_SET);

	grm_content = (char *)malloc(grm_cnt_len + 1);
	if (NULL == grm_content)
	{
		printf("内存分配失败!\n");
		fclose(grm_file);
		grm_file = NULL;
		return -1;
	}
	fread((void*)grm_content, 1, grm_cnt_len, grm_file);
	grm_content[grm_cnt_len] = '\0';
	fclose(grm_file);
	grm_file = NULL;

	snprintf(grm_build_params, MAX_PARAMS_LEN - 1, 
		"engine_type = local, \
		asr_res_path = %s, sample_rate = %d, \
		grm_build_path = %s, ",
		ASR_RES_PATH,
		SAMPLE_RATE_16K,
		GRM_BUILD_PATH
		);
	ret = QISRBuildGrammar("bnf", grm_content, grm_cnt_len, grm_build_params, build_grm_cb, udata);

	free(grm_content);
	grm_content = NULL;

	return ret;
}

static UserData asr_data;
static char asr_params[MAX_PARAMS_LEN] = {0};
static struct speech_rec asr_iat;

static int listen_status = -1;	// 监听状态：-1:不听，0:没开始听或听完了，1:正在听
static int listen_would = 0;	// -1:需要关闭监听，1:需要打开监听

static char listen_result[BUFFER_SIZE];	// 识别结果
static int has_result = 0;				// 是否正常识别
static int has_error = 0;				// 是否识别出错
static int has_over = 0;				// 是否听完了
static char g_result[BUFFER_SIZE];		// 识别结果的缓冲区

// 识别完成的回调
void on_result(const char *result, char is_last) {
	if (result) {
		size_t left = BUFFER_SIZE - 1 - strlen(g_result);
		size_t size = strlen(result);
		if (left < size) {
			//printf("\nout of buffer\n");
			has_error = 1;
			return;
		}
		strcat(g_result, result);
		if (is_last) {
			strcpy(listen_result, g_result);	// 复制识别结果
			has_result = 1;
		}
	}
}
// 开始监听的回调
void on_speech_begin() {
	memset(g_result, 0, BUFFER_SIZE);
}
// 结束监听的回调
void on_speech_end(int reason) {
	has_over = 1;
	if (reason != END_REASON_VAD_DETECT) {
		//printf("\nRecognizer error: %d\n", reason);
		has_error = 1;
	}
}

/* 获取当前的识别结果，每个结果只能调用一次 */
char* xfei_listen_result() {
	if ( listen_status < 0 ) {
		if ( listen_would > 0 )
			listen_status = 0;	// 准备开始听
		listen_would = 0;
		return NULL;
	}

	char* ret = NULL;
	if ( listen_status > 0 ) {
		// 正在听
		if ( has_over == 0 )
			return NULL;	// 还没听完
		if (asr_iat.state > 0)
			usleep(10*1000);		// 等待一会儿，确保监听结束
		sr_uninit(&asr_iat);

		if ( has_result && ! has_error )
			ret = listen_result;	// 识别结果
		listen_status = 0;
	}

	if ( listen_would < 0 ) {
		listen_status = -1;			// 停止监听
		listen_would = 0;
		return NULL;
	}

	// 开始下一轮监听
	int errcode;
	struct speech_rec_notifier recnotifier = {
		on_result,
		on_speech_begin,
		on_speech_end
	};

	errcode = sr_init(&asr_iat, asr_params, SR_MIC, &recnotifier);
	if (errcode) {
		printf("xxx 初始化语音识别失败: %d xxx\n", errcode);
		listen_status = -1;			// 停止监听
		return ret;
	}
	errcode = sr_start_listening(&asr_iat);
	if (errcode) {
		sr_uninit(&asr_iat);
		printf("xxx 开始监听失败: %d xxx\n", errcode);
		listen_status = -1;			// 停止监听
		return ret;
	}
	listen_status = 1;
	has_result = 0;
	has_error = 0;
	has_over = 0;
	return ret;
}

/* 语音识别初始化 */
int xfei_asr_init() {
	int ret = 0 ;
	memset(&asr_data, 0, sizeof(UserData));
	//printf("构建离线识别语法网络...\n");
	ret = build_grammar(&asr_data);  //第一次使用某语法进行识别，需要先构建语法网络，获取语法ID，之后使用此语法进行识别，无需再次构建
	if (MSP_SUCCESS != ret) {
		printf("构建语音命令识别的语法调用失败！\n");
		return -1;
	}
	while (1 != asr_data.build_fini)
		usleep(300 * 1000);			// 暂停300毫秒
	if (MSP_SUCCESS != asr_data.errcode)
		return -1;
	//printf("离线识别语法网络构建完成，开始识别...\n");

	//离线语法识别参数设置
	snprintf(asr_params, MAX_PARAMS_LEN - 1,
		"engine_type = local, \
		asr_res_path = %s, sample_rate = %d, \
		grm_build_path = %s, local_grammar = %s, \
		result_type = xml, result_encoding = UTF-8, ",
		ASR_RES_PATH,
		SAMPLE_RATE_16K,
		GRM_BUILD_PATH,
		asr_data.grammar_id
		);
	return 0;
}
/* 语音识别结束 */
int xfei_asr_over() {
	if ( listen_status >= 0 ) {
		listen_would = -1;
		while ( listen_status >= 0 ) {	// 确认监听结束
			xfei_listen_result();
			usleep(100*1000);			// 休息100毫秒
		}
	}
}
/* 开始监听语音输入 */
void xfei_listen_on() {
	listen_would = 1;
}
/* 关闭语音监听 */
void xfei_listen_off() {
	listen_would = -1;
}
/* 当前的监听状态 */
int xfei_listen_status() {
	return listen_status >= 0 ? 1 : 0;
}
