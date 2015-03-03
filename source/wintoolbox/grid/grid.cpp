/***************************************************
*                                                  *
*  Some functions supporting the creation          *
*  and manipulation of grid-objects.               *
*                                                  *
*  ----------------------------------------------  *
*                                                  *
*  This file is part of TestMan!                   *
*  Copyright 2015 by Andreas Pollhammer            *
*                                                  *
***************************************************/
#include "grid.h"

GridHelper::GridHelper()
{
    setupfirst(0,0,10,10,5,5);
}
GridHelper::GridHelper(int px,int py,int xx,int yy,int xc,int yc)
{
    setupfirst(px,py,xx,yy,xc,yc);
}
GridHelper::~GridHelper()
{
    free(box);
}
void GridHelper::setfunction_selectbox(Selectbox_func func)
{
    selectbox=func;
}
void GridHelper::paint(HDC hdc)
{
    int i,j;
	HBRUSH hbr;
	HANDLE oldhbr;
	HPEN hpe;
	HANDLE oldhpe;

    if(drawseltab)
    {
        hbr=CreateSolidBrush(RGB(255,255,255));
        oldhbr=SelectObject(hdc,hbr);
        hpe=CreatePen(1,2,RGB(255,0,0));
        oldhpe=SelectObject(hdc,hpe);
        Rectangle(hdc,posX+currentcol*box_xx,posY-20,posX+currentcol*box_xx+box_xx+2,posY+5);
        SelectObject(hdc,oldhbr);
        DeleteObject(hbr);
        SelectObject(hdc,oldhpe);
        DeleteObject(hpe);
    }

    for(j=0;j<y_boxes;j++)
    {
        for(i=0;i<x_boxes;i++)
        {
            hbr=CreateSolidBrush(box[i+j*x_boxes].color);
            oldhbr=SelectObject(hdc,hbr);

            Rectangle(hdc,
                      posX+i*box_xx,
                      posY+j*box_yy,
                      posX+i*box_xx+box_xx+1,
                      posY+j*box_yy+box_yy+1);
            SelectObject(hdc,oldhbr);
            DeleteObject(hbr);

            int s=box[i+j*x_boxes].symbol;
            if((s>>1)%2)
            {
                print_rightbar(hdc,i,j);
            }
            if((s>>2)%2)
            {
                print_leftbar(hdc,i,j);
            }
            if(s%2)
            {
                printmark(hdc,
                          posX+i*box_xx-2,
                          posY+j*box_yy-2,
                          box_xx+6,
                          box_yy+6,
                          9,255,255,255);
                printmark(hdc,
                          posX+i*box_xx+2,
                          posY+j*box_yy+2,
                          box_xx-3,
                          box_yy-3,
                          17,0,0,0);
            }
        }
    }

    //current column
    hpe=CreatePen(0,1,RGB(255,0,0));
    oldhpe=SelectObject(hdc,hpe);
    MoveToEx(hdc,posX+currentcol*box_xx,posY,0);
    LineTo(hdc,posX+currentcol*box_xx,posY+y_boxes*box_yy+1);
    MoveToEx(hdc,posX+currentcol*box_xx-1,posY,0);
    LineTo(hdc,posX+currentcol*box_xx-1,posY+y_boxes*box_yy+1);

    MoveToEx(hdc,posX+currentcol*box_xx+box_xx,posY,0);
    LineTo(hdc,posX+currentcol*box_xx+box_xx,posY+y_boxes*box_yy+1);
    MoveToEx(hdc,posX+currentcol*box_xx+box_xx+1,posY,0);
    LineTo(hdc,posX+currentcol*box_xx+box_xx+1,posY+y_boxes*box_yy+1);
    SelectObject(hdc,oldhpe);
    DeleteObject(hpe);

    if(grideditmode)
    {
        hpe=CreatePen(1,1,RGB(255,255,255));
        oldhpe=SelectObject(hdc,hpe);
        MoveToEx(hdc,posX+currentcol*box_xx+1,posY+currentrow*box_yy+box_yy-1,0);
        LineTo(hdc,posX+currentcol*box_xx+1,posY+currentrow*box_yy+1);
        LineTo(hdc,posX+currentcol*box_xx+box_xx-1,posY+currentrow*box_yy+1);
        LineTo(hdc,posX+currentcol*box_xx+box_xx-1,posY+currentrow*box_yy+box_yy-1);
        LineTo(hdc,posX+currentcol*box_xx+1,posY+currentrow*box_yy+box_yy-1);
        SelectObject(hdc,oldhpe);
        DeleteObject(hpe);

        MoveToEx(hdc,posX+currentcol*box_xx+2,posY+currentrow*box_yy+box_yy-2,0);
        LineTo(hdc,posX+currentcol*box_xx+2,posY+currentrow*box_yy+2);
        LineTo(hdc,posX+currentcol*box_xx+box_xx-2,posY+currentrow*box_yy+2);
        LineTo(hdc,posX+currentcol*box_xx+box_xx-2,posY+currentrow*box_yy+box_yy-2);
        LineTo(hdc,posX+currentcol*box_xx+2,posY+currentrow*box_yy+box_yy-2);

        hpe=CreatePen(1,1,RGB(255,255,255));
        oldhpe=SelectObject(hdc,hpe);
        MoveToEx(hdc,posX+currentcol*box_xx+3,posY+currentrow*box_yy+box_yy-3,0);
        LineTo(hdc,posX+currentcol*box_xx+3,posY+currentrow*box_yy+3);
        LineTo(hdc,posX+currentcol*box_xx+box_xx-3,posY+currentrow*box_yy+3);
        LineTo(hdc,posX+currentcol*box_xx+box_xx-3,posY+currentrow*box_yy+box_yy-3);
        LineTo(hdc,posX+currentcol*box_xx+3,posY+currentrow*box_yy+box_yy-3);
        SelectObject(hdc,oldhpe);
        DeleteObject(hpe);
    }

    if(mark_status==MARK_R)
    {
        print_rightbar(hdc,currentcol,currentrow);
    }
    else if(mark_status==MARK_L)
    {
        print_leftbar(hdc,currentcol,currentrow);
    }

}
void GridHelper::mousemove(HWND hwnd,int mx,int my)
{
    RECT r;
    if(!isingrid(mx,my) || !grideditmode)return;
    if(lmb_status)
    {
        if(currentcol==getcol(mx)-1 && currentrow==getrow(my))
        {
            if(mark_status==0)
            {
                mark_status=MARK_R;
                r=getrect(currentcol,currentrow);
                InvalidateRect(hwnd,&r,1);
                ischanged=true;
            }
        }
        else if(currentcol==getcol(mx)+1 && currentrow==getrow(my))
        {
            if(mark_status==0)
            {
                mark_status=MARK_L;
                r=getrect(currentcol,currentrow);
                InvalidateRect(hwnd,&r,1);
                ischanged=true;
            }
        }
        else
        {
            if(mark_status==MARK_R)
            {
                mark_status=0;
                r=getrect(currentcol,currentrow);
                InvalidateRect(hwnd,&r,1);
                ischanged=true;
            }
            if(mark_status==MARK_L)
            {
                mark_status=0;
                r=getrect(currentcol,currentrow);
                InvalidateRect(hwnd,&r,1);
                ischanged=true;
            }
        }
    }
}
void GridHelper::lbuttondown(HWND hwnd,int mx,int my)
{
    if(!isingrid(mx,my))return;
    lmb_status=1;
    mark_status=0;
    select_box(hwnd,mx,my);
}
void GridHelper::lbuttonup(HWND hwnd,int mx,int my)
{
    RECT r;
    lmb_status=0;
    if(!isingrid(mx,my))return;
    if(currentcol==getcol(mx) && currentrow==getrow(my))
    {
        //item *ki=list->findnext(boxy(currentrow));
        //if(ki)ki->chsymbol(boxx(currentcol));
        if(grideditmode)box[currentcol+currentrow*x_boxes].chsymbol();
        r=getrect(currentcol,currentrow);
        InvalidateRect(hwnd,&r,1);
        ischanged=true;
    }
    if(mark_status==MARK_R && grideditmode)
    {
        //item *ki=list->findnext(boxy(currentrow));
        //if(ki)ki->chsymbol(boxx(currentcol),1);
        box[currentcol+currentrow*x_boxes].chsymbol(1);
        r=getrect(currentcol,currentrow);
        InvalidateRect(hwnd,&r,1);
        ischanged=true;
    }
    else if(mark_status==MARK_L && grideditmode)
    {
        //item *ki=list->findnext(boxy(currentrow));
        //if(ki)ki->chsymbol(boxx(currentcol),2);
        box[currentcol+currentrow*x_boxes].chsymbol(2);
        r=getrect(currentcol,currentrow);
        InvalidateRect(hwnd,&r,1);
        ischanged=true;
    }
    mark_status=0;
}
void GridHelper::rbuttondown(HWND hwnd,int mx,int my)
{
    if(!isingrid(mx,my) || !grideditmode)return;
    select_box(hwnd,mx,my);
    colorselect.selectcolor();
    box[currentcol+currentrow*x_boxes].color=colorselect.getcolor();
        /*
        item *todo=global_list->findnext(y-2+global_scrolly);
        if(todo)
        {
            todo->setcolor(x-13,lastcolor);
        }
        */
    RECT r=getrect(currentcol,currentrow);
    InvalidateRect(hwnd,&r,1);
}
void GridHelper::select(HWND hwnd,int boxx,int boxy)
{
    select_box(hwnd,posX+boxx*box_xx+box_xx/2,posY+boxy*box_yy+box_yy/2);
}
void GridHelper::setcolor(HWND hwnd,int col,int row,COLORREF color)
{
    box[col+row*x_boxes].setcolor(color);
    RECT r=getrect(col,row);
    InvalidateRect(hwnd,&r,1);
}
void GridHelper::seteditmode(bool mode)
{
    grideditmode=mode;
}
bool GridHelper::geteditmode()
{
    return grideditmode;
}
void GridHelper::setupfirst(int px,int py,int xx,int yy,int xc,int yc)
{
    posX=px;
    posY=py;
    box_xx=xx;
    box_yy=yy;
    x_boxes=xc;
    y_boxes=yc;
    currentcol=0;
    currentrow=0;
    scrollx=0;
    scrolly=0;
    mark_status=0;
    box=(GridHelper_Box *)malloc(x_boxes*y_boxes*sizeof(GridHelper_Box));
    int i;
    for(i=0;i<x_boxes*y_boxes;i++)
    {
        box[i].status=0;
        box[i].symbol=0;
        box[i].color=RGB(255,255,255);
    }
    lmb_status=false;
    ischanged=false;
    colselect=true;
    drawseltab=true;
    grideditmode=false;
    selectbox=0;
}
RECT GridHelper::getrect(int col,int row)
{
    RECT r;
    r.left=posX+col*box_xx;
    r.top=posY+row*box_yy;
    r.right=r.left+box_xx;
    r.bottom=r.top+box_yy;
    return r;
}
RECT GridHelper::getrect_col(int col)
{
    RECT r;
    r.left=posX+col*box_xx-1;
    r.top=posY-10;
    r.right=r.left+box_xx+3;
    r.bottom=r.top+box_yy*y_boxes+10;
    return r;
}
int GridHelper::getrow(int y)
{
    return (y-posY)/box_yy;
}
int GridHelper::getcol(int x)
{
    return (x-posX)/box_xx;
}
void GridHelper::print_rightbar(HDC hdc,int x,int y)
{
    print_rect(hdc,
               posX+(x+0.75)*box_xx-1,
               posY+(y)*box_yy+1,
               0.25*box_xx,
               box_yy-2,
               255,255,255);
    print_rect(hdc,
               posX+(x+0.75)*box_xx,
               posY+(y)*box_yy+2,
               0.25*box_xx-2,
               box_yy-4,
               0,0,0);
}
void GridHelper::print_leftbar(HDC hdc,int x,int y)
{
    print_rect(hdc,
               posX+(x)*box_xx+1,
               posY+(y)*box_yy+1,
               0.25*box_xx,
               box_yy-2,
               255,255,255);
    print_rect(hdc,
               posX+(x)*box_xx+2,
               posY+(y)*box_yy+2,
               0.25*box_xx-2,
               box_yy-4,
               0,0,0);
}
void GridHelper::print_rect(HDC hdc,int x,int y,int xx, int yy,unsigned char r,unsigned char g,unsigned char b)
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
    drawpoly(hdc,p,4,r,g,b,1,PS_SOLID,r,g,b,WINDING);
}
void GridHelper::printmark(HDC hdc,int x,int y,float breite,float hoehe,float border,unsigned char r,unsigned char g,unsigned char b)
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
        drawpoly(hdc,q,6,r,g,b,1,PS_SOLID,r,g,b,WINDING);

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
        drawpoly(hdc,q,6,r,g,b,1,PS_SOLID,r,g,b,WINDING);
}
void GridHelper::drawpoly(HDC hdc,LPPOINT p,int n,unsigned char r0,unsigned char g0,unsigned char b0,int rb,int rs,unsigned char r1,unsigned char g1,unsigned char b1,int fs)
{
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
}
void GridHelper::select_box(HWND hwnd,int mx,int my)
{
    RECT r;
    if(currentcol!=getcol(mx) && colselect)
    {
        r=getrect_col(currentcol);
        InvalidateRect(hwnd,&r,1);
        currentcol=getcol(mx);
        currentrow=getrow(my);
        r=getrect_col(currentcol);
        InvalidateRect(hwnd,&r,1);
        if(selectbox!=0)
        {
            selectbox(currentcol,currentrow);
        }
    }
    else if(grideditmode)
    {
        r=getrect(currentcol,currentrow);
        InvalidateRect(hwnd,&r,1);
        currentcol=getcol(mx);
        currentrow=getrow(my);
        r=getrect(currentcol,currentrow);
        InvalidateRect(hwnd,&r,1);
    }
}
bool GridHelper::isingrid(int x,int y)
{
    if(x>=posX && y>=posY && x<=posX+x_boxes*box_xx && y<=posY+y_boxes*box_yy)return true;
    return false;
}
