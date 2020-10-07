#include<Windows.h>
#include"resource1.h"
#include"BITMAPCLASS.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
BITMAPCLASS* bitclass;
vector<BITMAPCLASS*> m_vector;
vector<BITMAPCLASS*>::iterator iter;
LPCTSTR lpszClass = TEXT("BitMap"); //클래스 명 : 창이름
void InformationSave(HWND hWnd);

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

	InformationSave(hWnd); //비트맵 정보 저장 

	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

void InformationSave(HWND hWnd)//비트맵 정보 저장
{
	HDC hdc;
	PAINTSTRUCT ps;
	bitclass = new BITMAPCLASS;
	hdc = BeginPaint(hWnd, &ps);
	bitclass->Init(hdc, g_hInst, IDB_BITMAP1);
	bitclass->Information(100, 100, 145, 235, "강아지");
	m_vector.push_back(bitclass);
	bitclass = new BITMAPCLASS;
	bitclass->Init(hdc, g_hInst, IDB_BITMAP1);
	bitclass->Information(300, 100, 290, 470, 145, 235, "강아지");
	m_vector.push_back(bitclass);
	bitclass = new BITMAPCLASS;
	bitclass->Init(hdc, g_hInst, IDB_BITMAP2);
	bitclass->Information(600, 100, 145, 235, "호랑이");
	m_vector.push_back(bitclass);
	bitclass = new BITMAPCLASS;
	bitclass->Init(hdc, g_hInst, IDB_BITMAP3);
	bitclass->Information(800, 100, 145, 235, "오리");
	m_vector.push_back(bitclass);
	bitclass = new BITMAPCLASS;
	bitclass->Init(hdc, g_hInst, IDB_BITMAP4);
	bitclass->Information(1000, 100, 145, 235, "코끼리");
	m_vector.push_back(bitclass);
	bitclass = new BITMAPCLASS;
	bitclass->Init(hdc, g_hInst, IDB_BITMAP5);
	bitclass->Information(600, 400, 145, 235, "말");
	m_vector.push_back(bitclass);
	bitclass = new BITMAPCLASS;
	bitclass->Init(hdc, g_hInst, IDB_BITMAP6);
	bitclass->Information(800, 400, 145, 235, "소");
	m_vector.push_back(bitclass);
	bitclass = new BITMAPCLASS;
	bitclass->Init(hdc, g_hInst, IDB_BITMAP7);
	bitclass->Information(1000, 400, 145, 235, "고양이");
	m_vector.push_back(bitclass);
	bitclass = new BITMAPCLASS;
	bitclass->Init(hdc, g_hInst, IDB_BITMAP8);
	bitclass->Information(1200, 100, 145, 235, "원숭이");
	m_vector.push_back(bitclass);
	bitclass = new BITMAPCLASS;
	bitclass->Init(hdc, g_hInst, IDB_BITMAP9);
	bitclass->Information(1200, 400, 145, 235, "개구리");
	m_vector.push_back(bitclass);
	bitclass = new BITMAPCLASS;
	bitclass->Init(hdc, g_hInst, IDB_BITMAP10);
	bitclass->Information(100, 400, 145, 235, "닭");
	m_vector.push_back(bitclass);


}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;	
	PAINTSTRUCT ps;
	int x, y;
	string Name;
	char name[100];
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, TRUE);
		for (iter = m_vector.begin(); iter != m_vector.end(); iter++)
		{
			bitclass = *iter;
			if ((x > bitclass->Getx() && x < bitclass->Getx() + bitclass->GetWidth()) && (y > bitclass->Gety() && y < bitclass->Gety() + bitclass->GetHeight()))//x좌표가 비트맵 크기 안에 있을떄
			{
				Name = bitclass->GetName() + "입니다.";
				strcpy(name, Name.c_str());
				MessageBox(hWnd, TEXT(name), TEXT("무슨 동물 일까요.?"), MB_OK);
				return 0;
			}
		}
		
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (iter = m_vector.begin(); iter != m_vector.end(); iter++)
		{
			bitclass = *iter;
			bitclass->draw(hdc);
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		m_vector.clear();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}
