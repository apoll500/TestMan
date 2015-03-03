#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "../windraw.h"
#include "../wintoolbox/pipes.h"
#include "lable.h"

#define INITIAL_STRING_LENGTH 32
#define MAXCOLS 17

void runalltests(void);
void resetalltests(void);

void ini_item(void);
void free_item(void);
void cut_item(void);
unsigned char trc_64(unsigned char);
unsigned char trc_64u(unsigned char);
unsigned char *c_datatostr_64(void *,long);
void *c_strtodata_64(unsigned char *);

class item
{
private:
    char flag[MAXCOLS];
    COLORREF color[MAXCOLS];
    unsigned char symbol[MAXCOLS];
    //char status[MAXCOLS];

    char *name;//Bezeichnung des Tests
    char *tag;//nicht verwendet
    int nameln,tagln;

    item *nextitem;

    char *run;//commandline for test execution
    char *out;//target oft the test output (a filename or stdout)
    char *file;//filename of the file containig the valid output
    int runln,outln,fileln;

public:
    //LADEN
    void setcolref(COLORREF *c)
    {
        int i=0;
        for(i=0;i<MAXCOLS;i++)
        {
            color[i]=c[i];
        }
    }
    void setsymbols(char *s)
    {
        int i=0;
        for(i=0;i<MAXCOLS;i++)
        {
            symbol[i]=s[i];
        }
    }
    //Konstruktor
    item()
    {
        int i;

        nameln=INITIAL_STRING_LENGTH;
        name=(char *)malloc((nameln+1)*sizeof(char));
        name[0]=0;

        runln=INITIAL_STRING_LENGTH;
        run=(char *)malloc((nameln+1)*sizeof(char));
        run[0]=0;

        outln=INITIAL_STRING_LENGTH;
        out=(char *)malloc((nameln+1)*sizeof(char));
        out[0]=0;

        fileln=INITIAL_STRING_LENGTH;
        file=(char *)malloc((nameln+1)*sizeof(char));
        file[0]=0;

        //strcpy(name,"(undefined)");
        tagln=INITIAL_STRING_LENGTH;
        tag=(char *)malloc((tagln+1)*sizeof(char));
        for(i=0;i<MAXCOLS;i++)
        {
            color[i]=RGB(255,255,255);
            symbol[i]=0;
        }
        nextitem=0;
    }
    ~item()
    {
        free(name);
        free(tag);
        free(run);
        free(out);
        free(file);
    }
    char *runtest();
    void setname(char *a)
    {
        nameln=strlen(a);
        name=(char *)realloc(name,(nameln+1)*sizeof(char));
        strcpy(name,a);
    }
    void setrun(char *a)
    {
        runln=strlen(a);
        run=(char *)realloc(run,(runln+1)*sizeof(char));
        strcpy(run,a);
    }
    void setout(char *a)
    {
        outln=strlen(a);
        out=(char *)realloc(out,(outln+1)*sizeof(char));
        strcpy(out,a);
    }
    void setfile(char *a)
    {
        fileln=strlen(a);
        file=(char *)realloc(file,(fileln+1)*sizeof(char));
        strcpy(file,a);
    }
    char *getname(void)
    {
        return name;
    }
    char *getrun(void)
    {
        return run;
    }
    char *getout(void)
    {
        return out;
    }
    char *getfile(void)
    {
        return file;
    }
    void chsymbol(int id)
    {
        chsymbol(id,0);
    }
    void chsymbol(int id,int flag)
    {
        if(id<0 || id>=MAXCOLS)return;
        //int p=pow(2,flag);
        if((symbol[id]>>flag)%2==0)symbol[id]+=1<<flag;
        else symbol[id]-=1<<flag;
    }
    char getsymbol(int id)
    {
        if(id<0 || id>=MAXCOLS)return 0;
        return symbol[id];
    }
    void setcolor(int id,COLORREF c)
    {
        if(id<0 || id>=MAXCOLS)return;
        color[id]=c;
    }
    void setcolor(COLORREF c);
    COLORREF getcolor(int id)
    {
        if(id<0 || id>=MAXCOLS)return RGB(255,255,255);
        return color[id];
    }
    void settag(char *a)
    {
        tag=(char *)realloc(tag,(strlen(a)+1)*sizeof(char));
        strcpy(tag,a);
    }
    void setnextitem(item *i)
    {
        if(i==0)
        {
            cutright();
            return;
        }
        if(nextitem==0)
        {
            nextitem=i;
        }
        else
        {
            item *next=nextitem;
            nextitem=i;
            i->setlastitem(next);
        }
    }
    void cutright(void)
    {
        item *n,*c=this->findnext();
        while(c!=0)
        {
            n=c->findnext();
            delete c;
            c=n;
        }
        this->nextitem=0;
    }
    void setlastitem(item *i)
    {
        item *last=findlast();
        last->setnextitem(i);
    }
    item *findlast()
    {
        if(nextitem==0)
            return this;
        return findlast();
    }
    item *findnext()
    {
        return nextitem;
    }
    item *findnext(int n)
    {
        if(n>1)
        {
            n--;
            if(nextitem==0)
            {
                addnew();
            }
            return nextitem->findnext(n);
        }
        else if(n==1)
        {
            if(nextitem==0)
            {
                addnew();
            }
            return nextitem;
        }
        return this;
    }
    void write(FILE *f)
    {
        char *a;
        //ITEM:
        fwrite("ITEM:",5,sizeof(char),f);
        fwrite(name,strlen(name),sizeof(char),f);
        fwrite("\n",1,sizeof(char),f);
        //RUN:
        if(run[0]!=0)
        {
            fwrite("RUN:",4,sizeof(char),f);
            fwrite(run,strlen(run),sizeof(char),f);
            fwrite("\n",1,sizeof(char),f);
        }
        //OUT:
        if(out[0]!=0)
        {
            fwrite("OUT:",4,sizeof(char),f);
            fwrite(out,strlen(out),sizeof(char),f);
            fwrite("\n",1,sizeof(char),f);
        }
        //FILE:
        if(file[0]!=0)
        {
            a=(char *)c_datatostr_64(file,strlen(file)+1);
            fwrite("FILE:",5,sizeof(char),f);
            fwrite(a,strlen(a),sizeof(char),f);
            fwrite("\n",1,sizeof(char),f);
            free(a);
        }
        //COLORS:
        a=(char *)c_datatostr_64(color,MAXCOLS*sizeof(COLORREF));
        if(strcmp(a,"zzzz+wzzz1kzzzD+zzzz+wzzz1kzzzD+zzzz+wzzz1kzzzD+zzzz+wzzz1kzzzD+zzzz+wzzz1kzzzD+zzzz+wzzz1+")!=0)
        {
            fwrite("COLORS:",7,sizeof(char),f);
            fwrite(a,strlen(a),sizeof(char),f);
            fwrite("\n",1,sizeof(char),f);
        }
        free(a);
        //SYMBOLS:
        a=(char *)c_datatostr_64(symbol,MAXCOLS*sizeof(char));
        if(strcmp(a,"+++++++++++++++++++++++")!=0)
        {
            fwrite("SYMBOLS:",8,sizeof(char),f);
            fwrite(a,strlen(a),sizeof(char),f);
            fwrite("\n",1,sizeof(char),f);
        }
        free(a);
        //das nächste Item ausgeben:
        if(nextitem!=0)
        {
            fwrite("-------------\n",14,sizeof(char),f);
            nextitem->write(f);
        }
    }
    item *addnew()
    {
        item *newitem=new item();
        setlastitem(newitem);
        return newitem;
    }
};

extern item *global_list;

#endif
