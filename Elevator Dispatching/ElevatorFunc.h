#pragma once
#include"Elevator.h"

//当用户点击电梯外部响应按钮时的函数。
bool ClickElevatorOuterBtn(WORD wControlID);

//当用户点击电梯内部按钮的时候。
/*记录下哪一部电梯的内部按钮有被按过，然后处理。
由于消息会多次进入这个函数，所以不在此做处理*/
bool ClickElevatorInnerBtn(Elevator** lpMyElevator, WORD wControlID);

//当用户按下电梯的开关门键的时候，开始对内部电梯的按钮状态做处理。
bool ClickElevatorDoorBtn(Elevator** lpMyElevator, WORD wControlID);

//当用户按下报警键的时候。
bool ClickElevatorAlarmBtn(Elevator** lpMyElevator, WORD wControlID);

/*//获得当前空闲的电梯数量。
//传入所有Elevator的变量。
//该函数返回空闲电梯的数量，以及用iStillElevatorBuff标明是哪一部电梯空闲。iStillElevatorBuff不为NULL时。
//iStillElevatorBuff为NULL时仅返回空闲电梯的数量。
int GetStillElevators(Elevator* lpMyElevator, int* iStillElevatorBuff);*/

//  主线程中的计时器函数。
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
	//分配外部需求，将电梯外部需求转化为电梯内部需求。
	//对Elevator里面的外部需求数组进行扫描。分配任务。
	bool DispatchOuterRequtst(Elevator** lpMyElevator);


};

//将外部需求发送给自己楼下正在上升的电梯。
//返回true表示任务成功分配。
//iRequestFloor 发出请求的楼层，iUpingCount当前已有的正在上升的电梯数，lpUpingElevators是那几部电梯。
bool SendToUnderFloorUping(Elevator** lpMyElevator, int iRequestFloor, int iUpingCount, int* lpUpingElevators);

//2.(1)找正在下行的，且下行底线离自己绝对值最小；(2)找正静止的，且离自己距离绝对值最小；取二者中值较小的那部电梯执行任务。
bool SendToDowningOrStill(Elevator** lpMyElevator, int iRequestFloor, int iDowningCount, int* lpDowningElevators, int iStillCount, int* lpStillElevators);

//将外部需求发送给自己楼上正在下降的电梯。
bool SendToAboveFloorDowning(Elevator** lpMyElevator, int iRequestFloor, int iDowningCount, int* lpDowningElevators);

//2.(1)找正在上行的，且上行顶限离自己绝对值最小；(2)找静止的，且离自己绝对值最小；取二者中绝对值较小的那部电梯执行任务。
bool SendToUpingOrStill(Elevator** lpMyElevator, int iRequestFloor, int iUpingCount, int* lpUpingElevators, int iStillCount, int* lpStillElevators);

//开启五部电梯的全部线程。
bool StartAllElevators(Elevator** lpMyElevator, int iElevatorCount);