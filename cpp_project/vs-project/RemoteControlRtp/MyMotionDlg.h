// MyMotionDlg.h : 头文件
#include "stdafx.h"

#pragma once
#include "afxmt.h"
#include "afxwin.h"
#define WM_USER_THREAD WM_USER+1
static CString g_Commands; 
using namespace std;
using namespace cv;
// CMyMotionDlg 对话框
class CMyMotionDlg : public CDialog
{
// 构造
public:
	CMyMotionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYMOTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	int BuildSystem(void);
	int DestroySystem(void);
	void Cleanup(void);
	afx_msg void OnDestroy();
public:
	int m_lKp;
	int m_lKi;
	int m_lKd;
	float m_la;
	float m_ls;
	int m_rKp;
	int m_rKi;
	int m_rKd;
	float m_ra;
	float m_rs;
public:
	int m_ModeSelect;
	int m_PidSelect;
	int m_ModeSelect1;
	void Move(float lSpeed, int lKp,int lKi,int lKd,float la,float ls,float rSpeed,int rKp,int rKi,int rKd,float ra,float rs);

	afx_msg void OnBnClickedForward();
	afx_msg void OnBnClickedBackward();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedCheckVelocity();
	afx_msg void OnBnClickedCheckPosition();
	afx_msg void OnBnClickedCheckCorrespond();
	afx_msg void OnBnClickedCheckPid();
	afx_msg void OnBnClickedCheckDebugpid();
	afx_msg void OnBnClickedCheckLoadpid();
	afx_msg void OnBnClickedCheckSavepid();
	afx_msg void OnBnClickedButtonSavepid();
	afx_msg void OnBnClickedButtonLook();
	CMutex m_Mutex;
	DeviceMotionProc m_proc;
	DeviceEncoderProc m_EncoderProc;

	float m_fLeftSpeed;
	float m_fRightSpeed;
	float m_fLv;
	float m_fRv;
	int m_ClrState;
	float e_la;
	float e_ra;
	float m_CurrentTimer;
	float m_CurrentLD;
	float m_CurrentRD;
	afx_msg void OnBnClickedButtonDetadis();
	float m_fEncoder[5];
public:
	void targetRobot(IplImage* img,int i);
	void targetTrajectory(int framecount);
	void update();
	void robotmove(float lSpeed, float la,float rSpeed,float ra);
	void robotdrawline(IplImage* img,CvBox2D pre_Rage2D,CvBox2D End_Rage2D);
	void movetotarget(int count);
	void robotController(float lSpeed,float rSpeed,float acce);
	void delay();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// 期望机器人x轴方向速度
	float Vrx;
	// 期望机器人y轴方向速度
	float Vry;
	// 图像中实际机器人的X轴位置
	float X;
	// 图像中实际机器人的Y轴位置
	float Y;
	// 图像中实际机器人方向角
	float theta;
	// 上一帧图像实际机器人的X轴坐标
	float PreXd;
	// 上一帧图像实际机器人Y轴的坐标
	float PreYd;
	// 实际机器人的角速度
	float Wd;
	// 实际机器人的线速度
	float Vd;
	// 虚拟机器人的线速度
	float Vr;
	// 虚拟机器人的角速度
	float Wr;
	// 测量得到的机器人的线速度
	float V;
	// 测量得到的机器人的角速度   通过编码器
	float W;
	// cvWaitKey的等待时间
	int WaitTime;
	// 上一帧图像实际机器人期望的线速度
	float PreVd;
	// 上一帧图像实际机器人期望的角速度
	float PreWd;
	// 期望机器人的方向角
	float thetaR;
	// 参考机器人的中心坐标X
	float Xr;
	// 参考机器人的中心坐标Y
	float Yr;
	// 误差方程
	float e1;
	float e2;
	float e3;
	// 惯性坐标系下测量的值与期望的值的差
	float N1;
	float N2;
	// 力矩
	float T1;
	// 右轮力矩
	float T2;
	// 转动惯量
	float I;
	// 左轮速度
	float V1;
	// 右轮速度
	float V2;
	// 机器人轮子的半径
	float r;
	// 机器人两轮间的距离
	float R;
	afx_msg void OnBnClickedButtonopencamera();
	float m_Vr;
	float m_Wr;
	float m_X;
	float m_Xr;
	float m_Y;
	float m_Yr;
	float m_theta;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	// 测试程序变量
	int m;
	int md;
	int n;
	int nd;
	// 视频帧数
	int framecount;
	float m_thetaR;
	float m_T1;
	float m_T2;
	// 左轮弧长
	float S1;
	// 右轮弧长
	float S2;
	float m_V21;
	float m_V22;
	// 编码器中运行的时间
	float EncodeTime;
	// 内轮转过的圆心角
	float alfa1;
	// 外轮转过的圆心角
	float alfa2;
	// 左轮加速度
	float acc1;
	// 右轮加速度
	float acc2;
	float X1;
	float X2;
	float Y1;
	float px;
	float py;
	float m_e1;
	float m_e2;
	float m_e3;
	afx_msg void OnBnClickedBtnrc();
	CString m_EdtImg;
	CString m_EdtRe;
	CEdit m_Commands;
	CEdit m_EdtCMD;
	CString m_CstrIP;
	afx_msg void OnBnClickedBtnip();
	afx_msg LRESULT OnMyMessage(WPARAM wParam,LPARAM lParam);
	void DrawPicToHDC(IplImage *img, UINT ID);
	void DrawPicToHDC(Mat img, UINT ID);
	int m_iState;
	public:
		IMTDevice* m_pDevMotion;//运动虚拟设备
		IMTMotion* m_pMotion;

		IMTDevice* sonarDev;//声波虚拟设备
		IMTUltraSonic* m_pSonar;

		IMTDevice* m_PSDDev;//PSD虚拟设备
		IMTPSD* m_pPSD;

		IMTDevice* m_pDevEncoder;//编码器虚拟设备
		IMTEncoder* m_pEncoder;
		DeviceProc m_EncoderDisProc;

		imtposnav::RangeData range;
		imtposnav::IMTPosNav posandnav;
		float m_fDis[16] ;//存放声波测距返回值
		float PSD_m_fDis[16];//存放红外测距返回值
		float m_fEncoderDis[8];//存放编码器返回值
		int num;
		int m_bSonar;
		float m_fRobotSpeed;
		void* pGlobalDevLst;

	CString cstrClientIP;
	CString m_UltraSonic_B;
	CString m_UltraSonic_F;
	CString m_UltraSonic_FL;
	CString m_UltraSonic_FR;
	CString m_UltraSonic_L;
	CString m_UltraSonic_R;
	CString m_PSD_B;

		float fF;
		float fL;
		float fR;


		//声波返回值 是否有障碍物  有 为1   没有  为 0
		int PSD_FM;
		int PSD_FL1;
		int PSD_FL2;
		int PSD_FR1;
		int PSD_FR2;
		int PSD_BM;

		int UltraSonic_FM;
		int UltraSonic_FL1;
		int UltraSonic_FL2;
		int UltraSonic_FR1;
		int UltraSonic_FR2;
		int UltraSonic_BM;

public:
	CString m_PSD_F;
	CString m_PSD_FL;
	CString m_PSD_FR;
	CString m_PSD_L;
	CString m_PSD_R;
public:
	static void __stdcall RecvProc(void* pParam, float32* speed, UInt16 num);//超声波回调函数
	static void __stdcall PSD_RecvProc(void* pParam, float32* speed, UInt16 num);//红外回调函数
	static void _stdcall EncoderDisProcFun(void *pParam, float32* value, UInt16 num);//编码器回调函数
	static void _stdcall EncoderProcFun(void *pParam,float32* lvelocity, float32* rvelocity, float32* ldistance,float32* rdistance,float32 timer);
//    static void _stdcall EncoderProcFun(void *pParam,float32* lvelocity, float32* rvelocity, float32* ldistance,float32* rdistance,float32 timer);
	
	static void __stdcall PIDFunc(void* pParam, UInt8 LP, UInt8 LI,UInt8 LD,UInt8 RP,UInt8 RI,UInt8 RD);
	bool Turn_Angel(float angel);//转向角度
	void Move(float left, float right,float a);//使车运动的函数
	void Move(float lv,float rv);//使车运动的函数
   
	void on_odo();
};