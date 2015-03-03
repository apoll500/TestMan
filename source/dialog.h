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
#ifndef DIALOG_H
#define DIALOG_H

#include <windows.h>
#include "lib/stringhelp.h"
#include "lib/filehelp.h"
#include "mod/item.h"
#include "windraw.h"
#include "mod/lable.h"

#include "wintoolbox/file_dialog/global_file.h"
#include "wintoolbox/progdir/progdir.h"
#include "wintoolbox/file_dialog/savefile/savefile.h"

extern bool ischanged;

bool openconf(void);
bool savelist(HWND);
bool loadlist(wchar_t *);

#endif
