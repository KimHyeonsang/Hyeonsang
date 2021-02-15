#include<windows.h>
#include<vector>
#include<algorithm>

using namespace std;
#define BUFSIZE 100
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//글로벌 인스턴스핸들값
LPCTSTR lpszClass = TEXT("랭킹시스템연습"); //창이름


int Score = 0;

HANDLE hFile;
DWORD dwRead;
TCHAR g_Scoare[BUFSIZE];  //int를 문자열로 바꾸는것

RECT rect = { 100, 100, 500, 450 };
MSG Message;


static TCHAR g_str[BUFSIZE];
int str_len;
bool g_bcheck = true;
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

void MyTextPrint(HDC hdc, LPRECT rect, LPSTR str) // 글 출력 함수 (여러 줄 출력)
{
	DrawText(hdc, str, -1, rect, DT_CENTER | DT_VCENTER);//TextOut함수와 다르게 여러줄을 출력할수있다.(이건 가운데 정렬)
}

//왼쪽마우스를 클릭하면 점수가  올라가고 오른쪽마우스를 클릭을 할때 저장할 이름을 입력하고 이름과  점수를 저장하는창을 띄운다.
//저장한것의 점수가 높으면 위로 가게 한다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT  ps;

	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			800, 400, 100, 30, hWnd, (HMENU)100, g_hInst, NULL);
		CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			800, 450, 100, 30, hWnd, (HMENU)101, g_hInst, NULL);
		CreateWindow("button", "Score Up", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			800, 300, 100, 30, hWnd, (HMENU)102, g_hInst, NULL); //점수 증가용
		CreateWindow("button", "name save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			800, 350, 100, 30, hWnd, (HMENU)103, g_hInst, NULL); //이름 저장용
		return 0;
	case WM_COMMAND:
	{
		if (g_bcheck == true)
		{
			switch (LOWORD(wParam))
			{
			case 100: //SAVE
			{
				OPENFILENAME OFN;
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
				//  CREATE_NEW or 1 : 같은 파일 명이 존재하지 않을 경우에 새 파일을 만든다. 파일이 이미 존재하면 ERROR_FILE_EXISTS (80)에러를 발생시키고 fail을 리터한다.
				//	CREATE_ALWAYS or 2 : 항상 새 파일을 만든다.이미 존재 할 경우 기존 파일을 새 파일로 덮어 쓴다.파일이 이미 존재하면 ERROR_ALREADY_EXISTS(183)에러가 발생되나 success를 리턴한다.
				//	OPEN_EXISTING or 3 : 파일이 존재 할 경우에만 연다.파일이 존재하지 않을 경우 ERROR_FILE_NOT_FOUND(2)
				//	OPEN_ALWAYS or 4 : 파일이 존재 할 경우 열고, 존재하지 않으면 새로 만들고 연다.존재하지 않을 경우 ERROR_ALREADY_EXISTS(183)
				//	TRUNCATE_EXISTING or 5 : 파일이 존재할 경우 파일을 초기화 하고(크기를 0으로) 연다.파일이 존재하지 않을 경우 ERROR_FILE_NOT_FOUND(2) 오류를 발생시킨다.
				DWORD writeB;

				

				//여러개를 저장이 가능하다.
				WriteFile(hFile, g_Scoare, sizeof(g_Scoare), &writeB, NULL);
				WriteFile(hFile, g_str, sizeof(g_str), &writeB, NULL);
				
				
				MessageBox(hWnd, "성공", "Save", MB_OK);
				CloseHandle(hFile);
				InvalidateRect(hWnd, NULL, false);
			}
			break;
			case 101://load
			{
				HANDLE hFile = CreateFile("save.txt", GENERIC_READ, 0, NULL,
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
				DWORD readB;

				ReadFile(hFile, g_Scoare, sizeof(g_Scoare), &readB, NULL);
				ReadFile(hFile, g_str, sizeof(g_str), &readB, NULL);
				
				
				if (!hFile)
				{
					MessageBox(hWnd, g_str, "파일이 없습니다.", MB_OK);
				}
				MessageBox(hWnd, g_Scoare, "Load", MB_OK);
				MessageBox(hWnd, g_str, "Load", MB_OK);
				CloseHandle(hFile);
				InvalidateRect(hWnd, NULL, false);
			}
			break;
			case 102://score up
			{
				Score += 100;
				wsprintf(g_Scoare, "%d점", Score);
				
				InvalidateRect(hWnd, NULL, false);
			}
			break;
			case 103://이름 저장용
			{
				if (MessageBox(hWnd, "이름을 저장하세요. ", "이름을 입력하세요.", MB_OK) == IDOK)
				{
					//이름을 저장
				//	Ranking::GetInstance()->Saveraingking(Score);
					g_bcheck = false;
					//	TextOut(hdc, 100, 100, str, strlen(str));
					InvalidateRect(hWnd, NULL, false);
				}
			}
			break;
			}
		}
		return 0;
	}
	case WM_CHAR:
		if (g_bcheck == false)
		{
			str_len = lstrlen(g_str);

			if ((TCHAR)wParam == '\b') // 백 스페이스일 경우
				memmove(g_str + (str_len - 1), g_str + str_len, sizeof(TCHAR));//memmove 메모리를 이동한다. memcpy랑 비슷 복사한다. 안정성은 memmove가 뛰어나다.
			else if ((TCHAR)wParam == '\r') // 엔터일 경우
			{
				g_bcheck = true;
				//rnaking.cpp에 값을 넘겨주고 점수 초기화
				Score = 0;
				wsprintf(g_Scoare, "%d점", Score);
				g_str[str_len] = {0};
			}
			else
			{
				// WM_CHAR 메시지는 입력된 문자를 wParam으로 전달한다.
				g_str[str_len] = (TCHAR)wParam;
				g_str[str_len + 1] = 0;
			}
			// 강제로 WM_PAINT 메시지를 발생시킴

			// (3번째 인자: 화면 지우기 옵션 [TRUE:지우기o, FALSE:지우기x])
			InvalidateRect(hWnd, NULL, TRUE);
		}		
		return 0;
	case WM_PAINT: // 화면 변화 발생시 - 다시 그림
		hdc = BeginPaint(hWnd, &ps); // DC Handle 얻기
		if (g_bcheck == false)
		{		
			TextOut(hdc, 300, 50, "이름을 입력하세요", 17);
			MyTextPrint(hdc, &rect, g_str);
		}
		else
		{
			TextOut(hdc, 650, 100, g_Scoare, lstrlen(g_Scoare));
		}
		EndPaint(hWnd, &ps); // DC Handle 해제
		return 0;
	case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
		PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
		return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}

