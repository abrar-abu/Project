/*
#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int PaintFlag;
HBRUSH hbrush;
MONITORINFO mi;

WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbFullscreen = false;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevImstance, LPSTR CmdLine, int nCmdShow)
{
	HWND hwnd;
	WNDCLASSEX wndclass;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDOW");
	TCHAR button[] = TEXT("button");
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, TEXT("MYICON"));
	wndclass.hIconSm = LoadIcon(hInstance, TEXT("MYICON"));
	wndclass.hInstance = hInstance;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("MARKETAPP"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	GetWindowLong(hwnd, GWL_STYLE);
	mi = { sizeof(MONITORINFO) };
	if (GetWindowPlacement(hwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(hwnd, MONITORINFOF_PRIMARY), &mi))
	{

		SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(hwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
	}
	if (NULL == hwnd)
	{
		MessageBox(NULL, TEXT("WINDOW NOT CREATED"), TEXT("ERROR..."), 0);
		exit(0);
	}

	ShowWindow(hwnd, SW_MAXIMIZE);
	//UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc_heading,hdc_content,hdc_;
	PAINTSTRUCT ps;
	RECT rc;
	int i;
	TCHAR string[9][50] = { TEXT("DEVICE"),TEXT("COMPANY"),TEXT("SUB-TYPE"),TEXT("GENRATION"),TEXT("SIZE"),TEXT("MODEL"),TEXT("INCES"),TEXT("PRICE") ,TEXT("TOTAL")};
	TCHAR str[12][60] = { TEXT("CPU	"),TEXT("RAM "),TEXT("Motherboard"),TEXT("Graphics Card"),TEXT("Hard Disks"),TEXT("CD/DVD Drive"),
		TEXT("SMPS"),TEXT("Cabinet"),TEXT("Keyboard"),TEXT("Mouse"),TEXT("Monitor"),TEXT("Printer") };
	TCHAR str1[256];
	//TextOut(hdc, 450, 200, str, wcslen(str));

	//TextOut variables
	HPEN hPen;
	static HDC hdc;
	static int cxClient, cyClient;
	HBRUSH hBrush;
	RECT rect;

	switch (imsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, TEXT("WELCOME TO MARKETAPP"), TEXT("MESSAGE"), MB_OK);
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;
	case WM_PAINT:
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);

		FillRect(hdc, &ps.rcPaint, hBrush);
		ReleaseDC(hwnd, hdc);
		DeleteObject(hBrush);

		SetBkColor(hdc, RGB(255, 255, 255));
		hdc_heading = GetDC(hwnd);
		hdc_content = GetDC(hwnd);
		hdc = GetDC(hwnd);
		SetTextColor(hdc_heading, RGB(255, 0, 0));
		SetBkMode(hdc_heading, TRANSPARENT);
		SelectObject(hdc_heading, CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Castellar")));

		TextOut(hdc_heading, 10, 55, string[0], lstrlen(string[0]));
		TextOut(hdc_heading, 185, 55, string[1], lstrlen(string[1]));
		TextOut(hdc_heading, 440, 55, string[2], lstrlen(string[2]));
		TextOut(hdc_heading, 585, 55, string[3], lstrlen(string[3]));
		TextOut(hdc_heading, 785, 55, string[4], lstrlen(string[4]));
		TextOut(hdc_heading, 885, 55, string[5], lstrlen(string[5]));
		TextOut(hdc_heading, 1140, 55, string[6], lstrlen(string[6]));
		TextOut(hdc_heading, 1240, 55, string[7], lstrlen(string[7]));
		TextOut(hdc_heading, 10, 425, string[8], lstrlen(string[8]));

		for (int i = 0,y=85; i < 12; i++,y=y+28)
		{
			TextOut(hdc_heading, 10, y, str[i], lstrlen(str[i]));
		}
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		//hPen = (HPEN)GetStockObject(WHITE_PEN);
		SelectObject(hdc, hPen);
		MoveToEx(hdc, 0, 80, NULL);   //horizontal top 1
		LineTo(hdc, cxClient, 80);

		MoveToEx(hdc, 0, 50, NULL);    //horizontal top 2
		LineTo(hdc, cxClient, 50);

		MoveToEx(hdc, 0, 420, NULL);    //hotizontal bottom 1
		LineTo(hdc, cxClient, 420);

		MoveToEx(hdc, 0, 450, NULL);    //horizontal bottom 2
		LineTo(hdc, cxClient, 450);

		MoveToEx(hdc, 175, 50, NULL);    //vertical left1
		LineTo(hdc, 175, 450);

		MoveToEx(hdc, 430, 50, NULL);    //vertical left2
		LineTo(hdc, 430, 450);

		MoveToEx(hdc, 575, 50, NULL);    //vertical left3
		LineTo(hdc, 575, 450);

		MoveToEx(hdc, 775, 50, NULL);    //vertical left4
		LineTo(hdc, 775, 450);

		MoveToEx(hdc, 875, 50, NULL);    //vertical left5
		LineTo(hdc, 875, 450);

		MoveToEx(hdc,1130, 50, NULL);    //vertical left6
		LineTo(hdc, 1130, 450);

		MoveToEx(hdc, 1230, 50, NULL);    //vertical left7
		LineTo(hdc, 1230, 450);

		ReleaseDC(hwnd, hdc);
		DeleteObject(hPen);

/*
		hdc = BeginPaint(hwnd, &ps);
		Rectangle(hdc, 10, 10, 1300, 425);
		for (int i = 0, x = 80; i < 5; i++, x = x + 270)
		{
			TextOut(hdc, x, 30, string[i], lstrlen(string[i]));
		}
		for (int i = 0, y = 70; i < 12; i++, y = y + 30)
		{
			TextOut(hdc, 20, y, str[i], lstrlen(str[i]));
		}
		MoveToEx(hdc, 11, 61, 0);
		LineTo(hdc, 1300, 61);
		MoveToEx(hdc, 200, 10, 0);
		LineTo(hdc, 200, 425);
		MoveToEx(hdc, 1070, 11, 0);
		LineTo(hdc, 1070, 425);
		MoveToEx(hdc, 794, 11, 0);
		LineTo(hdc, 794, 425);
		MoveToEx(hdc, 541, 11, 0);
		LineTo(hdc, 541, 425);
		ReleaseDC(hwnd, hdc);
		EndPaint(hwnd, &ps);

		break;
	case WM_CLOSE:
		MessageBox(hwnd, TEXT("CLOSING THE WINDOW"), TEXT("MESSAGE"), MB_OK);
		
		break;
	case WM_DESTROY:
		ReleaseDC(hwnd, hdc);
		ReleaseDC(hwnd, hdc_heading);
		ReleaseDC(hwnd, hdc_content);
		PostQuitMessage(0);
		break;


	}
	return(DefWindowProc(hwnd, imsg, wParam, lParam));
}
*/