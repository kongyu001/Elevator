#include"stdafx.h"
#include"MainDlg.h"

//要是在该变量前加static，那么在其他源文件中即使用extern 该变量也不可见。
Elevator* lpMyElevator[5] = { NULL };//全局的电梯类指针，表示该大厦内现有的电梯实例。

//主界面窗口过程函数。
BOOL CALLBACK ElevatorDispatch_DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//设置应用程序图标。
		HICON hIcon = LoadIcon((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDI_ElevatorDispatch_Icon));
		SendMessage(hwnd, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);
		//初始化电梯静态的成员。
		Elevator::InitStaticElevator(hwnd, 20);//非常重要。
		//构建电梯实例。
		lpMyElevator[0] = new Elevator(hwnd, IDC_ElevatorList1, IDC_UserInsideRequest1, IDC_CurFloorEdit1, IDC_AlarmBtn1, IDC_OpenDoorBtn1, 20, ELEVATORTHREAD_TIMER1);
		lpMyElevator[1] = new Elevator(hwnd, IDC_ElevatorList2, IDC_UserInsideRequest2, IDC_CurFloorEdit2, IDC_AlarmBtn2, IDC_OpenDoorBtn2, 20, ELEVATORTHREAD_TIMER2);
		lpMyElevator[2] = new Elevator(hwnd, IDC_ElevatorList3, IDC_UserInsideRequest3, IDC_CurFloorEdit3, IDC_AlarmBtn3, IDC_OpenDoorBtn3, 20, ELEVATORTHREAD_TIMER3);
		lpMyElevator[3] = new Elevator(hwnd, IDC_ElevatorList4, IDC_UserInsideRequest4, IDC_CurFloorEdit4, IDC_AlarmBtn4, IDC_OpenDoorBtn4, 20, ELEVATORTHREAD_TIMER4);
		lpMyElevator[4] = new Elevator(hwnd, IDC_ElevatorList5, IDC_UserInsideRequest5, IDC_CurFloorEdit5, IDC_AlarmBtn5, IDC_OpenDoorBtn5, 20, ELEVATORTHREAD_TIMER5);
		//初始化时即开启主线程定时器。
		SetTimer(Elevator::GetMainDlgWnd(), ELEVATORTHREAD_MAINTIMER, 100, MainThreadTimerProc);//开启主线程计时器，分配外部需求。
	}
		return TRUE;
	case WM_COMMAND:
	{
		WORD wControlID = LOWORD(wParam);
		if ((wControlID >= 1006) && (wControlID <= 1043))//当有用户点击电梯外部的按钮的时候。
		{
			ClickElevatorOuterBtn(wControlID);
		}
		else if ((wControlID >= 1049) && (wControlID <= 1053))//当用户点击五部电梯内部的按钮的时候。
		{
			//改成只要有哪一个列表有按下的动作，那么记录下该动作。
			ClickElevatorInnerBtn(lpMyElevator, wControlID);//未知错误，消息会多次传入该listView中。不知什么情况。
		}
		else if ((wControlID >= 1054) && (wControlID <= 1068))//当开门关门按钮被按下的时候。
		{
			//只要有人按下关门键，开门键，全部电梯线程开始启动。
//			StartAllElevators(lpMyElevator, 5);//界面在初始化的时候消息经过此，窗口未初始化完成，子线程开启，窗口无法显示？
			ClickElevatorDoorBtn(lpMyElevator, wControlID);
		}
		else if ((wControlID >= 1070) && (wControlID <= 1074))
		{
			ClickElevatorAlarmBtn(lpMyElevator, wControlID);
		}
		switch (wControlID)
		{
		case IDC_ExcElevatorsBtn:
		{
//			StartAllElevators(lpMyElevator, 5);//开启全部电梯的线程。
//			for (int index = 0; index < 5; index++)
//			{
//				lpMyElevator[index]->ResumeElevatorThread();
//			}
//			lpMyElevator[0]->ResumeElevatorThread();
//			lpMyElevator[1]->ResumeElevatorThread();
			for (int index = 1006; index <= 1043; index++)//测试外部按钮全部按下。
			{
				ClickElevatorOuterBtn(index);
			}
		}
			return TRUE;
		default:
			return FALSE;
		}
	}
		return TRUE;
	case WM_CLOSE:
	{
		//关闭全部定时器。
		KillTimer(hwnd, ELEVATORTHREAD_TIMER1);
		KillTimer(hwnd, ELEVATORTHREAD_TIMER2);
		KillTimer(hwnd, ELEVATORTHREAD_TIMER3);
		KillTimer(hwnd, ELEVATORTHREAD_TIMER4);
		KillTimer(hwnd, ELEVATORTHREAD_TIMER5);
		KillTimer(hwnd, ELEVATORTHREAD_MAINTIMER);
		Elevator::ReleaseStaticElevator();//释放开辟的静态资源。
		//释放电梯资源。
		for (int index = 0; index < 5; index++)
		{
			delete lpMyElevator[index];
		}
		EndDialog(hwnd, 0);
	}
		return TRUE;
	default:
		break;
	}
	return FALSE;//未处理的消息转交给窗口处理。
}