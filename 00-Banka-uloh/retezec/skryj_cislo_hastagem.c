#include <stdio.h>
#include <stdlib.h>

#define N 50

typedef struct _retezec {
    char x;
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

// skryj v řetězci každé číslo přepsáním pomocí znaku #
void  nahradCislo(TRetezec *r)
{
    for (int i = 0; r->znak[i] != '\0'; i++) {
        if (r->znak[i] >= '0' && r->znak[i] <= '9') {
            r->znak[i] = r->x;
        }
    }
}

int main() {
    /* printf("Zadej retezec: "); */
    /* nactiRetezec(stdin, &r1); */

    TRetezec r1 = {
        .x = '#',
        .znak = {'1', '2', 'a', 'a', '3'}
    };
    

    vytiskniRetezec(stdout, r1);

    nahradCislo(&r1);

    vytiskniRetezec(stdout, r1);

    

    return 0;
}





