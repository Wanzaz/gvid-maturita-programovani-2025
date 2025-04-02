#include <stdio.h>
#include <stdlib.h>

#define N 50

typedef struct _retezec {
    char znak[N];
} TRetezec;

// Vrat pocet cislic v retezci


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


int pocetCiselVRetezci(TRetezec r)
{
    int pocet = 0;
    
    for (int i = 0; r.znak[i] != '\0'; i++) {
        if (r.znak[i] >= '0' && r.znak[i] <= '9') {
            pocet++;
        }
    }


    return pocet;
}

int main() {
    TRetezec r1;

    printf("Zadej retezec: ");
    nactiRetezec(stdin, &r1);
    vytiskniRetezec(stdout, r1);

    printf("Pocet znaku v retezci: %d\n", pocetCiselVRetezci(r1));

    return 0;
}


