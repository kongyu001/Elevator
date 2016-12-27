#include"stdafx.h"
#include"ElevatorStateMsg.h"

Interator* ConcreteAggregate::CreateItrator()
{
	return new ConcreteInterator(this);
}
//��ʼ����������״̬����ֹ�ڵ�һ�㡣
//HWND �����ھ����iButtonListID�����ڰ�ťList��ID��iMansionFloorsCount�����ܲ�����
//���Ҹ���¥�����ָ�ButtonList�����õ���״̬����������lpElevator���Ӧ��

bool Elevatorstop::SetElevatorState(int iElevatorState)
{
	this->iElevatorState = iElevatorState;
	this->DisplayElevatorstop();
	return true;
}
int Elevatorstop::GetElevatorState()
{
	return this->iElevatorState;
}
bool Elevatorstop::SetCurFloor(int iCurFloor)
{
	this->iCurFloor = iCurFloor;
	this->DisplayElevatorstop();
	return true;
}
int Elevatorstop::GetCurFloor()
{
	return this->iCurFloor;
}
bool Elevatorup::DisplayElevatorup()
{
	TCHAR szElevatorMsgHint[50] = { NULL };
	if (this->iElevatorState == ELEVATOR_STATE_UPING)
	{
		wsprintf(szElevatorMsgHint, TEXT("%d ������"), this->iCurFloor);
	}
	if (this->iCurFloorEditID == NULL)
	{
		MessageBox(NULL, TEXT("ElevatorStateMsg::hCurFloorEditWndΪ�գ���\r\n�޷���ʾ�������飡��"),
			TEXT("������Ϣ"), MB_OK | MB_ICONERROR);
		return false;
	}
	//��ʾ��ϸ��Ϣ��
	SetDlgItemText(this->lpElevator->GetMainDlgWnd(), this->iCurFloorEditID, szElevatorMsgHint);
	return true;
}
bool Elevatordown::DisplayElevatordown()
{
	TCHAR szElevatorMsgHint[50] = { NULL };
	if (this->iElevatorState == ELEVATOR_STATE_DOWNING)
	{
		wsprintf(szElevatorMsgHint, TEXT("%d �½���"), this->iCurFloor);
	}
	if (this->iCurFloorEditID == NULL)
	{
		MessageBox(NULL, TEXT("ElevatorStateMsg::hCurFloorEditWndΪ�գ���\r\n�޷���ʾ�������飡��"),
			TEXT("������Ϣ"), MB_OK | MB_ICONERROR);
		return false;
	}
	//��ʾ��ϸ��Ϣ��
	SetDlgItemText(this->lpElevator->GetMainDlgWnd(), this->iCurFloorEditID, szElevatorMsgHint);
	return true;
}
bool Elevatorstop::DisplayElevatorstop()
{
	TCHAR szElevatorMsgHint[50] = { NULL };
	if (this->iElevatorState == ELEVATOR_STATE_DOWNING)
	{
		wsprintf(szElevatorMsgHint, TEXT("%d ����"), this->iCurFloor);
	}
	if (this->iCurFloorEditID == NULL)
	{
		MessageBox(NULL, TEXT("ElevatorStateMsg::hCurFloorEditWndΪ�գ���\r\n�޷���ʾ�������飡��"),
			TEXT("������Ϣ"), MB_OK | MB_ICONERROR);
		return false;
	}
	//��ʾ��ϸ��Ϣ��
	SetDlgItemText(this->lpElevator->GetMainDlgWnd(), this->iCurFloorEditID, szElevatorMsgHint);
	return true;
}
//�����ݵ��������¥�����ʾ��ʾ��Ϣ��
//��ʾ���ݵĵ�����Ϣ����DisplayElevatorMsg��һ����DisplayElevatorMsgֻ��������״̬��
bool ElevatorStateMsg::DisplayElevatorArriveMsg()
{
	TCHAR szArriveMsg[50] = { NULL };
	wsprintf(szArriveMsg, TEXT("���ݵ��� %d ��"), this->iCurFloor);
	SetDlgItemText(this->lpElevator->GetMainDlgWnd(), this->iCurFloorEditID, szArriveMsg);
	return true;
}
int Elevatorup::IncreaseCurFloor()
{
	//��ʾ��˳����������������е�����˳���йء�
	//����һ��ʱ�ȵ������ٽ�������һ�㡣
	//����ȵ�����ǰ����������ʾ��ʾ��Ϣ��
	if ((this->iCurFloor) < (this->iElevatorFloorsCount))
	{
		++(this->iCurFloor);
		this->DisplayElevatorup();
		return this->iCurFloor;
	}
	this->DisplayElevatorup();
	return this->iCurFloor;
}
int Elevatordown::DecreaseCurFloor()
{
	//��ʾ��˳����������������е�����˳���йء�
	//����һ��ʱ�ȵݼ����ٽ�������һ�㡣
	//����ȵ�����ǰ����������ʾ��ʾ��Ϣ��
	if ((this->iCurFloor)>1)
	{
		--(this->iCurFloor);
		this->DisplayElevatordown();
		return this->iCurFloor;
	}
	this->DisplayElevatordown();
	return this->iCurFloor;
}
/*
//���øõ��ݸ�¥���ڲ������״̬��Ҫ���л������У�����������
//iFloorIndex  ¥�����   iInnerRequestState¥��״̬��
int ElevatorStateMsg::SetlpiInnerRequestState(int iFloorIndex)
{   
	int iInnerRequestState = ELEVATOR_INNERREQUEST_NONE;
	return iInnerRequestState;
}

//��ø�¥�������״̬��
int ElevatorStateMsg::GetlpiInnerRequestState()
{
	return this->lpiInnerRequestState[this->iCurFloor];
}
//��¥���ڲ�����״̬��Ϊ��ʼֵ��
bool ElevatorStateMsg::InitlpiInnerRequestState()
{
	memset(this->lpiInnerRequestState, ELEVATOR_INNERREQUEST_NONE,
		(this->lpElevator->GetInnerRequirementFloorsCount() + 1)*sizeof(int));
	return true;
}
*/
ElevatorStateMsg::ElevatorStateMsg(HWND hwnd, int iInnerButtonListID, int iCurFloorEditID, int iElevatorFloorsCount, Elevator* lpElevator)
{
	//���õ���״̬����������lpElevator���Ӧ��
	this->lpElevator = lpElevator;
	//����¥������ ���� �������е�¥�㰴ť������
	this->iElevatorFloorsCount = iElevatorFloorsCount;

	//��ʼ����ؾ����
	this->hElevatorInnerBtnWnd = GetDlgItem(hwnd, iInnerButtonListID);
	this->iCurFloorEditID = iCurFloorEditID;

	//��ʼ������״̬����ֹ�ڵ�һ�㡣һ����this->iCurFloorEditID = iCurFloorEditID;֮��
	this->SetCurFloor(1);
	this->SetElevatorState(ELEVATOR_STATE_STILL);

	/*	//���ó�ʼ���ڲ������״̬��
	this->lpiInnerRequestState = (int*)malloc((lpElevator->GetInnerRequirementFloorsCount())*sizeof(int));
	memset(this->lpiInnerRequestState, ELEVATOR_INNERREQUEST_NONE, (lpElevator->GetInnerRequirementFloorsCount() + 1)*sizeof(int));*/

	//�ָ���顣
	RECT buttonListRect;
	GetClientRect(this->hElevatorInnerBtnWnd, &buttonListRect);
	int iButtonItemHeight = buttonListRect.bottom / (this->iElevatorFloorsCount);

	TCHAR szFloorButtonHint[20][20] = { TEXT("20"), TEXT("19"), TEXT("18"), TEXT("17"), TEXT("16"), TEXT("15"), TEXT("14"), TEXT("13"),
		TEXT("12"), TEXT("11"), TEXT("10"), TEXT("9"), TEXT("8"), TEXT("7"), TEXT("6"), TEXT("5"), TEXT("4"), TEXT("3"), TEXT("2"), TEXT("1") };
	Aggregate* ag = new ConcreteAggregate();
	Interator* it = new ConcreteInterator(ag);
	for (; !(it->IsDone()); it->Next())
	{

		SendMessage(this->hElevatorInnerBtnWnd, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)szFloorButtonHint[it->CurrentItem()]);
		//����ÿ����ť�ĸ߶ȡ�
		SendMessage(this->hElevatorInnerBtnWnd, LB_SETITEMHEIGHT, (WPARAM)it->CurrentItem(), (LPARAM)iButtonItemHeight);
	}
	//��ʼ״̬�µ��ݾ�ֹͣ���ڵ�һ�㡣
	SendMessage(this->lpElevator->GetElevatorWnd(), LB_SETCURSEL, (WPARAM)iElevatorFloorsCount - 1, (LPARAM)0);
}

//���õ��ݵ�����״̬��
bool ElevatorStateMsg::SetElevatorState(int iElevatorState)
{
	this->iElevatorState = iElevatorState;
	this->DisplayElevatorMsg();
	return true;
}
//��õ�ǰ���ݵ�����״̬��
int ElevatorStateMsg::GetElevatorState()
{
	return this->iElevatorState;
}
//���õ�ǰ�����˶����˵ڼ��㡣
bool ElevatorStateMsg::SetCurFloor(int iCurFloor)
{
	this->iCurFloor = iCurFloor;
	this->DisplayElevatorMsg();
	return true;
}
//��õ�ǰ�����˶����˵ڼ��㡣
int ElevatorStateMsg::GetCurFloor()
{
	return this->iCurFloor;
}
//��õ����ڲ���ť�б�ľ����
HWND ElevatorStateMsg::GetElevatorInnerBtnWnd()
{
	return this->hElevatorInnerBtnWnd;
}

//������ʾ����ʾ����Ϣ��
bool ElevatorStateMsg::DisplayElevatorMsg()
{
	TCHAR szElevatorMsgHint[50] = { NULL };
	if (this->iElevatorState == ELEVATOR_STATE_UPING)
	{
		wsprintf(szElevatorMsgHint, TEXT("%d ������"), this->iCurFloor);
	}
	else if (this->iElevatorState == ELEVATOR_STATE_DOWNING)
	{
		wsprintf(szElevatorMsgHint, TEXT("%d �½���"), this->iCurFloor);
	}
	else
	{
		wsprintf(szElevatorMsgHint, TEXT("%d ����"), this->iCurFloor);
	}
	if (this->iCurFloorEditID == NULL)
	{
		MessageBox(NULL, TEXT("ElevatorStateMsg::hCurFloorEditWndΪ�գ���\r\n�޷���ʾ�������飡��"),
			TEXT("������Ϣ"), MB_OK | MB_ICONERROR);
		return false;
	}
	//��ʾ��ϸ��Ϣ��
	SetDlgItemText(this->lpElevator->GetMainDlgWnd(), this->iCurFloorEditID, szElevatorMsgHint);
	return true;
}//������ǰ���ݵĲ��������ص�����Ĳ�����
int ElevatorStateMsg::IncreaseCurFloor()
{
	//��ʾ��˳����������������е�����˳���йء�
	//����һ��ʱ�ȵ������ٽ�������һ�㡣
	//����ȵ�����ǰ����������ʾ��ʾ��Ϣ��
	if ((this->iCurFloor) < (this->iElevatorFloorsCount))
	{
		++(this->iCurFloor);
		this->DisplayElevatorMsg();
		return this->iCurFloor;
	}
	this->DisplayElevatorMsg();
	return this->iCurFloor;
}
//�ݼ���ǰ���ݵĲ��������ص�����Ĳ�����
int ElevatorStateMsg::DecreaseCurFloor()
{
	//��ʾ��˳����������������е�����˳���йء�
	//����һ��ʱ�ȵݼ����ٽ�������һ�㡣
	//����ȵ�����ǰ����������ʾ��ʾ��Ϣ��
	if ((this->iCurFloor)>1)
	{
		--(this->iCurFloor);
		this->DisplayElevatorMsg();
		return this->iCurFloor;
	}
	this->DisplayElevatorMsg();
	return this->iCurFloor;
}