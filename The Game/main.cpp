#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#define ID_BUTTON 100


LPSTR szClassName = TEXT("MyClass");
HINSTANCE hInstance;
LRESULT CALLBACK MyWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
   WNDCLASS wnd;
   MSG msg;
   HWND hwnd;

   hInstance = hInst;

   wnd.style = CS_HREDRAW | CS_VREDRAW;
   wnd.lpfnWndProc = MyWndProc;
   wnd.cbClsExtra = 0;
   wnd.cbWndExtra = 0;
   wnd.hInstance = hInstance;
   wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); //default icon
   wnd.hCursor = LoadCursor(NULL, IDC_ARROW);   //default arrow mouse cursor
   wnd.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255,255,255));
   wnd.lpszMenuName = NULL;                     //no menu
   wnd.lpszClassName = szClassName;

   if(!RegisterClass(&wnd))                     //register the WNDCLASS
   {
       MessageBox(NULL, "This Program Requires Windows NT",
                        "Error", MB_OK);
       return 0;
   }

   hwnd = CreateWindowEx(
                        (DWORD)NULL,
                        szClassName,
                       "TicTacToe",
                       WS_OVERLAPPED|WS_SYSMENU, //basic window style
                       450,
                       200,       //set starting point to default value
                       400,
                       350,       //set all the dimensions to default value
                       NULL,                //no parent window
                       NULL,                //no menu
                       hInstance,
                       NULL);               //no parameters to pass
   ShowWindow(hwnd, iCmdShow);              //display the window on the screen
   UpdateWindow(hwnd);             //make sure the window is updated correctly

   while(GetMessage(&msg, NULL, 0, 0))      //message loop
   {
       TranslateMessage(&msg);
       DispatchMessage(&msg);
   }
   return msg.wParam;
}

LRESULT CALLBACK MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND button;
    HDC hdc = GetDC(hwnd);
   static char * message = new char[100];
    LRESULT textSize;
    HBRUSH color ;
    HDC hdcMem;
    PAINTSTRUCT ps;
    BITMAP bitmap;
    HGDIOBJ oldBitmap;
    HBITMAP hbmplogo = NULL;
    hbmplogo = (HBITMAP)LoadImage(hInstance, "logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmplogo, sizeof(bitmap), &bitmap);


    switch(msg)
    {
        case WM_CREATE:
            button = CreateWindowEx(
                               (DWORD) NULL,
                               TEXT("button"),                      // The class name required is button
                               TEXT("Let's play"),                  // the caption of the button
                               WS_CHILD |WS_VISIBLE | BS_PUSHBUTTON,  // the styles
                               80,230,                                  // the left and top co-ordinates
                               230,45,                              // width and height
                               hwnd,                                 // parent window handle
                               (HMENU)ID_BUTTON,                   // the ID of your button
                               hInstance,                            // the instance of your application
                               NULL) ;


                            break;
        case WM_PAINT:
              hdc = BeginPaint(hwnd, &ps);
              hdcMem = CreateCompatibleDC(hdc);
              SelectObject(hdcMem, hbmplogo);

            // Copy the bits from the memory DC into the current dc
                BitBlt(hdc,
                10,
                10,
                bitmap.bmWidth, bitmap.bmHeight,
                hdcMem, 0, 0, SRCCOPY);

            // Restore the old bitmap
                DeleteDC(hdcMem);

            EndPaint(hwnd, &ps);

             break;
            case WM_CLOSE:
            if(MessageBox(hwnd, "Are you're sure ? ", "Message", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
                DestroyWindow(hwnd);

            break ;




        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
