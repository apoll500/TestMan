/***************************************************
*                                                  *
*  Windows-spezifische Hilfsfunktionen             *
*                                                  *
***************************************************/
#include "windraw.h"

int global_scrolly;
int global_scrolly_out;
int global_selline;
int global_scrollymax;
int global_scrollpagey;

HWND hwnd,hwndscr,hwndOut,hwndButton[10],hwndEdit[20],hwndCB,hwndLE,hwndRunButton[20];
HWND hwndText0,hwndText1,hwndOEd00,hwndOEd01,hwndOBu00,hwndOBu01,hwndOBu02;

GridHelper_Interface *grid;

void drawpoly(HWND hwnd,LPPOINT p,int n,unsigned char r0,unsigned char g0,unsigned char b0,int rb,int rs,unsigned char r1,unsigned char g1,unsigned char b1,int fs)
{
    HDC hdc=GetDC(hwnd);
	HBRUSH hbr;
	HANDLE oldhbr;
	HPEN hpen;
	HANDLE oldhpen;
	hbr=CreateSolidBrush(RGB(r0,g0,b0));
	oldhbr=SelectObject(hdc,hbr);
	hpen=CreatePen(rs,rb,RGB(r1,g1,b1));
	oldhpen=SelectObject(hdc,hpen);
	SetPolyFillMode(hdc,fs);
	Polygon(hdc,p,n);
	SelectObject(hdc,oldhbr);
	DeleteObject(hbr);
	SelectObject(hdc,oldhpen);
	DeleteObject(hpen);
	ReleaseDC(hwnd,hdc);
}
void drawrect(int x,int y,int xx, int yy,unsigned char r,unsigned char g,unsigned char b)
{
    POINT p[4];
    p[0].x=x;
    p[0].y=y;
    p[1].x=x+xx;
    p[1].y=y;
    p[2].x=x+xx;
    p[2].y=y+yy;
    p[3].x=x;
    p[3].y=y+yy;
    drawpoly(hwnd,p,4,r,g,b,1,PS_SOLID,r,g,b,WINDING);
}
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
