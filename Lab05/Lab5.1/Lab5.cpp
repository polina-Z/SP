// Lab5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab5.h"

#define MAX_LOADSTRING 100

#define RED 10001
#define WHITE 10002
#define GREEN 10003
#define BLUE 10004

#define THIN 10005
#define MEDIUM 10006
#define THICK 10007

#define FILL 10009
#define RHOMBUS 10010
#define SQUARE 10011
#define CIRCLE 10012
#define STAR 10013
#define DRAW 10014

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
UINT myColorMsg;
UINT myFigureMsg;
UINT myStateMsg;
UINT myThicknessMsg;

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.
    myColorMsg = RegisterWindowMessageW(L"MyColorMsg");
    myFigureMsg = RegisterWindowMessageW(L"MyFigureMsg");
    myStateMsg = RegisterWindowMessageW(L"MyStateMsg");
    myThicknessMsg = RegisterWindowMessageW(L"MyThicknessMsg");
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB5);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 400, 500, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        CreateWindow(L"Button", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
            20, 25, 50, 50, hWnd, (HMENU)RED, hInst, NULL);
        CreateWindow(L"Button", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
            20, 75, 50, 50, hWnd, (HMENU)WHITE, hInst, NULL);
        CreateWindow(L"Button", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
            70, 25, 50, 50, hWnd, (HMENU)GREEN, hInst, NULL);
        CreateWindow(L"Button", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
            70, 75, 50, 50, hWnd, (HMENU)BLUE, hInst, NULL);

        CreateWindow(L"Button", L"Thickness", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            20, 125, 100, 95, hWnd, 0, hInst, NULL);
        HWND button1 = CreateWindow(L"Button", L"Thin", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON
            | WS_GROUP, 30, 145, 80, 20, hWnd, (HMENU)THIN, hInst, NULL);
        // установка флажка по умолчанию в первый кружок
        SendMessage(button1, BM_SETCHECK, BST_CHECKED, 1);
        CreateWindow(L"Button", L"Medium", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            30, 170, 80, 20, hWnd, (HMENU)MEDIUM, hInst, NULL);
        CreateWindow(L"Button", L"Thick", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            30, 195, 80, 20, hWnd, (HMENU)THICK, hInst, NULL);

        CreateWindow(L"Button", L"Tools", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            20, 225, 100, 135, hWnd, 0, hInst, NULL);
        HWND button2 = CreateWindow(L"Button", L"Fill", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON
            | WS_GROUP, 30, 245, 85, 20, hWnd, (HMENU)FILL, hInst, NULL);
        // установка флажка по умолчанию в первый кружок
        SendMessage(button2, BM_SETCHECK, BST_CHECKED, 1);        
        CreateWindow(L"Button", L"Rhombus", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            30, 267, 85, 20, hWnd, (HMENU)RHOMBUS, hInst, NULL);
        CreateWindow(L"Button", L"Square", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            30, 289, 85, 20, hWnd, (HMENU)SQUARE, hInst, NULL);
        CreateWindow(L"Button", L"Circle", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            30, 311, 85, 20, hWnd, (HMENU)CIRCLE, hInst, NULL);
        CreateWindow(L"Button", L"Star", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            30, 333, 85, 20, hWnd, (HMENU)STAR, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Draw", WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
            200, 150, 150, 100, hWnd, (HMENU)DRAW, hInst, nullptr);
    }
    break;
    case WM_DRAWITEM:
    {
        //отрисовка цветных кнопок
        LPDRAWITEMSTRUCT di = (LPDRAWITEMSTRUCT)lParam;
        RECT rc = di->rcItem;
        HDC hdc = di->hDC;

        int isMyButton = 0;
        HPEN itemPen, whitePen, oldPen;
        HBRUSH itemBrush, whiteBrush, oldBrush;
        COLORREF color;

        switch (di->CtlID)
        {
        case RED:
            isMyButton = 1;
            color = RGB(255, 0, 0);
            break;
        case WHITE:
            isMyButton = 1;
            color = RGB(255, 255, 255);
            break;
        case GREEN:
            isMyButton = 1;
            color = RGB(0, 255, 0);
            break;
        case BLUE:
            isMyButton = 1;
            color = RGB(0, 0, 255);
            break;
        }

        if (isMyButton)
        {
            itemPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            itemBrush = CreateSolidBrush(color);
            whitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
            whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

            oldPen = (HPEN)SelectObject(hdc, whitePen);
            oldBrush = (HBRUSH)SelectObject(hdc, whiteBrush);

            Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

            SelectObject(hdc, itemPen);
            SelectObject(hdc, itemBrush);

            Rectangle(hdc, rc.left + 5, rc.top + 5, rc.right - 5, rc.bottom - 5);

            SelectObject(hdc, oldPen);
            SelectObject(hdc, oldBrush);
            DeleteObject(itemPen);
            DeleteObject(itemBrush);
            DeleteObject(whitePen);
            DeleteObject(whiteBrush);

            return TRUE;
        }
        else
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        HWND hReceiver = FindWindowW(nullptr, L"Lab5.2");
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case RED:
        case GREEN:
        case BLUE:
        case WHITE:
            if (hReceiver)
            {
                PostMessageW(hReceiver, myColorMsg, (WPARAM)hWnd, wmId - RED);
            }
            break;
        case FILL:
        case RHOMBUS:
        case SQUARE:
        case CIRCLE:
        case STAR:
            if (hReceiver)
            {
                PostMessageW(hReceiver, myFigureMsg, (WPARAM)hWnd, wmId - FILL);
            }
            break;
        case THIN:
        case MEDIUM:
        case THICK:
            if (hReceiver)
            {
                PostMessageW(hReceiver, myThicknessMsg, (WPARAM)hWnd, wmId - THIN);
            }
            break;
        case DRAW:
            if (hReceiver)
            {
                LRESULT state = !SendMessageW((HWND)lParam, BM_GETCHECK, 0, 0);
                SendMessageW((HWND)lParam, BM_SETCHECK, state, 0);
                PostMessageW(hReceiver, myStateMsg, (WPARAM)hWnd, state);
            }
            break;
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
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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

// Обработчик сообщений для окна "О программе".
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
