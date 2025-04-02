#include <ctype.h> // POZOR
#include <stdio.h>
#include <stdlib.h>

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

// nahraď v řetězci malá písmena za velká, nebo velká za malá
void  nahradVelkaMalymi(TRetezec *r)
{
    for (int i = 0; r->znak[i] != '\0'; i++) {
        if (r->znak[i] >= 'A' && r->znak[i] <= 'Z') { // isupper(r->znak[i])
            r->znak[i] = tolower(r->znak[i]);
        }
    }
}

// nahraď v řetězci malá písmena za velká, nebo velká za malá
void  nahradMaleVelkymi(TRetezec *r)
{
    for (int i = 0; r->znak[i] != '\0'; i++) {
        if (r->znak[i] >= 'a' && r->znak[i] <= 'z') { // islower(r->znak[i])
            r->znak[i] = toupper(r->znak[i]);
        }
    }
}

int main() {
    /* printf("Zadej retezec: "); */
    /* nactiRetezec(stdin, &r1); */

    TRetezec r1 = {
        .znak = {'C', 'H', 'Z', 'a', 'A', 'v', 'h', 'z'}
    };
    

    vytiskniRetezec(stdout, r1);
    nahradVelkaMalymi(&r1);
    vytiskniRetezec(stdout, r1);
    nahradMaleVelkymi(&r1);
    vytiskniRetezec(stdout, r1);

    

    return 0;
}
