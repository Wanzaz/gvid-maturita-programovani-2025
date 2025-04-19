#include <stdio.h>


typedef struct _matice {
    int radku;
    int sloupcu;
    int prvek[50][50];
} TMatice;


void nactiMatici(FILE *f, TMatice *m)
{
    if (fscanf(f, "%d%d", &m->radku, &m->sloupcu) != 2)  {
        return;
    }

    for (int i = 0; i < m->radku; i++) {
        for (int j = 0; j < m->sloupcu; j++) {
            if (fscanf(f, "%d", &m->prvek[i][j]) != 1)  {
                return;
            }
        }
    }
}

void vypisMatici(FILE *f, TMatice m)
{
    fprintf(f, "%d %d\n", m.radku, m.sloupcu);

    for (int i = 0; i < m.radku; i++) {
        for (int j = 0; j < m.sloupcu; j++) {
            fprintf(f, "%d ", m.prvek[i][j]);
        }
        fprintf(f, "\n");
    }
}


// vytvoř matici otočenou o 90, 180, 270 stupňů (zadej počet otočení o 90 stupňů parametrem)
void otaceniO90(TMatice *m) {
    TMatice nova;
    nova.radku = m->sloupcu;
    nova.sloupcu = m->radku;

    for (int i = 0; i < m->radku; i++) {
        for (int j = 0; j < m->sloupcu; j++) {
            nova.prvek[j][m->radku - 1 - i] = m->prvek[i][j];
        }
    }

    *m = nova;
}


void otaceniO90StupnuDoprava(TMatice *m, int pocetOtoceni)
{
    pocetOtoceni = pocetOtoceni % 4;

    for (int g = 0; g < pocetOtoceni; g++) {
        otaceniO90(m);
    }
}





int main(int argc, char *argv[])
{
    TMatice m = {
        .radku = 4,
        .sloupcu = 4,
        .prvek = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
        }
    };

    TMatice m1 = {
        .radku = 3,
        .sloupcu = 3,
        .prvek = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }
    };
    TMatice m2 = {
        .radku = 3,
        .sloupcu = 2,
        .prvek = {
            {1, 4},
            {2, 5},
            {3, 6}
        }
    };


    vypisMatici(stdout, m2);
    otaceniO90StupnuDoprava(&m2, 5);
    vypisMatici(stdout, m2);


    return 0;
}
