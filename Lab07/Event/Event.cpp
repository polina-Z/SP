// Event.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Event.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HANDLE ghEvent;
HANDLE threads[4];
int choice = 0;

HWND mainWnd;
RECT lprc{ 0, 0, 500, 500 };

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI        ThreadProc(LPVOID pParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.
    ghEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
    if (ghEvent == NULL)
    {
        return 0;
    }
    threads[0] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(L"AAAA"), CREATE_SUSPENDED, NULL);
    threads[1] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(L"BBBB"), CREATE_SUSPENDED, NULL);
    threads[2] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(L"CCCC"), CREATE_SUSPENDED, NULL);
    threads[3] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(L"DDDD"), CREATE_SUSPENDED, NULL);

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EVENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EVENT));

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

    TerminateThread(threads[3], 0);
    TerminateThread(threads[2], 0);
    TerminateThread(threads[1], 0);
    TerminateThread(threads[0], 0);
    CloseHandle(threads[3]);
    CloseHandle(threads[2]);
    CloseHandle(threads[1]);
    CloseHandle(threads[0]);
    CloseHandle(ghEvent);
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EVENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EVENT);
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
      CW_USEDEFAULT, 0, 500, 500, nullptr, nullptr, hInstance, nullptr);
   mainWnd = hWnd;
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
        for (int i = 0; i < 4; i++)
        {
            ResumeThread(threads[i]);
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
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            wchar_t* string;
            HDC hdc = BeginPaint(hWnd, &ps);
            GetClientRect(mainWnd, &lprc);
            switch (choice)
            {
            case 0:
            {
                DrawTextW(hdc, L"AAAA", 4, &lprc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            }
            break;
            case 1:
            {
                DrawTextW(hdc, L"BBBB", 4, &lprc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            }
            break;
            case 2:
            {
                DrawTextW(hdc, L"CCCC", 4, &lprc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            }
            break;
            case 3:
            {
                DrawTextW(hdc, L"DDDD", 4, &lprc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            }
            break;
            }

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        for (int i = 0; i < 4; i++)
        {
            SuspendThread(threads[i]);
        }
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

DWORD WINAPI ThreadProc(LPVOID pParam)
{
    wchar_t* string = reinterpret_cast<wchar_t*>(pParam);
    while (true)
    {
        auto result = WaitForSingleObject(ghEvent, INFINITE);
        switch (result)
        {
        case WAIT_OBJECT_0:
        case WAIT_ABANDONED:
        {
            if (string == L"AAAA")
            {
                choice = 0;
            }
            if (string == L"BBBB")
            {
                choice = 1;
            }
            if (string == L"CCCC")
            {
                choice = 2;
            }
            if (string == L"DDDD")
            {
                choice = 3;
            }

            InvalidateRect(mainWnd, &lprc, TRUE);
            Sleep(1000);
            SetEvent(ghEvent);
        }
        break;
        default:
            break;
        }
    }
    return 0;
}
