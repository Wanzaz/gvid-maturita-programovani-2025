#include <stdio.h>

// N = pocet radku
// M = pocet sloupcu

// načti M×N prvků do 2D pole ze standardního vstupu, ze souboru
void nactiPole2D(FILE *f, int n, int m, int pole[n][m])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(f, "%d", &pole[i][j]);
        }
    }
}

// vypiš výsledné pole na standardní výstup, do souboru
/* void funkce(int pole[][100], int n, int m); */
void vypisPole2D(FILE *f, int n, int m, int pole[n][m])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(f, "%d ", pole[i][j]);
        }
        fprintf(f, "\n");
    }
}

int main()
{
    int n = 3;
    int m = 3;
    int pole[n][m];

    int poleTestovaci[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // ze vstupu
    printf("Zadej matici s rozmery 3x3:\n");
    nactiPole2D(stdin, 3, 3, pole);
    vypisPole2D(stdout, 3, 3, pole);
    
    // Testovaci pole vytisk
    /* vypisPole2D(stdout, poleTestovaci, 3, 3); */


    // ze souboru
    /* FILE * f = fopen("matice.txt", "r"); */
    /* if (f == NULL) { */
    /*     printf("Nepodařilo se otevřít soubor\n"); */
    /*     return -1; */
    /* } */
    /* nactiPole2D(f, pole, 3, 3); */
    /* /1* vypisPole2D(stdout, pole, 3, 3); *1/ */
    /* vypisPole2D(stdout, 3, 3, pole); */
    /* fclose(f); */

    return 0;
}
