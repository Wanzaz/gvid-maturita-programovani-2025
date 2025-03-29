#include <stdio.h>
#include <stdbool.h>


void vypis2DPole(int n, int m, int pole[n][m])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", pole[i][j]);
        }
        printf("\n");
    }
}

// zjisti, zda je matice vertikálně, či horizontálně symetrická
bool vertikalneSymetricka(int n, int m, int pole[n][m])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m/2; j++) {
            if (pole[i][j] != pole[i][m - j - 1]) {
                return false;
            }
        }
    }

    return true;
}

// zjisti, zda je matice vertikálně, či horizontálně symetrická
bool horizontalneSymetricka(int n, int m, int pole[n][m])
{
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < m; j++) {
            if (pole[i][j] != pole[n - i - 1][j]) {
                return false;
            }
        }
    }

    return true;
}

// Bonusova implementace
bool jeSymetricka(int n, int m, int pole[n][m], char typ) {
    if (typ == 'v') { // vertikální
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m / 2; j++)
                if (pole[i][j] != pole[i][m - j - 1]) return false;
    } else if (typ == 'h') { // horizontální
        for (int i = 0; i < n / 2; i++)
            for (int j = 0; j < m; j++)
                if (pole[i][j] != pole[n - i - 1][j]) return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    int pole[5][5] = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5}
    };
    int pole2[4][4] = {
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
    };
    int pole3[5][5] = {
        {1, 2, 3, 2, 5},
        {1, 2, 3, 2, 1},
        {1, 5, 3, 2, 1},
        {1, 2, 3, 2, 1},
        {1, 2, 3, 2, 1}
    };
    int pole4[4][4] = {
        {1, 2, 2, 1},
        {1, 2, 2, 1},
        {1, 2, 2, 1},
        {1, 2, 2, 1},
    };

    /* vypis2DPole(5, 5, pole); */
    /* if (vertikalneSymetricka(5, 5, pole)) { */
    /*     printf("\nAno je vertikalne soumerna\n"); */
    /* } */
    vypis2DPole(4, 4, pole4);
    if (vertikalneSymetricka(4, 4, pole4)) {
        printf("\nJe vertikalne soumerna\n");
    } else {
        printf("\nNeni vertikalne soumerna\n");
    }

    vypis2DPole(4, 4, pole2);
    if (horizontalneSymetricka(4, 4, pole2)) {
        printf("\nJe horizontalne soumerna\n");
    } else {
        printf("\nNeni horiontalne soumerna\n");
    }

    return 0;
}

