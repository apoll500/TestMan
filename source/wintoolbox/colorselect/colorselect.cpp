/***************************************************
*                                                  *
*  Color-Selector.                                 *
*                                                  *
***************************************************/
#include "colorselect.h"

ColorSelector::ColorSelector()
{
    int i;
    customcolors=(COLORREF *)malloc(16*sizeof(COLORREF));
    for(i=0;i<16;i++)customcolors[i]=RGB(255,255,255);
    lastcolor=RGB(255,255,255);
}
ColorSelector::~ColorSelector()
{
    free(customcolors);
}
bool ColorSelector::selectcolor()
{
    CHOOSECOLOR cc;
    memset(&cc,0,sizeof(cc));
    cc.lStructSize=sizeof(cc);
    cc.Flags=CC_ANYCOLOR|CC_RGBINIT;
    cc.lpCustColors=customcolors;
    cc.rgbResult=lastcolor;
    if(ChooseColorA(&cc))
    {
        if(lastcolor!=cc.rgbResult)
        {
            lastcolor=cc.rgbResult;
            return true;
        }

        /*
        item *todo=global_list->findnext(y-2+global_scrolly);
        if(todo)
        {
            todo->setcolor(x-13,lastcolor);
        }
        RECT r=getrect2(x,y);
        InvalidateRect(hwnd,&r,1);
        */
    }
    return false;
}
int ColorSelector::getcolor()
{
    return lastcolor;
}
int ColorSelector::getcolor_r()
{
    return lastcolor & 255;
}
int ColorSelector::getcolor_g()
{
    return lastcolor>>8 & 255;
}
int ColorSelector::getcolor_b()
{
    return lastcolor>>16 & 255;
}
