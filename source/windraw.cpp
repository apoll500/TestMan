/***************************************************
*                                                  *
*  Windows-spezifische Hilfsfunktionen.            *
*                                                  *
*  ----------------------------------------------  *
*                                                  *
*  This file is part of TestMan!                   *
*  Copyright 2015 by Andreas Pollhammer            *
*                                                  *
***************************************************/
#include "windraw.h"

int global_scrolly;
int global_scrolly_out;
int global_selline;
int global_scrollymax;
int global_scrollpagey;

HWND hwnd,hwndscr,hwndOut,hwndButton[10],hwndEdit[20],hwndCB,hwndLE,hwndRunButton[20];
HWND hwndText0,hwndText1,hwndOEd00,hwndOEd01,hwndOBu00,hwndOBu01,hwndOBu02,hwndOBu03;

GridHelper_Interface *grid;

void ini_windraw(void)
{
    global_scrolly=0;
    global_scrollymax=19;
    global_scrollpagey=20;
}
void paint(HDC hdc)
{
	HBRUSH hbr;
	HANDLE oldhbr;
	HPEN hpe;
	HANDLE oldhpe;

    hbr=CreateSolidBrush(RGB(255,0,0));
    oldhbr=SelectObject(hdc,hbr);
    hpe=CreatePen(0,1,RGB(255,0,0));
    oldhpe=SelectObject(hdc,hpe);
    Rectangle(hdc,260-1,8-2,260-1+339+4,8-2+24+4);
    SelectObject(hdc,oldhbr);
    DeleteObject(hbr);
    SelectObject(hdc,oldhpe);
    DeleteObject(hpe);
}
void fillall(void)
{
    item *t=global_list->findnext(global_scrolly);
    int i=0,j;
    while(t!=0 && i<20)
    {
        SendMessageA(hwndEdit[i],WM_SETTEXT,0,(LPARAM)(t->getname()));
        for(j=0;j<17;j++)
        {
            grid->setcolor(hwnd,j,i,t->getcolor(j));
        }
        t=t->findnext();
        i++;
    }
    while(i<20)
    {
        SendMessageA(hwndEdit[i],WM_SETTEXT,0,(LPARAM)"");
        for(j=0;j<17;j++)
        {
            grid->setcolor(hwnd,j,i,RGB(255,255,255));
        }
        i++;
    }
}
