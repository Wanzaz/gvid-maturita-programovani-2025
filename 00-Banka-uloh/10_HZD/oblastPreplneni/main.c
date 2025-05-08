#include <stdio.h>
#include <stdbool.h>

/**
Vstupní soubor obsahuje textově zapsaná celá čísla větší než nula. Na začátku
jsou data seřazená vzestupně na konci je oblast přeplnění. 
Seřazenou oblast a oblast přeplnění odděluje řádek s hodnotou 0. Vytvoř funkci, která v tomto sou-
boru efektivně vyhledá zadanou hodnotu a bude brát v úvahu jak seřazenou ob-
last, tak oblast přeplnění.
**/


int hledejVSerazene(FILE *f, int hledana)
{
    int i = 0;
    int cislo;
    while(fscanf(f, "%d", &cislo) == 1) {
        if (cislo == hledana) {
            return true;
        }
        if (cislo >  hledana && cislo == 0) {
            return false;
        }
        i++;
    }

    return false;
}

bool hledejVPreplneni(FILE *f, int hledana)
{
    int i = 0;
    int cislo;
    while(fscanf(f, "%d", &cislo) == 1) {
        if (cislo == hledana) {
            return true;
        }
        i++;
    }
    return false;
}

bool hledejVSouboru(const char *cestaSouboru, int hledana)
{
    FILE *f = fopen(cestaSouboru, "r");
    if (f == NULL) {
        fprintf(stderr, "Nepodarilo se otevrit soubor");
        return -1;
    }

    if (hledejVSerazene(f, hledana)) {
        fclose(f);
        return true;
    }

    if (hledejVPreplneni(f, hledana)) {
        fclose(f);
        return true;
    }

    fclose(f);
    return false;
}


int main(int argc, char *argv[])
{
    char cestaSouboru[20];
    printf("Zadej cestu k souboru: ");
    scanf("%19s", cestaSouboru);


    int hledana;
    printf("Zadej hledanou hodnotu: ");
    scanf("%d", &hledana);


    if (hledejVSouboru(cestaSouboru, hledana)) {
        printf("Hodnota byla nalezena\n");
    } else {
        printf("Hodnota nebyla nalezena\n");
    }


    return 0;
}
