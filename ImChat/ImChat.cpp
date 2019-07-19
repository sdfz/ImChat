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
	static HWND Head_win;
	HDC hdc;

	static RECT rect;
	HRGN hRgn;
	static POINT point;
	static int cx, cy;
	mygdiplus Gdiimg;
	CONST WCHAR* imgstr = TEXT("img/logo.png");
	Rect imglogo = { 0,0,70,60 };

	RECT ImgExit = { 0,0,15,15};
	HBRUSH Brush;

	switch(message)
	{
	case WM_CREATE:
		//窗口圆角
		GetWindowRect(hWnd, &rect);
		hRgn = CreateRoundRectRgn(0, 0, rect.right - rect.left, rect.bottom - rect.top, 20, 20);
		SetWindowRgn(hWnd, hRgn, TRUE);


		Head_win = CreateWindow(
			TEXT("Edit"),		//窗口类名字
			NULL,					//窗口标题
			WS_CHILD,	//窗口外观样式 比如需要变宽或者标题之类的
			70,						//默认位置 x
			20,						//默认位置 y
			258,					//默认宽度 x
			20,						//默认高度 y
			hWnd,		  			//当前窗口父窗口
			NULL,		  			//窗口菜单句柄  也就是ID
			ImChat_Global_Instance, //当前窗口实例
			NULL		  			//lParam
		);

		GetWindowRect(Head_win, &rect);
		hRgn = CreateRoundRectRgn(0, 0, rect.right - rect.left, rect.bottom - rect.top, 20, 20);
		SetWindowRgn(Head_win, hRgn, TRUE);


		SetWindowLong(Head_win, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, 0, 200, LWA_ALPHA);


		SetWindowLong(Head_win, GWL_STYLE, COLOR_WINDOW + 2);
		UpdateWindow(Head_win);

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
		HPEN hPenOld,hPenOld1;

		hdc=BeginPaint(hWnd, &ps);

		hPen = CreatePen(PS_SOLID, 1, RGB(230, 230, 230));
		hPenOld = (HPEN)SelectObject(hdc, hPen);

		MoveToEx(hdc, 0, 60, NULL);
		LineTo(hdc, 950, 60);

		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);

		//logo
		imgIm(hdc, imglogo, imgstr);

		//搜索框
		MoveWindow(Head_win, 80, 23, 258, 20, TRUE);

		hPen = CreatePen(PS_SOLID, 1, RGB(236, 236, 236));
		hPenOld = (HPEN)SelectObject(hdc, hPen);

		RoundRect(hdc, 65, 10, 350, 50, 40, 40);

		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);


		//隐藏和退出
		GetWindowRect(hWnd, &rect);



		//画笔(描边)
		hPen = CreatePen(PS_SOLID, 1, RGB(71, 222, 0));
		hPenOld1 = (HPEN)SelectObject(hdc, hPen);

		//画刷(填充)
		Brush =CreateSolidBrush(RGB(71, 222, 0));
		hPenOld = (HPEN)SelectObject(hdc, Brush);

		SetWindowOrgEx(hdc, -850, -10, &point);
		Ellipse(hdc, ImgExit.left, ImgExit.top, ImgExit.right, ImgExit.bottom);

		SelectObject(hdc, hPenOld);
		DeleteObject(Brush);


		SelectObject(hdc, hPenOld1);
		DeleteObject(hPen);

		ShowWindow(Head_win, SW_SHOW);


		//文字测试
		//ImHead_string(hdc, cxClient, cyClient, 59, 106);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

}


void ImHead::imgIm(HDC & hdc, Rect img_rect, CONST WCHAR* imgstring)
{

	Graphics	grpx(hdc);

	Image*		pImage = Gdiplus::Image::FromFile(imgstring);
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
