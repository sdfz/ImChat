#include "ImChat.h"




HWND		ImChat::hWnd					= 0;
UINT		ImChat::message					= 0;
WPARAM		ImChat::wParam					= 0;
LPARAM		ImChat::lParam					= 0;
HINSTANCE	ImChat::ImChat_Global_Instance  = 0;


void ImChat::SetMessage(HWND hWnd1, UINT message1, WPARAM wParam1, LPARAM lParam1, HINSTANCE Instance1, WNDCLASS wc11)
{
	hWnd					= hWnd1;
	message					= message1;
	wParam					= wParam1;
	lParam					= lParam1;
	ImChat_Global_Instance	= Instance1;
	wc1						= wc11;
}
//#define WS_EX_NODRAG 0x40000000L
void ImHead::ImHead_Windows()
{
	static int cxClient, cyClient;
	//static HWND Head_win;
	HDC hdc;

	RECT rect;
	HRGN hRgn;
	static POINT point;
	static int cx, cy;
	mygdiplus Gdiimg;

	switch(message)
	{
	case WM_CREATE:
		//窗口圆角
		GetWindowRect(hWnd, &rect);
		hRgn = CreateRoundRectRgn(0, 0, rect.right - rect.left, rect.bottom - rect.top, 20, 20);
		SetWindowRgn(hWnd, hRgn, TRUE);


		//Head_win = CreateWindow(

		//	TEXT("MyWndClass"),		//窗口类名字
		//	NULL,					//窗口标题
		//	WS_CHILD| WS_BORDER,	//窗口外观样式 比如需要变宽或者标题之类的
		//	0,						//默认位置 x
		//	0,						//默认位置 y
		//	950,					//默认宽度 x
		//	80,						//默认高度 y
		//	hWnd,		  			//当前窗口父窗口
		//	NULL,		  			//窗口菜单句柄  也就是ID
		//	ImChat_Global_Instance, //当前窗口实例
		//	NULL		  			//lParam
		//);
		//UpdateWindow(Head_win);
		//ShowWindow(Head_win, SW_SHOW);

		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);//客户区的宽
		cyClient = HIWORD(lParam);//客户区的高
		break;
	
	case WM_LBUTTONDOWN:
		
		point.x = (LONG)LOWORD(lParam);
		point.y = (LONG)HIWORD(lParam);


		if ((point.x <= cxClient) && (point.y <= (cyClient-590)))
		{
			SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}
		
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;

		HPEN hPen;
		HPEN hPenOld;

		hdc=BeginPaint(hWnd, &ps);

		hPen = CreatePen(PS_SOLID, 1, RGB(230, 230, 230));
		hPenOld = (HPEN)SelectObject(hdc, hPen);

		MoveToEx(hdc, 0, 60, NULL);
		LineTo(hdc, 950, 60);

		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);



		imgIm(hdc);
		//文字测试
		ImHead_string(hdc, cxClient, cyClient, 59, 106);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

}


void ImHead::imgIm(HDC & hdc)
{

	Rect		img_rect(20, 20, 73, 73);
	Graphics	grpx(hdc);


	Image*		pImage = Gdiplus::Image::FromFile(TEXT("img/logo.png"));
	grpx.DrawImage(pImage, img_rect);

	delete pImage;
}


void ImHead::ImHead_string(HDC hd,int width, int height,int x,int y)
{
//	LPWSTR lpstrcpy;
	TCHAR szBuffer[100];
	wsprintf(szBuffer, TEXT("宽=%d     高=%d"), width, height);
	TextOut(hd, x, y, szBuffer, lstrlen(szBuffer));
}
