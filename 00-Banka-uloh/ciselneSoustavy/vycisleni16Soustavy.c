#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Načítej ze vstupu hodnoty zapsané v šestnáctkové soustavě a oddělené bílými znaky a vracej jejich vyčíslenou hodnotu. V případě chyby vrať zápornou hodnotu
// a ukonči program. Vyčíslené hodnoty zapisuj na výstup, každou na jeden řádek.


#define N 50

// Struktura pro uchování hodnoty a chybového stavu
typedef struct {
    int value;  // Vyčíslená hodnota v desítkové soustavě
    int error;  // Chybový stav (0 - bez chyby, -1 - chyba)
} HexResult;

typedef struct {
    char znak[N];
} TRetezec;


// Funkce pro převod šestnáctkového čísla na desítkové číslo
HexResult hexToDec(const char* hexStr) {
    HexResult result;
    result.error = 0;  // Předpokládáme, že není chyba

    // Pokusíme se převést šestnáctkové číslo na desítkovou hodnotu
    if (sscanf(hexStr, "%x", &result.value) != 1) {
        result.error = -1;  // Pokud převod neproběhne, nastavíme chybu
    }

    return result;
}

// Funkce pro zpracování vstupu a výstup výsledků
void nacitej(TRetezec *r) {

    while (scanf("%s", r->znak) == 1) {   // Čteme slovo za slovem
        HexResult result = hexToDec(r->znak);

        if (result.error == -1) {
            printf("Chyba při načítání hodnoty: %s\n", r->znak);
            exit(-1);
        }

        printf("Desítková hodnota: %u\n", result.value);
    }
}

int main() {
    TRetezec r;

    printf("Zadejte šestnáctková čísla oddělená mezerami: \n");

    nacitej(&r);

    return 0;
}

