/***************************************************
*                                                  *
*  Windows-Dialog                                  *
*                                                  *
*  ----------------------------------------------  *
*                                                  *
*  This file is part of TestMan!                   *
*  Copyright 2015 by Andreas Pollhammer            *
*                                                  *
***************************************************/
#include "dialog.h"

bool ischanged;

bool openconf(void)
{
    ShellExecute(hwnd,"open","testman.conf",NULL,NULL,5);
    return true;
}
bool savelist(HWND hwnd)
{
    int i;
    char *b;

    if(DOC_FILENAME==0 || DOC_FILENAME[0]==0)
    {
        savelistas(hwnd);
        return savelist(hwnd);
    }

    cut_item();

    char a[200];
    *((int *)a)=50;
    int ln=SendMessage(hwndCB,EM_GETLINE,0,(LPARAM)a);
    a[ln]=0;

    FILE *f=_wfopen(DOC_FILENAME,L"wt");
    if(f)
    {
        fwrite("TestMan-Vb01!\n",14,sizeof(char),f);
        fwrite("-------------\n",14,sizeof(char),f);
        fwrite("TITLE:",6,sizeof(char),f);
        fwrite(a,ln,sizeof(char),f);
        fwrite("\n",1,sizeof(char),f);
        fwrite("-------------\n",14,sizeof(char),f);
        for(i=0;i<MAXCOLS;i++)
        {
            fwrite("LABLE:",6,sizeof(char),f);
            fwrite(global_lablelist.gettext(i),strlen(global_lablelist.gettext(i)),sizeof(char),f);
            fwrite("\n",1,sizeof(char),f);
        }
        fwrite("COLID:",6,sizeof(char),f);
        i=global_lablelist.getid();
        b=(char *)c_datatostr_64(&i,sizeof(int));
        fwrite(b,strlen(b),sizeof(char),f);
        free(b);
        fwrite("\n",1,sizeof(char),f);
        fwrite("-------------\n",14,sizeof(char),f);
        global_list->write(f);
        fclose(f);

        ischanged=false;
    }
    else
    {
        MessageBoxA(hwnd,"Öffnen der Datei fehlgeschlagen!","Info",0);
    }

    return true;
}
bool loadlist(wchar_t *filename)
{
    int n,i=0;
    char line[2048];
    FILE *f=_wfopen(filename,L"rt");
    if(f)
    {
        global_lablelist.setid(0);
        //Erste Zeile:
        n=readline(line,2040,f);
        if(strcmp(line,"TestMan-Vb01!")==0)
        {
            free_item();
            ini_item();
            while(n!=0)
            {
                n=readline(line,2040,f);
                if(n!=0 && strcmpmin(line,"TITLE:")==0)
                {
                    SetWindowText(hwndCB,&line[6]);
                }
                if(n!=0 && strcmpmin(line,"LABLE:")==0)
                {
                    global_lablelist.setnexttext(&line[6]);
                }
                if(n!=0 && strcmpmin(line,"COLID:")==0)
                {
                    int *h=(int *)c_strtodata_64((unsigned char *)&line[6]);
                    grid->select(hwnd,0,0);
                    grid->select(hwnd,1,0);
                    grid->select(hwnd,*h,0);
                    free(h);
                }
                else if(n!=0 && strcmpmin(line,"ITEM:")==0)
                {
                    //SetWindowText(hwndEdit[i],&line[5]);
                    i++;
                    item *hhi=global_list->findnext(i-1);
                    if(hhi!=0)hhi->setname(&line[5]);
                }
                else if(n==98 && strcmpmin(line,"COLORS:")==0)
                {
                    COLORREF *c=(COLORREF *)c_strtodata_64((unsigned char *)&line[7]);
                    item *hi=global_list->findnext(i-1);
                    if(hi!=0)hi->setcolref(c);
                    free(c);
                }
                else if(n==31 && strcmpmin(line,"SYMBOLS:")==0)
                {
                    char *cs=(char *)c_strtodata_64((unsigned char *)&line[8]);
                    item *hi1=global_list->findnext(i-1);
                    if(hi1!=0)hi1->setsymbols(cs);
                    free(cs);
                }
                else if(n!=0 && strcmpmin(line,"RUN:")==0)
                {
                    item *hhi=global_list->findnext(i-1);
                    if(hhi!=0)hhi->setrun(&line[4]);
                }
                else if(n!=0 && strcmpmin(line,"OUT:")==0)
                {
                    item *hhi=global_list->findnext(i-1);
                    if(hhi!=0)hhi->setout(&line[4]);
                }
                else if(n!=0 && strcmpmin(line,"FILE:")==0)
                {
                    char *a=(char *)c_strtodata_64((unsigned char *)&line[5]);
                    item *hi1=global_list->findnext(i-1);
                    if(hi1!=0)hi1->setfile(a);
                    free(a);
                }
            }
            ischanged=false;
        }
        else
        {
            MessageBoxA(hwnd,"Falsches Dateiformat.\nErwartet TestMan-Vb01!","Info",0);
        }
        fclose(f);
    }
    else
    {
        MessageBoxA(hwnd,"Öffnen der Datei fehlgeschlagen!","Info",0);
    }

    global_scrolly=0;
    global_scrollymax=i;
    SCROLLINFO si;
    si.cbSize=sizeof(si);
    si.fMask=SIF_RANGE | SIF_PAGE | SIF_POS;
    si.nMin=0;
    si.nMax=global_scrollymax;
    si.nPage=global_scrollpagey;
    si.nPos=global_scrolly;
    SetScrollInfo(hwndscr,SB_CTL,&si,TRUE);

    fillall();

    return true;
}
