#ifndef FILEHELP_H
#define FILEHELP_H

#include <stdio.h>
#include <wchar.h>

#define DIRSEPERATOR "\\"
#define WDIRSEPERATOR L"\\"
#define DIRSEPERATOR2 "/"
#define WDIRSEPERATOR2 L"/"
#define LABLESEPERATOR ":"
#define WLABLESEPERATOR L":"

int c_pathtype(wchar_t *);
int readline(char *,int,FILE *);

#endif
