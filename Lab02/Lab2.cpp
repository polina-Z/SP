// Lab2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab2.h"

#define MAX_LOADSTRING 100

#define IDC_LISTBOXFIRST 10001
#define IDC_LISTBOXSECOND 10002
#define IDC_EDIT 10003
#define IDB_ADD 10004
#define IDB_CLEAR 10005
#define IDB_TORIGHT 10006
#define IDB_DELETE 10007

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hListboxFirst;
HWND hListboxSecond;
HWND hEdit;

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

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

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

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2);
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
      CW_USEDEFAULT, 0, 850, 470, nullptr, nullptr, hInstance, nullptr);

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
        hEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"Text",
            WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
            20, 20, 620, 50, hWnd, (HMENU)IDC_EDIT, hInst, nullptr);
        hListboxFirst = CreateWindowExW(WS_EX_CLIENTEDGE, L"LISTBOX", L"First Listbox",
            WS_BORDER | WS_CHILD | WS_HSCROLL | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
            20, 90, 300, 300, hWnd, (HMENU)IDC_LISTBOXFIRST, hInst, nullptr);
        hListboxSecond = CreateWindowExW(WS_EX_CLIENTEDGE, L"LISTBOX", L"Second Listbox",
            WS_BORDER | WS_CHILD | WS_HSCROLL | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
            510, 90, 300, 300, hWnd, (HMENU)IDC_LISTBOXSECOND, hInst, nullptr);
        CreateWindowW(L"BUTTON", L"Add", WS_CHILD | WS_VISIBLE, 660, 20, 150, 50, hWnd, (HMENU)IDB_ADD, hInst, nullptr);
        CreateWindowW(L"BUTTON", L"Delete", WS_CHILD | WS_VISIBLE, 340, 145, 150, 50, hWnd, (HMENU)IDB_DELETE, hInst, nullptr);
        CreateWindowW(L"BUTTON", L"ToRight", WS_CHILD | WS_VISIBLE, 340, 215, 150, 50, hWnd, (HMENU)IDB_TORIGHT, hInst, nullptr);
        CreateWindowW(L"BUTTON", L"Clear", WS_CHILD | WS_VISIBLE, 340, 285, 150, 50, hWnd, (HMENU)IDB_CLEAR, hInst, nullptr);
        SendMessageW(hEdit, EM_LIMITTEXT, MAX_LOADSTRING - 1, 0);
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDB_ADD:
            {
                int length = GetWindowTextLengthW(hEdit);
                if (length > 0)
                {
                    TCHAR buffer[MAX_LOADSTRING];
                    GetWindowTextW(hEdit, buffer, sizeof(buffer) / sizeof(buffer[0]));
                    int index = SendMessageW(hListboxFirst, LB_FINDSTRINGEXACT, -1, (LPARAM)buffer);
                    if (index == LB_ERR)
                    {
                        SendMessageW(hListboxFirst, LB_ADDSTRING, 0, (LPARAM)buffer);
                        SetWindowTextW(hEdit, L"");
                    }
                }
                else
                {
                    MessageBox(NULL, L"Сначала необходимо\nввести тест", L"Ошибка", MB_OK);
                }
            }
            break;
            case IDB_DELETE:
            {
                int index = SendMessageW(hListboxFirst, LB_GETCURSEL, 0, 0);
                if (index != LB_ERR)
                {
                    SendMessageW(hListboxFirst, LB_DELETESTRING, index, 0);
                }
                else
                {
                    MessageBox(NULL, L"Сначала необходимо\nвыбрать пункт текста\nдля удаления", L"Ошибка", MB_OK);
                }

            }
            break;
            case IDB_TORIGHT:
            {
                int index1 = SendMessageW(hListboxFirst, LB_GETCURSEL, 0, 0);
                if (index1 != LB_ERR)
                {
                    TCHAR buffer[MAX_LOADSTRING];
                    SendMessageW(hListboxFirst, LB_GETTEXT, index1, (LPARAM)buffer);
                    int index2 = SendMessageW(hListboxSecond, LB_FINDSTRINGEXACT, -1, (LPARAM)buffer);
                    if (index2 == LB_ERR)
                    {
                        SendMessageW(hListboxSecond, LB_ADDSTRING, 0, (LPARAM)buffer);
                    }
                }
                else
                {
                    MessageBox(NULL, L"Сначала необходимо\nвыбрать пункт текста\nдля переноса", L"Ошибка", MB_OK);
                }
            }
            break;
            case IDB_CLEAR:
            {
                SendMessageW(hListboxFirst, LB_RESETCONTENT, 0, 0);
                SendMessageW(hListboxSecond, LB_RESETCONTENT, 0, 0);
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
