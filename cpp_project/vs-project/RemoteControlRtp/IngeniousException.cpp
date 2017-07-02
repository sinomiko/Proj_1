//#include "StdAfx.h"
#include "IngeniousException.h"

// begin to implement the IngeniousException class

IngeniousException::IngeniousException(String16 tips,UInt32 id/*,ERROR_TYPE = ERROR*/)
: m_tips(tips)
//, m_errorType(ERROR)
, m_errorID(id)
{
#ifdef _DEBUG
	m_traceLevel = GUI_DEBUG;
#endif
}

IngeniousException::~IngeniousException(void)
{

}

int  IngeniousException::GetErrorID()
{	
	return (int)m_errorID;
}

String16  IngeniousException::GetErrorMessage()
{
	return GetMessageFromID(m_errorID);
	/*return String16(L"");*/
}

char*	IngeniousException::GetErrorMsg()
{
	String16 str16= GetErrorMessage();
	char *strTchar = new char[256];
	setlocale(LC_CTYPE,"");
	wcstombs(strTchar, str16.c_str(), 256);
	return strTchar ;
}

#ifdef _DEBUG
void  IngeniousException::SetTraceLevel(TRACE_LEVEL level)
{
	m_traceLevel = level;
}

void  IngeniousException::TraceOutput()
{
}
#endif

// begin to implement the OsException class
ErrorInfo OsException::ErrorTable1[] = 
{
	{ERR_SYS ,		String16(L"系统 --- ")},
	{ERR_CAP ,		String16(L"图象采集设备 --- ")},
	{ERR_IMAGE   ,		String16(L"图象处理设备 --- ")},
	{ERR_NETDEV ,		String16(L"网络设备 --- ")},
	{ERR_MOTION ,		String16(L"运动控制设备 --- ")},
	{ERR_VOICE   ,		String16(L"语音设备 --- ")},
	{ERR_SERIAL ,		String16(L"串口设备 --- ")},
	{ERR_MONITOR ,		String16(L"监控设备 --- ")},
	{ERR_PSD   ,		String16(L"PSD设备 --- ")},
	{ERR_ULTRASONIC   , 	String16(L"超声设备 --- ")},
	{ERR_ENCODER ,          String16(L"码盘---")},
	{ERR_MTFITTINGS ,   String16(L"配件设备---")},
	{ERR_GYRO ,         String16(L"陀螺仪---")},
	{ERR_ACCELEROMETER ,String16(L"加速度计---")},
	{ERR_COMPASS3200 ,  String16(L"平面罗盘---")},
	{ERR_CAMERA,        String16(L"云台摄像机---")},
	{ERR_DIDO,       String16(L"DIDO设备---")},
	{ERR_CHECK,       String16(L"硬件自检---")},
	{0,String16(L"")}
};

ErrorInfo OsException::ErrorTable2[] = 
{
	{ERR_FILENOTFOUND ,		String16(L"路径错误，文件未找到!")},
	{ERR_DEV_CREATEFAIL ,		String16(L"设备创建失败")},
	{ERR_USER_PTRNULL   ,		String16(L"用户指针为空")},
	{ERR_DEV_INITFAIL ,		String16(L"初始化失败")},
	{ERR_DEV_STARTFAIL ,		String16(L"启动失败")},
	{ERR_BUFFPTRNULL   ,		String16(L"设备缓冲区指针为空")},
	{ERR_DEV_ENDFAIL ,		String16(L"停止设备操作失败")},
	{ERR_INTERFACENOTEXIST ,	String16(L"查询的接口不存在")},
	{ERR_CREATEOBJECTFAIL , 	String16(L"创建部件对象失败")},
	{ERR_NEWFACTORYFAIL ,		String16(L"NEW创建COM FACTORY失败")},
	{ERR_FACTORYIDNOTMATCH ,	String16(L"FACTORY ID不匹配")},
	{ERR_CREATEINSTANCE   , 	String16(L"创建COM实例失败")},
	{ERR_UNRECO ,			String16(L"未知错误")},
	{ERR_SOCKINITFAIL ,		String16(L"SOCKET初始化失败")},
	{ERR_CONNECTFAIL   ,		String16(L"SOCKET连接失败")},
	{ERR_SOCKBINDFAIL ,		String16(L"SOCKET绑定失败")},
	{ERR_SOCKLISTENFAIL ,		String16(L"SOCKET监听失败")},
	{ERR_ACCEPTFAIL   ,		String16(L"接受SOCKET创建失败")},
	{ERR_SENDFAIL ,			String16(L"发送数据失败")},
	{ERR_COLORN24 ,			String16(L"颜色为非24色")},
	{ERR_VIDEODEVICEUNVALID   , 	String16(L"视频设备无效")},
	{ERR_COLORN256   ,		String16(L"颜色为非256色")},
	{ERR_LOADFILEFAIL   ,		String16(L"加载文件失败")},
	{0,String16(L"")}
};

ErrorInfo OsException::ErrorTable3[] = 
{
	{ERR_DEV_STATE , String16(L"设备状态轮转错误")},
	{0,String16(L"")}
};

OsException::OsException(String16 tips,UInt32 id/*,ERROR_TYPE errorType = ERROR*/)
: IngeniousException(tips,id/*,errorType*/)
{

}

OsException::~OsException()
{
}

 String16 OsException::GetMessageFromID( UInt32 id )
{

	long temp1;
	long temp2;
	long temp3;
	temp1 = id & 0x0ff0000;
	temp2 = id & 0x00ff00;
	temp3 = id & 0x0000ff;
	String16 str1,str2,str3;
	String16 strRes(L"");

	for ( int i = 0;ErrorTable1[i].id > 0; i++ )
	{
		if ( ErrorTable1[i].id == temp1 )
		{
			str1 = ErrorTable1[i].message;
		}
	}
	for ( int i = 0;ErrorTable2[i].id > 0; i++ )
	{
		if ( ErrorTable2[i].id == temp2 )
		{
			str2 = ErrorTable2[i].message;
		}
	}
/*	for ( int i = 0;ErrorTable3[i].id > 0; i++ )
	{
		if ( ErrorTable3[i].id == temp3 )
		{
			str3 = ErrorTable3[i].message;
		}
	}
*/
	strRes.append(str1);
	strRes.append(str2);
//	strRes.append(str3);
	return String16(strRes);
}

