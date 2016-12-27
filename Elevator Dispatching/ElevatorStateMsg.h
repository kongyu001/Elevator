#pragma once 

#include<Windows.h>
#include<windowsx.h>
#include"resource.h"
#include"Elevator.h"

//定义电梯当前运行状态的常量。
#define ELEVATOR_STATE_UPING 0x1012
#define ELEVATOR_STATE_DOWNING 0x1013
#define ELEVATOR_STATE_STILL 0x1014
#define ELEVATOR_INNERREQUEST_NONE 0x1015
#define ELEVATOR_INNERREQUEST_UP 0x1016
#define ELEVATOR_INNERREQUEST_DOWN 0x1017

class Elevator;//在两个类互相包含的时候，需要先声明一下。
class ElevatorStateMsg
{
public:
	//初始化电梯运行状态，静止在第一层。
	//HWND 父窗口句柄，iButtonListID电梯内按钮List的ID，iMansionFloorsCount大厦总层数。
	//并且根据楼层数分割ButtonList。将该电梯状态与其所属的lpElevator相对应。
	ElevatorStateMsg(HWND hwnd, int iButtonListID, int iCurFloorEditID, int iElevatorFloorsCount, Elevator* lpElevator);
	//设置电梯的运行状态。
	bool SetElevatorState(int iElevatorState);
	//获得当前电梯的运行状态。
	int GetElevatorState();
	//设置当前电梯运动到了第几层。
	bool SetCurFloor(int iCurFloor);
	//获得当前电梯运动到了第几层。
	int GetCurFloor();
	//递增当前电梯的层数。返回递增后的层数。
	int IncreaseCurFloor();
	//递减当前电梯的层数。返回递增后的层数。
	int DecreaseCurFloor();
	//获得电梯内部按钮列表的句柄。
	HWND GetElevatorInnerBtnWnd();
	//当电梯到达需求的楼层后，显示提示信息。
	bool DisplayElevatorArriveMsg();//显示电梯的到达信息，跟DisplayElevatorMsg不一样，DisplayElevatorMsg只包含三个状态。
	bool DisplayElevatorMsg();//显示当前电梯的运行状态信息。

/*	//设置该电梯该楼层内部需求的状态，要上行还是下行，还是无需求。
	//iFloorIndex  楼层序号  楼层的状态由内部决定。
	int SetlpiInnerRequestState(int iFloorIndex);
	//获得该楼层需求的状态。
	int GetlpiInnerRequestState();
	//将楼层内部需求状态设为初始值。
	bool InitlpiInnerRequestState();*/
	
private:
	int iElevatorState;//该电梯此时的运行状态。
//	int* lpiInnerRequestState;//21个元素
	int iCurFloor;//记录当前电梯运行至哪一层。
	int iElevatorFloorsCount;//该电梯一共支持多少层楼。
	HWND hElevatorInnerBtnWnd;//该电梯内对应的ButtonList的句柄。
	int iCurFloorEditID;//实时显示当前电梯停靠在第几层的Edit控件ID。
	class Elevator* lpElevator;//记录该电梯状态属于哪一部电梯。
};