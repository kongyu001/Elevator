#pragma once
#include"Elevator.h"

//���û���������ⲿ��Ӧ��ťʱ�ĺ�����
bool ClickElevatorOuterBtn(WORD wControlID);

//���û���������ڲ���ť��ʱ��
/*��¼����һ�����ݵ��ڲ���ť�б�������Ȼ����
������Ϣ���ν���������������Բ��ڴ�������*/
bool ClickElevatorInnerBtn(Elevator** lpMyElevator, WORD wControlID);

//���û����µ��ݵĿ����ż���ʱ�򣬿�ʼ���ڲ����ݵİ�ť״̬������
bool ClickElevatorDoorBtn(Elevator** lpMyElevator, WORD wControlID);

//���û����±�������ʱ��
bool ClickElevatorAlarmBtn(Elevator** lpMyElevator, WORD wControlID);

/*//��õ�ǰ���еĵ���������
//��������Elevator�ı�����
//�ú������ؿ��е��ݵ��������Լ���iStillElevatorBuff��������һ�����ݿ��С�iStillElevatorBuff��ΪNULLʱ��
//iStillElevatorBuffΪNULLʱ�����ؿ��е��ݵ�������
int GetStillElevators(Elevator* lpMyElevator, int* iStillElevatorBuff);*/

//  ���߳��еļ�ʱ��������
VOID CALLBACK MainThreadTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
class singleton
{
protected:
	singleton()
	{}
private:
	static singleton* p;
public:
	static singleton* initance();
	//�����ⲿ���󣬽������ⲿ����ת��Ϊ�����ڲ�����
	//��Elevator������ⲿ�����������ɨ�衣��������
	bool DispatchOuterRequtst(Elevator** lpMyElevator);


};

//���ⲿ�����͸��Լ�¥�����������ĵ��ݡ�
//����true��ʾ����ɹ����䡣
//iRequestFloor ���������¥�㣬iUpingCount��ǰ���е����������ĵ�������lpUpingElevators���Ǽ������ݡ�
bool SendToUnderFloorUping(Elevator** lpMyElevator, int iRequestFloor, int iUpingCount, int* lpUpingElevators);

//2.(1)���������еģ������е������Լ�����ֵ��С��(2)������ֹ�ģ������Լ��������ֵ��С��ȡ������ֵ��С���ǲ�����ִ������
bool SendToDowningOrStill(Elevator** lpMyElevator, int iRequestFloor, int iDowningCount, int* lpDowningElevators, int iStillCount, int* lpStillElevators);

//���ⲿ�����͸��Լ�¥�������½��ĵ��ݡ�
bool SendToAboveFloorDowning(Elevator** lpMyElevator, int iRequestFloor, int iDowningCount, int* lpDowningElevators);

//2.(1)���������еģ������ж������Լ�����ֵ��С��(2)�Ҿ�ֹ�ģ������Լ�����ֵ��С��ȡ�����о���ֵ��С���ǲ�����ִ������
bool SendToUpingOrStill(Elevator** lpMyElevator, int iRequestFloor, int iUpingCount, int* lpUpingElevators, int iStillCount, int* lpStillElevators);

//�����岿���ݵ�ȫ���̡߳�
bool StartAllElevators(Elevator** lpMyElevator, int iElevatorCount);