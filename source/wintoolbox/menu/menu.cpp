/***************************************************
*                                                  *
*  Some functions supporting the creation          *
*  and manipulation of menus and menu entrys.      *
*                                                  *
***************************************************/

#include "menu.h"

MenuHelper::MenuHelper(int ln)
{
    item_maxln=max(1,ln);
    setupfirst();
}
MenuHelper::MenuHelper()
{
    item_maxln=MENUHELPER_EXPSTEP;
    setupfirst();
}
MenuHelper::~MenuHelper()
{
    free(item);
}
int MenuHelper::createNewMenuTitle(const char *title)
{
    checkmem();
    item[item_count].menu_item=CreatePopupMenu();
    item[item_count].menu_parent=toplevelmenu;
    AppendMenu(toplevelmenu,MF_STRING | MF_POPUP,(UINT)item[item_count].menu_item,title);
    item_count++;
    return item_count-1;
}
int MenuHelper::createNewMenuSubTitle(int parent,const char *title)
{
    checkmem();
    item[item_count].menu_item=CreatePopupMenu();
    item[item_count].menu_parent=item[parent].menu_item;
    AppendMenu(item[parent].menu_item,MF_STRING | MF_POPUP,(UINT)item[item_count].menu_item,title);
    item_count++;
    return item_count-1;
}
void MenuHelper::createNewMenuPoint(int parent,int action_id,const char *title)
{
    AppendMenu(item[parent].menu_item,MF_STRING,action_id,title);
}
void MenuHelper::select(HWND hwnd)
{
    SetMenu(hwnd,toplevelmenu);
}
void MenuHelper::setupfirst()
{
    item_count=0;
    item=(MenuHelper_Item *)malloc(item_maxln*sizeof(MenuHelper_Item));
    createNewMenu();
}
void MenuHelper::checkmem()
{
    if(item_count>=item_maxln)
    {
        item_maxln+=MENUHELPER_EXPSTEP;
        item=(MenuHelper_Item *)realloc(item,item_maxln*sizeof(MenuHelper_Item));
    }
}
void MenuHelper::createNewMenu()
{
    toplevelmenu=CreateMenu();
}
