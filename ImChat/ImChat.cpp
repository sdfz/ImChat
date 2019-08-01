#include "ImChat.h"




//Im初始化
HWND		ImChat::hWnd					= 0;
UINT		ImChat::message					= 0;
WPARAM		ImChat::wParam					= 0;
LPARAM		ImChat::lParam					= 0;
HINSTANCE	ImChat::ImChat_Global_Instance  = 0;
CONST WCHAR* ImChat::hWnd_class				= 0;

void ImChat::SetMessage(HWND hWnd1, UINT message1, WPARAM wParam1, LPARAM lParam1, HINSTANCE Instance1, WNDCLASS wc11, CONST WCHAR* hWnd_class1)
{
	hWnd					= hWnd1;
	message					= message1;
	wParam					= wParam1;
	lParam					= lParam1;
	ImChat_Global_Instance	= Instance1;
	wc0						= wc11;
	hWnd_class				= hWnd_class1;
}


//头
void ImHead::ImHead_Windows()
{
	static int cxClient, cyClient;
	static HWND Head_win;
	static HDC hdc;

	static RECT rect;
	HRGN hRgn;
	static POINT point;
	static int cx, cy;
	//mygdiplus Gdiimg;
	CONST WCHAR* imgstr		 = TEXT("img/logo.png");
	CONST WCHAR* imgstr_hide = TEXT("img/hide.png");
	CONST WCHAR* imgstr_exit = TEXT("img/exit.png");

	Rect imglogo		= { 0,0,70,60 };
	Rect imglogo_hide	= { 900,12,12,12 };
	Rect imglogo_exit	= { 920,12,12,12 };


	HPEN hPen;
	HPEN hPenOld;
	static HWND Head_win11;
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
		ShowWindow(Head_win, SW_SHOW);

		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);//客户区的宽
		cyClient = HIWORD(lParam);//客户区的高
		break;
	
	case WM_LBUTTONDOWN:
		
		hdc=GetDC(hWnd);
		point.x = (LONG)LOWORD(lParam);
		point.y = (LONG)HIWORD(lParam);

		if ((point.x <= cxClient) && (point.y <= (cyClient-590)))
		{
			SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}

		//隐藏
		if ((point.x >= imglogo_hide.X) && (point.x <= (imglogo_hide.X + imglogo_hide.Width)) && (point.y >= imglogo_hide.Y) && (point.y <= imglogo_hide.Y + imglogo_hide.Height))
		{
			ShowWindow(hWnd, SW_MINIMIZE);
		}

		//退出
		if ((point.x >= imglogo_exit.X) && (point.x <= (imglogo_exit.X + imglogo_exit.Width)) && (point.y >= imglogo_exit.Y) && (point.y <= imglogo_exit.Y + imglogo_exit.Height))
		{
			PostQuitMessage(0);
		}

		ReleaseDC(hWnd, hdc);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;

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
		//GetWindowRect(hWnd, &rect);
		//SetWindowOrgEx(hdc, -850, -10, &point);
		imgIm(hdc, imglogo_hide, imgstr_hide);
		imgIm(hdc, imglogo_exit, imgstr_exit);
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
	mygdiplus Gdiimg;
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



//HWND ImBody::Head_Im = 0;
HWND ImBody::Head_Im_Music = 0;


//body
void ImBody::ImBody_Windows()
{
	HDC hdc, hdcc;

	CONST WCHAR* win_classss = TEXT("Static");
	CONST WCHAR* imgstrim = TEXT("img/im.png");
	Rect img_im_xy = { 10,50,48,48 };

	CONST WCHAR* imgstrMusic = TEXT("img/Music.png");
	Rect img_Music_xy = { 10,120,48,48 };
	static HWND Head_m_ddMusic;

	switch (message)
	{
	case WM_CREATE:
	
		Head_Im_Music = CreateWindow(win_classss, NULL,
			WS_CHILD | WS_BORDER,
			0,
			60,
			70,
			590,
			hWnd,
			NULL,
			ImChat_Global_Instance,
			NULL);


		//InvalidateRgn(Head_win11, NULL, TRUE);
		UpdateWindow(Head_Im_Music);
		ShowWindow(Head_Im_Music, SW_SHOW);



		Head_m_ddMusic = CreateWindow(win_classss, NULL,
			WS_CHILD | WS_BORDER,
			70,
			60,
			200,
			590,
			hWnd,
			(HMENU)1993,
			ImChat_Global_Instance,
			NULL);
		
		UpdateWindow(Head_m_ddMusic);
		ShowWindow(Head_m_ddMusic, SW_SHOW);
		break;
	
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(Head_Im_Music, &ps);
		//im
		imgIm(hdc, img_im_xy, imgstrim);
		imgIm(hdc, img_Music_xy, imgstrMusic);

		//ImHead_string(hdc, 100, 100, 59, 106);

		EndPaint(Head_Im_Music, &ps);



		PAINTSTRUCT ps1;
		hdcc = BeginPaint(Head_m_ddMusic, &ps1);
		//im
		imgIm(hdc, img_im_xy, imgstrim);
		//imgIm(hdc, img_Music_xy, imgstrMusic);

		//ImHead_string(hdc, 100, 100, 59, 106);

		EndPaint(Head_m_ddMusic, &ps1);

		break;
	}
}