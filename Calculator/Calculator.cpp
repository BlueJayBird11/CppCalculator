// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")


#define ID_BUTTON1 1 // Button identifier
#define ID_BUTTON2 2 // Second Button identifier

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Calculator");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_TAB_CLASSES;
    InitCommonControlsEx(&icex);

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, Jay!");
    HWND hwndButton1, hwndButton2;
    HWND hwndTab;
    // TCITEM tie;
    TCITEM tie = { 0 };

    // Create the SPWSTRs for the tabs
    
    char text1[] = "Calculator";
    wchar_t wtext1[20];
    mbstowcs(wtext1, text1, strlen(text1) + 1);//Plus null
    LPWSTR ptr1 = wtext1;

    char text2[] = "Trace Logic";
    wchar_t wtext2[20];
    mbstowcs(wtext2, text2, strlen(text2) + 1);//Plus null
    LPWSTR ptr2 = wtext2;
 
    NMHDR* pNmhdr = (NMHDR*)lParam;

    switch (message)
    {
        case WM_CREATE:
            hwndTab = CreateWindow(WC_TABCONTROL, _T(""),
                WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                0, 0, 500, 600, hWnd, NULL, hInst, NULL);

            // Zero out the TCITEM structure.
            ZeroMemory(&tie, sizeof(TCITEM));

            tie.mask = TCIF_TEXT;
            tie.pszText = ptr1;
            TabCtrl_InsertItem(hwndTab, 0, &tie);

            tie.pszText = ptr2;
            TabCtrl_InsertItem(hwndTab, 1, &tie);


            // Create a push button
            hwndButton1 = CreateWindow(
                TEXT("BUTTON"),  // Predefined class; Unicode assumed 
                TEXT("1"),      // Button text 
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                10,         // x position 
                50,         // y position 
                100,        // Button width
                30,        // Button height
                hwndTab,     // Parent window
                (HMENU)ID_BUTTON1,       // No menu.
                (HINSTANCE)GetWindowLongPtr(hwndTab, GWLP_HINSTANCE),
                NULL);      // Pointer not needed.

            // Create the second button
            hwndButton2 = CreateWindow(
                TEXT("BUTTON"),  // Predefined class; Unicode assumed
                TEXT("2"),   // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                120,        // x position, to the right of the first button
                50,         // y position, same as the first button
                100,        // Button width
                30,         // Button height
                hwndTab,     // Parent window
                (HMENU)ID_BUTTON2,       // Button identifier
                (HINSTANCE)GetWindowLongPtr(hwndTab, GWLP_HINSTANCE),
                NULL);      // Pointer not needed.

            break;
        
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            TextOut(hdc, 10, 10, greeting, _tcslen(greeting));
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_BUTTON1) {
                MessageBox(hWnd, TEXT("1 Button clicked!"), TEXT("Message"), MB_OK);
            }
            else if (LOWORD(wParam) == ID_BUTTON2) {
                MessageBox(hWnd, TEXT("2 Button clicked!"), TEXT("Message"), MB_OK);
            }
            break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
