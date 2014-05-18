/***************************************************
*                                                  *
*                                                  *
*                                                  *
***************************************************/
#include <stdio.h>
#include <windows.h>
#include <wchar.h>

#include "resource.h"
#include "item.h"
#include "windraw.h"
#include "pipes.h"
#include "dialog.h"

LRESULT CALLBACK MainWindowProcedure(HWND,UINT,WPARAM,LPARAM);
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
    wincl.lpfnWndProc=MainWindowProcedure;
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
bool ini_windowsetup(HINSTANCE hThisInstance,int nCmdShow)
{
    int i;
    hwnd=CreateWindowEx(
           0,
           szClassName_Main,
           "TestMan",
           WS_OVERLAPPEDWINDOW,// | WS_EX_CONTROLPARENT,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           RASTER_X*31+5,
           RASTER_Y*24+7,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );
    hwndOut=CreateWindowEx(
           0,
           szClassName_Out,
           "TestMan",
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
    hwndButton[3]=CreateWindow("BUTTON","new",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,260,0,50,20,hwnd,NULL,hThisInstance,NULL);
    hwndButton[2]=CreateWindow("BUTTON","open",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,310,0,50,20,hwnd,NULL,hThisInstance,NULL);
    hwndButton[4]=CreateWindow("BUTTON","save",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,360,0,50,20,hwnd,NULL,hThisInstance,NULL);
    hwndButton[5]=CreateWindow("BUTTON","save as",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,410,0,70,20,hwnd,NULL,hThisInstance,NULL);
    hwndButton[6]=CreateWindow("BUTTON","conf",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,480,0,60,20,hwnd,NULL,hThisInstance,NULL);
    hwndButton[1]=CreateWindow("BUTTON","about",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,27.25*RASTER_X,0.25*RASTER_Y,RASTER_X*2.75,RASTER_Y*1.5,hwnd,NULL,hThisInstance,NULL);
    for(i=0;i<20;i++)
    {
        hwndEdit[i]=CreateWindow("EDIT","",ES_AUTOHSCROLL | WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,0,41+i*RASTER_Y,239,RASTER_Y-1,hwnd,NULL,hThisInstance,NULL);
        hwndRunButton[i]=CreateWindow("BUTTON",">",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,240,41+i*RASTER_Y,20,RASTER_Y-1,hwnd,NULL,hThisInstance,NULL);
    }

    //hwndCB=CreateWindow("EDIT","",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,RASTER_X*0.5,RASTER_Y*0.5,259-RASTER_X*1,RASTER_Y*1,hwnd,NULL,hThisInstance,NULL);
    hwndCB=CreateWindow("EDIT","",ES_AUTOHSCROLL | WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,RASTER_X*0.25,RASTER_Y*0.25,259-RASTER_X*0.5,RASTER_Y*1.5,hwnd,NULL,hThisInstance,NULL);

    hwndText0=CreateWindow("EDIT","",ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_VSCROLL | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | WS_TABSTOP | WS_VISIBLE | WS_CHILD,2,2,400,600,hwndOut,NULL,hThisInstance,NULL);
    hwndText1=CreateWindow("EDIT","",ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_VSCROLL | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_WANTRETURN | WS_TABSTOP | WS_VISIBLE | WS_CHILD,405,2,400,600,hwndOut,NULL,hThisInstance,NULL);

    ShowWindow(hwnd,nCmdShow);
    //ShowWindow(hwndOut,nCmdShow);

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
        if (IsDialogMessage(hwnd,&messages)){}
        else{
        TranslateMessage(&messages);
        DispatchMessage(&messages);
        }
    }

    free_item();
    free_dialog();

    return messages.wParam;
}

LRESULT CALLBACK MainWindowProcedure(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    PAINTSTRUCT ps;RECT r;
    static bool lmb_status=0;
    int i;

    switch(message)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
            BeginPaint(hwnd,&ps);
            paint(ps.hdc);
            EndPaint(hwnd,&ps);
            break;
        case WM_MOUSEMOVE:
            if(lmb_status)
            {
                if(global_currentcol==getrow(LOWORD(lParam))-1 && global_currentrow==getcol(HIWORD(lParam)))
                {
                    if(global_mark_status==0)
                    {
                        global_mark_status=MARK_R;
                        r=getrect2(global_currentcol,global_currentrow);
                        InvalidateRect(hwnd,&r,1);
                        ischanged=true;
                    }
                }
                else if(global_currentcol==getrow(LOWORD(lParam))+1 && global_currentrow==getcol(HIWORD(lParam)))
                {
                    if(global_mark_status==0)
                    {
                        global_mark_status=MARK_L;
                        r=getrect2(global_currentcol,global_currentrow);
                        InvalidateRect(hwnd,&r,1);
                        ischanged=true;
                    }
                }
                else
                {
                    if(global_mark_status==MARK_R)
                    {
                        global_mark_status=0;
                        r=getrect2(global_currentcol,global_currentrow);
                        InvalidateRect(hwnd,&r,1);
                        ischanged=true;
                    }
                    if(global_mark_status==MARK_L)
                    {
                        global_mark_status=0;
                        r=getrect2(global_currentcol,global_currentrow);
                        InvalidateRect(hwnd,&r,1);
                        ischanged=true;
                    }
                }
            }
            break;
        case WM_LBUTTONDOWN:
            lmb_status=1;
            global_mark_status=0;
            r=getrect2(global_currentcol,global_currentrow);
            InvalidateRect(hwnd,&r,1);
            global_currentcol=getrow(LOWORD(lParam));
            global_currentrow=getcol(HIWORD(lParam));
            r=getrect2(global_currentcol,global_currentrow);
            InvalidateRect(hwnd,&r,1);
            break;
        case WM_LBUTTONUP:
            lmb_status=0;
            if(global_currentcol==getrow(LOWORD(lParam)) && global_currentrow==getcol(HIWORD(lParam)))
            {
                item *ki=global_list->findnext(boxy(global_currentrow));
                if(ki)ki->chsymbol(boxx(global_currentcol));
                r=getrect2(global_currentcol,global_currentrow);
                InvalidateRect(hwnd,&r,1);
                ischanged=true;
            }
            if(global_mark_status==MARK_R)
            {
                item *ki=global_list->findnext(boxy(global_currentrow));
                if(ki)ki->chsymbol(boxx(global_currentcol),1);
                r=getrect2(global_currentcol,global_currentrow);
                InvalidateRect(hwnd,&r,1);
                ischanged=true;
            }
            else if(global_mark_status==MARK_L)
            {
                item *ki=global_list->findnext(boxy(global_currentrow));
                if(ki)ki->chsymbol(boxx(global_currentcol),2);
                r=getrect2(global_currentcol,global_currentrow);
                InvalidateRect(hwnd,&r,1);
                ischanged=true;
            }
            global_mark_status=0;
            break;
        case WM_RBUTTONDOWN:
            r=getrect2(global_currentcol,global_currentrow);
            InvalidateRect(hwnd,&r,1);
            global_currentcol=getrow(LOWORD(lParam));
            global_currentrow=getcol(HIWORD(lParam));
            r=getrect2(global_currentcol,global_currentrow);
            InvalidateRect(hwnd,&r,1);
            setcolor(global_currentcol,global_currentrow,hwnd);
            break;
        //case DM_GETDEFID:
            //MessageBoxA(hwnd,"ToDoMan","About",0);
            //break;
        case WM_COMMAND:
            switch(HIWORD(wParam))
            {
                case BN_CLICKED:
                    if((HWND)lParam==hwndButton[1])
                    {
                        MessageBoxA(hwnd,"TestMan\n(Test-Manager)\nVersion b00.01\n\nCopyright 2014 by [PSP].\nSee README.TXT for further information.","About",0);
                    }
                    else if((HWND)lParam==hwndButton[2])
                    {
                        if(!ischanged || IDOK==MessageBoxA(hwnd,"Dies setzt alle Eingaben zurück.\nNicht gespeicherte Eingaben gehen verlohren.","HALLO",MB_OKCANCEL))
                        {
                            openlist(hwnd);
                            SetWindowTextW(hwnd,DOC_FILENAME);
                            InvalidateRect(hwnd,0,1);
                        }
                    }
                    else if((HWND)lParam==hwndButton[3])
                    {
                        if(!ischanged || IDOK==MessageBoxA(hwnd,"Dies setzt alle Eingaben zurück.\nNicht gespeicherte Eingaben gehen verlohren.","HALLO",MB_OKCANCEL))
                        {
                            free_item();
                            ini_item();
                            free_filename();
                            fillall();
                            SetWindowTextW(hwnd,DOC_FILENAME);
                            ischanged=false;
                            InvalidateRect(hwnd,0,1);
                        }
                    }
                    else if((HWND)lParam==hwndButton[4])
                    {
                        savelist(hwnd);
                        SetWindowTextW(hwnd,DOC_FILENAME);
                    }
                    else if((HWND)lParam==hwndButton[5])
                    {
                        savelistas(hwnd);
                        SetWindowTextW(hwnd,DOC_FILENAME);
                    }
                    else if((HWND)lParam==hwndButton[6])
                    {
                        openconf();
                    }
                    else
                    {
                        for(i=0;i<20;i++)
                        {
                            if((HWND)lParam==hwndRunButton[i])
                            {
                                item *ti=global_list->findnext(i);
                                if(ti)
                                {
                                    if(ti->getname()[0]!=0)
                                    {

                                        char a[600];
                                        char output_style[512];

                                        //A) programm-Name aus Titelfeld.
                                        //*((int *)a)=50;//Maximale Anzahl Zeichen.
                                        //int ln=SendMessage(hwndCB,EM_GETLINE,0,(LPARAM)a);
                                        //a[ln]=0;//wird möglicherweise nicht nullterminiert

                                        //B) programm-Name aus conf-File, je nach suffix.
                                        int infilenameln=strlen(ti->getname());
                                        if(strcmp(&(ti->getname()[infilenameln-strlen(EXTE1)]),EXTE1)==0)
                                        {
                                            strcpy(a,PROG1);
                                            strcpy(output_style,OUTP1);
                                        }
                                        else if(strcmp(&(ti->getname()[infilenameln-strlen(EXTE2)]),EXTE2)==0)
                                        {
                                            strcpy(a,PROG2);
                                            strcpy(output_style,OUTP2);
                                        }
                                        else
                                        {
                                            strcpy(a,PROG3);
                                            strcpy(output_style,OUTP3);
                                        }

                                        //MessageBoxA(0,a,"",0);
                                        //MessageBoxA(0,ti->getname(),"",0);
                                        //MessageBoxA(0,ti->getname(),"",0);
                                        //xexecute(a,ti->getname());
                                        char *c=(char *)malloc((strlen(a)+strlen(ti->getname())+10)*sizeof(char));
                                        strcpy(c,a);
                                        strcat(c," ");
                                        strcat(c,ti->getname());
                                        int u=xCreatePipe();
                                        int v=xCreatePipe();//"D:\\Q\\WORK\\compiler\\CB\\psp\\bin\\Debug\\psp.exe"
                                        PROCESS_INFORMATION pi=xCreateProcess(c,u,v);
                                        xClosePipeHandle(u,1);
                                        char *rr=xReadFromPipe(u);
                                        DWORD return_val;
                                        GetExitCodeProcess(pi.hProcess,&return_val);
                                        CloseSubProcess(pi);
                                        xCloseAllPipes();

                                        rr=(char *)realloc(rr,(strlen(rr)+100)*sizeof(char));
                                        sprintf(&rr[strlen(rr)],"\n\r\n\rProcess returned (%d)\n",(unsigned int)return_val);

                                        if(strcmp(output_style,"SIMPLETEST")==0 && rr[0]==0)// || r[0]=='\n')
                                        {
                                            MessageBoxA(0,"Test-OK!","Result",0);
                                        }
                                        else if(strcmp(output_style,"SIMPLETEST")==0 || strcmp(output_style,"EMULATOR")==0)
                                        {
                                            SetWindowText(hwndText1,rr);
                                            SetWindowText(hwndText0,c);
                                        }
                                        if(strcmp(output_style,"COMPILER")==0)
                                        {
                                            SetWindowText(hwndText1,rr);
                                            //MessageBoxA(0,r,"",0);
                                            //*
                                            //MessageBoxA(0,ti->getname(),"",0);
                                            int lln=1024;
                                            char *input=(char *)malloc(lln*sizeof(char));
                                            FILE *f=fopen(ti->getname(),"rb");
                                            if(f!=0)
                                            {
                                                int ii=0;char cc=fgetc(f);
                                                while(!feof(f))
                                                {
                                                    if(ii>lln-3)
                                                    {
                                                        lln=lln*2;
                                                        input=(char *)realloc(input,lln*sizeof(char));
                                                    }
                                                    input[ii++]=cc;
                                                    cc=fgetc(f);
                                                }
                                                input[ii]=0;
                                                SetWindowText(hwndText0,input);
                                                //MessageBoxA(0,input,"",0);
                                                free(input);
                                                fclose(f);
                                            }
                                            else
                                            {
                                                SetWindowText(hwndText0,"");
                                                MessageBoxA(0,"could'nt open input file","",0);
                                            }
                                            //*/


                                        }

                                        ShowWindow(hwndOut,SW_NORMAL);

                                        free(rr);
                                        free(c);
                                    }
                                }
                            }
                        }
                    }
                    break;
                case EN_CHANGE:
                    for(int i=0;i<20;i++)
                    {
                        if((HWND)lParam==hwndEdit[i])
                        {
                            char a[200];
                            *((int *)a)=50;
                            int ln=SendMessage(hwndEdit[i],EM_GETLINE,0,(LPARAM)a);
                            a[ln]=0;
                            item *ti=global_list->findnext(i);
                            if(ti)
                            {
                                ti->setname(a);
                            }
                        }
                    }
                    ischanged=true;
                    break;
                //case EN_KILLFOCUS:
                    //MessageBoxA(hwnd,"CF","About",0);
                    //break;
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
    int winxx;
    int winyy;

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
            EndPaint(hwnd,&ps);
            break;
        case WM_SIZE:
            winxx=LOWORD(lParam);
            winyy=HIWORD(lParam);
            MoveWindow(hwndText0,0,0,winxx/2-2,winyy,1);
            MoveWindow(hwndText1,winxx/2+2,0,winxx/2-2,winyy,1);
            break;
        default:
            return DefWindowProc(hwnd,message,wParam,lParam);
    }

    return 0;
}
