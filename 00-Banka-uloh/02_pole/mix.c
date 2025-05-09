#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    float prvek[256];
    int stupen;
} TPolynom;

typedef int (*TAkce)(void);

typedef struct 
{
    bool jeChyba;
    char popis[256];
    TAkce akce;
} TPolozka;

float horner(TPolynom p, float hodnota) 
{
    float vysledek = 0;
    for (int i = 0; i <= p.stupen; i++) {
        vysledek = vysledek * hodnota + p.prvek[i];
    }

    return vysledek;
}

void poslednichN(FILE* vstup, FILE* vystup, int n)
{
    int cislo;
    int posledni[n];
    int i = 0;

    puts("zadavej cisla:");
    while (fscanf(vstup, "%i", &cislo) == 1) { 
        posledni[i] = cislo;
        i = (i + 1) % n;
    }

    printf("poslednich %i\n", n);
    int soucet = 0;
    for (int j = 0; j < n; j++) {
        soucet += posledni[j];
        fprintf(vystup, "%i\n", posledni[(i + j) % n]);
    }

    printf("poslednich %i\n pozpatku", n);
    for (int j = n - 1; j >= 0; j--) {
        fprintf(vystup, "%i\n", posledni[(i + j) % n]);
    }

    fprintf(vystup,"soucet: %i\n", soucet);
}

void histogram(FILE* vstup, int vystup[256])
{
    for (int i = 0; i < 255; i++) {
        vystup[i] = 0;
    }
    char c;
    while ((c = fgetc(vstup)) != EOF) {
        vystup[c]++;
    }
}


int hornerAkce(void)
{
    printf("zadej hodnotu x: ");
    float x;
    if (scanf("%f", &x) != 1) {
        puts("chyba vstupu");
        return 0;
    }

    printf("zadej stupen: ");
    TPolynom p;
    if (scanf("%i", &p.stupen) != 1 || p.stupen > 255) {
        puts("chyba vstupu");
        return 0;
    }

    printf("zadej koeficienty: ");
    for (int i = 0; i <= p.stupen; i++) {
        if (scanf("%f", &p.prvek[i]) != 1) {
            puts("chyba vstupu");
            return 0;
        }       
    }

    printf("vysledek: %f\n", horner(p, x));

    return 0;
}

int nAkce(void)
{
    printf("zadej hodnotu n: ");
    int n = 0;
    if (scanf("%i", &n) != 1) {
        puts("chyba vstupu");
        return 0;
    }
    poslednichN(stdin, stdout, n);

    return 0;
}

int histogramAkce(void)
{
    puts("pis text");
    int histogram_data[256];
    histogram(stdin, histogram_data);

    puts("histogram male anglicke abecedy:");
    for (int i = 'a'; i <= 'z'; i++) {
        printf("%c: %i\n", i, histogram_data[i]);
    }

    return 0;
}

int konecAkce(void) 
{
    return 1;
}

int chybaAkce(void)
{
    puts("Chyba vstupu!");
    return 0;
}


int main(void)
{
    TPolozka menu[256];
    for (int i = 0; i < 256; i++) {
        menu[i] = (TPolozka) { true, "Chyba", chybaAkce };
    }
    menu['A'] = (TPolozka) { false, "Horner", hornerAkce };
    menu['B'] = (TPolozka) { false, "Poslednich N", nAkce };
    menu['C'] = (TPolozka) { false, "Histogram", histogramAkce };
    menu['K'] = (TPolozka) { false, "Konec", konecAkce };
    while ("bobinka mi prodala fentanyl") {
        puts("akce:");
        for (int i = 0; i < 256; i++) {
            if (!menu[i].jeChyba) {
                printf("%c -- %s\n", i, menu[i].popis);
            }
        }
        printf("zadej akci: ");
        char akce;
        if (scanf("%c", &akce) != 1) {
            continue;
        }

        if (menu[akce].akce() == 1) {
            return 0;
        }
    }

    return 1;
}

