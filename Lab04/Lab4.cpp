// Lab4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab4.h"
#include <Windowsx.h>
#include <math.h>

#define MAX_LOADSTRING 100
#define IDT_TIMER    10001

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HBITMAP hFrames[7];
int frameIndex = 0;
float posX = 100.0f;
float posY = 100.0f;
constexpr float speed = 30.0f;
POINT position{ 100, 100 };

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
    hFrames[0] = (HBITMAP)LoadImage(NULL, L"pic1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hFrames[1] = (HBITMAP)LoadImage(NULL, L"pic2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hFrames[2] = (HBITMAP)LoadImage(NULL, L"pic3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hFrames[3] = (HBITMAP)LoadImage(NULL, L"pic4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hFrames[4] = (HBITMAP)LoadImage(NULL, L"pic5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hFrames[5] = (HBITMAP)LoadImage(NULL, L"pic6.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hFrames[6] = (HBITMAP)LoadImage(NULL, L"pic7.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4));

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
    DeleteObject(hFrames[6]);
    DeleteObject(hFrames[5]);
    DeleteObject(hFrames[4]);
    DeleteObject(hFrames[3]);
    DeleteObject(hFrames[2]);
    DeleteObject(hFrames[1]);
    DeleteObject(hFrames[0]);

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB4);
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
        SetTimer(hWnd, IDT_TIMER, 60, nullptr);
    }
    case WM_LBUTTONDOWN:
    {
        position.x = GET_X_LPARAM(lParam);
        position.y = GET_Y_LPARAM(lParam);
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
        HDC hdc = BeginPaint(hWnd, &ps);

        HDC hCompDc = CreateCompatibleDC(hdc);
        auto hOldBm = SelectObject(hCompDc, hFrames[frameIndex]);
        BITMAP bm;
        GetObject(hFrames[frameIndex], sizeof(bm), &bm);
        if ((float)(position.x) - posX >= 0)
            BitBlt(hdc, (int)posX - bm.bmWidth / 2, (int)posY - bm.bmHeight, bm.bmWidth, bm.bmHeight, hCompDc, 0, 0, SRCCOPY);
        else
            StretchBlt(hdc, (int)posX + (bm.bmWidth + 1) / 2, (int)posY - bm.bmHeight, -bm.bmWidth, bm.bmHeight,
                hCompDc, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        SelectObject(hCompDc, hOldBm);
        DeleteDC(hCompDc);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_TIMER:
    {
        switch (wParam)
        {
        case IDT_TIMER:
        {
            RECT oldRect{ (int)posX - 50, (int)posY - 150, (int)posX + 50, (int)posY };
            InvalidateRect(hWnd, &oldRect, TRUE);

            float vecX = (float)(position.x) - posX;
            float vecY = (float)(position.y) - posY;
            float vecM2 = vecX * vecX + vecY * vecY;
            if (vecM2 > speed * speed)
            {
                float vecM = sqrtf(vecM2);
                posX += vecX / vecM * speed;
                posY += vecY / vecM * speed;
                frameIndex++;
                if (frameIndex >= 4)
                    frameIndex = 0;
            }
            else
            {
                posX = (float)(position.x);
                posY = (float)(position.y);
                if (vecM2 > 0)
                {
                    frameIndex++;
                }
            }

            RECT newRect{ (int)posX - 50, (int)posY - 150, (int)posX + 50, (int)posY };
            InvalidateRect(hWnd, &newRect, FALSE);
        }
        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
    {
        KillTimer(hWnd, IDT_TIMER);
        PostQuitMessage(0);
    }
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
