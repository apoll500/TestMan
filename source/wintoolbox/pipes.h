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
#ifndef PIPES_H
#define PIPES_H

#include <stdio.h>
#include <windows.h>

#define BUFSIZE 4096

int xexecute(char *,char *);

PROCESS_INFORMATION CreateSubProcess(char *,HANDLE,HANDLE);
void CloseSubProcess(PROCESS_INFORMATION);
PROCESS_INFORMATION xCreateProcess(char *,int,int);
int xCreatePipe();
int xCloseAllPipes();
int xCloseHandle(int u);
int xClosePipeHandle(int u,int v);
char *xReadFromPipe(int u);
int xWriteToPipe(char *a,int u);

#endif
