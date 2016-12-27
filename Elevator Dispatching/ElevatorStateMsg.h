#pragma once 

#include<Windows.h>
#include<windowsx.h>
#include"resource.h"
#include"Elevator.h"

//������ݵ�ǰ����״̬�ĳ�����
#define ELEVATOR_STATE_UPING 0x1012
#define ELEVATOR_STATE_DOWNING 0x1013
#define ELEVATOR_STATE_STILL 0x1014
#define ELEVATOR_INNERREQUEST_NONE 0x1015
#define ELEVATOR_INNERREQUEST_UP 0x1016
#define ELEVATOR_INNERREQUEST_DOWN 0x1017

class Elevator;//�������໥�������ʱ����Ҫ������һ�¡�
class ElevatorStateMsg
{
public:
	//��ʼ����������״̬����ֹ�ڵ�һ�㡣
	//HWND �����ھ����iButtonListID�����ڰ�ťList��ID��iMansionFloorsCount�����ܲ�����
	//���Ҹ���¥�����ָ�ButtonList�����õ���״̬����������lpElevator���Ӧ��
	ElevatorStateMsg(HWND hwnd, int iButtonListID, int iCurFloorEditID, int iElevatorFloorsCount, Elevator* lpElevator);
	//���õ��ݵ�����״̬��
	bool SetElevatorState(int iElevatorState);
	//��õ�ǰ���ݵ�����״̬��
	int GetElevatorState();
	//���õ�ǰ�����˶����˵ڼ��㡣
	bool SetCurFloor(int iCurFloor);
	//��õ�ǰ�����˶����˵ڼ��㡣
	int GetCurFloor();
	//������ǰ���ݵĲ��������ص�����Ĳ�����
	int IncreaseCurFloor();
	//�ݼ���ǰ���ݵĲ��������ص�����Ĳ�����
	int DecreaseCurFloor();
	//��õ����ڲ���ť�б�ľ����
	HWND GetElevatorInnerBtnWnd();
	//�����ݵ��������¥�����ʾ��ʾ��Ϣ��
	bool DisplayElevatorArriveMsg();//��ʾ���ݵĵ�����Ϣ����DisplayElevatorMsg��һ����DisplayElevatorMsgֻ��������״̬��
	bool DisplayElevatorMsg();//��ʾ��ǰ���ݵ�����״̬��Ϣ��

/*	//���øõ��ݸ�¥���ڲ������״̬��Ҫ���л������У�����������
	//iFloorIndex  ¥�����  ¥���״̬���ڲ�������
	int SetlpiInnerRequestState(int iFloorIndex);
	//��ø�¥�������״̬��
	int GetlpiInnerRequestState();
	//��¥���ڲ�����״̬��Ϊ��ʼֵ��
	bool InitlpiInnerRequestState();*/
	
private:
	int iElevatorState;//�õ��ݴ�ʱ������״̬��
//	int* lpiInnerRequestState;//21��Ԫ��
	int iCurFloor;//��¼��ǰ������������һ�㡣
	int iElevatorFloorsCount;//�õ���һ��֧�ֶ��ٲ�¥��
	HWND hElevatorInnerBtnWnd;//�õ����ڶ�Ӧ��ButtonList�ľ����
	int iCurFloorEditID;//ʵʱ��ʾ��ǰ����ͣ���ڵڼ����Edit�ؼ�ID��
	class Elevator* lpElevator;//��¼�õ���״̬������һ�����ݡ�
};