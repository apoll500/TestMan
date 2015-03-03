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
#ifndef WINTOOLBOX_MENUHELPER_H
#define WINTOOLBOX_MENUHELPER_H

#define MENUHELPER_EXPSTEP 25

#include <windows.h>
#include "menu_interface.h"

class MenuHelper_Item
{
public:
    HMENU menu_item;
    HMENU menu_parent;
};
class MenuHelper:public MenuHelper_Interface
{
private:
    HMENU toplevelmenu;
    MenuHelper_Item *item;
    int item_maxln;
    int item_count;
public:
    MenuHelper(int ln);
    MenuHelper();
    ~MenuHelper();
    virtual int createNewMenuTitle(const char *title);
    virtual int createNewMenuSubTitle(int parent,const char *title);
    virtual void createNewMenuPoint(int parent,int action_id,const char *title);
    virtual void select(HWND hwnd);
private:
    void setupfirst();
    void checkmem();
    void createNewMenu();
};

#endif

