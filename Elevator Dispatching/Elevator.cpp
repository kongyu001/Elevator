#include"stdafx.h"
#include"Elevator.h"


extern  Elevator* lpMyElevator[5];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////非静态成员///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//在此构造函数中，将电梯与它对应的ListView绑定。并且初始化电梯状态，以及楼层状态。
//hwnd 父窗口句柄，iFloorListID电梯对应的ListView的ID，iMansionFloorsCount电梯一共支持多少层楼。
Elevator::Elevator(HWND hwnd, int iFloorListID, int iInnerButtonListID, int iCurFloorEditID, int iAlarmControlID, int iOpenDoorID, 
	int iElevatorFloorsCount, int iTimerID)
{
	//获得大厦层数。
	this->iElevatorFloorsCount = iElevatorFloorsCount;
	//记录线程该电梯对应的定时器ID。
	this->iElevatorTimerID = iTimerID;
	this->iElevatorArrivalTimerId = iTimerID + 10;//电梯到站后的设置电梯暂停的计时器为电梯的计时器加10。
	//电梯初始的报警状态。非报警状态。
	this->SetElevatorAlarmState(false);
//	this->ElevatorArriveEventHandle = NULL;
	//获得楼层List的句柄。这句一定要在实例化lpElevatorStateMsg之前，因为在其的构造函数中将用到。
	this->hElevatorWnd = GetDlgItem(hwnd, iFloorListID);
	//获得报警键的HWND。
	this->hAlarmControlWnd = GetDlgItem(hwnd, iAlarmControlID);
	//获得开门键的HWND。
	this->hOpenDoorWnd = GetDlgItem(hwnd, iOpenDoorID);
	//初始化内部需求的最高最低楼层。初始化都在第一层。
	this->iMaxInnerRequirementFloor = 1;
	this->iMinInnerRequirementFloor = 1;
	//初始化电梯状态。
	this->iInnerRequirementFloorsCount = 0;//没有任何用户需求。
	this->lpbInnerRequirementFloors = (bool*)malloc((this->iElevatorFloorsCount + 1) * sizeof(bool));
	memset(this->lpbInnerRequirementFloors, 0, (this->iElevatorFloorsCount + 1) * sizeof(bool));
	//初始化时电梯内按钮未被按下。
	this->bElevatorInnerBtnClick = false;
	//划分该电梯的List楼层。
	RECT mansionRect;
	GetClientRect(this->hElevatorWnd, &mansionRect);
	int iMansionHeight = mansionRect.bottom;
	//获得每层楼的高度。
	int iFloorHeight = iMansionHeight / (this->iElevatorFloorsCount);
	TCHAR szFloorHint[20][20] = { TEXT("第20层"), TEXT("第19层"), TEXT("第18层"), TEXT("第17层"), TEXT("第16层"), TEXT("第15层"),
		TEXT("第14层"), TEXT("第13层"), TEXT("第12层"), TEXT("第11层"), TEXT("第10层"), TEXT("第9层"), TEXT("第8层"), TEXT("第7层"),
		TEXT("第6层"), TEXT("第5层"), TEXT("第4层"), TEXT("第3层"), TEXT("第2层"), TEXT("第1层") };//这里没有写成动态的，今后再改。
	for (int index = 0; index < (this->iElevatorFloorsCount); index++)
	{
		SendMessage(this->hElevatorWnd, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)szFloorHint[index]);
		//设置当前楼层的高度。
		/*Sets the height, in pixels, of items in a list box. If the list box has the LBS_OWNERDRAWVARIABLE style, 
		this message sets the height of the item specified by the wParam parameter. Otherwise, 
		this message sets the height of all items in the list box. */
		SendMessage(this->hElevatorWnd, LB_SETITEMHEIGHT, (WPARAM)index, (LPARAM)iFloorHeight);
	}
	//构建内部类。该类中有电梯当前停靠层数以及电梯运行状态的信息。
	lpElevatorStateMsg = new ElevatorStateMsg(hwnd, iInnerButtonListID, iCurFloorEditID, (this->iElevatorFloorsCount), this);
	//初始化完成之后，开辟暂停的新线程。
	/*The thread is created in a suspended state, and does not run until the ResumeThread function is called.*/
	this->ElevatorThreadHandle = (HANDLE)_beginthreadex(NULL, 0, ElevatorThreadFunc, &(this->iElevatorTimerID), CREATE_SUSPENDED, NULL);
	//电梯线程呈非工作状态。
	this->SetElevatorThreadWork(false);//按下关门按钮的时候启动线程。
}

//析构函数，释放lpRequirementFloors。
Elevator::~Elevator()
{
	free((void*)(this->lpbInnerRequirementFloors));
	delete (this->lpElevatorStateMsg);//电梯运行状态。
}

//获得表示楼层的ListView的句柄。
HWND Elevator::GetElevatorWnd()
{
	return this->hElevatorWnd;
}

//设置电梯的运行状态。
bool Elevator::SetElevatorState(int iElevatorState)
{
	this->lpElevatorStateMsg->SetElevatorState(iElevatorState);
	return true;
}

//获得当前电梯的运行状态。
int Elevator::GetElevatorState()
{
	return this->lpElevatorStateMsg->GetElevatorState();
}

//设置当前电梯运动到了第几层。
bool Elevator::SetCurFloor(int iCurFloor)
{
	this->lpElevatorStateMsg->SetCurFloor(iCurFloor);
	return true;
}
//获得当前电梯运动到了第几层。
int Elevator::GetCurFloor()
{
	return this->lpElevatorStateMsg->GetCurFloor();
}

//将ListView的下标转化为正常的楼梯层数。
//放回正常的楼层数，楼层从1开始。传入ListView的正常index。
int Elevator::TransLVindexToFloor(int iLVindex)
{
	return (this->iElevatorFloorsCount) - iLVindex;//放回正常的楼层数，从一开始。
}

//返回正常的ListView下标，下标从零开始，传入的为正常楼层下标。
int Elevator::TransFloorToLVindex(int iFloorIndex)
{
	return (this->iElevatorFloorsCount) - iFloorIndex;
}

//设置电梯内按钮有没有被按下并未被处理，有即为true。
//若按钮按下的信息已被处理那么向其中传入false。
bool Elevator::SetElevatorInnerBtnClick(bool bElevatorInnerBtnClick)
{
	this->bElevatorInnerBtnClick = bElevatorInnerBtnClick;
	return true;
}

//返回获得电梯内按钮是否被按下的状态。
bool Elevator::GetElevatorInnerBtnClick()
{
	return this->bElevatorInnerBtnClick;
}

//刷新电梯的内部需求，即更新lpInnerRequirementFloors，iInnerRequirementFloorsCount这两个变量。
//当外部需求填入后，外部需求变成内部需求，此时也需要刷新内部需求。
bool Elevator::RefreshInsideRequest()//这个函数十分重要。
{
	if (this->GetElevatorAlarmState())
	{
		return false;//电梯处于报警状态 那么不要更新。
	}
	if (this->GetElevatorInnerBtnClick())//需要更新的情况下才做一下操作。
	{
		//获得当前被选择按钮的总数。
		int iInnerSelFloorCount = SendMessage(this->lpElevatorStateMsg->GetElevatorInnerBtnWnd(),
			LB_GETSELCOUNT, (WPARAM)0, (LPARAM)0);
		int* lpInnerSelFloors = (int*)malloc((iInnerSelFloorCount + 1)*sizeof(int));//记录下已经选择的楼层。
		SendMessage(this->lpElevatorStateMsg->GetElevatorInnerBtnWnd(),
			LB_GETSELITEMS, (WPARAM)(iInnerSelFloorCount + 1), (LPARAM)lpInnerSelFloors);//这是在LV中的顺序，跟楼层的顺序刚好相反。
		//接下来开始更新数据。
		//若当前内部需求是0，那么直接将新的内部需求填入。实际上就是填入bool的数组，在数组相应的楼层位置置true或false。
/*			for (int index = iInnerSelFloorCount; index >= 0; -- index)
			{/*index--    --index并无区别*/
/*				this->lpInnerRequirementFloors[iInnerSelFloorCount - index] =
					(this->TransLVindexToFloor(lpInnerSelFloors[index - 1]));
			}*/
		//先把原来的内部需求记录数组清空。
		memset(this->lpbInnerRequirementFloors, 0, ((this->iElevatorFloorsCount) + 1)*sizeof(bool));
		for (int index = 0; index < iInnerSelFloorCount; index++)
		{
			//bool 数组的一个元素代表一个楼层。有需求的话将该楼层置为true。
			this->lpbInnerRequirementFloors[this->TransLVindexToFloor(lpInnerSelFloors[index])] = true;//表示该层有需求。
		}
		//改变内部需求总量。变成此时内部需求总量。
		this->iInnerRequirementFloorsCount = iInnerSelFloorCount;
		if (iInnerSelFloorCount == 0)
		{
			this->SetMaxInnerRequirementFloor(this->GetCurFloor());
			this->SetMinInnerRequirementFloor(this->GetCurFloor());
			this->SetElevatorInnerBtnClick(false);
			this->SetElevatorState(ELEVATOR_STATE_STILL);//将电梯的状态置为停止。
			free(lpInnerSelFloors);
			return true;
		}
		//更新内部需求此时所需到达的最高最低的层数。
		this->SetMaxInnerRequirementFloor(this->TransLVindexToFloor(lpInnerSelFloors[0]));
		this->SetMinInnerRequirementFloor(this->TransLVindexToFloor(lpInnerSelFloors[iInnerSelFloorCount - 1]));
		//表示已记录此时电梯的内部需求。
		this->SetElevatorInnerBtnClick(false);
		//释放空间。
		free(lpInnerSelFloors);
	}
	return true;
}


//设置此时内部需求中需到达的最高楼层。
bool Elevator::SetMaxInnerRequirementFloor(int iMaxInnerRequirementFloor)
{
	this->iMaxInnerRequirementFloor = iMaxInnerRequirementFloor;
	return true;
}

//获得此时内部需求中需到达的最高楼层。
int Elevator::GetMaxInnerRequirementFloor()
{
	return this->iMaxInnerRequirementFloor;
}

//设置此时内部需求中需到达的最低的楼层。
bool Elevator::SetMinInnerRequirementFloor(int iMinInnerRequirementFloor)
{
	this->iMinInnerRequirementFloor = iMinInnerRequirementFloor;
	return true;
}

//获得此时内部需求中需到达的最低的楼层。
int Elevator::GetMinInnerRequirementFloor()
{
	return this->iMinInnerRequirementFloor;
}

//获得类中ElevatorStateMsg类的指针。
class ElevatorStateMsg* Elevator::GetElevatorStateMsg()
{
	return this->lpElevatorStateMsg;
}

//获得电梯中内部需求的总量。
int Elevator::GetInnerRequirementFloorsCount()
{
	return this->iInnerRequirementFloorsCount;
}

//获得内部需求量的数组。
bool* Elevator::GetlpbInnerRequirementFloors()
{
	return this->lpbInnerRequirementFloors;
}


//递增内部需求的总量，返回递增后的值。
int Elevator::IncreaseInnerRequirementFloorsCount()
{
	return (++(this->iInnerRequirementFloorsCount));
}

//递减内部需求总量，返回递减后的值。
int Elevator::DecreaseInnerRequirementFloorsCount()
{
	return (--(this->iInnerRequirementFloorsCount));
}

//接受外部需求将其转化为内部需求，传入的参数为楼层数。不分外部的上行或则下行需求。
//iElevatorState 接受的是外部上行还是下行需求。
bool Elevator::ReceiveOuterRequest(int iFloorIndex, int iElevatorState)//非常重要。
{
	//但是如果电梯处于报警状态，那么这次任务分配无效。
	if (this->GetElevatorAlarmState())
	{
		return false;
	}
	//电梯处于非报警状态时。
	//总之上行或者下行需求少一。
	if (iElevatorState == ELEVATOR_STATE_UPING)
	{
		Elevator::SetOuterRequestUp(iFloorIndex, false);
	}
	if (iElevatorState == ELEVATOR_STATE_DOWNING)
	{
		Elevator::SetOuterRequestDown(iFloorIndex, false);
	}
	//将外部需求转化为该电梯的内部需求。
	if ((this->lpbInnerRequirementFloors)[iFloorIndex] == true)//如果内部需求中已有该楼层，那么直接返回。
	{
		return true;
	}
	this->IncreaseInnerRequirementFloorsCount();//递增内部需求的总量。
	//将值赋入对应的内部需求数组。
	(this->lpbInnerRequirementFloors)[iFloorIndex] = true;//写入需求。
	//同时检测当前刚转化的需求与原来最高、最低内部需求的关系。
	if (iFloorIndex > (this->iMaxInnerRequirementFloor))
	{
		this->iMaxInnerRequirementFloor = iFloorIndex;
	}
	else if (iFloorIndex < (this->iMinInnerRequirementFloor))
	{
		this->iMinInnerRequirementFloor = iFloorIndex;
	}
	//相当于在电梯的内部按下内部需求按钮。
	this->SetElevatorInnerBtnClick(true);//说明有新的内部需求没有被刷新到电梯的内部需求队列中。
	//点亮内部需求按钮。
	SendMessage(this->lpElevatorStateMsg->GetElevatorInnerBtnWnd(), LB_SETSEL,
		(WPARAM)TRUE, (LPARAM)(this->TransFloorToLVindex(iFloorIndex)));
	//如果电梯计时器未开启，那么开启电梯的计时器。
	if (!(this->bElevatorThreadWork))
	{
		this->ResumeElevatorThread();
	}
	return true;
}

//获得线程的句柄。
HANDLE Elevator::GetElevatorThreadHandle()
{
	return this->ElevatorThreadHandle;
}

//标记电梯当前运动到了第几层。
bool Elevator::MarkCurFloor()
{
	SendMessage(this->hElevatorWnd, LB_SETCURSEL, 
		(WPARAM)(this->TransFloorToLVindex( this->lpElevatorStateMsg->GetCurFloor()) ), (LPARAM)0);//注意真实楼层与电梯下标之间的转化。
	return true;
}

//标记电梯当前运动到了第几层。
bool Elevator::MarkCurFloor(int iCurFloor)
{
	SendMessage(this->hElevatorWnd, LB_SETCURSEL, (WPARAM)(this->TransFloorToLVindex(iCurFloor)), (LPARAM)0);
	return true;
}

//重新启动电梯。
//这里开启线程后有反应。
DWORD Elevator::ResumeElevatorThread()
{
	if (!(this->GetElevatorAlarmState()))
	{
		this->SetElevatorThreadWork(true);//将电梯设置为工作状态。
		SetTimer(Elevator::GetMainDlgWnd(), this->iElevatorTimerID, 1000, ElevatorTimerProc);
	}
	//设置门的状态，因为是关门之后调用此函数。
	this->SetElevatorDoorState(false);
	return ResumeThread(this->ElevatorThreadHandle);
}

//设置电梯的报警状态。
bool Elevator::SetElevatorAlarmState(bool bIsAlarm)
{
	if (this->lpElevatorStateMsg)
	{
		//解除或则开启报警状态，电梯的内部需求都将被清空。
		SendMessage(this->lpElevatorStateMsg->GetElevatorInnerBtnWnd(), LB_SETSEL,
			(WPARAM)FALSE, (LPARAM)-1);
	}
//这一句在这里无效，因为程序在初始化的时候会有初始化报警Btn的消息，此时Elevator类还未完成初始化，
//比如楼层的ListView句柄此时未初始化，表示当前楼层和状态的类没有初始化，但是又要对他们进行访问，因此程序崩溃。。
//	this->MarkCurFloor();//由于其由ClearElevator调用会停止计时器，有可能出现显示屏跟电梯楼层来不及更新而不相符的情况，所以这里Mark一下。
	if (bIsAlarm)
	{
		this->MarkCurFloor();//由于其由ClearElevator调用会停止计时器，有可能出现显示屏跟电梯楼层来不及更新而不相符的情况，所以这里Mark一下。
		//设置报警键的文字。
		TCHAR szAlarmMsg[10] =TEXT("☎");
		Button_SetText(this->hAlarmControlWnd, szAlarmMsg);
		return ((this->bIsAlarm) = bIsAlarm);
	}
	TCHAR szAlarmMsg[10] = TEXT("☏");
	Button_SetText(this->hAlarmControlWnd, szAlarmMsg);
	(this->bIsAlarm) = bIsAlarm;
	//解除报警状态后，开启定时器。
	SetTimer(Elevator::GetMainDlgWnd(), this->iElevatorTimerID, 1000, ElevatorTimerProc);
	return (this->bIsAlarm);
}
//得到电梯的报警状态。
bool Elevator::GetElevatorAlarmState()
{
	return this->bIsAlarm;
}

//清除电梯的全部内部需求，并且关闭电梯的即使器。
bool Elevator::ClearElevator()
{
	//清空电梯的内部需求。
	this->iInnerRequirementFloorsCount = 0;
	this->iMaxInnerRequirementFloor = this->lpElevatorStateMsg->GetCurFloor();
	this->iMinInnerRequirementFloor = this->lpElevatorStateMsg->GetCurFloor();
	//取消电梯内部按钮的高亮。
	for (int iFloorIndex = 0; iFloorIndex < (this->iMansionFloorsCount + 1); iFloorIndex++)
	{
		if ((this->lpbInnerRequirementFloors)[iFloorIndex])
		{
			//取消高亮。
			SendMessage(this->lpElevatorStateMsg->GetElevatorInnerBtnWnd(), LB_SETSEL, 
				(WPARAM)FALSE, (LPARAM)(this->TransFloorToLVindex(iFloorIndex)));
		}
	}
	memset(this->lpbInnerRequirementFloors, 0, (this->iMansionFloorsCount + 1));
	//设置电梯处于报警状态。
	this->SetElevatorAlarmState(true);//之后电梯将不会接受外部或者内部的需求。
	this->SetElevatorState(ELEVATOR_STATE_STILL);//电梯静止态。
	this->lpElevatorStateMsg->DisplayElevatorMsg();
//	this->SetElevatorInnerBtnClick(false);
	KillTimer(Elevator::GetMainDlgWnd(), this->iElevatorTimerID);
	return true;
}

//暂停电梯的进程。
//暂停线程无效。
DWORD Elevator::SuspendElevatorThread()
{
//	this->SetElevatorThreadWork(false);//此时电梯暂停，处于非工作状态。
	if (((this->GetElevatorState()) == ELEVATOR_STATE_STILL) ||
		(((this->lpbInnerRequirementFloors[this->lpElevatorStateMsg->GetCurFloor()]) == true) && ((this->GetElevatorState()) != ELEVATOR_STATE_STILL)) )//如果电梯的当前楼层是内部需求层，那么关闭定时器。
	{
		this->SetElevatorDoorState(true);//此时电梯处于开门状态。
//		KillTimer(Elevator::GetMainDlgWnd(), this->iElevatorTimerID);
	}//否则不做响应。
	return SuspendThread(this->ElevatorThreadHandle);
}

//设置电梯线程是否为开启状态。true表示为开启状态。返回值没有意义。最后变为检测电梯开关门的标记。
bool Elevator::SetElevatorThreadWork(bool bIsWork)
{
	this->bElevatorThreadWork = bIsWork;
	return true;
}

//获得当前电梯的线程是否处于开启状态。返回当前状态。最后变为检测电梯开关门的标记。
bool Elevator::GetElevatorThreadWork()
{
	return this->bElevatorThreadWork;
}

//电梯到达需求层后的暂停。暂停两秒钟。
bool Elevator::ElevatorArrivalSuspend(int iMillisecond)
{
	//显示详细信息。
//	this->GetElevatorStateMsg()->DisplayElevatorArriveMsg();
	KillTimer(Elevator::GetMainDlgWnd(), this->iElevatorTimerID);
/*	this->ElevatorArriveEventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);   
	HANDLE ElevatorArriveThread = (HANDLE)_beginthreadex(NULL, 0, ElevatorArriveThreadFunc, 
		&(this->ElevatorArriveEventHandle), 0, NULL);*/
	SetTimer(Elevator::GetMainDlgWnd(), this->iElevatorArrivalTimerId,
		iMillisecond, ElevatorArrivalSuspend_TimerProc);
/*	WaitForSingleObject(this->ElevatorArriveEventHandle, INFINITE);//这样子会把计时器都暂停掉。等待不要写在消息循环里。
	CloseHandle(this->ElevatorArriveEventHandle);*/
	return true;
}

/*unsigned int _stdcall ElevatorArriveThreadFunc(PVOID pM)
{
	SetTimer(Elevator::GetMainDlgWnd(), (UINT_PTR)(pM), 1000, ElevatorArrivalSuspend_TimerProc);
	return 0;
}*/

VOID CALLBACK ElevatorArrivalSuspend_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTimer)
{
	SetTimer(Elevator::GetMainDlgWnd(), idEvent - 10, 1000, ElevatorTimerProc);//暂停计时器id比运行电梯计时器的id大10。
/*	SetEvent(*((HANDLE*)(idEvent)));//通知事件。*/
	KillTimer(Elevator::GetMainDlgWnd(), idEvent);//一次性的计时器。
}

//设置电梯门的状态。返回设置后的状态。
bool Elevator::SetElevatorDoorState(bool bIsDoorOpen)
{
	if (bIsDoorOpen)
	{
		TCHAR szOpenDoorMsg[20] = TEXT("♓");
		Button_SetText(this->hOpenDoorWnd, szOpenDoorMsg);
		return ((this->bIsDoorOpen) = bIsDoorOpen);
	}
	TCHAR szOpenDoorMsg[20] = TEXT("开门");
	Button_SetText(this->hOpenDoorWnd, szOpenDoorMsg);
	return ((this->bIsDoorOpen) = bIsDoorOpen);
}
//得到电梯门的状态。
bool Elevator::GetElevatorDoorState()
{
	return this->bIsDoorOpen;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////静态成员//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//这两个变量所有的Elevator实例都能访问，在构造函数中初始化。
HWND Elevator::hMainDlgWnd = NULL;
bool* Elevator::lpbOuterRequestUp = NULL;
bool* Elevator::lpbOuterRequestDown = NULL;
int Elevator::iMansionFloorsCount = 0;
int Elevator::iOuterRequestUps = 0;
int Elevator::iOuterRequestDowns = 0;
WORD Elevator::OuterRequestUpControlID[21] = { 0, IDC_1FloorUp, IDC_2FloorUp, IDC_3FloorUp, IDC_4FloorUp, IDC_5FloorUp, IDC_6FloorUp,
IDC_7FloorUp, IDC_8FloorUp, IDC_9FloorUp, IDC_10FloorUp, IDC_11FloorUp, IDC_12FloorUp, IDC_13FloorUp, IDC_14FloorUp, IDC_15FloorUp,
IDC_16FloorUp, IDC_17FloorUp, IDC_18FloorUp, IDC_19FloorUp, 0 };
WORD Elevator::OuterRequestDownControlID[21] = { 0, 0, IDC_2FloorDown, IDC_3FloorDown, IDC_4FloorDown, IDC_5FloorDown, IDC_6FloorDown,
IDC_7FloorDown, IDC_8FloorDown, IDC_9FloorDown, IDC_10FloorDown, IDC_11FloorDown, IDC_12FloorDown, IDC_13FloorDown, IDC_14FloorDown,
IDC_15FloorDown, IDC_16FloorDown, IDC_17FloorDown, IDC_18FloorDown, IDC_19FloorDown, IDC_20FloorDown };

//初始化跟电梯有关的静态变量。
//主窗口句柄，上下行外部需求的boolean数组。
bool Elevator::InitStaticElevator(HWND hwnd, int iMansionFloorsCount)
{
	//初始化大厦的总层数。
	Elevator::iMansionFloorsCount = iMansionFloorsCount;
	//记录主窗口句柄。
	Elevator::hMainDlgWnd = hwnd;
	//初始化外部需求状态。
	if (Elevator::lpbOuterRequestUp == NULL)
	{
		Elevator::lpbOuterRequestUp = (bool*)malloc((Elevator::iMansionFloorsCount + 1)*sizeof(bool));
		memset(Elevator::lpbOuterRequestUp, 0, (Elevator::iMansionFloorsCount + 1)*sizeof(bool));
	}
	if (Elevator::lpbOuterRequestDown == NULL)
	{
		Elevator::lpbOuterRequestDown = (bool*)malloc((Elevator::iMansionFloorsCount + 1)*sizeof(bool));
		memset(Elevator::lpbOuterRequestDown, 0, (Elevator::iMansionFloorsCount + 1)*sizeof(bool));
	}
	Elevator::iOuterRequestUps = 0;
	Elevator::iOuterRequestDowns = 0;
	return true;
}
//释放跟电梯有关的静态变量。
bool Elevator::ReleaseStaticElevator()
{
	free(Elevator::lpbOuterRequestUp);
	free(Elevator::lpbOuterRequestDown);
	return true;
}

//记录外部客户上楼的需求。
//传入的iFloorIndex是正常的楼层下标，bOuterRequestUp表示有无需求，true表示有。
bool Elevator::SetOuterRequestUp(int iFloorIndex, bool bOuterRequestUp)
{
	if ((iFloorIndex<1) || (iFloorIndex>19))
	{
		MessageBox(NULL, TEXT("Elevator::SetOuterRequestUp 上行楼层参数有误！"), TEXT("错误消息"), MB_OK | MB_ICONERROR);
		return false;
	}

	//改变按钮的文字。
	TCHAR szBtnHint[20] = { NULL };
	if (bOuterRequestUp)//如果是确定上行需求，那么改变响应Button的文字。
	{
		wsprintf(szBtnHint, TEXT("%d☆"), iFloorIndex);
		Button_SetText(GetDlgItem(Elevator::hMainDlgWnd, Elevator::OuterRequestUpControlID[iFloorIndex]), szBtnHint);
		//增加外部上行需求量。
		Elevator::IncreaseOuterRequestUps(iFloorIndex, bOuterRequestUp);
	}
	else//如果是取消上行需求，那么恢复原来的文字。
	{
		wsprintf(szBtnHint, TEXT("%d↑"), iFloorIndex);
		Button_SetText(GetDlgItem(Elevator::hMainDlgWnd, Elevator::OuterRequestUpControlID[iFloorIndex]), szBtnHint);
		//减少外部上行需求量。
		Elevator::DecreaseOuterRequestUps(iFloorIndex, bOuterRequestUp);
	}
	return true;
}

//记录外部客户下楼的需求。
//传入的iFloorIndex是正常的楼层下标，bOuterRequestDown表示有无需求，true表示有。
bool Elevator::SetOuterRequestDown(int iFloorIndex, bool bOuterRequestDown)
{
	if ((iFloorIndex<2) || (iFloorIndex>20))
	{
		MessageBox(NULL, TEXT("Elevator::SetOuterRequestDown 下行楼层参数有误！"), TEXT("错误消息"), MB_OK | MB_ICONERROR);
		return false;
	}
	
	//改变按钮的文字。
	TCHAR szBtnHint[20] = { NULL };
	if (bOuterRequestDown)//如果确定是下行需求。
	{
		wsprintf(szBtnHint, TEXT("%d★"), iFloorIndex);
		Button_SetText(GetDlgItem(Elevator::hMainDlgWnd, Elevator::OuterRequestDownControlID[iFloorIndex]), szBtnHint);
		//增加外部下行需求量。判断原来是否已有需求。
		Elevator::IncreaseOuterRequestDowns(iFloorIndex,bOuterRequestDown);
	}
	else//取消下行需求那么恢复原样。
	{
		wsprintf(szBtnHint, TEXT("%d↓"), iFloorIndex);
		Button_SetText(GetDlgItem(Elevator::hMainDlgWnd, Elevator::OuterRequestDownControlID[iFloorIndex]), szBtnHint);
		//减少外部上行需求量。
		Elevator::DecreaseOuterRequestDowns(iFloorIndex, bOuterRequestDown);
	}
	return true;
}

//获得主窗口的句柄。
HWND Elevator::GetMainDlgWnd()
{
	return Elevator::hMainDlgWnd;
}

//增加外部上行需求量。判断重复的事情在这里面做。返回改变后的值。
int Elevator::IncreaseOuterRequestUps(int iFloorIndex, bool bOuterRequestUp)
{
	if (Elevator::lpbOuterRequestUp[iFloorIndex] == bOuterRequestUp)
	{
		//已经相等，那么不需要改变数组中的变量。
		return Elevator::iOuterRequestUps;//如果需求动作已存在，那么不自增。
	}
	//设置数组中的变量。
	//传入的是正常下标，转化为数组下标不需要减一，第一个和最后一个元素的无用。
	Elevator::lpbOuterRequestUp[iFloorIndex] = bOuterRequestUp;
	return ++(Elevator::iOuterRequestUps);
}
//减少上行需求量。判断重复的事情在这里面做。返回改变后的值。
int Elevator::DecreaseOuterRequestUps(int iFloorIndex, bool bOuterRequestUp)
{
	if (Elevator::lpbOuterRequestUp[iFloorIndex] == bOuterRequestUp)
	{
		return Elevator::iOuterRequestUps;
	}
	//设置数组中的变量。
	//传入的是正常下标，转化为数组下标不需要减一，第一个和最后一个元素的无用。
	Elevator::lpbOuterRequestUp[iFloorIndex] = bOuterRequestUp;
	return --(Elevator::iOuterRequestUps);
}

//增加外部下行需求量。判断重复的事情在这里面做。返回改变后的值。
int Elevator::IncreaseOuterRequestDowns(int iFloorIndex, bool bOuterRequestDown)
{
	if (Elevator::lpbOuterRequestDown[iFloorIndex] == bOuterRequestDown)
	{
		return Elevator::iOuterRequestDowns;
	}
	//设置数组中的变量。
	//传入的是正常下标，转化为数组下标不需要减一，第一个和第二个元素无用。
	Elevator::lpbOuterRequestDown[iFloorIndex] = bOuterRequestDown;
	return ++(Elevator::iOuterRequestDowns);
}
//减少外部下行需求量。判断重复的事情在这里面做。返回改变后的值。
int Elevator::DecreaseOuterRequestDowns(int iFloorIndex, bool bOuterRequestDown)
{
	if (Elevator::lpbOuterRequestDown[iFloorIndex] == bOuterRequestDown)
	{
		return Elevator::iOuterRequestDowns;
	}
	//设置数组中的变量。
	//传入的是正常下标，转化为数组下标不需要减一，第一个和第二个元素无用。
	Elevator::lpbOuterRequestDown[iFloorIndex] = bOuterRequestDown;
	return --(Elevator::iOuterRequestDowns);
}


//返回外部客户在当前楼层的上楼需求状态。
//iFloorIndex 当前楼层数。
bool Elevator::GetOuterRequestUp(int iFloorIndex)
{
	return Elevator::lpbOuterRequestUp[iFloorIndex];
}
//返回外部客户在当前楼层的下楼需求状态。
//iFloorIndex 当前楼层数。
bool Elevator::GetOuterRequestDown(int iFloorIndex)
{
	return Elevator::lpbOuterRequestDown[iFloorIndex];
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////线程函数//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//电梯的线程函数。//Timer在此跟五个电梯绑定。
unsigned int _stdcall ElevatorThreadFunc(PVOID lpVoid)//不能是类的成员函数。
{
	int iElevatorTimerID = *((int*)(lpVoid));
	SetTimer(Elevator::GetMainDlgWnd(), iElevatorTimerID, 1000, ElevatorTimerProc);
	return 0;
}


//定时器函数。每隔一秒钟该部电梯扫描当前自己的内部需求，并满足自己的内部需求。
VOID CALLBACK ElevatorTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTimer)
{
	Elevator* lpElevator = lpMyElevator[idEvent];//根据Timer的Id取出lpMyElevator数组里的值。
	//扫描内部需求的方式就是检查多选的ListView中被选择的项。
	if (lpElevator->GetElevatorAlarmState())//如果电梯处于报警状态，那么不需要刷新电梯的需求数，因为电梯此时不能载客。
	{
		return;
	}
	lpElevator->RefreshInsideRequest();//首先刷新内部需求。
	int iInnerRequestCount = lpElevator->GetInnerRequirementFloorsCount();//获得此时内部需求的总量。
	int iElevatorState = lpElevator->GetElevatorState();
	switch (iElevatorState)//对三种运行状态的电梯做不同的处理。
	{
	case ELEVATOR_STATE_UPING:
	{
		UpingElevatorAction(lpElevator, iInnerRequestCount);
	}
		break;
	case ELEVATOR_STATE_DOWNING:
	{
		DowningElevatorAction(lpElevator, iInnerRequestCount);
	}
		break;
	case ELEVATOR_STATE_STILL:
	{
		StillElevatorAction(lpElevator, iInnerRequestCount);
	}
		break;
	default:
		break;
	}
}

//三种状态下的信息运行时的不同动作。
//上升状态下。
bool UpingElevatorAction(Elevator* lpElevator, int iInnerRequestCount)
{
	//如果此时电梯处于开门状态等。
	if ((lpElevator->GetElevatorDoorState()) &&
		(((lpElevator->GetlpbInnerRequirementFloors())[lpElevator->GetElevatorStateMsg()->GetCurFloor()]) == true))
	{
		return false;//不操作。
	}
	//先扫描当前楼层，若其lpbInnerRequirementFloors的值为true，那么置为false，表示满足需求。
	if ((lpElevator->GetlpbInnerRequirementFloors())[lpElevator->GetCurFloor()] == true)//到达需求层。
	{
		SendMessage(lpElevator->GetElevatorStateMsg()->GetElevatorInnerBtnWnd(), LB_SETSEL,
			(WPARAM)FALSE, (LPARAM)( lpElevator->TransFloorToLVindex(lpElevator->GetCurFloor()) ) );//取消对应的内部需求按钮高亮。也要注意楼层跟LV下标的转化。
		//显示提示信息。
//		lpElevator->GetElevatorStateMsg()->DisplayElevatorArriveMsg();//这样也无效。
		(lpElevator->GetlpbInnerRequirementFloors())[lpElevator->GetCurFloor()] = false;//表示已经满足需求。
		lpElevator->DecreaseInnerRequirementFloorsCount();//内部的总需求减少一。
		//暂停0.6秒钟，模拟电梯到站。
		lpElevator->ElevatorArrivalSuspend(600);
		
		//检查当前楼层是否是最高楼层。
		if ((lpElevator->GetCurFloor()) == (lpElevator->GetMaxInnerRequirementFloor()))//如果此时已到达需求最高楼层。
		{
			lpElevator->SetElevatorInnerBtnClick(true);
/*			if ((lpElevator->GetInnerRequirementFloorsCount()) != 0)//而内部需求又不是0.即说明在该层之下还有需求。
			{
				//那么电梯应该向下走。
				lpElevator->SetElevatorState(ELEVATOR_STATE_DOWNING);
			}
			else//若此时的内部需求是0，那么电梯就禁止停在这一层。
			{*/
				lpElevator->SetElevatorState(ELEVATOR_STATE_STILL);
/*			}*/
			//到达最高层之后不需要进行递增当前楼层的操作。
			return true;
		}
		//因为计时器暂停会偏差到下一个楼层中，因此不再这里进行递减操作。
		//没有到达极值层但是到了需求层,电梯从该层上升一层。
//		lpElevator->GetElevatorStateMsg()->IncreaseCurFloor();
		//标记当前到达的楼层。
//		lpElevator->MarkCurFloor();
		return true;
	}
	//该层没有内部需求的情况,电梯从该层上升一层。
	lpElevator->GetElevatorStateMsg()->IncreaseCurFloor();
	//标记当前到达的楼层。
	lpElevator->MarkCurFloor();
	return true;
}

//下降状态下。
bool DowningElevatorAction(Elevator* lpElevator, int iInnerRequestCount)
{
	//如果此时电梯处于运行状态，比如开门等。
	if ((lpElevator->GetElevatorDoorState()) &&
		(((lpElevator->GetlpbInnerRequirementFloors())[lpElevator->GetElevatorStateMsg()->GetCurFloor()]) == true))
	{
		return false;//不操作。
	}
	//先扫描内部需求，如果有内部需求，那么满足内部需求。
	if ((lpElevator->GetlpbInnerRequirementFloors())[lpElevator->GetCurFloor()] == true)//有内部需求。
	{
		//显示提示信息。
//		lpElevator->GetElevatorStateMsg()->DisplayElevatorArriveMsg();//这样也无效。
		SendMessage(lpElevator->GetElevatorStateMsg()->GetElevatorInnerBtnWnd(), LB_SETSEL,
			(WPARAM)FALSE, (LPARAM)( lpElevator->TransFloorToLVindex(lpElevator->GetCurFloor()) ) );//取消对应的内部需求按钮高亮。
		(lpElevator->GetlpbInnerRequirementFloors())[lpElevator->GetCurFloor()] = false;//满足该层的需求。
		lpElevator->DecreaseInnerRequirementFloorsCount();//递减内部需求的总量。
		//在这里定时器停止0.6秒钟，模拟电梯到站。
		lpElevator->ElevatorArrivalSuspend(600);
		//显示提示信息。
//		lpElevator->GetElevatorStateMsg()->DisplayElevatorArriveMsg();//这里显示不出来，Sleep的原因？
		//在这里睡眠2秒，模拟电梯到达楼层后客户进出电梯的时间。
//		Sleep(2000);
		if ((lpElevator->GetCurFloor()) == (lpElevator->GetMinInnerRequirementFloor()))//电梯此时在最低需求楼层。
		{
			lpElevator->SetElevatorInnerBtnClick(true);//因为refesh里面会把内部的需求清零，再重新填充，所以要迫使其刷新。
/*			if ((lpElevator->GetInnerRequirementFloorsCount()) > 0)//但是此时有向上的内部需求。
			{
				//那么电梯转向。
				lpElevator->SetElevatorState(ELEVATOR_STATE_UPING);//向上满足需求。
			}
			else//这时已经没有内部需求，那么电梯静止在原地。
			{*/
				lpElevator->SetElevatorState(ELEVATOR_STATE_STILL);
/*			}*/
			//到达最低层之后不需要再递减。
			return true;
		}
		//因为计时器暂停会偏差到下一个楼层中，因此不再这里进行递减操作。
		//该层没有内部需求的情况,或没有到达极值层,电梯从该层下降一层。
//		lpElevator->GetElevatorStateMsg()->DecreaseCurFloor();
		//标记当前到达的楼层。
//		lpElevator->MarkCurFloor();
		return true;
	}
	//该层没有内部需求的情况,或没有到达极值层,电梯从该层下降一层。
	lpElevator->GetElevatorStateMsg()->DecreaseCurFloor();
	//标记当前到达的楼层。
	lpElevator->MarkCurFloor();
	return true;
}
//静止状态下。
bool StillElevatorAction(Elevator* lpElevator, int iInnerRequestCount)
{
	//标记当前到达的楼层。
	lpElevator->MarkCurFloor();
	//如果此时电梯处于运行状态，比如开门等。
	if ((lpElevator->GetElevatorDoorState()) && 
		( ( (lpElevator->GetlpbInnerRequirementFloors())[lpElevator->GetElevatorStateMsg()->GetCurFloor()]) == true) )
	{
		return false;//不操作。
	}
	if (iInnerRequestCount == 0)//当前内部需求为0。有没有必要？有必要，电梯停留在1层，并且此时没有需求的时候。
	{
		lpElevator->SetElevatorState(ELEVATOR_STATE_STILL);
		lpElevator->SetMaxInnerRequirementFloor(lpElevator->GetCurFloor());
		lpElevator->SetMinInnerRequirementFloor(lpElevator->GetCurFloor());
		//有必要取消该楼层的高
	}
	else//当内部需求存在的时候。
	{
		int iMaxInnerRequestFloor = lpElevator->GetMaxInnerRequirementFloor();
		int iMinInnerRequestFloor = lpElevator->GetMinInnerRequirementFloor();
		int iCurFloor = lpElevator->GetCurFloor();
		//要求等待时间最小。此时内部需求不为0.
		if ((iMaxInnerRequestFloor != iCurFloor) && (iMinInnerRequestFloor != iCurFloor))
		{
			if (iCurFloor == 1)//电梯直接就在第一层，那么直接置为上升状态。
			{
				lpElevator->SetElevatorState(ELEVATOR_STATE_UPING);
			}
			else if (iCurFloor > iMaxInnerRequestFloor)
			{
				lpElevator->SetElevatorState(ELEVATOR_STATE_DOWNING);
			}
			else if (iCurFloor < iMinInnerRequestFloor)
			{
				lpElevator->SetElevatorState(ELEVATOR_STATE_UPING);
			}
			//这个情况是最顶和最低楼层把需求楼层夹住的情况。
			else if ((iMaxInnerRequestFloor - 2 * iCurFloor) <= -1)//此时电梯应该先满足上行需求。
			{
				lpElevator->SetElevatorState(ELEVATOR_STATE_UPING);//做上行的准备。
			}
			else
			{
				lpElevator->SetElevatorState(ELEVATOR_STATE_DOWNING);// 先满足下行需求。
			}
		}
	}
	return true;
}