#include<windows.h>
#include<vector>
#include<algorithm>

using namespace std;
#define BUFSIZE 100
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("��ŷ�ý��ۿ���"); //â�̸�


int Score = 0;

HANDLE hFile;
DWORD dwRead;
TCHAR g_Scoare[BUFSIZE];  //int�� ���ڿ��� �ٲٴ°�

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
	//WndClass�� �⺻ ������ȯ���� ����� ����ü��. �ɹ������� �ؿ��� ����.
	WndClass.cbClsExtra = 0; //���࿵��
	WndClass.cbWndExtra = 0; //���࿵�� (�Ű�x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//������ ���
	WndClass.hInstance = hInstance;//(���α׷� �ڵ鰪(��ȣ)���)
	WndClass.lpfnWndProc = WndProc;	//���μ��� �Լ� ȣ��
	WndClass.lpszClassName = lpszClass;	//Ŭ���� �̸�
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//�������� ������ ������ ���� �� �ٽ� �׸���.
	RegisterClass(&WndClass);  //������� WidClass�� ���

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))//����ڿ��� �޽����� �޾ƿ��� �Լ�(WM_QUIT �޽��� ���� �� ����)
	{
		TranslateMessage(&Message); //  Ű���� �Է� �޽��� ó���Լ�
		DispatchMessage(&Message); //���� �޽����� WndProc�� �����ϴ� �Լ�
	}
	return (int)Message.wParam;
}

void MyTextPrint(HDC hdc, LPRECT rect, LPSTR str) // �� ��� �Լ� (���� �� ���)
{
	DrawText(hdc, str, -1, rect, DT_CENTER | DT_VCENTER);//TextOut�Լ��� �ٸ��� �������� ����Ҽ��ִ�.(�̰� ��� ����)
}

//���ʸ��콺�� Ŭ���ϸ� ������  �ö󰡰� �����ʸ��콺�� Ŭ���� �Ҷ� ������ �̸��� �Է��ϰ� �̸���  ������ �����ϴ�â�� ����.
//�����Ѱ��� ������ ������ ���� ���� �Ѵ�.
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
			800, 300, 100, 30, hWnd, (HMENU)102, g_hInst, NULL); //���� ������
		CreateWindow("button", "name save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			800, 350, 100, 30, hWnd, (HMENU)103, g_hInst, NULL); //�̸� �����
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

				memset(&OFN, 0, sizeof(OPENFILENAME));//memset�� ����ϴ����� ���ӵȸ޸𸮿� ���� �����ҋ��� for������ �����ӵ��� ���ü��ִ�.
				OFN.lStructSize = sizeof(OPENFILENAME);//OPENFILENAME����ü�� ũ�⸦ �˾ƾ� �Ѵ�.
				OFN.hwndOwner = hWnd; //�����ָ� �����Ѵ�. ������ NULL�Է�
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
				//  CREATE_NEW or 1 : ���� ���� ���� �������� ���� ��쿡 �� ������ �����. ������ �̹� �����ϸ� ERROR_FILE_EXISTS (80)������ �߻���Ű�� fail�� �����Ѵ�.
				//	CREATE_ALWAYS or 2 : �׻� �� ������ �����.�̹� ���� �� ��� ���� ������ �� ���Ϸ� ���� ����.������ �̹� �����ϸ� ERROR_ALREADY_EXISTS(183)������ �߻��ǳ� success�� �����Ѵ�.
				//	OPEN_EXISTING or 3 : ������ ���� �� ��쿡�� ����.������ �������� ���� ��� ERROR_FILE_NOT_FOUND(2)
				//	OPEN_ALWAYS or 4 : ������ ���� �� ��� ����, �������� ������ ���� ����� ����.�������� ���� ��� ERROR_ALREADY_EXISTS(183)
				//	TRUNCATE_EXISTING or 5 : ������ ������ ��� ������ �ʱ�ȭ �ϰ�(ũ�⸦ 0����) ����.������ �������� ���� ��� ERROR_FILE_NOT_FOUND(2) ������ �߻���Ų��.
				DWORD writeB;

				

				//�������� ������ �����ϴ�.
				WriteFile(hFile, g_Scoare, sizeof(g_Scoare), &writeB, NULL);
				WriteFile(hFile, g_str, sizeof(g_str), &writeB, NULL);
				
				
				MessageBox(hWnd, "����", "Save", MB_OK);
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
					MessageBox(hWnd, g_str, "������ �����ϴ�.", MB_OK);
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
				wsprintf(g_Scoare, "%d��", Score);
				
				InvalidateRect(hWnd, NULL, false);
			}
			break;
			case 103://�̸� �����
			{
				if (MessageBox(hWnd, "�̸��� �����ϼ���. ", "�̸��� �Է��ϼ���.", MB_OK) == IDOK)
				{
					//�̸��� ����
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

			if ((TCHAR)wParam == '\b') // �� �����̽��� ���
				memmove(g_str + (str_len - 1), g_str + str_len, sizeof(TCHAR));//memmove �޸𸮸� �̵��Ѵ�. memcpy�� ��� �����Ѵ�. �������� memmove�� �پ��.
			else if ((TCHAR)wParam == '\r') // ������ ���
			{
				g_bcheck = true;
				//rnaking.cpp�� ���� �Ѱ��ְ� ���� �ʱ�ȭ
				Score = 0;
				wsprintf(g_Scoare, "%d��", Score);
				g_str[str_len] = {0};
			}
			else
			{
				// WM_CHAR �޽����� �Էµ� ���ڸ� wParam���� �����Ѵ�.
				g_str[str_len] = (TCHAR)wParam;
				g_str[str_len + 1] = 0;
			}
			// ������ WM_PAINT �޽����� �߻���Ŵ

			// (3��° ����: ȭ�� ����� �ɼ� [TRUE:�����o, FALSE:�����x])
			InvalidateRect(hWnd, NULL, TRUE);
		}		
		return 0;
	case WM_PAINT: // ȭ�� ��ȭ �߻��� - �ٽ� �׸�
		hdc = BeginPaint(hWnd, &ps); // DC Handle ���
		if (g_bcheck == false)
		{		
			TextOut(hdc, 300, 50, "�̸��� �Է��ϼ���", 17);
			MyTextPrint(hdc, &rect, g_str);
		}
		else
		{
			TextOut(hdc, 650, 100, g_Scoare, lstrlen(g_Scoare));
		}
		EndPaint(hWnd, &ps); // DC Handle ����
		return 0;
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}

