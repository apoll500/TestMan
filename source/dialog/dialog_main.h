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
#ifndef DIALOG_MAIN_H
#define DIALOG_MAIN_H

#include <windows.h>
#include "../dialog.h"
#include "../wintoolbox/file_dialog/openfile/openfile.h"
#include "alerts.h"

void main_open(void);
void main_reset(void);
void main_save(HWND hwnd);
void main_saveas(HWND hwnd);

#endif
