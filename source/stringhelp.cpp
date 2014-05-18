/***************************************************
*                                                  *
*  Funktionen zur Manipulation von Strings         *
*                                                  *
***************************************************/

#include "stringhelp.h"

void strtowcs(char *in,wchar_t *out)
{
    int i,n=strlen(in);
    for(i=0;i<n;i++)
    {
        out[i]=btowc(in[i]);
        if(in[i]==0 || out[i]==WEOF)
        {
            out[i]=0;
            i=n;
        }
    }
    out[i]=0;
}
int cutrightwcs2(wchar_t *a,wchar_t s)
{
	//sucht das letzte Vorkommen von s im String a und schneidet a am Zeichen s ab. (s wird nicht weggeschnitten)
	//Falls s nicht gefunden wird wird der Original-String beibehalten.
	int i,n,r=-1;
	n=wcslen(a);
	for(i=n-1;i>-1;i--)
	{
		if(a[i]==s)
		{
			//Zeichenkette abschneiden
			a[i+1]=0;
			//Position merken
			r=i;
			//Schleife abbrechen
			i=-1;
		}
	}
	return r;
}
