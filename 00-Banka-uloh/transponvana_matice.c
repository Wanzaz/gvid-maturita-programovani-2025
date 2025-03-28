#include <stdio.h>


void vypis2DPole(int n, int m, int pole[n][m])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", pole[i][j]);
        }
        printf("\n");
    }
}

// vytvoř transponovanou matici
// A =
// 1  2  3
// 4  5  6
// 0  0  0

// Aᵗ =
// 1  4  0
// 2  5  0
// 3  6  0


// vytvoř transponovanou matici - in place
void transponuj(int n, int m, int pole[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < m; j++) {
            int tmp = pole[i][j];
            pole[i][j] = pole[j][i];
            pole[j][i] = tmp;
        }
    }
}

// vytvoř transponovanou matici - pomoci dalsiho  pole
void transponujMatici(int n, int m, int vstup[n][m], int vystup[m][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vystup[j][i] = vstup[i][j];
        }
    }
}



int main(int argc, char *argv[])
{
    int pole[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
    };
    int vystup[3][3];

    int pole2[3][3] = {
        {1, 4},
        {2, 5},
        {3, 6},
    };
    int pole3[4][4] = {
        {1, 5},
        {2, 6},
        {3, 7},
        {4, 8},
    };

    int pole4[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
    };

    /* vypis2DPole(3, 3, pole); */
    /* transponujMatici(3, 3, pole, vystup); */
    /* vypis2DPole(3, 3, vystup); */

    /* vypis2DPole(3, 3, pole); */
    /* transponuj(3, 3, pole); */
    /* vypis2DPole(3, 3, pole); */

    vypis2DPole(4, 4, pole3);
    transponuj(4, 4, pole3);
    printf("--------\n");
    vypis2DPole(4, 4, pole3);


    return 0;
}
