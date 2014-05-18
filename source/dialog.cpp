/***************************************************
*                                                  *
*  Windows-Dialoge                                 *
*                                                  *
***************************************************/

#include "dialog.h"

wchar_t *EWIN_TXT_CDIR;
wchar_t *DOC_FILENAME;
COLORREF *COLOR_CUSTCOLS;
COLORREF COLOR_LASTCOL;

char *PROG1;
char *PROG2;
char *PROG3;
char *EXTE1;
char *EXTE2;
char *EXTE3;
char *OUTP1;
char *OUTP2;
char *OUTP3;

bool ischanged;

bool ini_dialog(void)
{
    int i;
    DOC_FILENAME=0;
    ini_progdir();
    loadconf();

    COLOR_CUSTCOLS=(COLORREF *)malloc(16*sizeof(COLORREF));
    for(i=0;i<16;i++)COLOR_CUSTCOLS[i]=RGB(255,255,255);
    COLOR_LASTCOL=RGB(255,255,255);

    return true;
}

void free_filename(void)
{
    if(DOC_FILENAME!=0)
    {
        free(DOC_FILENAME);
    }
    DOC_FILENAME=0;
}

bool free_dialog(void)
{
    free(COLOR_CUSTCOLS);
    free_filename();

    free(PROG1);
    free(PROG2);
    free(PROG3);
    free(EXTE1);
    free(EXTE2);
    free(EXTE3);
    free(OUTP1);
    free(OUTP2);
    free(OUTP3);

    return true;
}

bool openconf(void)
{
    ShellExecute(hwnd,"open","testman.conf",NULL,NULL,5);
    return true;
}

bool loadconf(void)
{

    PROG1=0;
    PROG2=0;
    PROG3=0;
    EXTE1=0;
    EXTE2=0;
    EXTE3=0;
    OUTP1=0;
    OUTP2=0;
    OUTP3=0;

    int n;
    char line[512];
    FILE *f=fopen("testman.conf","rt");
    if(f)
    {
        n=readline(line,511,f);
        while(n)
        {
            if(n!=0 && strcmpmin(line,"prog1=")==0)
            {
                PROG1=(char *)malloc((strlen(&line[6])+1)*sizeof(char));
                strcpy(PROG1,&line[6]);
            }
            else if(n!=0 && strcmpmin(line,"prog2=")==0)
            {
                PROG2=(char *)malloc((strlen(&line[6])+1)*sizeof(char));
                strcpy(PROG2,&line[6]);
            }
            else if(n!=0 && strcmpmin(line,"prog3=")==0)
            {
                PROG3=(char *)malloc((strlen(&line[6])+1)*sizeof(char));
                strcpy(PROG3,&line[6]);
            }
            else if(n!=0 && strcmpmin(line,"exte1=")==0)
            {
                EXTE1=(char *)malloc((strlen(&line[6])+1)*sizeof(char));
                strcpy(EXTE1,&line[6]);
            }
            else if(n!=0 && strcmpmin(line,"exte2=")==0)
            {
                EXTE2=(char *)malloc((strlen(&line[6])+1)*sizeof(char));
                strcpy(EXTE2,&line[6]);
            }
            else if(n!=0 && strcmpmin(line,"exte3=")==0)
            {
                EXTE3=(char *)malloc((strlen(&line[6])+1)*sizeof(char));
                strcpy(EXTE3,&line[6]);
            }
            else if(n!=0 && strcmpmin(line,"outp1=")==0)
            {
                OUTP1=(char *)malloc((strlen(&line[6])+1)*sizeof(char));
                strcpy(OUTP1,&line[6]);
            }
            else if(n!=0 && strcmpmin(line,"outp2=")==0)
            {
                OUTP2=(char *)malloc((strlen(&line[6])+1)*sizeof(char));
                strcpy(OUTP2,&line[6]);
            }
            else if(n!=0 && strcmpmin(line,"outp3=")==0)
            {
                OUTP3=(char *)malloc((strlen(&line[6])+1)*sizeof(char));
                strcpy(OUTP3,&line[6]);
            }
            n=readline(line,511,f);
        }
        fclose(f);
    }

    if(PROG1==0){PROG1=(char *)malloc(10);PROG1[0]=0;}
    if(PROG2==0){PROG2=(char *)malloc(10);PROG2[0]=0;}
    if(PROG3==0){PROG3=(char *)malloc(10);PROG3[0]=0;}
    if(EXTE1==0){EXTE1=(char *)malloc(10);EXTE1[0]=0;}
    if(EXTE2==0){EXTE2=(char *)malloc(10);EXTE2[0]=0;}
    if(EXTE3==0){EXTE3=(char *)malloc(10);EXTE3[0]=0;}
    if(OUTP1==0){OUTP1=(char *)malloc(10);OUTP1[0]=0;}
    if(OUTP2==0){OUTP2=(char *)malloc(10);OUTP2[0]=0;}
    if(OUTP3==0){OUTP3=(char *)malloc(10);OUTP3[0]=0;}

    return true;
}

bool setcolor(int x,int y,HWND hwnd)
{
    CHOOSECOLOR cc;
    memset(&cc,0,sizeof(cc));
    cc.lStructSize=sizeof(cc);
    cc.Flags=CC_ANYCOLOR|CC_RGBINIT;
    cc.lpCustColors=COLOR_CUSTCOLS;
    cc.rgbResult=COLOR_LASTCOL;
    if(ChooseColorA(&cc))
    {
        COLOR_LASTCOL=cc.rgbResult;
        item *todo=global_list->findnext(y-2+global_scrolly);
        if(todo)
        {
            todo->setcolor(x-13,COLOR_LASTCOL);
        }
        RECT r=getrect2(x,y);
        InvalidateRect(hwnd,&r,1);

        ischanged=true;
    }
    return true;
}

bool openlist(HWND hwnd)
{
    OPENFILENAMEW fn;

    memset( &fn, 0, sizeof( fn ) );
    fn.lStructSize     = sizeof( fn );
    fn.lpstrFilter     = L"TestMan-Configurations (*.tdl)\0*.tdl\0All files (*.*)\0*.*\0";
    fn.nMaxFile        = MAX_PATH;
    fn.nFilterIndex    = 0;
    fn.lpstrFileTitle  = NULL;
    fn.nMaxFileTitle   = 0;
    fn.lpstrInitialDir = EWIN_TXT_CDIR;
    fn.lpstrFile       = (wchar_t *)malloc((MAX_PATH+1)*sizeof(wchar_t));
    fn.lpstrFile[0]=0;
    fn.lpstrDefExt     = L"";
    fn.Flags           = OFN_EXPLORER | OFN_ENABLESIZING | OFN_HIDEREADONLY;
    fn.lpstrTitle      = L"Select input data file.";
    if(GetOpenFileNameW(&fn))
    {
        if(DOC_FILENAME==0)
        {
            DOC_FILENAME=(wchar_t *)malloc((wcslen(fn.lpstrFile)+1)*sizeof(wchar_t));
        }
        else
        {
            DOC_FILENAME=(wchar_t *)realloc(DOC_FILENAME,(wcslen(fn.lpstrFile)+1)*sizeof(wchar_t));
        }
        wcscpy(DOC_FILENAME,fn.lpstrFile);

        //Laden
        loadlist(DOC_FILENAME);
        return true;
    }
    return false;
}

bool savelistas(HWND hwnd)
{
    OPENFILENAMEW fn;

    memset( &fn, 0, sizeof( fn ) );
    fn.lStructSize     = sizeof( fn );
    fn.lpstrFilter     = L"TestMan-Configurations (*.tdl)\0*.tdl\0All files (*.*)\0*.*\0";
    fn.nMaxFile        = MAX_PATH;
    fn.nFilterIndex    = 0;
    fn.lpstrFileTitle  = NULL;
    fn.nMaxFileTitle   = 0;
    fn.lpstrInitialDir = EWIN_TXT_CDIR;
    fn.lpstrFile       = (wchar_t *)malloc((MAX_PATH+1)*sizeof(wchar_t));
    fn.lpstrFile[0]=0;
    fn.lpstrDefExt     = L"";
    fn.Flags           = OFN_EXPLORER | OFN_ENABLESIZING | OFN_HIDEREADONLY;
    fn.lpstrTitle      = L"Select input data file.";
    if(GetSaveFileNameW(&fn))
    {
        if(DOC_FILENAME==0)
        {
            DOC_FILENAME=(wchar_t *)malloc((wcslen(fn.lpstrFile)+1)*sizeof(wchar_t));
        }
        else
        {
            DOC_FILENAME=(wchar_t *)realloc(DOC_FILENAME,(wcslen(fn.lpstrFile)+1)*sizeof(wchar_t));
        }
        wcscpy(DOC_FILENAME,fn.lpstrFile);
        savelist(hwnd);
        return true;
    }
    return false;
}

bool savelist(HWND hwnd)
{
    if(DOC_FILENAME==0 || DOC_FILENAME[0]==0)
    {
        return savelistas(hwnd);
    }

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
        global_list->write(f);
        fclose(f);

        ischanged=false;
    }
    else
    {
        MessageBoxA(hwnd,"�ffnen der Datei fehlgeschlagen!","Info",0);
    }

    return true;
}

bool loadlist(wchar_t *filename)
{
    int n,i=0;
    char line[256];
    FILE *f=_wfopen(filename,L"rt");
    if(f)
    {
        //Erste Zeile:
        n=readline(line,250,f);
        if(strcmp(line,"TestMan-Vb01!")==0)
        {
            free_item();
            ini_item();
            while(n!=0)
            {
                n=readline(line,250,f);
                if(n!=0 && strcmpmin(line,"TITLE:")==0)
                {
                    SetWindowText(hwndCB,&line[6]);
                }
                else if(n!=0 && strcmpmin(line,"ITEM:")==0)
                {
                    SetWindowText(hwndEdit[i++],&line[5]);
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
        MessageBoxA(hwnd,"�ffnen der Datei fehlgeschlagen!","Info",0);
    }
    return true;
}

int readline(char *line,int maxln,FILE *f)
{
    int i=0;
    line[i]=fgetc(f);
    while(!feof(f) && line[i]!='\n' && line[i]!='\r' && i<maxln)
    {
        line[++i]=fgetc(f);
    }
    line[i]=0;
    return i;
}

int strcmpmin(const char *a,const char *b)
{
    int i=0,r=0;
    while(a[i]!=0 && b[i]!=0)
    {
        r=a[i]-b[i];
        if(r)return r;
        i++;
    }
    return r;
}

void ini_progdir(void)
{
    wchar_t *f;//Zeiger auf Dateinamen
	int fln;

    //int m_argc;

	//Programmverzeichnis wchar_t *
#ifdef ap_USEWARGV
	fln=wcslen(__wargv[0]);
	f=(wchar_t *)malloc((fln+2)*sizeof(wchar_t));
	wcscpy(f,__wargv[0]);
	//f[wcslen(f)-11]=0;
	if(cutrightwcs2(f,_T("\\")[0])==-1)
	{
		f[0]=0;
	}
	EWIN_TXT_CDIR=(wchar_t *)malloc((wcslen(f)+1)*sizeof(wchar_t));
	wcscpy(EWIN_TXT_CDIR,f);

	//m_argc=__argc;

#else
	//Programmverzeichnis char *
	fln=strlen(_argv[0]);
	f=(wchar_t *)malloc((fln+2)*sizeof(wchar_t));
	strtowcs(_argv[0],f);
	//f[wcslen(f)-11]=0;
	if(cutrightwcs2(f,L"\\"[0])==-1)
	{
		f[0]=0;
	}
	EWIN_TXT_CDIR=(wchar_t *)malloc((wcslen(f)+1)*sizeof(wchar_t));
	wcscpy(EWIN_TXT_CDIR,f);

	//m_argc=_argc;

#endif

	//Falls kein absoluter Pfad. den aktuellen Pfad (dos:cd) voranstellen.
	if(c_pathtype(EWIN_TXT_CDIR)<3)
	{
		wchar_t *r_x;
		//POSIX: getcwd(), ISO: _getcwd() (bzw._wgetcwd()) nicht in der c-Runtime Library enthalten, WINDOWS: GetCurrentDirectory()
		r_x=_wgetcwd(0,0);//Argument 0 l�sst die Funktion den Speicher selbst anfordern
		if(r_x!=0)
		{
			r_x=(wchar_t *)realloc(r_x,(wcslen(r_x)+wcslen(EWIN_TXT_CDIR)+5)*sizeof(wchar_t));
			wcscat(r_x,WDIRSEPERATOR);
			wcscat(r_x,EWIN_TXT_CDIR);
			//c_mgowcspath(&r_x,EWIN_TXT_CDIR,0);
			free(EWIN_TXT_CDIR);
			EWIN_TXT_CDIR=r_x;
		}
	}
}