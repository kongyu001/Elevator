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
class IElevatorstate
{
public:int show();
};
class Elevatorup :public IElevatorstate
{
	Elevatorup(HWND hwnd, int iButtonListID, int iCurFloorEditID, int iElevatorFloorsCount, Elevator* lpElevator);
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
	//��õ����ڲ���ť�б�ľ����
	HWND GetElevatorInnerBtnWnd();
	//�����ݵ��������¥�����ʾ��ʾ��Ϣ��
	bool DisplayElevatorArriveMsg();//��ʾ���ݵĵ�����Ϣ����DisplayElevatorMsg��һ����DisplayElevatorMsgֻ��������״̬��
	bool DisplayElevatorup();//��ʾ��ǰ���ݵ�����״̬��Ϣ��
private:
	int iElevatorState;//�õ��ݴ�ʱ������״̬��
	//	int* lpiInnerRequestState;//21��Ԫ��
	int iCurFloor;//��¼��ǰ������������һ�㡣
	int iElevatorFloorsCount;//�õ���һ��֧�ֶ��ٲ�¥��
	HWND hElevatorInnerBtnWnd;//�õ����ڶ�Ӧ��ButtonList�ľ����
	int iCurFloorEditID;//ʵʱ��ʾ��ǰ����ͣ���ڵڼ����Edit�ؼ�ID��
	class Elevator* lpElevator;//��¼�õ���״̬������һ�����ݡ�
};
class Elevatordown :public IElevatorstate
{
	Elevatordown(HWND hwnd, int iButtonListID, int iCurFloorEditID, int iElevatorFloorsCount, Elevator* lpElevator);
	//���õ��ݵ�����״̬��
	bool SetElevatorState(int iElevatorState);
	//��õ�ǰ���ݵ�����״̬��
	int GetElevatorState();
	//���õ�ǰ�����˶����˵ڼ��㡣
	bool SetCurFloor(int iCurFloor);
	//��õ�ǰ�����˶����˵ڼ��㡣
	int GetCurFloor();
	//�ݼ���ǰ���ݵĲ��������ص�����Ĳ�����
	int DecreaseCurFloor();
	//��õ����ڲ���ť�б�ľ����
	HWND GetElevatorInnerBtnWnd();
	//�����ݵ��������¥�����ʾ��ʾ��Ϣ��
	bool DisplayElevatorArriveMsg();//��ʾ���ݵĵ�����Ϣ����DisplayElevatorMsg��һ����DisplayElevatorMsgֻ��������״̬��
	bool DisplayElevatordown();//��ʾ��ǰ���ݵ�����״̬��Ϣ��
private:
	int iElevatorState;//�õ��ݴ�ʱ������״̬��
	//	int* lpiInnerRequestState;//21��Ԫ��
	int iCurFloor;//��¼��ǰ������������һ�㡣
	int iElevatorFloorsCount;//�õ���һ��֧�ֶ��ٲ�¥��
	HWND hElevatorInnerBtnWnd;//�õ����ڶ�Ӧ��ButtonList�ľ����
	int iCurFloorEditID;//ʵʱ��ʾ��ǰ����ͣ���ڵڼ����Edit�ؼ�ID��
	class Elevator* lpElevator;//��¼�õ���״̬������һ�����ݡ�
};
class Elevatorstop :public IElevatorstate
{
	Elevatorstop(HWND hwnd, int iButtonListID, int iCurFloorEditID, int iElevatorFloorsCount, Elevator* lpElevator);
	//���õ��ݵ�����״̬��
	bool SetElevatorState(int iElevatorState);
	//��õ�ǰ���ݵ�����״̬��
	int GetElevatorState();
	//���õ�ǰ�����˶����˵ڼ��㡣
	bool SetCurFloor(int iCurFloor);
	//��õ�ǰ�����˶����˵ڼ��㡣
	int GetCurFloor();
	//��õ����ڲ���ť�б�ľ����
	HWND GetElevatorInnerBtnWnd();
	//�����ݵ��������¥�����ʾ��ʾ��Ϣ��
	bool DisplayElevatorArriveMsg();//��ʾ���ݵĵ�����Ϣ����DisplayElevatorMsg��һ����DisplayElevatorMsgֻ��������״̬��
	bool DisplayElevatorstop();//��ʾ��ǰ���ݵ�����״̬��Ϣ��
private:
	int iElevatorState;//�õ��ݴ�ʱ������״̬��
	//	int* lpiInnerRequestState;//21��Ԫ��
	int iCurFloor;//��¼��ǰ������������һ�㡣
	int iElevatorFloorsCount;//�õ���һ��֧�ֶ��ٲ�¥��
	HWND hElevatorInnerBtnWnd;//�õ����ڶ�Ӧ��ButtonList�ľ����
	int iCurFloorEditID;//ʵʱ��ʾ��ǰ����ͣ���ڵڼ����Edit�ؼ�ID��
	class Elevator* lpElevator;//��¼�õ���״̬������һ�����ݡ�
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