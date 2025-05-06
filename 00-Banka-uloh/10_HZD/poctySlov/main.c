#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

/**
Pomocí podprogramů vyřeš... Názvy souborů a dalších parametrů musí hlavní program
získat od uživatele (ze vstupu nebo z parametrů příkazového řádku).
• Vytvoř podprogram, který zpracuje vstupní soubor tak, že každý výskyt znaku
# nahradí zadaným textovým řetězcem a výsledek zapíše do výstupního souboru.

• Vytvoř podprogram, který zkombinuje dva vstupní soubory tak, že bude do vý-
stupního souboru zapisovat střídavě vždy jeden řádek z prvního a pak ze druhé-
ho souboru.

• Vytvoř podprogram, který zjistí počet slov na každém řádku vstupního souboru
a tyto počty zapíše na odpovídající řádky výstupního souboru.
• Vstupní soubor obsahuje textově zapsaná celá čísla větší než nula. Na začátku
jsou data seřazená vzestupně na konci je oblast přeplnění. Seřazenou oblast

a oblast přeplnění odděluje řádek s hodnotou 0. Vytvoř funkci, která v tomto sou-
boru efektivně vyhledá zadanou hodnotu a bude brát v úvahu jak seřazenou ob-
last, tak oblast přeplnění.
**/


/**
• Vytvoř podprogram, který zjistí počet slov na každém řádku vstupního souboru
a tyto počty zapíše na odpovídající řádky výstupního souboru.
**/


int pocetSlovNaRadku(char* r) {
    int pocet = 0;
    bool veSlove = false;

    for (int i = 0; r[i] != '\0'; i++) {
        if (isspace(r[i])) {
            veSlove = false;
        } else if (!veSlove) {
            veSlove = true;
            pocet++;
        }
    }
    return pocet;
}

void poctySlov(FILE* in, FILE *out) {
    char *radek = NULL;
    size_t len = 0;
    ssize_t nread;
    int pocetSlov;

    while ((nread = getline(&radek, &len, in)) != -1) {
        pocetSlov = pocetSlovNaRadku(radek);
        fprintf(out, "%d\n", pocetSlov);
    }

    if (radek) { free(radek); }
}

int main() {
    char vstupniSoubor[100];
    char vystupniSoubor[100];

    printf("Zadejte název vstupního souboru: ");
    if (scanf("%99s", vstupniSoubor) != 1) {
        fprintf(stderr, "Chyba při načítání názvu vstupního souboru.\n");
        return 1;
    }

    printf("Zadejte název výstupního souboru pro počty slov: ");
    if (scanf("%99s", vystupniSoubor) != 1) {
        fprintf(stderr, "Chyba při načítání názvu výstupního souboru.\n");
        return 1;
    }

    FILE *vstup = fopen(vstupniSoubor, "r");
    if (vstup == NULL) {
        perror("Chyba při otevírání vstupního souboru");
        return 1;
    }

    FILE *vystup = fopen(vystupniSoubor, "w");
    if (vystup == NULL) {
        perror("Chyba při otevírání výstupního souboru");
        fclose(vstup);
        return 1;
    }

    poctySlov(vstup, vystup);

    fclose(vstup);
    fclose(vystup);

    printf("Počty slov z každého řádku souboru '%s' byly zapsány do souboru '%s'.\n", vstupniSoubor, vystupniSoubor);

    return 0;
}
