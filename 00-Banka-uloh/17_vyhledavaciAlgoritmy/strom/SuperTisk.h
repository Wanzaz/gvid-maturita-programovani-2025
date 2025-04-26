#ifndef SUPERTISK_H_INCLUDED
#define SUPERTISK_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include "strom.h"

typedef struct
{
    int x;
    bool ok;
    int pocetCifer; // pocetcifer, pokud je zaporne (-), tak +1
    int start; // zacatek znaku cifry
    int stred; // stred znaku cifry
    int konec; // konec znaku cifry
    int _levy; // zacatek _ vlevo
    int _pravy; // konec _ vpravo
} Tdata;

typedef struct
{
    Tdata *uroven;
    int sirka; // soucet...cisla v lichem poctu cifer + mezery mezi cisly
    int MaxCifra; // delka ejdelsi cifry v radku
} Tpatro;


void SuperTisk(FILE *out, Tuzel *u);





#endif // SUPERTISK_H_INCLUDED
