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

// zjisti počet sudých prvků v každém sloupci a zapiš jej do posledního řádku v tomto sloupci
void pocetSudychVeSloupci(TMatice* m)
{
    int counter = 0;
    for (int j = 0; j < m->sloupcu; j++) {
        for (int i = 0; i < m->radku; i++) {
            if ((m->prvek[i][j] % 2) == 0)
                counter++;
        }

        m->prvek[m->radku - 1][j] = counter;
        counter = 0;
    }
}


int main(int argc, char *argv[])
{
    TMatice m = {
        .radku = 4,
        .sloupcu = 4,
        .prvek = {
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4}
        }
    };

    vypisMatici(stdout, m);
    pocetSudychVeSloupci(&m);
    vypisMatici(stdout, m);


    return 0;
}

/* void nacti2DPole (FILE* f, int n, int m, int pole[n][m]) */
/* { */
/*     for (int i = 0; i < n; i++) { */
/*         for (int j = 0; j < m; j++) { */
/*             fscanf(f ,"%d", &pole[i][j]); */
/*         } */
/*     } */
/* } */



/* void vypis2DPole (FILE* f, int n, int m, int pole[n][m]) */
/* { */
/*     for (int i = 0; i < n; i++) { */
/*         for (int j = 0; j < m; j++) { */
/*             fprintf(f ,"%d ", pole[i][j]); */
/*         } */
/*         fprintf(f,"\n"); */
/*     } */
/* } */


/* // zjisti počet sudých prvků v každém sloupci a zapiš jej do posledního řádku v tomto sloupci */
/* void pocetSudychVeSloupci(int n, int m, int pole[n][m]) */
/* { */
/*     int pocetSudych = 0; */
/*     for (int sloupec = 0; sloupec < m; sloupec++) { */
/*         for (int radek = 0; radek < n - 1; radek++) { */
/*             if ((pole[radek][sloupec] % 2) == 0) { */
/*                 pocetSudych++; */
/*             } */
/*         } */
/*         pole[n - 1][sloupec] = pocetSudych; // POZOR n -1 -> jen n by bylo mimo rozsah */
/*         pocetSudych = 0; */
/*     } */
/* } */




/* int main(int argc, char *argv[]) */
/* { */
/*     int poleTestovaci[4][3] = { */
/*         {1, 2, 3}, */
/*         {1, 2, 3}, */
/*         {1, 2, 3}, */
/*         {0, 0, 0} */
/*     }; */

/*     // int pole[4][3]; */
/*     // FILE * f = fopen("matice.txt", "r"); */
/*     // if (f == NULL) { */
/*         // return -1; */
/*     // } */
/*     // nacti2DPole(f, 3, 3, pole); */

/*     // vypis2DPole(stdout, 3, 3, poleTestovaci); */
/*     pocetSudychVeSloupci(4, 3, poleTestovaci); */
/*     vypis2DPole(stdout, 4, 3, poleTestovaci); */


/*     // fclose(f); */
/*     return 0; */
/* } */
