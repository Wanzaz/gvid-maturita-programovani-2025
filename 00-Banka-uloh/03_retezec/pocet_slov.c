#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 50

typedef struct _retezec {
    char znak[N];
} TRetezec;



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


// FSCANF - SSCANF

// vrat pocet slov v retezci - PRVNI MYSLENKA
int  pocetSlovVRetezci(TRetezec r)
{
    int pocet = 0;
    for (int i = 0; r.znak[i] != '\0'; i++) {
        if ((!isspace(r.znak[i]) && isspace(r.znak[i + 1])) || (!isspace(r.znak[i]) && r.znak[i + 1] == '\0')) {
            pocet++;
        }
    }

    return pocet;
}

// Vrátí počet slov v řetězci - LEPSI VARIANTA
int pocetSlovVRetezci1(TRetezec r) {
    int pocet = 0;
    bool veSlove = false;

    for (int i = 0; r.znak[i] != '\0'; i++) {
        if (isspace(r.znak[i])) {
            veSlove = false;
        } else if (!veSlove) {
            veSlove = true;
            pocet++;
        }
    }

    return pocet;
}

int main() {
    TRetezec r;
    printf("Zadej retezec: ");
    nactiRetezec(stdin, &r);

    /* TRetezec r = { */
    /*     .znak = {'1', '2', 'a', 'a', '3'} */
    /* }; */
    

    vytiskniRetezec(stdout, r);


    printf("Pocet slov v retezci: %d\n", pocetSlovVRetezci1(r));

    

    return 0;
}






