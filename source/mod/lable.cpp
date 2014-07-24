/***************************************************
*                                                  *
*  LABLES                                          *
*                                                  *
***************************************************/
#include "lable.h"

Lable global_lablelist;


void selectbox(int x,int y)
{
    global_lablelist.setid(x);
    SendMessageA(hwndLE,WM_SETTEXT,0,(LPARAM)(global_lablelist.gettext(x)));
    //ACHTUNG! SendMessageA macht offenbar ein peek! Daher vorher neue id setzen.
}
