#include <stdio.h>
#include <string.h>

// Vytvoř podprogram, který zapíše zadanou hodnotu na výstup ve zvolené číselné soustavě. Základ číselné soustavy a hodnota budou parametry podprogramu
// a zjisti je od uživatele. Počítej se základy od 2 do 36.


#define DIGITS "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef struct _parametry {
    int zakladSoustavy;
    int hodnota;
    char vysledek[100];
} Tparametry;

// Funkce pro převod čísla z desítkové do libovolné soustavy (2–36)
void prevod(Tparametry *p)
{
    int index = 0;
    int cislo = p->hodnota;

    if (cislo == 0) {
        p->vysledek[0] = '0';
        p->vysledek[1] = '\0';
        return;
    }

    // Dělíme číslo základem a ukládáme zbytky jako znaky
    while (cislo > 0) {
        int zbytek = cislo % p->zakladSoustavy;
        p->vysledek[index++] = DIGITS[zbytek];
        cislo /= p->zakladSoustavy;
    }

    p->vysledek[index] = '\0';

    // Otočíme výsledek (protože je uložen pozpátku)
    char tmp;
    for (int i = 0; i < index / 2; ++i) {
        tmp = p->vysledek[i];
        p->vysledek[i] = p->vysledek[index - 1 - i];
        p->vysledek[index - 1 - i] = tmp;
    }
}

// Načtení parametrů od uživatele (ze vstupu)
void nactiParametry(FILE* f, Tparametry *p)
{
    fscanf(f, "%d - %d", &p->hodnota, &p->zakladSoustavy);
}

int main(int argc, char *argv[])
{
    Tparametry p;

    printf("Zadej parametry ve tvaru: hodnota - Zaklad soustavy\n");
    nactiParametry(stdin, &p);

    if (p.zakladSoustavy < 2 || p.zakladSoustavy > 36) {
        printf("Základ soustavy musí být mezi 2 a 36.\n");
        return -1;
    }

    prevod(&p);

    printf("Výsledek: %s\n", p.vysledek);

    return 0;
}

