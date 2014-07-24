#ifndef DIALOG_H
#define DIALOG_H

#include <windows.h>
#include "lib/stringhelp.h"
#include "lib/filehelp.h"
#include "mod/item.h"
#include "windraw.h"
#include "mod/lable.h"

extern wchar_t *EWIN_TXT_CDIR;
extern wchar_t *DOC_FILENAME;
extern bool ischanged;

bool ini_dialog(void);
bool free_dialog(void);
void free_filename(void);
bool openconf(void);
bool openlist(HWND);
bool savelistas(HWND);
bool savelist(HWND);
bool loadlist(wchar_t *);
void ini_progdir(void);

#endif
