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
#ifndef WTB_FILE_DIALOG_GLOBAL_FILE_H
#define WTB_FILE_DIALOG_GLOBAL_FILE_H

#include <stdlib.h>

#define WTB_FILE_FILTER_TDL     L"TestMan-Configurations (*.tdl)\0*.tdl\0All files (*.*)\0*.*\0"
#define WTB_FILE_TEXT_STD_OPEN  L"Select input data file."
#define WTB_FILE_TEXT_STD_SAVE  L"Select output data file."

extern wchar_t *DOC_FILENAME;

bool ini_dialog(void);
bool free_dialog(void);
void free_filename(void);

#endif
