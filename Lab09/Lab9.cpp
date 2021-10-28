// Lab9.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab9.h"
#include <strsafe.h>

#define MAX_LOADSTRING 100
#define IDC_LISTBOX 10001
#define IDC_EDIT 10002
#define IDB_SEARCH 10003

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hListbox;
HWND hEdit;
HKEY keys[] = { 
    HKEY_CLASSES_ROOT,
    HKEY_CURRENT_USER,
    HKEY_LOCAL_MACHINE,
    HKEY_USERS,
    HKEY_CURRENT_CONFIG
};

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void Search(TCHAR* s);
void SearchRec(HKEY hKeyRoot, LPTSTR lpSubKey, TCHAR* s);

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
    LoadStringW(hInstance, IDC_LAB9, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB9));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB9));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB9);
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
      CW_USEDEFAULT, 0, 660, 640, nullptr, nullptr, hInstance, nullptr);

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
        hListbox = CreateWindowExW(WS_EX_CLIENTEDGE, L"LISTBOX", L"First Listbox",
            WS_BORDER | WS_CHILD | WS_HSCROLL | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
            20, 20, 600, 400, hWnd, (HMENU)IDC_LISTBOX, hInst, nullptr);
        hEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"Microsoft",
            WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
            20, 430, 460, 50, hWnd, (HMENU)IDC_EDIT, hInst, nullptr);
        CreateWindowW(L"BUTTON", L"Search", WS_CHILD | WS_VISIBLE, 500, 430, 120, 50, hWnd, (HMENU)IDB_SEARCH, hInst, nullptr);
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDB_SEARCH:
            {
                int length = GetWindowTextLengthW(hEdit);
                if (length > 0)
                {
                    //TCHAR buffer[MAX_LOADSTRING];
                    //GetWindowTextW(hEdit, buffer, sizeof(buffer) / sizeof(buffer[0]));
                    //SendMessage(hListbox, LB_RESETCONTENT, 0, 0);
                    //int len;
                    //len = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
                    TCHAR buffer[256];
                    SendMessage(hEdit, WM_GETTEXT, len + 1, (LPARAM)buffer);
                    Search(buffer);
                    //SendMessageW(hListbox, LB_ADDSTRING, 0, (LPARAM)buffer);
                    /*int index = SendMessageW(hListb, LB_FINDSTRINGEXACT, -1, (LPARAM)buffer);
                    if (index == LB_ERR)
                    {
                        SendMessageW(hListboxFirst, LB_ADDSTRING, 0, (LPARAM)buffer);
                        SetWindowTextW(hEdit, L"");
                    }*/
                }
                else
                {
                    MessageBox(NULL, L"Сначала необходимо\nввести текст", L"Ошибка", MB_OK);
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
int x = 1000;
void SearchRec(HKEY hKeyRoot, LPTSTR lpSubKey, TCHAR* s)
{
    if (--x <= 0) return;
    LPTSTR lpEnd;
    LONG lResult;
    DWORD dwSize;
    TCHAR szName[MAX_PATH];
    HKEY hKey;
    FILETIME ftWrite;

    lResult = RegOpenKeyEx(hKeyRoot, lpSubKey, 0, KEY_READ, &hKey);

    if (lResult != ERROR_SUCCESS)
    {
        return;
    }

    if (_tcsstr(lpSubKey, s) != NULL)
        SendMessage(hListbox, LB_ADDSTRING, 0, (LPARAM)lpSubKey);

    lpEnd = lpSubKey + lstrlen(lpSubKey);

    if (*(lpEnd - 1) != TEXT('\\'))
    {
        *lpEnd = TEXT('\\');
        lpEnd++;
        *lpEnd = TEXT('\0');
    }

    dwSize = MAX_PATH;
    lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
        NULL, NULL, &ftWrite);

    if (lResult == ERROR_SUCCESS)
    {
        int index = 0;
        do
        {
            index++;

            StringCchCopy(lpEnd, MAX_PATH * 2, szName);

            SearchRec(hKeyRoot, lpSubKey, s);
            if (x <= 0) return;

            dwSize = MAX_PATH;

            lResult = RegEnumKeyEx(hKey, index, szName, &dwSize, NULL,
                NULL, NULL, &ftWrite);

        } while (lResult == ERROR_SUCCESS);
    }

    lpEnd--;
    *lpEnd = TEXT('\0');

    RegCloseKey(hKey);
}

void Search(TCHAR* s)
{
    SendMessage(hListbox, LB_RESETCONTENT, 0, 0);

    LPTSTR lpSubKey = TEXT("Software");
    TCHAR szSearchKey[MAX_PATH * 2];
    StringCchCopy(szSearchKey, MAX_PATH * 2, lpSubKey);

    x = 1000;
    SearchRec(HKEY_LOCAL_MACHINE, szSearchKey, s);
}