
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

int soucetObvodu(int n, int m, int pole[n][m])
{
    int obvod = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i == 0) || (j == 0) || (i == n - 1) || (j == m -1)) {
                obvod += pole[i][j];
            }
        }
    }

    return obvod;
}

int soucetObsahu(int n, int m, int pole[n][m])
{
    int obsah = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!((i == 0) || (j == 0) || (i == n - 1) || (j == m -1))) {
                obsah += pole[i][j];
            }
        }
    }

    return obsah;
}



int main(int argc, char *argv[])
{
    int pole[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };

    int poleTest[4][4] = {
    {2, 3, 4, 5},
    {6, 7, 8, 9},
    {10, 11, 12, 13},
    {0, 0, 0, 0}
};

    vypis2DPole(4, 4, poleTest);
    printf("Soucet obvodu matice: %d\n" , soucetObvodu(4, 4, poleTest));
    printf("Soucet obsahu matice: %d\n" , soucetObsahu(4, 4, poleTest));

    return 0;
}
