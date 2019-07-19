#ifndef  _ImChat
#define  _ImChat

#include<windows.h>
#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace Gdiplus;


class ImChat
{


public:
	static HWND			hWnd;
	static UINT			message;
	static WPARAM		wParam;
	static LPARAM		lParam;
	static HINSTANCE	ImChat_Global_Instance;
		   WNDCLASS		wc1;
	ImChat()	{};
	~ImChat()	{};
	void SetMessage(HWND hWnd1, UINT message1, WPARAM wParam1, LPARAM lParam1, HINSTANCE Instance1, WNDCLASS wc11);
};



class mygdiplus
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR			gdiplusToken;
public:
	mygdiplus()
	{
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}
	~mygdiplus()
	{
		GdiplusShutdown(gdiplusToken);
	}
};




class ImHead : public ImChat
{
public:
	ImHead() {};
	~ImHead() {};

	void ImHead_Windows();
	void ImHead_string(HDC hd, int width, int height, int x, int y);

	
	void imgIm(HDC & hdc);
};
#endif
