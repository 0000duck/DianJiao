#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

/** 播放wav文件 */
char * play_wav(char * wav_file) {
    int ret;
    unsigned int val;
    int dir=0;
    char *buffer;
    int size;
    snd_pcm_uframes_t frames;
    snd_pcm_uframes_t periodsize;
    snd_pcm_t *playback_handle;		//PCM设备句柄pcm.h
    snd_pcm_hw_params_t *hw_params;	//硬件信息和PCM流配置

    FILE *fp = fopen(wav_file, "rb");
	if(fp == NULL)
		return "wav file not found";
	fseek(fp, 100, SEEK_SET);

    //1. 打开PCM，最后一个参数为0意味着标准配置
    ret = snd_pcm_open(&playback_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (ret < 0)
        return "snd_pcm_open error";
    //2. 分配snd_pcm_hw_params_t结构体
    ret = snd_pcm_hw_params_malloc(&hw_params);
    if (ret < 0)
        return "snd_pcm_hw_params_malloc error";
    //3. 初始化hw_params
    ret = snd_pcm_hw_params_any(playback_handle, hw_params);
    if (ret < 0)
        return "snd_pcm_hw_params_any error";
    //4. 初始化访问权限
    ret = snd_pcm_hw_params_set_access(playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (ret < 0)
        return "snd_pcm_hw_params_set_access error";
    //5. 初始化采样格式SND_PCM_FORMAT_U8,8位
    ret = snd_pcm_hw_params_set_format(playback_handle, hw_params, SND_PCM_FORMAT_S16_LE);
    if (ret < 0)
        return "snd_pcm_hw_params_set_format error";
    //6. 设置采样率，如果硬件不支持我们设置的采样率，将使用最接近的
    //val = 44100,有些录音采样频率固定为8KHz
    val = 16000;
    ret = snd_pcm_hw_params_set_rate_near(playback_handle, hw_params, &val, &dir);
    if (ret < 0)
        return "snd_pcm_hw_params_set_rate_near error";
    //7. 设置通道数量  1
    ret = snd_pcm_hw_params_set_channels(playback_handle, hw_params, 1);
    if (ret < 0)
        return "snd_pcm_hw_params_set_channels error";

    /* Set period size to 32 frames. */
    frames = 32;
    periodsize = frames ;
    ret = snd_pcm_hw_params_set_buffer_size_near(playback_handle, hw_params, &periodsize);
    if (ret < 0)
        return "snd_pcm_hw_params_set_buffer_size_near error";	//??? return
    periodsize /= 2;

    ret = snd_pcm_hw_params_set_period_size_near(playback_handle, hw_params, &periodsize, 0);
    if (ret < 0)
        return "snd_pcm_hw_params_set_period_size_near error";	//??? return

    //8. 设置hw_params
    ret = snd_pcm_hw_params(playback_handle, hw_params);
    if (ret < 0)
        return "snd_pcm_hw_params error";

    /* Use a buffer large enough to hold one period */
	snd_pcm_hw_params_get_period_size(hw_params, &frames, &dir);

	size = frames * 2; /* 2 bytes/sample, 2 channels */
	buffer = (char *) malloc(size);

	while (1)
	{
	   ret = fread(buffer, 1, size, fp);
	   if ( ret == 0 )
		   break;	// end of file
	   else if (ret != size) {
		   // shorter read in buffer
	   }
	   //9. 写音频数据到PCM设备
	   while ( (ret = snd_pcm_writei(playback_handle, buffer, frames)) < 0 ) {
		   usleep(2000);
		   if (ret == -EPIPE) {	/* EPIPE means underrun */
				 // 完成硬件参数设置，使设备准备好
				 snd_pcm_prepare(playback_handle);
		   } else if (ret < 0) {
			   // snd_pcm_writei error
		   }
	   }

	}
	//10. 关闭PCM设备句柄
	snd_pcm_close(playback_handle);
	return NULL;
}
