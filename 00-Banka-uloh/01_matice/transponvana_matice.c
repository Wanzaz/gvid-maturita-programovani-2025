#include <stdio.h>

// vytvoř transponovanou matici
// A =
// 1  2  3
// 4  5  6

// Aᵗ =
// 1  4
// 2  5
// 3  6

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

// vytvor transponovanou matici
void transpozice(TMatice *m)
{
    TMatice tmp;
    tmp.radku = m->sloupcu;
    tmp.sloupcu = m->radku;

    for (int i = 0; i < m->radku; i++) {
        for (int j = 0; j < m->sloupcu; j++) {
            tmp.prvek[j][i] = m->prvek[i][j];  // Překlápíme prvky
        }
    }

    *m = tmp; // Překopírujeme do původní matice
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

    TMatice m1 = {
        .radku = 3,
        .sloupcu = 2,
        .prvek = {
            {1, 2},
            {3, 4},
            {5, 6}
        }
    };


    vypisMatici(stdout, m1);
    transpozice(&m1);
    vypisMatici(stdout, m1);


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

/* // vytvoř transponovanou matici */
/* // A = */
/* // 1  2  3 */
/* // 4  5  6 */
/* // 0  0  0 */

/* // Aᵗ = */
/* // 1  4  0 */
/* // 2  5  0 */
/* // 3  6  0 */


/* // vytvoř transponovanou matici - in place */
/* void transponuj(int n, int m, int pole[n][m]) { */
/*     for (int i = 0; i < n; i++) { */
/*         for (int j = i + 1; j < m; j++) { // POZOR j = i + 1; */
/*             int tmp = pole[i][j]; */
/*             pole[i][j] = pole[j][i]; */
/*             pole[j][i] = tmp; */
/*         } */
/*     } */
/* } */

/* // vytvoř transponovanou matici - pomoci dalsiho  pole */
/* void transponujMatici(int n, int m, int vstup[n][m], int vystup[m][n]) { */
/*     for (int i = 0; i < n; i++) { */
/*         for (int j = 0; j < m; j++) { */
/*             vystup[j][i] = vstup[i][j]; */
/*         } */
/*     } */
/* } */



/* int main(int argc, char *argv[]) */
/* { */
/*     int pole[3][3] = { */
/*         {1, 2, 3}, */
/*         {4, 5, 6}, */
/*     }; */
/*     int vystup[3][3]; */

/*     int pole2[3][3] = { */
/*         {1, 4}, */
/*         {2, 5}, */
/*         {3, 6}, */
/*     }; */
/*     int pole3[4][4] = { */
/*         {1, 5}, */
/*         {2, 6}, */
/*         {3, 7}, */
/*         {4, 8}, */
/*     }; */

/*     int pole4[4][4] = { */
/*         {1, 2, 3, 4}, */
/*         {5, 6, 7, 8}, */
/*     }; */

/*     /1* vypis2DPole(3, 3, pole); *1/ */
/*     /1* transponujMatici(3, 3, pole, vystup); *1/ */
/*     /1* vypis2DPole(3, 3, vystup); *1/ */

/*     /1* vypis2DPole(3, 3, pole); *1/ */
/*     /1* transponuj(3, 3, pole); *1/ */
/*     /1* vypis2DPole(3, 3, pole); *1/ */

/*     vypis2DPole(4, 4, pole3); */
/*     transponuj(4, 4, pole3); */
/*     printf("--------\n"); */
/*     vypis2DPole(4, 4, pole3); */


/*     return 0; */
/* } */
