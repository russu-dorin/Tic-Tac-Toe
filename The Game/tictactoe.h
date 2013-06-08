#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <iostream>


void CenterWindow(HWND hwnd)
{
    RECT rc;

    GetWindowRect(hwnd, &rc) ;

    SetWindowPos(hwnd, 0,
        (GetSystemMetrics(SM_CXSCREEN) - rc.right)/2,
        (GetSystemMetrics(SM_CYSCREEN) - rc.bottom)/2,
         0, 0, SWP_NOZORDER|SWP_NOSIZE);
}

HWND CreateControl(const char szType[], const char szCaption[],
                    const HWND hParent, const HINSTANCE hInstance,
                    DWORD dwStyle, DWORD dwExStyle, const RECT Wnd, const int id)
                    {
                        dwStyle |= WS_CHILD | WS_VISIBLE;

                       return CreateWindowEx(dwExStyle,
                                             szType,
                                             szCaption,
                                             dwStyle,
                                             Wnd.left,
                                             Wnd.top,
                                             Wnd.right,
                                             Wnd.bottom,
                                             hParent,
                                             reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
                                             hInstance,
                                             0);
                    }


