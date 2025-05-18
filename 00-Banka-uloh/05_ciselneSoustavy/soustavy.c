#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int prevedCifru(char cifra)
{
    if (cifra >= 'A' && cifra <= 'Z') {
        return cifra - 'A' + 10;
    }

    if (cifra >= '0' && cifra <= '9') {
        return cifra - '0';
    }

    return -1;
}


/**
• Načítej ze vstupu hodnoty zapsané v šestnáctkové soustavě a oddělené bílými
znaky a vracej jejich vyčíslenou hodnotu. V případě chyby vrať zápornou hodnotu
a ukonči program. Vyčíslené hodnoty zapisuj na výstup, každou na jeden řádek.
**/
void vyhodnot16(FILE* vstup, FILE* vystup)
{
    char c;
    int vysledek = 0;
    while ((c = fgetc(vstup)) != EOF) {
        if (c == ' ') {
            fprintf(vystup, "%i\n", vysledek);
            vysledek = 0;
            continue;
        }

        if (c == '\n') {
            fprintf(vystup, "%i\n", vysledek);
            return;
        }


        int cifra = prevedCifru(c);
        if (cifra == -1) {
            printf("-1\n");
            return;
        }
        vysledek = vysledek * 16 + cifra;        
        
    }
}

char cisloNaCifru(int cislo)
{
    if (cislo < 10) {
        return cislo + '0';
    }

    if (cislo < 37) {
        return cislo - 10 + 'A';
    }

    return 0;
}

/**
• Vytvoř podprogram, který zapíše zadanou hodnotu na výstup ve zvolené číselné
soustavě. Základ číselné soustavy a hodnota budou parametry podprogramu
a zjisti je od uživatele. Počítej se základy od 2 do 36.
**/
bool prevedDoSoustavy(int cislo, int soustava, char vystup[], int max)
{
    if (soustava < 2 || soustava > 36) {
        return false;
    }

    int i = 0;
    while (cislo > 0) {
        if (i == max - 2) {
            return false;
        }
        vystup[i] = cisloNaCifru(cislo % soustava);
        cislo = cislo / soustava;
        i++;
    }

    vystup[i] = '\0';

    char h;
    for (int j = 0; j < i / 2; j++) {
        h = vystup[j];
        vystup[j] = vystup[i - 1 - j];
        vystup[i - 1 - j] = h;
    }

    return false;
}

/**
• Na vstupu jsou dvě celá čísla oddělená písmenem E, např. 124E-10. Načti je jako
celá čísla a vrať desetinné číslo, které představují (předveď, že víš, co ten zápis představuje). V případě chyby vrať hodnotu NAN (Not A Number = 0.0/0.0). Ne-
smíš je načítat jako desetinné číslo. Získanou hodnotu vytiskni s přesností na 3 desetinná místa v semilogaritmickém tvaru.
**/
float vyhodnotVedeckyTvar(FILE* vstup)
{
    int a, b;
    if (fscanf(vstup, "%iE%i", &a, &b) != 2) {
        return 0.0/0.0;
    }

    float zaklad = b >= 0 ? 10 : 0.1;
    float vysledek = a;

    for (int i = 0; i < abs(b); i++) {
        vysledek *= zaklad; 
    }

    return vysledek;
}

int main(void)
{
//    vyhodnot16(stdin, stdout);
//    char vysledek[69];
//    prevedDoSoustavy(69, 18, vysledek, 69);
//    printf("%s\n", vysledek);
    printf("%.3E\n", vyhodnotVedeckyTvar(stdin));
}
