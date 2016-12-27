#pragma once 

#include<Windows.h>
#include<windowsx.h>
#include"resource.h"
#include"ElevatorStateMsg.h"
#include<process.h>

//这个Timer的ID也可以用来标明Elevator实例的序号。
#define ELEVATORTHREAD_TIMER1 0
#define ELEVATORTHREAD_TIMER2 1
#define ELEVATORTHREAD_TIMER3 2
#define ELEVATORTHREAD_TIMER4 3
#define ELEVATORTHREAD_TIMER5 4	//跟后面的代码有关，这只能是这几个数字。
//电梯到站后的设置电梯暂停的计时器为电梯的计时器加10。
#define ELEVATORTHREAD_MAINTIMER 5
#define MAX_ELEVATOR_INNERREQUEST_NUM 6  //电梯内内部需求最大的数量。

//定义一个电梯类，包括电梯运行的状态，该电梯所属的ListView等等。
class Elevator
{
public:
	//在此构造函数中，将电梯与它对应的ListView绑定。并且初始化电梯状态，以及楼层状态。
	//hwnd 父窗口句柄，iListViewID电梯对应的ListView的ID，iMansionFloorsCount电梯一共支持多少层楼，iAlarmControlID报警键的ID。
	Elevator(HWND hwnd, int iFloorListID, int iInnerButtonListID, int iCurFloorEditID, int iAlarmControlID, int iOpenDoorID, 
		int iElevatorFloorsCount, int iTimerID);
	//析构函数，释放lpRequirementFloors。
	~Elevator();
	//设置电梯的运行状态。
	bool SetElevatorState(int iElevatorState);
	//获得当前电梯的运行状态。
	int GetElevatorState();
	//设置当前电梯运动到了第几层。
	bool SetCurFloor(int iCurFloor);
	//标记电梯当前运动到了第几层。
	bool MarkCurFloor();
	//标记电梯当前运动到了第几层。
	bool MarkCurFloor(int iCurFloor);
	//获得当前电梯运动到了第几层。
	int GetCurFloor();
	//获得表示楼层的ListView的句柄。
	HWND GetElevatorWnd();
	//将ListView的下标转化为正常的楼梯层数。
	//返回正常的楼层数，楼层从1开始。传入ListView的正常index。
	int TransLVindexToFloor(int iLVindex);
	//返回正常的ListView下标，下标从零开始，传入的为正常楼层下标。
	int TransFloorToLVindex(int iFloorIndex);
	//设置电梯内按钮有没有被按下并未被处理，有即为true。
	//若按钮按下的信息已被处理那么向其中传入false。
	bool SetElevatorInnerBtnClick(bool bElevatorInnerBtnClick);
	//返回获得电梯内按钮是否被按下的状态。
	bool GetElevatorInnerBtnClick();
	//刷新电梯的内部需求，即更新lpInnerRequirementFloors，iInnerRequirementFloorsCount这两个变量。
	bool RefreshInsideRequest();//这个函数十分重要。
	//设置此时内部需求中需到达的最高楼层。
	bool SetMaxInnerRequirementFloor(int iMaxInnerRequirementFloor);
	//获得此时内部需求中需到达的最高楼层。
	int GetMaxInnerRequirementFloor();
	//设置此时内部需求中需到达的最低的楼层。
	bool SetMinInnerRequirementFloor(int iMinInnerRequirementFloor);
	//获得此时内部需求中需到达的最低的楼层。
	int GetMinInnerRequirementFloor();
	//获得类中ElevatorStateMsg类的指针。
	class ElevatorStateMsg* GetElevatorStateMsg();
	//获得电梯中内部需求的总量。
	int GetInnerRequirementFloorsCount();
	//获得内部需求量的数组。
	bool* GetlpbInnerRequirementFloors();
	//递增内部需求的总量，返回递增后的值。
	int IncreaseInnerRequirementFloorsCount();
	//递减内部需求总量，返回递减后的值。
	int DecreaseInnerRequirementFloorsCount();
	//接受外部需求将其转化为内部需求，传入的参数为楼层数。不分外部的上行或则下行需求。
	//iElevatorState 接受的是外部上行还是下行需求。
	bool ReceiveOuterRequest(int iFloorIndex, int iElevatorState);
	//获得线程的句柄。
	HANDLE GetElevatorThreadHandle();
	//重新启动电梯。
	DWORD ResumeElevatorThread();
	//暂停电梯的线程。
	DWORD SuspendElevatorThread();
	//设置电梯线程是否为开启状态。true表示为开启状态。最后变为检测电梯开关门的标记。
	bool SetElevatorThreadWork(bool bIsWork);
	//获得当前电梯的线程是否处于开启状态。返回当前状态。最后变为检测电梯开关门的标记。
	bool GetElevatorThreadWork();
	//电梯到达需求层后的暂停。暂停两秒钟。
	bool ElevatorArrivalSuspend(int iMillisecond);
	//清除电梯的全部内部需求，并且关闭电梯的即使器。
	bool ClearElevator();


	//初始化跟电梯有关的静态变量。
	//hwnd父窗口句柄，iMansionFloorsCount大厦层数。
	static bool InitStaticElevator(HWND hwnd, int iMansionFloorsCount);
	//释放跟电梯有关的静态变量。
	static bool ReleaseStaticElevator();
	//记录外部客户上楼的需求。
	static bool SetOuterRequestUp(int iFloorIndex, bool bOuterRequestUp);
	//记录外部客户下楼的需求。
	static bool SetOuterRequestDown(int iFloorIndex, bool bOuterRequestDown);
	//返回外部客户在当前楼层的上楼需求状态。//iFloorIndex 当前楼层数。
	static bool GetOuterRequestUp(int iFloorIndex);
	//返回外部客户在当前楼层的下楼需求状态。//iFloorIndex 当前楼层数。
	static bool GetOuterRequestDown(int iFloorIndex);
	//获得主窗口的句柄。
	static HWND GetMainDlgWnd();
	//增加外部上行需求量。返回改变后的值。
	static int IncreaseOuterRequestUps(int iFloorIndex, bool bOuterRequestUp);
	//减少外部上行需求量。返回改变后的值。
	static int DecreaseOuterRequestUps(int iFloorIndex, bool bOuterRequestUp);
	//增加外部下行需求量。返回改变后的值。
	static int IncreaseOuterRequestDowns(int iFloorIndex, bool bOuterRequestDown);
	//减少外部下行需求量。返回改变后的值。
	static int DecreaseOuterRequestDowns(int iFloorIndex, bool bOuterRequestDown);
	//设置电梯的报警状态。
	bool SetElevatorAlarmState(bool bIsAlarm);
	//得到电梯的报警状态。
	bool GetElevatorAlarmState();
	 //设置电梯门的状态。开门true 关门false
	bool SetElevatorDoorState(bool bIsDoorOpen);
	//得到电梯门的状态。
	bool GetElevatorDoorState();

private:
	class ElevatorStateMsg* lpElevatorStateMsg;//含有内部的类的话要注意声明方式。
	HWND hElevatorWnd;//该部电梯对应的表示楼层的ListView的句柄。
	int iElevatorFloorsCount;//该电梯一共支持多少层楼。
	bool* lpbInnerRequirementFloors;//记录该部电梯中的用户需要到的楼层。总共有21个单元。
	int iInnerRequirementFloorsCount;//记录用户需要到的楼层一共有多少个，即该部电梯中的内部需求总量。
	int iMaxInnerRequirementFloor;//此时内部需求中需到达的最高楼层。
	int iMinInnerRequirementFloor;//此时内部需求中需到达的最低的楼层。
	HANDLE ElevatorThreadHandle;//一个电梯实例对应一个线程。
//	HANDLE ElevatorArriveEventHandle;//电梯到达需求楼层之后，等待事件的句柄。
	HWND hAlarmControlWnd;//报警键的HWND。
	HWND hOpenDoorWnd;//开门键的HWND。
	int iElevatorTimerID;//该电梯对应的定时器的ID。
	int iElevatorArrivalTimerId;//电梯到站计时器的ID。
	//若电梯内的按钮被点击，且未被处理，那么这个值为true，处理过后置为false
	//所谓处理就是向lpInnerRequirementFloors	iInnerRequirementFloorsCount填入值。
	bool bElevatorInnerBtnClick;
	//标明电梯线程是否开启的变量。
	bool bElevatorThreadWork;
	//标明电梯是否处于报警状态。
	bool bIsAlarm;//如果处于报警状态，那么电梯将不会接受任何需求。
	//标记电梯门是否处于开启状态。
	bool bIsDoorOpen;//标记电梯门是否处于开启状态。

	static HWND hMainDlgWnd;//记录主窗口的句柄。
	static int iMansionFloorsCount;//该大厦一共有多少层。
	static bool* lpbOuterRequestUp;//记录电梯外部需求中需要上楼的需求，true表示有该需求。
	static int iOuterRequestUps;//外部上楼需求一共有多少个。
	static bool* lpbOuterRequestDown;//记录电梯外部需求中需要下楼的需求，true表示有该需求。
	static int iOuterRequestDowns;//外部上楼需求一共有多少个。
	static WORD OuterRequestUpControlID[21];//记录外部需求的上行按钮控件ID。
	static WORD OuterRequestDownControlID[21];//记录外部需求的上行按钮控件ID。
};

//电梯的线程函数。
unsigned int _stdcall ElevatorThreadFunc(PVOID lpVoid);//不能是类的成员函数。
//电梯到达需求站之后的线程函数。
//unsigned int _stdcall ElevatorArriveThreadFunc(PVOID pM);
//电梯运作定时器函数。
VOID CALLBACK ElevatorTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
//电梯到达需求楼层，暂停的计时器函数。
VOID CALLBACK ElevatorArrivalSuspend_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTimer);
//三种状态下的信息运行时的不同动作。
//上升状态下。
bool UpingElevatorAction(Elevator* lpElevator, int iInnerRequestCount);
//下降状态下。
bool DowningElevatorAction(Elevator* lpElevator, int iInnerRequestCount);
//静止状态下。
bool StillElevatorAction(Elevator* lpElevator, int iInnerRequestCount);
