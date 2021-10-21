// Lab3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab3.h"

#define MAX_LOADSTRING 100
#define IDB_DRAW     10001
#define IDB_CLEAR    10002

// Глобальные переменные:
bool isDrawn = false;
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
constexpr int imageX = 200;
constexpr int imageY = 400;

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
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
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
      CW_USEDEFAULT, 0, 350, 300, nullptr, nullptr, hInstance, nullptr);

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
        CreateWindowW(L"BUTTON", L"Draw", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 50, 180, 100, 50, hWnd, (HMENU)IDB_DRAW, hInst, nullptr);
        CreateWindowW(L"BUTTON", L"Clear", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, 200, 180, 100, 50, hWnd, (HMENU)IDB_CLEAR, hInst, nullptr);
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDB_DRAW:
            {
                if (!isDrawn)
                {
                    isDrawn = true;
                    RECT rect{ 40, 40, 280, 130 };
                    InvalidateRect(hWnd, &rect, FALSE);
                }
            }
            break;
            case IDB_CLEAR:
                if (isDrawn)
                {
                    isDrawn = false;
                    RECT rect{ 40, 40, 280, 130 };
                    InvalidateRect(hWnd, &rect, TRUE);
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
    case WM_DRAWITEM:
    {
        DRAWITEMSTRUCT* pItem = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);

        switch (wParam)
        {
        case IDB_DRAW:
        {
            COLORREF color;
            if (pItem->itemState & ODS_SELECTED)
                color = RGB(254, 138, 0);
            else
                color = RGB(0, 255, 0);

            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            auto hOldPen = SelectObject(pItem->hDC, hPen);

            HBRUSH hBrush = CreateSolidBrush(color);
            auto hOldBrush = SelectObject(pItem->hDC, hBrush);


            RoundRect(pItem->hDC, pItem->rcItem.left, pItem->rcItem.top, pItem->rcItem.right, pItem->rcItem.bottom, 32, 32);
            auto oldColor = GetTextColor(pItem->hDC);
            SetTextColor(pItem->hDC, RGB(0, 0, 0));
            SetBkColor(pItem->hDC, color);
            DrawTextW(pItem->hDC, L"Draw", -1, &(pItem->rcItem), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            SetTextColor(pItem->hDC, oldColor);
            SelectObject(pItem->hDC, hOldBrush);
            SelectObject(pItem->hDC, hOldPen);
            DeleteObject(hBrush);
            DeleteObject(hOldPen);
            return TRUE;
        }
        break;
        case IDB_CLEAR:
        {
            COLORREF color;
            if (pItem->itemState & ODS_SELECTED)
                color = RGB(254, 138, 0);
            else
                color = RGB(255, 0, 0);

            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            auto hOldPen = SelectObject(pItem->hDC, hPen);

            HBRUSH hBrush = CreateSolidBrush(color);
            auto hOldBrush = SelectObject(pItem->hDC, hBrush);


            RoundRect(pItem->hDC, pItem->rcItem.left, pItem->rcItem.top, pItem->rcItem.right, pItem->rcItem.bottom, 32, 32);

            auto oldColor = GetTextColor(pItem->hDC);
            SetTextColor(pItem->hDC, RGB(0, 0, 0));
            SetBkColor(pItem->hDC, color);
            DrawTextW(pItem->hDC, L"Clear", -1, &(pItem->rcItem), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            SetTextColor(pItem->hDC, oldColor);
            SelectObject(pItem->hDC, hOldBrush);
            SelectObject(pItem->hDC, hOldPen);
            DeleteObject(hBrush);
            DeleteObject(hOldPen);
            return TRUE;
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);         
            if (isDrawn)
            {
                int xp = 40;
                int yp = 40;

                HPEN hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 204, 0));
                HBRUSH hGreenBrush = CreateSolidBrush(RGB(0, 204, 0));
                SelectObject(hdc, hGreenPen);
                SelectObject(hdc, hGreenBrush);
                Rectangle(hdc, 40, 110, 280, 120);
                DeleteObject(hGreenBrush);
                DeleteObject(hGreenPen);

                HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 191, 255));
                HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 191, 255));
                SelectObject(hdc, hBluePen);
                SelectObject(hdc, hBlueBrush);
                POINT points3[] = {
                    // part4
                    {xp + 50, yp + 50},
                    {xp + 90, yp + 20},
                    {xp + 70, yp + 10},
                    {xp + 60, yp + 10},
                    {xp + 70, yp + 20},
                    {xp + 90, yp + 20},
                    // part5
                    {xp + 90, yp + 50},
                    {xp + 70, yp + 80},
                    {xp + 60, yp + 90},
                    {xp + 80, yp + 90},
                    {xp + 140, yp + 50}
                };
                Polygon(hdc, points3, 6);
                Polygon(hdc, points3 + 6, 5);
                DeleteObject(hBlueBrush);
                DeleteObject(hBluePen);

                HPEN hSilverPen = CreatePen(PS_SOLID, 1, RGB(192, 192, 192));
                HBRUSH hSilverBrush = CreateSolidBrush(RGB(192, 192, 192));
                SelectObject(hdc, hSilverPen);
                SelectObject(hdc, hSilverBrush);
                POINT points1[] = {
                    // part1
                    {40, 40},
                    {60, 40},
                    {80, 60},
                    {90, 60},
                    {90, 90},
                    {84, 90},
                    {60, 80},
                    {50, 50},
                    // part2
                    {xp + 170, yp + 20},
                    {xp + 180, yp + 20},
                    {xp + 200, yp + 30},
                    {xp + 180, yp + 30},
                    {xp + 180, yp + 40},
                    {xp + 210, yp + 40},
                    {xp + 230, yp + 50},
                    {xp + 170, yp + 50}
                };
                Polygon(hdc, points1, 8);
                Polygon(hdc, points1 + 8, 8);
                Rectangle(hdc, xp + 50, yp + 20, xp + 170, yp + 50);

                HPEN hGreyPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
                HBRUSH hGreyBrush = CreateSolidBrush(RGB(128, 128, 128));
                DeleteObject(hSilverBrush);
                DeleteObject(hSilverPen);
                SelectObject(hdc, hGreyPen);
                SelectObject(hdc, hGreyBrush);
                POINT points2[] = {
                    // part3
                    {xp + 44, yp + 50},
                    {xp + 70, yp + 60},
                    {xp + 210, yp + 60},
                    {xp + 230, yp + 50}
                };
                Polygon(hdc, points2, 4);

                DeleteObject(hGreyBrush);
                DeleteObject(hGreyPen);

                HPEN hCreamPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 204));
                HBRUSH hCreamBrush = CreateSolidBrush(RGB(255, 255, 204));
                SelectObject(hdc, hCreamPen);
                SelectObject(hdc, hCreamBrush);
                POINT points4[] = {
                    // part6
                    {xp + 200, yp + 30},
                    {xp + 180, yp + 30},
                    {xp + 180, yp + 40},
                    {xp + 210, yp + 40},

                };
                Polygon(hdc, points4, 4);
                Rectangle(hdc, xp + 90, yp + 30, xp + 100, yp + 40);
                Rectangle(hdc, xp + 110, yp + 30, xp + 120, yp + 40);
                Rectangle(hdc, xp + 130, yp + 30, xp + 140, yp + 40);
                Rectangle(hdc, xp + 150, yp + 30, xp + 160, yp + 40);
                DeleteObject(hCreamBrush);
                DeleteObject(hCreamPen);

                HPEN hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
                HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
                SelectObject(hdc, hBlackPen);
                SelectObject(hdc, hBlackBrush);
                Ellipse(hdc, 185 - 5, 105 + 5, 185 + 5, 105 - 5);
                DeleteObject(hBlackBrush);
                DeleteObject(hBlackPen);
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
