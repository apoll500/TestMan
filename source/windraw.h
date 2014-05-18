#ifndef WINDRAW_H
#define WINDRAW_H

#include <windows.h>
#include "item.h"

#define RASTER_X 20
#define RASTER_Y 20

#define MARK_R 1
#define MARK_L 2

#define BUFSIZE 4096

void ini_windraw(void);
int getrow(int);
int getcol(int);
RECT getrect2(int,int);
RECT getrect(int,int);
void paint(HDC);
void fillall(void);
int boxx(int x);
int boxy(int y);

void ncpaint_out(HDC hdc);

extern int global_currentcol;
extern int global_currentrow;
extern int global_scrolly;
extern int global_mark_status;
extern HWND hwnd,hwndOut,hwndButton[10],hwndEdit[20],hwndCB,hwndRunButton[20],hwndText0,hwndText1;

#endif
