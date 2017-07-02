#ifndef _HEADER_H_RTPH263
#define _HEADER_H_RTPH263

#include "encoder/libr263.h"
#include "decoder/Tmndec.h"

//#include "rtplib/rtpheader.h"

#include "rtpsession.h"
#include "rtpudpv4transmitter.h"
#include "rtpipv4address.h"
#include "rtpsessionparams.h"
#include "rtperrors.h"
#include "rtppacket.h"
#ifndef WIN32
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif // WIN32
//using namespace jrtplib;

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//#ifdef _DEBUG
//#pragma comment(lib, "opencv_core244d.lib")
//#pragma comment(lib, "opencv_highgui244d.lib")
//#pragma comment(lib, "opencv_imgproc244d.lib")
//#else
//#pragma comment(lib, "opencv_core220.lib")
//#pragma comment(lib, "opencv_highgui220.lib")
//#pragma comment(lib, "opencv_imgproc220.lib")
//#endif

#define WIDTH_QCIF 176
#define HEIGHT_QCIF 144

#define WIDTH_CIF  352
#define HEIGHT_CIF 288

//定义了CIF则使用CIF大小，否则使用QCIF大小
#define CIF			

#ifdef CIF
#define WIDTH		WIDTH_CIF
#define HEIGHT		HEIGHT_CIF
#define PARAM_FORM	CPARAM_CIF
#else
#define WIDTH	WIDTH_QCIF
#define HEIGHT	HEIGHT_QCIF
#define PARAM_FORM	CPARAM_QCIF
#endif
#endif	//for _HEADER_H_RTPH263