#include "ticTacToe.h"
#include "resource.h"

#define ID_BUTTON 100

#define X 1
#define O 2

//Global Windows
HWND BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4,
     BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8, BUTTON_9; //Main buttons
HWND BUTTON_RESTART;
HWND STATIC_TURN;
HWND STATIC_TITLE;
HWND STATIC_XSCORE, STATIC_OSCORE, STATIC_PEACE_SCORE;
HWND STATIC_XVALUE, STATIC_OVALUE, STATIC_PEACE_VALUE;

//Icons
HICON xIcon = NULL;
HICON oIcon = NULL;
HICON peaceIcon = NULL;


enum{
    IDB_1, IDB_2, IDB_3, IDB_4, IDB_5, IDB_6, IDB_7, IDB_8, IDB_9,
    IDS_TURN,
    IDB_RESTART,
    IDS_TITLE,
    IDS_XSCORE, IDS_OSCORE, IDS_PEACE_SCORE,
    IDS_XVALUE, IDS_OVALUE, IDS_PEACE_VALUE,

    };

HINSTANCE hInstance;
HWND hwnd1;
HWND hwnd2;
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
LRESULT CALLBACK MyWndProc1(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Windows Procedure for the game
LRESULT CALLBACK MyWndProc2(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
void InitGUI(const HWND hwnd, CREATESTRUCT *cs);

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
    wnd.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255,128,0));
    wnd.lpszMenuName = NULL;                     //no menu
    wnd.lpszClassName = "MyClass1";
    wnd.hIconSm=NULL;

    if(!RegisterClassEx(&wnd))                     //register the WNDCLASS
        {MessageBox(NULL,"Could not register class1","Window Class Failed",MB_ICONERROR);
        }


    // The Window 2 structure
    wnd2.cbSize=sizeof(WNDCLASSEX);
    wnd2.hInstance = hInstance;
    wnd2.lpfnWndProc = MyWndProc2;                  /* This function is called by windows */
    wnd2.style = CS_HREDRAW | CS_VREDRAW;           /* Redraw */
    wnd2.cbSize = sizeof (WNDCLASSEX);
    wnd2.hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
    wnd2.hCursor = LoadCursor (NULL, IDC_ARROW);
    wnd2.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);  /* Menu */
    wnd2.cbClsExtra = 0;                            /* No extra bytes after the window class */
    wnd2.cbWndExtra = 0;                            /* structure or the window instance */
    wnd2.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wnd2.lpszClassName = "MyClass2";
    wnd2.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 0, 0, 0);


    /* Register the window class, and if it fails quit the program */
   if (!RegisterClassEx (&wnd2))
        {MessageBox(NULL,"Could not register class2","Window Class Failed",MB_ICONERROR);
        }


    hwnd1 = CreateWindowEx(
                        NULL,
                        "MyClass1",
                       "Tic-Tac-Toe",
                       WS_OVERLAPPED|WS_SYSMENU,        //basic window style
                       CW_USEDEFAULT,CW_USEDEFAULT,     //set starting point to default value
                       409, 350,                        //set all the dimensions to default value
                       NULL,                            //no parent window
                       NULL,                            //no menu
                       hInstance,
                       NULL);                           //no parameters to pass
    ShowWindow(hwnd1, SW_SHOW);              //display the window on the screen
    UpdateWindow(hwnd1);             //make sure the window is updated correctly
    // Place the Window in the center of the screen
    CenterWindow(hwnd1);

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
                               91,230,                                  // the left and top co-ordinates
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
                                        CW_USEDEFAULT,     /* where the window ends up on the screen */
                                        546,                 /* The programs width */
                                        625,                 /* and height in pixels */
                                        NULL,        /* The window is a child-window to desktop */
                                        NULL,                /* No menu */
                                        hInstance,       /* Program Instance handler */
                                        NULL                 /* No Window Creation data */
                                );
                                ShowWindow(hwnd2,SW_SHOW);
                                CenterWindow(hwnd2);
                                DestroyWindow(hwnd);
                            }

                        }

                        break;
                    }
                }
                break;

            case WM_CLOSE:
            /*if(MessageBox(hwnd, "Are you sure? ", "Message", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
                {
                    DestroyWindow(hwnd);
                    PostQuitMessage(0);
                }
              */
                DestroyWindow(hwnd);
                PostQuitMessage(0);
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

        case WM_CREATE:

            xIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_X));
            oIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_O));
            peaceIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_PEACE));


            InitGUI(hwnd, reinterpret_cast<CREATESTRUCT*>(lParam));



                break;

        case WM_COMMAND:

            switch(LOWORD(wParam))
            {

                    //Menu items
                    case IDR_FILE_QUIT:

                        PostQuitMessage(0);

                        break;

                    case IDR_OPTIONS_1PLAY:

                        SetWindowText(STATIC_TITLE, "One Player Game");

                        break;

                    case IDR_OPTIONS_2PLAY:

                        SetWindowText(STATIC_TITLE, "Two Player Game");

                        break;

                    case IDR_HELP_ABOUT:

                        DialogBox(GetModuleHandle(NULL),
                                MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);

                        break;

            }

            break;











        case WM_CLOSE:
            /*{
                    if(MessageBox(hwnd, "Are you sure? ", "Message", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
                    DestroyWindow(hwnd);
            }
            */
            DestroyWindow(hwnd);
            PostQuitMessage(0);
            break;
	    case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void InitGUI(const HWND hwnd, CREATESTRUCT *cs)
{
       RECT rc = {45, 70, 150, 150};

       BUTTON_1 = CreateControl("BUTTON",       //Type of control
                                "",             //Caption for control
                                hwnd,           //Parent window
                                cs->hInstance,  //HINSTANCE
                                BS_ICON,        //dwStyle
                                0,              //dwExStyle
                                rc,             //RECT struct
                                IDB_1           //ID
                                );

        rc.left += 150;
        BUTTON_2 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_2
                                );

        rc.left += 150;
        BUTTON_3 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_3
                                );

        rc.left -= 300;
        rc.top += 150;
        BUTTON_4 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_4
                                );

        rc.left += 150;
        BUTTON_5 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_5
                                );

        rc.left += 150;
        BUTTON_6 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_6
                                );

        rc.left -= 300;
        rc.top += 150;
        BUTTON_7 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_7
                                );

        rc.left += 150;
        BUTTON_8 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_8
                                );

        rc.left += 150;
        BUTTON_9 = CreateControl("BUTTON",
                                "",
                                hwnd,
                                cs->hInstance,
                                BS_ICON,
                                0,
                                rc,
                                IDB_9
                                );

        SetRect(&rc, 214, 20, 116, 18);
        STATIC_TITLE = CreateControl("STATIC",
                                     "One Player Game",
                                     hwnd,
                                     cs->hInstance,
                                     SS_SIMPLE,
                                     WS_EX_STATICEDGE,
                                     rc,
                                     IDS_TITLE
                                     );

        rc.left -= 195;
        STATIC_TURN = CreateControl("STATIC",
                                    "Krestik's turn",
                                    hwnd,
                                    cs->hInstance,
                                    SS_SIMPLE,
                                    0,
                                    rc,
                                    IDS_TURN
                                    );

        SetRect(&rc, 430, 13, 70, 30);
        BUTTON_RESTART = CreateControl("BUTTON",
                                       "Restart",
                                       hwnd,
                                       cs->hInstance,
                                       BS_PUSHBUTTON,
                                       WS_EX_CLIENTEDGE,
                                       rc,
                                       IDB_RESTART
                                       );

        ShowWindow(BUTTON_RESTART, false);

        SetRect(&rc, 45, 540, 90, 19);
        STATIC_XSCORE = CreateControl("STATIC",
                                      "Krestik Score:",
                                      hwnd,
                                      cs->hInstance,
                                      SS_SIMPLE,
                                      0,
                                      rc,
                                      IDS_XSCORE
                                      );

        rc.left += 95;
        STATIC_XVALUE = CreateControl("STATIC",
                                      "0",
                                      hwnd,
                                      cs->hInstance,
                                      SS_SIMPLE,
                                      0,
                                      rc,
                                      IDS_XVALUE
                                      );

        rc.left += 80;
        STATIC_PEACE_SCORE = CreateControl("STATIC",
                                        "Peace Score:",
                                        hwnd,
                                        cs->hInstance,
                                        SS_SIMPLE,
                                        0,
                                        rc,
                                        IDS_PEACE_SCORE
                                        );

        rc.left += 90;
        STATIC_PEACE_VALUE = CreateControl("STATIC",
                                        "0",
                                        hwnd,
                                        cs->hInstance,
                                        SS_SIMPLE,
                                        0,
                                        rc,
                                        IDS_PEACE_VALUE
                                        );

        rc.left += 82;
        STATIC_OSCORE = CreateControl("STATIC",
                                      "Nolik's Score:",
                                      hwnd,
                                      cs->hInstance,
                                      SS_SIMPLE,
                                      0,
                                      rc,
                                      IDS_OSCORE
                                      );

        rc.left += 94;
        STATIC_OVALUE = CreateControl("STATIC",
                                      "0",
                                      hwnd,
                                      cs->hInstance,
                                      SS_SIMPLE,
                                      0,
                                      rc,
                                      IDS_OVALUE
                                      );
}



BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        switch(msg)
        {
                case WM_COMMAND:

                    switch(LOWORD(wParam))
                    {
                            case IDOK:

                                EndDialog(hwnd, IDOK);

                                break;

                            case IDCANCEL:

                                EndDialog(hwnd, IDCANCEL);

                                break;
                    }

                    break;

                default:

                    return FALSE;

                    break;
        }

        return TRUE;
}
