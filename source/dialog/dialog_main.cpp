/***************************************************
*                                                  *
*  Some dialogs.                                   *
*                                                  *
*  ----------------------------------------------  *
*                                                  *
*  This file is part of TestMan!                   *
*  Copyright 2015 by Andreas Pollhammer            *
*                                                  *
***************************************************/
#include "dialog_main.h"

void main_open(void)
{
    if(!ischanged || IDOK==showResetWarning(hwnd))
    {
        openlist(hwnd);
        loadlist(DOC_FILENAME);
        SetWindowTextW(hwnd,DOC_FILENAME);
        InvalidateRect(hwnd,0,1);
    }
}
void main_reset(void)
{
    if(!ischanged || IDOK==showResetWarning(hwnd))
    {
        free_item();
        ini_item();
        free_filename();
        fillall();
        SetWindowTextW(hwnd,DOC_FILENAME);
        SendMessageA(hwndCB,WM_SETTEXT,0,(LPARAM)"");
        global_lablelist.reset();
        selectbox(0,0);
        grid->select(hwnd,0,0);
        ischanged=false;
        InvalidateRect(hwnd,0,1);
    }
}
void main_save(HWND hwnd)
{
    savelist(hwnd);
    SetWindowTextW(hwnd,DOC_FILENAME);
}
void main_saveas(HWND hwnd)
{
    savelistas(hwnd);
    savelist(hwnd);
    SetWindowTextW(hwnd,DOC_FILENAME);
}
