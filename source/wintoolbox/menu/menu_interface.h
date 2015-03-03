/***************************************************
*                                                  *
*  Some functions supporting the creation          *
*  and manipulation of menus and menu entrys.      *
*                                                  *
*  ----------------------------------------------  *
*                                                  *
*  This file is part of TestMan!                   *
*  Copyright 2015 by Andreas Pollhammer            *
*                                                  *
***************************************************/
#ifndef WINTOOLBOX_MENU_INTER_H
#define WINTOOLBOX_MENU_INTER_H

#include <windows.h>

class MenuHelper_Interface
{
public:
    virtual ~MenuHelper_Interface(){};
    virtual int createNewMenuTitle(const char *title)=0;
    virtual int createNewMenuSubTitle(int parent,const char *title)=0;
    virtual void createNewMenuPoint(int parent,int action_id,const char *title)=0;
    virtual void select(HWND hwnd)=0;
};

#endif
