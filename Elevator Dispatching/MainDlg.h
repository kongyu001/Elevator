#pragma once

#include<Windows.h>
#include<windowsx.h>
#include"resource.h"
#include"Elevator.h"
#include"ElevatorFunc.h"
#include <iostream>  
#include <string>
#include <vector>
#include <ctime>
#define COMMAND_H


//������Ĵ��ڹ��̺�����
BOOL CALLBACK ElevatorDispatch_DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_ElevatorDispatch_Dlg), NULL, ElevatorDispatch_DlgProc);
	return 0;
}class WM_C0MMAND
{
public:
	void FloorOne()
	{
		std::cout << "����Ƿ��أ�" << std::endl;
	}
};
//Command�࣬��������
class Command
{
protected:
	WM_C0MMAND*receiver;
public:
	Command(WM_C0MMAND*receiver)
	{
		this->receiver = receiver;
	}
	virtual void ExcuteCommand() = 0;
};
//ConcreteCommand�࣬��������
class FloorOneCommand :public Command
{
public:
	FloorOneCommand(WM_C0MMAND*receiver) :Command(receiver) {}
	void ExcuteCommand()
	{
		receiver->FloorOne();
	}
};
//���ó�������
void Outweight(Command*command)
{
	//�ж��������Ͳ�����ͬ�Ĵ���
	if (typeid(*command) == typeid(FloorOneCommand))
	{
		std::cout << "���г��أ����Ա��" << std::endl;
	}
}
