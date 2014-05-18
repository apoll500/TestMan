/***************************************************
*                                                  *
*  Some usefull functions for file-I/O.            *
*                                                  *
***************************************************/

#include "filehelp.h"

int c_pathtype(wchar_t *path)
{
	//Ermittelt ob der String path eine absolute oder relative Pfadangabe enth�lt
	//und ob der Pfad auf eine Datei oder ein Verzeichnis zeigt.
	//
	// Merkmale:
	//   absoluter Pfad:
	//     - Pfad beginnt mit Dirseperatorzeichen (root in Linux) ODER
	//     - Pfad enth�lt ":" vor dem Auftreten des ersten Dirseperatorzeichens.
	//     - SONST: relativer Pfad.
	//   Pfad zeigt auf Verzeichnis, wenn letztes Zeichen ein Dirseperatorzeichen ist, sonst zeigt der Pfad auf eine Datei.
	//
	int i;
	int n=wcslen(path);
	int isabs=0;
	int isdir=0;
	if(path[n-1]==WDIRSEPERATOR[0] || path[n-1]==WDIRSEPERATOR2[0]){isdir=1;}
	if(path[0]==WDIRSEPERATOR[0] || path[0]==WDIRSEPERATOR2[0]){isabs=1;}
	else
	{
		for(i=0;i<n;i++)
		{
			if(path[i]==WDIRSEPERATOR[0] || path[i]==WDIRSEPERATOR2[0]){i=n;}
			if(path[i]==WLABLESEPERATOR[0]){isabs=1;}
		}
	}
	return isabs+isdir*2;
}
