#include<Windows.h>
#include<math.h>

#define PIE 3.141592f
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Timer"); //클래스 명 : 창이름
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); 
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc; 
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW; 
	RegisterClass(&WndClass); 
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		(HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, NULL, 0, 0)) 
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
	void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
	RECT rt = { 50, 50, 1200, 600 };
	static int x = 200;
	static int y = 200;
	enum MOVE
	{
		MOVE_BASIC = 0,
		MOVE_UP_LEFT,
		MOVE_UP_RIGHT,
		MOVE_DOWN_LEFT,
		MOVE_DOWN_RIGHT
	};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;
	static TCHAR sTime[128];
	
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 50, TimeProc);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, 50, 50, 1200, 600);
		Ellipse(hdc, x - 50, y - 50, x + 50, y + 50);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}

void CALLBACK TimeProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	int speed_x = 20;
	int speed_y = 30;
	static MOVE move = MOVE_BASIC;
	if (x + 50 >= rt.right)
	{
		if (move == MOVE_UP_RIGHT)
			move = MOVE_UP_LEFT;
		else if (move == MOVE_DOWN_RIGHT)
			move = MOVE_DOWN_LEFT;
	}
	else if (y - 50 <= rt.top)
	{
		if (move == MOVE_UP_RIGHT)
			move = MOVE_DOWN_RIGHT;
		else if (move == MOVE_UP_LEFT)
			move = MOVE_DOWN_LEFT;
		
	}
	else if (x - 50 <= rt.left)
	{
		if (move == MOVE_UP_LEFT)
			move = MOVE_UP_RIGHT;
		else if (move == MOVE_DOWN_LEFT)
			move = MOVE_DOWN_RIGHT;
		
	}
	else if (y + 50 >= rt.bottom)
	{
		if (move == MOVE_DOWN_RIGHT)
			move = MOVE_UP_RIGHT;
		else if (move == MOVE_DOWN_LEFT)
			move = MOVE_UP_LEFT;
		else if (move == MOVE_BASIC)
			move = MOVE_UP_RIGHT;		
	}
	switch (move)
	{
	case MOVE_BASIC:
		x += speed_x;
		y += speed_y;
		break;
	case MOVE_UP_LEFT: //위왼
		x -= speed_x;
		y -= speed_y;
		break;
	case MOVE_UP_RIGHT://위오른쪽
		x += speed_x;
		y -= speed_y;
		break;
	case MOVE_DOWN_RIGHT://아래 오른쪽
		x += speed_x;
		y += speed_y;		
		break;
	case MOVE_DOWN_LEFT://아래 왼쪽
		x -= speed_x;
		y += speed_y;
		break;
	}
	InvalidateRect(hWnd, &rt, TRUE);
}
