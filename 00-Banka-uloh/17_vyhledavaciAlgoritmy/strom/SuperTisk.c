#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "strom.h"
#include "SuperTisk.h"

/**
_ podle poctu pater, kazde patro vyse: +1 _
**/


int DelkaCisla(int x)
{
    int delka=0;
    if (x==0 || x<0){
        delka=1;
        x=-x;
    }

    while(x>0)
    {
        delka++;
        x=x/10;
    }
    return delka;
}


bool ProjdiPatro(Tpatro **pole,Tuzel *u, int patro, int actual, bool *alokace, int *kolikaty)
{
    if(u!=NULL)
    {
        if(!(*alokace) && actual==patro)
        {
            *pole=realloc(*pole,actual*sizeof(Tpatro));
             (*pole+actual-1)->uroven=malloc(pow(2,patro-1)*sizeof(Tdata));
             for(int i=0;i<pow(2,patro-1);i++)
                    (*pole+actual-1)->uroven[i].ok=false;
            *alokace=true;
        }
        if(actual==patro)
        {
            (*pole+actual-1)->uroven[*kolikaty].ok=true;
            (*pole+actual-1)->uroven[*kolikaty].x=u->klic;
            (*pole+actual-1)->uroven[*kolikaty].start=-1;
            (*pole+actual-1)->uroven[*kolikaty].stred=-1;
            (*pole+actual-1)->uroven[*kolikaty].konec=-1;
            (*pole+actual-1)->uroven[*kolikaty]._levy=-1;
            (*pole+actual-1)->uroven[*kolikaty]._pravy=-1;
            (*pole+actual-1)->uroven[*kolikaty].pocetCifer=DelkaCisla(u->klic);
            *kolikaty=*kolikaty+1;
            return true;
        }

        if(actual<patro)
        {
            bool a=ProjdiPatro(pole,u->levy, patro, actual+1, alokace, kolikaty);
            bool b=ProjdiPatro(pole,u->pravy, patro, actual+1, alokace, kolikaty);
            return a||b;
        }
    }
    else{
        *kolikaty=*kolikaty+pow(2,patro-actual);
    }

    return false;
}




int VyplnPole(Tpatro **pole,Tuzel *u)
{
    bool dalsi=true;
    int patro=1;
    *pole=malloc(sizeof(Tpatro));
    (*pole)->uroven=malloc(sizeof(Tdata));
    (*pole)->uroven->ok=true;
    (*pole)->uroven->x=u->klic;
    (*pole)->uroven->pocetCifer=DelkaCisla(u->klic);
    (*pole)->uroven->konec=-1;
    (*pole)->uroven->start=-1;
    (*pole)->uroven->stred=-1;
    (*pole)->uroven->_levy=-1;
    (*pole)->uroven->_pravy=-1;

    int kolikaty=0;
    bool alokace=false;
    while(dalsi)
    {
        patro++;
        dalsi=ProjdiPatro(pole, u, patro, 1, &alokace, &kolikaty);
        kolikaty=0;
        alokace=false;
    }
    return patro-1;
}

void NastavSirky(Tpatro *pole, int pocetPater)
{
    int pocetCisel;
    for(int i=0;i<pocetPater;i++)
    {
        pole[i].sirka=0;
        pocetCisel=0;
        for(int j=0;j<pow(2,i);j++)
        {
            if(pole[i].uroven[j].ok)
            {
                pocetCisel++;
                pole[i].sirka=pole[i].sirka + pole[i].uroven[j].pocetCifer + ((pole[i].uroven[j].pocetCifer%2==0) ? 1 : 0);
            }
        }
        pole[i].sirka=pole[i].sirka+pocetCisel-1;
    }
}

int NejvetsiCifra(Tpatro *pole, int pocetPater)
{
    int maxCifra, nejvetsiZevsech=0;
    for(int i=0;i<pocetPater;i++)
    {
        maxCifra=-1;
        for(int j=0;j<pow(2,i);j++)
        {
            if(pole[i].uroven[j].ok)
            {
                if(maxCifra<pole[i].uroven[j].pocetCifer)
                    maxCifra=pole[i].uroven[j].pocetCifer;
            }
        }
        pole[i].MaxCifra= (maxCifra%2==0) ? (maxCifra+1) : maxCifra;
        if(nejvetsiZevsech<pole[i].MaxCifra)
            nejvetsiZevsech=pole[i].MaxCifra;
    }
    return nejvetsiZevsech;
}


int VlozCislaDoRadku(Tpatro *pole,char *tiskpole, int pocetPater,int mezery[],int i,int mezeraMeziCisly)
{
    int actual=0, x, j=0, mocnina, krok;
    if(i==pocetPater-1)
    {
        while(j<pow(2,i))
        {
            if(pole[i].uroven[j].ok)
            {  /** Mezery pred cislem **/

                for(int m=0;m<(pole[i].MaxCifra - pole[i].uroven[j].pocetCifer)/2;m++  )
                {
                    tiskpole[actual]=' ';
                    actual++;
                }
                x=pole[i].uroven[j].x;
                /** CISLO **/
                for(int m=0;m<pole[i].uroven[j].pocetCifer;m++  )
                {
                    if(x<0)
                    {
                        tiskpole[actual]='-';
                        pole[i].uroven[j].start=actual;
                        actual++;
                        x=x*(-1);
                    } else
                    {   mocnina =  (int) pow(10,pole[i].uroven[j].pocetCifer-m-1);
                        tiskpole[actual]= 48+ x/mocnina;
                        if(pole[i].uroven[j].start<0) pole[i].uroven[j].start=actual;
                        actual++;
                        x=x%mocnina;
                    }
                }
                pole[i].uroven[j].konec=actual-1;
                pole[i].uroven[j].stred= (pole[i].uroven[j].pocetCifer%2==0) ? ( (pole[i].uroven[j].konec+pole[i].uroven[j].start+1)/2 ) : ( (pole[i].uroven[j].konec+pole[i].uroven[j].start)/2 );
                /** Mezery za cislem **/
                for(int m=0;m< ( pole[i].MaxCifra-(pole[i].MaxCifra-pole[i].uroven[j].pocetCifer)/2 -pole[i].uroven[j].pocetCifer);m++  )
                {
                    tiskpole[actual]=' ';
                    actual++;
                }
                /** Mezery mezi cisly **/
                mezery[j]= mezeraMeziCisly==1 ? actual : mezeraMeziCisly/2+actual;
                for(int m=0; m<mezeraMeziCisly; m++)
                {
                    tiskpole[actual]=' ';
                    actual++;
                }
            }
            else
            {
                /** Misto cisla **/
                for(int m=0; m<pole[i].MaxCifra; m++)
                {   tiskpole[actual]=' ';
                    actual++;
                }
                /** Mezery mezi cisly **/
                mezery[j]= mezeraMeziCisly==1 ? actual : mezeraMeziCisly/2+actual;
                for(int m=0; m<mezeraMeziCisly; m++)
                {
                    tiskpole[actual]=' ';
                    actual++;
                }
            }
            if (((int)pow(2,pocetPater-1) )*pole[i].MaxCifra*2 <= actual-2) return -1;
            j++;
        }
        tiskpole[actual]='\0';
    }
    else
    {
         krok=(int) pow(2,pocetPater-2-i);
         while(j<pow(2,i))
         {
            if(pole[i].uroven[j].ok)
            {
                 /**MEZERY Pred CISLEM**/

                 for(int m=0; m < mezery[(int) pow(2,pocetPater-2-i)-1]-(pole[i].uroven[j].pocetCifer)/2 ; m++)
                 {
                    tiskpole[actual]=' ';
                    actual++;
                 }

                 x=pole[i].uroven[j].x;
                 /** CISLO **/
                 for(int m=0;m<pole[i].uroven[j].pocetCifer;m++ )
                 {
                     if(x<0)
                     {
                        tiskpole[actual]='-';
                        pole[i].uroven[j].start=actual;
                        actual++;
                        x=x*(-1);
                     } else
                     {  mocnina =  (int) pow(10,pole[i].uroven[j].pocetCifer-m-1);
                        tiskpole[actual]= 48+ x/mocnina;
                        if(pole[i].uroven[j].start<0) {
                                pole[i].uroven[j].start=actual;

                        }
                        actual++;
                        x=x%mocnina;
                     }
                 }
                 pole[i].uroven[j].konec=actual-1;
                pole[i].uroven[j].stred= (pole[i].uroven[j].pocetCifer%2==0) ? ( (pole[i].uroven[j].konec+pole[i].uroven[j].start+1)/2 ) : ( (pole[i].uroven[j].konec+pole[i].uroven[j].start)/2 );
                /** Mezery za cislem do vyplneni licheho poctu cifer**/
                for(int m=0;m< ( pole[i].MaxCifra-(pole[i].MaxCifra-pole[i].uroven[j].pocetCifer)/2 -pole[i].uroven[j].pocetCifer);m++  )
                {
                    tiskpole[actual]=' ';
                    actual++;
                }

                /**MEZERY Za CISLEM **/
                if(j+1<pow(2,i))
                     for(int m=actual; m < mezery[((int) pow(2,pocetPater-2-i))-1 +((int) pow(2,pocetPater-1-i))*j +krok]; m++) //+((int) pow(2,pocetPater-1-i))*(j+1)-1
                     {
                        tiskpole[actual]=' ';
                        actual++;
                     }
                 tiskpole[actual]=' '; /** Mezera uprostred **/
                 actual++;
                 /** DOPLNENI __ __ pred a za CISLEM ***/
                 /** LEVY _ **/

                 if(pole[i+1].uroven[2*j].ok)
                 {
                     pole[i].uroven[j]._levy=pole[i+1].uroven[2*j].stred+1+(pocetPater-i)/2;
                     for(int m=pole[i].uroven[j]._levy; m<pole[i].uroven[j].start;m++)
                     {

                         tiskpole[m]='_';
                     }

                 }
                 /** PRAVY _ **/
                 if(pole[i+1].uroven[2*j+1].ok)
                 {
                     pole[i].uroven[j]._pravy=pole[i+1].uroven[2*j+1].stred-1-(pocetPater-i)/2;
                     for(int m=pole[i].uroven[j].konec+1; m<=pole[i].uroven[j]._pravy;m++)
                     {
                         tiskpole[m]='_';
                         if(!(j+1<pow(2,i)))
                         {
                             actual++;
                             tiskpole[actual]='\0';
                             tiskpole[m+1]='\0';
                         }
                     }
                 }
            }
            else
            {
                if(j+1<pow(2,i))
                     for(int m=actual; m < mezery[((int) pow(2,pocetPater-2-i))-1 +((int) pow(2,pocetPater-1-i))*j +krok]; m++)
                     {
                        tiskpole[actual]=' ';
                        actual++;
                     }
                 tiskpole[actual]=' ';
                 actual++;
            }
            j++;
         }
         tiskpole[actual]='\0';
    }
    return 1;
}


int VyplntiskPole(Tpatro *pole,char **tiskpole, int pocetPater)
{
    int mezery[(int) pow(2,pocetPater-1)];
    int mezeraMeziCisly=1, kolize;

    VlozCislaDoRadku(pole,tiskpole[pocetPater],pocetPater,mezery,pocetPater-1,mezeraMeziCisly);

    for(int i=pocetPater-1; i>=0; i--)
    {
        if(i==pocetPater-1)
          kolize=VlozCislaDoRadku(pole,tiskpole[i],pocetPater,mezery,i,mezeraMeziCisly);
        else
            kolize=VlozCislaDoRadku(pole,tiskpole[i],pocetPater,mezery,i,mezeraMeziCisly);
        if(kolize>1)
        {
            mezeraMeziCisly=kolize;
            i=pocetPater;
        }
        if (kolize==-1) return -1;
    }
    return 0;
}



void SipkyLevaPrava(Tpatro *pole,int patro,int pocetPater, FILE *out)
{
    bool Levy=true;
    int aktual;

    for(int r=0; r<(pocetPater-patro)/2;r++) //pocet radku
    {
        Levy=true;
        aktual=0;
        for(int j=0;j<(int) pow(2,patro+1);j++)
        {
            if(Levy)
            {
                if(pole[patro].uroven[j/2].ok)
                {
                    for(int m=aktual;m<pole[patro].uroven[j/2]._levy-1-r;m++)
                    {
                        fprintf(out," ");
                        aktual++;
                    }
                    if(pole[patro+1].uroven[j].ok)
                          {
                             fprintf(out,"/");
                             aktual++;
                          }
                }
                Levy=false;
            }
            else
            {
                 if(pole[patro].uroven[j/2].ok)
                    {
                        for(int m=aktual;m<pole[patro].uroven[j/2]._pravy+1+r;m++)
                        {
                            fprintf(out," ");
                            aktual++;
                        }
                        if(pole[patro+1].uroven[j].ok)
                          {
                              fprintf(out,"\\");
                                aktual++;
                          }
                    }
                Levy=true;
            }
        }
        fprintf(out,"\n");
    }
}



void SuperTisk(FILE *out, Tuzel *u)
{
    Tpatro *pole;
    char **tiskPole;
    if(u==NULL)
    {
        fprintf(out, "Strom je prazdny.\n");
        return;
    }


    int pocetPater=VyplnPole(&pole,u);
    NastavSirky(pole,pocetPater);
    int NejvetsiCifraZeVsech=NejvetsiCifra(pole,pocetPater);


     tiskPole=malloc(sizeof(char*)*(pocetPater+1));
     if( (tiskPole)==NULL) return;
     for(int i=0;i<=pocetPater; i++)
         tiskPole[i]=malloc(sizeof(char)*( ((int)pow(2,pocetPater-1) )*(NejvetsiCifraZeVsech+2) ));


    if( VyplntiskPole(pole, tiskPole, pocetPater)==-1)
    {
        printf("Neco se moc pokakalo, sorry jako\n");
        return;
    }

    for(int i=0; i<pocetPater; i++)
    {
        fprintf(out,"%s",tiskPole[i]);
        fprintf(out,"\n");
        SipkyLevaPrava(pole,i, pocetPater, out);
    }


    /**Smazani dynamickych promennych**/
    for(int i=0; i<pocetPater;i++)
    {
        free(pole[i].uroven);
        free(tiskPole[i]);
    }
    free(pole);
    free(tiskPole[pocetPater]);
    free(tiskPole);

}
