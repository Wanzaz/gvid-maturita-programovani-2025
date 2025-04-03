#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct _sopka {
    char nazev[20];
    int vyska;
    bool aktivni;
} TSopka;

typedef struct _sopky {
    int pocet;
    TSopka prvek[50];
} TSopky;

// Pomocí podprogramů zpracuj soubor se strukturovanými daty, kde na každém řádku je záznam o sopkách – název (20 znaků), výška (v metrech), zda je aktivní (ano/ne).
// Počet uložených záznamů není předem znám. Názvy souborů musí zadávat uživatel (dotazem nebo přes parametry příkazového řádku).


void nactiSopkyZeSouboru(FILE *f, TSopky *s)
{
    char status[4];
    int i = 0;
    while (fscanf(f, "%19s %d %3s", s->prvek[i].nazev, &s->prvek[i].vyska, status) == 3) {
        s->prvek[i].aktivni = (strcmp(status, "ano") == 0);
        i++;
    }

    s->pocet = i;
}

void vytiskniSopky(FILE *f, TSopky s)
{
    for (int i = 0; i < s.pocet; i++) {
        fprintf(stdout, "%-20s %5d m  Aktivní: %s\n", 
               s.prvek[i].nazev, s.prvek[i].vyska, 
               s.prvek[i].aktivni ? "Ano" : "Ne");
    }
}

// Vytvoř funkci vracející průměrnou výšku všech ne/aktivních sopek (vybere se parametrem).
int prumernaVyska(TSopky s, bool aktivni)
{
    int sum = 0;
    int pocetAktivnich = 0;

    for (int i = 0; i < s.pocet; i++) {
        if (s.prvek[i].aktivni == aktivni) {
            sum += s.prvek[i].vyska;
            pocetAktivnich++;
        }
    }

    if (pocetAktivnich == 0) {
        return -2;
    }

    return sum / pocetAktivnich;
}

int main(int argc, char *argv[])
{
    TSopky sopky = {
        .pocet = 10,
        .prvek = {
            {"Eyjafjallajökull", 1651, true},
            {"Fudži", 3776, true},
            {"Vesuv", 1281, true},
            {"Etna", 3329, true},
            {"Stromboli", 924, true},
            {"Mauna Loa", 4169, true},
            {"Kilimandžáro", 5895, false},
            {"Krakatoa", 813, true},
            {"Popocatépetl", 5426, true},
            {"Helens", 2549, true}
        }
    };
    TSopky s;

    char cesta[20];

    printf("Zadej nazev souboru sopek: ");
    scanf("%19s", cesta);

    FILE *f = fopen(cesta, "r");
    if (f == NULL) {
        printf("Nepodarilo se soubor otevrit\n");
        return -1;
    }

    nactiSopkyZeSouboru(f, &s);
    vytiskniSopky(stdout, s);

    printf("Prumerna vyska aktivnich sopek: %d m\n", prumernaVyska(s, true));
    printf("Prumerna vyska neaktivnich sopek: %d m\n", prumernaVyska(s, false));

    fclose(f);
    return 0;
}

