/***************************************************
*                                                  *
*  Windows-spezifische Ein-/Ausgabe                *
*                                                  *
***************************************************/

#include "windraw.h"

int global_currentcol;
int global_currentrow;
int global_scrolly;
int global_mark_status;
HWND hwnd,hwndOut,hwndButton[10],hwndEdit[20],hwndCB,hwndRunButton[20],hwndText0,hwndText1;

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

void print_rect(int x,int y,int xx, int yy,unsigned char r,unsigned char g,unsigned char b)
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

void print_rightbar(int x,int y)
{
    print_rect((x+0.75)*RASTER_X-1,(y)*RASTER_Y+1,0.25*RASTER_X,RASTER_Y-2,255,255,255);
    print_rect((x+0.75)*RASTER_X,(y)*RASTER_Y+2,0.25*RASTER_X-2,RASTER_Y-4,0,0,0);
}

void print_leftbar(int x,int y)
{
    print_rect((x)*RASTER_X+1,(y)*RASTER_Y+1,0.25*RASTER_X,RASTER_Y-2,255,255,255);
    print_rect((x)*RASTER_X+2,(y)*RASTER_Y+2,0.25*RASTER_X-2,RASTER_Y-4,0,0,0);
}

void printmark(int x,int y,int border,int breite,int hoehe,unsigned char r,unsigned char g,unsigned char b)
{
    POINT p[16];
    POINT q[6];

        p[0].x=x+1+2*breite/border;
        p[0].y=y+1+2*hoehe/border;
        p[1].x=x+1+3*breite/border;
        p[1].y=p[0].y;
        p[2].x=x+breite/2;
        p[2].y=y+hoehe/2-hoehe/border;
        p[3].x=x+breite-2-3*breite/border;
        p[3].y=p[0].y;
        p[4].x=x+breite-2-2*breite/border;
        p[4].y=p[0].y;
        p[5].x=p[4].x;
        p[5].y=y+1+3*hoehe/border;
        p[6].x=x+breite/2+breite/border;
        p[6].y=y+hoehe/2;
        p[7].x=p[4].x;
        p[7].y=y+hoehe-2-3*hoehe/border;
        p[8].x=p[4].x;
        p[8].y=y+hoehe-2-2*hoehe/border;
        p[9].x=p[3].x;
        p[9].y=p[8].y;
        p[10].x=p[2].x;
        p[10].y=y+hoehe/2+hoehe/border;
        p[11].x=p[1].x;
        p[11].y=p[8].y;
        p[12].x=p[0].x;
        p[12].y=p[8].y;
        p[13].x=p[0].x;
        p[13].y=p[7].y;
        p[14].x=x+breite/2-breite/border;
        p[14].y=p[6].y;
        p[15].x=p[0].x;
        p[15].y=p[5].y;

        q[0].x=p[0].x;
        q[0].y=p[0].y;
        q[1].x=p[1].x;
        q[1].y=p[1].y;
        q[2].x=p[7].x;
        q[2].y=p[7].y;
        q[3].x=p[8].x;
        q[3].y=p[8].y;
        q[4].x=p[9].x;
        q[4].y=p[9].y;
        q[5].x=p[15].x;
        q[5].y=p[15].y;
        drawpoly(hwnd,q,6,r,g,b,1,PS_SOLID,r,g,b,WINDING);

        q[0].x=p[3].x;
        q[0].y=p[3].y;
        q[1].x=p[4].x;
        q[1].y=p[4].y;
        q[2].x=p[5].x;
        q[2].y=p[5].y;
        q[3].x=p[11].x;
        q[3].y=p[11].y;
        q[4].x=p[12].x;
        q[4].y=p[12].y;
        q[5].x=p[13].x;
        q[5].y=p[13].y;
        drawpoly(hwnd,q,6,r,g,b,1,PS_SOLID,r,g,b,WINDING);
}

void printmark2(int x,int y,int h,int border,int boxvalue,unsigned char r,unsigned char g,unsigned char b)
{
    POINT p[16];
    POINT q[6];

        p[0].x=x+1+2*h/border;
        p[0].y=y+1+2*h/border;
        p[1].x=x+1+3*h/border;
        p[1].y=p[0].y;
        p[2].x=x+h/2;
        p[2].y=y+h/2-h/border;
        p[3].x=x+h-1-3*h/border;
        p[3].y=p[0].y;
        p[4].x=x+h-1-2*h/border;
        p[4].y=p[0].y;
        p[5].x=p[4].x;
        p[5].y=y+1+3*h/border;
        p[6].x=x+h/2+h/border;
        p[6].y=y+h/2;
        p[7].x=p[4].x;
        p[7].y=y+h-1-3*h/border;
        p[8].x=p[4].x;
        p[8].y=y+h-1-2*h/border;
        p[9].x=p[3].x;
        p[9].y=p[8].y;
        p[10].x=p[2].x;
        p[10].y=y+h/2+h/border;
        p[11].x=p[1].x;
        p[11].y=p[8].y;
        p[12].x=p[0].x;
        p[12].y=p[8].y;
        p[13].x=p[0].x;
        p[13].y=p[7].y;
        p[14].x=x+h/2-h/border;
        p[14].y=p[6].y;
        p[15].x=p[0].x;
        p[15].y=p[5].y;

        q[0].x=p[0].x;
        q[0].y=p[0].y;
        q[1].x=p[1].x;
        q[1].y=p[1].y;
        q[2].x=p[7].x;
        q[2].y=p[7].y;
        q[3].x=p[8].x;
        q[3].y=p[8].y;
        q[4].x=p[9].x;
        q[4].y=p[9].y;
        q[5].x=p[15].x;
        q[5].y=p[15].y;
        drawpoly(hwnd,q,6,r*.6,g*.6,b*.6,1,PS_SOLID,r*.6,g*.6,b*.6,WINDING);

        q[0].x=p[3].x;
        q[0].y=p[3].y;
        q[1].x=p[4].x;
        q[1].y=p[4].y;
        q[2].x=p[5].x;
        q[2].y=p[5].y;
        q[3].x=p[11].x;
        q[3].y=p[11].y;
        q[4].x=p[12].x;
        q[4].y=p[12].y;
        q[5].x=p[13].x;
        q[5].y=p[13].y;
        drawpoly(hwnd,q,6,r*.6,g*.6,b*.6,1,PS_SOLID,r*.6,g*.6,b*.6,WINDING);
}

void print_symbol_clclose(int x,int y,int breite,int hoehe,unsigned char r,unsigned char g,unsigned char b)
{
    POINT p[16];
    p[0].x=x+breite/4;
    p[0].y=y+hoehe/4;
    p[1].x=x+3*breite/4;
    p[1].y=y+hoehe/4;
    p[2].x=x+3*breite/4;
    p[2].y=y+3*hoehe/4;
    p[3].x=x+breite/4;
    p[3].y=y+3*hoehe/4;
    drawpoly(hwnd,p,4,r*.6,g*.6,b*.6,1,PS_SOLID,r*.6,g*.6,b*.6,WINDING);
}

void ini_windraw(void)
{
    global_currentcol=-1;
    global_currentrow=-1;
    global_scrolly=0;
    global_mark_status=0;
}

int getrow(int y)
{
    return y/RASTER_Y;
}
int getcol(int x)
{
    return x/RASTER_X;
}
int boxx(int x)
{
    return x-13;
}
int boxy(int y)
{
    return y-2;
}

RECT getrect2(int x,int y)
{
    RECT r;
    r.left=x*RASTER_X;
    r.top=y*RASTER_Y;
    r.right=x*RASTER_X+RASTER_X;
    r.bottom=y*RASTER_Y+RASTER_Y;
    return r;
}
RECT getrect(int x,int y)
{
    x=getcol(x);
    y=getrow(y);
    return getrect2(x,y);
}
void paint(HDC hdc)
{
    int i,j;
    Rectangle(hdc,13*RASTER_X,1*RASTER_Y+5,26*RASTER_X+RASTER_X+1,1*RASTER_Y+RASTER_Y+1);
    TextOutA(hdc,261,26," A",2);
    TextOutA(hdc,262+RASTER_X,26,"B ",2);
    TextOutA(hdc,262+RASTER_X*2,26,"C ",2);
    TextOutA(hdc,262+RASTER_X*3,26,"  ",2);
    TextOutA(hdc,262+RASTER_X*4,26,"1 ",2);
    TextOutA(hdc,262+RASTER_X*5,26,"2 ",2);
    TextOutA(hdc,262+RASTER_X*6,26,"3 ",2);
    TextOutA(hdc,261+RASTER_X*7,26,"4 ",2);
    TextOutA(hdc,262+RASTER_X*8,26,"5 ",2);
    TextOutA(hdc,262+RASTER_X*9,26,"6 ",2);
    TextOutA(hdc,262+RASTER_X*10,26,"7 ",2);
    TextOutA(hdc,262+RASTER_X*11,26,"8 ",2);
    TextOutA(hdc,262+RASTER_X*12,26,"9 ",2);
    TextOutA(hdc,262+RASTER_X*13,26,"* ",2);
/*
	HBRUSH hbr;
	HANDLE oldhbr;
	HPEN hpen;
	HANDLE oldhpen;
	hbr=CreateSolidBrush(RGB(r0,g0,b0));
	oldhbr=SelectObject(hdc,hbr);
	hpen=CreatePen(rs,rb,RGB(r1,g1,b1));
	oldhpen=SelectObject(hdc,hpen);
	Rectangle(hdc,x,y,x+xx,y+yy);
	SelectObject(hdc,oldhbr);
	DeleteObject(hbr);
	SelectObject(hdc,oldhpen);
	DeleteObject(hpen);
*/
	HBRUSH hbr;
	HANDLE oldhbr;
	HPEN hpe;
	HANDLE oldhpe;

    //Farben
    item *todo=global_list->findnext(global_scrolly);
    j=0;
    while(todo!=0 && j<20)
    {
        for(i=0;i<17;i++)
        {
            hbr=CreateSolidBrush(todo->getcolor(i));
            oldhbr=SelectObject(hdc,hbr);
            Rectangle(hdc,(i+13)*RASTER_X,(j+2)*RASTER_Y,(i+13)*RASTER_X+RASTER_X+1,(j+2)*RASTER_Y+RASTER_Y+1);
            SelectObject(hdc,oldhbr);
            DeleteObject(hbr);

            int s=todo->getsymbol(i);
            if((s>>1)%2)
            {
                print_rightbar(i+13,j+2);
            }
            if((s>>2)%2)
            {
                print_leftbar(i+13,j+2);
            }
            if(s%2)
            {
                printmark((i+13)*RASTER_X,(j+2)*RASTER_Y,15,RASTER_X+1,RASTER_Y+1,255,255,255);
                printmark((i+13)*RASTER_X+1,(j+2)*RASTER_Y+1,15,RASTER_X-1,RASTER_Y-1,0,0,0);
            }
        }
        todo=todo->findnext();
        j++;
    }
    /*
    int j0=j+2;
    for(i=13;i<30;i++)
    {
        for(j=j0;j<22;j++)
        {
            Rectangle(hdc,i*RASTER_X,j*RASTER_Y,i*RASTER_X+RASTER_X+1,j*RASTER_Y+RASTER_Y+1);
        }
    }
    */
    //Rectangle(hdc,global_currentcol*RASTER_X+2,global_currentrow*RASTER_Y+2,global_currentcol*RASTER_X+RASTER_X-1,global_currentrow*RASTER_Y+RASTER_Y-1);

/*
    printmark(global_currentcol*RASTER_X,global_currentrow*RASTER_Y,
              15,
              RASTER_X+1,RASTER_Y+1,
              0,0,250);

    printmark(global_currentcol*RASTER_X+1,global_currentrow*RASTER_Y+1,
              15,
              RASTER_X-1,RASTER_Y-1,
              255,255,255);
*/

            hpe=CreatePen(1,1,RGB(255,255,255));
            oldhpe=SelectObject(hdc,hpe);
    MoveToEx(hdc,global_currentcol*RASTER_X+1,global_currentrow*RASTER_Y+RASTER_Y-1,0);
    LineTo(hdc,global_currentcol*RASTER_X+1,global_currentrow*RASTER_Y+1);
    LineTo(hdc,global_currentcol*RASTER_X+RASTER_X-1,global_currentrow*RASTER_Y+1);
    LineTo(hdc,global_currentcol*RASTER_X+RASTER_X-1,global_currentrow*RASTER_Y+RASTER_Y-1);
    LineTo(hdc,global_currentcol*RASTER_X+1,global_currentrow*RASTER_Y+RASTER_Y-1);
            SelectObject(hdc,oldhpe);
            DeleteObject(hpe);

    MoveToEx(hdc,global_currentcol*RASTER_X+2,global_currentrow*RASTER_Y+RASTER_Y-2,0);
    LineTo(hdc,global_currentcol*RASTER_X+2,global_currentrow*RASTER_Y+2);
    LineTo(hdc,global_currentcol*RASTER_X+RASTER_X-2,global_currentrow*RASTER_Y+2);
    LineTo(hdc,global_currentcol*RASTER_X+RASTER_X-2,global_currentrow*RASTER_Y+RASTER_Y-2);
    LineTo(hdc,global_currentcol*RASTER_X+2,global_currentrow*RASTER_Y+RASTER_Y-2);

            hpe=CreatePen(1,1,RGB(255,255,255));
            oldhpe=SelectObject(hdc,hpe);
    MoveToEx(hdc,global_currentcol*RASTER_X+3,global_currentrow*RASTER_Y+RASTER_Y-3,0);
    LineTo(hdc,global_currentcol*RASTER_X+3,global_currentrow*RASTER_Y+3);
    LineTo(hdc,global_currentcol*RASTER_X+RASTER_X-3,global_currentrow*RASTER_Y+3);
    LineTo(hdc,global_currentcol*RASTER_X+RASTER_X-3,global_currentrow*RASTER_Y+RASTER_Y-3);
    LineTo(hdc,global_currentcol*RASTER_X+3,global_currentrow*RASTER_Y+RASTER_Y-3);
            SelectObject(hdc,oldhpe);
            DeleteObject(hpe);

    if(global_mark_status==MARK_R)
    {
        print_rightbar(global_currentcol,global_currentrow);
    }
    else if(global_mark_status==MARK_L)
    {
        print_leftbar(global_currentcol,global_currentrow);
    }

    //print_symbol_clclose(10,10,50,50,100,100,200);
}
void fillall(void)
{
    //Formular ausfüllen
    item *todo=global_list->findnext(global_scrolly);
    int i=0;
    while(todo!=0 && i<20)
    {
        SendMessageA(hwndEdit[i],WM_SETTEXT,0,(LPARAM)(todo->getname()));
        todo=todo->findnext();
        i++;
    }
    //
    SendMessageA(hwndCB,WM_SETTEXT,0,(LPARAM)"");
}

void ncpaint_out(HDC hdc)
{
    Rectangle(hdc,2,2,200,200);
    TextOutA(hdc,50,10,"INPUT",5);
}
