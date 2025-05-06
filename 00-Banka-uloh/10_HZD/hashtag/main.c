#include <stdio.h>

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

void menimeZnakNaHashtag(FILE *in, FILE *out, const char retezec[])
{
    int znak;
    while ((znak = fgetc(in)) != EOF) {
        if (znak == '#') {
            fputs(retezec, out);
        } else {
            fputc(znak, out);
        }
    }
}

int main()
{
    char vstupniSoubor[100];
    char vystupniSoubor[100];
    char nahrazujiciRetezec[100];

    printf("Zadejte název vstupního souboru: ");
    if (scanf("%99s", vstupniSoubor) != 1) {
        fprintf(stderr, "Chyba při načítání názvu vstupního souboru.\n");
        return 1;
    }

    printf("Zadejte název výstupního souboru: ");
    if (scanf("%99s", vystupniSoubor) != 1) {
        fprintf(stderr, "Chyba při načítání názvu výstupního souboru.\n");
        return 1;
    }

    printf("Zadejte řetězec, kterým se nahradí '#': ");
    if (scanf("%99s", nahrazujiciRetezec) != 1) {
        fprintf(stderr, "Chyba při načítání nahrazujícího řetězce.\n");
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

    menimeZnakNaHashtag(vstup, vystup, nahrazujiciRetezec);

    fclose(vstup);
    fclose(vystup);

    printf("Znak '#' byl nahrazen řetězcem '%s' v souboru '%s'.\n", nahrazujiciRetezec, vystupniSoubor);

    return 0;
}

