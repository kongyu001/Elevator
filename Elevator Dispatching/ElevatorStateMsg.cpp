#include"stdafx.h"
#include"ElevatorStateMsg.h"

Interator* ConcreteAggregate::CreateItrator()
{
	return new ConcreteInterator(this);
}
//初始化电梯运行状态，静止在第一层。
//HWND 父窗口句柄，iButtonListID电梯内按钮List的ID，iMansionFloorsCount大厦总层数。
//并且根据楼层数分割ButtonList。将该电梯状态与其所属的lpElevator相对应。

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
		wsprintf(szElevatorMsgHint, TEXT("%d 上升中"), this->iCurFloor);
	}
	if (this->iCurFloorEditID == NULL)
	{
		MessageBox(NULL, TEXT("ElevatorStateMsg::hCurFloorEditWnd为空！！\r\n无法显示电梯详情！！"),
			TEXT("错误消息"), MB_OK | MB_ICONERROR);
		return false;
	}
	//显示详细信息。
	SetDlgItemText(this->lpElevator->GetMainDlgWnd(), this->iCurFloorEditID, szElevatorMsgHint);
	return true;
}
bool Elevatordown::DisplayElevatordown()
{
	TCHAR szElevatorMsgHint[50] = { NULL };
	if (this->iElevatorState == ELEVATOR_STATE_DOWNING)
	{
		wsprintf(szElevatorMsgHint, TEXT("%d 下降中"), this->iCurFloor);
	}
	if (this->iCurFloorEditID == NULL)
	{
		MessageBox(NULL, TEXT("ElevatorStateMsg::hCurFloorEditWnd为空！！\r\n无法显示电梯详情！！"),
			TEXT("错误消息"), MB_OK | MB_ICONERROR);
		return false;
	}
	//显示详细信息。
	SetDlgItemText(this->lpElevator->GetMainDlgWnd(), this->iCurFloorEditID, szElevatorMsgHint);
	return true;
}
bool Elevatorstop::DisplayElevatorstop()
{
	TCHAR szElevatorMsgHint[50] = { NULL };
	if (this->iElevatorState == ELEVATOR_STATE_DOWNING)
	{
		wsprintf(szElevatorMsgHint, TEXT("%d 空闲"), this->iCurFloor);
	}
	if (this->iCurFloorEditID == NULL)
	{
		MessageBox(NULL, TEXT("ElevatorStateMsg::hCurFloorEditWnd为空！！\r\n无法显示电梯详情！！"),
			TEXT("错误消息"), MB_OK | MB_ICONERROR);
		return false;
	}
	//显示详细信息。
	SetDlgItemText(this->lpElevator->GetMainDlgWnd(), this->iCurFloorEditID, szElevatorMsgHint);
	return true;
}
//当电梯到达需求的楼层后，显示提示信息。
//显示电梯的到达信息，跟DisplayElevatorMsg不一样，DisplayElevatorMsg只包含三个状态。
bool ElevatorStateMsg::DisplayElevatorArriveMsg()
{
	TCHAR szArriveMsg[50] = { NULL };
	wsprintf(szArriveMsg, TEXT("电梯到达 %d 层"), this->iCurFloor);
	SetDlgItemText(this->lpElevator->GetMainDlgWnd(), this->iCurFloorEditID, szArriveMsg);
	return true;
}
int Elevatorup::IncreaseCurFloor()
{
	//显示的顺序跟调动电梯上下行递增的顺序有关。
	//在这一层时先递增，再将电梯上一层。
	//因此先递增当前层数，再显示提示信息。
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
	//显示的顺序跟调动电梯上下行递增的顺序有关。
	//在这一层时先递减，再将电梯下一层。
	//因此先递增当前层数，再显示提示信息。
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
//设置该电梯该楼层内部需求的状态，要上行还是下行，还是无需求。
//iFloorIndex  楼层序号   iInnerRequestState楼层状态。
int ElevatorStateMsg::SetlpiInnerRequestState(int iFloorIndex)
{   
	int iInnerRequestState = ELEVATOR_INNERREQUEST_NONE;
	return iInnerRequestState;
}

//获得该楼层需求的状态。
int ElevatorStateMsg::GetlpiInnerRequestState()
{
	return this->lpiInnerRequestState[this->iCurFloor];
}
//将楼层内部需求状态设为初始值。
bool ElevatorStateMsg::InitlpiInnerRequestState()
{
	memset(this->lpiInnerRequestState, ELEVATOR_INNERREQUEST_NONE,
		(this->lpElevator->GetInnerRequirementFloorsCount() + 1)*sizeof(int));
	return true;
}
*/
ElevatorStateMsg::ElevatorStateMsg(HWND hwnd, int iInnerButtonListID, int iCurFloorEditID, int iElevatorFloorsCount, Elevator* lpElevator)
{
	//将该电梯状态与其所属的lpElevator相对应。
	this->lpElevator = lpElevator;
	//根据楼层数量 决定 电梯内有的楼层按钮数量。
	this->iElevatorFloorsCount = iElevatorFloorsCount;

	//初始化相关句柄。
	this->hElevatorInnerBtnWnd = GetDlgItem(hwnd, iInnerButtonListID);
	this->iCurFloorEditID = iCurFloorEditID;

	//初始化电梯状态。静止在第一层。一定在this->iCurFloorEditID = iCurFloorEditID;之后。
	this->SetCurFloor(1);
	this->SetElevatorState(ELEVATOR_STATE_STILL);

	/*	//设置初始化内部需求的状态。
	this->lpiInnerRequestState = (int*)malloc((lpElevator->GetInnerRequirementFloorsCount())*sizeof(int));
	memset(this->lpiInnerRequestState, ELEVATOR_INNERREQUEST_NONE, (lpElevator->GetInnerRequirementFloorsCount() + 1)*sizeof(int));*/

	//分割按键块。
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
		//设置每个按钮的高度。
		SendMessage(this->hElevatorInnerBtnWnd, LB_SETITEMHEIGHT, (WPARAM)it->CurrentItem(), (LPARAM)iButtonItemHeight);
	}
	//初始状态下电梯静止停靠在第一层。
	SendMessage(this->lpElevator->GetElevatorWnd(), LB_SETCURSEL, (WPARAM)iElevatorFloorsCount - 1, (LPARAM)0);
}

//设置电梯的运行状态。
bool ElevatorStateMsg::SetElevatorState(int iElevatorState)
{
	this->iElevatorState = iElevatorState;
	this->DisplayElevatorMsg();
	return true;
}
//获得当前电梯的运行状态。
int ElevatorStateMsg::GetElevatorState()
{
	return this->iElevatorState;
}
//设置当前电梯运动到了第几层。
bool ElevatorStateMsg::SetCurFloor(int iCurFloor)
{
	this->iCurFloor = iCurFloor;
	this->DisplayElevatorMsg();
	return true;
}
//获得当前电梯运动到了第几层。
int ElevatorStateMsg::GetCurFloor()
{
	return this->iCurFloor;
}
//获得电梯内部按钮列表的句柄。
HWND ElevatorStateMsg::GetElevatorInnerBtnWnd()
{
	return this->hElevatorInnerBtnWnd;
}

//电梯显示屏显示的信息。
bool ElevatorStateMsg::DisplayElevatorMsg()
{
	TCHAR szElevatorMsgHint[50] = { NULL };
	if (this->iElevatorState == ELEVATOR_STATE_UPING)
	{
		wsprintf(szElevatorMsgHint, TEXT("%d 上升中"), this->iCurFloor);
	}
	else if (this->iElevatorState == ELEVATOR_STATE_DOWNING)
	{
		wsprintf(szElevatorMsgHint, TEXT("%d 下降中"), this->iCurFloor);
	}
	else
	{
		wsprintf(szElevatorMsgHint, TEXT("%d 空闲"), this->iCurFloor);
	}
	if (this->iCurFloorEditID == NULL)
	{
		MessageBox(NULL, TEXT("ElevatorStateMsg::hCurFloorEditWnd为空！！\r\n无法显示电梯详情！！"),
			TEXT("错误消息"), MB_OK | MB_ICONERROR);
		return false;
	}
	//显示详细信息。
	SetDlgItemText(this->lpElevator->GetMainDlgWnd(), this->iCurFloorEditID, szElevatorMsgHint);
	return true;
}//递增当前电梯的层数。返回递增后的层数。
int ElevatorStateMsg::IncreaseCurFloor()
{
	//显示的顺序跟调动电梯上下行递增的顺序有关。
	//在这一层时先递增，再将电梯上一层。
	//因此先递增当前层数，再显示提示信息。
	if ((this->iCurFloor) < (this->iElevatorFloorsCount))
	{
		++(this->iCurFloor);
		this->DisplayElevatorMsg();
		return this->iCurFloor;
	}
	this->DisplayElevatorMsg();
	return this->iCurFloor;
}
//递减当前电梯的层数。返回递增后的层数。
int ElevatorStateMsg::DecreaseCurFloor()
{
	//显示的顺序跟调动电梯上下行递增的顺序有关。
	//在这一层时先递减，再将电梯下一层。
	//因此先递增当前层数，再显示提示信息。
	if ((this->iCurFloor)>1)
	{
		--(this->iCurFloor);
		this->DisplayElevatorMsg();
		return this->iCurFloor;
	}
	this->DisplayElevatorMsg();
	return this->iCurFloor;
}