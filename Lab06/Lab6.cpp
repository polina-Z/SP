// Lab6.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab6.h"
#include "math.h"

#define MAX_LOADSTRING 100
#define IDB_START     10001
#define IDB_STOP      10002

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HBITMAP hClock;
int sek = 0;

struct ThreadInfo
{
    float posX;
    float posY;
    int speed;
    int thickness;
    int length;
    COLORREF color;
    HANDLE handle;
};
ThreadInfo threads[] = {
    { 450, 442, 2, 10, 125, RGB(0, 0, 0), nullptr},
    { 450, 392, 1, 15, 90, RGB(0, 0, 255), nullptr },
};
HWND mainWnd;
bool isRunning = false;

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
    hClock = (HBITMAP)LoadImage(NULL, L"Clock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    threads[0].handle = CreateThread(NULL, 0, ThreadProc, (LPVOID)(threads + 0), CREATE_SUSPENDED, NULL);
    threads[1].handle = CreateThread(NULL, 0, ThreadProc, (LPVOID)(threads + 1), CREATE_SUSPENDED, NULL);
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB6));

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

    TerminateThread(threads[1].handle, 0);
    TerminateThread(threads[0].handle, 0);
    CloseHandle(threads[1].handle);
    CloseHandle(threads[0].handle);

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB6));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB6);
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
        CW_USEDEFAULT, 0, 760, 640, nullptr, nullptr, hInstance, nullptr);
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
        CreateWindowW(L"BUTTON", L"Start", WS_CHILD | WS_VISIBLE, 10, 215, 100, 50, hWnd, (HMENU)IDB_START, hInst, nullptr);
        CreateWindowW(L"BUTTON", L"Stop", WS_CHILD | WS_VISIBLE, 10, 315, 100, 50, hWnd, (HMENU)IDB_STOP, hInst, nullptr);
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDB_START:
            if (!isRunning)
            {
                isRunning = true;
                for (int i = 0; i < 2; i++)
                {
                    ResumeThread(threads[i].handle);
                }
            }
            break;
        case IDB_STOP:
            if (isRunning)
            {
                isRunning = false;
                for (int i = 0; i < 2; i++)
                {
                    SuspendThread(threads[i].handle);
                }
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
        HDC hCompDc = CreateCompatibleDC(hdc);
        auto hOldBm = SelectObject(hCompDc, hClock);
        BITMAP bm;
        GetObject(hClock, sizeof(bm), &bm);
        BitBlt(hdc, 150, 0, bm.bmWidth, bm.bmHeight, hCompDc, 0, 0, SRCCOPY);
        SelectObject(hCompDc, hOldBm);
        DeleteDC(hCompDc);

        for (int i = 0; i < 2; i++)
        {
            HPEN hPen = CreatePen(PS_SOLID, threads[i].thickness, threads[i].color);
            SelectObject(hdc, hPen);
            int x = threads[i].posX;
            int y = threads[i].posY;
            MoveToEx(hdc, 450, 292, NULL);
            LineTo(hdc, threads[i].posX, threads[i].posY);
            DeleteObject(hPen);
        }

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

DWORD WINAPI ThreadProc(LPVOID pParam)
{
    ThreadInfo& thread = *reinterpret_cast<ThreadInfo*>(pParam);
    while (true)
    {
        RECT oldRect{ 325, 185, 575, 447};
        InvalidateRect(mainWnd, &oldRect, TRUE);
        thread.posX = 450 + thread.length * sin(3.14 *  thread.speed * sek / 30);
        thread.posY = 320 - thread.length * cos(3.14 * thread.speed * sek / 30);
        sek++;
        if (sek >= 360)
        {
            sek = 0;
        }
        Sleep(30);
    }
    return 0;
}