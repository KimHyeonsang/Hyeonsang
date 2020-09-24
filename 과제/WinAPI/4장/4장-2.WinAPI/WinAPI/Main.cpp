#include<Windows.h>
#include<math.h>

#define PIE 3.141592f
#define CENTER_X 700
#define CENTER_Y 300
#define SECOND 1000
#define RADIUS 150
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Timer2"); //클래스 명 : 창이름
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
	double GetRadian(double _num)
	{
		return _num * (2 * PIE / 60);
	}
	void CALLBACK analogTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

	int Long_x = CENTER_X;
	int Long_y = CENTER_Y;

	int small_x = CENTER_X;
	int small_y = CENTER_Y;

	int middle_x = CENTER_X;
	int middle_y = CENTER_Y;
	
	SYSTEMTIME time;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rt = { 500, 550, 800, 600 };
	PAINTSTRUCT ps;
	static TCHAR str[128];
	int radius = 160;
	static TCHAR sTime[128];
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, SECOND, analogTimer);
		SetTimer(hWnd, 2, SECOND, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		SendMessage(hWnd, WM_TIMER, 2, 0);
		return 0; 
	case WM_TIMER:
			GetLocalTime(&time);
			wsprintf(sTime, TEXT("디지털 시계: %d:%d:%d"),
				time.wHour, time.wMinute, time.wSecond);
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, CENTER_X - RADIUS, CENTER_Y - RADIUS, CENTER_X + RADIUS, CENTER_Y + RADIUS);
		Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
		TextOut(hdc, 650, 500, "아날로그 시계", 13);
		TextOut(hdc, 550, 575, sTime, lstrlen(sTime));
		for (int number = 1; number <= 60; number++)
		{
			MoveToEx(hdc, CENTER_X, CENTER_Y, NULL);
			LineTo(hdc, Long_x, Long_y);
			MoveToEx(hdc, CENTER_X, CENTER_Y, NULL);
			LineTo(hdc, small_x, small_y);
			MoveToEx(hdc, CENTER_X, CENTER_Y, NULL);
			LineTo(hdc, middle_x, middle_y);
			if (number % 5 == 0)//나머지가 0일떄
			{
				wsprintf(str, TEXT("%d"), number /5);
				TextOut(hdc, CENTER_X + radius * sin(GetRadian(number)), CENTER_Y + (-radius) * cos(GetRadian(number)),str,lstrlen(str));
			}
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	}
	
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}

void CALLBACK analogTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	int Longradius = 140;	
	int smallradius = 80;
	int middleradius = 120;
	Long_x = CENTER_X + Longradius * sin(GetRadian(time.wSecond));
	Long_y = CENTER_Y + (-Longradius) * cos(GetRadian(time.wSecond));

	small_x = CENTER_X + smallradius * sin(GetRadian(time.wHour));
	small_y = CENTER_Y + (-smallradius) * cos(GetRadian(time.wHour));

	middle_x = CENTER_X + middleradius * sin(GetRadian(time.wMinute));
	middle_y = CENTER_Y + (-middleradius) * cos(GetRadian(time.wMinute));

	InvalidateRect(hWnd, NULL, TRUE);
}
