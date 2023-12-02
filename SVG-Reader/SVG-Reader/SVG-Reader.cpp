// SVG-Reader.cpp : Defines the entry point for the application.
//
#include "Object.h"
#include "resource.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
float scale = 1;
float Rotate = 0;
float scroll_x = 0;
float scroll_y = 0;
float max_width = 0, max_height = 0;
string path = "C:\\Users\\LENOVO\\Downloads\\svg-11.svg";
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
    bool is_dragging = false;
    POINT last_mouse_position;
    vector<shape*> shapes;
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
            case IDM_ZOOM_IN:
                scale *= 1.1;
                InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
                goto DrawAgain;
            case IDM_ZOOM_OUT:
                scale *= 0.9;
                InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
                goto DrawAgain;
            case IDM_DEFAULT:
                scale = 1;
                Rotate = 0;
                scroll_x = 0;
                scroll_y = 0;
                InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
                goto DrawAgain;
            case IDM_ROTATE_LEFT:
                Rotate -= 30;
                InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
                goto DrawAgain;
            case IDM_ROTATE_RIGHT:
                Rotate += 30;
                InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
                goto DrawAgain;
            case IDM_UP:
                scroll_y -= 20;
                InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
                goto DrawAgain;
            case IDM_DOWN:
                scroll_y += 20;
                InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
                goto DrawAgain;
            case IDM_RIGHT:
                scroll_x += 20;
                InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
                goto DrawAgain;
            case IDM_LEFT:
                scroll_x -= 20;
                InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
                goto DrawAgain;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
            case VK_UP:
                // Xử lý mũi tên lên
                scroll_y -= 20;
                InvalidateRect(hWnd, NULL, TRUE);
                goto DrawAgain;
                break;
            case VK_DOWN:
                // Xử lý mũi tên xuống
                scroll_y += 20;
                InvalidateRect(hWnd, NULL, TRUE);
                goto DrawAgain;
                break;
            case VK_LEFT:
                // Xử lý mũi tên trái
                scroll_x -= 20;
                InvalidateRect(hWnd, NULL, TRUE);
                goto DrawAgain;
                break;
            case VK_RIGHT:
                // Xử lý mũi tên phải
                scroll_x += 20;
                InvalidateRect(hWnd, NULL, TRUE);
                goto DrawAgain;
                break;
            case 'i': case 'I':
                scale *= 1.1;
                InvalidateRect(hWnd, NULL, TRUE);
                goto DrawAgain;
                break;
            case 'o': case 'O':
                scale *= 0.9;
                InvalidateRect(hWnd, NULL, TRUE);
                goto DrawAgain;
                break;
            case 'r': case 'R':
                Rotate += 30;
                InvalidateRect(hWnd, NULL, TRUE);
                goto DrawAgain;
                break;
            case 'l': case 'L':
                Rotate -= 30;
                InvalidateRect(hWnd, NULL, TRUE);
                goto DrawAgain;
                break;
                break;
            case 'd': case 'D':
                scale = 1;
                Rotate = 0;
                scroll_x = 0;
                scroll_y = 0;
                InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
                goto DrawAgain;
        }
    }
    case WM_MOUSEWHEEL:
    {
        short delta = GET_WHEEL_DELTA_WPARAM(wParam);
        if (delta > 0)
            scale *= 1.1;
        else
            scale *= 0.9;
        InvalidateRect(hWnd, NULL, TRUE); // Force a repaint
        goto DrawAgain;
    }
    case WM_PAINT:
        {
            DrawAgain:
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            Graphics graphics(hdc);
            vector<shape*> shapes = read_file(path, max_width, max_height);
            transform_image(graphics, Rotate, max_width + scroll_x, max_height + scroll_y , scroll_x, scroll_y, scale);
            for (int i = 0; i < shapes.size(); i++) {
                shapes[i]->draw(graphics);
            }
            EndPaint(hWnd, &ps);
            
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        for (int i = 0; i < shapes.size(); i++) {
            delete shapes[i];
        }
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
