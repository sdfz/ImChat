#ifndef  _ImChat
#define  _ImChat

#include<windows.h>
#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace Gdiplus;


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


class ImChat
{
public:
	static HWND			hWnd;
	static UINT			message;
	static WPARAM		wParam;
	static LPARAM		lParam;
	static HINSTANCE	ImChat_Global_Instance;
		   WNDCLASS		wc0;
	ImChat()	{};
	~ImChat()	{};
	static CONST WCHAR* hWnd_class;
	void SetMessage(HWND hWnd1, UINT message1, WPARAM wParam1, LPARAM lParam1, HINSTANCE Instance1, WNDCLASS wc11, CONST WCHAR* hWnd_class1);
};


class ImHead : public ImChat
{
public:
	ImHead()  {};
	~ImHead() {};

	virtual void ImHead_Windows();
	virtual void ImHead_string(HDC hd, int width, int height, int x, int y);
	virtual void imgIm(HDC & hdc, Rect img_rect1, CONST WCHAR* imgstring);
};


class ImBody : public ImHead
{
public:
	ImBody() {};
	~ImBody(){};
	static HWND Head_Im_Music;
	//static HWND Head_Music;

	void ImBody_Windows();
};

#endif
