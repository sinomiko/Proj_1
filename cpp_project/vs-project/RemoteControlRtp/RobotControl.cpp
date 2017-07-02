#include "stdafx.h"

#include "MyMotion.h"
#include "MyMotionDlg.h"
//#include ".\mymotiondlg.h"


int k3 = 2;
int k4 = 2;
float h = 0;



void CMyMotionDlg::PreInfor(CvBox2D Pre_Rage2D,CvBox2D End_Rage2D)  //计算测量得到的速度，线速度
{
	//if((a-angle1)>=0.0)  sign=1;
	//if((a-angle1)<0.0)  sign=-1;
 //float angle1 = 30.0;  //angle1 的数值代表着奇数步的角度
 //float a0 = 2000;
 //int sign=1;   //   sign的数值只有+1和-1，代表着角度(a0-angle1),(a0-angle2)的符号
	//  W = (-1)*3*sign*sqrt(abs((int)(a0-angle1)));    //  电机转动的角速度,10为因子，可以更改，以改变转动的快慢
	//  V21= (-1)*w*r;         //  电机左轮转动的速度。电机速度与w有关系，即与a有关系，a越小，则速度也就越小
	//  V22= 1*w*r;            //  电机右轮转动的速度。电机速度与w有关系，即与a有关系，a越小，则速度也就越小	  
    PreXd = Pre_Rage2D.center.x;
	PreYd = Pre_Rage2D.center.y;
	float diffX = X - PreXd;
	float diffY = Y - PreYd;
	if(diffX == 0)
	{
		PreWd = 0;
	}
	else
	{
		PreWd = atan(diffY/diffX);
	}	
	PreVd = Vd;
	/*x = End_Rage2D.center.x;
	y = End_Rage2D.center.y;*/
	float diff = sqrt(pow(X - PreXd,2)+pow(Y - PreYd,2));
	V = diff*1000/WaitTime;	  //实际机器人的线速度
}
CvPoint DPoint[100000];
void CMyMotionDlg::targetRobot(IplImage* img,int i)
{
	int px = 277;
	int py = 178;
	//Vy = Vy*(-1);
	cvLine(img,cvPoint(0,py),cvPoint(714,py),cvScalar(0,0,0),2);
	cvLine(img,cvPoint(px,0),cvPoint(px,488),cvScalar(0,0,0),2);
	//cvCircle(img,cvPoint(px,py),20,cvScalar(0,0,0),2);
	thetaR = i * 0.5; // 角度
	Xr =  177 +110 - 110 * cos(thetaR);
	Yr =  178 + 110 * sin(thetaR);

	//DPoint[i] = cvPoint(Xr,Yr);	//实际的轨迹			
	//for(int j = 1 ;j<i;j++)
	//{			
	//	cvLine(img,DPoint[j-1],DPoint[j],CV_RGB(255,0,0),2,8,0); 	
	//}
	//cvCircle(img,cvPoint(Xr,Yr),10,cvScalar(0,0,255),2);
	//cvCircle(img,cvPoint(px,py),100,cvScalar(0,0,0),4,8,0);
	Vrx = (0.08)*cos(thetaR);
	Vry  =(0.08)*sin(thetaR);
	Vr = sqrt(pow(Vrx,2)+pow(Vry,2));
}

int sumX = 0;
int sumY = 0;
int sumXd = 0;
int sumYd = 0;
float L = 0;
float minX = 300.0;
float maxX = 377.0;
float minY = 50.0;
float maxY = 278.0;
float a = 0;
float minJiao1 = 5;
float ZJiao1 = 30;
//float px = 277;
//float py = 178;

void CMyMotionDlg::robotdrawline(IplImage* img,CvBox2D pre_Rage2D,CvBox2D End_Rage2D)
{
     float preX = pre_Rage2D.center.x; //上一帧图像中物体的位置
	 float preY = pre_Rage2D.center.y;
	 float nowX = End_Rage2D.center.x;// 当前图像中物体的位置
	 float nowY = End_Rage2D.center.y;
	 float xy = atan((nowY-178)/(nowX-277));
	 float distX = pow(X-277,2);
	 float distY = pow(Y-178,2);
	 float dis = sqrt(distX+distY);

	 float diffY = nowY-preY;
	 float diffX = nowX - preX;

	 
	 if(diffX == 0)
		 theta = 0;
	 else
	    theta = atan(diffY/diffX);  //计算出当前机器人的方向角
	    float jiaodu = theta*180/3.14;

		int i = jiaodu/30;
	/* if(jiaodu<=minJiao1&&jiaodu>=-minJiao1)
		 robotmove(0.2,0.2,0.1,0.2);*/
	 robotmove(0.2,0.2,0.13,0.2);
	// else
	 //{		 
		 if(dis>90)
			 robotmove(0.2,0.2,0.08,0.2);
		 else if(dis>100)
			 robotmove(0,0.2,0,0.2);
		 else
		 {
			 if(jiaodu>30*i+5)
				 robotmove(0.15,0.2,0.13,0.2);
			 else
				 if(jiaodu<30*i-5)
				  robotmove(0.13,0.2,0.15,0.2);	 
				 else
					robotmove(0.1,0.2,0.1,0.2);		
		 }		
		//	 /*   a+=theta;
		//	 if(a == 30)
		//	   robotmove(0.08,0.2,0.08,0.2);
		//	 else
		//	 {
		//	   robotmove(-0.1,0.2,0.1,0.2);
		//	 }
		//*/
		//float area = pow(X,2)+pow(Y,2);
	 //  if(area<=31400)
		//   robotmove(0.2,0.2,0.08,0.2);
	 //}

}

float PM1 = 0;
float PM2 = 0;
float caltheta = 0;
int cont = 0;
void CMyMotionDlg::RobotControl(int i)
{
	//robotmove(0.08,0.2,0.08,0.2);
	//计算角度（0-360）方向为逆时针


	
	if(cont/3==0)
	{		
		float diffx = X - X1;   //面积大的减去面积小的
		float diffy = Y - Y1;
		if(diffx == 0)
			caltheta =0;
		else   //实际机器人的角度变化范围为0-360度  实际机器人在图像中运行方向和实际的运行方向相反
		{
			caltheta = atan(diffy/diffx)*180/3.14;
			//	theta = caltheta;
			if(diffy<0 && diffx < 0)  //第一象限
				theta = caltheta;
			if(diffy > 0 && diffx < 0) //第二象限
				theta = 360 - abs(caltheta);
			if(diffy>0 && diffx > 0) //第三象限
				theta = 180 + caltheta;
			if(diffy<0&&diffx>0) //第四象限
				theta =180-abs(caltheta);
		}

		thetaR = cont * 0.5; // 角度
		thetaR = 30;
		Xr =  177 +110 - 110 * cos(thetaR);
		Yr =  178 + 110 * sin(thetaR);

		//调整机器人的角度
		if(theta<thetaR)
		{
			robotmove(0.08,0.2,0,0.2);  //调整角度
		}
		else
		{
			robotmove(0,0.2,0.08,0.2);
			cont++;
		}

	//	if(theta>thetaR)
	//	{
	//		cont++;
	//	    robotmove(0.08,0.2,0.08,0.2);    //向内侧转动
	//	}
	//	else   //调整机器人的角度
	//	{
	//	   robotmove(0.08,0.2,0,0.12);    //原地调整角度
	//	}

	//控制器的设计
	//运用算法计算实际机器人的线速度和角速度
		float c1;
		float c2;
		float c3;
		e1 = X - Xr;   //误差
		e2 = Y - Yr;
		e3 = theta - thetaR;

		if(e1>0)
		{		
			if(e3<0)
			{
				robotmove(0,0.2,0.08,0.2);
			}
			else
			{
				robotmove(0.08,0.2,0.15,0.2);
			   cont++;
			}
		}
		else
		{
			robotmove(0.08,0.2,0.08,0.2);
		}

		float H = -e1*cos(theta)-e2*sin(theta);	
		L = -k4*L+H;
		h = h + L * WaitTime/1000;    //离散化
		Vd = Vr+h/5333;    //求得实际机器人的线速度
	///*Wd = Vd/r; */

	//if(e3 == 0)
	//{
	//	c1 = 0;
	//	c2 = 0;
	//	c3 = 0;
	//}
	//else
	//{
	//   c1 = sin(e3/2);
	//   c2 = 2*Vr*e1*c1*sin(theta)/e3;
	//   c3 = 2*Vr*e2*c1*cos(theta)/e3;
	//}
	//
	//Wd = Wr - k3*e3 +c2  - c3; 

	////测量实际机器人的值与所期望实际机器人的值的误差
	//N1 = V - Vd;
	//N2 = W - Wd;    

	////线速度和角速度的更新率
	//float PVd1 = (Vd - PreVd)*1000/WaitTime;
	//float PWd1 = (Wd - PreWd)*1000/WaitTime;

	////估计值更新率
	//float Pba1 = -N1*PVd1;
	//float Pba2 = -N2*PWd1;

	////估计值	
	//PM1 = PM1 + Pba1;
	//PM2 = PM2 + Pba2;
	////PM2 += PM2;
	////PM2 += PM2;
	////计算力矩  （没有考虑Us1）
	//float Tao1 = PVd1 * PM1 - 20 * N1 - (e1 * cos(theta) + e2 * sin(theta));
	//float Tao2 = PWd1 * PM2 - 20 * N2 - e3;
	//T1 = 0.05*Tao1 + 0.05 * Tao2;
	//T2 = 0.05*Tao1 + 0.05 * Tao2;
	//
	////由力矩转换为速度 反馈给机器人
	//Wd = Wd+T2/I;      //机器人实际的转动角速度
	////V1 = (-1)* Wd* r;   //将角速度转换成线速度，左转为正
	//V2 = Wd*r;    //机器人实际的转动角速度
	//V = W* r;   //将角速度转换成线速度，左转为正  
	}
	else
	{
		robotmove(V1,0.2,V2,0.2);
    }
}

void CMyMotionDlg::robotcontrolorigion(int i)
{
	//robotmove(0.8,0.2,0.08,0.2);
	////计算角度（0-360）方向为逆时针
	//float diffx = X - X1;
	//float diffy = Y - Y1;
	//if(diffx == 0)
	//	caltheta =0;
	//else   //实际机器人的角度变化范围为0-360度  实际机器人在图像中运行方向和实际的运行方向相反
	//{
	//	caltheta = atan(diffy/diffx)*180/3.14;
	//	//	theta = caltheta;
	//	if(diffy<0 && diffx < 0)  //第一象限
	//		theta = caltheta;
	//	if(diffy > 0 && diffx < 0) //第二象限
	//		theta = 360 - abs(caltheta);
	//	if(diffy>0 && diffx > 0) //第三象限
	//		theta = 180 + caltheta;
	//	if(diffy<0&&diffx>0) //第四象限
	//		theta =180-abs(caltheta);
	//}

	////虚拟机器人的线速度和角速度
	//thetaR = cont*0.5;  //0.5指每一帧图像转动的方向角
	//Xr =  157 + 210 - 210 * cos(thetaR);
	//Yr =  244 + 210 * sin(thetaR);

	////	if(theta>thetaR)
	////	{
	////		cont++;
	////	    robotmove(0.08,0.2,0.08,0.2);    //向内侧转动
	////	}
	////	else   //调整机器人的角度
	////	{
	////	   robotmove(0.08,0.2,0,0.12);    //原地调整角度
	////	}

	////控制器的设计
	////运用算法计算实际机器人的线速度和角速度
	//float c1;
	//float c2;
	//float c3;
	//e1 = X - Xr;   //误差
	//e2 = Y - Yr;
	//e3 = theta - thetaR;
	//float H = -e1*cos(theta)-e2*sin(theta);	
	//L = -k4*L+H;
	//h = h + L * WaitTime/1000;    //离散化
	//Vd = Vr+h/5333;    //求得实际机器人的线速度
	/////*Wd = Vd/r; */

	////if(e3 == 0)
	////{
	////	c1 = 0;
	////	c2 = 0;
	////	c3 = 0;
	////}
	////else
	////{
	////   c1 = sin(e3/2);
	////   c2 = 2*Vr*e1*c1*sin(theta)/e3;
	////   c3 = 2*Vr*e2*c1*cos(theta)/e3;
	////}
	////
	////Wd = Wr - k3*e3 +c2  - c3; 

	//////测量实际机器人的值与所期望实际机器人的值的误差
	////N1 = V - Vd;
	////N2 = W - Wd;    

	//////线速度和角速度的更新率
	////float PVd1 = (Vd - PreVd)*1000/WaitTime;
	////float PWd1 = (Wd - PreWd)*1000/WaitTime;

	//////估计值更新率
	////float Pba1 = -N1*PVd1;
	////float Pba2 = -N2*PWd1;

	//////估计值	
	////PM1 = PM1 + Pba1;
	////PM2 = PM2 + Pba2;
	//////PM2 += PM2;
	//////PM2 += PM2;
	//////计算力矩  （没有考虑Us1）
	////float Tao1 = PVd1 * PM1 - 20 * N1 - (e1 * cos(theta) + e2 * sin(theta));
	////float Tao2 = PWd1 * PM2 - 20 * N2 - e3;
	////T1 = 0.05*Tao1 + 0.05 * Tao2;
	////T2 = 0.05*Tao1 + 0.05 * Tao2;
	////
	//////由力矩转换为速度 反馈给机器人
	////Wd = Wd+T2/I;      //机器人实际的转动角速度
	//////V1 = (-1)* Wd* r;   //将角速度转换成线速度，左转为正
	////V2 = Wd*r;    //机器人实际的转动角速度
	////V = W* r;   //将角速度转换成线速度，左转为正 
}