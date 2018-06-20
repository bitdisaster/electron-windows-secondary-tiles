// SecondaryTilesWin32App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SecondaryTilesWin32App.h"
#include "SecondaryTilesLib.h"
#include <shellapi.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);



	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SECONDARYTILESWIN32APP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SECONDARYTILESWIN32APP));

	MSG msg;

	LPWSTR *szArglist;
	int nArgs;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (nArgs > 1)
	{
		MessageBox(NULL, lpCmdLine, L"Tile Args", NULL);
	}

	LocalFree(szArglist);


	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SECONDARYTILESWIN32APP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SECONDARYTILESWIN32APP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void Test(HWND hWnd)
{
	auto options = new SecondaryTiles::TileOptions();
	options->ShowNameOnSquare150x150Logo = true;
	options->ShowNameOnSquare310x310Logo = true;
	options->ShowNameOnWide310x150Logo = true;
	options->BackgroundColor = "#FF00FF";
	options->ForegroundText = SecondaryTiles::ForegroundText::Light;
	options->Square150x150Logo = "ms-appx:///images/Square150x150Logo.png";
	options->Wide310x150Logo = "ms-appx:///images/Wide310x150Logo.png";
	options->Square310x310Logo = "ms-appx:///images/Square310x310Logo.png";
	options->Square70x70Logo = "undefined"; // "ms-appx:///images/Square70x70Logo.png";

	SecondaryTiles::RequestCreate(hWnd, "Tile1", L"Hello Options X", "tileId=Tile1", SecondaryTiles::TileSize::Default, *options);
	//SecondaryTiles::RequestCreateAsync(hWnd, L"Tile1", L"Hello Options Y", L"tileId=Tile1", L"ms-appx:///images/Square150x150Logo.png", true);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		CreateWindowEx(
			NULL,
			L"button",
			L"Pin Secondary Tile",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
			50,
			50,
			300,
			50,
			hWnd,
			(HMENU)200,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);

		CreateWindowEx(
			NULL,
			L"button",
			L"Check Secondary Tile",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
			50,
			100,
			300,
			50,
			hWnd,
			(HMENU)201,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);

		CreateWindowEx(
			NULL,
			L"button",
			L"Delete Secondary Tile",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
			50,
			150,
			300,
			50,
			hWnd,
			(HMENU)202,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);

		CreateWindowEx(
			NULL,
			L"button",
			L"Notify Secondary Tile",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
			50,
			200,
			300,
			50,
			hWnd,
			(HMENU)203,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);

		CreateWindowEx(
			NULL,
			L"button",
			L"Badge Secondary Tile",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
			50,
			250,
			300,
			50,
			hWnd,
			(HMENU)204,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);

		CreateWindowEx(
			NULL,
			L"button",
			L"Clear Notification",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
			50,
			300,
			300,
			50,
			hWnd,
			(HMENU)205,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);

		CreateWindowEx(
			NULL,
			L"button",
			L"Clear Badge",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
			50,
			350,
			300,
			50,
			hWnd,
			(HMENU)206,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);

	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case 200:
			if (wmEvent == BN_CLICKED)
			{
				Test(hWnd);
			}
			break;
		case 201:
			if (wmEvent == BN_CLICKED)
			{
				if (SecondaryTiles::Exists("Tile1"))
				{
					MessageBox(NULL, L"TRUE", L"Tile EXISTS", NULL);
				}
				else
				{
					MessageBox(NULL, L"FALSE", L"Tile EXISTS", NULL);
				}
			}
			break;
		case 202:
			if (wmEvent == BN_CLICKED)
			{
				SecondaryTiles::RequestDelete("Tile1");
			}
			break;
		case 203:
			if (wmEvent == BN_CLICKED)
			{
				string bla = "<tile> \
								<visual> \
								<binding template=\"TileWide\" branding=\"logo\"> \
								<group> \
								<subgroup> \
								<text hint-style=\"caption\">Hello tile from Win32</text> \
								</subgroup> \
								</group> \
								</binding> \
								</visual> \
								</tile>";

				SecondaryTiles::Notify("Tile1", bla);

				string bla2 = "<tile> \
								<visual> \
								<binding template=\"TileWide\" branding=\"logo\"> \
								<group> \
								<subgroup> \
								<text hint-style=\"caption\">Second hello from Win32</text> \
								</subgroup> \
								</group> \
								</binding> \
								</visual> \
								</tile>";

				SecondaryTiles::Notify("Tile1", bla2);
			}
			break;
		case 204:
			if (wmEvent == BN_CLICKED)
			{
				string badge = "<badge value = \"99\"/>";
				SecondaryTiles::BadgeNotify("Tile1", badge);
			}
			break;
		case 205:
			if (wmEvent == BN_CLICKED)
			{
				SecondaryTiles::ClearNotification("Tile1");
			}
			break;
		case 206:
			if (wmEvent == BN_CLICKED)
			{
				SecondaryTiles::ClearBadge("Tile1");
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
