#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <windows.h>
#include <math.h>

#define INITIAL_STRING_LENGTH 32
#define MAXCOLS 17

void ini_item(void);
void free_item(void);
unsigned char trc_64(unsigned char);
unsigned char trc_64u(unsigned char);
unsigned char *c_datatostr_64(void *,long);
void *c_strtodata_64(unsigned char *);

class item
{
private:
    char *name;
    char flag[MAXCOLS];
    COLORREF color[MAXCOLS];
    unsigned char symbol[MAXCOLS];
    char status[MAXCOLS];
    char *tag;
    int nameln,tagln;
    item *nextitem;
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
    }
    //
    void setname(char *a)
    {
        nameln=strlen(a);
        name=(char *)realloc(name,(nameln+1)*sizeof(char));
        strcpy(name,a);
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
    COLORREF getcolor(int id)
    {
        if(id<0 || id>=MAXCOLS)return RGB(255,255,255);
        return color[id];
    }
    char *getname()
    {
        return name;
    }
    void settag(char *a)
    {
        tag=(char *)realloc(tag,(strlen(a)+1)*sizeof(char));
        strcpy(tag,a);
    }
    void setnextitem(item *i)
    {
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
            if(nextitem!=0)
                return nextitem->findnext(n);
            return 0;
        }
        else if(n==1)
        {
            return nextitem;
        }
        return this;
    }
    void write(FILE *f)
    {
        //ITEM:
        fwrite("ITEM:",5,sizeof(char),f);
        fwrite(name,strlen(name),sizeof(char),f);
        fwrite("\n",1,sizeof(char),f);
        //COLORS:
        fwrite("COLORS:",7,sizeof(char),f);
        unsigned char *a=c_datatostr_64(color,MAXCOLS*sizeof(COLORREF));
        fwrite(a,strlen((char *)a),sizeof(unsigned char),f);
        free(a);
        fwrite("\n",1,sizeof(char),f);
        //SYMBOLS:
        fwrite("SYMBOLS:",8,sizeof(char),f);
        a=c_datatostr_64(symbol,MAXCOLS*sizeof(char));
        fwrite(a,strlen((char *)a),sizeof(unsigned char),f);
        free(a);
        fwrite("\n",1,sizeof(char),f);
        //das nächste Item ausgeben:
        if(nextitem!=0)
        {
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
