#include <stdio.h>

typedef struct _matice {
    int radku;
    int sloupcu;
    int prvek[50][50];
} TMatice;


// načti M×N prvků do 2D pole ze standardního vstupu, ze souboru
void nactiMatici(FILE* f, TMatice *m)
{
    if (fscanf(f, "%d%d", &m->radku, &m->sloupcu) != 2)  {
        return;
    }

    for (int i = 0 ; i < m->radku; i++) {
        for (int j = 0; j < m->sloupcu; j++) {
            if (fscanf(f, "%d", &m->prvek[i][j]) != 1) {
                return;
            }
        }
    }
}


// vypiš výsledné pole na standardní výstup, do souboru
void vypisMatici(FILE* f, TMatice m)
{
    fprintf(f, "%d %d\n", m.radku, m.sloupcu);

    for (int i = 0 ; i < m.radku; i++) {
        for (int j = 0; j < m.sloupcu; j++) {
            fprintf(f, "%d ", m.prvek[i][j]);
        }
        fprintf(f, "\n");
    }
}

int soucetObvodu(TMatice m)
{
    int obvod = 0;
    for (int i = 0; i < m.radku; i++) {
        for (int j = 0; j < m.sloupcu; j++) {
            if ((i == 0) || (j == 0) || (i == m.radku - 1) || (j == m.sloupcu -1)) {
                obvod += m.prvek[i][j];
            }
        }
    }

    return obvod;
}

int soucetObsahu(TMatice m)
{
    if (m.radku < 3 || m.sloupcu < 3) {
        return 0; // Matice nemá vnitřní prvky
    }

    /* int obsah = 0; */
    /* for (int i = 0; i < m.radku; i++) { */
    /*     for (int j = 0; j < m.sloupcu; j++) { */
    /*         if (!((i == 0) || (j == 0) || (i == m.radku - 1) || (j == m.sloupcu -1))) { */
    /*             obsah += m.prvek[i][j]; */
    /*         } */
    /*     } */
    /* } */
    int obsah = 0;
    for (int i = 1; i < m.radku - 1; i++) {
        for (int j = 1; j < m.sloupcu - 1; j++) {
                obsah += m.prvek[i][j];
        }
    }

    return obsah;
}

int main(int argc, char *argv[])
{
    TMatice m = {
        .radku = 3,
        .sloupcu = 3,
        .prvek = {
            {1, 2, 3},
            {1, 2, 3},
            {1, 2, 3}
        }
    };

    vypisMatici(stdout, m);
    printf("Soucet obvodu matice: %d\n" , soucetObvodu(m));
    printf("Soucet obsahu matice: %d\n" , soucetObsahu(m));



    return 0;
}

/* void vypis2DPole(int n, int m, int pole[n][m]) */
/* { */
/*     for (int i = 0; i < n; i++) { */
/*         for (int j = 0; j < m; j++) { */
/*             printf("%d ", pole[i][j]); */
/*         } */
/*         printf("\n"); */
/*     } */
/* } */

/* int soucetObvodu(int n, int m, int pole[n][m]) */
/* { */
/*     int obvod = 0; */
/*     for (int i = 0; i < n; i++) { */
/*         for (int j = 0; j < m; j++) { */
/*             if ((i == 0) || (j == 0) || (i == n - 1) || (j == m -1)) { */
/*                 obvod += pole[i][j]; */
/*             } */
/*         } */
/*     } */

/*     return obvod; */
/* } */

/* int soucetObsahu(int n, int m, int pole[n][m]) */
/* { */
/*     int obsah = 0; */
/*     for (int i = 0; i < n; i++) { */
/*         for (int j = 0; j < m; j++) { */
/*             if (!((i == 0) || (j == 0) || (i == n - 1) || (j == m -1))) { */
/*                 obsah += pole[i][j]; */
/*             } */
/*         } */
/*     } */

/*     return obsah; */
/* } */



/* int main(int argc, char *argv[]) */
/* { */
/*     int pole[3][3] = { */
/*         {1, 2, 3}, */
/*         {1, 2, 3}, */
/*         {1, 2, 3}, */
/*     }; */

/*     int poleTest[4][4] = { */
/*     {2, 3, 4, 5}, */
/*     {6, 7, 8, 9}, */
/*     {10, 11, 12, 13}, */
/*     {0, 0, 0, 0} */
/* }; */

/*     vypis2DPole(4, 4, poleTest); */
/*     printf("Soucet obvodu matice: %d\n" , soucetObvodu(4, 4, poleTest)); */
/*     printf("Soucet obsahu matice: %d\n" , soucetObsahu(4, 4, poleTest)); */

/*     return 0; */
/* } */
