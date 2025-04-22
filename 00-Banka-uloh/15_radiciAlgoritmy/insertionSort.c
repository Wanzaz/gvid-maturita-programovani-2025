#include <stdio.h>
typedef struct _pole {
    int delka;
    float prvek[15];
} Tpole;

void insertionSortSeZarazkouNaKonci(Tpole *p) { // n o 1 vetsi !!!!
    for (int d = p->delka - 2; d >= 0; d--) { // ted jdeme odzadu
        p->prvek[p->delka] = p->prvek[d]; // zarazka
        int i = d; // i je index hledane pozice

        while (p->prvek[p->delka] > p->prvek[i + 1]) {
            p->prvek[i] = p->prvek[i + 1];
            i++;
        }
        p->prvek[i] = p->prvek[p->delka]; // vlozeni odlozeneho
    }
}


void put(FILE* to, float numbers[], int size) {
    fprintf(to, "%i\n", size);
    for (int i = 0; i < size; i++) {
        fprintf(to, "%f\n", numbers[i]);
    }
}

int main(int argc, char *argv[])
{
    Tpole p = {
        .delka = 5,
        .prvek = {4, 3, 2, 8, 5, 0} // místo navíc pro zarážku
    };

    insertionSortSeZarazkouNaKonci(&p);
    put(stdout, p.prvek, p.delka); // tiskneme jen 5 platných prvků

    return 0;
}



