#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define START_CAPACITY 10

typedef struct _sopka {
    char nazev[START_CAPACITY];
    int vyska;
    bool aktivni;
} TSopka;

typedef struct _sopky {
    int pocet;
    int kapacita;
    TSopka *prvek;  // Dynamicky alokované pole
} TSopky;

// Pomocí podprogramů zpracuj soubor se strukturovanými daty, kde na každém řádku je záznam o sopkách – název (20 znaků), výška (v metrech), zda je aktivní (ano/ne).
// Počet uložených záznamů není předem znám. Názvy souborů musí zadávat uživatel (dotazem nebo přes parametry příkazového řádku).





void nactiSopkyZeSouboru(FILE *f, TSopky *s)
{
    char status[4];
    s->pocet = 0;
    s->kapacita = START_CAPACITY;

    s->prvek = malloc(sizeof(TSopka) * s->kapacita);
    if (s->prvek == NULL) {
        printf("Chyba při alokaci paměti!\n");
        exit(-1);
    }

    while (fscanf(f, "%19s %d %3s", s->prvek[s->pocet].nazev, &s->prvek[s->pocet].vyska, status) == 3) {
        s->prvek[s->pocet].aktivni = (strcmp(status, "ano") == 0);
        s->pocet++;

        // Pokud dojdeme na konec alokovaného prostoru, zvětšíme ho
        if (s->pocet >= s->kapacita) {
            int new_size = s->kapacita * 2;  // Zdvojnásobíme velikost pole
            TSopka *temp = realloc(s->prvek, sizeof(TSopka) * new_size);
            if (temp == NULL) {
                printf("Chyba při realokaci paměti!\n");
                free(s->prvek);
                exit(-1);
            }
            s->prvek = temp;
            s->kapacita = new_size;
        }
    }
}

void vytiskniSopky(FILE *f, TSopky s)
{
    for (int i = 0; i < s.pocet; i++) {
        fprintf(f, "%-20s %5d m  Aktivní: %s\n", 
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

// Vypiš názvy všech sopek vyšších než hodnota zadaná parametrem. U každého názvu vypiš, zda je sopka aktivní, či ne.
void vytiskniVyssiSopky(FILE *f, TSopky s, int vyska)
{
    for (int i = 0; i < s.pocet; i++) {
        if (s.prvek[i].vyska > vyska) {
            fprintf(f, "%-20s %5d m  Aktivní: %s\n", 
                   s.prvek[i].nazev, s.prvek[i].vyska, 
                   s.prvek[i].aktivni ? "Ano" : "Ne");
        }
    }
}


// Zapiš do výstupního souboru všechny záznamy pouze o ne/aktivních sopkách (zadej parametrem). 
void zapisovaniDoSouboru(FILE *f, TSopky s, bool aktivni)
{
    for (int i = 0; i < s.pocet; i++) {
        if (s.prvek[i].aktivni == aktivni) {
            fprintf(f, "%s %d %s\n", 
                   s.prvek[i].nazev, s.prvek[i].vyska, 
                   s.prvek[i].aktivni ? "ano" : "ne");
        }
    }

}

// Vytvoř jeden soubor se záznamy o aktivních a druhý se zá-
// znamy o neaktivních sopkách. Výstupní soubory musí zachovávat formát vstupní-
// ho souboru.
void zapisovaniDoSouboruAKNEK(FILE *aktivni, FILE *neaktivni, TSopky s)
{
    for (int i = 0; i < s.pocet; i++) {
        if (s.prvek[i].aktivni) {
            fprintf(aktivni, "%s %d %s\n", 
                   s.prvek[i].nazev, s.prvek[i].vyska, 
                   s.prvek[i].aktivni ? "ano" : "ne");
        } else if (!s.prvek[i].aktivni){
            fprintf(neaktivni, "%s %d %s\n", 
                   s.prvek[i].nazev, s.prvek[i].vyska, 
                   s.prvek[i].aktivni ? "ano" : "ne");
        }
    }
}

int main(int argc, char *argv[])
{
    TSopky s;
    char cesta[20];

    printf("Zadej nazev souboru sopek: ");
    scanf("%19s", cesta);

    FILE *f = fopen(cesta, "r");
    if (f == NULL) {
        printf("Nepodarilo se soubor otevrit\n");
        return -1;
    }

    // Nacitani a vypisovani
    nactiSopkyZeSouboru(f, &s);
    vytiskniSopky(stdout, s);

    // Prumerna vyska
    printf("Prumerna vyska aktivnich sopek: %d m\n", prumernaVyska(s, true));
    printf("Prumerna vyska neaktivnich sopek: %d m\n", prumernaVyska(s, false));

    // Vyssi sopky
    printf("-----------------------------\n");
    vytiskniVyssiSopky(stdout, s, 2000);

    // Zapisovani do souboru - aktivni/neaktivni
    char cesta1[20];

    printf("Zadej nazev vystupniho souboru: ");
    scanf("%19s", cesta1);

    FILE *vystup = fopen(cesta1, "w");
    if (vystup == NULL) {
        printf("Nepodarilo se soubor otevrit\n");
        return -1;
    }
    zapisovaniDoSouboru(vystup, s, false);
    

    // Zapisovani do 2 souboru - aktivni/neaktivni
    char cesta2[20];
    char cesta3[20];

    printf("Zadej nazev vystupniho souboru pro aktivni: ");
    scanf("%19s", cesta2);
    printf("Zadej nazev vystupniho souboru pro neaktivni: ");
    scanf("%19s", cesta3);

    FILE *aktivni = fopen(cesta2, "w");
    FILE *neaktivni = fopen(cesta3, "w");
    if (neaktivni == NULL || aktivni == NULL) {
        printf("Nepodarilo se soubor otevrit\n");
        free(s.prvek);
        return -1;
    }

    zapisovaniDoSouboruAKNEK(aktivni, neaktivni, s);


    free(s.prvek);  // Uvolníme alokovanou paměť
    fclose(f);
    fclose(vystup);
    fclose(aktivni);
    fclose(neaktivni);
    return 0;
}

