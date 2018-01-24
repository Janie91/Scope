#include <iostream>
#include "visa.h"
using namespace std;
ViSession vidp,vip;
long status=-1;
int main()
{
	float vRange=-1,vTemp=-1;
	viOpenDefaultRM(&vidp);
	status=viOpen(vidp,"TCPIP0::10.193.49.240::inst0::INSTR",VI_NULL,VI_NULL,&vip);
	if(status!=0)
	{
		cout<<"示波器连接不成功，请IP地址或本地连接再重新连接！"<<endl;
		viClose(vip);
		viClose(vidp);
		return 0;
	}
	else
	{
		viClear(vip);			
		viPrintf(vip,"*rst\n");
		viPrintf(vip,":autoscale\n");

		viPrintf(vip,":channel4:display on\n");//打开通道
		viPrintf(vip,":channel4:offset 0\n");

		viPrintf(vip,":timebase:reference left\n");
		viPrintf(vip,"timebase:range %f\n",0.02f);//设置时间轴代表的时间长度

		viPrintf(vip,":trigger:edge:source external\n");//外触发模式
		viPrintf(vip,":trigger:mode edge\n");//边沿触发
		viPrintf(vip,":trigger:sweep normal\n");//触发模式为标准
		viPrintf(vip,":trigger:edge:coupling dc\n");//耦合方式为DC
		viPrintf(vip,":trigger:edge:level 1\n");//触发电平为1V
		viPrintf(vip,":trigger:edge:slope positive\n");//上升沿

		viPrintf(vip, ":acquire:type hresolution\n");
		viPrintf(vip,":acquire:complete 100\n");

		viPrintf(vip,":measure:source channel4\n");
		viQueryf(vip,":channel4:range?\n","%f\n",&vRange);//获得纵向的电压范围
		viQueryf(vip,":measure:vpp?\n","%f\n",&vTemp);//测量峰峰值

		cout<<"垂直分辨率为："<<vRange/8*1000<<"mV"<<endl;
		cout<<"峰峰值为："<<vTemp*1000<<"mV"<<endl;
	}
	cin.get();
	viClose(vip);
	viClose(vidp);
	return 0;
}