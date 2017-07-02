#pragma once

#define METHOD_NOT_IMP 10000
#define FILE_NOT_FOUND 10001
#define MEMORY_ALLOC   10002
#pragma warning(disable:4996)                                     
//namespace MTR {

#include "ingenious.h"
#include "globalDef.h"

typedef struct tagErrorInfo
{
	UInt32   id;
	String16 message;	
}ErrorInfo;

class IngeniousException : public std::exception
{
public:
	//enum ERROR_TYPE{ ERROR , WARNING };

	//explicit IngeniousException(String16 tips,UInt32 id,ERROR_TYPE errorType = ERROR);
	explicit IngeniousException(String16 tips,UInt32 id);
	virtual  ~IngeniousException(void);
	
	String16	GetTips();
	int			GetErrorID();
	String16	GetErrorMessage();
	char*		GetErrorMsg();

#ifdef _DEBUG
	// FILE			: dump to the MTR.txt file
	// GUI_DEBUG    : dump to Ingenious debug GUI tool
	enum  TRACE_LEVEL{ FILE, GUI_DEBUG };
	void  SetTraceLevel(TRACE_LEVEL type);
	void  TraceOutput();

private:
	TRACE_LEVEL m_traceLevel;
#endif

protected:
	virtual String16  GetMessageFromID(UInt32 id) = 0;

private:
	String16  m_tips;
	UInt32    m_errorID;
	//ERROR_TYPE m_errorType;
};

class OsException : public IngeniousException
{
public:
	//explicit OsException(String16 tips,UInt32 id,ERROR_TYPE errorType = ERROR);
	explicit OsException(String16 tips,UInt32 id);
	virtual  ~OsException();

protected:
	virtual String16  GetMessageFromID(UInt32 id);
private:
	static  ErrorInfo ErrorTable1[];
	static  ErrorInfo ErrorTable2[];
	static  ErrorInfo ErrorTable3[];
};

class ComException : public IngeniousException                   
{

};

class SensorException : public IngeniousException
{

};

class NetworkException : public IngeniousException
{

};

class MotionException : public IngeniousException
{

};
 
//};  // end namespace MTR

