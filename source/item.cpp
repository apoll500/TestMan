/***************************************************
*                                                  *
*  ITEMS                                           *
*                                                  *
***************************************************/

#include "item.h"

item *global_list;

void ini_item(void)
{
    int i;
    item *p,*t;
    global_list=new item();
    p=global_list;
    for(i=0;i<19;i++)
    {
        t=new item();
        p->setnextitem(t);
        p=t;
    }
}

void free_item(void)
{
    item *n,*c=global_list;
    while(c->findnext()!=0)
    {
        n=c->findnext();
        delete c;
        c=n;
    }
    delete c;
}

unsigned char trc_64(unsigned char c)
{
	if(c==0){c=43;}
	else if(c<12){c=c+46;}
	else if(c<38){c=c+53;}
	else{c=c+59;}
	return c;
}

unsigned char trc_64u(unsigned char c)
{
	if(c==43){c=0;}
	else if(c<58){c=c-46;}
	else if(c<91){c=c-53;}
	else{c=c-59;}
	return c;
}

unsigned char *c_datatostr_64(void *v,long vln)
{
	//Daten in String umwandeln
	//
	long i,n=vln/3;
	if(vln!=3)
	{
		int x=0;
		x++;
	}
	//if(n*3<vln){n++;}
	unsigned char *c;
	c=(unsigned char *)malloc((n*4+6)*sizeof(unsigned char));
	for(i=0;i<n;i++)
	{
		//00111111=63ischanged=false;
		//11000000=192
		//00001111=15
		//11110000=240
		//00000011=3
		//11111100=252
		c[4*i]=trc_64(((unsigned char *)v)[3*i] & 63);
		c[4*i+1]=trc_64((((unsigned char *)v)[3*i] & 192)>>6 | (((unsigned char *)v)[3*i+1] & 15)<<2);
		c[4*i+2]=trc_64((((unsigned char *)v)[3*i+1] & 240)>>4 | (((unsigned char *)v)[3*i+2] & 3)<<4);
		c[4*i+3]=trc_64((((unsigned char *)v)[3*i+2] & 252)>>2);
	}
	c[4*i]=0;
	//Letztes Datenpaket ergänzen
	if(vln-n*3==1)
	{
		c[4*n]=trc_64(((unsigned char *)v)[3*n] & 63);
		c[4*n+1]=trc_64((((unsigned char *)v)[3*n] & 192)>>6);
		c[4*n+2]=0;
	}
	if(vln-n*3==2)
	{
		c[4*n]=trc_64(((unsigned char *)v)[3*n] & 63);
		c[4*n+1]=trc_64((((unsigned char *)v)[3*n] & 192)>>6 | (((unsigned char *)v)[3*n+1] & 15)<<2);
		c[4*n+2]=trc_64((((unsigned char *)v)[3*n+1] & 240)>>4);
		c[4*n+3]=0;
	}
	//(wchar_t *)v
	return c;
}

void *c_strtodata_64(unsigned char *c)
{
	//String in Daten umwandeln

	long aln=strlen((char *)c);
	long i,n=aln/4;
	unsigned char *v;
	v=(unsigned char *)malloc((n*3+4)*sizeof(unsigned char));
	for(i=0;i<n;i++)
	{
		//00111111=63
		//11000000=192
		//00001111=15
		//11110000=240
		//00000011=3
		//11111100=252
		//00111100=60
		//00110000=48
		v[3*i]=trc_64u(c[4*i]) | (trc_64u(c[4*i+1]) & 3)<<6;
		v[3*i+1]=(trc_64u(c[4*i+1]) & 60)>>2 | (trc_64u(c[4*i+2]) & 15)<<4;
		v[3*i+2]=(trc_64u(c[4*i+2]) & 48)>>4 | trc_64u(c[4*i+3])<<2;
	}
	//v[3*i]=0;
	//Letztes Datenpaket ergänzen
	if(aln-n*4==2)
	{
		v[3*i]=trc_64u(c[4*i]) | (trc_64u(c[4*i+1]) & 3)<<6;
	}
	else if(aln-n*4==3)
	{
		v[3*i]=trc_64u(c[4*i]) | (trc_64u(c[4*i+1]) & 3)<<6;
		v[3*i+1]=(trc_64u(c[4*i+1]) & 60)>>2 | (trc_64u(c[4*i+2]) & 15)<<4;
	}
	//(wchar_t *)v;
	return (void *)v;
}
