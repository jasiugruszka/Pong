// WindowsProject1.cpp : definiuje punkt wejœcia dla aplikacji
//


#include "stdafx.h"
#include "commdlg.h"
#include "resource.h"
#include "targetver.h"
#include <windows.h>



#define MAX_LOADSTRING 100              //dane wejsciowe
#define ID_TIMER 1001
#define ID_NPCTIMER 1002
#define win_width 600
#define win_height 600
#define paletka_width 100
#define paletka_height 20
#define pilka_srednica 16
#define ID_CLOSE 2000
#define ID_EXIT 2001



// Zmienne globalne:
HINSTANCE hInst;                                // bie¿¹ce wyst¹pienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytu³u
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna g³ównego
HWND hWnd;
HWND pilka;
HWND paletka;
HWND paletka2;
static BOOL lose = false;

// Przeka¿ dalej deklaracje funkcji do³¹czonych w tym module kodu:
ATOM				MyRegisterClass(HINSTANCE hInstance);
ATOM				MyRegisterClassPilka(HINSTANCE hInstance);
ATOM				MyRegisterClassPaletka(HINSTANCE hInstance);
ATOM				MyRegisterClassPaletka2(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	pilkaProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	paletkaProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	paletka2Proc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Przegrana(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: W tym miejscu umieœæ kod.


	MSG msg;
	HACCEL hAccelTable;

	// Zainicjuj ci¹gi globalne
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_P4LAB02TRY2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	MyRegisterClassPilka(hInstance);
	MyRegisterClassPaletka(hInstance);
	MyRegisterClassPaletka2(hInstance);

	// Wykonaj inicjacje aplikacji:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_P4LAB02TRY2));

	// G³ówna pêtla wiadomoœci:
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
//  FUNKCJA: MyRegisterClass()
//
//  CEL: Rejestruje klasê okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)        //Samo okno
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

ATOM MyRegisterClassPilka(HINSTANCE hInstance)  //pi³ka
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= pilkaProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_P4LAB02TRY2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreateSolidBrush(RGB(135,13,255)));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_P4LAB02TRY2);
	wcex.lpszClassName	= L"PILKAclass";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

ATOM MyRegisterClassPaletka(HINSTANCE hInstance) //paletka pierwsza
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= paletkaProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_P4LAB02TRY2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreateSolidBrush(RGB(200,0,0)));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_P4LAB02TRY2);
	wcex.lpszClassName	= L"PALETKAclass";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

ATOM MyRegisterClassPaletka2(HINSTANCE hInstance)   //paletka druga
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= paletka2Proc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_P4LAB02TRY2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreateSolidBrush(RGB(100,0,40)));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_P4LAB02TRY2);
	wcex.lpszClassName	= L"PALETKA2class";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}



//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   CEL: Zapisuje dojœcie wyst¹pienia i tworzy okno g³ówne
//
//   KOMENTARZE:
//
//        W tej funkcji dojœcie wyst¹pienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyœwietlane okno g³ówne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; //  Przechowuj dojœcie wyst¹pienia w zmiennej globalnej

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, win_width, win_height, NULL, NULL, hInstance, NULL);   //ZAMIAST WYMIAROW OKNA: CW_USEDEFAULT, 0, CW_USEDEFAULT, 0
	if (!hWnd)
	{
		return FALSE;
	}
	
	
	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_MINIMIZEBOX);
	SetWindowLong(hWnd, GWL_EXSTYLE, 0);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//stworz okno - pilka
	pilka = CreateWindow(L"PILKAclass", szTitle, WS_VISIBLE|WS_CHILD,
		184, 50, pilka_srednica, pilka_srednica, hWnd, NULL, GetModuleHandle(NULL), NULL);
	//zaokraglenie
	SetWindowRgn(pilka,(HRGN)CreateRoundRectRgn(0,0,pilka_srednica,pilka_srednica,pilka_srednica,pilka_srednica),TRUE);
	ShowWindow(pilka, nCmdShow);
	UpdateWindow(pilka);
	//stworz okno - paletka
	paletka = CreateWindow(L"PALETKAclass", szTitle, WS_VISIBLE|WS_CHILD,
		150, win_height-25, paletka_width, paletka_height, hWnd, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(paletka, nCmdShow);
	UpdateWindow(paletka);
	//stworz okno - paletka2
	paletka2 = CreateWindow(L"PALETKA2class", szTitle, WS_VISIBLE|WS_CHILD,
		150, 5, paletka_width, paletka_height, hWnd, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(paletka2, nCmdShow);
	UpdateWindow(paletka2);

	return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  CEL: Przetwarza wiadomoœci dla okna g³ównego.
//
//  WM_COMMAND — przetwarzaj menu aplikacji
//  WM_PAINT — pomaluj okno g³ówne
//  WM_DESTROY — opublikuj komunikat o rezygnacji i wróæ
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
	case WM_NCRBUTTONDOWN:                          //myszka otwieraj¹ca menu popup
		{
			POINT click;
			GetCursorPos(&click);
			HMENU hPopupMenu = CreatePopupMenu();
			InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, IDM_EXIT, L"WyjdŸ");
		
			TrackPopupMenu(hPopupMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, click.x, click.y, 0, hWnd, NULL);
		}

	case WM_NCHITTEST:
		return HTCAPTION;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			SetFocus(paletka);
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

LRESULT CALLBACK pilkaProc(HWND pilka, UINT message, WPARAM wParam, LPARAM lParam)        //ruch pilki
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH brush;
	//poczatkowe ustawienia pilki
	static int x=win_width/2;
	static int y=win_height/2;
	static int dx=1;
	static int dy=-1;
	static int paletka2x;
	static int paletka2y;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(pilka,ID_TIMER,16,NULL);
		break;
	case WM_TIMER:
		//uzyskanie pozycji paletek i pilki
		RECT prc;//paletka
		GetWindowRect(paletka,&prc);
		RECT brc;//pilka
		GetWindowRect(pilka,&brc);
		RECT mainrc;//calosc
		GetWindowRect(hWnd,&mainrc);
		RECT p2rc;//paletka2
		GetWindowRect(paletka2,&p2rc);

		paletka2x= p2rc.left - mainrc.left;
		paletka2y= p2rc.bottom - mainrc.top;

		RECT inter;
		IntersectRect(&inter, &prc, &brc);

		//uderzenie góra
		if(y < 0)
			dy = -1 * dy;
		//uderzenie dó³
		if(y+pilka_srednica > win_height){
			if (lose == false){
				lose = true;
				dy = -1 * dy;
				DialogBox(NULL,(LPCWSTR)IDD_LOSE, hWnd, Przegrana);
			}
		}
		//uderzenie lewo
		if(x < 0)
			dx = -1 * dx;
		//uderzenie prawo
		if(x+pilka_srednica > win_width)
			dx = -1 * dx;
		//uderzenie dolna paletka
		if((brc.bottom >= prc.top) && (brc.left+pilka_srednica/2 >= prc.left) && (brc.right-pilka_srednica/2 <= prc.right))
			dy = -1 * dy;
		//uderzenie gorna paletka
		if((brc.top <= p2rc.bottom) && (brc.left >= p2rc.left) && (brc.right <= p2rc.right))
			dy = -1 * dy;
		// uderzenie prawa strona dolna paletka
		if((brc.left <= prc.right) && (brc.bottom > prc.top) && (brc.right > prc.right))
			dx = -1 *dx;
		//uderzenie lewa strona dolna paletka
		if((brc.right >= prc.left) && (brc.bottom > prc.top) && (brc.left < prc.left))
			dx = -1 *dx;

		y=y+(dy*5);
		x=x+(dx*5);
		SetWindowPos(pilka,HWND_TOP,x,y,pilka_srednica,pilka_srednica,SWP_SHOWWINDOW);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(pilka, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK paletkaProc(HWND paletka, UINT message, WPARAM wParam, LPARAM lParam)   // ruch paletki  
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH brush;

	switch (message)
	{
	case WM_KEYDOWN:
		{
			RECT rc;   //uzyskanie polozenia...
			GetWindowRect(paletka,&rc);
			RECT mainrc;
			GetWindowRect(hWnd,&mainrc);
			int pleft = rc.left - mainrc.left;
			int pright = rc.right - mainrc.left;
			int ptop = rc.top - mainrc.top;

			switch (wParam)
			{
			case VK_RIGHT:
				{
					if (pright+10 <= win_width)
						SetWindowPos(paletka,HWND_TOP,pleft+10,ptop,paletka_width,paletka_height,SWP_SHOWWINDOW);
				}
				break;
			case VK_LEFT:
				{
					if (pleft-10 >= 0)
						SetWindowPos(paletka,HWND_TOP,pleft-10,ptop,paletka_width,paletka_height,SWP_SHOWWINDOW);
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
			RECT mainrc;                                                 // ruch paletki
			GetWindowRect(hWnd, &mainrc);
			RECT oldrc;
			GetWindowRect(paletka, &oldrc);
			RECT *newrc;
			newrc = (RECT*)lParam;

			newrc->top = oldrc.top;
			newrc->bottom = oldrc.bottom;

			if (newrc->left <= mainrc.left){
				newrc->left = mainrc.left;
				newrc->right = mainrc.left+paletka_width;
			}
			if (newrc->right >= mainrc.right){
				newrc->right = mainrc.right;
				newrc->left = mainrc.right-paletka_width;
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(paletka, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK paletka2Proc(HWND paletka2, UINT message, WPARAM wParam, LPARAM lParam){
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH brush;
	int static pilkax;
	int static pilkady = 1;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(paletka2,ID_NPCTIMER,16,NULL);
		break;
	case WM_TIMER:
		RECT brc;
		GetWindowRect(pilka,&brc);
		RECT mainrc;
		GetWindowRect(hWnd,&mainrc);
		pilkax= brc.left - mainrc.left;
	
		if(!(pilkax <= paletka_width/2 - pilka_srednica) && !(pilkax >= win_width - paletka_width/2))
			//paletka komputera
				SetWindowPos(paletka2,HWND_TOP,pilkax-paletka_width/2 + pilka_srednica/2 ,5,100,20,SWP_SHOWWINDOW);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(paletka2, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK Przegrana(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	KillTimer(paletka2,ID_NPCTIMER);
	KillTimer(pilka,ID_TIMER);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		
		if (LOWORD(wParam) == IDCANCEL){
			EndDialog(hDlg, LOWORD(wParam));
			DestroyWindow(hWnd);
			return (INT_PTR)TRUE;
		}
		break;

	}
	return (INT_PTR)FALSE;
}