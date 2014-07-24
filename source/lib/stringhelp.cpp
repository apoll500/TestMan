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
char *strcpyn(char *a,const char *b,int n)
{
    //Maximal n Bytes von b nach a kopieren.
    //b muss ein nullterminierter String sein.
    //a wird automatisch nullterminiert.
    //Der Speicher fuer a muss ausreichend gross sein.
    //Rueckgabewert: a
    int i=0;
    while(i<n && b[i]!=0)
    {
        a[i]=b[i];
        i=i+1;
    }
    a[i]=0;
    return a;
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
