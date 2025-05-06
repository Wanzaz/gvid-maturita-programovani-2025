#include <stdio.h>
#include <stdlib.h>

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
• Vytvoř podprogram, který zkombinuje dva vstupní soubory tak, že bude do vý-
stupního souboru zapisovat střídavě vždy jeden řádek z prvního a pak ze druhé-
ho souboru.
**/

void kombinujSoubory(FILE *in1, FILE *in2, FILE *out)
{
    char *radek1 = NULL;
    size_t len1 = 0;
    ssize_t nread1;

    char *radek2 = NULL;
    size_t len2 = 0;
    ssize_t nread2;

    while (1) {
        // Pokusíme se přečíst řádek z prvního souboru
        nread1 = getline(&radek1, &len1, in1);
        if (nread1 > 0) {
            fputs(radek1, out);
        }

        // Pokusíme se přečíst řádek z druhého souboru
        nread2 = getline(&radek2, &len2, in2);
        if (nread2 > 0) {
            fputs(radek2, out);
        }

        // Pokud jsme dosáhli konce obou souborů, ukončíme smyčku
        if (nread1 <= 0 && nread2 <= 0) {
            break;
        }
    }

    if (radek1) free(radek1);
    if (radek2) free(radek2);
}


int main()
{
    char vstupniSoubor1[100];
    char vstupniSoubor2[100];
    char vystupniSoubor[100];

    printf("Zadejte název prvního vstupního souboru: ");
    if (scanf("%99s", vstupniSoubor1) != 1) {
        fprintf(stderr, "Chyba při načítání názvu prvního vstupního souboru.\n");
        return 1;
    }

    printf("Zadejte název druhého vstupního souboru: ");
    if (scanf("%99s", vstupniSoubor2) != 1) {
        fprintf(stderr, "Chyba při načítání názvu druhého vstupního souboru.\n");
        return 1;
    }

    printf("Zadejte název výstupního souboru: ");
    if (scanf("%99s", vystupniSoubor) != 1) {
        fprintf(stderr, "Chyba při načítání názvu výstupního souboru.\n");
        return 1;
    }

    FILE *vstup1 = fopen(vstupniSoubor1, "r");
    if (vstup1 == NULL) {
        fprintf(stderr, "Chyba při otevírání prvního vstupního souboru");
        return 1;
    }

    FILE *vstup2 = fopen(vstupniSoubor2, "r");
    if (vstup2 == NULL) {
        fprintf(stderr, "Chyba při otevírání druhého vstupního souboru");
        fclose(vstup1);
        return 1;
    }

    FILE *vystup = fopen(vystupniSoubor, "w");
    if (vystup == NULL) {
        fprintf(stderr, "Chyba při otevírání výstupního souboru");
        fclose(vstup1);
        fclose(vstup2);
        return 1;
    }

    kombinujSoubory(vstup1, vstup2, vystup);

    fclose(vstup1);
    fclose(vstup2);
    fclose(vystup);

    printf("Soubory '%s' a '%s' byly zkombinovány do souboru '%s'.\n", vstupniSoubor1, vstupniSoubor2, vystupniSoubor);

    return 0;
}

