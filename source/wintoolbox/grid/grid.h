/***************************************************
*                                                  *
*                                                  *
*                                                  *
*  ----------------------------------------------  *
*                                                  *
*  This file is part of TestMan!                   *
*  Copyright 2015 by Andreas Pollhammer            *
*                                                  *
***************************************************/
#ifndef WINTOOLBOX_GRIDHELPER_H
#define WINTOOLBOX_GRIDHELPER_H

#include <windows.h>
#include "grid_interface.h"
#include "../colorselect/colorselect.h"

#define MARK_R 1
#define MARK_L 2

class GridHelper_Box
{
public:
    char status;
    unsigned char symbol;
    COLORREF color;
    void chsymbol()
    {
        chsymbol(0);
    }
    void chsymbol(int flag)
    {
        if((symbol>>flag)%2==0)symbol+=1<<flag;
        else symbol-=1<<flag;
    }
    char getsymbol(int id)
    {
        return symbol;
    }
    void setcolor(COLORREF c)
    {
        color=c;
    }

};
class GridHelper:public GridHelper_Interface
{
private:
    int posX,posY;
    int box_xx,box_yy;
    int x_boxes,y_boxes;
    int currentcol,currentrow;
    int scrollx,scrolly;
    GridHelper_Box *box;
    bool lmb_status;
    int mark_status;
    bool ischanged;
    ColorSelector colorselect;
    bool colselect;//allow selecting of columns
    bool drawseltab;//draw tab for selected column
    bool grideditmode;//allow setting of symbols and marks in the grid
    Selectbox_func selectbox;
public:
    GridHelper();
    GridHelper(int px,int py,int xx,int yy,int xc,int yc);
    ~GridHelper();
    virtual void setfunction_selectbox(Selectbox_func func);
    virtual void paint(HDC hdc);
    virtual void mousemove(HWND hwnd,int mx,int my);
    virtual void lbuttondown(HWND hwnd,int mx,int my);
    virtual void lbuttonup(HWND hwnd,int mx,int my);
    virtual void rbuttondown(HWND hwnd,int mx,int my);
    virtual void select(HWND hwnd,int boxx,int boxy);
    virtual void setcolor(HWND hwnd,int col,int row,COLORREF color);
    virtual void seteditmode(bool mode);
    virtual bool geteditmode();
private:
    void setupfirst(int px,int py,int xx,int yy,int xc,int yc);
    RECT getrect(int col,int row);
    RECT getrect_col(int col);
    int getrow(int y);
    int getcol(int x);
    void print_rightbar(HDC hdc,int x,int y);
    void print_leftbar(HDC hdc,int x,int y);
    void print_rect(HDC hdc,int x,int y,int xx, int yy,unsigned char r,unsigned char g,unsigned char b);
    void printmark(HDC hdc,int x,int y,float breite,float hoehe,float border,unsigned char r,unsigned char g,unsigned char b);
    void drawpoly(HDC hdc,LPPOINT p,int n,unsigned char r0,unsigned char g0,unsigned char b0,int rb,int rs,unsigned char r1,unsigned char g1,unsigned char b1,int fs);
    void select_box(HWND hwnd,int mx,int my);
    bool isingrid(int x,int y);
};

#endif

