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
#ifndef WINDRAW_H
#define WINDRAW_H

#include <windows.h>
#include "mod/item.h"
#include "wintoolbox/grid/grid.h"

void ini_windraw(void);
void paint(HDC);
void fillall(void);

extern int global_scrolly;
extern int global_scrolly_out;
extern int global_selline;
extern int global_scrollymax;
extern int global_scrollpagey;

extern HWND hwnd,hwndscr,hwndOut,hwndButton[10],hwndEdit[20],hwndCB,hwndLE,hwndRunButton[20];
extern HWND hwndText0,hwndText1,hwndOEd00,hwndOEd01,hwndOBu00,hwndOBu01,hwndOBu02,hwndOBu03;
extern GridHelper_Interface *grid;

#endif
