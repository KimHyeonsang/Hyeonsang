#include<Windows.h>
#include<math.h>

#define PIE 3.141592f
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("KeyDown"); //Ŭ���� �� : â�̸�
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass�� �⺻ ������ȯ���� ����� ����ü��. �ɹ������� �ؿ��� ����.
	WndClass.cbClsExtra = 0; //���࿵��
	WndClass.cbWndExtra = 0; //���࿵�� (�Ű�x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //������ ���
	WndClass.hInstance = hInstance; //(���α׷� �ڵ鰪(��ȣ)���)
	WndClass.lpfnWndProc = WndProc; //���μ��� �Լ� ȣ��
	WndClass.lpszClassName = lpszClass; //Ŭ���� �̸�
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //�������� ������ ������ ���� �� �ٽ� �׸���.
	RegisterClass(&WndClass); //������� WidClass�� ���
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		(HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, NULL, 0, 0)) //����ڿ��� �޽����� �޾ƿ��� �Լ�(WM_QUIT �޽��� ���� �� ����), �޽����� ������� ��⸦ �ϰ��ִٰ� ���� �۵�.
	{
		TranslateMessage(&Message); // Ű���� �Է� �޽��� ó���Լ�
		DispatchMessage(&Message); //���� �޽����� WndProc�� �����ϴ� �Լ�
	}
	return (int)Message.wParam;
}
	RECT rt = { 50, 50, 1200, 600 };
	enum FIGURE
	{
		FIGURE_SQUARE = 1,
		FIGURE_CIRCLE 
	};
	void temporary_Figure(HDC hdc,FIGURE Figure, int x, int y)
	{
		if (Figure == FIGURE_SQUARE)
			Rectangle(hdc, x - 50, y - 50, x + 50, y + 50);
		else if (Figure == FIGURE_CIRCLE)
			Ellipse(hdc, x - 50, y - 50, x + 50, y + 50);
	}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static FIGURE Figure = FIGURE_CIRCLE;
	static int Mouse_x = 400;
	static int Mouse_y = 400;
	static int temporary_x = 200;
	static int temporary_y = 200;
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			Mouse_x -= 100;
			break;
		case VK_RIGHT:
			Mouse_x += 100;
			break;
		case VK_UP:
			Mouse_y -= 100;
			break;
		case VK_DOWN:
			Mouse_y += 100;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_MOUSEMOVE:
		if (Mouse_x - 50 < rt.left || Mouse_x + 50 > rt.right) //x��ǥ�� ���ϋ� y�������
		{			//x��
			if (Mouse_y - 50 >= rt.top && Mouse_y + 50 <= rt.bottom) //y���� �簢������ �ȿ� ��������
			{
				Mouse_y = HIWORD(lParam); //y�ุ ������
				temporary_x = LOWORD(lParam); //�ӽ� x�࿡ ����
			}
			else
			{
				temporary_y = HIWORD(lParam); //�ӽ� y�࿡ ����
				temporary_x = LOWORD(lParam); //�ӽ� x�࿡ ����
				if (temporary_y - 50 > rt.top && temporary_y + 50 < rt.bottom)
				{
					Mouse_y = HIWORD(lParam);
					temporary_x = LOWORD(lParam);
				}
			}
			if (temporary_x - 50 > rt.left && temporary_x + 50 < rt.right) //���� �ӽ� x���� ������ �ð�� �۵�
			{
				Mouse_y = HIWORD(lParam);				
				Mouse_x = LOWORD(lParam);
			}
						
		}
		else if ((Mouse_x - 50 >= rt.left && Mouse_y - 50 >= rt.top) && (Mouse_x + 50 <= rt.right && Mouse_y - 50 >= rt.top) && (Mouse_x - 50 >= rt.left && Mouse_y + 50 <= rt.bottom)
			&& (Mouse_x + 50 <= rt.right && Mouse_y - 50 >= rt.top))
		{//����
			Mouse_x = LOWORD(lParam);
			Mouse_y = HIWORD(lParam);
		}
		else if (Mouse_y + 50 > rt.bottom || Mouse_y - 50 < rt.top) // y��ǥ�� ���������� x��ǥ ������
		{//y��
			if (Mouse_x - 50 >= rt.left && Mouse_x + 50 <= rt.right) //x���� �簢������ �ȿ� ��������
			{
				Mouse_x = LOWORD(lParam);
				temporary_y = HIWORD(lParam);
			}
			else
			{
				temporary_y = HIWORD(lParam); //�ӽ� y�࿡ ����
				temporary_x = LOWORD(lParam); //�ӽ� x�࿡ ����
				if (temporary_x - 50 > rt.left && temporary_x + 50 < rt.right)
				{
					Mouse_x = LOWORD(lParam);
					temporary_y = HIWORD(lParam);
				}
			}
			if (temporary_y + 50 < rt.bottom && temporary_y - 50 > rt.top)//�簢�� �ȿ� ������� 
			{
				Mouse_x = LOWORD(lParam);
				Mouse_y = HIWORD(lParam);
			}			
		}
		InvalidateRect(hWnd, &rt, TRUE);
		return 0;
	case WM_LBUTTONDOWN:
		if (MessageBox(hWnd, TEXT("������ �ٲٰڽ��ϴ�."), TEXT("���� �ٲٱ�"), MB_OK) == IDOK)
		{
			if (Figure == FIGURE_SQUARE)
				Figure = FIGURE_CIRCLE;
			else if (Figure == FIGURE_CIRCLE)
				Figure = FIGURE_SQUARE;

		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, 50, 50, 1200, 600);
		temporary_Figure(hdc, Figure, Mouse_x, Mouse_y);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY: // �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}
