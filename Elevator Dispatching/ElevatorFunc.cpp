#include"stdafx.h"
#include"ElevatorFunc.h"

extern Elevator* lpMyElevator[5];
singleton* singleton::p = new singleton;
singleton* singleton::initance()
{
	return p;
}
//���û���������ⲿ��Ӧ��ťʱ�ĺ�����
bool ClickElevatorOuterBtn(WORD wControlID)
{
	switch (wControlID)
	{
		//�ⲿ��������ť��
	case IDC_1FloorUp:
	{
		Elevator::SetOuterRequestUp(1, true);
	}
		break;
	case IDC_2FloorUp:
	{
		Elevator::SetOuterRequestUp(2, true);
	}
		break;
	case IDC_3FloorUp:
	{
		Elevator::SetOuterRequestUp(3, true);
	}
		break;
	case IDC_4FloorUp:
	{
		Elevator::SetOuterRequestUp(4, true);
	}
		break;
	case IDC_5FloorUp:
	{
		Elevator::SetOuterRequestUp(5, true);
	}
		break;
	case IDC_6FloorUp:
	{
		Elevator::SetOuterRequestUp(6, true);
	}
		break;
	case IDC_7FloorUp:
	{
		Elevator::SetOuterRequestUp(7, true);
	}
		break;
	case IDC_8FloorUp:
	{
		Elevator::SetOuterRequestUp(8, true);
	}
		break;
	case IDC_9FloorUp:
	{
		Elevator::SetOuterRequestUp(9, true);
	}
		break;
	case IDC_10FloorUp:
	{
		Elevator::SetOuterRequestUp(10, true);
	}
		break;
	case IDC_11FloorUp:
	{
		Elevator::SetOuterRequestUp(11, true);
	}
		break;
	case IDC_12FloorUp:
	{
		Elevator::SetOuterRequestUp(12, true);
	}
		break;
	case IDC_13FloorUp:
	{
		Elevator::SetOuterRequestUp(13, true);
	}
		break;
	case IDC_14FloorUp:
	{
		Elevator::SetOuterRequestUp(14, true);
	}
		break;
	case IDC_15FloorUp:
	{
		Elevator::SetOuterRequestUp(15, true);
	}
		break;
	case IDC_16FloorUp:
	{
		Elevator::SetOuterRequestUp(16, true);
	}
		break;
	case IDC_17FloorUp:
	{
		Elevator::SetOuterRequestUp(17, true);
	}
		break;
	case IDC_18FloorUp:
	{
		Elevator::SetOuterRequestUp(18, true);
	}
		break;
	case IDC_19FloorUp:
	{
		Elevator::SetOuterRequestUp(19, true);
	}
		break;
		//�ⲿ��������ť��
	case IDC_20FloorDown:
	{
		Elevator::SetOuterRequestDown(20, true);
	}
		break;
	case IDC_19FloorDown:
	{
		Elevator::SetOuterRequestDown(19, true);
	}
		break;
	case IDC_18FloorDown:
	{
		Elevator::SetOuterRequestDown(18, true);
	}
		break;
	case IDC_17FloorDown:
	{
		Elevator::SetOuterRequestDown(17, true);
	}
		break;
	case IDC_16FloorDown:
	{
		Elevator::SetOuterRequestDown(16, true);
	}
		break;
	case IDC_15FloorDown:
	{
		Elevator::SetOuterRequestDown(15, true);
	}
		break;
	case IDC_14FloorDown:
	{
		Elevator::SetOuterRequestDown(14, true);
	}
		break;
	case IDC_13FloorDown:
	{
		Elevator::SetOuterRequestDown(13, true);
	}
		break;
	case IDC_12FloorDown:
	{
		Elevator::SetOuterRequestDown(12, true);
	}
		break;
	case IDC_11FloorDown:
	{
		Elevator::SetOuterRequestDown(11, true);
	}
		break;
	case IDC_10FloorDown:
	{
		Elevator::SetOuterRequestDown(10, true);
	}
		break;
	case IDC_9FloorDown:
	{
		Elevator::SetOuterRequestDown(9, true);
	}
		break;
	case IDC_8FloorDown:
	{
		Elevator::SetOuterRequestDown(8, true);
	}
		break;
	case IDC_7FloorDown:
	{
		Elevator::SetOuterRequestDown(7, true);
	}
		break;
	case IDC_6FloorDown:
	{
		Elevator::SetOuterRequestDown(6, true);
	}
		break;
	case IDC_5FloorDown:
	{
		Elevator::SetOuterRequestDown(5, true);
	}
		break;
	case IDC_4FloorDown:
	{
		Elevator::SetOuterRequestDown(4, true);
	}
		break;
	case IDC_3FloorDown:
	{
		Elevator::SetOuterRequestDown(3, true);
	}
		break;
	case IDC_2FloorDown:
	{
		Elevator::SetOuterRequestDown(2, true);
	}
		break;
	default:
		return false;
	}
	return true;
}

//���û���������ڲ���ť��ʱ��
/*��¼����һ�����ݵ��ڲ���ť�б�������Ȼ����
������Ϣ���ν���������������Բ��ڴ�������*/
bool ClickElevatorInnerBtn(Elevator** lpMyElevator, WORD wControlID)
{
	switch (wControlID)
	{
	case IDC_UserInsideRequest1:
	{
		lpMyElevator[0]->SetElevatorInnerBtnClick(true);
	}
		break;
	case IDC_UserInsideRequest2:
	{
		lpMyElevator[1]->SetElevatorInnerBtnClick(true);
	}
		break;
	case IDC_UserInsideRequest3:
	{
		lpMyElevator[2]->SetElevatorInnerBtnClick(true);
	}
		break;
	case IDC_UserInsideRequest4:
	{
		lpMyElevator[3]->SetElevatorInnerBtnClick(true);
	}
		break;
	case IDC_UserInsideRequest5:
	{
		lpMyElevator[4]->SetElevatorInnerBtnClick(true);
	}
		break;
	default:
		return false;
	}
	return true;
}


//���û����µ��ݵĿ����ż���ʱ�򣬿�ʼ���ڲ����ݵİ�ť״̬������
bool ClickElevatorDoorBtn(Elevator** lpMyElevator, WORD wControlID)
{
	switch (wControlID)
	{
		//�û������ż�֮��ķ�Ӧ-�����߳̿�����
	case IDC_CloseDoorBtn1:
	{
		lpMyElevator[0]->RefreshInsideRequest();
		if (lpMyElevator[0]->GetElevatorDoorState())
		{
			lpMyElevator[0]->ResumeElevatorThread();
		}
	}
		break;
	case IDC_CloseDoorBtn2:
	{
		lpMyElevator[1]->RefreshInsideRequest();
		if (lpMyElevator[1]->GetElevatorDoorState())
		{
			lpMyElevator[1]->ResumeElevatorThread();
		}
	}
		break;
	case IDC_CloseDoorBtn3:
	{
		lpMyElevator[2]->RefreshInsideRequest();
		if (lpMyElevator[2]->GetElevatorDoorState())
		{
			lpMyElevator[2]->ResumeElevatorThread();
		}
	}
		break;
	case IDC_CloseDoorBtn4:
	{
		lpMyElevator[3]->RefreshInsideRequest();
		if (lpMyElevator[3]->GetElevatorDoorState())
		{
			lpMyElevator[3]->ResumeElevatorThread();
		}
	}
		break;
	case IDC_CloseDoorBtn5:
	{
		lpMyElevator[4]->RefreshInsideRequest();
		if (lpMyElevator[4]->GetElevatorDoorState())
		{
			lpMyElevator[4]->ResumeElevatorThread();
		}
	}
		break;
		//�û������ż�������ǰ¥����������ô�����߳���ͣ�������������Ӧ��
	case IDC_OpenDoorBtn1:
	{
		if (lpMyElevator[0]->GetElevatorThreadWork())
		{
			lpMyElevator[0]->SuspendElevatorThread();//�����Ч��
		}
	}
		break;
	case IDC_OpenDoorBtn2:
	{
		if (lpMyElevator[1]->GetElevatorThreadWork())
		{
			lpMyElevator[1]->SuspendElevatorThread();
		}
	}
		break;
	case IDC_OpenDoorBtn3:
	{
		if (lpMyElevator[2]->GetElevatorThreadWork())
		{
			lpMyElevator[2]->SuspendElevatorThread();
		}
	}
		break;
	case IDC_OpenDoorBtn4:
	{
		if (lpMyElevator[3]->GetElevatorThreadWork())
		{
			lpMyElevator[3]->SuspendElevatorThread();
		}
	}
		break;
	case IDC_OpenDoorBtn5:
	{
		if (lpMyElevator[4]->GetElevatorThreadWork())
		{
			lpMyElevator[4]->SuspendElevatorThread();
		}
	}
		break;
	default:
		return false;
	}
	return true;
}

//���û����±�������ʱ�򡣹رոõ��ݵļ�ʱ����������ոõ��ݵ�ȫ������
bool ClickElevatorAlarmBtn(Elevator** lpMyElevator, WORD wControlID)
{
	switch (wControlID)
	{
	case IDC_AlarmBtn1:
	{
		if (!(lpMyElevator[0]->GetElevatorAlarmState()))//ԭ��δ���ڱ���״̬��
		{
			lpMyElevator[0]->ClearElevator();
			return TRUE;
		}
		lpMyElevator[0]->SetElevatorAlarmState(false);//�������״̬��
	}
		break;
	case IDC_AlarmBtn2:
	{
		if (!(lpMyElevator[1]->GetElevatorAlarmState()))
		{
			lpMyElevator[1]->ClearElevator();
			return TRUE;
		}
		lpMyElevator[1]->SetElevatorAlarmState(false);
	}
		break;
	case IDC_AlarmBtn3:
	{
		if (!(lpMyElevator[2]->GetElevatorAlarmState()))
		{
			lpMyElevator[2]->ClearElevator();
			return TRUE;
		}
		lpMyElevator[2]->SetElevatorAlarmState(false);
	}
		break;
	case IDC_AlarmBtn4:
	{
		if (!(lpMyElevator[3]->GetElevatorAlarmState()))
		{
			lpMyElevator[3]->ClearElevator();
			return TRUE;
		}
		lpMyElevator[3]->SetElevatorAlarmState(false);
	}
		break;
	case IDC_AlarmBtn5:
	{
		if (!(lpMyElevator[4]->GetElevatorAlarmState()))
		{
			lpMyElevator[4]->ClearElevator();
			return TRUE;
		}
		lpMyElevator[4]->SetElevatorAlarmState(false);
	}
		break;
	default:
		return false;
	}
	return true;
}


/*//��õ�ǰ���еĵ���������
//��������Elevator�ı�����
//�ú������ؿ��е��ݵ��������Լ���iStillElevatorBuff��������һ�����ݿ��С�iStillElevatorBuff��ΪNULLʱ��
//iStillElevatorBuffΪNULLʱ�����ؿ��е��ݵ�������
int GetStillElevators(Elevator** lpMyElevator, int* iStillElevatorBuff)
{
	int iStillElevatorCount = 0;
	//���ڵ��ݵ�������5.
	for (int ieIndex = 0; ieIndex < 5; ieIndex++)
	{
		if (lpMyElevator[ieIndex]->GetElevatorState() == ELEVATOR_STATE_STILL)//�����ǰ���ݴ��ھ�ֹ״̬��
		{
			if (iStillElevatorBuff != NULL)
			{
				iStillElevatorBuff[iStillElevatorCount] = ieIndex;//��¼������һ�����ݿ��С�
			}
			iStillElevatorCount++;
		}
	}
	return iStillElevatorCount;
}*/

//���߳��еļ�ʱ��������
VOID CALLBACK MainThreadTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	//��ʱˢ�²������ⲿ����
	singleton *t1 = singleton::initance();
	t1->DispatchOuterRequtst(lpMyElevator);

}


//�����ⲿ���󣬽������ⲿ����ת��Ϊ�����ڲ�����
//��Elevator������ⲿ�����������ɨ�衣��������
bool singleton::DispatchOuterRequtst(Elevator** lpMyElevator)
{
	int iUpingCount = 0, iDowningCount = 0, iStillCount = 0;//��¼��ʱ����״̬���ݵ�������
	int UpingElevators[6] = { NULL }, DowningElevators[6] = { NULL }, StillElevators[6] = { NULL };//��¼����״̬���ݵ��±ꡣ
	for (int index = 0; index < 5; index++)//��¼��ʱ�ĵ���״̬��
	{
		if (lpMyElevator[index]->GetElevatorAlarmState())//����ò����ݴ��ڱ���״̬��
		{
			continue;
		}
		switch (lpMyElevator[index]->GetElevatorState())
		{
		case ELEVATOR_STATE_UPING:
		{
			UpingElevators[iUpingCount] = index;
			iUpingCount++;
		}
			break;
		case ELEVATOR_STATE_STILL:
		{
			StillElevators[iStillCount] = index;
			iStillCount++;
		}
			break;
		case ELEVATOR_STATE_DOWNING:
		{
			DowningElevators[iDowningCount] = index;
			iDowningCount++;
		}
			break;
		default:
			break;
		}
	}
	//��¼�����״̬���ݵ�����֮�󣬿�ʼ�����ⲿ����
	//�����������е��ⲿ����
	for (int iRequestFloor = 1; iRequestFloor < 20; iRequestFloor++)
	{
		if (Elevator::GetOuterRequestUp(iRequestFloor))
		{
			//1.�����е��ݣ�����λ���Լ���¥��֮�¡�
			if (!SendToUnderFloorUping(lpMyElevator, iRequestFloor, iUpingCount, UpingElevators))//�������δ�ɹ�������������еĵ��ݡ�
			{
				//2.(1)���������еģ������е������Լ�����ֵ��С��(2)������ֹ�ģ������Լ��������ֵ��С��ȡ������ֵ��С���ǲ�����ִ������
				SendToDowningOrStill(lpMyElevator, iRequestFloor, iDowningCount, DowningElevators, iStillCount, StillElevators);
			}
		}
	}
	//�����������е��ⲿ����
	for (int iRequestFloor = 2; iRequestFloor < 21; iRequestFloor++)
	{
		if (Elevator::GetOuterRequestDown(iRequestFloor))
		{
			//1.�����е��ݣ�����λ���Լ���¥��֮�ϡ�
			if (!SendToAboveFloorDowning(lpMyElevator, iRequestFloor, iDowningCount, DowningElevators))//�������δ�ɹ�����������½��ĵ��ݡ�
			{
				//2.(1)���������еģ������ж������Լ�����ֵ��С��(2)�Ҿ�ֹ�ģ������Լ�����ֵ��С��ȡ�����о���ֵ��С���ǲ�����ִ������
				SendToUpingOrStill(lpMyElevator, iRequestFloor, iUpingCount, UpingElevators, iStillCount, StillElevators);
			}
		}
	}
	return true;
}


//���ⲿ�����͸��Լ�¥�����������ĵ��ݡ�
//����true��ʾ����ɹ����䡣
//iRequestFloor ���������¥�㣬iUpingCount��ǰ���е����������ĵ�������lpUpingElevators���Ǽ������ݡ�
bool SendToUnderFloorUping(Elevator** lpMyElevator, int iRequestFloor, int iUpingCount, int* lpUpingElevators)
{
	//Ҫ�ж�iUpingCount�Ƿ�Ϊ�㣬��0�����������еĵ��ݣ�ֱ�ӷ���false��
	if (iUpingCount == 0)
	{
		return false;//���񽫽�����һ������
	}
	int iElevatorCount = 0;//���������ĵ�������
	int iElevatorsIndex[6] = { NULL };//���ط��������ĵ����±ꡣ
	int iDistance[6] = { NULL };//��¼����¥������ݵ�ǰ¥��ľ��롣
	//�����е��ݡ���ô�����ⲿ����¥��֮�µ����е��ݡ�
	for (int index = 0; index < iUpingCount; index++)
	{
		if ((lpMyElevator[lpUpingElevators[index]]->GetCurFloor()) < iRequestFloor)//�����ⲿ����¥��֮�µ����е��ݡ�
		{
			iElevatorsIndex[iElevatorCount] = lpUpingElevators[index];//��¼���������ĵ��ݵ��±ꡣ
			iDistance[iElevatorCount] = iRequestFloor - (lpMyElevator[lpUpingElevators[index]]->GetCurFloor());//��¼���롣
			iElevatorCount++;
		}
	}
	//������������ĵ�����Ϊ0.
	if (iElevatorCount == 0)
	{
		return false;
	}

	//���������ĵ������ж������ô������С�������һ����
	int ieIndex = 0;//��С�����±ꡣ
	for (; ieIndex < iElevatorCount; ieIndex++)
	{
		if ((lpMyElevator[iElevatorsIndex[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
		{
			break;
		}
	}
	//Ҫ���Ҳ�������6�������ĵ�����ô������ⲿ�����׸���һ��ȥ���㡣
	if (ieIndex == iElevatorCount)
	{
		return false;
	}
	int iMinDistance = iDistance[ieIndex];//��һ����������6�������ĵ��ݾ���Ϊ��̾��롣
	for (int index = ieIndex + 1; index < iElevatorCount; index++)
	{
		if ((iDistance[index] < iMinDistance) && 
			((lpMyElevator[iElevatorsIndex[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM))//�ҵ���С���롣ͬʱ�ڲ������ܶ���������
		{
			ieIndex = index;
			iMinDistance = iDistance[index];
		}
	}
	//�ҵ���С��������±���±�֮��,�Ҹ���С�ڵ���6�����õ��ݷ�������
	lpMyElevator[iElevatorsIndex[ieIndex]]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_UPING);
	return true;
}

//2.(1)���������еģ������е������Լ�����ֵ��С��(2)������ֹ�ģ������Լ��������ֵ��С��ȡ������ֵ��С���ǲ�����ִ������
bool SendToDowningOrStill(Elevator** lpMyElevator, int iRequestFloor, int iDowningCount, int* lpDowningElevators, int iStillCount, int* lpStillElevators)
{
	if ((iDowningCount == 0) && (iStillCount == 0))
	{
		return false;//��ǰû�пɵ��õĵ��ݡ�
	}
	//1.�ҳ����е��������е��߾��Լ��������ֵ��С��¥�㡣
	int iDowningIndex = -1;//�洢���������ĵ����±ꡣ
	int iDowningDistance = 100;//����20�㣬�����ܳ���100.
	if (iDowningCount != 0)
	{
		//Ҫ��������Ϊ�㣬��ô�ҳ���һ�����������������ĵ��ݡ�
		int ieIndex = 0;
/*		for (; ieIndex < iDowningCount; ieIndex++)
		{
			if ((lpMyElevator[lpDowningElevators[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
			{
			break;//�ҵ�������ѭ����
			}
		}
		if (ieIndex != iDowningCount)
		{
			iDowningDistance = abs((lpMyElevator[lpDowningElevators[ieIndex]]->GetMinInnerRequirementFloor()) - iRequestFloor);//���е������Լ���С�ľ���ֵ���롣
			iDowningIndex = lpDowningElevators[ieIndex];//��¼�µ�һ�����������������ĵ����±ꡣ
			for (int index = ieIndex + 1; index < iDowningCount; index++)
			{
				//���е���������¥��֮�
				if ((abs((lpMyElevator[lpDowningElevators[index]]->GetMinInnerRequirementFloor()) - iRequestFloor) < iDowningDistance) &&
				( (lpMyElevator[lpDowningElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM ) )//�����������������£��ҵ�������С��¥���±ꡣ
				{
					iDowningDistance = abs((lpMyElevator[lpDowningElevators[index]]->GetMinInnerRequirementFloor()) - iRequestFloor);
					iDowningIndex = lpDowningElevators[index];//��¼�¾���ֵ��С���±ꡣ
				}
			}
		}*/
		for (; ieIndex < iDowningCount; ieIndex++)
		{
			if ((lpMyElevator[lpDowningElevators[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM)
			{
				if ((lpMyElevator[lpDowningElevators[ieIndex]]->GetCurFloor()) < iRequestFloor)//�ⲿ�������У������Լ�֮���������еĵ��ݣ���Ϊ�����¥�����������¥�������
				{
					break;//�ҵ�������ѭ����
				}
			}
		}
		if (ieIndex != iDowningCount)
		{
			iDowningDistance = iRequestFloor - (lpMyElevator[lpDowningElevators[ieIndex]]->GetMinInnerRequirementFloor());//���е������Լ���С�ľ���ֵ���롣
			iDowningIndex = lpDowningElevators[ieIndex];//��¼�µ�һ�����������������ĵ����±ꡣ
			for (int index = ieIndex + 1; index < iDowningCount; index++)
			{
				//���е���������¥��֮�
				if (((iRequestFloor - (lpMyElevator[lpDowningElevators[index]]->GetMinInnerRequirementFloor())) < iDowningDistance) &&
					((lpMyElevator[lpDowningElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM))//�����������������£��ҵ�������С��¥���±ꡣ
				{
					iDowningDistance = iRequestFloor - (lpMyElevator[lpDowningElevators[index]]->GetMinInnerRequirementFloor());
					iDowningIndex = lpDowningElevators[index];//��¼�¾���ֵ��С���±ꡣ
				}
			}
		}
	}
	//2.�ҳ���ֹ�����о��Լ��������ֵ��С��¥�㡣
	int iStillIndex = -1;//�洢���������ĵ����±ꡣ
	int iStillDistance = 100;
	if (iStillCount != 0)
	{
		//Ҫ��������Ϊ�㣬��ô�ҳ���һ������������������¥�㡣
		int ieIndex = 0;
		for (; ieIndex < iStillCount; ieIndex++)
		{
			if ( (lpMyElevator[lpStillElevators[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
			{
				break;
			}
		}
		//���ǵ��ݿ���ȫ�����ص������
		if (ieIndex == iStillCount)
		{
			return false;//����ȫ�����أ����ⲿ�������ʧ�ܣ��ȴ���һ�η��䡣
		}
		iStillDistance = abs((lpMyElevator[lpStillElevators[ieIndex]]->GetCurFloor()) - iRequestFloor);//��ǰ����ͣ��¥�����Լ�¥��ľ���ֵ��
		iStillIndex = lpStillElevators[ieIndex];
		for (int index = ieIndex + 1; index < iStillCount; index++)
		{
			//��ǰ¥��������¥��֮�
			if ((abs((lpMyElevator[lpStillElevators[index]]->GetCurFloor()) - iRequestFloor) < iStillDistance) &&
				((lpMyElevator[lpStillElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM) )
			{
				iStillDistance = abs((lpMyElevator[lpStillElevators[index]]->GetCurFloor()) - iRequestFloor);
				iStillIndex = lpStillElevators[index];//��¼�¾���ֵ��С���±ꡣ
			}
		}
	}
	//���û���������еĵ��ݡ�
	if (iDowningIndex == -1)//ֻ��ѡһ����������½�����û��һ������������
	{
		if (iStillDistance == 0)//��Ϊ�����п��ܾ�ͣ������¥�㡣�Ծ�ͣ���ڵ�ǰ¥����������ô�Ͳ���Ϊ����Ϊ�û�����ֱ�ӽ�����ݡ�
		{
			Elevator::SetOuterRequestUp(iRequestFloor, false);
			return true;
		}
		if (iStillIndex == -1)
		{
			return false;//����ֹ�����ֲ�����������Ҫ����ô���������䲻�ɹ���
		}
		lpMyElevator[iStillIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_UPING);
	}
	else if (iStillIndex == -1)
	{
		lpMyElevator[iDowningIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_UPING);
	}
	else//�����к;�ֹ�ĵ����ж������������ĵ��ݡ�
	{
		if (iDowningDistance < iStillDistance)//���ҳ���������������ѡȡ��
		{
			lpMyElevator[iDowningIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_UPING);
		}
		else
		{
			if (iStillDistance == 0)
			{
				Elevator::SetOuterRequestUp(iRequestFloor, false);
				return true;
			}
			lpMyElevator[iStillIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_UPING);
		}
	}
	return true;
}

//���ⲿ�����͸��Լ�¥�������½��ĵ��ݡ�
//����true��ʾ����ɹ����䡣
//iRequestFloor ���������¥�㣬iDowningCount��ǰ���е������½��ĵ�������lpDowningElevators���Ǽ������ݵ��±ꡣ
bool SendToAboveFloorDowning(Elevator** lpMyElevator, int iRequestFloor, int iDowningCount, int* lpDowningElevators)
{
	if (iDowningCount == 0)//�����½��ĵ�����Ϊ0.
	{
		return false;
	}
	int iElevatorCount = 0;//���������ĵ�������
	int iElevatorsIndex[6] = { NULL };//���ط��������ĵ����±ꡣ
	int iDistance[6] = { NULL };//��¼����¥������ݵ�ǰ¥��ľ��롣
	//�����е��ݣ���ô���ⲿ����¥��֮�ϵ����е��ݡ�
	for (int index = 0; index < iDowningCount; index++)
	{
		if ((lpMyElevator[lpDowningElevators[index]]->GetCurFloor()) > iRequestFloor)
		{
			iElevatorsIndex[iElevatorCount] = lpDowningElevators[index];//��¼���������ĵ��ݵ��±ꡣ
			iDistance[iElevatorCount] = (lpMyElevator[lpDowningElevators[index]]->GetCurFloor()) - iRequestFloor;
			iElevatorCount++;
		}
	}
	//������ϵ��ݵ�������Ϊ0.
	if (iElevatorCount == 0)
	{
		return false;
	}
	
	int ieIndex = 0;//��С�����±ꡣ
	for (; ieIndex < iElevatorCount; ieIndex++)
	{
		if ((lpMyElevator[iElevatorsIndex[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
		{
			break;
		}
	}
	//Ҫ���Ҳ����ڲ����󲻳������ĵ��ݡ�
	if (ieIndex == iElevatorCount)
	{
		return false;
	}
	//���������ĵ������ж������ô������С�������һ����
	int iMinDistance = iDistance[ieIndex];
	for (int index = ieIndex + 1; index < iElevatorCount; index++)
	{
		//��������������������£�����Ҫ��С��
		if ( (iMinDistance > iDistance[index]) && 
			((lpMyElevator[iElevatorsIndex[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM))
		{
			iMinDistance = iDistance[index];
			ieIndex = index;
		}
	}
	//�ҵ�������С�ĵ��ݺ�,����������Ҫ�󣬷�������
	lpMyElevator[iElevatorsIndex[ieIndex]]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_DOWNING);
	return true;
}

//2.(1)���������еģ������ж������Լ�����ֵ��С��(2)�Ҿ�ֹ�ģ������Լ�����ֵ��С��ȡ�����о���ֵ��С���ǲ�����ִ������
bool SendToUpingOrStill(Elevator** lpMyElevator, int iRequestFloor, int iUpingCount, int* lpUpingElevators, int iStillCount, int* lpStillElevators)
{
	if ((iUpingCount == 0) && (iStillCount == 0))//��ǰû�пɵ��õĵ��ݡ�
	{
		return false;
	}
	//�пɵ��õĵ��ݡ�
	//1.�ҳ����е��������ж��޾�����¥�����С���롣
	int iUpingIndex = -1;//��¼��С������ݵ��±ꡣ
	int iUpingDistance = 100;//��¼���ߵľ��롣
	//�ҳ�����״̬����ֵ��С���±ꡣ
	if (iUpingCount != 0)
	{
		//����������Ϊ0����ô�ҵ���һ���������������±���±ꡣ
		int ieIndex = 0;
		for (; ieIndex < iUpingCount; ieIndex++)
		{
			if ((lpMyElevator[lpUpingElevators[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
			{
				if ((lpMyElevator[lpUpingElevators[ieIndex]]->GetCurFloor())>iRequestFloor)
				{//�ⲿ�����������еģ���ʱҪ�ҵ�ǰ¥�����Լ�֮�ϵ����е��ݣ���Ϊ���������е��ݵĶ��޿���������¥�������
					break;
				}
			}
		}
		//�����ҵ��������������±��
		if (ieIndex != iUpingCount)
		{
/*			iUpingIndex = lpUpingElevators[ieIndex];
			iUpingDistance = abs((lpMyElevator[lpUpingElevators[ieIndex]])->GetCurFloor() - iRequestFloor);
			for (int index = ieIndex + 1; index < iUpingCount; index++)
			{
				//���ж���������¥��֮�
				if (iUpingDistance >(abs(((lpMyElevator[lpUpingElevators[index]])->GetMaxInnerRequirementFloor()) - iRequestFloor)) &&
					((lpMyElevator[lpUpingElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM))
					//��������������Ϣ��ǰ���£�ʹ¥��ľ���ֵ������С��
				{
					iUpingDistance = abs(((lpMyElevator[lpUpingElevators[index]])->GetMaxInnerRequirementFloor()) - iRequestFloor);
					iUpingIndex = lpUpingElevators[index];
				}
			}*/
			iUpingIndex = lpUpingElevators[ieIndex];
			iUpingDistance = (lpMyElevator[lpUpingElevators[ieIndex]])->GetCurFloor() - iRequestFloor;
			for (int index = ieIndex + 1; index < iUpingCount; index++)
			{
				if (iUpingDistance >(((lpMyElevator[lpUpingElevators[index]])->GetMaxInnerRequirementFloor()) - iRequestFloor) &&
					((lpMyElevator[lpUpingElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM))
				{
					iUpingDistance = ((lpMyElevator[lpUpingElevators[index]])->GetMaxInnerRequirementFloor()) - iRequestFloor;
					iUpingIndex = lpUpingElevators[index];
				}
			}
		}
	}
	//�ҳ���ֹ״̬����ֵ��С���±ꡣ
	int iStillIndex = -1;//��¼��С������ݵ��±ꡣ
	int iStillDistance = 100;//��¼���ߵ���С���롣
	//�ҳ���ֹ״̬����ֵ��С���±ꡣ
	if (iStillCount != 0)
	{
		//��ֹ��������Ϊ0����ô�ҵ���һ�������������ĵ����±���±ꡣ
		int ieIndex = 0;
		for (; ieIndex < iStillCount; ieIndex++)
		{
			if ((lpMyElevator[lpStillElevators[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
			{
				break;
			}
		}
		//������ȫ�����ص�ʱ������Ҫ�Ӹ��жϡ���ʱ�ⲿ������Ҫ�ȴ������ڲ����������ٺ����ת��Ϊ�ڲ�����
		if (ieIndex == iStillCount)
		{
			return false;//���������ĵ���ȫ�����أ��ⲿ�������ʧ�ܣ����ⲿ����ȴ���һ�η��䡣
		}
		iStillIndex = lpStillElevators[ieIndex];
		iStillDistance = abs((lpMyElevator[lpStillElevators[ieIndex]]->GetCurFloor()) - iRequestFloor);
		for (int index = ieIndex + 1; index < iStillCount; index++)
		{
			//���ݵ�ǰ¥��������¥��֮�
			if ( (abs((lpMyElevator[lpStillElevators[index]]->GetCurFloor() - iRequestFloor)) < iStillDistance) && 
				( (lpMyElevator[lpStillElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM) )
			{
				iStillDistance = abs((lpMyElevator[lpStillElevators[index]]->GetCurFloor() - iRequestFloor));
				iStillIndex = lpStillElevators[index];
			}
		}
	}
	//�����С����ֵ��¥��󣬿�ʼ��������
	if (iUpingIndex == -1)//���е��ݲ�����Ҫ��
	{
		if (iStillDistance == 0)
		{
			Elevator::SetOuterRequestDown(iRequestFloor, false);//�����¥��պ�����䵽�ĵ��ݵĵ�ǰ¥����ͬ��
			return true;
		}
		if (iStillIndex == -1)
		{
			return false;//��ֹ����Ҳ������Ҫ��
		}
		lpMyElevator[iStillIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_DOWNING);
	}
	else if (iStillIndex == -1)
	{
		lpMyElevator[iUpingIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_DOWNING);
	}
	else//�Ӷ������ҳ�����ֵ��С����һ����������������к;�ֹ�ĵ����ж������������ĵ��ݡ�
	{
		if (iUpingDistance > iStillDistance)
		{
			if (iStillDistance ==0 )
			{
				Elevator::SetOuterRequestDown(iRequestFloor, false);//�����¥��պ�����䵽�ĵ��ݵĵ�ǰ¥����ͬ��
				return true;
			}
			lpMyElevator[iStillIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_DOWNING);
		}
		else
		{
			lpMyElevator[iUpingIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_DOWNING);
		}
	}
	return true;
}

//�����岿���ݵ�ȫ���̡߳�
/*bool StartAllElevators(Elevator** lpMyElevator, int iElevatorCount)
{
	for (int index = 0; index < iElevatorCount; index++)
	{
		lpMyElevator[index]->ResumeElevatorThread();
	}
	return true;
}*/