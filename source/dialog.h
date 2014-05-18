#ifndef DIALOG_H
#define DIALOG_H

#include <windows.h>
#include "stringhelp.h"
#include "filehelp.h"
#include "item.h"
#include "windraw.h"

//enthält das aktuelle Verzeichnis
extern wchar_t *EWIN_TXT_CDIR;
extern wchar_t *DOC_FILENAME;
extern bool ischanged;
extern char *PROG1;
extern char *PROG2;
extern char *PROG3;
extern char *EXTE1;
extern char *EXTE2;
extern char *EXTE3;
extern char *OUTP1;
extern char *OUTP2;
extern char *OUTP3;

bool ini_dialog(void);
bool free_dialog(void);
void free_filename(void);
bool openconf(void);
bool openlist(HWND);
bool savelistas(HWND);
bool savelist(HWND);
void ini_progdir(void);
bool setcolor(int,int,HWND);
int readline(char *,int,FILE *);
bool loadlist(wchar_t *);
int strcmpmin(const char *,const char *);
bool loadconf(void);

#endif
