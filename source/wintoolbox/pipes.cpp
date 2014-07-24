/***************************************************
*                                                  *
*  Pipes.                                          *
*                                                  *
***************************************************/
#include "pipes.h"

void ErrorExit(const char *lpszFunction)
{
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,(lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR));
    wsprintfA((LPTSTR)lpDisplayBuf,TEXT("Function %s failed with error %d:\n%s"),lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(1);
}
unsigned long WriteToPipe(char *text,HANDLE pipewh)
{
   unsigned long lnw=0;
   WriteFile(pipewh,text,strlen(text),&lnw,NULL);
   return lnw;
}
char *ReadFromPipe(HANDLE piperh)
{
	char *a;
	int aln=500,ln=0,h;
	a=(char *)malloc((aln+2)*sizeof(char));
	a[0]=0;

	int c=0;
	//char b[2];b[0]=0;b[1]=0;

	DWORD dwRead;
	CHAR chBuf[BUFSIZE];
	BOOL bSuccess=TRUE;//FALSE;
	//HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for(;;)
	{
		bSuccess=ReadFile(piperh,chBuf,200,&dwRead,NULL);
		if(!bSuccess || dwRead==0){break;}
		//bSuccess=WriteFile(piperh,chBuf,dwRead,&dwWritten,NULL);
		//if(!bSuccess){break;}
		h=dwRead;//strlen(chBuf);
		chBuf[h]=0;
		//c=getchar();//piperh);
		//h=1;
		if(c==EOF)
		{
			break;
		}
		else
		{
			//b[0]=c;
			if(ln+h>aln)
			{
				aln=aln+500;
				a=(char *)realloc(a,(aln+2)*sizeof(char));
			}
			strcat(a,chBuf);
			ln=ln+h;
		}
	}
	return a;
}
int ManagePipes(int action,HANDLE *rh)
{
	static SECURITY_ATTRIBUTES sat;
	static HANDLE *h;
	static int *ht;
	static int counth=0,counthm=0;
	int k,i;
	if(counth==0)
	{//Initialisierung (erster Aufruf)
		counthm=counthm+2;
		h=(HANDLE *)malloc(counthm*sizeof(HANDLE));
		ht=(int *)malloc(counthm*sizeof(int));
		ht[counth]=0;
		ht[counth+1]=0;
	}
	if(action==1)
	{//Create a new Pipe
		if(counth>counthm-2)
		{
			counthm=counthm+2;
			h=(HANDLE *)realloc(h,counthm*sizeof(HANDLE));
			ht=(int *)realloc(ht,counthm*sizeof(int));
			ht[counth]=0;
			ht[counth+1]=0;
		}
		//Set the bInheritHandle flag so pipe handles are inherited.
		sat.nLength=sizeof(SECURITY_ATTRIBUTES);
		sat.bInheritHandle=TRUE;
		sat.lpSecurityDescriptor=NULL;
		if(!CreatePipe(&h[counth],&h[counth+1],&sat,0))
		{
			ErrorExit("CreatePipe()");
			return -1;
		}
		if(!SetHandleInformation(h[counth],HANDLE_FLAG_INHERIT,HANDLE_FLAG_INHERIT)
			&& !SetHandleInformation(h[counth+1],0,0))
		{
			ErrorExit("SetHandleInformation()");
			return -1;
		}
		ht[counth]=1;
		ht[counth+1]=1;
		counth=counth+2;
		return counth-2;
	}
	if(action>199)
	{//Handle freigeben
		k=action-200;
		if(k<counth)
		{
			if(ht[k]!=0)
			{
				CloseHandle(h[k]);
				ht[k]=0;
				return 1;
			}
			return 0;
		}
		else
		{
			return 0;
		}
	}
	if(action>99)
	{//Handle abfragen
		k=action-100;
		if(k<=counth)
		{
			*rh=h[k];
			return 1;
		}
		else
		{
			*rh=NULL;
			return 0;
		}
	}
	if(action==9)
	{//Free all
		//Handles freigeben
		for(i=0;i<counth;i++)
		{
			if(ht[i]!=0)
			{
				CloseHandle(h[i]);
			}
		}
		//Speicher freigeben
		counth=0;
		free(h);
		return 0;
	}
	return -1;
}
PROCESS_INFORMATION CreateSubProcess(char *progname,HANDLE substdoutw,HANDLE substdinr)
{
   PROCESS_INFORMATION piProcInfo;
   STARTUPINFO siStartInfo;
   BOOL bSuccess=FALSE;
   ZeroMemory(&piProcInfo,sizeof(PROCESS_INFORMATION));
   ZeroMemory(&siStartInfo,sizeof(STARTUPINFO));
   siStartInfo.cb=sizeof(STARTUPINFO);
   siStartInfo.hStdError=substdoutw;
   siStartInfo.hStdOutput=substdoutw;
   siStartInfo.hStdInput=substdinr;
   siStartInfo.dwFlags=STARTF_USESTDHANDLES | STARTF_FORCEOFFFEEDBACK | STARTF_USESHOWWINDOW;
   siStartInfo.wShowWindow=SW_HIDE;
   bSuccess=CreateProcess(NULL,
      progname,      // command line
      NULL,          // process security attributes
      NULL,          // primary thread security attributes
      TRUE,          // handles are inherited
      0,             // creation flags
      NULL,          // use parent's environment
      NULL,          // use parent's current directory
      &siStartInfo,  // STARTUPINFO pointer
      &piProcInfo);  // receives PROCESS_INFORMATION
   if(!bSuccess)
   {
      ErrorExit("CreateProcess");
      return piProcInfo;
   }
   else
   {
      //später machen
      //CloseHandle(piProcInfo.hProcess);
      //CloseHandle(piProcInfo.hThread);
      return piProcInfo;
   }
}
void CloseSubProcess(PROCESS_INFORMATION piProcInfo)
{
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
}
PROCESS_INFORMATION xCreateProcess(char *a,int u,int v)
{
    HANDLE h1,h2;
    ManagePipes(u+101,&h1);
    ManagePipes(v+100,&h2);
    return CreateSubProcess(a,h1,h2);
}
int xCreatePipe()
{
	return ManagePipes(1,NULL);
}
int xCloseAllPipes()
{
	ManagePipes(9,NULL);
	return 0;
}
int xCloseHandle(int u)
{
	ManagePipes(u+200,NULL);
	return 0;
}
int xClosePipeHandle(int u,int v)
{
	ManagePipes(u+v+200,NULL);
	return 0;
}
char *xReadFromPipe(int u)
{
    char *a;
    HANDLE h1;
    ManagePipes(u+100,&h1);
    a=ReadFromPipe(h1);
	return a;
}
int xWriteToPipe(char *a,int u)
{
    HANDLE h1;
    ManagePipes(u+101,&h1);
    WriteToPipe(a,h1);
	return 0;
}
int xexecute(char *program,char *command)
{
    //*
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    if(CreateProcess(program,command,NULL,NULL,false,0,NULL,NULL,&si,&pi))
    {
        // Wait until child process exits.
        WaitForSingleObject( pi.hProcess, INFINITE );

        // Close process and thread handles.
        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
    }
    else
    {//Fehler
    }
    //*/

    //CREATE_UNICODE_ENVIRONMENT
    //WinExec(fn,1);

    //ShellExecute(hwnd,"open",command,NULL,NULL,5);

	return 0;
}
