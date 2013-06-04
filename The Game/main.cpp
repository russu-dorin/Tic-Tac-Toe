#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#define ID_BUTTON 100

HINSTANCE hInstance;
HWND hwnd1;
HWND hwnd2;
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
LRESULT CALLBACK MyWndProc1(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MyWndProc2(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSEX wnd;
    WNDCLASSEX wnd2;
    memset(&wnd,0,sizeof(WNDCLASSEX));
	memset(&wnd2,0,sizeof(WNDCLASSEX));
    MSG msg;
    HWND hwnd1;
    HWND hwnd2;

    hInstance = hInst;

    // The Window 1 structure
    wnd.cbSize=sizeof(WNDCLASSEX);
    wnd.style = CS_HREDRAW | CS_VREDRAW;
    wnd.lpfnWndProc = MyWndProc1;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hInstance = hInstance;
    wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); //default icon
    wnd.hCursor = LoadCursor(NULL, IDC_ARROW);   //default arrow mouse cursor
    wnd.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255,255,255));
    wnd.lpszMenuName = NULL;                     //no menu
    wnd.lpszClassName = "MyClass1";
    wnd.hIconSm=NULL;

    if(!RegisterClassEx(&wnd))                     //register the WNDCLASS
        {MessageBox(NULL,"Could not register class1","Window Class Failed",MB_ICONERROR);
        }


    // The Window 2 structure
    wnd2.cbSize=sizeof(WNDCLASSEX);
    wnd2.hInstance = hInstance;
    wnd2.lpfnWndProc = MyWndProc2;      /* This function is called by windows */
    wnd2.style = CS_HREDRAW | CS_VREDRAW;    /* Redraw */
    wnd2.cbSize = sizeof (WNDCLASSEX);
    wnd2.hIcon = LoadIcon (NULL, IDI_ASTERISK);
    wnd2.hCursor = LoadCursor (NULL, IDC_ARROW);
    wnd2.lpszMenuName = NULL;                 /* Menu */
    wnd2.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wnd2.cbWndExtra = 0;                      /* structure or the window instance */
    wnd2.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    wnd2.lpszClassName = "MyClass2";
    wnd2.hIconSm=NULL;

    /* Register the window class, and if it fails quit the program */
   if (!RegisterClassEx (&wnd2))
        {MessageBox(NULL,"Could not register class2","Window Class Failed",MB_ICONERROR);
        }




    hwnd1 = CreateWindowEx(
                        NULL,
                        "MyClass1",
                       "Tic-Tac-Toe",
                       WS_OVERLAPPED|WS_SYSMENU, //basic window style
                       450,
                       200,       //set starting point to default value
                       400,
                       350,       //set all the dimensions to default value
                       NULL,                //no parent window
                       NULL,                //no menu
                       hInstance,
                       NULL);               //no parameters to pass
    ShowWindow(hwnd1, SW_SHOW);              //display the window on the screen
    UpdateWindow(hwnd1);             //make sure the window is updated correctly


    while(GetMessage(&msg, NULL, 0, 0))      //message loop
    {
       TranslateMessage(&msg);
       DispatchMessage(&msg);
    }
    return msg.wParam;
    }

LRESULT CALLBACK MyWndProc1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND button;
    HDC hdc = GetDC(hwnd);
    HDC hdcMem;
    PAINTSTRUCT ps;
    BITMAP bitmap;
    HBITMAP hbmplogo = NULL;
    hbmplogo = (HBITMAP)LoadImage(hInstance, "logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmplogo, sizeof(bitmap), &bitmap);


    switch(msg)
    {
        case WM_CREATE:
            button = CreateWindowEx(
                               NULL,
                               TEXT("button"),                      // The class name required is button
                               TEXT("Let's play"),                  // the caption of the button
                               WS_CHILD |WS_VISIBLE |BS_PUSHBUTTON,  // the styles
                               80,230,                                  // the left and top co-ordinates
                               230,45,                              // width and height
                               hwnd,                                 // parent window handle
                               (HMENU)ID_BUTTON,                   // the ID of your button
                               GetModuleHandle(NULL),                            // the instance of your application
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

            case WM_COMMAND:
                {
                    switch(LOWORD(wParam))
                    {
                    case ID_BUTTON:
                        {
                            if(!IsWindow(hwnd2))
                            {
                                hwnd2 = CreateWindowEx (
                                        0,                   /* Extended possibilites for variation */
                                        "MyClass2",         /* Classname */
                                        "Tic-Tac-Toe",       /* Title Text */
                                        WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, /* default window */
                                        CW_USEDEFAULT,       /* Windows decides the position */
                                        CW_USEDEFAULT,       /* where the window ends up on the screen */
                                        546,                 /* The programs width */
                                        625,                 /* and height in pixels */
                                        NULL,        /* The window is a child-window to desktop */
                                        NULL,                /* No menu */
                                        hInstance,       /* Program Instance handler */
                                        NULL                 /* No Window Creation data */
                                );
                                ShowWindow(hwnd2,SW_SHOW);
                                DestroyWindow(hwnd);
                            }

                        }

                        break;
                    }
                }
                break;

            case WM_CLOSE:
            if(MessageBox(hwnd, "Are you sure? ", "Message", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
                {
                    DestroyWindow(hwnd);
                    PostQuitMessage(0);
                }

            break ;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK MyWndProc2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		{
                if(MessageBox(hwnd, "Are you sure? ", "Message", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
                DestroyWindow(hwnd);
		}
		break;
	    case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
