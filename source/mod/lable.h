#ifndef LABLE_H
#define LABLE_H

#include <windows.h>
#include "../lib/stringhelp.h"
#include "../windraw.h"

#define MAXLABLELENGTH 128
#define MAXCOLS 17

void selectbox(int,int);

class Lable
{
private:
    int id;
    char text[MAXCOLS][MAXLABLELENGTH+1];
public:
    Lable()
    {
        id=0;
    }
    void setid(int x)
    {
        if(x<0 || x>=MAXCOLS){id=0;return;}
        id=x;
    }
    int getid()
    {
        return id;
    }
    void reset()
    {
        int i;
        for(i=0;i<MAXCOLS;i++)
        {
            text[i][0]=0;
        }
    }
    void settext(int id,char *a)
    {
        if(id<0 || id>=MAXCOLS)return;
        strcpyn(text[id],a,MAXLABLELENGTH);
    }
    void settext(char *a)
    {
        strcpyn(text[id],a,MAXLABLELENGTH);
    }
    void setnexttext(char *a)
    {
        if(id<0 || id>=MAXCOLS){id=0;return;}
        strcpyn(text[id],a,MAXLABLELENGTH);
        id++;
        if(id<0 || id>=MAXCOLS){id=0;return;}
    }
    char *gettext(int id)
    {
        if(id<0 || id>=MAXCOLS)return (char *)"";
        return text[id];
    }
};

extern Lable global_lablelist;

#endif
