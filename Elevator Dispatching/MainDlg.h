#pragma once

#include<Windows.h>
#include<windowsx.h>
#include"resource.h"
#include"Elevator.h"
#include"ElevatorFunc.h"

//主界面的窗口过程函数。
BOOL CALLBACK ElevatorDispatch_DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_ElevatorDispatch_Dlg), NULL, ElevatorDispatch_DlgProc);
	return 0;
}