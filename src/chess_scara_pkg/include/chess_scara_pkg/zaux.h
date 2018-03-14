//
//  Header.h
//  single_move
//
//  Created by 谢江文 on 17/10/24.
//  Copyright © 2017年 xjw. All rights reserved.
//

#ifndef zaux_h
#define zaux_h

#include "chess_scara_pkg/zmotion.h"

#define MAX_AXIS_AUX   32
#define MAX_CARD_AUX   16
#define  ZAUX_ERROR(cText,a)


#define OutputDebugString  OutputDebugStringA

#ifdef Z_DEBUG
#undef THIS_FILE
static const char THIS_FILE[] = "zmcaux";
#endif

int g_ZMC_MaxExcuteWaitms = 1000;
int g_ZMC_bIfDebugtoFile = false;
char g_ZMC_aDebugFileName[2048];

#if 0
//错误输出部分
#endif


/*************************************************************
 Description:    //与控制器建立链接， 串口方式.
 Input:          //串口号COMId
 Output:         //卡链接phandle
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_OpenCom(uint32 comid, ZMC_HANDLE * phandle)
{
    int32 iresult;
    iresult = ZMC_OpenCom(comid, phandle);
    
    return iresult;
}

/*************************************************************
 Description:    //快速控制器建立链接
 Input:          //最小串口号uimincomidfind
 Input:          //最大串口号uimaxcomidfind
 Input:          //链接时间uims
 Output:         //有效COM pcomid
 Output:         //卡链接handle
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_SearchAndOpenCom(uint32 uimincomidfind, uint32 uimaxcomidfind,uint* pcomid, uint32 uims, ZMC_HANDLE * phandle)
{
    int32 iresult;
    iresult =ZMC_SearchAndOpenCom(uimincomidfind, uimaxcomidfind, pcomid,uims, phandle);
    
    return iresult;
}

/*************************************************************
 Description:    //可以修改缺省的波特率等设置
 
 uint32 dwByteSize = 8, uint32 dwParity = NOPARITY, uint32 dwStopBits = ONESTOPBIT
 
	Input:          //
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_SetComDefaultBaud(uint32 dwBaudRate, uint32 dwByteSize, uint32 dwParity, uint32 dwStopBits)
{
    int32 iresult;
    iresult = ZMC_SetComDefaultBaud(dwBaudRate,dwByteSize,dwParity,dwStopBits);
    
    return iresult;
}


/*************************************************************
 Description:    //修改控制器IP地址
 Input:          //卡链接handle
 Input:          //IP地址
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_SetIp(ZMC_HANDLE handle, char * ipaddress)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    //生成命令
    sprintf(cmdbuff, "IP_ADDRESS=%s)", ipaddress);
    
    //调用命令执行函数
    //return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    
    return  ZMC_Execute(handle, cmdbuff,1000, cmdbuffAck,2048);

}

/*************************************************************
 Description:    //与控制器建立链接
 Input:          //IP地址，字符串的方式输入
 Output:         //卡链接handle
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_OpenEth(char *ipaddr, ZMC_HANDLE * phandle)
{
    int32 iresult;
    iresult = ZMC_OpenEth(ipaddr, phandle);
    
    return iresult;
}

/*************************************************************
 Description:    //快速检索IP列表
 Input:          //uims 响应时间
 Input:          //addrbufflength		最大长度
 output:			//ipaddrlist		当前晚点IP列表
 Return:         //错误码, ERR_OK表示有搜索到.
 *************************************************************/
int32 __stdcall ZAux_SearchEthlist(char *ipaddrlist, uint32 addrbufflength, uint32 uims)
{
    //自动搜索IP地址
    int32 iresult;
    iresult = ZMC_SearchEth(ipaddrlist, addrbufflength, uims);
    return iresult;
}

/*************************************************************
 Description:    //快速检索控制器
 Input:          //控制器IP地址
 Input:          //响应时间
 Output:         //
 Return:         //错误码, ERR_OK表示有搜索到.
 *************************************************************/
int32 __stdcall ZAux_SearchEth(const char *ipaddress,  uint32 uims)
{
    //自动搜索IP地址
    char buffer[10240];
    int32 iresult;
    
    //
    iresult = ZMC_SearchEth(buffer, 10230, uims);
    if(ERR_OK != iresult)
    {
        return 20010; //错误
    }
    
    //从字符串转换过来
    int ipos =0;
    const char * pstring;
    pstring = buffer;
    
    for(int j= 0; j< 100;j++) //最多100个IP列表
    {
        char buffer2[256];
        buffer2[0] = '\0';
        
        //跳过空格
        while(' ' == pstring[0])
        {
            pstring++;
        }
        
        ipos = sscanf(pstring , "%s", buffer2);// &buffer2
        if(EOF  == ipos)
        {
            break;
        }
        
        //跳过字符
        while((' ' != pstring[0]) && ('\t' != pstring[0]) && ('\0' != pstring[0]))
        {
            pstring++;
        }
        
        if(0 == strcmp(buffer2, ipaddress))
        {
            return ERR_OK;
        }
        
    }
    
    
    return 20010; //错误
}


/*************************************************************
 Description:    //关闭控制器链接
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Close(ZMC_HANDLE  handle)
{
    int32 iresult;
    iresult = ZMC_Close(handle);
    
    return iresult;
}

/*************************************************************
 Description:    //暂停继续运行BAS项目
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Resume(ZMC_HANDLE handle)
{
    int32 iresult;
    iresult = ZMC_Resume(handle);
    
    return iresult;
}

/*************************************************************
 Description:    //暂停
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Pause(ZMC_HANDLE handle)
{
    int32 iresult;
    iresult = ZMC_Pause(handle);
    
    return iresult;
}


/*************************************************************
 Description:    //单个BAS文件生成ZAR并且下载到控制器运行
 Input:          //卡链接handle
 Input:          //Filename BAS文件路径
 Input:          //RAM-ROM  0-RAM  1-ROM
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_BasDown(ZMC_HANDLE handle,const char *Filename,uint32 run_mode )
{
    int32 	iresult;
    char    atemp[4096];
    char    adir[4096];
    
    iresult = ZMC_MakeOneFileZpj(atemp, adir, Filename);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    if (run_mode == 0)
    {
        iresult = ZMC_MakeZarAndRamRun2(handle, atemp, adir, NULL, 0);
        
    }
    else
    {
        iresult = ZMC_MakeZarAndDown2(handle, atemp, adir, NULL, 0);
    }
    
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    iresult = ZMC_Resume(handle);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    return ERR_OK;
}




/*************************************************************
 Description:    //命令跟踪设置.
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_SetTraceFile(int bifTofile, const char *pFilePathName)
{
    g_ZMC_bIfDebugtoFile = bifTofile;
    strcpy(g_ZMC_aDebugFileName, pFilePathName);
    
    return ERR_OK;
}



#if 0
//****************************************************IO指令**************************
// 可以使用 ZMC_GetIn ZMC_GetOutput 等
#endif



/*************************************************************
 Description:    //读取输入信号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetIn(ZMC_HANDLE handle, int ionum , uint32 *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?IN(%d)", ionum);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //打开输出信号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetOp(ZMC_HANDLE handle, int ionum, uint32 iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    //生成命令
    sprintf(cmdbuff, "op(%d,%d)", ionum, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取输出口状态
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetOp(ZMC_HANDLE handle, int ionum, uint32 *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?OP(%d)", ionum);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取模拟量输入信号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetAD(ZMC_HANDLE handle, int ionum , float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?AIN(%d)", ionum);
    
    //调用命令执行函数
    //	iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //打开模拟量输出信号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetDA(ZMC_HANDLE handle, int ionum, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    //生成命令
    sprintf(cmdbuff, "AOUT(%d) = %f", ionum, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取模拟输出口状态
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetDA(ZMC_HANDLE handle, int ionum, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?AOUT(%d)", ionum);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置输入口反转
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetInvertIn(ZMC_HANDLE handle, int ionum, int bifInvert)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    //生成命令
    sprintf(cmdbuff, "INVERT_IN(%d,%d)", ionum, bifInvert);
    
    //调用命令执行函数
    return  ZMC_Execute(handle, cmdbuff, 500,cmdbuffAck,2048);
    //return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取输入口反转状态
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetInvertIn(ZMC_HANDLE handle, int ionum, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?INVERT_IN(%d)", ionum);
    
    //调用命令执行函数
    iresult = ZMC_Execute(handle, cmdbuff, 500,cmdbuffAck,2048);
    //iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}


/*************************************************************
 Description:    //设置pwm频率
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetPwmFreq(ZMC_HANDLE handle, int ionum, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    //生成命令
    sprintf(cmdbuff, "PWM_FREQ(%d) = %f", ionum, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取pwm频率
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetPwmFreq(ZMC_HANDLE handle, int ionum, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
   	if(NULL == pfValue)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?PWM_FREQ(%d)", ionum);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置pwm占空比
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetPwmDuty(ZMC_HANDLE handle, int ionum, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    //生成命令
    sprintf(cmdbuff, "PWM_DUTY(%d) = %f", ionum, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取pwm占空比
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetPwmDuty(ZMC_HANDLE handle, int ionum, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
   	if(NULL == pfValue)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?PWM_DUTY(%d)", ionum);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}



#if 0
//通过modbus快速读取特殊寄存器
#endif

/*************************************************************
 Description:    //参数 快速读取多个输入
 Input:          //卡链接handle
 Output:         //按位存储
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_GetModbusIn(ZMC_HANDLE handle, int ionumfirst, int ionumend, uint8 *pValueList)
{
    if(ionumend < ionumfirst)
    {
        return ERR_AUX_PARAERR;
    }
    
    return ZMC_Modbus_Get0x(handle, 10000+ionumfirst, ionumend-ionumfirst +1, pValueList);
}

/*************************************************************
 Description:    //参数 快速读取多个当前的输出状态
 Input:          //卡链接handle
 Output:         //按位存储
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_GetModbusOut(ZMC_HANDLE handle, int ionumfirst, int ionumend, uint8 *pValueList)
{
    if(ionumend < ionumfirst)
    {
        return ERR_AUX_PARAERR;
    }
    
    return ZMC_Modbus_Get0x(handle, 20000+ionumfirst, ionumend-ionumfirst +1, pValueList);
}

/*************************************************************
 Description:    //参数 快速读取多个当前的DPOS
 Input:          //卡链接handle
 Output:         //按存储
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_GetModbusDpos(ZMC_HANDLE handle, int imaxaxises, float *pValueList)
{
    return ZMC_Modbus_Get4x(handle, 10000, imaxaxises*2, (uint16 *)pValueList);
}

/*************************************************************
 Description:    //参数 快速读取多个当前的MPOS
 Input:          //卡链接handle
 Output:         //按存储
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_GetModbusMpos(ZMC_HANDLE handle, int imaxaxises, float *pValueList)
{
    return ZMC_Modbus_Get4x(handle, 11000, imaxaxises*2, (uint16 *)pValueList);
}

/*************************************************************
 Description:    //参数 快速读取多个当前的速度
 Input:          //卡链接handle
 Output:         //按存储
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_GetModbusCurSpeed(ZMC_HANDLE handle, int imaxaxises, float *pValueList)
{
    return ZMC_Modbus_Get4x(handle, 12000, imaxaxises*2, (uint16 *)pValueList);
}

#if 0
//采用ZMC_DirectCommand 来快速获取一些状态, ZMC_DirectCommand的执行比ZMC_Execute要快
// 只有参数，变量，数组元素等能使用ZMC_DirectCommand
// 20130901以后的版本，一些运动函数也可以调用ZMC_DirectCommand，当运动条件不满足的时候，会立刻返回失败。
// ZMC_DirectCommand调用运动函数时，参数必须是具体的数值，不能是变量表达式。
#endif

#if 0
//**************************************轴参数部分***************************************
#endif


/*************************************************************
 Description:    //通用的参数修改函数 sParam: 填写参数名称
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetParam(ZMC_HANDLE handle,const char *sParam,int iaxis, float fset)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    //生成命令
    sprintf(cmdbuff, "%s(%d)=%f", sParam,iaxis, fset);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //参数 通用的参数读取函数, sParam:填写参数名称
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetParam(ZMC_HANDLE handle,const char *sParam, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?%s(%d)", sParam,iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置加速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetAccel(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "ACCEL(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取加速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetAccel(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?ACCEL(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取叠加轴
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetAddax(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?ADDAX_AXIS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置轴告警信号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetAlmIn(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "ALM_IN(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取告警信号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetAlmIn(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?ALM_IN(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置轴类型
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetAtype(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "ATYPE(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取轴类型
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetAtype(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?ATYPE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取轴状态
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetAxisStatus(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?AXISSTATUS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置轴地址
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetAxisAddress(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "AXIS_ADDRESS(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取轴地址
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetAxisAddress(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?AXIS_ADDRESS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置轴使能
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetAxisEnable(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "AXIS_ENABLE(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取轴使能状态
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetAxisEnable(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?AXIS_ENABLE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置链接速率
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetClutchRate(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "CLUTCH_RATE(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取链接速率
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetClutchRate(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?CLUTCH_RATE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置锁存触发的结束坐标范围点
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetCloseWin(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "CLOSE_WIN(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取锁存触发的结束坐标范围点
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetCloseWin(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?CLOSE_WIN(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置拐角减速
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetCornerMode(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "CORNER_MODE(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取拐角减速
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetCornerMode(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?CORNER_MODE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置回零爬行速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetCreep(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "CREEP(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取回零爬行速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetCreep(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?CREEP(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置原点信号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetDatumIn(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "DATUM_IN(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取原点信号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetDatumIn(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?DATUM_IN(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置减速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetDecel(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "DECEL(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取减速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetDecel(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?DECEL(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置拐角减速角度，开始减速角度，单位为弧度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetDecelAngle(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "DECEL_ANGLE(%d)=%.3f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取拐角开始减速角度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetDecelAngle(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?DECEL_ANGLE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //.3f
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置轴位置
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetDpos(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "DPOS(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取轴位置
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetDpos(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?DPOS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取内部编码器值
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetEncoder(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?ENCODER(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取当前运动的最终位置
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetEndMove(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?ENDMOVE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取当前和缓冲中运动的最终位置，可以用于相对绝对转换
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetEndMoveBuffer(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?ENDMOVE_BUFFER(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置SP运动的结束速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetEndMoveSpeed(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "ENDMOVE_SPEED(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取SP运动的结束速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetEndMoveSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?ENDMOVE_SPEED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置错误标记，和AXISSTATUS做与运算来决定哪些错误需要关闭WDOG。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetErrormask(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "ERRORMASK(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取错误标记，和AXISSTATUS做与运算来决定哪些错误需要关闭WDOG。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetErrormask(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?ERRORMASK(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置快速JOG输入
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetFastJog(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FAST_JOG(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取快速JOG输入
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFastJog(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FAST_JOG(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置快速减速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetFastDec(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FASTDEC(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取快速减速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFastDec(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FASTDEC(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取随动误差
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFe(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置最大允许的随动误差值
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetFeLimit(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FE_LIMIT(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取最大允许的随动误差值
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFeLimit(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FE_LIMIT(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置报警时随动误差值
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetFRange(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FE_RANGE(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取报警时的随动误差值
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFeRange(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FE_RANGE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}


/*************************************************************
 Description:    //设置保持输入
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetFholdIn(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FHOLD_IN(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取保持输入
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFholdIn(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FHOLD_IN(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}


/*************************************************************
 Description:    //设置轴保持速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetFhspeed(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FHSPEED(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取轴保持速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFhspeed(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FHSPEED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置SP运动的运行速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetForceSpeed(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FORCE_SPEED(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取SP运动的运行速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetForceSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FORCE_SPEED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置正向软限位
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetFsLimit(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FS_LIMIT(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取正向软限位
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFsLimit(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FS_LIMIT(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置小圆限速最小半径
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetFullSpRadius(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FULL_SP_RADIUS(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取小圆限速最小半径
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFullSpRadius(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FULL_SP_RADIUS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置正向硬限位输入
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetFwdIn(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FWD_IN(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取正向硬限位输入
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFwdIn(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FWD_IN(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置正向JOG输入
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetFwdJog(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "FWD_JOG(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取正向JOG输入
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetFwdJog(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?FWD_JOG(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取轴是否运动结束
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetIfIdle(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?IDLE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置脉冲输出模式
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetInvertStep(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "INVERT_STEP(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取脉冲输出模式
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetInvertStep(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?INVERT_STEP(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置插补时轴是否参与速度计算，缺省参与（1）。此参数只对直线和螺旋的第三个轴起作用
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetInterpFactor(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "INTERP_FACTOR(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取插补时轴是否参与速度计算，缺省参与（1）。此参数只对直线和螺旋的第三个轴起作用
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetInterpFactor(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?INTERP_FACTOR(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置JOG时速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetJogSpeed(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "JOGSPEED(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取JOG时速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetJogSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?JOGSPEED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取当前链接运动的参考轴号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetLinkax(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?LINKAX(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取当前除了当前运动是否还有缓冲
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetLoaded(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?LOADED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置轴起始速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetLspeed(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "LSPEED(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取轴起始速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetLspeed(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?LSPEED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置回零反找等待时间
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetHomeWait(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "HOMEWAIT(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取回零反找等待时间
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetHomeWait(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?HOMEWAIT(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取编码器锁存示教返回状态
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetMark(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?MARK(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取编码器锁存示教返回状态
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetMarkB(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?MARKB(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置脉冲输出最高频率
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetMaxSpeed(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "MAX_SPEED(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取脉冲输出最高频率
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetMaxSpeed(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?MAX_SPEED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置连续插补
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetMerge(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "MERGE(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取连续插补状态
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetMerge(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?MERGE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取当前被缓冲起来的运动个数
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetMovesBuffered(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?MOVES_BUFFERED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取当前正在运动指令的MOVE_MARK标号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetMoveCurmark(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?MOVE_CURMARK(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置运动指令的MOVE_MARK标号
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetMovemark(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "MOVE_MARK(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}


/*************************************************************
 Description:    //设置反馈位置
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetMpos(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "MPOS(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取反馈位置
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetMpos(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?MPOS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取反馈速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetMspeed(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?MSPEED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取当前正在运动指令类型
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetMtype(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?MTYPE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取当前正在进行的运动指令后面的第一条指令类型，当插补联动时，对从轴总是返回主轴的运动指令类型
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetNtype(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?NTYPE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置修改偏移位置
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetOffpos(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "OFFPOS(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取修改偏移位置
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetOffpos(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?OFFPOS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置锁存触发的结束坐标范围点。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetOpenWin(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "OPEN_WIN(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取锁存触发的结束坐标范围点。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetOpenWin(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?OPEN_WIN(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取返回锁存的测量反馈位置(MPOS)
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetRegPos(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?REG_POS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取返回锁存的测量反馈位置(MPOS)
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetRegPosB(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?REG_POSB(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取返回轴当前运动还未完成的距离
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetRemain(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?REMAIN(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //参数  轴剩余的缓冲, 按直线段来计算
 REMAIN_BUFFER为唯一一个可以加AXIS并用ZMC_DirectCommand获取的.
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetRemain_LineBuffer(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?REMAIN_BUFFER(1) AXIS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}


/*************************************************************
 Description:    //参数  轴剩余的缓冲, 按最复杂的空间圆弧来计算
 REMAIN_BUFFER为唯一一个可以加AXIS并用ZMC_DirectCommand获取的.
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetRemain_Buffer(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?REMAIN_BUFFER() AXIS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}


/*************************************************************
 Description:    //设置根据REP_OPTION设置来自动循环轴DPOS和MPOS坐标。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetRepDist(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "REP_DIST(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取根据REP_OPTION设置来自动循环轴DPOS和MPOS坐标。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetRepDist(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?REP_DIST(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置坐标重复设置
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetRepOption(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "REP_OPTION(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取坐标重复设置
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetRepOption(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?REP_OPTION(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置负向硬件限位开关对应的输入点编号，-1无效。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetRevIn(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "Rev_In(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取负向硬件限位开关对应的输入点编号，-1无效。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetRevIn(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?REV_IN(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置负向JOG输入对应的输入点编号，-1无效。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetRevJog(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "REV_JOG(%d)=%d", iaxis, iValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取负向JOG输入对应的输入点编号，-1无效。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetRevJog(ZMC_HANDLE handle, int iaxis, int *piValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?REV_JOG(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置负向软限位位置。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetRsLimit(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "RS_LIMIT(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取负向软限位位置。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetRsLimit(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?RS_LIMIT(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置轴速度，单位为units/s，当多轴运动时，作为插补运动的速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetSpeed(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "SPEED(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取轴速度，单位为units/s，当多轴运动时，作为插补运动的速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?Speed(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置 S曲线设置。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetSramp(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "SRAMP(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取 S曲线设置。
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetSramp(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?SRAMP(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置 自定义速度的SP运动的起始速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetStartMoveSpeed(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "STARTMOVE_SPEED(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取自定义速度的SP运动的起始速度
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetStartMoveSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?STARTMOVE_SPEED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置 减速到最低的最小拐角
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetStopAngle(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "STOP_ANGLE(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取减速到最低的最小拐角
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetStopAngle(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?STOP_ANGLE(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置 脉冲当量
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetUnits(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if( iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "UNITS(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取脉冲当量
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetUnits(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?UNITS(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //设置 减速倒角
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetZsmooth(ZMC_HANDLE handle, int iaxis, float fValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    if(iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "ZSMOOTH(%d)=%f", iaxis, fValue);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
 Description:    //读取倒角半径
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetZsmooth(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?ZSMOOTH(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //读取返回轴当前当前运动和缓冲运动还未完成的距离
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetVectorBuffered(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?VECTOR_BUFFERED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //参数
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetVpSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?VP_SPEED(%d)", iaxis);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}


/*************************************************************
 Description:    //全局变量读取, 也可以是参数等等
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetVariablef(ZMC_HANDLE handle, const char *pname, float *pfValue)
{
    int i;
    float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?%s", pname);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%f",pfValue);
    
    return ERR_OK;
}

/*************************************************************
 Description:    //全局变量读取, 也可以是参数等等
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetVariableInt(ZMC_HANDLE handle, const char *pname, int *piValue)
{
    int i;
    //float ftemp;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == piValue)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "?%s", pname);
    
    //调用命令执行函数
    //iresult = ZMC_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    //
    sscanf(cmdbuffAck, "%d",piValue);
    
    return ERR_OK;
}


///////////////////////  只有下面的运动函数支持直接调用，并不是所有的指令都支持
///////////////////////  必须 20130901 以后的控制器版本支持

/*************************************************************
 Description:    //BASE指令调用
 
 仅仅修改在线命令的BASE列表，不对控制器的运行任务的BASE进行修改.
 修改后，后续的所有MOVE等指令都是以这个BASE为基础
 
	Input:          //卡链接handle
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Base(ZMC_HANDLE handle, int imaxaxises, int *piAxislist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    //
    
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "BASE(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%d,",piAxislist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%d)",piAxislist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

int32 __stdcall ZAux_Execute_Base(ZMC_HANDLE handle, int imaxaxises, int *piAxislist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    char  cmdbuffAck[2048];
    
    //
    
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "BASE(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%d,",piAxislist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%d)",piAxislist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    // return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
    iresult = ZMC_Execute(handle, cmdbuff, 1000, cmdbuffAck,2048);

    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    return ERR_OK;

}



/*************************************************************
 Description:    //定义DPOS
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Defpos(ZMC_HANDLE handle, int imaxaxises, float *pfDposlist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    char  cmdbuffAck[2048];
    
    //
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "DEFPOS(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDposlist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDposlist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck,2048);
}

/*************************************************************
 Description:    //相对插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Move(ZMC_HANDLE handle, int imaxaxises, float *pfDisancelist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    //
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "MOVE(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDisancelist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //相对插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveSp(ZMC_HANDLE handle, int imaxaxises, float *pfDisancelist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    //
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "MOVESP(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDisancelist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveAbs(ZMC_HANDLE handle, int imaxaxises, float *pfDisancelist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    //
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "MOVEABS(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDisancelist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

int32 __stdcall ZAux_Execute_MoveAbs(ZMC_HANDLE handle, int imaxaxises, float *pfDisancelist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    char  cmdbuffAck[2048];
    
    //
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "MOVEABS(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDisancelist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    // return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);

    iresult = ZMC_Execute(handle, cmdbuff, 1000, cmdbuffAck,2048);

    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    if(0 == strlen(cmdbuffAck))
    {
        return ERR_NOACK;
    }
    
    return ERR_OK;
}

/*************************************************************
 Description:    //插补 BASE后立刻调用运动函数.
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_BaseAndMoveAbs(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float *pfDisancelist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    
    //生成命令
    strcpy(cmdbuff, "BASE(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%d,",piAxislist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%d)",piAxislist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //换行
    strcat(cmdbuff, "\n");
    
    //生成命令
    strcat(cmdbuff, "MOVEABS(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDisancelist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

int32 __stdcall ZAux_Execute_BaseAndMoveAbs(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float *pfDisancelist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    char  cmdbuffAck[2048];
    
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    
    //生成命令
    strcpy(cmdbuff, "BASE(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%d,",piAxislist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%d)",piAxislist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //换行
    strcat(cmdbuff, "\n");
    
    //生成命令
    strcat(cmdbuff, "MOVEABS(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDisancelist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    // return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
    iresult = ZMC_Execute(handle, cmdbuff, 1000, cmdbuffAck, 2048);

    if(ERR_OK != iresult)
    {
        return iresult;
    }
    
    //
    // if(0 == strlen(cmdbuffAck))
    // {
    //     return ERR_NOACK;
    // }
    
    return ERR_OK;
}

/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveAbsSp(ZMC_HANDLE handle, int imaxaxises, float *pfDisancelist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "MOVEABSSP(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDisancelist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveModify(ZMC_HANDLE handle, int imaxaxises, float *pfDisancelist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "MOVEMODIFY(");
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDisancelist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 
 end1              第一个轴运动坐标
 end2              第二个轴运动坐标
 centre1    第一个轴运动圆心，相对与起始点。
 centre2    第二个轴运动圆心，相对与起始点。
 direction  0-逆时针，1-顺时针
 
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveCirc(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVECIRC(%f,%f,%f,%f,%d)", fend1,fend2,fcenter1,fcenter2,idirection);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 
 end1              第一个轴运动坐标
 end2              第二个轴运动坐标
 centre1    第一个轴运动圆心，相对与起始点。
 centre2    第二个轴运动圆心，相对与起始点。
 direction  0-逆时针，1-顺时针
 
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveCircSp(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVECIRCSP(%f,%f,%f,%f,%d)", fend1,fend2,fcenter1,fcenter2,idirection);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 
 end1              第一个轴运动坐标，绝对位置
 end2              第二个轴运动坐标，绝对位置
 centre1    第一个轴运动圆心，绝对位置
 centre2    第二个轴运动圆心，绝对位置
 direction  0-逆时针，1-顺时针
 
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveCircAbs(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVECIRCABS(%f,%f,%f,%f,%d)", fend1,fend2,fcenter1,fcenter2,idirection);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 
 end1              第一个轴运动坐标，绝对位置
 end2              第二个轴运动坐标，绝对位置
 centre1    第一个轴运动圆心，绝对位置
 centre2    第二个轴运动圆心，绝对位置
 direction  0-逆时针，1-顺时针
 
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveCircAbsSp(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVECIRCABSSP(%f,%f,%f,%f,%d)", fend1,fend2,fcenter1,fcenter2,idirection);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}



/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 
 mid1       第一个轴中间点，相对起始点距离
 mid2       第二个轴中间点，相对起始点距离
 end1              第一个轴结束点，相对起始点距离
 end2              第二个轴结束点，相对起始点距离
 
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveCirc2(ZMC_HANDLE handle, float fmid1, float fmid2, float fend1, float fend2)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVECIRC2(%f,%f,%f,%f)", fmid1,fmid2,fend1,fend2);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 
 mid1       第一个轴中间点，绝对位置
 mid2       第二个轴中间点，绝对位置
 end1              第一个轴结束点，绝对位置
 end2              第二个轴结束点，绝对位置
 
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveCirc2Abs(ZMC_HANDLE handle, float fmid1, float fmid2, float fend1, float fend2)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVECIRC2ABS(%f,%f,%f,%f)", fmid1,fmid2,fend1,fend2);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 
 mid1       第一个轴中间点，相对起始点距离
 mid2       第二个轴中间点，相对起始点距离
 end1              第一个轴结束点，相对起始点距离
 end2              第二个轴结束点，相对起始点距离
 
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveCirc2Sp(ZMC_HANDLE handle, float fmid1, float fmid2, float fend1, float fend2)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVECIRC2SP(%f,%f,%f,%f)", fmid1,fmid2,fend1,fend2);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 
 mid1       第一个轴中间点，绝对位置
 mid2       第二个轴中间点，绝对位置
 end1              第一个轴结束点，绝对位置
 end2              第二个轴结束点，绝对位置
 
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveCirc2AbsSp(ZMC_HANDLE handle, float fmid1, float fmid2, float fend1, float fend2)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVECIRC2ABSSP(%f,%f,%f,%f)", fmid1,fmid2,fend1,fend2);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}



/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 end1              第一个轴运动坐标
 
	end2              第二个轴运动坐标
	
 centre1    第一个轴运动圆心，相对与起始点
 
 centre2    第二个轴运动圆心，相对与起始点
 
 direction  0-逆时针，1-顺时针
 
 distance3第三个轴运动距离。
 
 mode      第三轴的速度计算:
 0(缺省)
 第三轴参与速度计算。
 1
 第三轴不参与速度计算。
 
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MHelical(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fDistance3, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MHELICAL(%f,%f,%f,%f,%d,%f,%d)", fend1,fend2,fcenter1,fcenter2,idirection, fDistance3, imode);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 end1              第一个轴运动坐标
 
	end2              第二个轴运动坐标
	
 centre1    第一个轴运动圆心，相对与起始点
 
 centre2    第二个轴运动圆心，相对与起始点
 
 direction  0-逆时针，1-顺时针
 
 distance3第三个轴运动距离。
 
 mode      第三轴的速度计算:
 0(缺省)
 第三轴参与速度计算。
 1
 第三轴不参与速度计算。
 
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MHelicalAbs(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fDistance3, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MHELICALABS(%f,%f,%f,%f,%d,%f,%d)", fend1,fend2,fcenter1,fcenter2,idirection, fDistance3, imode);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 end1              第一个轴运动坐标
 
	end2              第二个轴运动坐标
	
 centre1    第一个轴运动圆心，相对与起始点
 
 centre2    第二个轴运动圆心，相对与起始点
 
 direction  0-逆时针，1-顺时针
 
 distance3第三个轴运动距离。
 
 mode      第三轴的速度计算:
 0(缺省)
 第三轴参与速度计算。
 1
 第三轴不参与速度计算。
 
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MHelicalSp(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fDistance3, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MHELICALSP(%f,%f,%f,%f,%d,%f,%d)", fend1,fend2,fcenter1,fcenter2,idirection, fDistance3, imode);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 end1              第一个轴运动坐标
 
	end2              第二个轴运动坐标
	
 centre1    第一个轴运动圆心，相对与起始点
 
 centre2    第二个轴运动圆心，相对与起始点
 
 direction  0-逆时针，1-顺时针
 
 distance3第三个轴运动距离。
 
 mode      第三轴的速度计算:
 0(缺省)
 第三轴参与速度计算。
 1
 第三轴不参与速度计算。
 
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MHelicalAbsSp(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fDistance3, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MHELICALABSSP(%f,%f,%f,%f,%d,%f,%d)", fend1,fend2,fcenter1,fcenter2,idirection, fDistance3, imode);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 mid1       第一个轴中间点
 
	mid2       第二个轴中间点
	
 end1              第一个轴结束点
 
 end2              第二个轴结束点
 
 distance3第三个轴运动距离
 
 mode      第三轴的速度计算:
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MHelical2(ZMC_HANDLE handle, float fmid1, float fmid2, float fend1, float fend2, float fDistance3, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MHELICAL2(%f,%f,%f,%f,%f,%d)", fmid1,fmid2,fend1,fend2, fDistance3, imode);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 mid1       第一个轴中间点
 
	mid2       第二个轴中间点
	
 end1              第一个轴结束点
 
 end2              第二个轴结束点
 
 distance3   第三个轴运动结束点
 
 mode      第三轴的速度计算:
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MHelical2Abs(ZMC_HANDLE handle, float fmid1, float fmid2, float fend1, float fend2, float fDistance3, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MHELICAL2ABS(%f,%f,%f,%f,%f,%d)", fmid1,fmid2,fend1,fend2, fDistance3, imode);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 mid1       第一个轴中间点
 
	mid2       第二个轴中间点
	
 end1              第一个轴结束点
 
 end2              第二个轴结束点
 
 distance3第三个轴运动距离
 
 mode      第三轴的速度计算:
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MHelical2Sp(ZMC_HANDLE handle, float fmid1, float fmid2, float fend1, float fend2, float fDistance3, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MHELICAL2SP(%f,%f,%f,%f,%f,%d)", fmid1,fmid2,fend1,fend2, fDistance3, imode);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 mid1       第一个轴中间点
 
	mid2       第二个轴中间点
	
 end1              第一个轴结束点
 
 end2              第二个轴结束点
 
 distance3   第三个轴运动结束点
 
 mode      第三轴的速度计算:
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MHelical2AbsSp(ZMC_HANDLE handle, float fmid1, float fmid2, float fend1, float fend2, float fDistance3, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MHELICAL2ABSSP(%f,%f,%f,%f,%f,%d)", fmid1,fmid2,fend1,fend2, fDistance3, imode);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}



/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MEclipse(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MECLIPSE(%f,%f,%f,%f,%d,%f,%f)", fend1,fend2,fcenter1,fcenter2,idirection, fADis, fBDis);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MEclipseAbs(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MECLIPSEABS(%f,%f,%f,%f,%d,%f,%f)", fend1,fend2,fcenter1,fcenter2,idirection, fADis, fBDis);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MEclipseSp(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MECLIPSESP(%f,%f,%f,%f,%d,%f,%f)", fend1,fend2,fcenter1,fcenter2,idirection, fADis, fBDis);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MEclipseAbsSp(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MECLIPSEABSSP(%f,%f,%f,%f,%d,%f,%f)", fend1,fend2,fcenter1,fcenter2,idirection, fADis, fBDis);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补 椭圆 + 螺旋
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MEclipseHelical(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis, float fDistance3)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MECLIPSE(%f,%f,%f,%f,%d,%f,%f,%f)", fend1,fend2,fcenter1,fcenter2,idirection, fADis, fBDis, fDistance3);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补  椭圆 + 螺旋
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MEclipseHelicalAbs(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis,float fDistance3)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MECLIPSEABS(%f,%f,%f,%f,%d,%f,%f,%f)", fend1,fend2,fcenter1,fcenter2,idirection, fADis, fBDis,fDistance3);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补 椭圆 + 螺旋
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MEclipseHelicalSp(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis, float fDistance3)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MECLIPSESP(%f,%f,%f,%f,%d,%f,%f,%f)", fend1,fend2,fcenter1,fcenter2,idirection, fADis, fBDis, fDistance3);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补  椭圆 + 螺旋
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MEclipseHelicalAbsSp(ZMC_HANDLE handle, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis,float fDistance3)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MECLIPSEABSSP(%f,%f,%f,%f,%d,%f,%f,%f)", fend1,fend2,fcenter1,fcenter2,idirection, fADis, fBDis,fDistance3);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补  空间圆弧
 Input:          //卡链接handle
 end1              第1个轴运动距离参数1
 
 end2              第2个轴运动距离参数1
 
	end3              第3个轴运动距离参数1
	
 centre1    第1个轴运动距离参数2
 
 centre2    第2个轴运动距离参数2
 
 centre3    第3个轴运动距离参数2
 
 mode      指定前面参数的意义
 0 当前点，中间点，终点三点定圆弧，距离参数1为终点距离，距离参数2为中间点距离。
 1 走最小的圆弧，距离参数1为终点距离，距离参数2为圆心的距离。
 2 当前点，中间点，终点三点定圆，距离参数1为终点距离，距离参数2为中间点距离。
 3 先走最小的圆弧，再继续走完整圆，距离参数1为终点距离，距离参数2为圆心的距离。
 
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MSpherical(ZMC_HANDLE handle, float fend1, float fend2, float fend3, float fcenter1, float fcenter2, float fcenter3, int imode, float fcenter4, float fcenter5)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MSPHERICAL(%f,%f,%f,%f,%f,%f,%d,%f,%f)", fend1,fend2,fend3,fcenter1,fcenter2,fcenter3,imode,fcenter4,fcenter5);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补  空间圆弧
 Input:          //卡链接handle
 end1              第1个轴运动距离参数1
 
 end2              第2个轴运动距离参数1
 
	end3              第3个轴运动距离参数1
	
 centre1    第1个轴运动距离参数2
 
 centre2    第2个轴运动距离参数2
 
 centre3    第3个轴运动距离参数2
 
 mode      指定前面参数的意义
 0 当前点，中间点，终点三点定圆弧，距离参数1为终点距离，距离参数2为中间点距离。
 1 走最小的圆弧，距离参数1为终点距离，距离参数2为圆心的距离。
 2 当前点，中间点，终点三点定圆，距离参数1为终点距离，距离参数2为中间点距离。
 3 先走最小的圆弧，再继续走完整圆，距离参数1为终点距离，距离参数2为圆心的距离。
 
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MSphericalSp(ZMC_HANDLE handle, float fend1, float fend2, float fend3, float fcenter1, float fcenter2, float fcenter3, int imode, float fcenter4, float fcenter5)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MSPHERICALSP(%f,%f,%f,%f,%f,%f,%d,%f,%f)", fend1,fend2,fend3,fcenter1,fcenter2,fcenter3,imode, fcenter4, fcenter5);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //渐开线圆弧插补运动，相对移动方式，当起始半径0直接扩散时从0角度开始
 Input:          //卡链接handle
 
 centre1: 第1轴圆心的相对距离
 
	centre2: 第2轴圆心的相对距离
	
 circles:  要旋转的圈数，可以为小数圈，负数表示顺时针.
 
 pitch:   每圈的扩散距离，可以为负。
 
 distance3        第3轴螺旋的功能，指定第3轴的相对距离，此轴不参与速度计算。
 
 distance4        第4轴螺旋的功能，指定第4轴的相对距离，此轴不参与速度计算。
 
 
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveSpiral(ZMC_HANDLE handle, float centre1, float centre2, float circles, float pitch, float distance3, float distance4)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVESPIRAL(%f,%f,%f,%f,%f,%f)", centre1,centre2,circles,pitch,distance3,distance4);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //渐开线圆弧插补运动，相对移动方式，当起始半径0直接扩散时从0角度开始
 Input:          //卡链接handle
 
 centre1: 第1轴圆心的相对距离
 
	centre2: 第2轴圆心的相对距离
	
 circles:  要旋转的圈数，可以为小数圈，负数表示顺时针.
 
 pitch:   每圈的扩散距离，可以为负。
 
 distance3        第3轴螺旋的功能，指定第3轴的相对距离，此轴不参与速度计算。
 
 distance4        第4轴螺旋的功能，指定第4轴的相对距离，此轴不参与速度计算。
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveSpiralSp(ZMC_HANDLE handle, float centre1, float centre2, float circles, float pitch, float distance3, float distance4)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVESPIRALSP(%f,%f,%f,%f,%f,%f)", centre1,centre2,circles,pitch,distance3,distance4);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //空间直线运动，根据下一个直线运动的绝对坐标在拐角自动插入圆弧，加入圆弧后会使得运动的终点与直线的终点不一致，拐角过大时不会插入圆弧，当距离不够时会自动减小半径
 Input:          //卡链接handle
 end1              第1个轴运动绝对坐标
 end2              第2个轴运动绝对坐标
 end3              第3个轴运动绝对坐标
 next1      第1个轴下一个直线运动绝对坐标
 next2      第2个轴下一个直线运动绝对坐标
 next3      第3个轴下一个直线运动绝对坐标
 radius      插入圆弧的半径，当过大的时候自动缩小。
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveSmooth(ZMC_HANDLE handle, float end1, float end2, float end3, float next1, float next2, float next3, float radius)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVESMOOTH(%f,%f,%f,%f,%f,%f,%f)", end1,end2,end3,next1,next2,next3,radius);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //空间直线运动，根据下一个直线运动的绝对坐标在拐角自动插入圆弧，加入圆弧后会使得运动的终点与直线的终点不一致，拐角过大时不会插入圆弧，当距离不够时会自动减小半径
 Input:          //卡链接handle
 end1              第1个轴运动绝对坐标
 end2              第2个轴运动绝对坐标
 end3              第3个轴运动绝对坐标
 next1      第1个轴下一个直线运动绝对坐标
 next2      第2个轴下一个直线运动绝对坐标
 next3      第3个轴下一个直线运动绝对坐标
 radius      插入圆弧的半径，当过大的时候自动缩小。
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveSmoothSp(ZMC_HANDLE handle, float end1, float end2, float end3, float next1, float next2, float next3, float radius)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVESMOOTHSP(%f,%f,%f,%f,%f,%f,%f)", end1,end2,end3,next1,next2,next3,radius);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //运动暂停
 Input:          //卡链接handle
 
 0（缺省） 暂停当前运动。
 1 在当前运动完成后正准备执行下一条运动指令时暂停。
 2 在当前运动完成后正准备执行下一条运动指令时，并且两条指令的MARK标识不一样时暂停。这个模式可以用于一个动作由多个指令来实现时，可以在一整个动作完成后暂停。
 
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MovePause(ZMC_HANDLE handle, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVE_PAUSE(%d)", imode);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //运动暂停
 Input:          //卡链接handle
 
 0（缺省） 暂停当前运动。
 1 在当前运动完成后正准备执行下一条运动指令时暂停。
 2 在当前运动完成后正准备执行下一条运动指令时，并且两条指令的MARK标识不一样时暂停。这个模式可以用于一个动作由多个指令来实现时，可以在一整个动作完成后暂停。
 
	Output:         //
	Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveResume(ZMC_HANDLE handle)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVE_RESUME");
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //在当前的运动末尾位置增加速度限制，用于强制拐角减速
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveLimit(ZMC_HANDLE handle, float limitspeed)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVELIMIT(%f)", limitspeed);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //在运动缓冲中加入输出指令
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveOp(ZMC_HANDLE handle, int ioutnum, int ivalue)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVE_OP(%d,%d)", ioutnum, ivalue);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //在运动缓冲中加入输出指令
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveOpMulti(ZMC_HANDLE handle, int ioutnumfirst, int ioutnumend, int ivalue)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVE_OP(%d,%d,%d)", ioutnumfirst, ioutnumend, ivalue);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //在运动缓冲中加入输出指令
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveOp2(ZMC_HANDLE handle, int ioutnum, int ivalue, int iofftimems)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVE_OP2(%d,%d,%d)", ioutnum, ivalue, iofftimems);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //在运动缓冲中加入AOUT输出指令
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveAout(ZMC_HANDLE handle, int ioutnum, float fvalue)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVE_AOUT(%d,%f)", ioutnum, fvalue);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}



/*************************************************************
 Description:    //在运动缓冲中加入延时指令
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveDelay(ZMC_HANDLE handle, int itimems)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVE_WA(%d)", itimems);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_MoveTurnabs(ZMC_HANDLE handle, int tablenum ,int imaxaxises, float *pfDisancelist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    //
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "MOVE_TURNABS(");
    
    sprintf(tempbuff, "%d,",tablenum);
    strcat(cmdbuff, tempbuff);
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDisancelist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
 Input:          //卡链接handle
 tablenum       存储旋转参数的table编号
 refpos1    第一个轴参考点，绝对位置
 refpos2    第二个轴参考点，绝对位置
 mode      1-参考点是当前点前面，2-参考点是结束点后面，3-参考点在中间，采用三点定圆的方式。
 end1              第一个轴结束点，绝对位置
 end2              第二个轴结束点，绝对位置
 imaxaxises        螺旋轴个数
 pfDisancelist	螺旋轴距离列表
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_McircTurnabs(ZMC_HANDLE handle, int tablenum ,float refpos1,float refpos2,int mode,float end1,float end2,int imaxaxises, float *pfDisancelist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    //
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "MCIRC_TURNABS(");
    
    sprintf(tempbuff, "%d,%f,%f,%d,%f,%f,",tablenum,refpos1,refpos2,mode,end1,end2);
    strcat(cmdbuff, tempbuff);
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%f,",pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%f)",pfDisancelist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //电子凸轮
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Cam(ZMC_HANDLE handle, int istartpoint, int iendpoint, float ftablemulti, float fDistance)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "CAM(%d,%d,%f,%f)", istartpoint,iendpoint,ftablemulti,fDistance);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //电子凸轮
 Input:          //卡链接handle
 
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Cambox(ZMC_HANDLE handle, int istartpoint, int iendpoint, float ftablemulti, float fDistance, int ilinkaxis, int ioption, float flinkstartpos)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "CAMBOX(%d,%d,%f,%f,%d,%d,%f)", istartpoint,iendpoint,ftablemulti,fDistance, ilinkaxis, ioption, flinkstartpos);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //连接 特殊凸轮
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Movelink(ZMC_HANDLE handle, float fDistance, float fLinkDis, float fLinkAcc, float fLinkDec,int iLinkaxis, int ioption, float flinkstartpos)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVELINK(%f,%f,%f,%f,%d,%d,%f)", fDistance, fLinkDis, fLinkAcc,fLinkDec,iLinkaxis,ioption,flinkstartpos);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //连接 特殊凸轮
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Moveslink(ZMC_HANDLE handle, float fDistance, float fLinkDis, float startsp, float endsp,int iLinkaxis, int ioption, float flinkstartpos)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "MOVESLINK(%f,%f,%f,%f,%d,%d,%f)", fDistance, fLinkDis, startsp,endsp,iLinkaxis,ioption,flinkstartpos);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //连接 同步运动指令
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Connect(ZMC_HANDLE handle, float ratio, int link_axis,int move_axis)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "CONNECT(%f,%d) AXIS(%d)", ratio, link_axis,move_axis);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //连接 同步运动指令
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Connpath(ZMC_HANDLE handle, float ratio, int link_axis,int move_axis)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "CONNPATH(%f,%d) AXIS(%d)", ratio, link_axis,move_axis);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //位置锁存指令
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Regist(ZMC_HANDLE handle, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "REGIST(%d)", imode);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //编码器输入齿轮比，缺省(1,1)
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_EncoderRatio(ZMC_HANDLE handle, int mpos_count,int input_count)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "ENCODER_RATIO(%d,%d)", mpos_count,input_count);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}


/*************************************************************
 Description:    //编码器输入齿轮比，缺省(1,1)
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_StepRatio(ZMC_HANDLE handle, int mpos_count,int input_count)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "STEP_RATIO(%d,%d)", mpos_count,input_count);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //所有轴立即停止
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Rapidstop(ZMC_HANDLE handle, int imode)
{
    //int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    //生成命令
    sprintf(cmdbuff, "RAPIDSTOP(%d)", imode);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //多个轴运动停止
 Input:          //卡链接handle  轴号， 距离
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_CancelAxisList(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, int imode)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "CANCEL(%d) AXIS(%d)\n", imode, piAxislist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "CANCEL(%d) AXIS(%d)",imode, piAxislist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //CONNFRAME机械手指令
 
 Input:          //卡链接handle
 frame机械手类型
 imaxaxises 关联虚拟轴个数
 piAxislist 虚拟轴列表
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Connframe(ZMC_HANDLE handle, int frame, int tablenum , int imaxaxises , int *piAxislist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    //
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "CONNFRAME(");
    
    sprintf(tempbuff, "%d,%d,",frame,tablenum);
    strcat(cmdbuff, tempbuff);
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%d,",piAxislist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%d)",piAxislist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //CONNREFRAME机械手指令
 
 Input:          //卡链接handle
 frame机械手类型
 imaxaxises 关联关节轴个数
 piAxislist 关节轴列表
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Connreframe(ZMC_HANDLE handle, int frame, int tablenum , int imaxaxises , int *piAxislist)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    //
    if(0 > imaxaxises || imaxaxises > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    strcpy(cmdbuff, "CONNREFRAME(");
    
    sprintf(tempbuff, "%d,%d,",frame,tablenum);
    strcat(cmdbuff, tempbuff);
    
    for(i = 0; i< imaxaxises-1; i++)
    {
        //
        sprintf(tempbuff, "%d,",piAxislist[i]);
        strcat(cmdbuff, tempbuff);
    }
    
    //
    sprintf(tempbuff, "%d)",piAxislist[imaxaxises-1]);
    strcat(cmdbuff, tempbuff);
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}



/*********************************单轴运动
 
 /*************************************************************
 Description:    //叠加
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Singl_Addax(ZMC_HANDLE handle, int iaxis, int iaddaxis)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(0 > iaxis || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "ADDAX(%d) AXIS(%d)", iaddaxis, iaxis);
    
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck,2048);
}


/*************************************************************
 Description:    //单轴运动停止
 Input:          //卡链接handle  轴号， 模式
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Singl_Cancel(ZMC_HANDLE handle, int iaxis, int imode)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(0 > iaxis || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "CANCEL(%d) AXIS(%d)", imode, iaxis);
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //连续运动
 Input:          //卡链接handle  轴号， 方向
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Singl_Vmove(ZMC_HANDLE handle, int iaxis, int idir)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(0 > iaxis || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "VMOVE(%d) AXIS(%d)", idir, iaxis);
    
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck,2048);
}

/*************************************************************
 Description:    //回零
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Singl_Datum(ZMC_HANDLE handle, int iaxis, int imode)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(0 > iaxis || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "DATUM(%d) AXIS(%d)", imode, iaxis);
    
    
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck,2048);
}

/*************************************************************
 Description:    //单轴运动
 Input:          //卡链接handle  轴号， 距离
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Singl_Move(ZMC_HANDLE handle, int iaxis, float fdistance)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    if(0 > iaxis || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "MOVE(%f) AXIS(%d)", fdistance, iaxis);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
 Description:    //单轴运动
 Input:          //卡链接handle  轴号， 距离
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_Singl_MoveAbs(ZMC_HANDLE handle, int iaxis, float fdistance)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    
    if(0 > iaxis || iaxis > MAX_AXIS_AUX)
    {
        return  ERR_AUX_PARAERR;
    }
    
    //生成命令
    sprintf(cmdbuff, "MOVEABS(%f) AXIS(%d)", fdistance, iaxis);
    
    
    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}






/*********************内存操作
 /*************************************************************
 Description:    //写VR,
 Input:          //卡链接handle  轴号， 距离
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetVrf(ZMC_HANDLE handle,int vrstartnum, int numes, float *pfValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    if(NULL == pfValue || numes < 0)
    {
        return  ERR_AUX_PARAERR;
    }
    
    for(i = 0; i< numes; i++)
    {
        //
        sprintf(cmdbuff, "VR(%d) =  %f ", (i + vrstartnum) , pfValue[i]);
        //调用命令执行函数
        iresult = ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
        if(ERR_OK != iresult)
        {
            return iresult;
        }
    }
    
    return ERR_OK;
    
    
}



/*************************************************************
 Description:    //字符串转为float
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_TransStringtoFloat(const char* pstringin, int inumes,  float* pfvlaue)
{
    char *ptemp;
    
    ptemp = (char*)pstringin;
    while(' ' == *ptemp)
    {
        ptemp++;
    }
    
    if(!(isdigit(ptemp[0]) || ('-' == ptemp[0])))
    {
        return ERR_ACKERROR;
    }
    
    char *pstringnew = ptemp;
    
    //
    for(int i =0; i < inumes;i++)
    {
        
        while((' ' == *pstringnew) || ('\t' == *pstringnew))
        {
            pstringnew++;
        }
        if(('\0' == pstringnew[0]) || ('\r' == pstringnew[0]) || ('\n' == pstringnew[0]) || !(isdigit(pstringnew[0]) || ('-' == pstringnew[0])))
        {
            break;
        }
        
        double dvalue = strtod(pstringnew, &ptemp);
        if((pstringnew == ptemp))
        {
            //break;
            return ERR_ACKERROR;
        }
        
        pfvlaue[i] = dvalue;
        
        //跳过上次的
        pstringnew = ptemp;
    }
    
    
    return ERR_OK;
}

/*************************************************************
 Description:    //字符串转为int
 Input:          //卡链接handle
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_TransStringtoInt(const char* pstringin, int inumes,  int* pivlaue)
{
    char *ptemp;
    
    ptemp = (char*)pstringin;
    while(' ' == *ptemp)
    {
        ptemp++;
    }
    
    if(!(isdigit(ptemp[0]) || ('-' == ptemp[0])))
    {
        return ERR_ACKERROR;
    }
    
    char *pstringnew = ptemp;
    
    //
    for(int i =0; i < inumes;i++)
    {
        
        while((' ' == *pstringnew) || ('\t' == *pstringnew))
        {
            pstringnew++;
        }
        if(('\0' == pstringnew[0]) || ('\r' == pstringnew[0]) || ('\n' == pstringnew[0]) || !(isdigit(pstringnew[0]) || ('-' == pstringnew[0])))
        {
            break;
        }
        
        double dvalue = strtod(pstringnew, &ptemp);
        if((pstringnew == ptemp))
        {
            //break;
            return ERR_ACKERROR;
        }
        
        pivlaue[i] = dvalue;    //转换成整数
        
        //跳过上次的
        pstringnew = ptemp;
    }
    
    
    return ERR_OK;
}


#if 0
//U盘格式的相关函数
#endif


/*************************************************************
 Description:    //VR读取, 可以一次读取多个
 Input:          //卡链接handle  
 Output:         //pfValue  多个时必须分配空间.
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetVrf(ZMC_HANDLE handle, int vrstartnum, int numes, float *pfValue)
{
    int i, icur, isend;
    int32 iresult;
    char  tempbuff[2048];
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || numes < 0)
    {
        return  ERR_AUX_PARAERR;
    }
    
    isend = 0;
    while(1)
    {
        //一次发送个数15个
        icur = numes - isend;
        if(icur > 15)
        {
            icur = 15;
        }
        
        //生成命令
        strcpy(cmdbuff, "?");
        for(i = 0; i< icur; i++)
        {
            //
            sprintf(tempbuff, "vr(%d) ",vrstartnum+isend+i);
            strcat(cmdbuff, tempbuff);
        }
        
        //调用命令执行函数
        iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
        if(ERR_OK != iresult)
        {
            return iresult;
        }
        
        //
        if(0 == strlen(cmdbuffAck))
        {
            return ERR_NOACK;
        }
        
        //
        iresult = ZAux_TransStringtoFloat(cmdbuffAck, icur, pfValue+isend);
        if(ERR_OK != iresult)
        {
            return iresult;
        }
        
        isend+= icur;
        if(isend >= numes)
        {
            break;
        }
    }
    
    
    return ERR_OK;
}

/*************************************************************
 Description:    //VRINT读取， 必须150401以上版本才支持VRINT的DIRECTCOMMAND读取
 Input:          //卡链接handle  
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetVrInt(ZMC_HANDLE handle, int vrstartnum, int numes, int *piValue)
{
    int i, icur, isend;
    int32 iresult;
    char  tempbuff[2048];
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    
    if(NULL == piValue || numes < 0)
    {
        return  ERR_AUX_PARAERR;
    }
    
    isend = 0;
    while(1)
    {
        //一次发送个数15个
        icur = numes - isend;
        if(icur > 15)
        {
            icur = 15;
        }
        
        //生成命令
        strcpy(cmdbuff, "?");
        for(i = 0; i< icur; i++)
        {
            //
            sprintf(tempbuff, "vr_int(%d) ",vrstartnum+isend+i);
            strcat(cmdbuff, tempbuff);
        }
        
        //调用命令执行函数
        iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
        if(ERR_OK != iresult)
        {
            return iresult;
        }
        
        //
        if(0 == strlen(cmdbuffAck))
        {
            return ERR_NOACK;
        }
        
        //
        
        iresult = ZAux_TransStringtoInt(cmdbuffAck, icur, piValue+isend);
        if(ERR_OK != iresult)
        {
            return iresult;
        }
        
        isend+= icur;
        if(isend >= numes)
        {
            break;
        }
    }
    
    return ERR_OK;
}

/*************************************************************
 Description:    //写table 
 Input:          //卡链接handle  轴号， 距离
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_SetTable(ZMC_HANDLE handle,int tabstart, int numes, float *pfValue)
{
    int i;
    int32 iresult;
    
    char  cmdbuff[2048];
    char  tempbuff[2048];
    
    if(NULL == pfValue || numes < 0)
    {
        return  ERR_AUX_PARAERR;
    }
    
    for(i = 0; i< numes; i++)
    {
        //
        sprintf(cmdbuff, "table(%d) =  %f ", (i + tabstart) , pfValue[i]);
        //调用命令执行函数
        iresult = ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
        if(ERR_OK != iresult)
        {
            return iresult;
        }
    }
    
    return ERR_OK;
    
    
}

/*************************************************************
 Description:    //table读取, 可以一次读取多个
 Input:          //卡链接handle  
 Output:         //pfValue  多个时必须分配空间.
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Direct_GetTable(ZMC_HANDLE handle, int tabstart, int numes, float *pfValue)
{
    int i, icur, isend;
    int32 iresult;
    char  tempbuff[2048];
    char  cmdbuff[2048];
    char  cmdbuffAck[2048];
    
    if(NULL == pfValue || numes < 0)
    {
        return  ERR_AUX_PARAERR;
    }
    
    
    isend = 0;
    while(1)
    {
        //一次发送个数15个
        icur = numes - isend;
        if(icur > 15)
        {
            icur = 15;
        }
        
        //生成命令
        strcpy(cmdbuff, "?");
        for(i = 0; i< icur; i++)
        {
            //
            sprintf(tempbuff, "TABLE(%d) ",tabstart+isend+i);
            strcat(cmdbuff, tempbuff);
        }
        
        //调用命令执行函数
        iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
        if(ERR_OK != iresult)
        {
            return iresult;
        }
        
        //
        if(0 == strlen(cmdbuffAck))
        {
            return ERR_NOACK;
        }
        
        //
        iresult = ZAux_TransStringtoFloat(cmdbuffAck, icur, pfValue+isend);
        if(ERR_OK != iresult)
        {
            return iresult;
        }
        
        isend+= icur;
        if(isend >= numes)
        {
            break;
        }
    }
    
    
    return ERR_OK;
}



#if 0
//辅助函数
#endif

/*************************************************************
 Description:    //把float格式的变量列表存储到文件， 与控制器的U盘文件格式一致.
 Input:          //
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_WriteUFile(const char *sFilename, float *pVarlist, int inum)
{
    FILE *pfile;
    
    //写入文件
    pfile = fopen(sFilename, "wb");
    if(NULL == pfile)
    {
        //
        ZAUX_ERROR("open file:%s err", sFilename);
        return ERR_AUX_FILE_ERROR;
    }
    
    fseek(pfile, 0, SEEK_SET);
    
    if(fwrite(pVarlist, 4, inum, pfile) != inum)
    {
        //
        ZAUX_ERROR("fwrite size != %d", inum);
        fclose(pfile);
        return ERR_AUX_OS_ERR;
    }
    
    //关闭文件
    fclose(pfile);
    return ERR_OK;
}

/*************************************************************
 Description:    //读取float格式的变量列表， 与控制器的U盘文件格式一致.
 Input:          //
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_ReadUFile(const char *sFilename, float *pVarlist, int* pinum)
{
    FILE *pfile;
    uint32 uifilesize;
    
    //读取文件
    pfile = fopen(sFilename, "rb");
    if(NULL == pfile)
    {
        //
        ZAUX_ERROR("open file:%s err", sFilename);
        return ERR_AUX_FILE_ERROR;
    }
    fseek(pfile, 0, SEEK_END);
    
    uifilesize = ftell(pfile);
    
    fseek(pfile, 0, SEEK_SET);	
    if(fread(pVarlist, 1, uifilesize, pfile) != uifilesize)
    {
        //
        ZAUX_ERROR("read size != %d", uifilesize);
        fclose(pfile);
        
        return ERR_AUX_OS_ERR;
    }
    //关闭文件
    fclose(pfile);
    
    *pinum = uifilesize/4;
    return ERR_OK;
}



/*************************************************************
 Description:    //modbus寄存器操作
 Input:          //卡链接handle 寄存器地址
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Modbus_Set0x(ZMC_HANDLE handle, uint16 start, uint16 inum, uint8* pdata)
{
    int32 iresult;
    iresult = ZMC_Modbus_Set0x(handle,start,inum,pdata);
    
    return iresult;
}

/*************************************************************
 Description:    //modbus寄存器操作
 Input:          //卡链接handle 寄存器地址
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Modbus_Get0x(ZMC_HANDLE handle, uint16 start, uint16 inum, uint8* pdata)
{
    int32 iresult;
    iresult = ZMC_Modbus_Get0x(handle,start,inum, pdata);
    
    return iresult;
}

/*************************************************************
 Description:    //modbus寄存器操作
 Input:          //卡链接handle 寄存器地址
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Modbus_Set4x(ZMC_HANDLE handle, uint16 start, uint16 inum, uint16* pdata)
{
    int32 iresult;
    iresult = ZAux_Modbus_Set4x(handle,start,inum, pdata);
    
    return iresult;
}

/*************************************************************
 Description:    //modbus寄存器操作
 Input:          //卡链接handle 寄存器地址
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Modbus_Get4x(ZMC_HANDLE handle, uint16 start, uint16 inum, uint16* pdata)
{
    int32 iresult;
    iresult = ZAux_Modbus_Get4x(handle, start, inum, pdata);
    
    return iresult;
}

/*************************************************************
 Description:    //modbus_ieee
 Input:          //
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Modbus_Get4x_Float(ZMC_HANDLE handle, uint16 start, uint16 inum, float* pfdata)
{
    int 	i,j;
    int32 	iresult;
    void * pf;
    uint16 * pi;
    uint16  tempdata[2048];
    
    if(NULL == pfdata || inum < 0)
    {
        return  ERR_AUX_PARAERR;
    }
    
    
    pi = tempdata;
    pf = pfdata;
    
    iresult = ZMC_Modbus_Get4x(handle,start,inum*2,tempdata);
    if(iresult == 0)
    {
        
        for(i=1;i<inum +1;i++)
        {
            for(j=0;j<2;j++)
            {
                *((uint16 *)pf + j )  = *(pi +j);
            }
            pf = pfdata +i;
            pi = pi+2;
        }
    }
    
    return iresult;
}

/*************************************************************
 Description:    //modbus_ieee
 Input:          //
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Modbus_Set4x_Float(ZMC_HANDLE handle, uint16 start, uint16 inum, float* pfdata)
{
    int 	i,j;
    int32 	iresult;
    void * pf;
    uint16 * pi;
    uint16  tempdata[2048];
    
    if(NULL == pfdata || inum < 0)
    {
        return  ERR_AUX_PARAERR;
    }
    
    pi = tempdata;
    pf = pfdata;
    
    for(i=1;i<inum +1;i++)
    {
        for(j=0;j<2;j++)
        {
            *(pi +j) = *((uint16 *)pf + j);
        }
        pf = pfdata +i;
        pi = pi+2;
    }	
    iresult = ZMC_Modbus_Set4x(handle,start,inum*2,tempdata);
    return iresult;
}

/*************************************************************
 Description:    //modbus_long
 Input:          //
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Modbus_Get4x_Long(ZMC_HANDLE handle, uint16 start, uint16 inum, int32 * pidata)
{
    int 	i,j;
    int32 	iresult;
    void * pitemp;
    uint16 * pi;
    uint16  tempdata[2048];
    
    if(NULL == pidata || inum < 0)
    {
        return  ERR_AUX_PARAERR;
    }
    
    pi = tempdata;
    pitemp = pidata;
    
    iresult = ZMC_Modbus_Get4x(handle,start,inum*2,tempdata);
    if(iresult == 0)
    {
        
        for(i=1;i<inum +1;i++)
        {
            for(j=0;j<2;j++)
            {
                *((uint16 *)pitemp + j )  = *(pi +j);
            }
            pitemp = pidata +i;
            pi = pi+2;
        }
    }
    
    return iresult;
}

/*************************************************************
 Description:    //modbus_long
 Input:          //
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_Modbus_Set4x_Long(ZMC_HANDLE handle, uint16 start, uint16 inum, int32 * pidata)
{
    int 	i,j;
    int32 	iresult;
    void * pitemp;
    uint16 * pi;
    uint16  tempdata[2048];
    
    if(NULL == pidata || inum < 0)
    {
        return  ERR_AUX_PARAERR;
    }
    
    pi = tempdata;
    pitemp = pidata;
    
    for(i=1;i<inum +1;i++)
    {
        for(j=0;j<2;j++)
        {
            *(pi +j) = *((uint16 *)pitemp + j);
        }
        pitemp = pidata +i;
        pi = pi+2;
    }	
    iresult = ZMC_Modbus_Set4x(handle,start,inum*2,tempdata);
    return iresult;
}

/*************************************************************
 Description:    //写用户flash块, float数据
 Input:          //卡链接handle
 uiflashid 	flash块号
 uinumes		变量个数
 Output:         //
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_FlashWritef(ZMC_HANDLE handle, uint16 uiflashid, uint32 uinumes, float *pfvlue)
{
    int32 iresult;
    iresult = ZMC_FlashWritef(handle, uiflashid, uinumes,pfvlue);
    
    return iresult;
}


/*************************************************************
 Description:    //读取用户flash块, float数据
 Input:          //卡链接handle
 uiflashid 	flash块号
 uibuffnum	缓冲变量个数
 Output:         //
 puinumesread 读取到的变量个数
 Return:         //错误码
 *************************************************************/
int32 __stdcall ZAux_FlashReadf(ZMC_HANDLE handle, uint16 uiflashid, uint32 uibuffnum, float *pfvlue, uint32* puinumesread)
{
    int32 iresult;
    iresult = ZMC_FlashReadf(handle, uiflashid, uibuffnum,pfvlue,puinumesread);
    return iresult;
}




#endif /* zaux_h */
