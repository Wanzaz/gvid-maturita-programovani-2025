#include <stdio.h>
#include <stdlib.h>

#define N 50

typedef struct _retezec {
    char x;
    char y;
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


// nahraď v řetězci každý výskyt znaku x znakem y (x a y jsou parametry funkce)
void  nahradXYVRetezci(TRetezec *r, char x, char y)
{
    for (int i = 0; r->znak[i] != '\0'; i++) {
        if (r->znak[i] == x) {
            r->znak[i] = y;
        }
    }
}

// nahraď v řetězci každý výskyt znaku x znakem y (x a y jsou parametry funkce)
void  nahradXYVRetezciS(TRetezec *r)
{
    for (int i = 0; r->znak[i] != '\0'; i++) {
        if (r->znak[i] == r->x) {
            r->znak[i] = r->y;
        }
    }
}


int main() {
    /* printf("Zadej retezec: "); */
    /* nactiRetezec(stdin, &r1); */

    TRetezec r1 = {
        .x = 'X',
        .y = 'Y',
        .znak = {'X', 'X', 'a', 'a', 'X'}
    };
    

    vytiskniRetezec(stdout, r1);

    /* nahradXYVRetezciS(&r1); */
    nahradXYVRetezci(&r1, r1.x, r1.y); // ano je to nelogicke to predavat jako parametr, kdyz uz to mam v te sktrukture, ale snazim se splnit zadani

    vytiskniRetezec(stdout, r1);

    

    return 0;
}




