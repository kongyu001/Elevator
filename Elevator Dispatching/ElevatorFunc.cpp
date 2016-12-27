#include"stdafx.h"
#include"ElevatorFunc.h"

extern Elevator* lpMyElevator[5];
singleton* singleton::p = new singleton;
singleton* singleton::initance()
{
	return p;
}
//当用户点击电梯外部响应按钮时的函数。
bool ClickElevatorOuterBtn(WORD wControlID)
{
	switch (wControlID)
	{
		//外部上行需求按钮。
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
		//外部下行需求按钮。
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

//当用户点击电梯内部按钮的时候。
/*记录下哪一部电梯的内部按钮有被按过，然后处理。
由于消息会多次进入这个函数，所以不在此做处理*/
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


//当用户按下电梯的开关门键的时候，开始对内部电梯的按钮状态做处理。
bool ClickElevatorDoorBtn(Elevator** lpMyElevator, WORD wControlID)
{
	switch (wControlID)
	{
		//用户按关门键之后的反应-电梯线程开启。
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
		//用户按开门键，若当前楼层有需求，那么电梯线程暂停，否则电梯无响应。
	case IDC_OpenDoorBtn1:
	{
		if (lpMyElevator[0]->GetElevatorThreadWork())
		{
			lpMyElevator[0]->SuspendElevatorThread();//这句无效。
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

//当用户按下报警键的时候。关闭该电梯的计时器，并且清空该电梯的全部任务。
bool ClickElevatorAlarmBtn(Elevator** lpMyElevator, WORD wControlID)
{
	switch (wControlID)
	{
	case IDC_AlarmBtn1:
	{
		if (!(lpMyElevator[0]->GetElevatorAlarmState()))//原来未处于报警状态。
		{
			lpMyElevator[0]->ClearElevator();
			return TRUE;
		}
		lpMyElevator[0]->SetElevatorAlarmState(false);//解除报警状态。
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


/*//获得当前空闲的电梯数量。
//传入所有Elevator的变量。
//该函数返回空闲电梯的数量，以及用iStillElevatorBuff标明是哪一部电梯空闲。iStillElevatorBuff不为NULL时。
//iStillElevatorBuff为NULL时仅返回空闲电梯的数量。
int GetStillElevators(Elevator** lpMyElevator, int* iStillElevatorBuff)
{
	int iStillElevatorCount = 0;
	//现在电梯的数量是5.
	for (int ieIndex = 0; ieIndex < 5; ieIndex++)
	{
		if (lpMyElevator[ieIndex]->GetElevatorState() == ELEVATOR_STATE_STILL)//如果当前电梯处于静止状态。
		{
			if (iStillElevatorBuff != NULL)
			{
				iStillElevatorBuff[iStillElevatorCount] = ieIndex;//记录下是哪一部电梯空闲。
			}
			iStillElevatorCount++;
		}
	}
	return iStillElevatorCount;
}*/

//主线程中的计时器函数。
VOID CALLBACK MainThreadTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	//定时刷新并分配外部需求。
	singleton *t1 = singleton::initance();
	t1->DispatchOuterRequtst(lpMyElevator);

}


//分配外部需求，将电梯外部需求转化为电梯内部需求。
//对Elevator里面的外部需求数组进行扫描。分配任务。
bool singleton::DispatchOuterRequtst(Elevator** lpMyElevator)
{
	int iUpingCount = 0, iDowningCount = 0, iStillCount = 0;//记录此时各种状态电梯的数量。
	int UpingElevators[6] = { NULL }, DowningElevators[6] = { NULL }, StillElevators[6] = { NULL };//记录各种状态电梯的下标。
	for (int index = 0; index < 5; index++)//记录此时的电梯状态。
	{
		if (lpMyElevator[index]->GetElevatorAlarmState())//如果该部电梯处于报警状态。
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
	//记录完各个状态电梯的数量之后，开始分配外部需求。
	//首先满足上行的外部需求。
	for (int iRequestFloor = 1; iRequestFloor < 20; iRequestFloor++)
	{
		if (Elevator::GetOuterRequestUp(iRequestFloor))
		{
			//1.找上行电梯，并且位于自己的楼层之下。
			if (!SendToUnderFloorUping(lpMyElevator, iRequestFloor, iUpingCount, UpingElevators))//如果任务未成功分配给正在上行的电梯。
			{
				//2.(1)找正在下行的，且下行底线离自己绝对值最小；(2)找正静止的，且离自己距离绝对值最小；取二者中值较小的那部电梯执行任务。
				SendToDowningOrStill(lpMyElevator, iRequestFloor, iDowningCount, DowningElevators, iStillCount, StillElevators);
			}
		}
	}
	//再来满足下行的外部需求。
	for (int iRequestFloor = 2; iRequestFloor < 21; iRequestFloor++)
	{
		if (Elevator::GetOuterRequestDown(iRequestFloor))
		{
			//1.找下行电梯，并且位于自己的楼层之上。
			if (!SendToAboveFloorDowning(lpMyElevator, iRequestFloor, iDowningCount, DowningElevators))//如果任务未成功分配给正在下降的电梯。
			{
				//2.(1)找正在上行的，且上行顶限离自己绝对值最小；(2)找静止的，且离自己绝对值最小；取二者中绝对值较小的那部电梯执行任务。
				SendToUpingOrStill(lpMyElevator, iRequestFloor, iUpingCount, UpingElevators, iStillCount, StillElevators);
			}
		}
	}
	return true;
}


//将外部需求发送给自己楼下正在上升的电梯。
//返回true表示任务成功分配。
//iRequestFloor 发出请求的楼层，iUpingCount当前已有的正在上升的电梯数，lpUpingElevators是那几部电梯。
bool SendToUnderFloorUping(Elevator** lpMyElevator, int iRequestFloor, int iUpingCount, int* lpUpingElevators)
{
	//要判断iUpingCount是否为零，是0，无正在上行的电梯，直接返回false。
	if (iUpingCount == 0)
	{
		return false;//任务将交给下一级处理。
	}
	int iElevatorCount = 0;//符合条件的电梯数。
	int iElevatorsIndex[6] = { NULL };//承载符合条件的电梯下标。
	int iDistance[6] = { NULL };//记录需求楼层与电梯当前楼层的距离。
	//有上行电梯。那么找在外部需求楼层之下的上行电梯。
	for (int index = 0; index < iUpingCount; index++)
	{
		if ((lpMyElevator[lpUpingElevators[index]]->GetCurFloor()) < iRequestFloor)//找在外部需求楼层之下的上行电梯。
		{
			iElevatorsIndex[iElevatorCount] = lpUpingElevators[index];//记录符合条件的电梯的下标。
			iDistance[iElevatorCount] = iRequestFloor - (lpMyElevator[lpUpingElevators[index]]->GetCurFloor());//记录距离。
			iElevatorCount++;
		}
	}
	//如果符合条件的电梯数为0.
	if (iElevatorCount == 0)
	{
		return false;
	}

	//符合条件的电梯数有多个，那么返回最小距离的那一个。
	int ieIndex = 0;//最小距离下标。
	for (; ieIndex < iElevatorCount; ieIndex++)
	{
		if ((lpMyElevator[iElevatorsIndex[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
		{
			break;
		}
	}
	//要是找不到少于6人条件的电梯那么将这个外部需求抛给下一级去满足。
	if (ieIndex == iElevatorCount)
	{
		return false;
	}
	int iMinDistance = iDistance[ieIndex];//第一个满足少于6人条件的电梯距离为最短距离。
	for (int index = ieIndex + 1; index < iElevatorCount; index++)
	{
		if ((iDistance[index] < iMinDistance) && 
			((lpMyElevator[iElevatorsIndex[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM))//找到最小距离。同时内部需求不能多于六个。
		{
			ieIndex = index;
			iMinDistance = iDistance[index];
		}
	}
	//找到最小距离电梯下标的下标之后,且负荷小于等于6，给该电梯分配任务。
	lpMyElevator[iElevatorsIndex[ieIndex]]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_UPING);
	return true;
}

//2.(1)找正在下行的，且下行底线离自己绝对值最小；(2)找正静止的，且离自己距离绝对值最小；取二者中值较小的那部电梯执行任务。
bool SendToDowningOrStill(Elevator** lpMyElevator, int iRequestFloor, int iDowningCount, int* lpDowningElevators, int iStillCount, int* lpStillElevators)
{
	if ((iDowningCount == 0) && (iStillCount == 0))
	{
		return false;//当前没有可调用的电梯。
	}
	//1.找出下行电梯中下行底线距自己距离绝对值最小的楼层。
	int iDowningIndex = -1;//存储符合条件的电梯下标。
	int iDowningDistance = 100;//电梯20层，不可能超过100.
	if (iDowningCount != 0)
	{
		//要是总数不为零，那么找出第一个满足需求数条件的电梯。
		int ieIndex = 0;
/*		for (; ieIndex < iDowningCount; ieIndex++)
		{
			if ((lpMyElevator[lpDowningElevators[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
			{
			break;//找到后跳出循环。
			}
		}
		if (ieIndex != iDowningCount)
		{
			iDowningDistance = abs((lpMyElevator[lpDowningElevators[ieIndex]]->GetMinInnerRequirementFloor()) - iRequestFloor);//下行底线离自己最小的绝对值距离。
			iDowningIndex = lpDowningElevators[ieIndex];//记录下第一个满足需求数条件的电梯下标。
			for (int index = ieIndex + 1; index < iDowningCount; index++)
			{
				//下行底限与需求楼层之差。
				if ((abs((lpMyElevator[lpDowningElevators[index]]->GetMinInnerRequirementFloor()) - iRequestFloor) < iDowningDistance) &&
				( (lpMyElevator[lpDowningElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM ) )//在满足需求数条件下，找到距离最小的楼层下标。
				{
					iDowningDistance = abs((lpMyElevator[lpDowningElevators[index]]->GetMinInnerRequirementFloor()) - iRequestFloor);
					iDowningIndex = lpDowningElevators[index];//记录下绝对值最小的下标。
				}
			}
		}*/
		for (; ieIndex < iDowningCount; ieIndex++)
		{
			if ((lpMyElevator[lpDowningElevators[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM)
			{
				if ((lpMyElevator[lpDowningElevators[ieIndex]]->GetCurFloor()) < iRequestFloor)//外部需求上行，找在自己之下正在下行的电梯，因为其底线楼层可能离需求楼层最近。
				{
					break;//找到后跳出循环。
				}
			}
		}
		if (ieIndex != iDowningCount)
		{
			iDowningDistance = iRequestFloor - (lpMyElevator[lpDowningElevators[ieIndex]]->GetMinInnerRequirementFloor());//下行底线离自己最小的绝对值距离。
			iDowningIndex = lpDowningElevators[ieIndex];//记录下第一个满足需求数条件的电梯下标。
			for (int index = ieIndex + 1; index < iDowningCount; index++)
			{
				//下行底限与需求楼层之差。
				if (((iRequestFloor - (lpMyElevator[lpDowningElevators[index]]->GetMinInnerRequirementFloor())) < iDowningDistance) &&
					((lpMyElevator[lpDowningElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM))//在满足需求数条件下，找到距离最小的楼层下标。
				{
					iDowningDistance = iRequestFloor - (lpMyElevator[lpDowningElevators[index]]->GetMinInnerRequirementFloor());
					iDowningIndex = lpDowningElevators[index];//记录下绝对值最小的下标。
				}
			}
		}
	}
	//2.找出静止电梯中距自己距离绝对值最小的楼层。
	int iStillIndex = -1;//存储符合条件的电梯下标。
	int iStillDistance = 100;
	if (iStillCount != 0)
	{
		//要是总数不为零，那么找出第一个满足需求数条件的楼层。
		int ieIndex = 0;
		for (; ieIndex < iStillCount; ieIndex++)
		{
			if ( (lpMyElevator[lpStillElevators[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
			{
				break;
			}
		}
		//考虑电梯可能全部满载的情况。
		if (ieIndex == iStillCount)
		{
			return false;//电梯全部满载，该外部需求分配失败，等待下一次分配。
		}
		iStillDistance = abs((lpMyElevator[lpStillElevators[ieIndex]]->GetCurFloor()) - iRequestFloor);//当前电梯停靠楼层与自己楼层的绝对值。
		iStillIndex = lpStillElevators[ieIndex];
		for (int index = ieIndex + 1; index < iStillCount; index++)
		{
			//当前楼层与需求楼层之差。
			if ((abs((lpMyElevator[lpStillElevators[index]]->GetCurFloor()) - iRequestFloor) < iStillDistance) &&
				((lpMyElevator[lpStillElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM) )
			{
				iStillDistance = abs((lpMyElevator[lpStillElevators[index]]->GetCurFloor()) - iRequestFloor);
				iStillIndex = lpStillElevators[index];//记录下绝对值最小的下标。
			}
		}
	}
	//如果没有正在下行的电梯。
	if (iDowningIndex == -1)//只能选一个的情况。下降电梯没有一个符合条件。
	{
		if (iStillDistance == 0)//因为电梯有可能就停在需求楼层。对就停留在当前楼层的情况，那么就不作为，因为用户可以直接进入电梯。
		{
			Elevator::SetOuterRequestUp(iRequestFloor, false);
			return true;
		}
		if (iStillIndex == -1)
		{
			return false;//而静止电梯又不满足需求数要求。那么这次任务分配不成功。
		}
		lpMyElevator[iStillIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_UPING);
	}
	else if (iStillIndex == -1)
	{
		lpMyElevator[iDowningIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_UPING);
	}
	else//即下行和静止的电梯中都有满足条件的电梯。
	{
		if (iDowningDistance < iStillDistance)//从找出的两个距离里面选取。
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

//将外部需求发送给自己楼上正在下降的电梯。
//返回true表示任务成功分配。
//iRequestFloor 发出请求的楼层，iDowningCount当前已有的正在下降的电梯数，lpDowningElevators是那几部电梯的下标。
bool SendToAboveFloorDowning(Elevator** lpMyElevator, int iRequestFloor, int iDowningCount, int* lpDowningElevators)
{
	if (iDowningCount == 0)//正在下降的电梯数为0.
	{
		return false;
	}
	int iElevatorCount = 0;//符合条件的电梯数。
	int iElevatorsIndex[6] = { NULL };//承载符合条件的电梯下标。
	int iDistance[6] = { NULL };//记录需求楼层与电梯当前楼层的距离。
	//有下行电梯，那么找外部需求楼层之上的下行电梯。
	for (int index = 0; index < iDowningCount; index++)
	{
		if ((lpMyElevator[lpDowningElevators[index]]->GetCurFloor()) > iRequestFloor)
		{
			iElevatorsIndex[iElevatorCount] = lpDowningElevators[index];//记录符合条件的电梯的下标。
			iDistance[iElevatorCount] = (lpMyElevator[lpDowningElevators[index]]->GetCurFloor()) - iRequestFloor;
			iElevatorCount++;
		}
	}
	//如果符合电梯的条件数为0.
	if (iElevatorCount == 0)
	{
		return false;
	}
	
	int ieIndex = 0;//最小距离下标。
	for (; ieIndex < iElevatorCount; ieIndex++)
	{
		if ((lpMyElevator[iElevatorsIndex[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
		{
			break;
		}
	}
	//要是找不到内部需求不超过六的电梯。
	if (ieIndex == iElevatorCount)
	{
		return false;
	}
	//符合条件的电梯数有多个，那么返回最小距离的那一个。
	int iMinDistance = iDistance[ieIndex];
	for (int index = ieIndex + 1; index < iElevatorCount; index++)
	{
		//在满足需求个数的条件下，距离要最小。
		if ( (iMinDistance > iDistance[index]) && 
			((lpMyElevator[iElevatorsIndex[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM))
		{
			iMinDistance = iDistance[index];
			ieIndex = index;
		}
	}
	//找到距离最小的电梯后,需求数满足要求，分配任务。
	lpMyElevator[iElevatorsIndex[ieIndex]]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_DOWNING);
	return true;
}

//2.(1)找正在上行的，且上行顶限离自己绝对值最小；(2)找静止的，且离自己绝对值最小；取二者中绝对值较小的那部电梯执行任务。
bool SendToUpingOrStill(Elevator** lpMyElevator, int iRequestFloor, int iUpingCount, int* lpUpingElevators, int iStillCount, int* lpStillElevators)
{
	if ((iUpingCount == 0) && (iStillCount == 0))//当前没有可调用的电梯。
	{
		return false;
	}
	//有可调用的电梯。
	//1.找出上行电梯中上行顶限距需求楼层的最小距离。
	int iUpingIndex = -1;//记录最小距离电梯的下标。
	int iUpingDistance = 100;//记录两者的距离。
	//找出上行状态绝对值最小的下标。
	if (iUpingCount != 0)
	{
		//上行数量不为0，那么找到第一个满足需求数的下标的下标。
		int ieIndex = 0;
		for (; ieIndex < iUpingCount; ieIndex++)
		{
			if ((lpMyElevator[lpUpingElevators[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
			{
				if ((lpMyElevator[lpUpingElevators[ieIndex]]->GetCurFloor())>iRequestFloor)
				{//外部的需求是下行的，此时要找当前楼层在自己之上的上行电梯，因为这样的上行电梯的顶限可能离需求楼层最近。
					break;
				}
			}
		}
		//就是找到满足需求数的下标后。
		if (ieIndex != iUpingCount)
		{
/*			iUpingIndex = lpUpingElevators[ieIndex];
			iUpingDistance = abs((lpMyElevator[lpUpingElevators[ieIndex]])->GetCurFloor() - iRequestFloor);
			for (int index = ieIndex + 1; index < iUpingCount; index++)
			{
				//上行顶限与需求楼层之差。
				if (iUpingDistance >(abs(((lpMyElevator[lpUpingElevators[index]])->GetMaxInnerRequirementFloor()) - iRequestFloor)) &&
					((lpMyElevator[lpUpingElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM))
					//在满足需求数信息的前提下，使楼层的绝对值距离最小。
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
	//找出静止状态绝对值最小的下标。
	int iStillIndex = -1;//记录最小距离电梯的下标。
	int iStillDistance = 100;//记录两者的最小距离。
	//找出静止状态绝对值最小的下标。
	if (iStillCount != 0)
	{
		//静止电梯数不为0，那么找到第一个满足需求数的电梯下标的下标。
		int ieIndex = 0;
		for (; ieIndex < iStillCount; ieIndex++)
		{
			if ((lpMyElevator[lpStillElevators[ieIndex]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM )
			{
				break;
			}
		}
		//当电梯全部满载的时候，这里要加个判断。此时外部需求需要等待电梯内部需求量减少后才能转化为内部需求。
		if (ieIndex == iStillCount)
		{
			return false;//符合条件的电梯全部满载，外部需求分配失败，该外部需求等待下一次分配。
		}
		iStillIndex = lpStillElevators[ieIndex];
		iStillDistance = abs((lpMyElevator[lpStillElevators[ieIndex]]->GetCurFloor()) - iRequestFloor);
		for (int index = ieIndex + 1; index < iStillCount; index++)
		{
			//电梯当前楼层与需求楼层之差。
			if ( (abs((lpMyElevator[lpStillElevators[index]]->GetCurFloor() - iRequestFloor)) < iStillDistance) && 
				( (lpMyElevator[lpStillElevators[index]]->GetInnerRequirementFloorsCount()) < MAX_ELEVATOR_INNERREQUEST_NUM) )
			{
				iStillDistance = abs((lpMyElevator[lpStillElevators[index]]->GetCurFloor() - iRequestFloor));
				iStillIndex = lpStillElevators[index];
			}
		}
	}
	//获得最小绝对值的楼层后，开始分配任务。
	if (iUpingIndex == -1)//上行电梯不满足要求。
	{
		if (iStillDistance == 0)
		{
			Elevator::SetOuterRequestDown(iRequestFloor, false);//分配的楼层刚好与分配到的电梯的当前楼层相同。
			return true;
		}
		if (iStillIndex == -1)
		{
			return false;//静止电梯也不满足要求。
		}
		lpMyElevator[iStillIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_DOWNING);
	}
	else if (iStillIndex == -1)
	{
		lpMyElevator[iUpingIndex]->ReceiveOuterRequest(iRequestFloor, ELEVATOR_STATE_DOWNING);
	}
	else//从二者中找出绝对值较小的那一个。这种情况下上行和静止的电梯中都有满足条件的电梯。
	{
		if (iUpingDistance > iStillDistance)
		{
			if (iStillDistance ==0 )
			{
				Elevator::SetOuterRequestDown(iRequestFloor, false);//分配的楼层刚好与分配到的电梯的当前楼层相同。
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

//开启五部电梯的全部线程。
/*bool StartAllElevators(Elevator** lpMyElevator, int iElevatorCount)
{
	for (int index = 0; index < iElevatorCount; index++)
	{
		lpMyElevator[index]->ResumeElevatorThread();
	}
	return true;
}*/