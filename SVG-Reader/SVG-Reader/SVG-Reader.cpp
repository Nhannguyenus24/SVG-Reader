// SVG-Reader.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SVG-Reader.h"
#include <windows.h>
#include <objidl.h>
#include "Drawing.h"
#include "Rotate.h"
#pragma comment (lib,"Gdiplus.lib")
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
    LoadStringW(hInstance, IDC_SVGREADER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SVGREADER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SVGREADER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SVGREADER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR token;
    GdiplusStartup(&token, &gdiplusStartupInput, nullptr);
    vector<int> a, b, c, d, e, f, g, h;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
            Drawing dr("sample.svg", hdc);
            //DrawRectangle(hdc, 20, 20, 800, 400, 0.2, 200, 100, 150, 1, 55, 55, 55, 2);
            //DrawRectangle(hdc, 0, 0, 200, 50, 0, 0, 0, 0, 1, 255, 0, 0, 2);
            //// TODO: Add any drawing code that uses hdc here...
            /*DrawRectangle(hdc, 25, 25, 800, 400, 0.01, 0, 0, 0, 1, 200, 200, 200, 2);
            DrawRectangle(hdc, 20, 20, 800, 400, 0.2, 200, 100, 150, 1, 55, 55, 55, 2);
            DrawRectangle(hdc, 0, 0, 200, 50, 0, 0, 0, 0, 1, 255, 0, 0, 2);
            DrawCircle(hdc, 200, 300, 100, 0.5, 255, 255, 0, 0.7, 0, 255, 255, 10);
            DrawEllipse(hdc, 500, 100, 100, 50, 0.5, 0, 255, 0, 0.7, 255, 255, 0, 3);
            a = { 5, 15, 15, 25, 25, 35, 35, 45, 45, 55, 55, 65, 65, 75, 75, 85, 85, 95, 95, 105, 105, 115 };
            b = { 37, 37, 32, 32, 37, 37, 25, 25, 37, 37, 17, 17, 37, 37, 10, 10, 37, 37, 2, 2, 37, 37 };
            DrawPolyline(hdc, a, b, 0.5, 0, 255, 255, 0.7, 255, 0, 0, 2);
            DrawLine(hdc, 10, 30, 30, 10, 0.7, 0, 0, 255, 5);
            DrawLine(hdc, 30, 30, 50, 10, 0.8, 0, 0, 255, 10);
            DrawLine(hdc, 50, 30, 70, 10, 0.9, 0, 0, 255, 15);
            DrawLine(hdc, 70, 30, 90, 10, 0.9, 0, 0, 255, 20);
            DrawLine(hdc, 90, 30, 110, 10, 1, 0, 0, 255, 25);
            c = { 850, 958, 958, 850, 742, 742 };
            d = { 75, 137, 262, 325, 262, 137 };
            DrawPolygon(hdc, c, d, 0.5, 153, 204, 255,0.7, 255, 0, 102, 10);
            e = { 350, 379, 469, 397, 423, 350, 277, 303, 231, 321 };
            f = { 75, 161, 161, 215, 301, 250, 301, 215, 161, 161 };
            DrawPolygon(hdc, e, f, 0.6, 255, 255, 0, 0.7, 255, 0, 0, 10);
            g = { 0, 40, 40, 80, 80, 120, 120 };
            h = { 40, 40, 80, 80, 120, 120, 140 };
            DrawPolyline(hdc, g, h, 0.5, 0, 0, 0, 1, 0, 0, 0, 1);*/
            //DrawText(hdc, 400, 400 - 30, "Nguyen Van A", 1, 255, 0, 255, 30);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    GdiplusShutdown(token);
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
