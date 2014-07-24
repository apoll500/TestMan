#ifndef COLORSELECT_H
#define COLORSELECT_H

#include <windows.h>

class ColorSelector
{
private:
    COLORREF lastcolor;
    COLORREF *customcolors;
public:
    ColorSelector();
    ~ColorSelector();
    virtual bool selectcolor();
    virtual int getcolor();
    virtual int getcolor_r();
    virtual int getcolor_g();
    virtual int getcolor_b();
};

#endif
