#include <stdio.h>

void nacti2DPole (FILE* f, int n, int m, int pole[n][m])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(f ,"%d", &pole[i][j]);
        }
    }
}



void vypis2DPole (FILE* f, int n, int m, int pole[n][m])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(f ,"%d ", pole[i][j]);
        }
        fprintf(f,"\n");
    }
}


// zjisti počet sudých prvků v každém sloupci a zapiš jej do posledního řádku v tomto sloupci
void pocetSudychVeSloupci(int n, int m, int pole[n][m])
{
    int pocetSudych = 0;
    for (int sloupec = 0; sloupec < m; sloupec++) {
        for (int radek = 0; radek < n - 1; radek++) {
            if ((pole[radek][sloupec] % 2) == 0) {
                pocetSudych++;
            }
        }
        pole[n - 1][sloupec] = pocetSudych; // POZOR n -1 -> jen n by bylo mimo rozsah
        pocetSudych = 0;
    }
}




int main(int argc, char *argv[])
{
    int poleTestovaci[4][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {0, 0, 0}
    };

    // int pole[4][3];
    // FILE * f = fopen("matice.txt", "r");
    // if (f == NULL) {
        // return -1;
    // }
    // nacti2DPole(f, 3, 3, pole);

    // vypis2DPole(stdout, 3, 3, poleTestovaci);
    pocetSudychVeSloupci(4, 3, poleTestovaci);
    vypis2DPole(stdout, 4, 3, poleTestovaci);


    // fclose(f);
    return 0;
}
