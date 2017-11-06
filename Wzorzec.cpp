
#include "stdafx.h"
#include "commdlg.h"
#include "P4 Lab 02 try2.h"


#define MAX_LOADSTRING 100
#define ID_TIMER 1001
#define ID_NPCTIMER 1002
#define win_width 400
#define win_height 400
#define pallet_width 100
#define pallet_height 20
#define ball_diameter 16
#define ID_CLOSE 2000
#define ID_EXIT 2001
#define IDM_COLOR 2002


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND hWnd;
HWND ball;
HWND pallet;
HWND pallet2;
static BOOL lose=false;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
ATOM				MyRegisterClassball(HINSTANCE hInstance);
ATOM				MyRegisterClasspallet(HINSTANCE hInstance);
ATOM				MyRegisterClasspallet2(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	ballProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	palletProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	pallet2Proc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Lose(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_P4LAB02TRY2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	MyRegisterClassball(hInstance);
	MyRegisterClasspallet(hInstance);
	MyRegisterClasspallet2(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_P4LAB02TRY2));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_P4LAB02TRY2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreateSolidBrush(RGB(255,255,255)));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_P4LAB02TRY2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

ATOM MyRegisterClassball(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= ballProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_P4LAB02TRY2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreateSolidBrush(RGB(0,0,255)));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_P4LAB02TRY2);
	wcex.lpszClassName	= L"ballclass";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

ATOM MyRegisterClasspallet(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= palletProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_P4LAB02TRY2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreateSolidBrush(RGB(0,0,0)));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_P4LAB02TRY2);
	wcex.lpszClassName	= L"palletclass";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

ATOM MyRegisterClasspallet2(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= pallet2Proc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_P4LAB02TRY2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreateSolidBrush(RGB(0,0,0)));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_P4LAB02TRY2);
	wcex.lpszClassName	= L"pallet2class";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		500, 500, win_width, win_height, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	// Remove borders
	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_MINIMIZEBOX);
	SetWindowLong(hWnd, GWL_EXSTYLE, 0);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//create a ball instance
	ball = CreateWindow(L"ballclass", szTitle, WS_VISIBLE|WS_CHILD,
		184, 50, ball_diameter, ball_diameter, hWnd, NULL, GetModuleHandle(NULL), NULL);
	//make window round
	SetWindowRgn(ball,(HRGN)CreateRoundRectRgn(0,0,ball_diameter,ball_diameter,ball_diameter,ball_diameter),TRUE);
	ShowWindow(ball, nCmdShow);
	UpdateWindow(ball);
	//create a pallet instance
	pallet = CreateWindow(L"palletclass", szTitle, WS_VISIBLE|WS_CHILD,
		150, win_height-25, pallet_width, pallet_height, hWnd, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(pallet, nCmdShow);
	UpdateWindow(pallet);
	SetFocus(pallet);
	//create a pallet2 instance
	pallet2 = CreateWindow(L"pallet2class", szTitle, WS_VISIBLE|WS_CHILD,
		150, 5, pallet_width, pallet_height, hWnd, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(pallet2, nCmdShow);
	UpdateWindow(pallet2);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH brush;


	switch (message)
	{
	case WM_NCRBUTTONDOWN:
		{
			POINT click;
			GetCursorPos(&click);
			HMENU hPopupMenu = CreatePopupMenu();
			InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, IDM_EXIT, L"Exit");
			InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, IDM_COLOR, L"Color Picker");
			//SetForegroundWindow(hWnd);
			TrackPopupMenu(hPopupMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, click.x, click.y, 0, hWnd, NULL);
		}

	case WM_NCHITTEST:
		return HTCAPTION;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_COLOR:
			{
				//color picker
				KillTimer(ball,ID_TIMER);
				KillTimer(pallet2,ID_TIMER);

				CHOOSECOLOR cc; 
				static COLORREF acrCustClr[16]; 
				HBRUSH hbrush;
				static DWORD rgbCurrent; 
				ZeroMemory(&cc, sizeof(CHOOSECOLOR));
				cc.lStructSize = sizeof(CHOOSECOLOR);
				cc.hwndOwner = hWnd;
				cc.lpCustColors = (LPDWORD)acrCustClr;
				cc.rgbResult = rgbCurrent;
				cc.Flags = CC_FULLOPEN | CC_RGBINIT;

				if (ChooseColor(&cc)==TRUE){
					RECT rc;
					GetClientRect(hWnd,&rc);
					HBRUSH newcolor;
					newcolor = CreateSolidBrush(cc.rgbResult);
					SetClassLong(hWnd,GCL_HBRBACKGROUND,(LONG)newcolor);
					InvalidateRect(hWnd,&rc,TRUE);
				}
				SetTimer(ball,ID_TIMER,16,NULL);
				SetTimer(pallet2,ID_NPCTIMER,16,NULL);
			}
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			SetFocus(pallet);
			hdc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);
		}
		break;

	case WM_DESTROY:
		KillTimer(hWnd, ID_TIMER);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK ballProc(HWND ball, UINT message, WPARAM wParam, LPARAM lParam){
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH brush;
	//set initial ball position and direction
	static int x=win_width/2;
	static int y=win_height/2;
	static int dx=1;
	static int dy=-1;
	static int pallet2x;
	static int pallet2y;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(ball,ID_TIMER,16,NULL);
		break;
	case WM_TIMER:
		//get ball and pallet positions
		RECT prc;
		GetWindowRect(pallet,&prc);
		RECT brc;
		GetWindowRect(ball,&brc);
		RECT mainrc;
		GetWindowRect(hWnd,&mainrc);
		RECT p2rc;
		GetWindowRect(pallet2,&p2rc);

		pallet2x= p2rc.left - mainrc.left;
		pallet2y= p2rc.bottom - mainrc.top;

		RECT inter;
		IntersectRect(&inter, &prc, &brc);

		//when ball hits top window edge
		if(y < 0)
			dy = -1 * dy;
		//when ball hits bottom window edge
		if(y+ball_diameter > win_height){
			if (lose == false){
				lose = true;
				dy = -1 * dy;
				DialogBox(NULL,(LPCWSTR)IDD_LOSE, hWnd, Lose);
			}
		}
		//when ball hits left window edge
		if(x < 0)
			dx = -1 * dx;
		//when ball hits right window edge (+16px ball)
		if(x+ball_diameter > win_width)
			dx = -1 * dx;
		//when ball hits top of bottom pallet
		if((brc.bottom >= prc.top) && (brc.left+ball_diameter/2 >= prc.left) && (brc.right-ball_diameter/2 <= prc.right))
			dy = -1 * dy;
		//when ball hits bottom of top pallet
		if((brc.top <= p2rc.bottom) && (brc.left >= p2rc.left) && (brc.right <= p2rc.right))
			dy = -1 * dy;
		//when ball hits right side of bottom pallet
		if((brc.left <= prc.right) && (brc.bottom > prc.top) && (brc.right > prc.right))
			dx = -1 *dx;
		//when ball hits left side of bottom pallet
		if((brc.right >= prc.left) && (brc.bottom > prc.top) && (brc.left < prc.left))
			dx = -1 *dx;

		y=y+(dy*3);
		x=x+(dx*3);
		SetWindowPos(ball,HWND_TOP,x,y,ball_diameter,ball_diameter,SWP_SHOWWINDOW);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(ball, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK palletProc(HWND pallet, UINT message, WPARAM wParam, LPARAM lParam){
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH brush;

	switch (message)
	{
	case WM_KEYDOWN:
		{
			RECT rc;
			GetWindowRect(pallet,&rc);
			RECT mainrc;
			GetWindowRect(hWnd,&mainrc);
			int pleft = rc.left - mainrc.left;
			int pright = rc.right - mainrc.left;
			int ptop = rc.top - mainrc.top;
			//int pbottom = rc.bottom - mainrc.top;
			switch (wParam)
			{
			case VK_RIGHT:
				{
					if (pright+10 <= win_width)
						SetWindowPos(pallet,HWND_TOP,pleft+10,ptop,pallet_width,pallet_height,SWP_SHOWWINDOW);
				}
				break;
			case VK_LEFT:
				{
					if (pleft-10 >= 0)
						SetWindowPos(pallet,HWND_TOP,pleft-10,ptop,pallet_width,pallet_height,SWP_SHOWWINDOW);
				}
				break;
			}
		}
	case WM_NCHITTEST: 
		{
			LRESULT hit = DefWindowProc(hWnd, message, wParam, lParam);
			if (hit == HTCLIENT) hit = HTCAPTION;
			return hit;
		}
	case  WM_MOVING: 
		{
			RECT mainrc;
			GetWindowRect(hWnd, &mainrc);
			RECT oldrc;
			GetWindowRect(pallet, &oldrc);
			RECT *newrc;
			newrc = (RECT*)lParam;

			newrc->top = oldrc.top;
			newrc->bottom = oldrc.bottom;

			if (newrc->left <= mainrc.left){
				newrc->left = mainrc.left;
				newrc->right = mainrc.left+pallet_width;
			}
			if (newrc->right >= mainrc.right){
				newrc->right = mainrc.right;
				newrc->left = mainrc.right-pallet_width;
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(pallet, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK pallet2Proc(HWND pallet2, UINT message, WPARAM wParam, LPARAM lParam){
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH brush;
	int static ballx;
	int static dbally = 1;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(pallet2,ID_NPCTIMER,16,NULL);
		break;
	case WM_TIMER:
		RECT brc;
		GetWindowRect(ball,&brc);
		RECT mainrc;
		GetWindowRect(hWnd,&mainrc);
		ballx= brc.left - mainrc.left;
		//if pallet won't move out of main window
		if(!(ballx <= pallet_width/2 - ball_diameter) && !(ballx >= win_width - pallet_width/2))
			//make the top pallet follow the ball
				SetWindowPos(pallet2,HWND_TOP,ballx-pallet_width/2 + ball_diameter/2 ,5,100,20,SWP_SHOWWINDOW);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(pallet2, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK Lose(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	KillTimer(pallet2,ID_NPCTIMER);
	KillTimer(ball,ID_TIMER);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		//restart game if user clicks yes
		/*if (LOWORD(wParam) == IDOK){
		SetWindowPos(ball,HWND_TOP,win_width/2,win_height/2,ball_diameter,ball_diameter,SWP_SHOWWINDOW);
		SetTimer(ball,ID_TIMER,16,NULL);
		SetTimer(pallet2,ID_NPCTIMER,16,NULL);
		EndDialog(hDlg, LOWORD(wParam));
		lose = false;
		//return (INT_PTR)TRUE;
		}*/
		//close app if user clicks no
		if (LOWORD(wParam) == IDCANCEL){
			EndDialog(hDlg, LOWORD(wParam));
			DestroyWindow(hWnd);
			return (INT_PTR)TRUE;
		}
		break;

	}
	return (INT_PTR)FALSE;
