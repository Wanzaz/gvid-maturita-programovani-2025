#include <stdio.h>
#include <stdbool.h>

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


// zjisti, zda je matice vertikálně, či horizontálně symetrická
bool jeSymetricka(TMatice m, char typ) {
    if (typ == 'v') { // vertikální
        for (int i = 0; i < m.radku; i++)
            for (int j = 0; j < m.sloupcu / 2; j++)
                if (m.prvek[i][j] != m.prvek[i][m.sloupcu - j - 1]) return false;
    } else if (typ == 'h') { // horizontální
        for (int i = 0; i < m.radku / 2; i++)
            for (int j = 0; j < m.sloupcu; j++)
                if (m.prvek[i][j] != m.prvek[m.radku - i - 1][j]) return false;
    } else if (typ == 'd') { // diagonalne
        for (int i = 0; i < m.radku; i++)
            for (int j = i + 1; j < m.sloupcu; j++)
                if (m.prvek[i][j] != m.prvek[j][i]) return false;
    }
    return true;
}

// zjisti, zda je matice diagonalne symetricka
bool symetrickaDiagonalne(TMatice m)
{
    if (m.sloupcu != m.radku) {
        return false; // neni ctvercova matice
    }
    for (int i = 0; i < m.radku; i++) {
        for (int j = i + 1; j < m.sloupcu; j++) {
            if (m.prvek[i][j] != m.prvek[j][i]) {
                return false;
            }
        }
    }
    return true;
}

// zjisti, zda je matice vertikálně, či horizontálně symetrická
bool symetrickaVertikalne(TMatice m)
{
    for (int i = 0; i < m.radku; i++) {
        for (int j = 0; j < m.sloupcu/2; j++) {
            if (m.prvek[i][j] != m.prvek[i][m.sloupcu - j - 1]) {
                return false;
            }
        }
    }
    return true;
}

// zjisti, zda je matice vertikálně, či horizontálně symetrická
bool symetrickaHorizontalne(TMatice m)
{
    for (int i = 0; i < m.radku/2; i++) {
        for (int j = 0; j < m.sloupcu; j++) {
            if (m.prvek[i][j] != m.prvek[m.radku - i - 1][j]) {

                return false;
            }
        }
    }

    return true;
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
    if (jeSymetricka(m, 'v')) {
        printf("Symetricka vertikalne\n");
    }
    if (jeSymetricka(m, 'h')) {
        printf("Symetricka horizontalne\n");
    }
    if (jeSymetricka(m, 'd')) {
        printf("Symetricka diagonalne\n");
    }
    vypisMatici(stdout, m);


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

/* // zjisti, zda je matice vertikálně, či horizontálně symetrická */
/* bool vertikalneSymetricka(int n, int m, int pole[n][m]) */
/* { */
/*     for (int i = 0; i < n; i++) { */
/*         for (int j = 0; j < m/2; j++) { */
/*             if (pole[i][j] != pole[i][m - j - 1]) { */
/*                 return false; */
/*             } */
/*         } */
/*     } */

/*     return true; */
/* } */

/* // zjisti, zda je matice vertikálně, či horizontálně symetrická */
/* bool horizontalneSymetricka(int n, int m, int pole[n][m]) */
/* { */
/*     for (int i = 0; i < n/2; i++) { */
/*         for (int j = 0; j < m; j++) { */
/*             if (pole[i][j] != pole[n - i - 1][j]) { */
/*                 return false; */
/*             } */
/*         } */
/*     } */

/*     return true; */
/* } */

/* // Bonusova implementace */
/* bool jeSymetricka(int n, int m, int pole[n][m], char typ) { */
/*     if (typ == 'v') { // vertikální */
/*         for (int i = 0; i < n; i++) */
/*             for (int j = 0; j < m / 2; j++) */
/*                 if (pole[i][j] != pole[i][m - j - 1]) return false; */
/*     } else if (typ == 'h') { // horizontální */
/*         for (int i = 0; i < n / 2; i++) */
/*             for (int j = 0; j < m; j++) */
/*                 if (pole[i][j] != pole[n - i - 1][j]) return false; */
/*     } */
/*     return true; */
/* } */

/* int main(int argc, char *argv[]) */
/* { */
/*     int pole[5][5] = { */
/*         {1, 2, 3, 4, 5}, */
/*         {1, 2, 3, 4, 5}, */
/*         {1, 2, 3, 4, 5}, */
/*         {1, 2, 3, 4, 5}, */
/*         {1, 2, 3, 4, 5} */
/*     }; */
/*     int pole2[4][4] = { */
/*         {1, 2, 3, 4}, */
/*         {1, 2, 3, 4}, */
/*         {1, 2, 3, 4}, */
/*         {1, 2, 3, 4}, */
/*     }; */
/*     int pole3[5][5] = { */
/*         {1, 2, 3, 2, 5}, */
/*         {1, 2, 3, 2, 1}, */
/*         {1, 5, 3, 2, 1}, */
/*         {1, 2, 3, 2, 1}, */
/*         {1, 2, 3, 2, 1} */
/*     }; */
/*     int pole4[4][4] = { */
/*         {1, 2, 2, 1}, */
/*         {1, 2, 2, 1}, */
/*         {1, 2, 2, 1}, */
/*         {1, 2, 2, 1}, */
/*     }; */

/*     /1* vypis2DPole(5, 5, pole); *1/ */
/*     /1* if (vertikalneSymetricka(5, 5, pole)) { *1/ */
/*     /1*     printf("\nAno je vertikalne soumerna\n"); *1/ */
/*     /1* } *1/ */
/*     vypis2DPole(4, 4, pole4); */
/*     if (vertikalneSymetricka(4, 4, pole4)) { */
/*         printf("\nJe vertikalne soumerna\n"); */
/*     } else { */
/*         printf("\nNeni vertikalne soumerna\n"); */
/*     } */

/*     vypis2DPole(4, 4, pole2); */
/*     if (horizontalneSymetricka(4, 4, pole2)) { */
/*         printf("\nJe horizontalne soumerna\n"); */
/*     } else { */
/*         printf("\nNeni horiontalne soumerna\n"); */
/*     } */

/*     return 0; */
/* } */

