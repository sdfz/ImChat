#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<windows.h>
#include <cstdio>
#include<tchar.h>
#include"ImChat.h"


using namespace std;

#define MAX_LINE 100
HINSTANCE Global_Instance;
WNDCLASS wc1;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)			    //如何进行显示 最大化还是最小化
{					//实例句柄                                                      窗口最大化还是最小化显示


	HWND	 hwnd;		//窗口句柄
	MSG		 msg;		//消息
	WNDCLASS wc;		//窗口类
	Global_Instance = hInstance;
	
						//1 设计一个窗口类
	wc.style = 0;							//窗口功能样式 改变窗口水平和垂直
	wc.lpfnWndProc = (WNDPROC)WndProc;				//窗口过程
	wc.cbClsExtra = 0;							//窗口类额外数据
	wc.cbWndExtra = 0;							//窗口额外数据
	wc.hInstance = hInstance;					//实例句柄
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);	//窗口左上角图标 系统默认
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//鼠标指针箭头 系统默认
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//窗口背景
	wc.lpszMenuName = NULL;							//菜单
	wc.lpszClassName = TEXT("MyWndClass");			//窗口名字

	wc1 = wc;										//2 注册窗口类
	RegisterClass(&wc);

	//3 创建窗口
	hwnd = CreateWindow(
		TEXT("MyWndClass"),		//窗口类名字
		TEXT("Hello WIN32"),	//窗口标题
		WS_POPUP,	//窗口外观样式 比如需要变宽或者标题之类的
		500,					//默认位置 x
		300,					//默认位置 y
		950,					//默认宽度 x
		650,					//默认高度 x
		NULL,		  			//当前窗口父窗口
		NULL,		  			//窗口菜单句柄  也就是ID
		hInstance,   	 		//当前窗口实例
		NULL		  			//lParam
	);

	//4 显示和更新窗口
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//5 消息循环
	//GetMessage去消息队列里面取消息放入msg结构里面
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//翻译键盘消息
		DispatchMessage(&msg);//转发到窗口过程;
	}
	return msg.wParam;
}


void ImChatfun(HWND hWnd1, UINT message1, WPARAM wParam1, LPARAM lParam1, HINSTANCE Global_Instance)
{
	ImChat ImChatStart;
	ImChatStart.SetMessage(hWnd1, message1, wParam1, lParam1, Global_Instance, wc1);
}

void ImHeafun()
{
	ImHead ImHeadStart;
	ImHeadStart.ImHead_Windows();
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	ImChatfun(hwnd, message, wParam, lParam, Global_Instance);
	ImHeafun();

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		
	}
	return 0;
}