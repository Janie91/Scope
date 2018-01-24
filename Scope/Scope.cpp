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
		cout<<"ʾ�������Ӳ��ɹ�����IP��ַ�򱾵��������������ӣ�"<<endl;
		viClose(vip);
		viClose(vidp);
		return 0;
	}
	else
	{
		viClear(vip);			
		viPrintf(vip,"*rst\n");
		viPrintf(vip,":autoscale\n");

		viPrintf(vip,":channel4:display on\n");//��ͨ��
		viPrintf(vip,":channel4:offset 0\n");

		viPrintf(vip,":timebase:reference left\n");
		viPrintf(vip,"timebase:range %f\n",0.02f);//����ʱ��������ʱ�䳤��

		viPrintf(vip,":trigger:edge:source external\n");//�ⴥ��ģʽ
		viPrintf(vip,":trigger:mode edge\n");//���ش���
		viPrintf(vip,":trigger:sweep normal\n");//����ģʽΪ��׼
		viPrintf(vip,":trigger:edge:coupling dc\n");//��Ϸ�ʽΪDC
		viPrintf(vip,":trigger:edge:level 1\n");//������ƽΪ1V
		viPrintf(vip,":trigger:edge:slope positive\n");//������

		viPrintf(vip, ":acquire:type hresolution\n");
		viPrintf(vip,":acquire:complete 100\n");

		viPrintf(vip,":measure:source channel4\n");
		viQueryf(vip,":channel4:range?\n","%f\n",&vRange);//�������ĵ�ѹ��Χ
		viQueryf(vip,":measure:vpp?\n","%f\n",&vTemp);//�������ֵ

		cout<<"��ֱ�ֱ���Ϊ��"<<vRange/8*1000<<"mV"<<endl;
		cout<<"���ֵΪ��"<<vTemp*1000<<"mV"<<endl;
	}
	cin.get();
	viClose(vip);
	viClose(vidp);
	return 0;
}