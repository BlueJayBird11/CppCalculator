// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")


#define ID_BUTTON1 1 // Button identifier
#define ID_BUTTON2 2
#define ID_BUTTON3 3
#define ID_BUTTON4 4
#define ID_BUTTON5 5
#define ID_BUTTON6 6
#define ID_BUTTON7 7
#define ID_BUTTON8 8
#define ID_BUTTON9 9
#define ID_BUTTON10 10
#define ID_BUTTON_DEC 11
#define ID_BUTTON_C 12
#define ID_BUTTON_CE 13
#define ID_BUTTON_PLUS 14
#define ID_BUTTON_MIN 15
#define ID_BUTTON_MULT 16
#define ID_BUTTON_DIV 17
#define ID_BUTTON_EQ 18
#define ID_BUTTON_PER 19

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
    static HWND hwndButton1 = NULL;
    static HWND hwndButton2 = NULL;
    static HWND hwndButton3 = NULL;
    static HWND hwndButton4 = NULL;
    static HWND hwndButton5 = NULL;
    static HWND hwndButton6 = NULL;
    static HWND hwndButton7 = NULL;
    static HWND hwndButton8 = NULL;
    static HWND hwndButton9 = NULL;
    static HWND hwndButton10 = NULL;
    static HWND hwndButtonDec = NULL;
    static HWND hwndButtonC = NULL;
    static HWND hwndButtonCE = NULL;
    static HWND hwndButtonPlus = NULL;
    static HWND hwndButtonMinus = NULL;
    static HWND hwndButtonMult = NULL;
    static HWND hwndButtonDiv = NULL;
    static HWND hwndButtonEq = NULL;
    static HWND hwndButtonPer = NULL;
    static HWND hwndTab = NULL;
    // TCITEM tie;
    TCITEM tie = { 0 };

    int start_x = 15;
    int start_y = 350;
    int button_size = 50;
    int spacing = 70;

    // Create the SPWSTRs for the tabs

    char text1[] = "Calculator";
    wchar_t wtext1[20];
    mbstowcs(wtext1, text1, strlen(text1) + 1);//Plus null
    LPWSTR ptr1 = wtext1;

    char text2[] = "Trace Logic";
    wchar_t wtext2[20];
    mbstowcs(wtext2, text2, strlen(text2) + 1);//Plus null
    LPWSTR ptr2 = wtext2;

    // NMHDR* pNmhdr = (NMHDR*)lParam;
    NMHDR* pNmhdr = reinterpret_cast<NMHDR*>(lParam);
    TCHAR test[] = _T("Hellooooooooooooooooooooo");

    int iPage;


    switch (message)
    {
    case WM_CREATE:
        std::cout << "CREATE EVERYTHING" << std::endl;
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


        // Create a push button 1
        hwndButton1 = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed 
            TEXT("1"),      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            start_x,         // x position 
            start_y,         // y position 
            button_size,        // Button width
            button_size,        // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON1,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // Create the second button 2
        hwndButton2 = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("2"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x+spacing,        // x position, to the right of the first button
            start_y,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON2,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // 3
        hwndButton3 = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("3"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 2*spacing,        // x position, to the right of the first button
            start_y,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON3,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // 4
        hwndButton4 = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("4"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x,        // x position, to the right of the first button
            start_y - spacing,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON4,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // 5
        hwndButton5 = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("5"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x+spacing,        // x position, to the right of the first button
            start_y-spacing,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON5,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // 6
        hwndButton6 = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("6"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 2 * spacing,        // x position, to the right of the first button
            start_y - spacing,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON6,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // 7
        hwndButton7 = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("7"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x,        // x position, to the right of the first button
            start_y - 2 * spacing,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON7,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // 8
        hwndButton8 = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("8"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + spacing,        // x position, to the right of the first button
            start_y - 2 * spacing,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON8,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // 9
        hwndButton9 = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("9"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 2 * spacing,        // x position, to the right of the first button
            start_y - 2 * spacing,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON9,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // 10 (0)
        hwndButton10 = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed 
            TEXT("0"),      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            start_x,         // x position 
            start_y + spacing,         // y position 
            button_size + spacing,        // Button width
            button_size,        // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON10,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // DEC
        hwndButtonDec = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed 
            TEXT("."),      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            start_x + 2 * spacing,         // x position 
            start_y + spacing,         // y position 
            button_size,        // Button width
            button_size,        // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON_DEC,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // C
        hwndButtonC = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("C"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 3 * spacing + spacing / 4,        // x position, to the right of the first button
            start_y - 2 * spacing,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON_C,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // CE
        hwndButtonCE = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("CE"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 4 * spacing + spacing / 4,        // x position, to the right of the first button
            start_y - 2 * spacing,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON_CE,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // PLUS
        hwndButtonPlus = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("+"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 3 * spacing + spacing / 4,        // x position, to the right of the first button
            start_y - spacing,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON_PLUS,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // MINUS
        hwndButtonMinus = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("-"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 4 * spacing + spacing / 4,       
            start_y - spacing,     
            button_size,       
            button_size,      
            hWnd,
            (HMENU)ID_BUTTON_MIN, 
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // MULT
        hwndButtonMult = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("*"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 3 * spacing + spacing / 4,        // x position, to the right of the first button
            start_y,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON_MULT,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // DIVIDE
        hwndButtonDiv = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("/"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 4 * spacing + spacing / 4,
            start_y,
            button_size,
            button_size,
            hWnd,
            (HMENU)ID_BUTTON_DIV,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // EQ
        hwndButtonEq = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("="),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 3 * spacing + spacing / 4,        // x position, to the right of the first button
            start_y + spacing,         // y position, same as the first button
            button_size,        // Button width
            button_size,         // Button height
            hWnd,     // Parent window
            (HMENU)ID_BUTTON_EQ,       // Button identifier
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

        // PER
        hwndButtonPer = CreateWindow(
            TEXT("BUTTON"),  // Predefined class; Unicode assumed
            TEXT("%"),   // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            start_x + 4 * spacing + spacing / 4,
            start_y + spacing,
            button_size,
            button_size,
            hWnd,
            (HMENU)ID_BUTTON_PER,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.


        // ShowWindow(hwndButton1, SW_HIDE);
        // ShowWindow(hwndButton2, SW_SHOW);

        break;

    case WM_NOTIFY:
        TCHAR debugStr[100];
        wsprintf(debugStr, TEXT("WM_NOTIFY: %s\n"), pNmhdr->idFrom == 1);
        OutputDebugString(debugStr);
        //if (pNmhdr->idFrom == 1 && pNmhdr->code == TCN_SELCHANGE) // Check if this is a notification from your tab control.
        //{
            iPage = TabCtrl_GetCurSel(pNmhdr->hwndFrom);

            // std::cout << "Here: " << iPage << std::endl;
            // char const* tempstr = std::to_string(iPage).c_str();
            //TCHAR debugStr[100];
            //wsprintf(debugStr, TEXT("Here: %d\n"), iPage);
            //OutputDebugString(debugStr);


            if (iPage == 0)
            {
                // First tab selected, adjust visibility accordingly
                ShowWindow(hwndButton1, SW_SHOW);
                ShowWindow(hwndButton2, SW_SHOW);
                ShowWindow(hwndButton3, SW_SHOW);
                ShowWindow(hwndButton4, SW_SHOW);
                ShowWindow(hwndButton5, SW_SHOW);
                ShowWindow(hwndButton6, SW_SHOW);
                ShowWindow(hwndButton7, SW_SHOW);
                ShowWindow(hwndButton8, SW_SHOW);
                ShowWindow(hwndButton9, SW_SHOW);
                ShowWindow(hwndButton10, SW_SHOW);

                ShowWindow(hwndButtonDec, SW_SHOW);
                ShowWindow(hwndButtonC, SW_SHOW);
                ShowWindow(hwndButtonCE, SW_SHOW);
                ShowWindow(hwndButtonMult, SW_SHOW);
                ShowWindow(hwndButtonDiv, SW_SHOW);
                ShowWindow(hwndButtonPlus, SW_SHOW);
                ShowWindow(hwndButtonMinus, SW_SHOW);
                ShowWindow(hwndButtonEq, SW_SHOW);
                ShowWindow(hwndButtonPer, SW_SHOW);
            }
            else if (iPage == 1)
            {
                // Second tab selected, adjust visibility accordingly
                ShowWindow(hwndButton1, SW_HIDE);
                ShowWindow(hwndButton2, SW_HIDE);
                ShowWindow(hwndButton3, SW_HIDE);
                ShowWindow(hwndButton4, SW_HIDE);
                ShowWindow(hwndButton5, SW_HIDE);
                ShowWindow(hwndButton6, SW_HIDE);
                ShowWindow(hwndButton7, SW_HIDE);
                ShowWindow(hwndButton8, SW_HIDE);
                ShowWindow(hwndButton9, SW_HIDE);
                ShowWindow(hwndButton10, SW_HIDE);

                ShowWindow(hwndButtonDec, SW_HIDE);
                ShowWindow(hwndButtonC, SW_HIDE);
                ShowWindow(hwndButtonCE, SW_HIDE);
                ShowWindow(hwndButtonMult, SW_HIDE);
                ShowWindow(hwndButtonDiv, SW_HIDE);
                ShowWindow(hwndButtonPlus, SW_HIDE);
                ShowWindow(hwndButtonMinus, SW_HIDE);
                ShowWindow(hwndButtonEq, SW_HIDE);
                ShowWindow(hwndButtonPer, SW_HIDE);

            }

        // }
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
        // TCHAR debugStr[100];
        // wsprintf(debugStr, TEXT("Here: %s\n"), LOWORD(wParam));
        // OutputDebugString(debugStr);
        if (LOWORD(wParam) == ID_BUTTON1) {
            MessageBox(hWnd, TEXT("1 Button clicked!"), TEXT("Message"), MB_OK);
        }
        else if (LOWORD(wParam) == ID_BUTTON2) {
            MessageBox(hwndTab, TEXT("2 Button clicked!"), TEXT("Message"), MB_OK);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
