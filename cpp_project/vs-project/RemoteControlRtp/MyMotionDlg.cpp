// MyMotionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyMotion.h"
#include "MyMotionDlg.h"
#include ".\mymotiondlg.h"
#include "afxdialogex.h"
#include "winsock.h"
#include "matlib.h"
#include "header_rtph263.h"
#include <cstdlib> 
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace jrtplib;
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
static float32 m_t = 0.0f;//运行时间
static float32 ld_basic = 0.0f;//左轮期望位移
static float32 rd_basic = 0.0f;//右轮期望位移
const float32 PI = 3.1415926f;
int delaycount;
float CurrentAngel;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
//
ofstream outlv("c:\\Data\\lv.txt");
ofstream outrv("c:\\Data\\rv.txt");
ofstream outld("c:\\Data\\ld.txt");
ofstream outrd("c:\\Data\\rd.txt");
ofstream outla("c:\\Data\\la.txt");
ofstream outra("c:\\Data\\ra.txt");
ofstream out("c:\\trace.txt");
ofstream out1("c:\\trace1.txt");
#define SendPortBase	3000
#define ReceivePortBase	2000
int ByteCount = 0;
unsigned char cdata[20000];
int cbuffer_size = 20000;
unsigned char rgbdata[400000];
int buffersize = 400000;

//编码回调
void OwnWriteFunction(int byte)
{
	if(ByteCount<cbuffer_size)
	{
		cdata[ByteCount]=(unsigned char)byte;
		++ByteCount;
	}
}

void checkerror(int rtperr)
{
	if (rtperr < 0)
	{
		std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
		exit(-1);
	}
}

UINT ThreadCmd(LPVOID pParam)
{
	CMyMotionDlg* dlg=(CMyMotionDlg*)pParam;

	//加载套接字
	WORD wVersionRequested;
	WSADATA wsaData;//保存winsock库的版本号
	int err;
	wVersionRequested=MAKEWORD(1,1);//包含了请求版本号的word值
	err=WSAStartup(wVersionRequested,&wsaData);//加载套接字，如果其返回值不等于0则退出
	if (err!=0)
	{
		return 0;
	}
	if (LOBYTE (wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();//如果不是我们请求的版本，那么调用wsacleanup函数，终止对winsock库的使用，并返回
		return 0;

	}
	//加载完套接字库之后，就可以按照上面讲述的基于TCP（面向连接）的socket编程中的服务器端程序流来编写程序
	//创建用于监听的套接字
	SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);	//定义socket类型的变量：sockSrv，用来接收socket函数返回的套接字。
	//socket函数：第一个参数只能是AF_INET（或者）PF_INET；本例是基于TCP协议的网络程序，需要创建的是流式套接字，因此将socket的函数的第二个参数设置为SOCK_STREAM
	//将其第三个参数指定为0，该函数将根据地址格式和套接字类别，自动选择一个合适的协议
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//对变量sin_addr.S_un.S_addr成员进行赋值，该成员为u_long类型，该函数将一个u_long转换为网络字节顺序
	addrSrv.sin_family=AF_INET;//其他成员都是按网络字节顺序表示的
	addrSrv.sin_port=htons(6000);//为所编写的网络程序指定端口号。
	//注意：htons与htonl这两个函数不一样:如果利用htons将一个int或者long型数值转化为网络字节顺序，可能会丢失数据

	//绑定套接字，将这个套接字绑定到本地的某个地址和端口上
	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//第一个字节：要绑定的套接字；第二个字节：需要一个指针，可以用取地址符来实现
	//addrSrv变量是SOCKADDR_IN结构体类型，这里需要SOCKADDR*类型，对SOCKADDR类型来说，大小写是一样的
	//将套接字设为监听模式，准备接受客户请求
	listen(sockSrv,5);//第一个参数：将要设置的套接字，第二个参数是等待连接队列的最大长度。本例将此参数值设置为5



	SOCKADDR_IN addrClient;//绑定之前，定义一个SOCKADDR_IN类型的变量addrSrv,然后对该地址结构体变量中的成员进行赋值。
	int len=sizeof(SOCKADDR);
	char sendBuf1[100];
	sprintf(sendBuf1,"welcome");
	while(true)
	{
		//等待客户请求到来
		SOCKET sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);	//接收到请求，返回一个新的对应于此链接的套接字,第三个参数调用之前必须赋初始值，即SOCKADDR_IN结构体的长度
		//作为服务器端，需要不断等待客户端的连接请求到来，所以，程序接着进入一个循环，第一步调用accept函数等待并接受客户端的地址信息。
		//当客户端请求到来时，该函数接受该请求，建立连接 ，同时它将返回一个相对与当前这个新连接的一个套接字描述符，保存在sockConn中。
		//然后利用这个套接字就可以与客户端进行通信了


		//此时，可以利用send函数向客户端发送数据，首先定义一个字符数组，并将客户端的地址格式化处理后放到这个数组中。
		//在格式化客户端接收地址时，使用inet_ntoa函数，该函数接受一个in_addr结构体类型的参数并返回一个以点分十进制格式表示的IP地址字符串
		//而SOCKADDR_IN结构体中的sin_addr成员是in_addr类型，正好可以作为参数传递
		//设置发送的字符串
		//sprintf(sendBuf,"welcome %s to use",inet_ntoa(addrClient.sin_addr));

		//发送数据
		send(sockConn,sendBuf1,strlen(sendBuf1)+1,0);
		//向客户端发送数据，需要使用已经建立的哪个套接字：sockConn，而不是使用用于监听的哪个套接字：addrSrv
		//发送长短可以用strlen来获得，但上述程序在发送数据时，多发送了一个字节，主要是为了让接收端在接受数据之后增加一个“\0”作为结尾标志

		//接收数据
		char recvBuf[100];
		//定义一个字符数组，用于保存接受的数据
		recv(sockConn,recvBuf,100,0);
		//数据发送完毕，还可以从客户端接收数据，用recv函数：第一个参数是建立连接之后的哪个套接字：sockConn；
		//打印接受的数据

// 		dlg->UpdateData(TRUE);
// 		dlg->m_EdtRe=recvBuf;
// 		dlg->UpdateData(FALSE);
// 		dlg->GetDlgItem(IDC_EdtRe)->SetWindowText(dlg->m_EdtRe);
		if(strcmp(recvBuf, "left")==0)
		{
			g_Commands="left";
			sprintf(sendBuf1,"left");
			dlg->PostMessage(WM_USER_THREAD,0,0);
		}
		else if(strcmp(recvBuf, "right")==0)
		{
			g_Commands="right";
			sprintf(sendBuf1,"right");
			dlg->PostMessage(WM_USER_THREAD,0,0);
		}
		else if(strcmp(recvBuf, "backward")==0)
		{
			g_Commands="backward";
			sprintf(sendBuf1,"backward");
			dlg->PostMessage(WM_USER_THREAD,0,0);
		}
		else if(strcmp(recvBuf, "forward")==0)
		{	
			g_Commands="forward";
		    sprintf(sendBuf1,"forward");
			dlg->PostMessage(WM_USER_THREAD,0,0);
		}
		else if(strcmp(recvBuf, "stop")==0)
		{
			g_Commands="stop";
			sprintf(sendBuf1,"stop");
			dlg->PostMessage(WM_USER_THREAD,0,0);
		}
		else 
		{
			dlg->m_EdtRe=recvBuf;
			sprintf(sendBuf1,"Commands not found");
		}
		// 		sockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
		// 		send(sockConn,recvBuf,strlen(recvBuf)+1,0);
		closesocket(sockConn);
		//关闭已建立连接的套接字，释放为该套接字分配的资源，进入下一个循环，等待另一个客户的请求到来

	}
	/**************************************
	因为程序使用了WinSock库中的函数，按照动态链接库的使用方法，需要天界程序相应的.lib文件，需要为本程序添加ws2_32.lib
	***********************************/


	closesocket(sockSrv);
	return 0;

}

UINT ThreadImg(LPVOID pParam)
{
	CMyMotionDlg *dlg=(CMyMotionDlg*) pParam;
//	dlg->m_string.Format(_T("Begin Sending Image!\n"));
// 	dlg->m_cListInfor.AddString(dlg->m_string);
// 	dlg->m_cListInfor.SetCurSel(dlg->m_cListInfor.GetCount()-1);

	//////////////////////////////
	IplImage * pSendFrame;
	CvCapture * pSendCapture = cvCaptureFromCAM(0);
// 	cvSetCaptureProperty( pSendCapture, CV_CAP_PROP_FRAME_WIDTH,320 );
// 	cvSetCaptureProperty( pSendCapture, CV_CAP_PROP_FRAME_HEIGHT,240 );
//  	cvSetCaptureProperty( pSendCapture, CV_CAP_PROP_FPS ,5 );

	pSendFrame = cvQueryFrame( pSendCapture ) ;
	IplImage * pFrame;
	pFrame=cvRetrieveFrame(pSendCapture);           // retrieve the captured frame
	uchar * pSendBufData = (uchar *)pSendFrame->imageData;
	////////////////////////////////////

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 1, 1);

	err = WSAStartup( wVersionRequested, &wsaData);
	if( err != 0 )return -1;
	if( LOBYTE( wsaData.wVersion) != 1 ||
		HIBYTE( wsaData.wVersion) != 1 )
	{
		WSACleanup();
		return -1;
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5600);

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	listen(sockSrv, 5);
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		//CVAPI(IplImage*) cvRetrieveFrame( CvCapture* capture );
		//img=cvRetrieveFrame(pSendCapture);           // retrieve the captured frame

		
		pSendFrame = cvQueryFrame( pSendCapture ) ;
		char c=cvWaitKey(1);
		cvShowImage("Video Server",pSendFrame);
		/*send(sockConn, (const char *)pBufData, 480*1920+640*3+320+3 , 0);*/
		send(sockConn, (const char *)pSendBufData, 480*1920 , 0);
		closesocket(sockConn);		
	}

	WSACleanup();
	return 0;
}
UINT ThreadImgLocalRecv(LPVOID pParam)
{
	CMyMotionDlg *dlg=(CMyMotionDlg*) pParam;

	//dlg->m_string.Format(_T("Begin receiving Image\n"));
	//dlg->m_cListInfor.AddString(dlg->m_string);
	//dlg->m_cListInfor.SetCurSel(dlg->m_cListInfor.GetCount()-1);

	//////////////////////////////
	IplImage * pColorImg ;
	pColorImg = cvCreateImage( cvSize(640,480), 8, 3 );
	pColorImg->widthStep = 1920;//pFrame->widthStep/(sizeof(uchar));//1920
	pColorImg->origin = 0;//pFrame->origin;//0
	pColorImg->width = 640;//cvGetSize(pFrame).width;//640
	pColorImg->height =480;// cvGetSize(pFrame).height;//480
	pColorImg->nChannels  =3;// pFrame->nChannels;//3
	uchar * pBufData = (uchar *)pColorImg->imageData;
	/*cvNamedWindow("Video Receiving from Server");*/
	//////////////////////////////
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup( wVersionRequested, &wsaData);
	if (err != 0)
	{
		return -1;
	}

	if( LOBYTE( wsaData.wVersion) != 1 ||
		HIBYTE( wsaData.wVersion) != 1 )
	{
		WSACleanup();
		return -1;
	}

	SOCKADDR_IN addrSrv;
	CString IPAddr;
	//读取输入命令

	IPAddr=dlg->cstrClientIP;
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//地址
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5600);

	while (1)
	{	
		SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
		/*SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);*/
		if(connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == INVALID_SOCKET)
		{
			//	m_string.Format(_T("%s\n","connecting failed!"));
			//dlg->m_string.Format(_T("connecting failed!\n"));
		}
		else
		{
			recv(sockClient, (char *)pBufData, 640*1920,0);
			cvShowImage("Video Receiving from Server",pColorImg);
			//dlg->DrawPicToHDC(pColorImg, IDC_STATIC_PIC);
			char c =cvWaitKey(1);	
			if(c == 27)
				break;

		}
		closesocket(sockClient);
	}

	WSACleanup();
	cvDestroyWindow("ClientGrayImage");
	return 0;
}
UINT ThreadImgRecv(LPVOID pParam)
{
	CMyMotionDlg *dlg=(CMyMotionDlg*) pParam;

	//dlg->m_string.Format(_T("Begin receiving Image\n"));
	//dlg->m_cListInfor.AddString(dlg->m_string);
	//dlg->m_cListInfor.SetCurSel(dlg->m_cListInfor.GetCount()-1);

	//////////////////////////////
	IplImage * pColorImg ;
	pColorImg = cvCreateImage( cvSize(320,240), 8, 3 );
	pColorImg->widthStep = 960;//pFrame->widthStep/(sizeof(uchar));//1920
	pColorImg->origin = 0;//pFrame->origin;//0
	pColorImg->width = 320;//cvGetSize(pFrame).width;//640
	pColorImg->height =240;// cvGetSize(pFrame).height;//480
	pColorImg->nChannels  =3;// pFrame->nChannels;//3
	uchar * pBufData = (uchar *)pColorImg->imageData;
	/*cvNamedWindow("Video Receiving from Server");*/
	//////////////////////////////
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup( wVersionRequested, &wsaData);
	if (err != 0)
	{
		return -1;
	}

	if( LOBYTE( wsaData.wVersion) != 1 ||
		HIBYTE( wsaData.wVersion) != 1 )
	{
		WSACleanup();
		return -1;
	}
	
		SOCKADDR_IN addrSrv;
		CString IPAddr;
		//读取输入命令

		IPAddr=dlg->cstrClientIP;
		addrSrv.sin_addr.S_un.S_addr=inet_addr(IPAddr);//地址
		addrSrv.sin_family = AF_INET;
		addrSrv.sin_port = htons(5800);

		while (1)
		{	
			SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
			/*SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);*/
			if(connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == INVALID_SOCKET)
			{
				//	m_string.Format(_T("%s\n","connecting failed!"));
				//dlg->m_string.Format(_T("connecting failed!\n"));
			}
			else
			{
				recv(sockClient, (char *)pBufData, 240*960,0);
				//cvShowImage("Video Receiving from Server",pColorImg);
				dlg->DrawPicToHDC(pColorImg, IDC_STATIC_PIC);
				char c =cvWaitKey(1);	
				if(c == 27)
					break;

			}
			closesocket(sockClient);
		}

	WSACleanup();
	cvDestroyWindow("ClientGrayImage");
	return 0;
}

UINT ThreadImgRtpSending(LPVOID pParam)
{
	CMyMotionDlg *dlg=(CMyMotionDlg*) pParam;
  
	//opencv var
	Mat frame;
	Mat temp[3];
	VideoCapture capture;
	int frameCount = 0;

	//h263 ----------encoder/decoder init
	unsigned int yuv[WIDTH*HEIGHT*3/2];
	CParam h263Param;
	Bits bits;
	InitLookupTable();
	h263Param.format = PARAM_FORM;
	InitH263Encoder(&h263Param);
	WriteByteFunction = OwnWriteFunction;

	//rtp---initialze and creation
	WSADATA dat;
	WSAStartup(MAKEWORD(2,2), &dat);

	const size_t MaxPackSize = 20000;
	RTPSession session;
	RTPSessionParams sessionparams;
	sessionparams.SetOwnTimestampUnit(1.0/90000.0);	//for video ---see RFC2190

	RTPUDPv4TransmissionParams transparams;
	transparams.SetPortbase(SendPortBase);
	int status = session.Create(sessionparams,&transparams);
	checkerror(status);
	CString IPAddr;
	//读取输入命令
	IPAddr=dlg->cstrClientIP;
	uint32_t data;
	if (IPAddr.Find(_T("0x"))==0)
	{
		_stscanf_s((LPCTSTR)IPAddr,_T("%x"),&data);
	} 
	else
	{
		_stscanf_s((LPCTSTR)IPAddr,_T("%d"),&data);
	}
	/*uint8_t localip[]={127, 0, 0, 1};*/
/*	uint8_t localip[]={192, 168, 0, 179};//客户端地址*/
		uint8_t localip[]={192, 168, 1, 129};//客户端地址
	RTPIPv4Address addr(localip, SendPortBase);
	status = session.AddDestination(addr);
	checkerror(status);

	session.SetDefaultPayloadType(34);	//PT for H.263----see RFC2190
	session.SetDefaultMark(true);		//true or false ?? both ok for my test	
	session.SetDefaultTimestampIncrement(3600);	// =90000/25
	session.SetMaximumPacketSize(MaxPackSize);
	capture.open(0);
	if (!capture.isOpened())
	{
		cout<<"open video/camera failed!"<<endl;
		return -1;
	}
	capture>>frame;
	if (frame.empty())
	{
		cout<<"grab frame failed! exit...."<<endl;
		return -1;
	}
	while (waitKey(40) != 27)	//25 fps
	{
		capture>>frame;
		if (frame.empty())
		{
			cout<<"grab frame failed! exit...."<<endl;
			return -1;
		}
		++frameCount;
 		resize(frame, temp[0], cv::Size(WIDTH, HEIGHT));	//resize to CIF
// 		imshow("raw", temp[0]);
	
		dlg->DrawPicToHDC(temp[0], IDC_STATIC_PIC2);
		char c =cvWaitKey(1);	
		if(c == 27)
			break;
		////---------------------------compress image frames-------------------------//	
		ConvertRGB2YUV(WIDTH, HEIGHT, temp[0].data, yuv);
		ByteCount = 0;
		h263Param.format = PARAM_FORM;
		h263Param.inter = CPARAM_INTRA;
		h263Param.Q_intra = 8;
		h263Param.data = yuv;
		CompressFrame(&h263Param, &bits);
		cout<<"compressed byte count is: "<<ByteCount<<endl;
		///-------------------------------------------------------------------------//

		status = session.SendPacket(cdata, ByteCount);
		checkerror(status);

	}
	//release resources
	cvDestroyAllWindows();
	ExitH263Encoder(&h263Param);

	RTPTime delay(5.0);
	session.BYEDestroy(delay, "trans over", 10);
	WSACleanup();
	return 0;
}

UINT ThreadImgRtpReceiving(LPVOID pParam)
{
	CMyMotionDlg *dlg=(CMyMotionDlg*) pParam;

	//opencv var
	Mat frame;
	Mat temp[3];
	VideoCapture capture;
	int frameCount = 0;

	//h263 ----------encoder/decoder init
	uchar *readData = NULL;
	uchar *imgBuffer = NULL;
	InitLookupTable();
	InitH263Decoder();

	//rtp---initialze and creation
#ifdef WIN32
	WSADATA dat;
	WSAStartup(MAKEWORD(2,2),&dat);
#endif // WIN32
	RTPPacket *packet;
	const size_t MaxPackSize = 20000;
	RTPSession sess;
	RTPSessionParams sessionparams;
	sessionparams.SetOwnTimestampUnit(1.0/90000.0);	//for video ---see RFC2190
	sessionparams.SetAcceptOwnPackets(true);
	/*RTPUDPv4TransmissionParams transparams;*/
	RTPUDPv4TransmissionParams transparams;
	transparams.SetPortbase(ReceivePortBase);
	int status = sess.Create(sessionparams,&transparams);
	checkerror(status);
	/********************************************/
	sess.SetDefaultPayloadType(34);	//PT for H.263----see RFC2190
	sess.SetDefaultMark(true);		//true or false ?? both ok for my test	
	sess.SetDefaultTimestampIncrement(3600);	// =90000/25
	sess.SetMaximumPacketSize(MaxPackSize);
	int packetNum = 0;
	while(waitKey(40) != 27)	//25fps
	{
		sess.BeginDataAccess();
		if (sess.GotoFirstSourceWithData())
		{
			do 
			{

				while( (packet = sess.GetNextPacket()) != NULL)
				{
					cout<<"packet count: "<<++packetNum<<endl;
					size_t dataLen = packet->GetPayloadLength();
					cout<<"payload length: "<<dataLen<<endl;
					readData = packet->GetPayloadData();
					imgBuffer = new uchar[dataLen];
					memcpy(imgBuffer, readData, dataLen);

					///----------------------------decompress--------------------------//
					DecompressFrame(imgBuffer, dataLen, rgbdata, buffersize);
					///----------------------------------------------------------------//

					Mat GotImg(HEIGHT, WIDTH, CV_8UC3, rgbdata);
					if(GotImg.empty())
					{
						cout<<"got image has no data, exiting...."<<endl;
						return -1;
					}
					dlg->DrawPicToHDC(GotImg, IDC_STATIC_PIC);
					//release buffers and packet
					delete []imgBuffer;
					imgBuffer = NULL;
					sess.DeletePacket(packet);
				}

			} while (sess.GotoNextSourceWithData());
		}
		sess.EndDataAccess();

	}

	///////////////////////////////////////////////////////////////////

	//release resources
	ExitH263Decoder();
	RTPTime delay(5.0);
	sess.BYEDestroy(delay, "trans over", 10);
	WSACleanup();


	return 0;
}
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMyMotionDlg 对话框



CMyMotionDlg::CMyMotionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyMotionDlg::IDD, pParent)
	, m_pDevMotion(NULL)
	, m_pMotion(NULL)
	, m_fLeftSpeed(0.1f)
	, m_fRightSpeed(0.1f)
	, m_lKp(0)
	, m_lKi(0)
	, m_lKd(0)
	, m_la(0.5f)
	, m_ls(1)
	, m_rKp(0)
	, m_rKi(0)
	, m_rKd(0)
	, m_ra(0.5f)
	, m_rs(1)
	, m_ModeSelect(1)
	, m_PidSelect(1)
	, m_ModeSelect1(0)
	, m_ClrState(0)
	, e_la(0.0f)
	, e_ra(10.0f)
	, m_fLv(0.0f)
	, m_fRv(0.0f)
	, m_CurrentTimer(0.0f)
	, m_CurrentLD(0.0f)
	, m_CurrentRD(0.0f)
	, m_pEncoder(NULL)
	, Vrx(0)
	, Vry(0)
	, X(0)
	, Y(0)
	, theta(0)
	, PreXd(0)
	, PreYd(0)
	, Wd(0)
	, Vd(0)
	, Vr(0)
	, Wr(0)
	, V(0)
	, W(0)
	, WaitTime(100)
	, PreVd(0)
	, PreWd(0)
	, thetaR(0)
	, Xr(0)
	, Yr(0)
	, e1(0)
	, e2(0)
	, e3(0)
	, N1(0)
	, N2(0)
	, T1(0)
	, T2(0)
	, I(60)
	, V1(0)
	, V2(0)
	, r(0.1)
	, R(2)
	, m(0)
	, md(0)
	, n(0)
	, nd(0)
	, framecount(0)
	, S1(0)
	, S2(0)
	, EncodeTime(0)
	, alfa1(0)
	, alfa2(0)
	, acc1(0)
	, acc2(0)
	, X1(0)
	, X2(0)
	, Y1(0)
	, px(277)
	, py(178)
	, m_iState(0)
	, cstrClientIP(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for (int i=0;i<4;i++)
	{
		m_fEncoderDis[i] = 0;
	}
	for (int i=0;i<5;i++)
	{
		m_fEncoder[i] = 0;
	}
	m_Vr = 0.0f;
	m_Wr = 0.0f;
	m_X = 0.0f;
	m_Xr = 0.0f;
	m_Y = 0.0f;
	m_Yr = 0.0f;
	m_theta = 0.0f;
	m_thetaR = 0.0f;
	m_T1 = 0.0f;
	m_T2 = 0.0f;
	//  m_V1 = 0.0f;
	//  m_V1 = 0.0f;
	//  m_V2 = 0.0f;
	m_V21 = 0.0f;
	m_V22 = 0.0f;
	m_e1 = 0.0f;
	m_e2 = 0.0f;
	m_e3 = 0.0f;
	m_EdtImg = _T("");
	m_EdtRe = _T("");
	m_CstrIP = _T("");
	m_UltraSonic_B = _T("");
	m_UltraSonic_F = _T("");
	m_UltraSonic_FL = _T("");
	m_UltraSonic_FR = _T("");
	m_UltraSonic_L = _T("");
	m_UltraSonic_R = _T("");
	m_PSD_B = _T("");
	m_PSD_F = _T("");
	m_PSD_FL = _T("");
	m_PSD_FR = _T("");
	m_PSD_L = _T("");
	m_PSD_R = _T("");
}

void CMyMotionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LKP, m_lKp);
	DDX_Text(pDX, IDC_LKI, m_lKi);
	DDX_Text(pDX, IDC_LKD, m_lKd);
	DDX_Text(pDX, IDC_LA, m_la);
	DDX_Text(pDX, IDC_LS, m_ls);
	DDX_Text(pDX, IDC_RKP, m_rKp);
	DDX_Text(pDX, IDC_RKI, m_rKi);
	DDX_Text(pDX, IDC_RKD, m_rKd);
	DDX_Text(pDX, IDC_RA, m_ra);
	DDX_Text(pDX, IDC_RS, m_rs);
	DDX_Text(pDX, IDC_LEFTSPEED, m_fLeftSpeed);
	DDX_Text(pDX, IDC_RIGHTSPEED, m_fRightSpeed);
	DDV_MinMaxFloat(pDX, m_fLeftSpeed, -2.5f, 2.5f);
	DDV_MinMaxFloat(pDX, m_fRightSpeed, -2.5f, 2.5f);
	DDX_Text(pDX, IDC_EdtImg, m_EdtImg);
	DDX_Text(pDX, IDC_EdtRe, m_EdtRe);


	DDX_Text(pDX, IDC_EdtIP, m_CstrIP);
	DDX_Text(pDX, IDC_ClientIP, cstrClientIP);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_B, m_UltraSonic_B);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_F, m_UltraSonic_F);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_FL, m_UltraSonic_FL);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_FR, m_UltraSonic_FR);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_L, m_UltraSonic_L);
	DDX_Text(pDX, IDC_EDIT_UltraSonic_R, m_UltraSonic_R);
	DDX_Text(pDX, IDC_EDIT_PSD_B, m_PSD_B);
	DDX_Text(pDX, IDC_EDIT_PSD_F, m_PSD_F);
	DDX_Text(pDX, IDC_EDIT_PSD_FL, m_PSD_FL);
	DDX_Text(pDX, IDC_EDIT_PSD_FR, m_PSD_FR);
	DDX_Text(pDX, IDC_EDIT_PSD_L, m_PSD_L);
	DDX_Text(pDX, IDC_EDIT_PSD_R, m_PSD_R);
}

BEGIN_MESSAGE_MAP(CMyMotionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_FORWARD, OnBnClickedForward)
	ON_BN_CLICKED(IDC_BACKWARD, OnBnClickedBackward)
	ON_BN_CLICKED(IDC_LEFT, OnBnClickedLeft)
	ON_BN_CLICKED(IDC_RIGHT, OnBnClickedRight)
	ON_BN_CLICKED(IDC_STOP, OnBnClickedStop)
	ON_BN_CLICKED(IDC_CHECK_VELOCITY, OnBnClickedCheckVelocity)
	ON_BN_CLICKED(IDC_CHECK_POSITION, OnBnClickedCheckPosition)
	ON_BN_CLICKED(IDC_CHECK_CORRESPOND, OnBnClickedCheckCorrespond)
	ON_BN_CLICKED(IDC_CHECK_PID, OnBnClickedCheckPid)
	ON_BN_CLICKED(IDC_CHECK_DEBUGPID, OnBnClickedCheckDebugpid)
	ON_BN_CLICKED(IDC_CHECK_LOADPID, OnBnClickedCheckLoadpid)
	ON_BN_CLICKED(IDC_CHECK_SAVEPID, OnBnClickedCheckSavepid)
	ON_BN_CLICKED(IDC_BUTTON_SAVEPID, OnBnClickedButtonSavepid)
	ON_BN_CLICKED(IDC_BUTTON_LOOK, OnBnClickedButtonLook)
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_BtnRC, &CMyMotionDlg::OnBnClickedBtnrc)
	ON_BN_CLICKED(IDC_BtnIP, &CMyMotionDlg::OnBnClickedBtnip)
	ON_MESSAGE(WM_USER_THREAD,OnMyMessage)
END_MESSAGE_MAP()


// CMyMotionDlg 消息处理程序

BOOL CMyMotionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	::CreateDirectory("c:\\Data",NULL);//创建文件夹
	ofstream outlv("c:\\Data\\lv.txt");
	ofstream outrv("c:\\Data\\rv.txt");
	ofstream outld("c:\\Data\\ld.txt");
	ofstream outrd("c:\\Data\\rd.txt");
	ofstream outla("c:\\Data\\la.txt");
	ofstream outra("c:\\Data\\ra.txt");
	if(!BuildSystem())//创建系统
	{
		return FALSE;
	}

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CMyMotionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyMotionDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMyMotionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CMyMotionDlg::BuildSystem(void)
{
	for (int i=0;i<16;i++) m_fDis[i] = 100 ;
	try
	{
		CreateDevice("MOTION",m_pDevMotion);// 根据给定的设备名称创建对应设备
		//，若创建成功，给传入的设备接口赋值。第一个参数：需要创建的设备名称
		//，如运动设备名称为：MOTION；第二个参数：创建的设备接口
		//，详见接口函数库
		m_pDevMotion->Init(); //初始化部件
		AddMsgReceiver(m_pDevMotion); // 将当前设备加入用户程序的设备列表；
		m_pDevMotion->QueryInterface(InterfaceID_MOTION, (LPVOID*)&m_pMotion);//查询部件实现的接口。第一个参数：对应接口标识；
		//第二个参数：对应设备对象地址，若设备创建失败，返回NULL；

		CreateDevice("MTULTRASONIC",sonarDev);//创建声波的虚拟设备
		AddMsgReceiver(sonarDev);
		sonarDev->QueryInterface(InterfaceID_ULTRASONIC, (LPVOID*)&m_pSonar);
		m_pSonar->SetSonarProc(RecvProc,(LPVOID*)this) ;

		CreateDevice("MTPSD",m_PSDDev);//创建红外的虚拟设备
		AddMsgReceiver(m_PSDDev);
		m_PSDDev->QueryInterface(InterfaceID_PSD, (LPVOID*)&m_pPSD);
		m_pPSD->SetPSDProc(PSD_RecvProc,(LPVOID*)this);

		Broadcast(NTY_MSG_DEV_PTR, sonarDev,pGlobalDevLst);
		Broadcast(NTY_MSG_DEV_PTR, m_PSDDev,pGlobalDevLst);

		SetTimer(1,100,0);

		m_proc = PIDFunc;
		m_pMotion->SetMotionProc(m_proc,this);//Set event handling process

		CreateDevice("MTENCODER",m_pDevEncoder);//创建编码器设备接口  激光码盘定位系统
		m_pDevEncoder->Init();
		AddMsgReceiver(m_pDevEncoder);
		m_pDevEncoder->QueryInterface(InterfaceID_ENCODER,(LPVOID*)&m_pEncoder);

		m_EncoderProc = EncoderProcFun;
		m_pEncoder->SetEncoderProc(m_EncoderProc,this);

		//传入一个函数EncoderDisProcFun指针，该函数接收到事件后，交由该指针指向的函数处理
		m_EncoderDisProc = EncoderDisProcFun;
		m_pEncoder->SetEncoderDisProc(m_EncoderDisProc,this);
		if (m_pEncoder)
		{
			m_pEncoder->EncoderDis();//获得码盘相对位移
		}

	}
	catch (IngeniousException& e)
	{
		Cleanup();//当程序出现异常时，停止并销毁创建的指针
		String16 str16;
		char strTchar[256];
		str16 = e.GetErrorMessage();
		setlocale(LC_CTYPE,"");
		wcstombs(strTchar, str16.c_str(), 256);
		MessageBox(strTchar, "ERROR", MB_OK);
		return 1;
	}
	UpdateData(TRUE);
// 	/*********************
// 	获取本地IP地址(CString)
// 	*********************/
// 	char name[255];
// 	PHOSTENT hostinfo;
// 	if( gethostname ( name, sizeof(name)) == 0)
// 	{
// 		if((hostinfo = gethostbyname(name)) != NULL)
// 		{
// 			m_CstrIP = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
// 		}
// 	}

	return 0;
}

int CMyMotionDlg::DestroySystem(void)
{
	try
	{
		KillTimer(1);
		if(m_pMotion)
		{
			m_pMotion->End();              //停止使用运动设备
			m_pMotion->Release();          //释放基本运动控制接口
			m_pMotion = NULL;
		}
		if (m_pEncoder)
		{
			m_pEncoder->Release();
			m_pEncoder = NULL;
		}
	}
	catch(IngeniousException& e)
	{
		String16 str16;
		char strTchar[256];
		str16 = e.GetErrorMessage();
		setlocale(LC_CTYPE,"");
		wcstombs(strTchar, str16.c_str(), 256);
		MessageBox(strTchar, "ERROR", MB_OK);
		return -1;
	}
	return 0;
}

void CMyMotionDlg::OnDestroy()
{
	CDialog::OnDestroy();
	DestroySystem();
	// TODO: 在此处添加消息处理程序代码
}

//机器人原先的移动方式
void CMyMotionDlg::Move(float lSpeed, int lKp,int lKi,int lKd,float la,float ls,float rSpeed,int rKp,int rKi,int rKd,float ra,float rs)
{
	UpdateData(TRUE);
	static CString s1;
	char s[256];	
	if (m_ModeSelect+m_ModeSelect1==4)
	{
		MessageBox("请选择速度闭环或位置闭环!");
	}
	if (!IsDlgButtonChecked(IDC_CHECK_PID)&&!IsDlgButtonChecked(IDC_CHECK_DEBUGPID)&&!IsDlgButtonChecked(IDC_CHECK_LOADPID))
	{
		m_PidSelect = 1;
	}
	if (!IsDlgButtonChecked(IDC_CHECK_VELOCITY)&&!IsDlgButtonChecked(IDC_CHECK_POSITION)&&!IsDlgButtonChecked(IDC_CHECK_CORRESPOND)&&!IsDlgButtonChecked(IDC_CHECK_SAVEPID)) 
	{
		m_ModeSelect = 1;
		m_ModeSelect1 = 0;
	}
	sprintf(s,"%d%d%f%f%d%d%d%d%d%d%f%f%f%f",m_ModeSelect+m_ModeSelect1, m_PidSelect,lSpeed,rSpeed,lKp,lKi,lKd,rKp,rKi,rKd,la,ls,ra,rs);
	if (s1!=s)
	{
		m_CurrentTimer = m_t;
		m_CurrentLD = ld_basic;
		m_CurrentRD = rd_basic;
	}
	s1 = s;
	ASSERT(m_pMotion);	
	if (m_pMotion)
	{
		m_pMotion->drive(m_ModeSelect+m_ModeSelect1, m_PidSelect,lSpeed, lKp, lKi, lKd, la, ls,  rSpeed, rKp, rKi, rKd, ra, rs);
		//参数1：1为速度闭环；参数2：1为默认PID；参数3：左轮速度；参数4：
		//左轮P值；参数5：左轮I值；参数6：左轮D值；参数7：左轮加速度；
		//参数8：左轮位移；参数9：右轮速度；参数10：右轮P值；
		//参数11：右轮I值；参数12：右轮D值；参数13：右轮加速度；参数14：右轮位移；
	}
}

//现有的机器人的移动方式  与控制器相结合
void CMyMotionDlg::robotmove(float lSpeed, float la,float rSpeed,float ra)
{
	ASSERT(m_pMotion);	
	if (m_pMotion)
	{
		m_pMotion->drive(1,1,lSpeed, 0,0,0, la, 0, rSpeed, 0,0,0, ra,0);
		//参数1：1为速度闭环；参数2：1为默认PID；参数3：左轮速度；参数4：
		//左轮P值；参数5：左轮I值；参数6：左轮D值；参数7：左轮加速度；
		//参数8：左轮位移；参数9：右轮速度；参数10：右轮P值；
		//参数11：右轮I值；参数12：右轮D值；参数13：右轮加速度；参数14：右轮位移；
	}
}


void CMyMotionDlg::Cleanup(void)
{
	if(m_pMotion)
	{
		m_pMotion->End();
		m_pMotion->Release();        
		m_pMotion = NULL;
	}
}

void CMyMotionDlg::OnBnClickedForward()
{
	UpdateData(TRUE);
	m_fLv = m_fLeftSpeed;
	m_fRv = m_fRightSpeed;
	Move(m_fLv, m_lKp,m_lKi,m_lKd,m_la,m_ls,m_fRv,m_rKp,m_rKi,m_rKd,m_ra,m_rs); 

}

void CMyMotionDlg::OnBnClickedBackward()
{
	UpdateData(TRUE);
	m_fLv = -m_fLeftSpeed;
	m_fRv = -m_fRightSpeed;
	Move(m_fLv,  m_lKp,m_lKi,m_lKd,m_la,m_ls, m_fRv,m_rKp,m_rKi,m_rKd,m_ra,m_rs);
}

void CMyMotionDlg::OnBnClickedLeft()
{
	UpdateData(TRUE);
	m_fLv = -m_fLeftSpeed;
	m_fRv = m_fRightSpeed;
	Move(m_fLv, m_lKp,m_lKi,m_lKd,m_la,m_ls, m_fRv,m_rKp,m_rKi,m_rKd,m_ra,m_rs);
}

void CMyMotionDlg::OnBnClickedRight()
{
	UpdateData(TRUE);
	m_fLv = m_fLeftSpeed;
	m_fRv = -m_fRightSpeed;
	Move(m_fLv,  m_lKp,m_lKi,m_lKd,m_la,m_ls, m_fRv,m_rKp,m_rKi,m_rKd,m_ra,m_rs);
}

void CMyMotionDlg::OnBnClickedStop()
{
	m_fLv = 0.0f;
	m_fRv = 0.0f;
	Move(0.0f,m_lKp,m_lKi,m_lKd,m_la,m_ls,0.0f,m_rKp,m_rKi,m_rKd,m_ra,m_rs);


	//KillTimer(1);
}

void CMyMotionDlg::OnBnClickedCheckVelocity()
{
	if (IsDlgButtonChecked(IDC_CHECK_VELOCITY))
	{
		GetDlgItem(IDC_CHECK_POSITION)->EnableWindow(FALSE);//disable IDC_CHECK_POSITION
		GetDlgItem(IDC_CHECK_SAVEPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_LS)->EnableWindow(FALSE);
		GetDlgItem(IDC_RS)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
		m_ModeSelect = 1;
	}
	else
	{
		GetDlgItem(IDC_CHECK_POSITION)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_SAVEPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_LS)->EnableWindow(TRUE);
		GetDlgItem(IDC_RS)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
		m_ModeSelect = 0;
	}
}

void CMyMotionDlg::OnBnClickedCheckPosition()
{
	if (IsDlgButtonChecked(IDC_CHECK_POSITION))
	{
		GetDlgItem(IDC_CHECK_VELOCITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_SAVEPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
		m_ModeSelect = 2;
	}
	else
	{
		GetDlgItem(IDC_CHECK_VELOCITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_SAVEPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
		m_ModeSelect = 0;
	}
}

void CMyMotionDlg::OnBnClickedCheckCorrespond()
{
	if (IsDlgButtonChecked(IDC_CHECK_CORRESPOND))
	{
		if (IsDlgButtonChecked(IDC_CHECK_POSITION))
		{
			m_ModeSelect1 = 4;
		}
		else if (IsDlgButtonChecked(IDC_CHECK_VELOCITY))
		{
			m_ModeSelect1 = 4;
		}
		else
		{
			MessageBox("请选择速度闭环或位置闭环");
		}
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
	}
	else
	{
		m_ModeSelect1 = 0;
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
	}
}

void CMyMotionDlg::OnBnClickedCheckPid()
{
	if (IsDlgButtonChecked(IDC_CHECK_PID))
	{
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_LKP)->EnableWindow(FALSE);
		GetDlgItem(IDC_LKI)->EnableWindow(FALSE);
		GetDlgItem(IDC_LKD)->EnableWindow(FALSE);
		GetDlgItem(IDC_RKP)->EnableWindow(FALSE);
		GetDlgItem(IDC_RKI)->EnableWindow(FALSE);
		GetDlgItem(IDC_RKD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);	
		m_PidSelect = 1;
	}
	else
	{
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_LKP)->EnableWindow(TRUE);
		GetDlgItem(IDC_LKI)->EnableWindow(TRUE);
		GetDlgItem(IDC_LKD)->EnableWindow(TRUE);
		GetDlgItem(IDC_RKP)->EnableWindow(TRUE);
		GetDlgItem(IDC_RKI)->EnableWindow(TRUE);
		GetDlgItem(IDC_RKD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
	}
}

void CMyMotionDlg::OnBnClickedCheckDebugpid()
{
	if (IsDlgButtonChecked(IDC_CHECK_DEBUGPID))
	{
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
		m_PidSelect = 2;
	}
	else
	{
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
	}
}

void CMyMotionDlg::OnBnClickedCheckLoadpid()
{
	if (IsDlgButtonChecked(IDC_CHECK_LOADPID))
	{
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
		m_PidSelect = 4;
	}
	else
	{
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
	}
}

void CMyMotionDlg::OnBnClickedCheckSavepid()
{
	if (IsDlgButtonChecked(IDC_CHECK_SAVEPID))
	{
		m_ModeSelect = 8;
		GetDlgItem(IDC_CHECK_VELOCITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_POSITION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_CORRESPOND)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(FALSE);
		GetDlgItem(IDC_LEFTSPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_RIGHTSPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_LA)->EnableWindow(FALSE);
		GetDlgItem(IDC_LS)->EnableWindow(FALSE);
		GetDlgItem(IDC_RA)->EnableWindow(FALSE);
		GetDlgItem(IDC_RS)->EnableWindow(FALSE);
		GetDlgItem(IDC_FORWARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BACKWARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_LEFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_RIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_VELOCITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_POSITION)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_CORRESPOND)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_PID)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_DEBUGPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_LOADPID)->EnableWindow(TRUE);
		GetDlgItem(IDC_LEFTSPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_RIGHTSPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_LA)->EnableWindow(TRUE);
		GetDlgItem(IDC_LS)->EnableWindow(TRUE);
		GetDlgItem(IDC_RA)->EnableWindow(TRUE);
		GetDlgItem(IDC_RS)->EnableWindow(TRUE);
		GetDlgItem(IDC_FORWARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BACKWARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_LEFT)->EnableWindow(TRUE);
		GetDlgItem(IDC_RIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SAVEPID)->EnableWindow(FALSE);
	}
}

void CMyMotionDlg::OnBnClickedButtonSavepid()
{
	UpdateData(TRUE);
	m_pMotion->drive(m_ModeSelect, 0,0.0f, m_lKp, m_lKi, m_lKd, 0.0f, 0.0f, 0.0f, m_rKp, m_rKi, m_rKd, 0.0f, 0.0f);
}

void CMyMotionDlg::OnBnClickedButtonLook()
{
	if (m_pMotion)
	{
		m_pMotion->EnableMotion(1,1);//Check PID Parameters
	}
}

void __stdcall CMyMotionDlg::PIDFunc(void* pParam, UInt8 LP, UInt8 LI,UInt8 LD,UInt8 RP,UInt8 RI,UInt8 RD)
{
	CMyMotionDlg *pThis = (CMyMotionDlg*)pParam;
	CSingleLock sLock(&(pThis->m_Mutex));
	sLock.Lock();
	char s[256];
	sprintf(s,"%s%d","左轮P值为:",LP);
	pThis->GetDlgItem(IDC_STATIC_LP)->SetWindowText(s);
	sprintf(s,"%s%d","左轮I值为:",LI);
	pThis->GetDlgItem(IDC_STATIC_LI)->SetWindowText(s);
	sprintf(s,"%s%d","左轮D值为:",LD);
	pThis->GetDlgItem(IDC_STATIC_LD)->SetWindowText(s);
	sprintf(s,"%s%d","右轮P值为:",RP);
	pThis->GetDlgItem(IDC_STATIC_RP)->SetWindowText(s);
	sprintf(s,"%s%d","右轮I值为:",RI);
	pThis->GetDlgItem(IDC_STATIC_RI)->SetWindowText(s);
	sprintf(s,"%s%d","右轮D值为:",RD);
	pThis->GetDlgItem(IDC_STATIC_RD)->SetWindowText(s);
	pThis->m_lKp=LP;
	pThis->m_lKi=LI;
	pThis->m_lKd=LD;
	pThis->m_rKp=RP;
	pThis->m_rKi=RI;
	pThis->m_rKd=RD;
	sLock.Unlock();
}

//编码器显示函数
void _stdcall CMyMotionDlg::EncoderDisProcFun(void *pParam, float32* value, UInt16 num)
{
	CMyMotionDlg *pThis = (CMyMotionDlg*)pParam;
	CSingleLock sLock(&(pThis->m_Mutex));
	sLock.Lock();
	pThis->m_fEncoderDis[num] = *value;//码盘相对位移分别为左轮相对位移、右轮相对位移、x轴相对位移、y轴相对位移，x轴向前，y轴向左
	if(num==3)
	{
		pThis->on_odo();
	}
	sLock.Unlock();
}

//声波回调函数
void __stdcall CMyMotionDlg::RecvProc(void* pParam,float32* speed, UInt16 num)//声波回调函数
{
	CMyMotionDlg *dlg = (CMyMotionDlg*)pParam;
// 	CString strBuffer="";
// 	CSingleLock sLock(&(dlg->m_Mutex));
// 	sLock.Lock();
// 	strBuffer.Format("channels %d:%f",num,*value);
// 	sLock.Unlock();
//     dlg->AddToListBox(strBuffer);
	dlg->m_fDis[num] = (float)(*speed) ;

}

//红外回调函数
void __stdcall CMyMotionDlg::PSD_RecvProc(void* pParam, float32* speed, UInt16 num)//红外回调函数

{
	CMyMotionDlg *dlh = (CMyMotionDlg*)pParam;

	dlh->PSD_m_fDis[num] = (float)(*speed);

}

//编码器处理函数
void _stdcall CMyMotionDlg::EncoderProcFun(void *pParam,float32* lvelocity, float32* rvelocity, float32* ldistance,float32* rdistance,float32 timer)
{
	CMyMotionDlg *pThis = (CMyMotionDlg*)pParam;
	CSingleLock sLock(&(pThis->m_Mutex));
	sLock.Lock();
	static float32 lvelocity0 = 0.0f;//前一时刻左轮速
	static float32 rvelocity0 = 0.0f;//前一时刻右轮速
	static int t=0;//时间超过8分钟的整数倍时加一，用于清除存储的数据

	float32 lv_basic = 0.0f;//左轮期望速度
	float32 rv_basic = 0.0f;//右轮期望速度
	float32 la_basic = 0.0f;//左轮期望加速度
	float32 ra_basic = 0.0f;//右轮期望加速度

	static float32 ld_basic1 = 0.0f;//左轮加速或减速时走过的位移
	float32 ld_basic2 = 0.0f;//左轮匀速时的位移
	static float32 rd_basic1 = 0.0f;//右轮加速或减速时走过的位移
	float32 rd_basic2 = 0.0f;//右轮匀速时的位移
	float32 la;//左轮加速度
	float32 ra;//右轮加速度
	la = ((*lvelocity)-lvelocity0)/timer;
	ra = ((*rvelocity)-rvelocity0)/timer; 
	if (la>5)//用于滤除偏差过大的值
	{
		la =pThis->m_la;
	}
	if (ra>5)
	{
		ra =pThis->m_ra;
	}
	lvelocity0 = *lvelocity;
	rvelocity0 = *rvelocity;
	m_t +=timer;//m_t为运行时间值，timer为上一时刻采集与这一时刻采集之间的差值
	pThis->m_fEncoder[0] = *lvelocity;
	pThis->m_fEncoder[1] = *rvelocity; 
	pThis->m_fEncoder[2] = *ldistance;
	pThis->m_fEncoder[3] = *rdistance; 
	pThis->m_fEncoder[4] = m_t; 

	//实际机器人的速度信息
	pThis->V1 = *lvelocity;  //左轮速度
	pThis->V2 = *rvelocity;//右轮速度
	pThis->S1 = *ldistance;//左轮位移
	pThis->S2 = *rdistance;  //右轮位移
	pThis->acc1 = la; //左轮加速度
	pThis->acc2 = ra; //右轮加速度

	pThis->EncodeTime = m_t;  //编码器中运行的时间
	char s[256];
	sprintf(s,"%.2f",pThis->m_fEncoderDis[0]);
	pThis->GetDlgItem(IDC_EDIT_LDIS)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoderDis[1]);
	pThis->GetDlgItem(IDC_EDIT_RDIS)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoderDis[2]);
	pThis->GetDlgItem(IDC_EDIT_XDIS)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoderDis[3]);
	pThis->GetDlgItem(IDC_EDIT_YDIS)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoder[0]);
	pThis->GetDlgItem(IDC_EDIT_V1)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoder[1]);
	pThis->GetDlgItem(IDC_EDIT_V2)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoder[2]);
	pThis->GetDlgItem(IDC_EDIT_D1)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoder[3]);
	pThis->GetDlgItem(IDC_EDIT_D2)->SetWindowText(s);
	sprintf(s,"%.2f",pThis->m_fEncoder[4]);
	if (m_t>480*t&&m_t<483*t)//间隔8分钟后清空文件内容
	{
		t++;
		outlv.close();
		outrv.close();
		outld.close();
		outrd.close();
		outla.close();
		outra.close();
		outlv.open("C:\\Data\\lv.txt");
		outrv.open("C:\\Data\\rv.txt");
		outld.open("C:\\Data\\ld.txt");
		outrd.open("C:\\Data\\rd.txt");
		outla.open("C:\\Data\\la.txt");
		outra.open("C:\\Data\\ra.txt");
	}
	else
	{
		float ttl=0.0f;
		float ttr=0.0f;
		static float m_fLv1 =0.0f;//上一时刻左轮速度值
		static float m_fRv1 =0.0f;//上一时刻右轮速度值
		ttl=(abs)(pThis->m_fLv)/pThis->m_la;//加速或减速到期望左轮速度值时的时间

		if (m_t<=ttl||pThis->m_fLv!=m_fLv1||pThis->m_fRv!=m_fRv1)//当时间没有到达期望时间或速度改变时
		{
			if (pThis->m_fLv>m_fLv1)
			{
				lv_basic = m_fLv1+(m_t-pThis->m_CurrentTimer)*pThis->m_la;//左轮期望速度
			}
			else if (pThis->m_fLv>m_fLv1)
			{
				lv_basic = m_fLv1-(m_t-pThis->m_CurrentTimer)*pThis->m_la;
			}
			else if (pThis->m_fLv==m_fLv1)
			{
				if (pThis->m_fLv>=0)
				{
					lv_basic = (m_t-pThis->m_CurrentTimer)*pThis->m_la;
				}
				else
				{
					lv_basic = -(m_t-pThis->m_CurrentTimer)*pThis->m_la;
				}

			}
			la_basic = pThis->m_la;
			ld_basic1 = pThis->m_CurrentLD+0.5*pThis->m_la*(m_t-pThis->m_CurrentTimer)*(m_t-pThis->m_CurrentTimer);
		}
		else
		{
			lv_basic = pThis->m_fLv;
			la_basic = 0;
			ld_basic2 = pThis->m_fLv*(m_t-pThis->m_CurrentTimer);
		}
		m_fLv1 = pThis->m_fLv;
		ld_basic = ld_basic1+ld_basic2;
		outlv<<(*lvelocity)<<" "<<(*lvelocity)-lv_basic<<" "<<m_t<<" "<<lv_basic<<endl;//保存左轮速度参数值，
		//第一个为实际速度值，第二个为误差值，第三个为时间，第四个为期望速度值
		outla<<la<<" "<<la-la_basic<<" "<<m_t<<" "<<la_basic<<endl;//保存左轮加速度参数值，
		//第一个为实际加速度值，第二个为误差值，第三个为时间，第四个为期望加速度值
		outld<<(*ldistance)<<" "<<(*ldistance)-ld_basic<<" "<<m_t<<" "<<ld_basic<<endl;//保存左轮位移参数值，
		//第一个为实际位移值，第二个为误差值，第三个为时间，第四个为期望位移值

		ttr=pThis->m_fRv/pThis->m_ra;//加速或减速到期望右轮速度值时的时间
		if (m_t<=ttr||pThis->m_fRv!=m_fRv1||pThis->m_fLv!=m_fLv1)
		{
			if (pThis->m_fRv>m_fRv1)
			{
				rv_basic = m_fRv1+(m_t-pThis->m_CurrentTimer)*pThis->m_ra;
			}
			else if (pThis->m_fRv>m_fRv1)
			{
				rv_basic = m_fRv1-(m_t-pThis->m_CurrentTimer)*pThis->m_ra;
			}
			else if (pThis->m_fRv==m_fRv1)
			{
				if (pThis->m_fRv>=0)
				{
					rv_basic = (m_t-pThis->m_CurrentTimer)*pThis->m_ra;
				}
				else
				{
					rv_basic = -(m_t-pThis->m_CurrentTimer)*pThis->m_ra;
				}
			}
			ra_basic = pThis->m_ra;
			rd_basic1 = pThis->m_CurrentRD+0.5*pThis->m_ra*(m_t-pThis->m_CurrentTimer)*(m_t-pThis->m_CurrentTimer);
		}
		else
		{
			rv_basic = pThis->m_fRv;
			ra_basic = 0;
			rd_basic2 = pThis->m_fRv*(m_t-pThis->m_CurrentTimer);
		}
		m_fRv1 = pThis->m_fRv;
		rd_basic = rd_basic1+rd_basic2;
		outrv<<(*rvelocity)<<" "<<(*rvelocity)-rv_basic<<" "<<m_t<<" "<<rv_basic<<endl;//保存右轮速度参数值，
		//第一个为实际速度值，第二个为误差值，第三个为时间，第四个为期望速度值
		outra<<ra<<" "<<ra-ra_basic<<" "<<m_t<<" "<<ra_basic<<endl;//保存右轮加速度参数值，
		//第一个为实际加速度值，第二个为误差值，第三个为时间，第四个为期望加速度值
		outrd<<(*rdistance)<<" "<<(*rdistance)-rd_basic<<" "<<m_t<<" "<<rd_basic<<endl;//保存右轮位移参数值，
		//第一个为实际位移值，第二个为误差值，第三个为时间，第四个为期望位移值
	}
	sLock.Unlock();
}

void CMyMotionDlg::on_odo()
{

	char str[256];
	DWORD t;
	unsigned int timestamp;
	static double x=posandnav.robpos.laser_pose.x,y=posandnav.robpos.laser_pose.y,r=posandnav.robpos.laser_pose.rot;
	t = GetTickCount();
	static unsigned int prevtime = t;
	timestamp = t;
	// 取码盘反馈（叠加到 odo）及系统时间戳timestamp
	if(fabs(m_fEncoderDis[0])<0.1&&fabs(m_fEncoderDis[0])>0.0&&fabs(m_fEncoderDis[1])>0.0&&fabs(m_fEncoderDis[1])<0.1)
	{
		double dr = (m_fEncoderDis[1] - m_fEncoderDis[0]) / WHEELWIDTH;
		if (r > PI)
			r -= 2*PI; 
		else if (r <= -PI)
			r += 2*PI;
		double s = sin(r);
		double c = cos(r);
		x += (m_fEncoderDis[2] * c - m_fEncoderDis[3] * s);
		y += (m_fEncoderDis[2] * s + m_fEncoderDis[3] * c);
		r += dr;
		posandnav.on_odo(Pose2d(x,y,r), timestamp);
	}
}

void CMyMotionDlg::OnBnClickedButtonDetadis()
{
	if (m_pEncoder)
	{
		m_pEncoder->EncoderDis();
	}
}




void CMyMotionDlg::update()
{
	UpdateData(TRUE);
	m_theta = theta;
	m_thetaR = thetaR;
	m_Wr = Wr;
	m_V21 = Vd;
	m_V22 = Y;
	m_Vr = e3;
	m_Xr = Xr;
	m_Yr = Yr;
	m_e1 = e1;
	m_e2 = e2;
	m_e3 = e3;
	UpdateData(FALSE);
}

void CMyMotionDlg::delay()
{
	//UpdateData(TRUE);

	if(delaycount == 10)
		delaycount = 0;
	else
		delaycount++;

}
void CMyMotionDlg::movetotarget(int count)
{
	UpdateData(TRUE);
	if(count>10)
		count =0;
	else
	{
		if(count<=10)
		{
			Move(m_fLeftSpeed, m_lKp,m_lKi,m_lKd,m_la,m_ls,m_fRightSpeed,m_rKp,m_rKi,m_rKd,m_ra,m_rs); //前进
		}
		else
		{		
			Move(0, m_lKp,m_lKi,m_lKd,m_la,m_ls,0,m_rKp,m_rKi,m_rKd,m_ra,m_rs); 
			KillTimer(2);		
		}
	}
}

BOOL CMyMotionDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		switch(pMsg->wParam) 
		{
		case 'W':
			GetDlgItem(IDC_FORWARD )->SetFocus();
			OnBnClickedForward();
			UpdateData(FALSE);
			return TRUE;
			break;
		case 'S':
			GetDlgItem(IDC_BACKWARD)->SetFocus();
			OnBnClickedBackward();
			UpdateData(FALSE);
			return TRUE;
			break;
		case 'A':
			GetDlgItem(IDC_LEFT)->SetFocus();
			OnBnClickedLeft();
			UpdateData(FALSE);
			return TRUE;
			break;
		case 'D':
			GetDlgItem(IDC_RIGHT)->SetFocus();
			OnBnClickedRight();
			UpdateData(FALSE);
			return TRUE;
			break;			
		case VK_RETURN:
			UpdateData(FALSE);
			return TRUE;
			break;
		case VK_SPACE:
			GetDlgItem(IDC_STOP)->SetFocus();
			OnBnClickedStop();
			UpdateData(FALSE);
			return TRUE;
			break;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
} 

void CMyMotionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	fL = m_fDis[LEFTCHANNEL];
	fR = m_fDis[RIGHTCHANNEL];
	fF = m_fDis[FRONTCHANNEL];


	if(PSD_m_fDis[0]<40) PSD_FM=1;   else PSD_FM=0;
	if(PSD_m_fDis[2]<40) PSD_FL1=1;  else PSD_FL1=0;
	if(PSD_m_fDis[4]<40) PSD_FL2=1;  else PSD_FL2=0;
	if(PSD_m_fDis[7]<40) PSD_BM=1;   else PSD_BM=0;
	if(PSD_m_fDis[10]<40) PSD_FR2=1; else PSD_FR2=0;
	if(PSD_m_fDis[12]<40) PSD_FR1=1; else PSD_FR1=0;

	//m_pEncoder->EncoderDis();
	CurrentAngel=posandnav.robpos.robot_pose.rot*180.0/PI;
	switch(nIDEvent)
	{
	case 1:
		{
			update();
			break;
		}

	case 2:
		{
			framecount++;
			movetotarget(framecount);
			break;
		}
	case 3:
		{				
			delay();
			break;
		}
	default:
		break;

	}
	CDialog::OnTimer(nIDEvent);
}




void CMyMotionDlg::OnBnClickedBtnrc()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData();
	if( m_bSonar )
	{	

	m_pSonar->OpenChannel(0);
	m_pSonar->OpenChannel(2);
	m_pSonar->OpenChannel(4);
	m_pSonar->OpenChannel(7);
	m_pSonar->OpenChannel(10);
	m_pSonar->OpenChannel(12);

	m_pPSD->OpenChannel(0);
	m_pPSD->OpenChannel(2);
	m_pPSD->OpenChannel(4);
	m_pPSD->OpenChannel(10);
	m_pPSD->OpenChannel(7);
	m_pPSD->OpenChannel(12);


	}
	else
	{
	m_iState = 1;
	for (int i=0;i<16;i++) m_fDis[i] = 100 ;

	m_pSonar->CloseChannel(0);
	m_pSonar->CloseChannel(2);
	m_pSonar->CloseChannel(4);
	m_pSonar->CloseChannel(7);
	m_pSonar->CloseChannel(10);
	m_pSonar->CloseChannel(21);

	m_pPSD->CloseChannel(0);
	m_pPSD->CloseChannel(2);
	m_pPSD->CloseChannel(4);
	m_pPSD->CloseChannel(7);
	m_pPSD->CloseChannel(10);
	m_pPSD->CloseChannel(12);
	}*/
	/*UpdateData(false);*/
	UpdateData(TRUE);
	AfxBeginThread(ThreadCmd,this);
	/***************************************/
// 	AfxBeginThread(ThreadImgRecv,this);
// 	AfxBeginThread(ThreadImgLocalRecv,this);
// 	AfxBeginThread(ThreadImg,this);
	/***************************************/
	AfxBeginThread(ThreadImgRtpSending,this);
	AfxBeginThread(ThreadImgRtpReceiving,this);
	
	/***************************************/
	m_EdtImg="Video Transmission";
	UpdateData(FALSE);

	//UpdateData(TRUE);
	//SetTimer(1,100,	NULL);

	////SetTimer(1,100,	TimerProc);
	////主程序设在此 开始运行

	////Turn_Angel(90);
	//posandnav.robpos.robot_pose.x=0;//设置机器人初始位置
	//posandnav.robpos.robot_pose.y=0;

	////ToPositionPD(1,0);
	//Turn_Angel(90);
	/*AfxBeginThread(ThreadDetecting,this);*/
	//AfxBeginThread(ThreadImg,NULL);
}


void CMyMotionDlg::OnBnClickedBtnip()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	/*********************
	获取本地IP地址(CString)
	*********************/
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	CString ip;
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD( 2, 0 );

	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
	{
		if( gethostname ( name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
			{
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}

		WSACleanup( );
	}
	m_CstrIP=ip;
	UpdateData(FALSE);
}
afx_msg LRESULT CMyMotionDlg::OnMyMessage(WPARAM wParam,LPARAM lParam)
{
	UpdateData(TRUE);
	m_EdtRe=g_Commands;
	UpdateData(FALSE);
	if(strcmp(g_Commands, "left")==0)
	{
		OnBnClickedLeft();
	}
	else if(strcmp(g_Commands, "right")==0)
	{
		OnBnClickedRight();
	}
	else if(strcmp(g_Commands, "forward")==0)
	{
		OnBnClickedForward();
	}
	else if(strcmp(g_Commands, "backward")==0)
	{
		OnBnClickedBackward();
	}
	else if(strcmp(g_Commands, "stop")==0)
	{
		OnBnClickedStop();
	}
// 	else 
// 	{
// 		OnBnClickedStop();
// 	}
	return 0;
}
void CMyMotionDlg::DrawPicToHDC(IplImage *img, UINT ID)
{	CDC *pDC = GetDlgItem(ID)->GetDC(); 
HDC hDC= pDC->GetSafeHdc(); 
CRect rect; 
GetDlgItem(ID)->GetClientRect(&rect); 
CvvImage cimg; 
cimg.CopyOf(img); 
cimg.DrawToHDC(hDC,&rect); 
ReleaseDC(pDC); 
}

void CMyMotionDlg::DrawPicToHDC(Mat img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	IplImage pimg = IplImage(img); //Mat convto IplImage
	cimg.CopyOf(&pimg,1);           // 复制图片
	cimg.DrawToHDC( hDC, &rect ); // 将图片绘制到显示控件的指定区域内
	ReleaseDC( pDC );
}
bool CMyMotionDlg::Turn_Angel(float angel)
{
	float angel_original=CurrentAngel;
	if(angel>0)//右转
	{

		while(1)
		{

			Move(0.15,-0.15); 
			if(abs(CurrentAngel-angel_original)>=abs(angel))
			{Move(0,0);
			break;}

		}
	}

	else   //左转
	{           
		while(1)
		{   
			Move(-0.15,0.15);
			if(abs(CurrentAngel-angel_original)>abs(angel))
			{Move(0,0);
			break;}
		}


	}


	return 0;
}


void CMyMotionDlg::Move(float left, float right,float a)
{
	static CString s1;
	char s[256];
	sprintf(s,"%f %f %f",left,right,a);
	ASSERT(m_pMotion);
	if (s1!=s)
	{
		if ( m_pMotion )
		{
			m_pMotion->drive(1, 1,left, 0, 0, 0, a, 0,  right, 0, 0, 0, a, 0);
		}
	}
	s1=s;
}
void CMyMotionDlg::Move(float lv,float rv)
{
	if (fabs(lv)>1.0||fabs(rv)>1.0)
	{
		AfxMessageBox("速度值超过最大范围值",MB_OK);
	}
	else
	{
		static CString s1;
		char s[256];
		sprintf(s,"%f %f",lv,rv);
		ASSERT(m_pMotion);
		if (s1!=s)
		{
			if (m_pMotion)
			{
				m_pMotion->drive(1,1,lv,0,0,0,0.5,0,rv,0,0,0,0.5,0);
			}
		}
		s1=s;
	}

}