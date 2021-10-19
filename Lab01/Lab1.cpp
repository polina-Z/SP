// Lab1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab1.h"

#define MAX_LOADSTRING 100
#define IDM_START 10001
#define IDM_STOP  10002
#define IDT_TIMER 10003

// Глобальные переменные
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HCURSOR hCursor;

//Text
LPCTSTR text = L"Лабораторная работа №1";
INT cchText = lstrlen(text);
RECT lprc{ 0, 0, 0, 0 };
int op1 = 1, op2 = 0, op3 = 0, op4 = 0;
RECT trect{ 0, 0, 0, 0 };


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID WINAPI MoveText(HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.
    hCursor = static_cast<HCURSOR>(LoadImage(nullptr, L"Cursor.cur", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE));
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

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


    DestroyCursor(hCursor);
    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor        = hCursor;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
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
            HMENU hMenu = GetMenu(hWnd);
            HMENU hSubMenu = CreateMenu();
            AppendMenuW(hSubMenu, MF_STRING, IDM_START, L"Start");
            AppendMenuW(hSubMenu, MF_STRING, IDM_STOP, L"Stop");
            InsertMenuW(hMenu, -1, MF_BYPOSITION | MF_STRING | MF_POPUP, reinterpret_cast<UINT_PTR>(hSubMenu), L"Дополнительно");
            break;
    }
    case WM_SETCURSOR:
    {
        UNREFERENCED_PARAMETER(wParam);
        int htId = LOWORD(lParam);
        switch (htId)
        {
        case HTTOP:
        case HTBOTTOM:
        case HTLEFT:
        case HTRIGHT:
            return DefWindowProc(hWnd, message, wParam, lParam);
        default:
            SetCursor(hCursor);
            return TRUE;
        }
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_START:
            SetTimer(hWnd, IDT_TIMER, 30, nullptr);
            break;
        case IDM_STOP:
            KillTimer(hWnd, IDT_TIMER);
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
        DrawTextW(hdc, text, cchText, &lprc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_TIMER:
    {
        switch (wParam)
        {
        case IDT_TIMER:
            UNREFERENCED_PARAMETER(lParam);
            InvalidateRect(hWnd, &lprc, TRUE);
            HDC hdc = GetWindowDC(hWnd);
            DrawTextW(hdc, text, cchText, &trect, DT_CALCRECT);
            ReleaseDC(hWnd, hdc);

            MoveText(hWnd);

            lprc.right = lprc.left + trect.right;
            lprc.bottom = lprc.top + trect.bottom;
            InvalidateRect(hWnd, &lprc, TRUE);
        }
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

VOID WINAPI MoveText(HWND hWnd)
{
    RECT winRect = { 0 };
    GetWindowRect(hWnd, &winRect);
    winRect.right = winRect.right - 100;
    winRect.bottom = winRect.bottom - 100;
    lprc.right = lprc.left + trect.right;
    lprc.bottom = lprc.top + trect.bottom;
    if (lprc.bottom <= winRect.bottom && op1 == 1 && lprc.right <= winRect.right)
    {
        lprc.left += 2;
        lprc.top += 2;
        lprc.right = lprc.left + trect.right;
        lprc.bottom = lprc.top + trect.bottom;
        if (lprc.bottom >= winRect.bottom)
        {
            op1 = 0;
            op2 = 1;
        }
        else
            if (lprc.right >= winRect.right)
            {
                op1 = 0;
                op3 = 1;
            }
    }
    else if (op2 == 1 && lprc.top >= winRect.top && lprc.right <= winRect.right)
    {
        lprc.left += 2;
        lprc.top -= 2;
        lprc.right = lprc.left + trect.right;
        lprc.bottom = lprc.top + trect.bottom;
        if (lprc.top <= winRect.top)
        {

            op2 = 0;
            op1 = 1;
        }
        else
            if (lprc.right >= winRect.right)
            {
                op2 = 0;
                op4 = 1;
            }
    }
    else if (op3 == 1 && lprc.bottom <= winRect.bottom && lprc.left >= winRect.left)
    {
        lprc.left -= 2;
        lprc.top += 2;
        lprc.right = lprc.left + trect.right;
        lprc.bottom = lprc.top + trect.bottom;
        if (lprc.bottom >= winRect.bottom)
        {

            op3 = 0;
            op4 = 1;
        }
        else
            if (lprc.left <= winRect.left)
            {
                op3 = 0;
                op1 = 1;
            }
    }
    else if (op4 == 1 && lprc.top >= winRect.top && lprc.left >= winRect.left)
    {
        lprc.left -= 2;
        lprc.top -= 2;
        lprc.right = lprc.left + trect.right;
        lprc.bottom = lprc.top + trect.bottom;
        if (lprc.top <= winRect.top)
        {

            op4 = 0;
            op3 = 1;
        }
        else
            if (lprc.left <= winRect.left)
            {
                op4 = 0;
                op2 = 1;
            }
    }
}