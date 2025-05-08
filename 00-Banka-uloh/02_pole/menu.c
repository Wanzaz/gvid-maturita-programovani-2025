#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char volba;
    const char *popis;
} TNabidkaPolozka;

char zobrazNabidku(const TNabidkaPolozka nabidka[], int pocet) {
    printf("\n--- Nabídka ---\n");
    for (int i = 0; i < pocet; i++) {
        printf("%c - %s\n", nabidka[i].volba, nabidka[i].popis);
    }

    printf("Zadejte volbu: ");
    char vstup;
    scanf("%c", &vstup);
    vstup = toupper(vstup);

    for (int i = 0; i < pocet; i++) {
        if (vstup == nabidka[i].volba) {
            return vstup;
        }
    }

    return 'X'; // Neznámá volba
}

int main() {
    TNabidkaPolozka nabidka[] = {
        {'A', "Volba A"},
        {'B', "Volba B"},
        {'K', "Konec"}
    };
    int pocetPolozek = sizeof(nabidka) / sizeof(nabidka[0]);

    char volba;
    do {
        volba = zobrazNabidku(nabidka, pocetPolozek);

        switch (volba) {
            case 'A':
                printf("Zvolena volba A.\n");
                break;
            case 'B':
                printf("Zvolena volba B.\n");
                break;
            case 'K':
                printf("Program se ukončuje.\n");
                break;
            case 'X':
                printf("Neznámá volba. Zkuste to znovu.\n");
                break;
        }
    } while (volba != 'K');

    return 0;
}

