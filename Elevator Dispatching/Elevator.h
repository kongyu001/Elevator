#pragma once 

#include<Windows.h>
#include<windowsx.h>
#include"resource.h"
#include"ElevatorStateMsg.h"
#include<process.h>

//���Timer��IDҲ������������Elevatorʵ������š�
#define ELEVATORTHREAD_TIMER1 0
#define ELEVATORTHREAD_TIMER2 1
#define ELEVATORTHREAD_TIMER3 2
#define ELEVATORTHREAD_TIMER4 3
#define ELEVATORTHREAD_TIMER5 4	//������Ĵ����йأ���ֻ�����⼸�����֡�
//���ݵ�վ������õ�����ͣ�ļ�ʱ��Ϊ���ݵļ�ʱ����10��
#define ELEVATORTHREAD_MAINTIMER 5
#define MAX_ELEVATOR_INNERREQUEST_NUM 6  //�������ڲ���������������

//����һ�������࣬�����������е�״̬���õ���������ListView�ȵȡ�
class Elevator
{
public:
	//�ڴ˹��캯���У�������������Ӧ��ListView�󶨡����ҳ�ʼ������״̬���Լ�¥��״̬��
	//hwnd �����ھ����iListViewID���ݶ�Ӧ��ListView��ID��iMansionFloorsCount����һ��֧�ֶ��ٲ�¥��iAlarmControlID��������ID��
	Elevator(HWND hwnd, int iFloorListID, int iInnerButtonListID, int iCurFloorEditID, int iAlarmControlID, int iOpenDoorID, 
		int iElevatorFloorsCount, int iTimerID);
	//�����������ͷ�lpRequirementFloors��
	~Elevator();
	//���õ��ݵ�����״̬��
	bool SetElevatorState(int iElevatorState);
	//��õ�ǰ���ݵ�����״̬��
	int GetElevatorState();
	//���õ�ǰ�����˶����˵ڼ��㡣
	bool SetCurFloor(int iCurFloor);
	//��ǵ��ݵ�ǰ�˶����˵ڼ��㡣
	bool MarkCurFloor();
	//��ǵ��ݵ�ǰ�˶����˵ڼ��㡣
	bool MarkCurFloor(int iCurFloor);
	//��õ�ǰ�����˶����˵ڼ��㡣
	int GetCurFloor();
	//��ñ�ʾ¥���ListView�ľ����
	HWND GetElevatorWnd();
	//��ListView���±�ת��Ϊ������¥�ݲ�����
	//����������¥������¥���1��ʼ������ListView������index��
	int TransLVindexToFloor(int iLVindex);
	//����������ListView�±꣬�±���㿪ʼ�������Ϊ����¥���±ꡣ
	int TransFloorToLVindex(int iFloorIndex);
	//���õ����ڰ�ť��û�б����²�δ�������м�Ϊtrue��
	//����ť���µ���Ϣ�ѱ�������ô�����д���false��
	bool SetElevatorInnerBtnClick(bool bElevatorInnerBtnClick);
	//���ػ�õ����ڰ�ť�Ƿ񱻰��µ�״̬��
	bool GetElevatorInnerBtnClick();
	//ˢ�µ��ݵ��ڲ����󣬼�����lpInnerRequirementFloors��iInnerRequirementFloorsCount������������
	bool RefreshInsideRequest();//�������ʮ����Ҫ��
	//���ô�ʱ�ڲ��������赽������¥�㡣
	bool SetMaxInnerRequirementFloor(int iMaxInnerRequirementFloor);
	//��ô�ʱ�ڲ��������赽������¥�㡣
	int GetMaxInnerRequirementFloor();
	//���ô�ʱ�ڲ��������赽�����͵�¥�㡣
	bool SetMinInnerRequirementFloor(int iMinInnerRequirementFloor);
	//��ô�ʱ�ڲ��������赽�����͵�¥�㡣
	int GetMinInnerRequirementFloor();
	//�������ElevatorStateMsg���ָ�롣
	class ElevatorStateMsg* GetElevatorStateMsg();
	//��õ������ڲ������������
	int GetInnerRequirementFloorsCount();
	//����ڲ������������顣
	bool* GetlpbInnerRequirementFloors();
	//�����ڲ���������������ص������ֵ��
	int IncreaseInnerRequirementFloorsCount();
	//�ݼ��ڲ��������������صݼ����ֵ��
	int DecreaseInnerRequirementFloorsCount();
	//�����ⲿ������ת��Ϊ�ڲ����󣬴���Ĳ���Ϊ¥�����������ⲿ�����л�����������
	//iElevatorState ���ܵ����ⲿ���л�����������
	bool ReceiveOuterRequest(int iFloorIndex, int iElevatorState);
	//����̵߳ľ����
	HANDLE GetElevatorThreadHandle();
	//�����������ݡ�
	DWORD ResumeElevatorThread();
	//��ͣ���ݵ��̡߳�
	DWORD SuspendElevatorThread();
	//���õ����߳��Ƿ�Ϊ����״̬��true��ʾΪ����״̬������Ϊ�����ݿ����ŵı�ǡ�
	bool SetElevatorThreadWork(bool bIsWork);
	//��õ�ǰ���ݵ��߳��Ƿ��ڿ���״̬�����ص�ǰ״̬������Ϊ�����ݿ����ŵı�ǡ�
	bool GetElevatorThreadWork();
	//���ݵ������������ͣ����ͣ�����ӡ�
	bool ElevatorArrivalSuspend(int iMillisecond);
	//������ݵ�ȫ���ڲ����󣬲��ҹرյ��ݵļ�ʹ����
	bool ClearElevator();


	//��ʼ���������йصľ�̬������
	//hwnd�����ھ����iMansionFloorsCount���ò�����
	static bool InitStaticElevator(HWND hwnd, int iMansionFloorsCount);
	//�ͷŸ������йصľ�̬������
	static bool ReleaseStaticElevator();
	//��¼�ⲿ�ͻ���¥������
	static bool SetOuterRequestUp(int iFloorIndex, bool bOuterRequestUp);
	//��¼�ⲿ�ͻ���¥������
	static bool SetOuterRequestDown(int iFloorIndex, bool bOuterRequestDown);
	//�����ⲿ�ͻ��ڵ�ǰ¥�����¥����״̬��//iFloorIndex ��ǰ¥������
	static bool GetOuterRequestUp(int iFloorIndex);
	//�����ⲿ�ͻ��ڵ�ǰ¥�����¥����״̬��//iFloorIndex ��ǰ¥������
	static bool GetOuterRequestDown(int iFloorIndex);
	//��������ڵľ����
	static HWND GetMainDlgWnd();
	//�����ⲿ���������������ظı���ֵ��
	static int IncreaseOuterRequestUps(int iFloorIndex, bool bOuterRequestUp);
	//�����ⲿ���������������ظı���ֵ��
	static int DecreaseOuterRequestUps(int iFloorIndex, bool bOuterRequestUp);
	//�����ⲿ���������������ظı���ֵ��
	static int IncreaseOuterRequestDowns(int iFloorIndex, bool bOuterRequestDown);
	//�����ⲿ���������������ظı���ֵ��
	static int DecreaseOuterRequestDowns(int iFloorIndex, bool bOuterRequestDown);
	//���õ��ݵı���״̬��
	bool SetElevatorAlarmState(bool bIsAlarm);
	//�õ����ݵı���״̬��
	bool GetElevatorAlarmState();
	 //���õ����ŵ�״̬������true ����false
	bool SetElevatorDoorState(bool bIsDoorOpen);
	//�õ������ŵ�״̬��
	bool GetElevatorDoorState();

private:
	class ElevatorStateMsg* lpElevatorStateMsg;//�����ڲ�����Ļ�Ҫע��������ʽ��
	HWND hElevatorWnd;//�ò����ݶ�Ӧ�ı�ʾ¥���ListView�ľ����
	int iElevatorFloorsCount;//�õ���һ��֧�ֶ��ٲ�¥��
	bool* lpbInnerRequirementFloors;//��¼�ò������е��û���Ҫ����¥�㡣�ܹ���21����Ԫ��
	int iInnerRequirementFloorsCount;//��¼�û���Ҫ����¥��һ���ж��ٸ������ò������е��ڲ�����������
	int iMaxInnerRequirementFloor;//��ʱ�ڲ��������赽������¥�㡣
	int iMinInnerRequirementFloor;//��ʱ�ڲ��������赽�����͵�¥�㡣
	HANDLE ElevatorThreadHandle;//һ������ʵ����Ӧһ���̡߳�
//	HANDLE ElevatorArriveEventHandle;//���ݵ�������¥��֮�󣬵ȴ��¼��ľ����
	HWND hAlarmControlWnd;//��������HWND��
	HWND hOpenDoorWnd;//���ż���HWND��
	int iElevatorTimerID;//�õ��ݶ�Ӧ�Ķ�ʱ����ID��
	int iElevatorArrivalTimerId;//���ݵ�վ��ʱ����ID��
	//�������ڵİ�ť���������δ��������ô���ֵΪtrue�����������Ϊfalse
	//��ν���������lpInnerRequirementFloors	iInnerRequirementFloorsCount����ֵ��
	bool bElevatorInnerBtnClick;
	//���������߳��Ƿ����ı�����
	bool bElevatorThreadWork;
	//���������Ƿ��ڱ���״̬��
	bool bIsAlarm;//������ڱ���״̬����ô���ݽ���������κ�����
	//��ǵ������Ƿ��ڿ���״̬��
	bool bIsDoorOpen;//��ǵ������Ƿ��ڿ���״̬��

	static HWND hMainDlgWnd;//��¼�����ڵľ����
	static int iMansionFloorsCount;//�ô���һ���ж��ٲ㡣
	static bool* lpbOuterRequestUp;//��¼�����ⲿ��������Ҫ��¥������true��ʾ�и�����
	static int iOuterRequestUps;//�ⲿ��¥����һ���ж��ٸ���
	static bool* lpbOuterRequestDown;//��¼�����ⲿ��������Ҫ��¥������true��ʾ�и�����
	static int iOuterRequestDowns;//�ⲿ��¥����һ���ж��ٸ���
	static WORD OuterRequestUpControlID[21];//��¼�ⲿ��������а�ť�ؼ�ID��
	static WORD OuterRequestDownControlID[21];//��¼�ⲿ��������а�ť�ؼ�ID��
};

//���ݵ��̺߳�����
unsigned int _stdcall ElevatorThreadFunc(PVOID lpVoid);//��������ĳ�Ա������
//���ݵ�������վ֮����̺߳�����
//unsigned int _stdcall ElevatorArriveThreadFunc(PVOID pM);
//����������ʱ��������
VOID CALLBACK ElevatorTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
//���ݵ�������¥�㣬��ͣ�ļ�ʱ��������
VOID CALLBACK ElevatorArrivalSuspend_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTimer);
//����״̬�µ���Ϣ����ʱ�Ĳ�ͬ������
//����״̬�¡�
bool UpingElevatorAction(Elevator* lpElevator, int iInnerRequestCount);
//�½�״̬�¡�
bool DowningElevatorAction(Elevator* lpElevator, int iInnerRequestCount);
//��ֹ״̬�¡�
bool StillElevatorAction(Elevator* lpElevator, int iInnerRequestCount);
