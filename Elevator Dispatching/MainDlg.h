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


//主界面的窗口过程函数。
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
		std::cout << "检测是否超载！" << std::endl;
	}
};
//Command类，抽象命令
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
//ConcreteCommand类，具体命令
class FloorOneCommand :public Command
{
public:
	FloorOneCommand(WM_C0MMAND*receiver) :Command(receiver) {}
	void ExcuteCommand()
	{
		receiver->FloorOne();
	}
};
//设置超载命令
void Outweight(Command*command)
{
	//判断命令类型并做不同的处理
	if (typeid(*command) == typeid(FloorOneCommand))
	{
		std::cout << "运行超载，请减员！" << std::endl;
	}
}
