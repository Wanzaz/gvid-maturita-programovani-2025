#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


typedef struct {
    int mantisa;
    int exponent;
    float vysledek;
} TEFormat;

// Na vstupu jsou dvě celá čísla oddělená písmenem E, např. 124E-10. 
// Načti je jako celá čísla a vrať desetinné číslo, které představují (předveď, že víš, co ten zápis představuje). V případě chyby vrať hodnotu NAN (Not A Number = 0.0/0.0). 
// Nesmíš je načítat jako desetinné číslo. Získanou hodnotu vytiskni s přesností na 3 desetinná místa v semilogaritmickém tvaru.


bool nacti(FILE *f, TEFormat *vstup)
{

    if (fscanf(f, "%dE%d", &vstup->mantisa, &vstup->exponent) != 2) {
        vstup->vysledek = 0.0 / 0.0;  // NaN
        return false;
    }

    return true;
}


// Výpočet výsledku
void vypocitej(TEFormat *v)
{
    v->vysledek = v->mantisa * pow(10, v->exponent); // 124E-10  →  124 × 10^(-10)
}

int main(int argc, char *argv[])
{
    TEFormat vstup;

    printf("Zadej vstup ve formatu: 124E-10\n");

    if (!nacti(stdin, &vstup)) {
        printf("Chybný vstup! Výsledek: %f\n", 0.0 / 0.0);
        return -1;
    }

    vypocitej(&vstup);

    // Výpis s přesností na 3 desetinná místa v semilogaritmickém zápisu
    printf("Výsledek: %.3e\n", vstup.vysledek);

    return 0;
}
