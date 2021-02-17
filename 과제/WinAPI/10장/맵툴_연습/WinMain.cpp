#include<windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("MapTool ����"); //â�̸�

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
int g_ishowplayer;

//���ʸ��콺�� Ŭ���ϸ� ������  �ö󰡰� �����ʸ��콺�� Ŭ���� �Ҷ� ������ �̸��� �Է��ϰ� �̸���  ������ �����ϴ�â�� ����.
//�����Ѱ��� ������ ������ ���� ���� �Ѵ�.
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HFONT hFont, OldFont;
	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow("button", "�÷��̾� ��� ��ȭ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			1200, 100, 150, 100, hWnd, (HMENU)90, g_hInst, NULL);
		CreateWindow("button", "��", WS_CHILD | WS_VISIBLE |BS_AUTORADIOBUTTON,
			1210, 120, 100, 30, hWnd, (HMENU)91, g_hInst, NULL);
		CreateWindow("button", "��", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			1210, 140, 100, 30, hWnd, (HMENU)92, g_hInst, NULL);
		CreateWindow("button", "��(�⺻)", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
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
			MessageBox(hWnd, "����", "Save", MB_OK);
			CloseHandle(hFile);
			InvalidateRect(hWnd, NULL, false);
		}
		break;
		case 101://load   �ʵ��� ������ �ϰ� 
		{
			HANDLE hFile = CreateFile("Test.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			DWORD readB;

			ReadFile(hFile, buf, sizeof(buf), &readB, NULL);
 			g_ishowplayer = atoi(buf); //���ڸ� ������ ��ȯ
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
						hFont = CreateFont(32, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ü�"));
						OldFont = (HFONT)SelectObject(hdc, hFont);
						TextOut(hdc, i * WIDTH, j * HEIGHT,"��",2);
						SelectObject(hdc, OldFont);
						DeleteObject(hFont);
						break;
					case WHITESTAR:
						hFont = CreateFont(32, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ü�"));
						OldFont = (HFONT)SelectObject(hdc, hFont);
						TextOut(hdc, i * WIDTH, j * HEIGHT, "��", 2);
						SelectObject(hdc, OldFont);
						DeleteObject(hFont);
						break;
					}
				}
			}
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}
