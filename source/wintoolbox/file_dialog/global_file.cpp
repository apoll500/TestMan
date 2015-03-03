/***************************************************
*                                                  *
*  Common elements required for File-Dialogues.    *
*                                                  *
*  ----------------------------------------------  *
*                                                  *
*  This file is part of TestMan!                   *
*  Copyright 2015 by Andreas Pollhammer            *
*                                                  *
***************************************************/
#include "global_file.h"

//Name of the currently selected file.
wchar_t *DOC_FILENAME;

bool ini_dialog(void)
{
    DOC_FILENAME=0;
    return true;
}
void free_filename(void)
{
    if(DOC_FILENAME!=0)
    {
        free(DOC_FILENAME);
    }
    DOC_FILENAME=0;
}
bool free_dialog(void)
{
    free_filename();
    return true;
}
