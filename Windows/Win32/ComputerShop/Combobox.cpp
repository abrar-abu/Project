
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

#include "Images.h"
#include "MyDaialog.h"
#include "MyReciept.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyReciptProc(HWND, UINT, WPARAM, LPARAM);

void DisplayError(LPTSTR lpszFunction);
void CreateMyOwnFile(TCHAR[]);
void CreateMyOwnWriteFile(TCHAR[]);

HANDLE hFile;
DWORD dwBytesWritten = 0;
BOOL bErrorFlag = FALSE;
BOOL TextOut_Flag = FALSE;
BOOL RECIEPT_FLAG = FALSE;
HDC hdcStatic;

HINSTANCE hInstance = NULL;
HBITMAP bitMap;
HWND ghwnd = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("Computer Shop");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, TEXT("IDI_ICON1"));
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, AppName,TEXT("COMPUTER SHOP"),WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 0, 0, 800, 600,NULL, NULL, hInstance, NULL);

	if (NULL == hwnd)
	{
		MessageBox(NULL, TEXT("Window not created "), TEXT("Error..."), 0);
		exit(0);
	}
	ghwnd = hwnd;

	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.lParam);
}

LRESULT CALLBACK WndProc(HWND hdlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hMemDC;
	HGDIOBJ oldBitmap;
	BITMAP  bitmap;
	PAINTSTRUCT ps;
	//Temporary
	HDC hdc_escape,hdc;
	//Content Used For WM_PAINT;
	HDC hdc_line,hdc_paint,hdc_contents,hdc_heading;
	static int cxClient, cyClient;
	HPEN hPen;
	HBRUSH hBrush;
	RECT rect;
	switch (iMsg)
	{
	case WM_CREATE:
		hInstance = (HINSTANCE)GetWindowLong(hdlg, GWL_HINSTANCE);
		bitMap = LoadBitmap((HINSTANCE)GetWindowLong(hdlg, GWL_HINSTANCE), MAKEINTRESOURCE(MAIN_WINDOW));
		if (!bitMap)
		{
			MessageBox(NULL, TEXT("IMAGE HAS NOT LOADED"), TEXT("ERROR"), MB_OK);
		}
		break;
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_SPACE:
			DialogBox(hInstance, TEXT("DATAENTRY"), ghwnd, MyDlgProc);
			break;
		case 'W':
		case 'w':
		case VK_ESCAPE:
			InvalidateRect(hdlg, NULL, TRUE);
			PostQuitMessage(0);
			break;
		case 'P':
		case 'p':
			DialogBox(hInstance, TEXT("DATAENTRY1"), ghwnd, MyReciptProc);
			break;
		}
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;
	case WM_PAINT:
		if (TextOut_Flag == FALSE)
		{
			hdc = BeginPaint(hdlg, &ps);
			hMemDC = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hMemDC, bitMap);
			GetObject(bitMap, sizeof(bitmap), &bitmap);
			BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);
			SelectObject(hMemDC, oldBitmap);
			SelectObject(hdc, CreateFont(40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Cooper Black")));
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkColor(hdc, TRANSPARENT);
			SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, 100, 200, TEXT("Click on Spacebar to Continue"), 29);
			DeleteDC(hMemDC);
			EndPaint(hdlg, &ps);
		}
		else
		{
			{
				//To Paint Background
				hBrush = CreateSolidBrush(RGB(0, 0, 0));
				hdc_paint = BeginPaint(hdlg, &ps);
				GetClientRect(hdlg, &rect);

				FillRect(hdc_paint, &ps.rcPaint, hBrush);
				ReleaseDC(hdlg, hdc_paint);
				DeleteObject(hBrush);
			}
			{
				//To Draw Lines 
				hdc_line = GetDC(hdlg);
				hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
				SelectObject(hdc_line, hPen);

				MoveToEx(hdc_line, 0, 80, NULL);   //horizontal top 1
				LineTo(hdc_line, cxClient, 80);

				MoveToEx(hdc_line, 0, 50, NULL);    //horizontal top 2
				LineTo(hdc_line, cxClient, 50);

				MoveToEx(hdc_line, 0, 420, NULL);    //hotizontal bottom 1
				LineTo(hdc_line, cxClient, 420);

				MoveToEx(hdc_line, 0, 450, NULL);    //horizontal bottom 2
				LineTo(hdc_line, cxClient, 450);

				MoveToEx(hdc_line, 175, 50, NULL);    //vertical left1
				LineTo(hdc_line, 175, 450);

				MoveToEx(hdc_line, 380, 50, NULL);    //vertical left2
				LineTo(hdc_line, 380, 450);

				MoveToEx(hdc_line, 575, 50, NULL);    //vertical left3
				LineTo(hdc_line, 575, 450);

				MoveToEx(hdc_line, 775, 50, NULL);    //vertical left4
				LineTo(hdc_line, 775, 450);

				MoveToEx(hdc_line, 875, 50, NULL);    //vertical left5
				LineTo(hdc_line, 875, 450);

				MoveToEx(hdc_line, 1130, 50, NULL);    //vertical left6
				LineTo(hdc_line, 1130, 450);

				MoveToEx(hdc_line, 1230, 50, NULL);    //vertical left7
				LineTo(hdc_line, 1230, 450);

				ReleaseDC(hdlg, hdc_line);
				DeleteObject(hPen);
			}
			{
				//All the Static Contents
				hdc_heading = GetDC(hdlg);
				SetTextColor(hdc_heading, RGB(255, 0, 0));
				SetBkMode(hdc_heading, TRANSPARENT);
				SelectObject(hdc_heading, CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Castellar")));

				TextOut(hdc_heading, 10, 55, st.HEADINGD[0], lstrlen(st.HEADINGD[0]));
				TextOut(hdc_heading, 185, 55, st.HEADINGD[1], lstrlen(st.HEADINGD[1]));
				TextOut(hdc_heading, 390, 55, st.HEADINGD[2], lstrlen(st.HEADINGD[2]));
				TextOut(hdc_heading, 585, 55, st.HEADINGD[3], lstrlen(st.HEADINGD[3]));
				TextOut(hdc_heading, 785, 55, st.HEADINGD[4], lstrlen(st.HEADINGD[4]));
				TextOut(hdc_heading, 885, 55, st.HEADINGD[5], lstrlen(st.HEADINGD[5]));
				TextOut(hdc_heading, 1140, 55, st.HEADINGD[6], lstrlen(st.HEADINGD[6]));
				TextOut(hdc_heading, 1240, 55, st.HEADINGD[7], lstrlen(st.HEADINGD[7]));
				TextOut(hdc_heading, 10, 425, st.HEADINGD[8], lstrlen(st.HEADINGD[8]));

				for (int i = 0, y = 85; i < 12; i++, y = y + 28)
				{
					TextOut(hdc_heading, 10, y, st.DEVICES[i], lstrlen(st.DEVICES[i]));
				}
				SetTextColor(hdc_heading, RGB(0, 255, 0));
				if (RECIEPT_FLAG == FALSE)
				{
					TextOut(hdc_heading, 10, 460, st.MESSAGES[0], lstrlen(st.MESSAGES[0]));
				}
				else 
				{
					TextOut(hdc_heading, 10, 460, st.MESSAGES[1], lstrlen(st.MESSAGES[1]));
				}

				ReleaseDC(hdlg, hdc_heading);
			}
			hdc_escape = GetDC(hdlg);
			SetTextColor(hdc_escape, RGB(0, 255, 0));
			SetBkMode(hdc_escape, TRANSPARENT);
			if (cb.Price != 0)
			{
				TextOut(hdc_escape, 185, 85, si.CPU[0], lstrlen(si.CPU[0]));
				TextOut(hdc_escape, 390, 85, si.CPU[1], lstrlen(si.CPU[1]));
				TextOut(hdc_escape, 585, 85, si.CPU[2], lstrlen(si.CPU[2]));
				TextOut(hdc_escape, 885, 85, si.CPU[3], lstrlen(si.CPU[3]));
				TextOut(hdc_escape, 1240, 85, cb.CPU_PRICE, lstrlen(cb.CPU_PRICE));

				TextOut(hdc_escape, 785, 85, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 85, TEXT("-----"), 5);
			}
			else
			{
				TextOut(hdc_escape, 185, 85, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 85, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 85, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 85, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 85, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 85, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 85, TEXT("-----"), 5);
			}
			if (ram.Price != 0)
			{
				TextOut(hdc_escape, 185, 113, si.RAM[0], lstrlen(si.RAM[0]));
				TextOut(hdc_escape, 785, 113, si.RAM[1], lstrlen(si.RAM[1]));
				TextOut(hdc_escape, 1240, 113, ram.RAM_PRICE, lstrlen(ram.RAM_PRICE));
			
				TextOut(hdc_escape, 585, 113, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 113, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 113, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 113, TEXT("-----"), 5);
			}
			else
			{
				TextOut(hdc_escape, 185, 113, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 113, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 113, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 113, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 113, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 113, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 113, TEXT("-----"), 5);
			}
			if (motherboard.Price != 0)
			{
				TextOut(hdc_escape, 185, 141, si.MOTHERBOARD[0], lstrlen(si.MOTHERBOARD[0]));
				TextOut(hdc_escape, 390, 141, si.MOTHERBOARD[1], lstrlen(si.MOTHERBOARD[1]));
				TextOut(hdc_escape, 1240, 141, motherboard.MOTHERBOARD_PRICE, lstrlen(motherboard.MOTHERBOARD_PRICE));
			
				TextOut(hdc_escape, 585, 141, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 141, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 141, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 141, TEXT("-----"), 5);
			}
			else
			{
				TextOut(hdc_escape, 185, 141, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 141, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 141, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 141, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 141, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 141, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 141, TEXT("-----"), 5);
			}
			if (graphic.Price != 0)
			{
				TextOut(hdc_escape, 185, 169, si.GRAPHIC[0], lstrlen(si.GRAPHIC[0]));
				TextOut(hdc_escape, 390, 169, si.GRAPHIC[1], lstrlen(si.GRAPHIC[1]));
				TextOut(hdc_escape, 785, 169, si.GRAPHIC[2], lstrlen(si.GRAPHIC[2]));
				TextOut(hdc_escape, 1240, 169, graphic.GRAPHIC_PRICE, lstrlen(graphic.GRAPHIC_PRICE));
			
				TextOut(hdc_escape, 585, 169, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 169, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 169, TEXT("-----"), 5);
			
			}
			else
			{
				TextOut(hdc_escape, 185, 169, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 169, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 169, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 169, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 169, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 169, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 169, TEXT("-----"), 5);
			}
			if (harddisk.Price != 0)
			{
				TextOut(hdc_escape, 185, 197, si.HARD[0], lstrlen(si.HARD[0]));
				TextOut(hdc_escape, 785, 197, si.HARD[1], lstrlen(si.HARD[1]));
				TextOut(hdc_escape, 1240, 197, harddisk.HARDDISK_PRICE, lstrlen(harddisk.HARDDISK_PRICE));

				TextOut(hdc_escape, 390, 197, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 197, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 197, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 197, TEXT("-----"), 5);

			}
			else
			{
				TextOut(hdc_escape, 185, 197, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 197, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 197, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 197, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 197, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 197, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 197, TEXT("-----"), 5);
			}
			if (cddvd.Price != 0)
			{
				TextOut(hdc_escape, 185, 225, si.CDDVD[0], lstrlen(si.CDDVD[0]));
				TextOut(hdc_escape, 390, 225, si.CDDVD[1], lstrlen(si.CDDVD[1]));
				TextOut(hdc_escape, 1240, 225, cddvd.CDDVD_PRICE, lstrlen(cddvd.CDDVD_PRICE));
			
				TextOut(hdc_escape, 585, 225, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 225, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 225, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 225, TEXT("-----"), 5);
			
			}
			else
			{
				TextOut(hdc_escape, 185, 225, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 225, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 225, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 225, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 225, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 225, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 225, TEXT("-----"), 5);
			}
			if (smps.Price != 0)
			{
				TextOut(hdc_escape, 185, 253, si.SMPS[0], lstrlen(si.SMPS[0]));
				TextOut(hdc_escape, 1240, 253, smps.SMPS_PRICE, lstrlen(smps.SMPS_PRICE));

				TextOut(hdc_escape, 390, 253, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 253, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 253, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 253, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 253, TEXT("-----"), 5);

			}
			else
			{
				TextOut(hdc_escape, 185, 253, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 253, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 253, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 253, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 253, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 253, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 253, TEXT("-----"), 5);
			}
			if (cabinate.Price != 0)
			{
				TextOut(hdc_escape, 185, 281, si.CABINATE[0], lstrlen(si.CABINATE[0]));
				TextOut(hdc_escape, 390, 281, si.CABINATE[1], lstrlen(si.CABINATE[1]));
				TextOut(hdc_escape, 1240, 281, cabinate.CABINATE_PRICE, lstrlen(cabinate.CABINATE_PRICE));
			
				TextOut(hdc_escape, 585, 281, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 281, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 281, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 281, TEXT("-----"), 5);

			}
			else
			{
				TextOut(hdc_escape, 185, 281, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 281, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 281, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 281, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 281, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 281, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 281, TEXT("-----"), 5);
			}
			if (keyboard.Price != 0) 
			{
				TextOut(hdc_escape, 185, 309, si.KEYBOARD[0], lstrlen(si.KEYBOARD[0]));
				TextOut(hdc_escape, 390, 309, si.KEYBOARD[1], lstrlen(si.KEYBOARD[1]));
				TextOut(hdc_escape, 1240, 309, keyboard.KEYBOARD_PRICE, lstrlen(keyboard.KEYBOARD_PRICE));
			
				TextOut(hdc_escape, 585, 309, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 309, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 309, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 309, TEXT("-----"), 5);
				
			}
			else
			{
				TextOut(hdc_escape, 185, 309, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 309, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 309, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 309, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 309, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 309, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 309, TEXT("-----"), 5);
			}
			if (mouse.Price != 0)
			{
				TextOut(hdc_escape, 185, 337, si.MOUSE[0], lstrlen(si.MOUSE[0]));
				TextOut(hdc_escape, 390, 337, si.MOUSE[1], lstrlen(si.MOUSE[1]));
				TextOut(hdc_escape, 1240, 337, mouse.MOUSE_PRICE, lstrlen(mouse.MOUSE_PRICE));
		
				TextOut(hdc_escape, 585, 337, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 337, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 337, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 337, TEXT("-----"), 5);
			
			}
			else
			{
				TextOut(hdc_escape, 185, 337, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 337, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 337, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 337, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 337, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 337, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 337, TEXT("-----"), 5);
			}
			if (monitor.Price != 0)
			{
				TextOut(hdc_escape, 185, 365, si.MONITOR[0], lstrlen(si.MONITOR[0]));
				TextOut(hdc_escape, 390, 365, si.MONITOR[1], lstrlen(si.MONITOR[1]));
				TextOut(hdc_escape, 1140, 365, si.MONITOR[2], lstrlen(si.MONITOR[2]));
				TextOut(hdc_escape, 1240, 365, monitor.MONITOR_PRICE, lstrlen(monitor.MONITOR_PRICE));
			
				TextOut(hdc_escape, 585, 365, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 365, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 365, TEXT("-----"), 5);
			
			}
			else
			{
				TextOut(hdc_escape, 185, 365, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 365, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 365, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 365, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 365, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 365, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 365, TEXT("-----"), 5);
			}
			if (printer.Price != 0)
			{
				TextOut(hdc_escape, 185, 393, si.PRINTER[0], lstrlen(si.PRINTER[0]));
				TextOut(hdc_escape, 1240, 393, printer.PRINTER_PRICE, lstrlen(printer.PRINTER_PRICE));
			
				TextOut(hdc_escape, 390, 393, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 393, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 393, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 393, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 393, TEXT("-----"), 5);

			}
			else
			{
				TextOut(hdc_escape, 185, 393, TEXT("-----"), 5);
				TextOut(hdc_escape, 390, 393, TEXT("-----"), 5);
				TextOut(hdc_escape, 585, 393, TEXT("-----"), 5);
				TextOut(hdc_escape, 785, 393, TEXT("-----"), 5);
				TextOut(hdc_escape, 885, 393, TEXT("-----"), 5);
				TextOut(hdc_escape, 1140, 393, TEXT("-----"), 5);
				TextOut(hdc_escape, 1240, 393, TEXT("-----"), 5);
			}
			si.Total = cb.Price + ram.Price + motherboard.Price + graphic.Price + harddisk.Price + cddvd.Price + smps.Price + cabinate.Price + keyboard.Price + mouse.Price + monitor.Price + printer.Price;
			_itoa_s(si.Total, si.TOTAL_PRICE, 10);
			if (si.Total != 0)
			{
				TextOut(hdc_escape, 1240, 425, si.TOTAL_PRICE, lstrlen(si.TOTAL_PRICE));
			}
			else
			{
				TextOut(hdc_escape, 1240, 425, TEXT("-----"), 5);
			}
			/*
			si.Total = cb.Price + ram.Price + motherboard.Price + graphic.Price + harddisk.Price + cddvd.Price + smps.Price + cabinate.Price + keyboard.Price + mouse.Price +monitor.Price + printer.Price;
			TextOut(hdc_escape, 10, 600, TEXT("Total"), 5);
			_itoa_s(si.Total, si.TOTAL_PRICE, 10);
			TextOut(hdc_escape, 600, 600, si.TOTAL_PRICE, strlen(si.TOTAL_PRICE));

			SelectObject(hdc_escape, CreateFont(25, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Bitstream Vera Sans Mono")));
			TextOut(hdc_escape, 50, 650, TEXT("Press P to print reciept and Esc to close the program"), 53);
			*/
		}
		break;
	case WM_DESTROY:

		DeleteObject(bitMap);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hdlg, iMsg, wParam, lParam));
}

BOOL CALLBACK MyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HDC hMemDC;
	HGDIOBJ oldBitmap;
	BITMAP  bitmap;
	PAINTSTRUCT ps;

	void AddStringInComboBox(HWND,TCHAR[]);

	HBRUSH g_hbrBackground = NULL;

	TCHAR str[50],str1[50];
	int index=0,index1=0;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		bitMap = LoadBitmap((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(DIALOG_WINDOW));
		ShowWindow(hwnd, SW_MAXIMIZE);

		//For CPU
		for (int i = 0; i < 3; i++)
		{
			SendMessage(GetDlgItem(hwnd, IDCPU), CB_ADDSTRING, (WPARAM)0, (LPARAM)cb.Company[i]);
		}
		SendMessage(GetDlgItem(hwnd, IDCPU), CB_SELECTSTRING, -1, (LPARAM)cb.Company[0]);
		ShowWindow(GetDlgItem(hwnd, IDCPU1), SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDCPU2), SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDCPU3), SW_HIDE);

		//For Ram
		for(int i=0;i<5;i++)
			SendMessage(GetDlgItem(hwnd, IDRAM), CB_ADDSTRING, 0, (LPARAM)ram.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDRAM), CB_SELECTSTRING, -1, (LPARAM)ram.Company[0]);
		ShowWindow(GetDlgItem(hwnd, IDRAM1), SW_HIDE);

		//for motherboard
		for (int i = 0; i<5; i++)
			SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD), CB_ADDSTRING, 0, (LPARAM)motherboard.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD), CB_SELECTSTRING, -1, (LPARAM)motherboard.Company[0]);
		ShowWindow(GetDlgItem(hwnd, IDMOTHERBOARD1), SW_HIDE);

		//for graphic
		for (int i = 0; i<4; i++)
			SendMessage(GetDlgItem(hwnd, IDGRAPHIC), CB_ADDSTRING, 0, (LPARAM)graphic.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDGRAPHIC), CB_SELECTSTRING, -1, (LPARAM)graphic.Company[0]);
		ShowWindow(GetDlgItem(hwnd, IDGRAPHIC1), SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDGRAPHIC2), SW_HIDE);

		//for harddisk
		for (int i = 0; i<3; i++)
			SendMessage(GetDlgItem(hwnd, IDHARD), CB_ADDSTRING, 0, (LPARAM)harddisk.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDHARD), CB_SELECTSTRING, -1, (LPARAM)harddisk.Company[0]);
		ShowWindow(GetDlgItem(hwnd, IDHARD1), SW_HIDE);

		//for CD/Dvd
		for (int i = 0; i<4; i++)
			SendMessage(GetDlgItem(hwnd, IDCD), CB_ADDSTRING, 0, (LPARAM)cddvd.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDCD), CB_SELECTSTRING, -1, (LPARAM)cddvd.Company[0]);
		ShowWindow(GetDlgItem(hwnd, IDCD1), SW_HIDE);

		//for smps
		for (int i = 0; i<3; i++)
			SendMessage(GetDlgItem(hwnd, IDSMPS), CB_ADDSTRING, 0, (LPARAM)smps.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDSMPS), CB_SELECTSTRING, -1, (LPARAM)smps.Company[0]);

		//for Cabinate
		for (int i = 0; i<4; i++)
			SendMessage(GetDlgItem(hwnd, IDCABINATE), CB_ADDSTRING, 0, (LPARAM)cabinate.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDCABINATE), CB_SELECTSTRING, -1, (LPARAM)cabinate.Company[0]);
		ShowWindow(GetDlgItem(hwnd, IDCABINATE1), SW_HIDE);

		//for keyboard
		for (int i = 0; i<4; i++)
			SendMessage(GetDlgItem(hwnd, IDKEYBOARD), CB_ADDSTRING, 0, (LPARAM)keyboard.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDKEYBOARD), CB_SELECTSTRING, -1, (LPARAM)keyboard.Company[0]);
		ShowWindow(GetDlgItem(hwnd, IDKEYBOARD1), SW_HIDE);
		
		//for mouse
		for (int i = 0; i<4; i++)
			SendMessage(GetDlgItem(hwnd, IDMOUSE), CB_ADDSTRING, 0, (LPARAM)mouse.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDMOUSE), CB_SELECTSTRING, -1, (LPARAM)mouse.Company[0]);
		ShowWindow(GetDlgItem(hwnd, IDMOUSE1), SW_HIDE);

		//for monitor
		for (int i = 0; i<4; i++)
			SendMessage(GetDlgItem(hwnd, IDMONITOR), CB_ADDSTRING, 0, (LPARAM)monitor.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDMONITOR), CB_SELECTSTRING, -1, (LPARAM)monitor.Company[0]);
		ShowWindow(GetDlgItem(hwnd, IDMONITOR1), SW_HIDE);
		ShowWindow(GetDlgItem(hwnd, IDMONITOR2), SW_HIDE);

		//for printer Perfect and Checked
		for (int i = 0; i<3; i++)
			SendMessage(GetDlgItem(hwnd, IDPRINTER), CB_ADDSTRING, 0, (LPARAM)printer.Company[i]);
		SendMessage(GetDlgItem(hwnd, IDPRINTER), CB_SELECTSTRING, -1, (LPARAM)printer.Company[0]);

		return(TRUE);

	case WM_CTLCOLORSTATIC:

		hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, RGB(255, 255, 255));
		SetBkMode(hdcStatic, TRANSPARENT);

		return (LRESULT)GetStockObject(NULL_BRUSH);

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hMemDC = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hMemDC, bitMap);
		GetObject(bitMap, sizeof(bitmap), &bitmap);
		BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, oldBitmap);
		SelectObject(hdc, CreateFont(40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Cooper Black")));
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, TRANSPARENT);
		SetBkMode(hdc, TRANSPARENT);
		DeleteDC(hMemDC);
		EndPaint(hwnd, &ps);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case ID_PBCONTINUE:
				DeleteObject(bitMap);
				EndDialog(hwnd, 0);
				break;   
			case IDOK:
				TextOut_Flag = TRUE;
				
				InvalidateRect(ghwnd, NULL, TRUE);
				EndDialog(hwnd, 0);
				break;
			case IDCANCEL:
				DeleteObject(bitMap);
				EndDialog(hwnd, 0);
				break;
			default:
				break;
		}
		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:
			switch (LOWORD(wParam))
			{
			case IDCPU:
				GetDlgItemText(hwnd, IDCPU, str, 50);
				SendMessage(GetDlgItem(hwnd, IDCPU1), CB_RESETCONTENT, 0, 0);
				if (lstrcmp(str, cb.Company[0]) == 0)
				{
					ShowWindow(GetDlgItem(hwnd, IDCPU1), SW_HIDE);
					ShowWindow(GetDlgItem(hwnd, IDCPU2), SW_HIDE);
					ShowWindow(GetDlgItem(hwnd, IDCPU3), SW_HIDE);
				}
				else
				{
					if (lstrcmp(str, cb.Company[1]) == 0)
					{
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDCPU1), CB_ADDSTRING, 0, (LPARAM)cb.SubtypeA[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDCPU1), CB_SELECTSTRING, -1, (LPARAM)cb.SubtypeA[0]);
					}
					else
					{
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDCPU1), CB_ADDSTRING, 0, (LPARAM)cb.SubtypeB[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDCPU1), CB_SELECTSTRING, -1, (LPARAM)cb.SubtypeB[0]);
					}
					ShowWindow(GetDlgItem(hwnd, IDCPU1), SW_SHOW);
					SetFocus(GetDlgItem(hwnd, IDCPU1));
				}
				cb.Price = 0;
				EnableWindow(GetDlgItem(hwnd, ID_ETCPU),TRUE);
				_itoa_s(cb.Price, cb.CPU_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETCPU), cb.CPU_PRICE);
				break;
			case IDCPU1:
				GetDlgItemText(hwnd, IDCPU, str, 50);
				SendMessage(GetDlgItem(hwnd, IDCPU2), CB_RESETCONTENT, 0, 0);
				if (lstrcmp(str, cb.Company[1]) == 0)
				{
					for (int i = 0; i < 3; i++)
					{
						SendMessage(GetDlgItem(hwnd, IDCPU2), CB_ADDSTRING, 0, (LPARAM)cb.GenrationA[i]);
					}
					SendMessage(GetDlgItem(hwnd, IDCPU2), CB_SELECTSTRING, -1, (LPARAM)cb.GenrationA[0]);
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						SendMessage(GetDlgItem(hwnd, IDCPU2), CB_ADDSTRING, 0, (LPARAM)cb.GenrationB[i]);
					}
					SendMessage(GetDlgItem(hwnd, IDCPU2), CB_SELECTSTRING, -1, (LPARAM)cb.GenrationB[0]);
				}
				ShowWindow(GetDlgItem(hwnd, IDCPU2), SW_SHOW);
				SetFocus(GetDlgItem(hwnd, IDCPU2));
				cb.Price = 0;
				_itoa_s(cb.Price, cb.CPU_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETCPU), cb.CPU_PRICE);
				break;
			case IDCPU2:
				GetDlgItemText(hwnd, IDCPU, str, 50);
				SendMessage(GetDlgItem(hwnd, IDCPU3), CB_RESETCONTENT, 0, 0);
				if (lstrcmp(str, cb.Company[1]) == 0)
				{
					for (int i = 0; i < 3; i++)
					{
						SendMessage(GetDlgItem(hwnd, IDCPU3), CB_ADDSTRING, 0, (LPARAM)cb.ModelA[i]);
					}
					SendMessage(GetDlgItem(hwnd, IDCPU3), CB_SELECTSTRING, -1, (LPARAM)cb.ModelA[0]);
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						SendMessage(GetDlgItem(hwnd, IDCPU3), CB_ADDSTRING, 0, (LPARAM)cb.ModelB[i]);
					}
					SendMessage(GetDlgItem(hwnd, IDCPU3), CB_SELECTSTRING, -1, (LPARAM)cb.ModelB[0]);
				}
				ShowWindow(GetDlgItem(hwnd, IDCPU3), SW_SHOW);
				SetFocus(GetDlgItem(hwnd, IDCPU3));
				cb.Price = 0;
				_itoa_s(cb.Price, cb.CPU_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETCPU), cb.CPU_PRICE);
				break;
			case IDCPU3:
				cb.Price = 0;
				_itoa_s(cb.Price, cb.CPU_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETCPU), cb.CPU_PRICE);
				if(lstrcmp(si.CPU[0], cb.Company[1]) == 0)
				{
					index= SendMessage(GetDlgItem(hwnd, IDCPU1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cb.Price = cb.Price + cb.SubtypeAPrice[index];
					index = SendMessage(GetDlgItem(hwnd, IDCPU2), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cb.Price = cb.Price + cb.GenrationAPrice[index];
					index = SendMessage(GetDlgItem(hwnd, IDCPU3), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cb.Price = cb.Price + cb.ModelAPrice[index];
				}
				else
				{
					index = SendMessage(GetDlgItem(hwnd, IDCPU1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cb.Price = cb.Price + cb.SubtypeBPrice[index];
					index = SendMessage(GetDlgItem(hwnd, IDCPU2), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cb.Price = cb.Price + cb.GenrationBPrice[index];
					index = SendMessage(GetDlgItem(hwnd, IDCPU3), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cb.Price = cb.Price + cb.ModelBPrice[index];
				}
				GetDlgItemText(hwnd, IDCPU, si.CPU[0], sizeof(si.CPU[0]));
				GetDlgItemText(hwnd, IDCPU1, si.CPU[1], sizeof(si.CPU[1]));
				GetDlgItemText(hwnd, IDCPU2, si.CPU[2], sizeof(si.CPU[2]));
				GetDlgItemText(hwnd, IDCPU3, si.CPU[3], sizeof(si.CPU[3]));
				_itoa_s(cb.Price, cb.CPU_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETCPU),cb.CPU_PRICE);
				break;
			case IDRAM:
				GetDlgItemText(hwnd, IDRAM, str, 50);
				if (lstrcmp(str, ram.Company[0]) == 0)
				{
					ShowWindow(GetDlgItem(hwnd, IDRAM1), SW_HIDE);
				}
				else
				{
					if (lstrcmp(str, ram.Company[1]) == 0)
					{
						SendMessage(GetDlgItem(hwnd, IDRAM1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDRAM1), CB_ADDSTRING, 0, (LPARAM)ram.SizeA[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDRAM1), CB_SELECTSTRING, -1, (LPARAM)ram.SizeA[0]);
					}
					else if (lstrcmp(str, ram.Company[2]) == 0) 
					{
						SendMessage(GetDlgItem(hwnd, IDRAM1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDRAM1), CB_ADDSTRING, 0, (LPARAM)ram.SizeB[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDRAM1), CB_SELECTSTRING, -1, (LPARAM)ram.SizeB[0]);
					}
					else if (lstrcmp(str, ram.Company[3]) == 0) 
					{
						SendMessage(GetDlgItem(hwnd, IDRAM1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDRAM1), CB_ADDSTRING, 0, (LPARAM)ram.SizeC[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDRAM1), CB_SELECTSTRING, -1, (LPARAM)ram.SizeC[0]);
					}
					else if (lstrcmp(str, ram.Company[4]) == 0) 
					{
						SendMessage(GetDlgItem(hwnd, IDRAM1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDRAM1), CB_ADDSTRING, 0, (LPARAM)ram.SizeD[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDRAM1), CB_SELECTSTRING, -1, (LPARAM)ram.SizeD[0]);
					}
				}
				ShowWindow(GetDlgItem(hwnd, IDRAM1), SW_SHOW);
				SetFocus(GetDlgItem(hwnd, IDRAM1));
				ram.Price = 0;
				EnableWindow(GetDlgItem(hwnd, ID_ETRAM), TRUE);
				_itoa_s(ram.Price, ram.RAM_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETRAM), ram.RAM_PRICE);
				break;
			case IDRAM1:
				ram.Price = 0;
				GetDlgItemText(hwnd, IDRAM, str, 50);
				if (lstrcmp(str, ram.Company[1]) == 0) 
				{
					index = SendMessage(GetDlgItem(hwnd, IDRAM1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					ram.Price = ram.Price + ram.SizeAPrice[index];
				}
				else if (lstrcmp(str, ram.Company[2]) == 0) 
				{
					index = SendMessage(GetDlgItem(hwnd, IDRAM1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					ram.Price = ram.Price + ram.SizeBPrice[index];
				}
				else if (lstrcmp(str, ram.Company[3]) == 0) 
				{
					index = SendMessage(GetDlgItem(hwnd, IDRAM1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					ram.Price = ram.Price + ram.SizeCPrice[index];
				}
				else if (lstrcmp(str, ram.Company[4]) == 0) 
				{
					index = SendMessage(GetDlgItem(hwnd, IDRAM1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					ram.Price = ram.Price + ram.SizeDPrice[index];
				}
				GetDlgItemText(hwnd, IDRAM, si.RAM[0], sizeof(si.RAM[0]));
				GetDlgItemText(hwnd, IDRAM1, si.RAM[1], sizeof(si.RAM[0]));
				_itoa_s(ram.Price, ram.RAM_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETRAM), ram.RAM_PRICE);
				break;
			case IDMOTHERBOARD:
				GetDlgItemText(hwnd, IDMOTHERBOARD, str, 50);
				SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_RESETCONTENT, 0, 0);
				if (lstrcmp(str, motherboard.Company[0]) == 0)
				{
					ShowWindow(GetDlgItem(hwnd, IDMOTHERBOARD1), SW_HIDE);
				}
				else
				{
					if (lstrcmp(str, motherboard.Company[1]) == 0) 
					{
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_ADDSTRING, 0, (LPARAM)motherboard.TypeA[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_SELECTSTRING, -1, (LPARAM)motherboard.TypeA[0]);
					}
					else if (lstrcmp(str, motherboard.Company[2]) == 0) 
					{
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_ADDSTRING, 0, (LPARAM)motherboard.TypeB[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_SELECTSTRING, -1, (LPARAM)motherboard.TypeB[0]);
					}
					else if (lstrcmp(str, motherboard.Company[3]) == 0) 
					{
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_ADDSTRING, 0, (LPARAM)motherboard.TypeC[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_SELECTSTRING, -1, (LPARAM)motherboard.TypeC[0]);
					}
					else if (lstrcmp(str, motherboard.Company[4]) == 0) 
					{
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_ADDSTRING, 0, (LPARAM)motherboard.TypeD[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_SELECTSTRING, -1, (LPARAM)motherboard.TypeD[0]);
					}
					ShowWindow(GetDlgItem(hwnd, IDMOTHERBOARD1), SW_SHOW);
					SetFocus(GetDlgItem(hwnd, IDMOTHERBOARD1));
				}
				motherboard.Price = 0;
				_itoa_s(motherboard.Price, motherboard.MOTHERBOARD_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETMOTHERBOARD), motherboard.MOTHERBOARD_PRICE);
				break;
			case IDMOTHERBOARD1:
				GetDlgItemText(hwnd, IDMOTHERBOARD, str, 50);
				GetDlgItemText(hwnd, IDMOTHERBOARD1, str1, 50);
				motherboard.Price = 0;
				if (lstrcmp(str, motherboard.Company[1]) == 0) 
				{
					index = SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					motherboard.Price = motherboard.Price + motherboard.TypeAPrice[index];
				}
				else if (lstrcmp(str, motherboard.Company[2]) == 0) 
				{
					index = SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					motherboard.Price = motherboard.Price + motherboard.TypeBPrice[index];
				}
				else if (lstrcmp(str, motherboard.Company[3]) == 0) 
				{ 
					index = SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					motherboard.Price = motherboard.Price + motherboard.TypeCPrice[index];
				}
				else if(lstrcmp(str, motherboard.Company[4]) == 0) 
				{
					index = SendMessage(GetDlgItem(hwnd, IDMOTHERBOARD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					motherboard.Price = motherboard.Price + motherboard.TypeDPrice[index];
				}
				GetDlgItemText(hwnd, IDMOTHERBOARD, si.MOTHERBOARD[0], sizeof(si.MOTHERBOARD[0]));
				GetDlgItemText(hwnd, IDMOTHERBOARD1, si.MOTHERBOARD[1], sizeof(si.MOTHERBOARD[1]));
				_itoa_s(motherboard.Price, motherboard.MOTHERBOARD_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETMOTHERBOARD), motherboard.MOTHERBOARD_PRICE);
				break;
			case IDGRAPHIC:
				graphic.Price = 0;
				GetDlgItemText(hwnd, IDGRAPHIC, str, 50);
				if (lstrcmp(str, graphic.Company[0]) == 0)
				{
					ShowWindow(GetDlgItem(hwnd, IDGRAPHIC1), SW_HIDE);
					ShowWindow(GetDlgItem(hwnd, IDGRAPHIC2), SW_HIDE);
				}
				else
				{
					if(lstrcmp(str, graphic.Company[1]) == 0)
					{
						SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 4; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_ADDSTRING, 0, (LPARAM)graphic.TypeA[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_SELECTSTRING, -1, (LPARAM)graphic.TypeA[0]);
					}
					else if (lstrcmp(str, graphic.Company[2]) == 0) 
					{
						SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_ADDSTRING, 0, (LPARAM)graphic.TypeB[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_SELECTSTRING, -1, (LPARAM)graphic.TypeB[0]);
					}
					else if (lstrcmp(str, graphic.Company[3]) == 0) 
					{
						SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_ADDSTRING, 0, (LPARAM)graphic.TypeC[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_SELECTSTRING, -1, (LPARAM)graphic.TypeC[0]);
					}
					ShowWindow(GetDlgItem(hwnd, IDGRAPHIC1), SW_SHOW);
					SetFocus(GetDlgItem(hwnd, IDGRAPHIC1));
				}
				_itoa_s(graphic.Price, graphic.GRAPHIC_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETGRAPHIC), graphic.GRAPHIC_PRICE);
				break;
			case IDGRAPHIC1:
				graphic.Price = 0;
				{
					SendMessage(GetDlgItem(hwnd, IDGRAPHIC2), CB_RESETCONTENT, 0, 0);
					for (int i = 0; i < 3; i++)
					{
						SendMessage(GetDlgItem(hwnd, IDGRAPHIC2), CB_ADDSTRING, 0, (LPARAM)graphic.CardSize[i]);
					}
					SendMessage(GetDlgItem(hwnd, IDGRAPHIC2), CB_SELECTSTRING, -1, (LPARAM)graphic.CardSize[0]);
					ShowWindow(GetDlgItem(hwnd, IDGRAPHIC2), SW_SHOW);
					SetFocus(GetDlgItem(hwnd, IDGRAPHIC2));
				}
				_itoa_s(graphic.Price, graphic.GRAPHIC_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETGRAPHIC), graphic.GRAPHIC_PRICE);
				break;
			case IDGRAPHIC2:
				graphic.Price = 0;
				GetDlgItemText(hwnd, IDGRAPHIC, str, 50);
				if (lstrcmp(str, graphic.Company[1]) == 0) 
				{
					index = SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					graphic.Price = graphic.Price + graphic.TypeAPrice[index];
					index = SendMessage(GetDlgItem(hwnd, IDGRAPHIC2), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					graphic.Price = graphic.Price + graphic.CardSizePrice[index];
				}
				else if (lstrcmp(str, graphic.Company[2]) == 0) 
				{
					index = SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					graphic.Price = graphic.Price + graphic.TypeBPrice[index];
					index = SendMessage(GetDlgItem(hwnd, IDGRAPHIC2), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					graphic.Price = graphic.Price + graphic.CardSizePrice[index];
				}
				else if (lstrcmp(str, graphic.Company[3]) == 0) 
				{
					index = SendMessage(GetDlgItem(hwnd, IDGRAPHIC1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					graphic.Price = graphic.Price + graphic.TypeCPrice[index];
					index = SendMessage(GetDlgItem(hwnd, IDGRAPHIC2), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					graphic.Price = graphic.Price + graphic.CardSizePrice[index];
				}
				GetDlgItemText(hwnd, IDGRAPHIC, si.GRAPHIC[0], sizeof(si.GRAPHIC[0]));
				GetDlgItemText(hwnd, IDGRAPHIC1, si.GRAPHIC[1], sizeof(si.GRAPHIC[1]));
				GetDlgItemText(hwnd, IDGRAPHIC2, si.GRAPHIC[2], sizeof(si.GRAPHIC[2]));
				_itoa_s(graphic.Price, graphic.GRAPHIC_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETGRAPHIC), graphic.GRAPHIC_PRICE);
				break;
			case IDHARD:
				harddisk.Price = 0;
				GetDlgItemText(hwnd, IDHARD, str, 50);
				if (lstrcmp(str, harddisk.Company[0]) == 0)
				{
					ShowWindow(GetDlgItem(hwnd, IDHARD1), SW_HIDE);
				}
				else
				{
					SendMessage(GetDlgItem(hwnd, IDHARD1), CB_RESETCONTENT, 0, 0);
					for (int i = 0; i < 3; i++)
					{
						SendMessage(GetDlgItem(hwnd, IDHARD1), CB_ADDSTRING, 0, (LPARAM)harddisk.HardDiskSize[i]);
					}
					SendMessage(GetDlgItem(hwnd, IDHARD1), CB_SELECTSTRING, -1, (LPARAM)harddisk.HardDiskSize[0]);
					ShowWindow(GetDlgItem(hwnd, IDHARD1), SW_SHOW);
					SetFocus(GetDlgItem(hwnd, IDHARD1));
				}
				_itoa_s(harddisk.Price, harddisk.HARDDISK_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETHARD), harddisk.HARDDISK_PRICE);
				break;
			case IDHARD1 :
				harddisk.Price = 0;
				GetDlgItemText(hwnd, IDHARD, str, 50);
				if (lstrcmp(str, harddisk.Company[1]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDHARD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					harddisk.Price = harddisk.Price + harddisk.WesternDigitalPrice[index];
				}
				else if (lstrcmp(str, harddisk.Company[2]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDHARD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					harddisk.Price = harddisk.Price + harddisk.SeagatePrice[index];
				}
				GetDlgItemText(hwnd, IDHARD, si.HARD[0], sizeof(si.HARD[0]));
				GetDlgItemText(hwnd, IDHARD1, si.HARD[1], sizeof(si.HARD[1]));
				_itoa_s(harddisk.Price, harddisk.HARDDISK_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETHARD), harddisk.HARDDISK_PRICE);
				break;
			case IDCD:
				cddvd.Price = 0;
				GetDlgItemText(hwnd, IDCD, str, 50);
				if (lstrcmp(str, cddvd.Company[0]) == 0)
				{
					ShowWindow(GetDlgItem(hwnd, IDCD1), SW_HIDE);
				}
				else
				{
					if (lstrcmp(str, cddvd.Company[1]) == 0)
					{
						SendMessage(GetDlgItem(hwnd, IDCD1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 4; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDCD1), CB_ADDSTRING, 0, (LPARAM)cddvd.TypeA[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDCD1), CB_SELECTSTRING, -1, (LPARAM)cddvd.TypeA[0]);
					}
					else if(lstrcmp(str, cddvd.Company[2]) == 0)
					{ 
						SendMessage(GetDlgItem(hwnd, IDCD1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 4; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDCD1), CB_ADDSTRING, 0, (LPARAM)cddvd.TypeB[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDCD1), CB_SELECTSTRING, -1, (LPARAM)cddvd.TypeB[0]);
					}
					else if(lstrcmp(str, cddvd.Company[3]) == 0)
					{
						SendMessage(GetDlgItem(hwnd, IDCD1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 4; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDCD1), CB_ADDSTRING, 0, (LPARAM)cddvd.TypeC[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDCD1), CB_SELECTSTRING, -1, (LPARAM)cddvd.TypeC[0]);
					}
					ShowWindow(GetDlgItem(hwnd, IDCD1), SW_SHOW);
					SetFocus(GetDlgItem(hwnd, IDCD1));
				}
				_itoa_s(cddvd.Price, cddvd.CDDVD_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETCD), cddvd.CDDVD_PRICE);
				break;
			case IDCD1:
				cddvd.Price = 0;
				GetDlgItemText(hwnd, IDCD, str, 50);
				if (lstrcmp(str, cddvd.Company[1]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDCD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cddvd.Price = cddvd.Price + cddvd.TypeAPrice[index];
				}
				else if (lstrcmp(str, cddvd.Company[2]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDCD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cddvd.Price = cddvd.Price + cddvd.TypeBPrice[index];
				}
				else if (lstrcmp(str, cddvd.Company[3]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDCD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cddvd.Price = cddvd.Price + cddvd.TypeCPrice[index];
				}
				GetDlgItemText(hwnd, IDCD, si.CDDVD[0], sizeof(si.CDDVD[0]));
				GetDlgItemText(hwnd, IDCD1, si.CDDVD[1], sizeof(si.CDDVD[1]));
				_itoa_s(cddvd.Price, cddvd.CDDVD_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETCD), cddvd.CDDVD_PRICE);
				break;
			case IDSMPS:
				smps.Price = 0;
				GetDlgItemText(hwnd, IDSMPS, str, 50);
				if (lstrcmp(str, smps.Company[0]) == 0)
				{

				}
				else
				{
					index = SendMessage(GetDlgItem(hwnd, IDSMPS), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					smps.Price = smps.Price + smps.CompanyPrice[index - 1];
				}
				GetDlgItemText(hwnd, IDSMPS, si.SMPS[0], sizeof(si.SMPS[0]));
				_itoa_s(smps.Price, smps.SMPS_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETSMPS), smps.SMPS_PRICE);
				break;
			case IDCABINATE:
				cabinate.Price = 0;
				GetDlgItemText(hwnd, IDCABINATE, str, 50);
				if (lstrcmp(str, cabinate.Company[0]) == 0)
				{
					ShowWindow(GetDlgItem(hwnd, IDCABINATE1), SW_HIDE);
				}
				else
				{
					if (lstrcmp(str, cabinate.Company[1]) == 0)
					{
						SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_ADDSTRING, 0, (LPARAM)cabinate.TypeA[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_SELECTSTRING, -1, (LPARAM)cabinate.TypeA[0]);
					}
					else if (lstrcmp(str, cabinate.Company[2]) == 0)
					{
						SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_ADDSTRING, 0, (LPARAM)cabinate.TypeB[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_SELECTSTRING, -1, (LPARAM)cabinate.TypeB[0]);
					}
					else if (lstrcmp(str, cabinate.Company[3]) == 0)
					{
						SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_ADDSTRING, 0, (LPARAM)cabinate.TypeC[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_SELECTSTRING, -1, (LPARAM)cabinate.TypeC[0]);
					}
					ShowWindow(GetDlgItem(hwnd, IDCABINATE1), SW_SHOW);
					SetFocus(GetDlgItem(hwnd, IDCABINATE1));
				}
				_itoa_s(cabinate.Price, cabinate.CABINATE_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETCABINATE), cabinate.CABINATE_PRICE);
				break;
			case IDCABINATE1:
				cabinate.Price = 0;
				GetDlgItemText(hwnd, IDCABINATE, str, 50);
				if (lstrcmp(str, cabinate.Company[1]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cabinate.Price = cabinate.Price + cabinate.TypeAPrice[index];
				}
				else if (lstrcmp(str, cabinate.Company[2]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cabinate.Price = cabinate.Price + cabinate.TypeBPrice[index];
				}
				else if (lstrcmp(str, cabinate.Company[3]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDCABINATE1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					cabinate.Price = cabinate.Price + cabinate.TypeCPrice[index];
				}
				GetDlgItemText(hwnd, IDCABINATE, si.CABINATE[0], sizeof(si.CABINATE[0]));
				GetDlgItemText(hwnd, IDCABINATE1, si.CABINATE[1], sizeof(si.CABINATE[1]));
				_itoa_s(cabinate.Price, cabinate.CABINATE_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETCABINATE), cabinate.CABINATE_PRICE);
				break;
			case IDKEYBOARD:
				keyboard.Price = 0;
				GetDlgItemText(hwnd, IDKEYBOARD, str, 50);
				if (lstrcmp(str, keyboard.Company[0]) == 0)
				{
					ShowWindow(GetDlgItem(hwnd, IDKEYBOARD1), SW_HIDE);
				}
				else
				{
					SendMessage(GetDlgItem(hwnd, IDKEYBOARD1), CB_RESETCONTENT, 0, 0);
					for (int i = 0; i < 2; i++)
					{
						SendMessage(GetDlgItem(hwnd, IDKEYBOARD1), CB_ADDSTRING, 0, (LPARAM)keyboard.KeyboardType[i]);
					}
					SendMessage(GetDlgItem(hwnd, IDKEYBOARD1), CB_SELECTSTRING, -1, (LPARAM)keyboard.KeyboardType[0]);
				}
				ShowWindow(GetDlgItem(hwnd, IDKEYBOARD1), SW_SHOW);
				SetFocus(GetDlgItem(hwnd, IDKEYBOARD1));
				_itoa_s(keyboard.Price, keyboard.KEYBOARD_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETKEYBOARD), keyboard.KEYBOARD_PRICE);
				break;
			case IDKEYBOARD1:
				keyboard.Price = 0;
				GetDlgItemText(hwnd, IDKEYBOARD, str, 50);
				if (lstrcmp(str, keyboard.Company[1]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDKEYBOARD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					keyboard.Price = keyboard.Price + keyboard.TypeAPrice[index];
				}
				else if (lstrcmp(str, keyboard.Company[2]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDKEYBOARD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					keyboard.Price = keyboard.Price + keyboard.TypeBPrice[index];
				}
				else if (lstrcmp(str, keyboard.Company[3]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDKEYBOARD1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					keyboard.Price = keyboard.Price + keyboard.TypeCPrice[index];
				}
				GetDlgItemText(hwnd, IDKEYBOARD, si.KEYBOARD[0], sizeof(si.KEYBOARD[0]));
				GetDlgItemText(hwnd, IDKEYBOARD1, si.KEYBOARD[1], sizeof(si.KEYBOARD[1]));
				_itoa_s(keyboard.Price, keyboard.KEYBOARD_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETKEYBOARD), keyboard.KEYBOARD_PRICE);
				break;
			case IDMOUSE:
				mouse.Price = 0;
				GetDlgItemText(hwnd, IDMOUSE, str, 50);
				if (lstrcmp(str, mouse.Company[0]) == 0)
				{
					ShowWindow(GetDlgItem(hwnd, IDMOUSE1), SW_HIDE);
				}
				else
				{
					SendMessage(GetDlgItem(hwnd, IDMOUSE1), CB_RESETCONTENT, 0, 0);
					for (int i = 0; i < 2; i++)
					{
						SendMessage(GetDlgItem(hwnd, IDMOUSE1), CB_ADDSTRING, 0, (LPARAM)mouse.MouseType[i]);
					}
					SendMessage(GetDlgItem(hwnd, IDMOUSE1), CB_SELECTSTRING, -1, (LPARAM)mouse.MouseType[0]);
				}
				ShowWindow(GetDlgItem(hwnd, IDMOUSE1), SW_SHOW);
				SetFocus(GetDlgItem(hwnd, IDMOUSE1));
				_itoa_s(mouse.Price, mouse.MOUSE_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETMOUSE), mouse.MOUSE_PRICE);
				break;
			case IDMOUSE1:
				mouse.Price = 0;
				GetDlgItemText(hwnd, IDMOUSE, str, 50);
				if (lstrcmp(str, mouse.Company[1]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDMOUSE1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					mouse.Price = mouse.Price + mouse.TypeAPrice[index];
				}
				else if (lstrcmp(str, mouse.Company[2]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDMOUSE1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					mouse.Price = mouse.Price + mouse.TypeBPrice[index];
				}
				else if (lstrcmp(str, mouse.Company[3]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDMOUSE1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					mouse.Price = mouse.Price + mouse.TypeCPrice[index];
				}
				GetDlgItemText(hwnd, IDMOUSE, si.MOUSE[0], sizeof(si.MOUSE[0]));
				GetDlgItemText(hwnd, IDMOUSE1, si.MOUSE[1], sizeof(si.MOUSE[1]));
				_itoa_s(mouse.Price, mouse.MOUSE_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETMOUSE), mouse.MOUSE_PRICE);
				break;
			case IDMONITOR:
				monitor.Price = 0;
				GetDlgItemText(hwnd, IDMONITOR, str, 50);
				if (lstrcmp(str, monitor.Company[0]) == 0)
				{
					ShowWindow(GetDlgItem(hwnd, IDMONITOR1), SW_HIDE);
					ShowWindow(GetDlgItem(hwnd, IDMONITOR2), SW_HIDE);
				}
				else
				{
					if (lstrcmp(str, monitor.Company[1]) == 0)
					{
						SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_ADDSTRING, 0, (LPARAM)monitor.TypeA[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_SELECTSTRING, -1, (LPARAM)monitor.TypeA[0]);
					}
					else if (lstrcmp(str, monitor.Company[2]) == 0)
					{
						SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_ADDSTRING, 0, (LPARAM)monitor.TypeB[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_SELECTSTRING, -1, (LPARAM)monitor.TypeB[0]);
					}
					else if (lstrcmp(str, monitor.Company[3]) == 0)
					{
						SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < 3; i++)
						{
							SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_ADDSTRING, 0, (LPARAM)monitor.TypeC[i]);
						}
						SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_SELECTSTRING, -1, (LPARAM)monitor.TypeC[0]);
					}
				}
				ShowWindow(GetDlgItem(hwnd, IDMONITOR1), SW_SHOW);
				SetFocus(GetDlgItem(hwnd, IDMONITOR1));
				_itoa_s(monitor.Price, monitor.MONITOR_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETMONITOR), monitor.MONITOR_PRICE);
				break;
			case IDMONITOR1:
				monitor.Price = 0;
				GetDlgItemText(hwnd, IDMONITOR, str, 50);
				if (lstrcmp(str, monitor.Company[0]) != 0)
				{
					SendMessage(GetDlgItem(hwnd, IDMONITOR2), CB_RESETCONTENT, 0, 0);
					for (int i = 0; i < 3; i++)
					{
						SendMessage(GetDlgItem(hwnd, IDMONITOR2), CB_ADDSTRING, 0, (LPARAM)monitor.MoitorSize[i]);
					}
					SendMessage(GetDlgItem(hwnd, IDMONITOR2), CB_SELECTSTRING, -1, (LPARAM)monitor.MoitorSize[0]);
				}
				ShowWindow(GetDlgItem(hwnd, IDMONITOR2), SW_SHOW);
				SetFocus(GetDlgItem(hwnd, IDMONITOR2));
				_itoa_s(monitor.Price, monitor.MONITOR_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETMONITOR), monitor.MONITOR_PRICE);
				break;
			case IDMONITOR2:
				monitor.Price = 0;
				GetDlgItemText(hwnd, IDMONITOR, str, 50);
				if (lstrcmp(str, monitor.Company[1]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					monitor.Price = monitor.Price + monitor.TypeAPrice[index];
					index = SendMessage(GetDlgItem(hwnd, IDMONITOR2), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					monitor.Price = monitor.Price + monitor.MoitorSizePrice[index];
				}
				else if (lstrcmp(str, monitor.Company[2]) == 0)
				{
					index = SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					monitor.Price = monitor.Price + monitor.TypeBPrice[index];
					index = SendMessage(GetDlgItem(hwnd, IDMONITOR2), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					monitor.Price = monitor.Price + monitor.MoitorSizePrice[index];
				}
				else if (lstrcmp(str, monitor.Company[3]) == 0)
				{ 
					index = SendMessage(GetDlgItem(hwnd, IDMONITOR1), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					monitor.Price = monitor.Price + monitor.TypeCPrice[index];
					index = SendMessage(GetDlgItem(hwnd, IDMONITOR2), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					monitor.Price = monitor.Price + monitor.MoitorSizePrice[index];
				}
				GetDlgItemText(hwnd, IDMONITOR, si.MONITOR[0], sizeof(si.MONITOR[0]));
				GetDlgItemText(hwnd, IDMONITOR1, si.MONITOR[1], sizeof(si.MONITOR[1]));
				GetDlgItemText(hwnd, IDMONITOR2, si.MONITOR[2], sizeof(si.MONITOR[2]));
				_itoa_s(monitor.Price, monitor.MONITOR_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETMONITOR), monitor.MONITOR_PRICE);
				break;
			case IDPRINTER:
				printer.Price = 0;
				GetDlgItemText(hwnd, IDPRINTER, str, 50);
				if (lstrcmp(str, printer.Company[0]) == 0)
				{
				}
				else
				{
					if (lstrcmp(str, printer.Company[1]) == 0)
					{
						index = SendMessage(GetDlgItem(hwnd, IDPRINTER), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
						printer.Price = printer.Price + printer.CompanyPrice[index - 1];
					}
					else if (lstrcmp(str, printer.Company[2]) == 0)
					{
						index = SendMessage(GetDlgItem(hwnd, IDPRINTER), CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
						printer.Price = printer.Price + printer.CompanyPrice[index - 1];
					}
				}
				GetDlgItemText(hwnd, IDPRINTER, si.PRINTER[0], sizeof(si.PRINTER[0]));
				_itoa_s(printer.Price, printer.PRINTER_PRICE, 10);
				SetWindowText(GetDlgItem(hwnd, ID_ETPRINTER), printer.PRINTER_PRICE);
				break;
			default :
				MessageBox(hwnd, TEXT("YOU ARE IN CBN_SELCHANGE DEFAULT"), TEXT("ERROR"), MB_OK);
				break;
			}
			break;
		}
		return (TRUE);
	}
	return(FALSE);
}

BOOL CALLBACK MyReciptProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[50], str25[100], str10[100];
	wsprintf(str25, TEXT("%25s"),TEXT(" "));
	wsprintf(str10, TEXT("%10s"), TEXT(" "));
	switch (iMsg)
	{
	case WM_INITDIALOG:
		return(TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDOK1:

				GetDlgItemText(hwnd, ID_ETNAME, str, 50);
				CreateMyOwnFile(str);
				if (cb.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
					CreateMyOwnWriteFile(TEXT("\t Processor               "));
					CreateMyOwnWriteFile(si.CPU[0]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.CPU[1]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.CPU[2]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.CPU[3]);
					CreateMyOwnWriteFile(TEXT("     "));
					CreateMyOwnWriteFile(cb.CPU_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (ram.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t RAM                     "));
					CreateMyOwnWriteFile(si.RAM[0]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.RAM[1]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(ram.RAM_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (motherboard.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t MOTHERBOARD             "));
					CreateMyOwnWriteFile(si.MOTHERBOARD[0]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.MOTHERBOARD[1]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(motherboard.MOTHERBOARD_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (graphic.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t GRAPHIC CARD            "));
					CreateMyOwnWriteFile(si.GRAPHIC[0]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.GRAPHIC[1]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.GRAPHIC[2]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(TEXT("               "));
					CreateMyOwnWriteFile(graphic.GRAPHIC_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (harddisk.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t HARD DISK               "));
					CreateMyOwnWriteFile(si.HARD[0]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.HARD[1]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(harddisk.HARDDISK_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (cddvd.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t CD/DVD                  "));
					CreateMyOwnWriteFile(si.CDDVD[0]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.CDDVD[1]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(cddvd.CDDVD_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (smps.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t SMPS                    "));
					CreateMyOwnWriteFile(si.SMPS[0]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(TEXT("                    "));
					CreateMyOwnWriteFile(smps.SMPS_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (cabinate.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t CABINATE                "));
					CreateMyOwnWriteFile(si.CABINATE[0]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.CABINATE[1]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(cabinate.CABINATE_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (keyboard.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t KEYBOARD                "));
					CreateMyOwnWriteFile(si.KEYBOARD[0]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.KEYBOARD[1]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(keyboard.KEYBOARD_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (mouse.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t MOUSE                   "));
					CreateMyOwnWriteFile(si.MOUSE[0]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.MOUSE[1]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(mouse.MOUSE_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (monitor.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t MONITOR                 "));
					CreateMyOwnWriteFile(si.MONITOR[0]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.MONITOR[1]);
					CreateMyOwnWriteFile(str10);
					CreateMyOwnWriteFile(si.MONITOR[2]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(TEXT("               "));
					CreateMyOwnWriteFile(monitor.MONITOR_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				if (printer.Price != 0)
				{
					CreateMyOwnWriteFile(TEXT("\t PRINTER                 "));
					CreateMyOwnWriteFile(si.PRINTER[0]);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(str25);
					CreateMyOwnWriteFile(TEXT("                    "));
					CreateMyOwnWriteFile(printer.PRINTER_PRICE);
					CreateMyOwnWriteFile(TEXT("\r\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"));
				}
				CreateMyOwnWriteFile(TEXT("\t TOTAL                   "));
				CreateMyOwnWriteFile(str25); CreateMyOwnWriteFile(str25); CreateMyOwnWriteFile(str25); CreateMyOwnWriteFile(str25); CreateMyOwnWriteFile(str25);
				CreateMyOwnWriteFile(str10);
				CreateMyOwnWriteFile(si.TOTAL_PRICE);
				RECIEPT_FLAG = TRUE;
				TextOut_Flag = TRUE;
				InvalidateRect(ghwnd, NULL, TRUE);
				CloseHandle(hFile);
				EndDialog(hwnd, 0);
				break;
			case IDCANCEL:
				EndDialog(hwnd, 0);
				break;
		}
		return (TRUE);
	}
	return(FALSE);
}

void CreateMyOwnFile(TCHAR filename[])
{
	hFile = CreateFile(filename,FILE_APPEND_DATA,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
}

void CreateMyOwnWriteFile(TCHAR data[])
{
	bErrorFlag = WriteFile(hFile,data,(DWORD)strlen(data),&dwBytesWritten,NULL);
	if (FALSE == bErrorFlag)
	{
		DisplayError(TEXT("WriteFile"));
		printf("Terminal failure: Unable to write to file.\n");
	}
}
void DisplayError(LPTSTR lpszFunction)
{
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,NULL,dw,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&lpMsgBuf,0,NULL);
	lpDisplayBuf =(LPVOID)LocalAlloc(LMEM_ZEROINIT,(lstrlen((LPCTSTR)lpMsgBuf)+ lstrlen((LPCTSTR)lpszFunction)+ 40)* sizeof(TCHAR));
	if (FAILED(StringCchPrintf((LPTSTR)lpDisplayBuf,LocalSize(lpDisplayBuf) / sizeof(TCHAR),TEXT("%s failed with error code %d as follows:\n%s"),lpszFunction,dw,lpMsgBuf)))
	{
		printf("FATAL ERROR: Unable to output error code.\n");
	}
	_tprintf(TEXT("ERROR: %s\n"), (LPCTSTR)lpDisplayBuf);
	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}
