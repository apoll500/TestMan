/***************************************************
*                                                  *
*  getting the program directory                   *
*                                                  *
*  ----------------------------------------------  *
*                                                  *
*  This file is part of TestMan!                   *
*  Copyright 2015 by Andreas Pollhammer            *
*                                                  *
***************************************************/
#include "progdir.h"

wchar_t *EWIN_TXT_CDIR;

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
