/***************************************************
*                                                  *
*  MAIN                                            *
*                                                  *
***************************************************/
#define RASTER_X 20
#define RASTER_Y 20

#include <stdio.h>
#include <windows.h>
#include <wchar.h>

#include "resource.h"
#include "mod/item.h"
#include "windraw.h"
#include "wintoolbox/pipes.h"
#include "dialog.h"

#include "wintoolbox/menu/menu.h"
#include "def/menu/def_menu_main.h"
#include "dialog/dialog_main.h"
#include "dialog/alerts.h"
#include "wintoolbox/grid/grid.h"
#include "mod/lable.h"

LRESULT CALLBACK MainWindowProcedure2(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK OutWindowProcedure(HWND,UINT,WPARAM,LPARAM);

char szClassName_Main[]="TestMan Main-Window";
char szClassName_Out[]="TestMan Output-Window";

bool ini_winclasses(HINSTANCE hThisInstance)
{
    WNDCLASSEX wincl;
    WNDCLASSEX winc2;

    /* The Window structure */
    wincl.hInstance=hThisInstance;
    wincl.lpszClassName=szClassName_Main;
    wincl.lpfnWndProc=MainWindowProcedure2;
    wincl.style=CS_DBLCLKS;
    wincl.cbSize=sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon=LoadIconA(hThisInstance,MAKEINTRESOURCE(IDI_SMALL));
    wincl.hIconSm=LoadIcon(hThisInstance,MAKEINTRESOURCE(IDI_SMALL));
    wincl.hCursor=LoadCursor(NULL,IDC_ARROW);
    wincl.lpszMenuName=NULL;
    wincl.cbClsExtra=0;
    wincl.cbWndExtra=0;
    wincl.hbrBackground=(HBRUSH)COLOR_BACKGROUND;


    /* The Window structure */
    winc2.hInstance=hThisInstance;
    winc2.lpszClassName=szClassName_Out;
    winc2.lpfnWndProc=OutWindowProcedure;
    winc2.style=CS_DBLCLKS;
    winc2.cbSize=sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    winc2.hIcon=LoadIconA(hThisInstance,MAKEINTRESOURCE(IDI_SMALL));
    winc2.hIconSm=LoadIcon(hThisInstance,MAKEINTRESOURCE(IDI_SMALL));
    winc2.hCursor=LoadCursor(NULL,IDC_ARROW);
    winc2.lpszMenuName=NULL;
    winc2.cbClsExtra=0;
    winc2.cbWndExtra=0;
    winc2.hbrBackground=(HBRUSH)COLOR_BACKGROUND;


    return RegisterClassEx(&wincl) && RegisterClassEx(&winc2);
}
HWND CreateAHorizontalScrollBar(HINSTANCE hThisInstance,HWND hwndParent, int sbHeight)
{
    RECT rect;

    // Get the dimensions of the parent window's client area;
    if (!GetClientRect(hwndParent, &rect))
        return NULL;

    // Create the scroll bar.
    return CreateWindowEx(
            0,                      // no extended styles
            "SCROLLBAR",           // scroll bar control class
            (PTSTR) NULL,           // no window text
            WS_CHILD | WS_VISIBLE   // window styles
                | SBS_VERT,         // horizontal scroll bar style
            30*RASTER_X+2,              // horizontal position
            RASTER_X*2, // vertical position
            RASTER_X-4,             // width of the scroll bar
            rect.bottom-RASTER_X*2,               // height of the scroll bar
            hwndParent,             // handle to main window
            (HMENU) NULL,           // no menu
            hThisInstance,                // instance owning this window
            (PVOID) NULL            // pointer not needed
        );
}
bool ini_windowsetup(HINSTANCE hThisInstance,int nCmdShow)
{
    int i;
    hwnd=CreateWindowEx(
           0,
           szClassName_Main,
           "TestMan",
           WS_POPUPWINDOW | WS_CAPTION,// | WS_OVERLAPPEDWINDOW,// | WS_EX_CONTROLPARENT,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           RASTER_X*31+5,
           RASTER_Y*24+10,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );
    hwndOut=CreateWindowEx(
           0,
           szClassName_Out,
           "TestManOut",
           WS_OVERLAPPEDWINDOW,// | WS_EX_CONTROLPARENT,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           823,
           643,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );

    //hwndButton[1] = CreateWindow("BUTTON","OK",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,0,0,60,20,hwnd,NULL,hThisInstance,NULL);
    /*
    hwndButton[3]=CreateWindow("BUTTON","new",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,260,3,50,20,hwnd,NULL,hThisInstance,NULL);
    hwndButton[2]=CreateWindow("BUTTON","open",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,310,3,50,20,hwnd,NULL,hThisInstance,NULL);
    hwndButton[4]=CreateWindow("BUTTON","save",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,360,3,50,20,hwnd,NULL,hThisInstance,NULL);
    hwndButton[5]=CreateWindow("BUTTON","save as",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,410,3,70,20,hwnd,NULL,hThisInstance,NULL);
    hwndButton[6]=CreateWindow("BUTTON","conf",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,480,3,63,20,hwnd,NULL,hThisInstance,NULL);
    hwndButton[1]=CreateWindow("BUTTON","about",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,27.15*RASTER_X,3,RASTER_X*3.75,RASTER_Y*1.75,hwnd,NULL,hThisInstance,NULL);
    */
    for(i=0;i<20;i++)
    {
        hwndEdit[i]=CreateWindow("EDIT","",ES_AUTOHSCROLL | WS_TABSTOP | WS_VISIBLE | ES_LEFT | WS_CHILD | BS_DEFPUSHBUTTON,0,41+i*RASTER_Y,239,RASTER_Y-1,hwnd,NULL,hThisInstance,NULL);
        hwndRunButton[i]=CreateWindow("BUTTON",">",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,240,41+i*RASTER_Y,20,RASTER_Y-1,hwnd,NULL,hThisInstance,NULL);
    }

    //hwndCB=CreateWindow("EDIT","",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,RASTER_X*0.5,RASTER_Y*0.5,259-RASTER_X*1,RASTER_Y*1,hwnd,NULL,hThisInstance,NULL);
    hwndCB=CreateWindow("EDIT","",ES_AUTOHSCROLL | WS_VSCROLL | ES_MULTILINE | WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,0,3,240,RASTER_Y*1.75,hwnd,NULL,hThisInstance,NULL);
    //CreateWindow("EDIT","",ES_AUTOHSCROLL | WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,260,3,356,RASTER_Y*1.75,hwnd,NULL,hThisInstance,NULL);
    hwndLE=CreateWindow("EDIT","",ES_AUTOHSCROLL | WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,261,8,339,24,hwnd,NULL,hThisInstance,NULL);

    hwndText0=CreateWindow("EDIT","",ES_AUTOHSCROLL | WS_TABSTOP | ES_AUTOVSCROLL | WS_VSCROLL | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | WS_TABSTOP | WS_VISIBLE | WS_CHILD,20,25,400,600,hwndOut,NULL,hThisInstance,NULL);
    hwndText1=CreateWindow("EDIT","",ES_AUTOHSCROLL | WS_TABSTOP | ES_AUTOVSCROLL | WS_VSCROLL | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | WS_TABSTOP | WS_VISIBLE | WS_CHILD,405,25,400,600,hwndOut,NULL,hThisInstance,NULL);
    hwndOEd00=CreateWindow("EDIT","",ES_AUTOHSCROLL | WS_TABSTOP | ES_LEFT | WS_TABSTOP | WS_VISIBLE | WS_CHILD,80,5,240,18,hwndOut,NULL,hThisInstance,NULL);
    hwndOEd01=CreateWindow("EDIT","",ES_AUTOHSCROLL | WS_TABSTOP | ES_LEFT | WS_TABSTOP | WS_VISIBLE | WS_CHILD,400,5,180,18,hwndOut,NULL,hThisInstance,NULL);
    hwndOBu01=CreateWindow("BUTTON","<<",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,400,580,50,24,hwndOut,NULL,hThisInstance,NULL);
    hwndOBu02=CreateWindow("BUTTON","apply",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,0,580,80,24,hwndOut,NULL,hThisInstance,NULL);
    hwndOBu00=CreateWindow("BUTTON","run",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,600,0,50,24,hwndOut,NULL,hThisInstance,NULL);

    ShowWindow(hwnd,nCmdShow);
    //ShowWindow(hwndOut,nCmdShow);

    setup_main_menu(hwnd,new MenuHelper());

    hwndscr=CreateAHorizontalScrollBar(hThisInstance,hwnd,24);
    SCROLLINFO si;
            si.cbSize=sizeof(si);
            si.fMask=SIF_RANGE | SIF_PAGE | SIF_POS;
            si.nMin=0;
            si.nMax=global_scrollymax;
            si.nPage=global_scrollpagey;
            si.nPos=global_scrolly;
            SetScrollInfo(hwndscr,SB_CTL,&si,TRUE);

    grid=new GridHelper(260,40,20,20,17,20);
    grid->setfunction_selectbox(selectbox);

    UpdateWindow(hwnd);

    return 1;
}
int WINAPI WinMain(HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
    MSG messages;

    ini_item();
    ini_dialog();
    ini_windraw();
    if(!ini_winclasses(hThisInstance))return 0;
    ini_windowsetup(hThisInstance,nCmdShow);

    fillall();
    ischanged=false;

    while(GetMessage(&messages,NULL,0,0))
    {
        if(IsDialogMessage(hwnd,&messages)){}
        else{
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }
    }

    free_item();
    free_dialog();

    return messages.wParam;
}
LRESULT CALLBACK MainWindowProcedure2(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    PAINTSTRUCT ps;
    SCROLLINFO si;
    //RECT r;
    //static bool lmb_status=0;
    int i;
    bool doscroll=true;

    int winxx;
    int winyy;

    switch(message)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
            BeginPaint(hwnd,&ps);
            paint(ps.hdc);
            grid->paint(ps.hdc);
            EndPaint(hwnd,&ps);
            break;
        case WM_SIZE:
            winxx=LOWORD(lParam);
            winyy=HIWORD(lParam);
            MoveWindow(hwndText0,0,0,winxx/2-2,winyy,1);
            MoveWindow(hwndText1,winxx/2+2,0,winxx/2-2,winyy,1);
            break;
        case WM_MOUSEMOVE:
            grid->mousemove(hwnd,LOWORD(lParam),HIWORD(lParam));
            break;
        case WM_LBUTTONDOWN:
            grid->lbuttondown(hwnd,LOWORD(lParam),HIWORD(lParam));
            break;
        case WM_LBUTTONUP:
            grid->lbuttonup(hwnd,LOWORD(lParam),HIWORD(lParam));
            break;
        case WM_RBUTTONDOWN:
            grid->rbuttondown(hwnd,LOWORD(lParam),HIWORD(lParam));
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case DEF_MENU_MAIN_FILE_EXIT:
                    PostQuitMessage(0);
                    break;
                case DEF_MENU_MAIN_FILE_NEW:
                    main_reset();
                    break;
                case DEF_MENU_MAIN_FILE_OPEN:
                    main_open();
                    break;
                case DEF_MENU_MAIN_FILE_SAVE:
                    main_save(hwnd);
                    break;
                case DEF_MENU_MAIN_FILE_SAVEAS:
                    main_saveas(hwnd);
                    break;
                case DEF_MENU_MAIN_EDIT_CONF:
                    openconf();
                    break;
                case DEF_MENU_MAIN_EDIT_MODE:
                    grid->seteditmode(!grid->geteditmode());
                    break;
                case DEF_MENU_MAIN_RUN_ALL:
                    runalltests();
                    break;
                case DEF_MENU_MAIN_RUN_RESET:
                    resetalltests();
                    break;
                case DEF_MENU_MAIN_HELP_ABOUT:
                    showAbout(hwnd);
                    break;
            }
            switch(HIWORD(wParam))
            {
                case BN_CLICKED:
                    for(i=0;i<20;i++)
                    {
                        if((HWND)lParam==hwndRunButton[i])
                        {
                            item *ti=global_list->findnext(i+global_scrolly);
                            if(ti)
                            {
                                global_selline=i;
                                global_scrolly_out=global_scrolly;
                                SendMessageA(hwndOEd00,WM_SETTEXT,0,(LPARAM)(ti->getrun()));
                                SendMessageA(hwndOEd01,WM_SETTEXT,0,(LPARAM)(ti->getout()));
                                SendMessageA(hwndText0,WM_SETTEXT,0,(LPARAM)(ti->getfile()));
                                SendMessageA(hwndText1,WM_SETTEXT,0,(LPARAM)"");
                                ShowWindow(hwndOut,SW_SHOWNORMAL);
                                ti->runtest();
                            }
                        }
                    }
                    break;
                case EN_CHANGE:
                    for(i=0;i<20;i++)
                    {
                        if((HWND)lParam==hwndEdit[i])
                        {
                            char a[200];
                            *((int *)a)=50;
                            int ln=SendMessage(hwndEdit[i],EM_GETLINE,0,(LPARAM)a);
                            a[ln]=0;
                            item *ti=global_list->findnext(i+global_scrolly);
                            if(ti)
                            {
                                ti->setname(a);
                            }
                        }
                    }

                    if((HWND)lParam==hwndLE)
                    {
                        char a[128];
                        *((int *)a)=127;
                        int ln=SendMessage(hwndLE,EM_GETLINE,0,(LPARAM)a);
                        a[ln]=0;
                        global_lablelist.settext(a);
                    }

                    ischanged=true;
                    break;
            }
            break;
        case WM_VSCROLL:
            switch(LOWORD(wParam))
            {
                case SB_PAGEUP:
                    global_scrolly-=20;
                    break;
                case SB_PAGEDOWN:
                    global_scrolly+=20;
                    break;
                case SB_LINEUP:
                    global_scrolly--;
                    break;
                case SB_LINEDOWN:
                    global_scrolly++;
                    break;
                case SB_THUMBPOSITION:
                    global_scrolly=HIWORD(wParam);
                    break;
                default:
                    doscroll=false;
                    break;
            }

            if(doscroll)
            {
                global_scrolly=max(0,global_scrolly);

                if(global_scrolly+global_scrollpagey>global_scrollymax+1)
                {
                    global_scrollymax=global_scrolly+global_scrollpagey-1;
                }

                si.cbSize=sizeof(si);
                si.fMask=SIF_RANGE | SIF_PAGE | SIF_POS;
                si.nMin=0;
                si.nMax=global_scrollymax;
                si.nPage=global_scrollpagey;
                si.nPos=global_scrolly;
                SetScrollInfo(hwndscr,SB_CTL,&si,TRUE);
                fillall();
            }

            break;
        default:
            return DefWindowProc(hwnd,message,wParam,lParam);
    }

    return 0;
}
LRESULT CALLBACK OutWindowProcedure(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    PAINTSTRUCT ps;
    static int winxx=0;
    static int winyy=0;

    switch(message)
    {
        //case WM_DESTROY:
            //ShowWindow(hwndOut,SW_HIDE);
            //break;
        case WM_CLOSE:
            ShowWindow(hwndOut,SW_HIDE);
            break;
        case WM_PAINT:
            BeginPaint(hwnd,&ps);
            //paint(ps.hdc);
            HBRUSH hbr;
            HANDLE oldhbr;
            HPEN hpe;
            HANDLE oldhpe;

            hbr=CreateSolidBrush(RGB(255,255,255));
            oldhbr=SelectObject(ps.hdc,hbr);
            hpe=CreatePen(1,2,RGB(255,0,0));
            oldhpe=SelectObject(ps.hdc,hpe);

            Rectangle(ps.hdc,1,1,winxx,25);
            TextOutA(ps.hdc,5,5,"Command:",8);
            TextOutA(ps.hdc,winxx-285,5,"Target:",7);
            TextOutA(ps.hdc,0,34,"Valid Output: ",14);
            TextOutA(ps.hdc,winxx/2+2,34,"Test Output: ",13);

            SelectObject(ps.hdc,oldhbr);
            DeleteObject(hbr);
            SelectObject(ps.hdc,oldhpe);
            DeleteObject(hpe);

            EndPaint(hwnd,&ps);
            break;
        case WM_SIZE:
            winxx=LOWORD(lParam);
            winyy=HIWORD(lParam);
            MoveWindow(hwndText0,0,50,winxx/2-2,winyy-75,1);
            MoveWindow(hwndText1,winxx/2+2,50,winxx/2-2,winyy-75,1);
            MoveWindow(hwndOBu02,0,winyy-25,80,25,1);
            MoveWindow(hwndOBu01,winxx/2+2,winyy-25,50,25,1);
            MoveWindow(hwndOBu00,winxx-52,2,50,21,1);
            MoveWindow(hwndOEd00,80,5,winxx-375,18,1);
            MoveWindow(hwndOEd01,winxx-235,5,180,18,1);
            InvalidateRect(hwndOut,0,1);
            break;
        case WM_COMMAND:
            switch(HIWORD(wParam))
            {
                case BN_CLICKED:
                    if((HWND)lParam==hwndOBu00)
                    {
                        item *ti=global_list->findnext(global_selline+global_scrolly_out);
                        if(ti)
                        {
                            ti->runtest();
                        }
                    }
                    else if((HWND)lParam==hwndOBu01)
                    {
                        int len=SendMessage(hwndText1,WM_GETTEXTLENGTH,0,0);
                        char *a=(char *)malloc((len+1)*sizeof(char));
                        len=SendMessage(hwndText1,WM_GETTEXT,len+1,(LPARAM)a);
                        a[len]=0;
                        SendMessage(hwndText0,WM_SETTEXT,0,(LPARAM)a);
                        free(a);
                    }
                    else if((HWND)lParam==hwndOBu02)
                    {
                        int len=SendMessage(hwndText1,WM_GETTEXTLENGTH,0,0);
                        char *a=(char *)malloc((len+1)*sizeof(char));
                        len=SendMessage(hwndText1,WM_GETTEXT,len+1,(LPARAM)a);
                        a[len]=0;
                        item *ti=global_list->findnext(global_selline+global_scrolly_out);
                        if(ti)
                        {
                            ti->setfile(a);
                        }
                        free(a);
                    }
                    break;
                case EN_CHANGE:
                    if((HWND)lParam==hwndOEd00)
                    {
                        char a[256];
                        *((int *)a)=255;
                        int ln=SendMessage(hwndOEd00,EM_GETLINE,0,(LPARAM)a);
                        a[ln]=0;
                        item *ti=global_list->findnext(global_selline+global_scrolly_out);
                        if(ti)
                        {
                            ti->setrun(a);
                        }
                    }
                    else if((HWND)lParam==hwndOEd01)
                    {
                        char a[256];
                        *((int *)a)=255;
                        int ln=SendMessage(hwndOEd01,EM_GETLINE,0,(LPARAM)a);
                        a[ln]=0;
                        item *ti=global_list->findnext(global_selline+global_scrolly_out);
                        if(ti)
                        {
                            ti->setout(a);
                        }
                    }
                    break;
            }
            break;
        default:
            return DefWindowProc(hwnd,message,wParam,lParam);
    }

    return 0;
}
