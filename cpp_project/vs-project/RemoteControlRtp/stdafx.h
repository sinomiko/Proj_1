// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件

#pragma once
#pragma warning(disable:4081)
#pragma warning(disable:4101)
#pragma warning(disable:4244)
#pragma warning(disable:4305)
#pragma warning(disable:4996)
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 标头中排除不常使用的资料
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用 Windows 95 和 Windows NT 4 或更高版本的特定功能。
#define WINVER 0x0500		//为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
#endif

#ifndef _WIN32_WINNT		// 允许使用 Windows NT 4 或更高版本的特定功能。
#define _WIN32_WINNT 0x0500		//为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用 Windows 98 或更高版本的特定功能。
#define _WIN32_WINDOWS 0x0510 //为 Windows Me 及更新版本改变为适当的值。
#endif

#ifndef _WIN32_IE			// 允许使用 IE 4.0 或更高版本的特定功能。
#define _WIN32_IE 0x0500	//为 IE 5.0 及更新版本改变为适当的值。
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常被安全忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心和标准组件
#include <afxext.h>         // MFC 扩展
#include <afxdisp.h>        // MFC 自动化类
#include <afxsock.h>
#include <WinSock2.h>
#include <afxdtctl.h>		// Internet Explorer 4 公共控件的 MFC 支持
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows 公共控件的 MFC 支持
#endif // _AFX_NO_AFXCMN_SUPPORT

//MTSOFT Include
#include "globalDef.h"   //全局定义头文件
#include "MTSystem.h"   //系统头文件
#include "MTDevice.h"   //设备头文件
#include "MTConfig.h"   //系统配置头文件
#include "IMTMotion.h"        //运动接口头文件
#include "Ingenious.h"        //参数类型定义
#include "IngeniousException.h" //异常处理
#include "IMTEncoder.h"
#include "IMTImageProcess.h"
#include "IMTImageCapture.h"
#include "IMTNetwork.h"
#include "IMTvoice.h"
#include "IMTUltraSonic.h"
#include "IMTPSD.h"
#include "IMotionDecision.h"
#include "IMTPosNav.h"
class CMTSystem;   //系统类
interface IMTMotion;  //运动接口
interface IMotionDecision;
interface IMTUltraSonic;
#define FRONTCHANNEL		0
#define LEFTCHANNEL			2
#define RIGHTCHANNEL		12

#define Avoid_FM 0
#define Avoid_FL1 2
#define Avoid_FL2 4
#define Avoid_FR1 12
#define Avoid_FR2 10
#define Avoid_BM 7
#define WHEELWIDTH 0.399
#include <fstream>
#include <afxcontrolbars.h>

//添加opencv的头文件
// #include<opencv\cv.h>
// #include<opencv\highgui.h>
// #include<opencv\cxcore.h>
// #include<opencv\cvaux.h>
#include<opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <afxsock.h>
#include<iostream>
#include "CvvImage.h"
using namespace cv;
using namespace std;
