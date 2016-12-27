#include"stdafx.h"
#include"MainDlg.h"

//Ҫ���ڸñ���ǰ��static����ô������Դ�ļ��м�ʹ��extern �ñ���Ҳ���ɼ���
Elevator* lpMyElevator[5] = { NULL };//ȫ�ֵĵ�����ָ�룬��ʾ�ô��������еĵ���ʵ����

//�����洰�ڹ��̺�����
BOOL CALLBACK ElevatorDispatch_DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//����Ӧ�ó���ͼ�ꡣ
		HICON hIcon = LoadIcon((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDI_ElevatorDispatch_Icon));
		SendMessage(hwnd, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);
		//��ʼ�����ݾ�̬�ĳ�Ա��
		Elevator::InitStaticElevator(hwnd, 20);//�ǳ���Ҫ��
		//��������ʵ����
		lpMyElevator[0] = new Elevator(hwnd, IDC_ElevatorList1, IDC_UserInsideRequest1, IDC_CurFloorEdit1, IDC_AlarmBtn1, IDC_OpenDoorBtn1, 20, ELEVATORTHREAD_TIMER1);
		lpMyElevator[1] = new Elevator(hwnd, IDC_ElevatorList2, IDC_UserInsideRequest2, IDC_CurFloorEdit2, IDC_AlarmBtn2, IDC_OpenDoorBtn2, 20, ELEVATORTHREAD_TIMER2);
		lpMyElevator[2] = new Elevator(hwnd, IDC_ElevatorList3, IDC_UserInsideRequest3, IDC_CurFloorEdit3, IDC_AlarmBtn3, IDC_OpenDoorBtn3, 20, ELEVATORTHREAD_TIMER3);
		lpMyElevator[3] = new Elevator(hwnd, IDC_ElevatorList4, IDC_UserInsideRequest4, IDC_CurFloorEdit4, IDC_AlarmBtn4, IDC_OpenDoorBtn4, 20, ELEVATORTHREAD_TIMER4);
		lpMyElevator[4] = new Elevator(hwnd, IDC_ElevatorList5, IDC_UserInsideRequest5, IDC_CurFloorEdit5, IDC_AlarmBtn5, IDC_OpenDoorBtn5, 20, ELEVATORTHREAD_TIMER5);
		//��ʼ��ʱ���������̶߳�ʱ����
		SetTimer(Elevator::GetMainDlgWnd(), ELEVATORTHREAD_MAINTIMER, 100, MainThreadTimerProc);//�������̼߳�ʱ���������ⲿ����
	}
		return TRUE;
	case WM_COMMAND:
	{
		WORD wControlID = LOWORD(wParam);
		if ((wControlID >= 1006) && (wControlID <= 1043))//�����û���������ⲿ�İ�ť��ʱ��
		{
			ClickElevatorOuterBtn(wControlID);
		}
		else if ((wControlID >= 1049) && (wControlID <= 1053))//���û�����岿�����ڲ��İ�ť��ʱ��
		{
			//�ĳ�ֻҪ����һ���б��а��µĶ�������ô��¼�¸ö�����
			ClickElevatorInnerBtn(lpMyElevator, wControlID);//δ֪������Ϣ���δ����listView�С���֪ʲô�����
		}
		else if ((wControlID >= 1054) && (wControlID <= 1068))//�����Ź��Ű�ť�����µ�ʱ��
		{
			//ֻҪ���˰��¹��ż������ż���ȫ�������߳̿�ʼ������
//			StartAllElevators(lpMyElevator, 5);//�����ڳ�ʼ����ʱ����Ϣ�����ˣ�����δ��ʼ����ɣ����߳̿����������޷���ʾ��
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
//			StartAllElevators(lpMyElevator, 5);//����ȫ�����ݵ��̡߳�
//			for (int index = 0; index < 5; index++)
//			{
//				lpMyElevator[index]->ResumeElevatorThread();
//			}
//			lpMyElevator[0]->ResumeElevatorThread();
//			lpMyElevator[1]->ResumeElevatorThread();
			for (int index = 1006; index <= 1043; index++)//�����ⲿ��ťȫ�����¡�
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
		//�ر�ȫ����ʱ����
		KillTimer(hwnd, ELEVATORTHREAD_TIMER1);
		KillTimer(hwnd, ELEVATORTHREAD_TIMER2);
		KillTimer(hwnd, ELEVATORTHREAD_TIMER3);
		KillTimer(hwnd, ELEVATORTHREAD_TIMER4);
		KillTimer(hwnd, ELEVATORTHREAD_TIMER5);
		KillTimer(hwnd, ELEVATORTHREAD_MAINTIMER);
		Elevator::ReleaseStaticElevator();//�ͷſ��ٵľ�̬��Դ��
		//�ͷŵ�����Դ��
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
	return FALSE;//δ�������Ϣת�������ڴ���
}