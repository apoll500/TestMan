/***************************************************
*                                                  *
*  Some functions supporting the creation          *
*  and manipulation of menus and menu entrys.      *
*                                                  *
***************************************************/
#ifndef WINTOOLBOX_GRID_INTER_H
#define WINTOOLBOX_GRID_INTER_H

#include <windows.h>

typedef void (*Selectbox_func)(int,int);

class GridHelper_Interface
{
public:
    virtual ~GridHelper_Interface(){};
    virtual void setfunction_selectbox(Selectbox_func func)=0;
    virtual void paint(HDC hdc)=0;
    virtual void mousemove(HWND hwnd,int mx,int my)=0;
    virtual void lbuttondown(HWND hwnd,int mx,int my)=0;
    virtual void lbuttonup(HWND hwnd,int mx,int my)=0;
    virtual void rbuttondown(HWND hwnd,int mx,int my)=0;
    virtual void select(HWND hwnd,int boxx,int boxy)=0;
    virtual void setcolor(HWND hwnd,int col,int row,COLORREF color)=0;
    virtual void seteditmode(bool mode)=0;
    virtual bool geteditmode()=0;
};

#endif
