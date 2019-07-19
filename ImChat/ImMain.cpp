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



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)			    //��ν�����ʾ ��󻯻�����С��
{					//ʵ�����                                                      ������󻯻�����С����ʾ


	HWND	 hwnd;		//���ھ��
	MSG		 msg;		//��Ϣ
	WNDCLASS wc;		//������
	Global_Instance = hInstance;
	
						//1 ���һ��������
	wc.style = 0;							//���ڹ�����ʽ �ı䴰��ˮƽ�ʹ�ֱ
	wc.lpfnWndProc = (WNDPROC)WndProc;				//���ڹ���
	wc.cbClsExtra = 0;							//�������������
	wc.cbWndExtra = 0;							//���ڶ�������
	wc.hInstance = hInstance;					//ʵ�����
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);	//�������Ͻ�ͼ�� ϵͳĬ��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//���ָ���ͷ ϵͳĬ��
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//���ڱ���
	wc.lpszMenuName = NULL;							//�˵�
	wc.lpszClassName = TEXT("MyWndClass");			//��������

	wc1 = wc;										//2 ע�ᴰ����
	RegisterClass(&wc);

	//3 ��������
	hwnd = CreateWindow(
		TEXT("MyWndClass"),		//����������
		TEXT("Hello WIN32"),	//���ڱ���
		WS_POPUP,	//���������ʽ ������Ҫ�����߱���֮���
		500,					//Ĭ��λ�� x
		300,					//Ĭ��λ�� y
		950,					//Ĭ�Ͽ�� x
		650,					//Ĭ�ϸ߶� x
		NULL,		  			//��ǰ���ڸ�����
		NULL,		  			//���ڲ˵����  Ҳ����ID
		hInstance,   	 		//��ǰ����ʵ��
		NULL		  			//lParam
	);

	//4 ��ʾ�͸��´���
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//5 ��Ϣѭ��
	//GetMessageȥ��Ϣ��������ȡ��Ϣ����msg�ṹ����
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//���������Ϣ
		DispatchMessage(&msg);//ת�������ڹ���;
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