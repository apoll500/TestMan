/***************************************************
*                                                  *
*  Some message boxes.                             *
*                                                  *
*  ----------------------------------------------  *
*                                                  *
*  This file is part of TestMan!                   *
*  Copyright 2015 by Andreas Pollhammer            *
*                                                  *
***************************************************/
#include "alerts.h"

int showAbout(HWND hwnd)
{
    return MessageBoxA(hwnd,"TestMan - Version b00.01_1\n\nCopyright 2014 by Andreas Pollhammer.\nSee README.TXT for further information.","About",0);
}
int showResetWarning(HWND hwnd)
{
    return MessageBoxA(hwnd,"Dies setzt alle Eingaben zurück.\nNicht gespeicherte Eingaben gehen verlohren.","HALLO",MB_OKCANCEL);
}
