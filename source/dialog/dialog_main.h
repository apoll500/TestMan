/***************************************************
*                                                  *
*  Some dialogs.                                   *
*                                                  *
***************************************************/
#ifndef DIALOG_MAIN_H
#define DIALOG_MAIN_H

#include <windows.h>
#include "../dialog.h"
#include "alerts.h"

void main_open(void);
void main_reset(void);
void main_save(HWND hwnd);
void main_saveas(HWND hwnd);

#endif
