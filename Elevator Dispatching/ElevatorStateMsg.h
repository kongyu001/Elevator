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
class IElevatorstate
{
public:int show();
};
class Elevatorup :public IElevatorstate
{
	Elevatorup(HWND hwnd, int iButtonListID, int iCurFloorEditID, int iElevatorFloorsCount, Elevator* lpElevator);
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
	//获得电梯内部按钮列表的句柄。
	HWND GetElevatorInnerBtnWnd();
	//当电梯到达需求的楼层后，显示提示信息。
	bool DisplayElevatorArriveMsg();//显示电梯的到达信息，跟DisplayElevatorMsg不一样，DisplayElevatorMsg只包含三个状态。
	bool DisplayElevatorup();//显示当前电梯的运行状态信息。
private:
	int iElevatorState;//该电梯此时的运行状态。
	//	int* lpiInnerRequestState;//21个元素
	int iCurFloor;//记录当前电梯运行至哪一层。
	int iElevatorFloorsCount;//该电梯一共支持多少层楼。
	HWND hElevatorInnerBtnWnd;//该电梯内对应的ButtonList的句柄。
	int iCurFloorEditID;//实时显示当前电梯停靠在第几层的Edit控件ID。
	class Elevator* lpElevator;//记录该电梯状态属于哪一部电梯。
};
class Elevatordown :public IElevatorstate
{
	Elevatordown(HWND hwnd, int iButtonListID, int iCurFloorEditID, int iElevatorFloorsCount, Elevator* lpElevator);
	//设置电梯的运行状态。
	bool SetElevatorState(int iElevatorState);
	//获得当前电梯的运行状态。
	int GetElevatorState();
	//设置当前电梯运动到了第几层。
	bool SetCurFloor(int iCurFloor);
	//获得当前电梯运动到了第几层。
	int GetCurFloor();
	//递减当前电梯的层数。返回递增后的层数。
	int DecreaseCurFloor();
	//获得电梯内部按钮列表的句柄。
	HWND GetElevatorInnerBtnWnd();
	//当电梯到达需求的楼层后，显示提示信息。
	bool DisplayElevatorArriveMsg();//显示电梯的到达信息，跟DisplayElevatorMsg不一样，DisplayElevatorMsg只包含三个状态。
	bool DisplayElevatordown();//显示当前电梯的运行状态信息。
private:
	int iElevatorState;//该电梯此时的运行状态。
	//	int* lpiInnerRequestState;//21个元素
	int iCurFloor;//记录当前电梯运行至哪一层。
	int iElevatorFloorsCount;//该电梯一共支持多少层楼。
	HWND hElevatorInnerBtnWnd;//该电梯内对应的ButtonList的句柄。
	int iCurFloorEditID;//实时显示当前电梯停靠在第几层的Edit控件ID。
	class Elevator* lpElevator;//记录该电梯状态属于哪一部电梯。
};
class Elevatorstop :public IElevatorstate
{
	Elevatorstop(HWND hwnd, int iButtonListID, int iCurFloorEditID, int iElevatorFloorsCount, Elevator* lpElevator);
	//设置电梯的运行状态。
	bool SetElevatorState(int iElevatorState);
	//获得当前电梯的运行状态。
	int GetElevatorState();
	//设置当前电梯运动到了第几层。
	bool SetCurFloor(int iCurFloor);
	//获得当前电梯运动到了第几层。
	int GetCurFloor();
	//获得电梯内部按钮列表的句柄。
	HWND GetElevatorInnerBtnWnd();
	//当电梯到达需求的楼层后，显示提示信息。
	bool DisplayElevatorArriveMsg();//显示电梯的到达信息，跟DisplayElevatorMsg不一样，DisplayElevatorMsg只包含三个状态。
	bool DisplayElevatorstop();//显示当前电梯的运行状态信息。
private:
	int iElevatorState;//该电梯此时的运行状态。
	//	int* lpiInnerRequestState;//21个元素
	int iCurFloor;//记录当前电梯运行至哪一层。
	int iElevatorFloorsCount;//该电梯一共支持多少层楼。
	HWND hElevatorInnerBtnWnd;//该电梯内对应的ButtonList的句柄。
	int iCurFloorEditID;//实时显示当前电梯停靠在第几层的Edit控件ID。
	class Elevator* lpElevator;//记录该电梯状态属于哪一部电梯。
};
class CPPCollection {
public:
	class Iterator{
	public:
		int index;
		CPPCollection& outer;
		Iterator(CPPCollection& o, int i) :outer(o), index(i){}
		void operator++(){
			index++;
		}
		TCHAR operator*() const{
			return outer.szFloorButtonHint[index][0];
		}
		bool operator!=(Iterator i){
			return i.index != index - 1;
		}
	};
public:
	TCHAR szFloorButtonHint[20][20];

	Iterator begin(){
		return Iterator(*this, 0);
	}
	Iterator end(){

		return Iterator(*this, 19);
	}
};
class ElevatorStateMsg :public IElevatorstate
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
class Interator;
class Aggregate
{
public:

	virtual ~Aggregate(){};
	virtual Interator* CreateItrator() = 0{};
	virtual int GetSize() = 0{};
	virtual int GetItem(int index) = 0{};
protected:
	Aggregate(){};
};


class ConcreteAggregate :public Aggregate
{
public:
	enum{ size = 20 };
	ConcreteAggregate()
	{
		for (int i = 0; i < size; i++)
			m_obj[i] = i;
	}
	~ConcreteAggregate(){};
	Interator* CreateItrator();
	int GetItem(int index)
	{
		if (GetSize()) return m_obj[index];
		else return -1;
	}
	int GetSize(){ return size; }
private:
	int m_obj[size];
};


class Interator
{
public:

	virtual ~Interator(){};
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual int CurrentItem() = 0;
protected:
	Interator(){};
};


class ConcreteInterator :public Interator
{
public:
	ConcreteInterator(Aggregate* ag, int index = 0)
	{
		m_ag = ag;
		m_index = index;
	}
	~ConcreteInterator(){};
	void First(){ m_index = 0; }
	void Next()
	{
		if (m_index != m_ag->GetSize()) m_index++;
	}
	bool IsDone(){
		return(m_index == m_ag->GetSize());
	}
	int CurrentItem(){
		return m_ag->GetItem(m_index);

	}
private:
	Aggregate* m_ag;
	int m_index;
};