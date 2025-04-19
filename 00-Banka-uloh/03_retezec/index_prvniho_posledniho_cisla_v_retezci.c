#include <stdio.h>
#include <stdlib.h>

#define N 50

typedef struct _retezec {
    char znak[N];
} TRetezec;


// vrať indexy první a poslední nalezené číslice v řetězci (přes parametry)

void nactiRetezec(FILE *f, TRetezec *r) {
    fgets(r->znak, N, f);  // Načteme max. MAX_ZNAKU-1 znaků

    // Odstranění případného '\n' na konci
    for (int i = 0; r->znak[i] != '\0'; i++) {
        if (r->znak[i] == '\n') {
            r->znak[i] = '\0';
            break;
        }
    }
}

void vytiskniRetezec(FILE *f, TRetezec r) {
    fprintf(f, "%s\n", r.znak);
}


void  prvniPosledniIndexCisel(TRetezec r, int *prvni, int *posledni)
{
    *prvni = -1;  // Výchozí hodnota: nenalezeno
    *posledni = -1;
    
    for (int i = 0; r.znak[i] != '\0'; i++) {
        if (r.znak[i] >= '0' && r.znak[i] <= '9') {
            if (*prvni == -1) {
                *prvni = i;
            }

            *posledni = i;
        }
    }
}

int main() {
    TRetezec r1;
    int prvni, posledni;

    printf("Zadej retezec: ");
    nactiRetezec(stdin, &r1);
    vytiskniRetezec(stdout, r1);

    prvniPosledniIndexCisel(r1, &prvni, &posledni);

    if (prvni == -1) {
        printf("V retezci nejsou zadne cislice.\n");
    } else {
        printf("Prvni index cisla je %d a posledni je %d\n", prvni, posledni);
    }

    return 0;
}



