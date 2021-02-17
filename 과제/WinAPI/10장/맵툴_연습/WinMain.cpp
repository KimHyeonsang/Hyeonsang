#include<windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//글로벌 인스턴스핸들값
LPCTSTR lpszClass = TEXT("MapTool 연습"); //창이름

TCHAR buf[1024];
int Score = 0;
HANDLE hFile;
DWORD dwRead;

#define WIDTH 33
#define HEIGHT 33
#define BLACKSTAR 1
#define WHITESTAR 2
#define CIRCLE 0
int Width = 17;
int Height = 17;

int g_map[13][15];

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass는 기본 윈도우환경을 만드는 구조체다. 맴버변수는 밑에와 같다.
	WndClass.cbClsExtra = 0; //예약영역
	WndClass.cbWndExtra = 0; //예약영역 (신경x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//아이콘 모양
	WndClass.hInstance = hInstance;//(프로그램 핸들값(번호)등록)
	WndClass.lpfnWndProc = WndProc;	//프로세스 함수 호출
	WndClass.lpszClassName = lpszClass;	//클레스 이름
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//윈도우의 수직과 수평이 변경 시 다시 그린다.
	RegisterClass(&WndClass);  //만들어진 WidClass를 등록

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))//사용자에게 메시지를 받아오는 함수(WM_QUIT 메시지 받을 시 종료)
	{
		TranslateMessage(&Message); //  키보드 입력 메시지 처리함수
		DispatchMessage(&Message); //받은 메시지를 WndProc에 전달하는 함수
	}
	return (int)Message.wParam;
}
int g_ishowplayer;

//왼쪽마우스를 클릭하면 점수가  올라가고 오른쪽마우스를 클릭을 할때 저장할 이름을 입력하고 이름과  점수를 저장하는창을 띄운다.
//저장한것의 점수가 높으면 위로 가게 한다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HFONT hFont, OldFont;
	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow("button", "플레이어 모습 변화", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			1200, 100, 150, 100, hWnd, (HMENU)90, g_hInst, NULL);
		CreateWindow("button", "★", WS_CHILD | WS_VISIBLE |BS_AUTORADIOBUTTON,
			1210, 120, 100, 30, hWnd, (HMENU)91, g_hInst, NULL);
		CreateWindow("button", "☆", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			1210, 140, 100, 30, hWnd, (HMENU)92, g_hInst, NULL);
		CreateWindow("button", "○(기본)", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			1210, 160, 100, 30, hWnd, (HMENU)93, g_hInst, NULL);

		CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			1200, 400, 100, 30, hWnd, (HMENU)100, g_hInst, NULL);
		CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
			1200, 450, 100, 30, hWnd, (HMENU)101, g_hInst, NULL);

		CheckRadioButton(hWnd, 91, 92, 93);

		memset(g_map, 0, sizeof(int) * Width * Height);
		g_map[2][2] = 1;
		return 0;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 91:
			g_ishowplayer = BLACKSTAR;
			InvalidateRect(hWnd, NULL, false);
			break;
		case 92:
			g_ishowplayer = WHITESTAR;
			InvalidateRect(hWnd, NULL, false);
			break;
		case 93:
			g_ishowplayer = CIRCLE;
			InvalidateRect(hWnd, NULL, false);
			break;
		case 100: //SAVE
		{
			OPENFILENAME OFN;
			char str[300];
			char IpstrFile[MAX_PATH] = "";
			char IpstrPath[MAX_PATH] = "";

			memset(&OFN, 0, sizeof(OPENFILENAME));//memset을 사용하는이유 연속된메모리에 값을 지정할떄는 for문보다 빠른속도가 나올수있다.
			OFN.lStructSize = sizeof(OPENFILENAME);//OPENFILENAME구조체의 크기를 알아야 한다.
			OFN.hwndOwner = hWnd; //소유주를 지정한다. 없으면 NULL입력
			OFN.lpstrFilter = "Every FIle(*.*)\0*.*\0Text File(*.txt)\0*.txt;*doc\0";
			OFN.lpstrFile = IpstrFile;
			OFN.nMaxFile = 256;
			GetCurrentDirectory(MAX_PATH, IpstrPath);
			OFN.lpstrInitialDir = IpstrPath;

			if (GetSaveFileName(&OFN) == 0)
			{
				DWORD err = CommDlgExtendedError();
				break;
			}
			HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL,
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			DWORD writeB;
			wsprintf(buf, "%d", g_ishowplayer);
			WriteFile(hFile, buf, sizeof(buf), &writeB, NULL);

			for (int i = 0;i < Width;i++)
			{
				for (int j = 0;j < Height;j++)
				{
					WriteFile(hFile, &g_map[i][j], sizeof(int), &writeB, NULL);
				}
			}
			MessageBox(hWnd, "성공", "Save", MB_OK);
			CloseHandle(hFile);
			InvalidateRect(hWnd, NULL, false);
		}
		break;
		case 101://load   맵들을 저장을 하고 
		{
			HANDLE hFile = CreateFile("Test.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			DWORD readB;

			ReadFile(hFile, buf, sizeof(buf), &readB, NULL);
 			g_ishowplayer = atoi(buf); //문자를 정수로 변환
			for (int i = 0;i < Width;i++)
			{
				for (int j = 0;j < Height;j++)
				{
					ReadFile(hFile, &g_map[i][j], sizeof(int), &readB, NULL);
				}
			}
			CloseHandle(hFile);
			InvalidateRect(hWnd, NULL, false);
		}
		break;
		return 0;
		}
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (int i = 0; i < Width; i++)
		{
			for (int j = 0; j < Height; j++)
			{
				if (g_map[i][j] == 0)
				{
					HPEN m_Collider = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					HPEN m_oldCollider = (HPEN)SelectObject(hdc, m_Collider);
					Rectangle(hdc, i * WIDTH, j * HEIGHT, (i + 1) * WIDTH, (j + 1) * HEIGHT);
				}
				else if (g_map[i][j] == 1)
				{
					/*HPEN m_Collider = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					HPEN m_oldCollider = (HPEN)SelectObject(hdc, m_Collider);
					Ellipse(hdc, i * WIDTH, j * HEIGHT, (i + 1) * WIDTH, (j + 1) * HEIGHT);*/
					HPEN m_Collider = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					HPEN m_oldCollider = (HPEN)SelectObject(hdc, m_Collider);
					switch (g_ishowplayer)
					{
					case CIRCLE:
						
						Ellipse(hdc, i * WIDTH, j * HEIGHT, (i + 1) * WIDTH, (j + 1) * HEIGHT);
						break;
					case BLACKSTAR:
						hFont = CreateFont(32, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
						OldFont = (HFONT)SelectObject(hdc, hFont);
						TextOut(hdc, i * WIDTH, j * HEIGHT,"★",2);
						SelectObject(hdc, OldFont);
						DeleteObject(hFont);
						break;
					case WHITESTAR:
						hFont = CreateFont(32, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
						OldFont = (HFONT)SelectObject(hdc, hFont);
						TextOut(hdc, i * WIDTH, j * HEIGHT, "☆", 2);
						SelectObject(hdc, OldFont);
						DeleteObject(hFont);
						break;
					}
				}
			}
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
		PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
		return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}
