#include<Windows.h>
#include<math.h>

#define PIE 3.141592f
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//글로벌 인스턴스핸들값
LPCTSTR lpszClass = TEXT("KeyDown"); //클래스 명 : 창이름
	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass는 기본 윈도우환경을 만드는 구조체다. 맴버변수는 밑에와 같다.
	WndClass.cbClsExtra = 0; //예약영역
	WndClass.cbWndExtra = 0; //예약영역 (신경x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //아이콘 모양
	WndClass.hInstance = hInstance; //(프로그램 핸들값(번호)등록)
	WndClass.lpfnWndProc = WndProc; //프로세스 함수 호출
	WndClass.lpszClassName = lpszClass; //클레스 이름
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //윈도우의 수직과 수평이 변경 시 다시 그린다.
	RegisterClass(&WndClass); //만들어진 WidClass를 등록
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
		(HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, NULL, 0, 0)) //사용자에게 메시지를 받아오는 함수(WM_QUIT 메시지 받을 시 종료), 메시지가 오기까지 대기를 하고있다가 오면 작동.
	{
		TranslateMessage(&Message); // 키보드 입력 메시지 처리함수
		DispatchMessage(&Message); //받은 메시지를 WndProc에 전달하는 함수
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
		if (Mouse_x - 50 < rt.left || Mouse_x + 50 > rt.right) //x좌표가 밖일떄 y축움직임
		{			//x축
			if (Mouse_y - 50 >= rt.top && Mouse_y + 50 <= rt.bottom) //y축이 사각형범위 안에 있을때에
			{
				Mouse_y = HIWORD(lParam); //y축만 움직임
				temporary_x = LOWORD(lParam); //임시 x축에 저장
			}
			else
			{
				temporary_y = HIWORD(lParam); //임시 y축에 저장
				temporary_x = LOWORD(lParam); //임시 x축에 저장
				if (temporary_y - 50 > rt.top && temporary_y + 50 < rt.bottom)
				{
					Mouse_y = HIWORD(lParam);
					temporary_x = LOWORD(lParam);
				}
			}
			if (temporary_x - 50 > rt.left && temporary_x + 50 < rt.right) //만약 임시 x축이 안으로 올경우 작동
			{
				Mouse_y = HIWORD(lParam);				
				Mouse_x = LOWORD(lParam);
			}
						
		}
		else if ((Mouse_x - 50 >= rt.left && Mouse_y - 50 >= rt.top) && (Mouse_x + 50 <= rt.right && Mouse_y - 50 >= rt.top) && (Mouse_x - 50 >= rt.left && Mouse_y + 50 <= rt.bottom)
			&& (Mouse_x + 50 <= rt.right && Mouse_y - 50 >= rt.top))
		{//내부
			Mouse_x = LOWORD(lParam);
			Mouse_y = HIWORD(lParam);
		}
		else if (Mouse_y + 50 > rt.bottom || Mouse_y - 50 < rt.top) // y좌표가 위에있을떄 x좌표 움직임
		{//y축
			if (Mouse_x - 50 >= rt.left && Mouse_x + 50 <= rt.right) //x축이 사각형범위 안에 있을때에
			{
				Mouse_x = LOWORD(lParam);
				temporary_y = HIWORD(lParam);
			}
			else
			{
				temporary_y = HIWORD(lParam); //임시 y축에 저장
				temporary_x = LOWORD(lParam); //임시 x축에 저장
				if (temporary_x - 50 > rt.left && temporary_x + 50 < rt.right)
				{
					Mouse_x = LOWORD(lParam);
					temporary_y = HIWORD(lParam);
				}
			}
			if (temporary_y + 50 < rt.bottom && temporary_y - 50 > rt.top)//사각형 안에 있을경우 
			{
				Mouse_x = LOWORD(lParam);
				Mouse_y = HIWORD(lParam);
			}			
		}
		InvalidateRect(hWnd, &rt, TRUE);
		return 0;
	case WM_LBUTTONDOWN:
		if (MessageBox(hWnd, TEXT("도형을 바꾸겠습니다."), TEXT("도형 바꾸기"), MB_OK) == IDOK)
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
	case WM_DESTROY: // 윈도우가 파괴되었다는 메세지
		PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보낸다.
		return 0; //WndProc의 Switch는 break 대신 return 0; 를 쓴다.
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case에 있는 메시지를 제외한 나머지 메시지를 처리한다.
}
