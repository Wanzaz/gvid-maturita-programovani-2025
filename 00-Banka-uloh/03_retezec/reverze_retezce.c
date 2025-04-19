#include <stdio.h>
#include <stdlib.h>

#define N 50

typedef struct _retezec {
    int delka;
    char znak[N];
} TRetezec;



void nactiRetezec(FILE *f, TRetezec *r) {
    fgets(r->znak, N, f);  // Načteme max. MAX_ZNAKU-1 znaků
    int i;

    // Odstranění případného '\n' na konci
    for (i = 0; r->znak[i] != '\0'; i++) {
        if (r->znak[i] == '\n') {
            r->znak[i] = '\0';
            break;
        }
    }

    r->delka = i;
}

void vytiskniRetezec(FILE *f, TRetezec r) {
    fprintf(f, "%s\n", r.znak);
}

// proveď reverzi řetězce jednou pomocí rekurze a jednou pomocí cyklu s co nejmenším počtem iterací
void reverzeRetezceCyklus(TRetezec *r)
{
    char tmp;
    for (int i = 0; i < r->delka/2; i++) {
        tmp = r->znak[i];
        r->znak[i] = r->znak[r->delka - i - 1];
        r->znak[r->delka - i - 1] = tmp;
    }
}

void _reverzeRetezceRekurzivne(TRetezec *r, int start, int konec)
{
    if (start >= konec) { return; } // koncime uprostred retezce

    char tmp = r->znak[start];
    r->znak[start] = r->znak[konec];
    r->znak[konec] = tmp;

    _reverzeRetezceRekurzivne(r, start + 1, konec - 1);
}

void reverzeRetezceRekurzivne(TRetezec *r)
{
    _reverzeRetezceRekurzivne(r, 0, r->delka - 1);
}

int main() {
    TRetezec r1;

    printf("Zadej retezec: ");
    nactiRetezec(stdin, &r1);
    vytiskniRetezec(stdout, r1);

    /* reverzeRetezceCyklus(&r1); */
    reverzeRetezceRekurzivne(&r1);
    vytiskniRetezec(stdout, r1);

    return 0;
}


