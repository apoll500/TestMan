/***************************************************
*                                                  *
*  Windows-Dialoge                                 *
*                                                  *
***************************************************/
#include "dialog.h"

wchar_t *EWIN_TXT_CDIR;
wchar_t *DOC_FILENAME;
bool ischanged;

bool ini_dialog(void)
{
    DOC_FILENAME=0;
    ini_progdir();
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
    free_filename();
    return true;
}
bool openconf(void)
{
    ShellExecute(hwnd,"open","testman.conf",NULL,NULL,5);
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
    int i;
    char *b;

    if(DOC_FILENAME==0 || DOC_FILENAME[0]==0)
    {
        return savelistas(hwnd);
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
    char line[256];
    FILE *f=_wfopen(filename,L"rt");
    if(f)
    {
        global_lablelist.setid(0);
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

    fillall();

    return true;
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
		r_x=_wgetcwd(0,0);//Argument 0 lässt die Funktion den Speicher selbst anfordern
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
