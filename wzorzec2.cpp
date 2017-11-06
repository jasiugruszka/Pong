#include <windows.h>
#include <ctime>

// Global Definitions
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

// Global Variables
const char lpClassName[] = "MyClass";
HWND mainWindow;

// Painting Variables
HPEN redPen;
HPEN greenPen;
HPEN whitePen;
HPEN bluePen;
HBRUSH blackBrush;
RECT p1s_rect, p2s_rect;
int p1_score = 0, p2_score = 0;
int paddle_x = 10, paddle_y = (WINDOW_HEIGHT / 2) - 20;
int paddle2_x = WINDOW_WIDTH - 15, paddle2_y = (WINDOW_HEIGHT / 2) - 20;
int ball_x = WINDOW_WIDTH / 2, ball_y = (WINDOW_HEIGHT / 2) - 20;
int bv_x = 0, bv_y = 0;
char p1s_text[9];
char p2s_text[9];

// Function Declarations
LRESULT CALLBACK WindowEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Standard Variables
	DWORD timeStart;

	// Create The Windows Class
	WNDCLASSEX wc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = lpClassName;
	wc.lpfnWndProc = WindowEvent;
	wc.hInstance = hInstance;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;

	// Register The Windows Class
	RegisterClassEx(&wc);

	// Create The Window
	mainWindow = CreateWindowEx(
		NULL,
		lpClassName,
		"Nano Pong - by Jake Chappell",
		WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		(GetSystemMetrics(SM_CXSCREEN) / 2) - (WINDOW_WIDTH / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (WINDOW_HEIGHT / 2),
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	// Make Sure The Window Was A Success
	if (!mainWindow)
		return 0;

	// Update The Window
	UpdateWindow(mainWindow);

	// Setup Painting Objects Before Loop
	redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	greenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	bluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	whitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	blackBrush = CreateSolidBrush(RGB(0, 0, 0));

	// Setup Rects (P1)
	p1s_rect.left = (WINDOW_WIDTH / 2) / 2 - 50;
	p1s_rect.right = (WINDOW_WIDTH / 2) / 2 + 50;
	p1s_rect.top = 20;
	p1s_rect.bottom = 40;

	// Setup Rects (P2)
	p2s_rect.left = (WINDOW_WIDTH / 2) / 2 * 3 - 50;
	p2s_rect.right = (WINDOW_WIDTH / 2) / 2 * 3 + 50;
	p2s_rect.top = 20;
	p2s_rect.bottom = 40;

	// The Main Loop
	MSG msg;

	while (1)
	{
		srand(GetTickCount());

		// Get Standard Messages
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		// Time Start
		timeStart = GetTickCount();

		while(GetTickCount() - timeStart < 5);

		// Move Ball

		if (ball_x + bv_x >= WINDOW_WIDTH)
		{
			p1_score++;
			ball_x = WINDOW_WIDTH / 2;
			ball_y = WINDOW_HEIGHT / 2 - 20;
			bv_x = 0;
			bv_y = 0;
		}

		if (ball_x + bv_x <= 0)
		{
			p2_score++;
			ball_x = WINDOW_WIDTH / 2;
			ball_y = WINDOW_HEIGHT / 2 - 20;
			bv_x = 0;
			bv_y = 0;
		}

		if (ball_x + bv_x >= paddle2_x - 6 && (ball_y <= paddle2_y + 40 && ball_y >= paddle2_y - 40))
			bv_x = -bv_x;

		if (ball_x + bv_x <= paddle_x + 6 && (ball_y <= paddle_y + 40 && ball_y >= paddle_y - 40))
			bv_x = -bv_x;

		ball_x += bv_x;

		if (ball_y + bv_y < WINDOW_HEIGHT - 30 && ball_y + bv_y > 0)
			ball_y += bv_y;
		else
		{
			bv_y = -bv_y;
			ball_y += bv_y;
		}

		if (GetAsyncKeyState(0x41) && paddle_y - 45 > 0)
			paddle_y -= 5;

		if (GetAsyncKeyState(0x5A) && paddle_y + 45 < WINDOW_HEIGHT - 30)
			paddle_y += 5;

		if (GetAsyncKeyState(VK_UP) && paddle2_y - 45 > 0)
			paddle2_y -= 5;

		if (GetAsyncKeyState(VK_DOWN) && paddle2_y + 45 < WINDOW_HEIGHT - 30)
			paddle2_y += 5;

		// If Space Is Pressed, Start Moving The Ball
		if (GetAsyncKeyState(VK_SPACE) && ball_x == WINDOW_WIDTH / 2 && ball_y == (WINDOW_HEIGHT / 2) - 20)
		{
			if (rand()%10 < 5)
				bv_x = -5;
			else
				bv_x = 5;

			if (rand()%10 < 5)
				bv_y = -5;
			else
				bv_y = 5;
		}

		// Repaint The Screen
		InvalidateRect(mainWindow, NULL, true);

	}

	return (int) msg.wParam;
}

// Callback Function (WindowEvent)
LRESULT CALLBACK WindowEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	itoa(p1_score, p1s_text, 10);
	itoa(p2_score, p2s_text, 10);

	switch (message)
	{
		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);

			SelectObject(hDC, whitePen);
			MoveToEx(hDC, WINDOW_WIDTH / 2, 0, NULL);
			LineTo(hDC, WINDOW_WIDTH / 2, WINDOW_HEIGHT - 20);

			// Player Scores

			SetTextColor(hDC, RGB(0, 255, 0));
			SetBkColor(hDC, RGB(0, 0, 0));
			SetBkMode(hDC, TRANSPARENT);

			DrawText(hDC, p1s_text, strlen(p1s_text), &p1s_rect, DT_CENTER);
			DrawText(hDC, p2s_text, strlen(p2s_text), &p2s_rect, DT_CENTER);

			SelectObject(hDC, redPen);
			SelectObject(hDC, blackBrush);

			Rectangle(hDC, paddle_x - 5, paddle_y - 40, paddle_x + 5, paddle_y + 40);

			SelectObject(hDC, bluePen);

			Rectangle(hDC, paddle2_x - 5, paddle2_y - 40, paddle2_x + 5, paddle2_y + 40);

			SelectObject(hDC, greenPen);

			Ellipse(hDC, ball_x - 7, ball_y - 7, ball_x + 7, ball_y + 7);

			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
