#include <stdio.h>

// N = pocet radku
// M = pocet sloupcu


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


int main(int argc, char *argv[])
{
    FILE* f = fopen("matice.txt", "r");
    if (f == NULL) {
        printf("Nepodarilo se soubor otevrit\n");
    }

    FILE* f1 = fopen("matice1.txt", "w");
    if (f1 == NULL) {
        printf("Nepodarilo se soubor otevrit\n");
    }
    

    // cvicna promenna
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

    TMatice m1;


    /* printf("Zadej velikost matice a prvky matice: \n"); */
    /* nactiMatici(stdin, &m1); */
    /* printf("--------------\n"); */
    /* vypisMatici(stdout, m1); */
    /* printf("--------------\n"); */
    /* vypisMatici(stdout, m); */
    /* printf("--------------\n"); */
    /* vypisMatici(f1, m); */
    printf("--------------\n");
    nactiMatici(f, &m1);
    vypisMatici(f1, m1);

    fclose(f);
    fclose(f1);
    return 0;
}








// Na nic kod

// načti M×N prvků do 2D pole ze standardního vstupu, ze souboru
/* void nactiPole2D(FILE *f, int n, int m, int pole[n][m]) */
/* { */
/*     for (int i = 0; i < n; i++) { */
/*         for (int j = 0; j < m; j++) { */
/*             fscanf(f, "%d", &pole[i][j]); */
/*         } */
/*     } */
/* } */

// vypiš výsledné pole na standardní výstup, do souboru
/* void funkce(int pole[][100], int n, int m); */
/* void vypisPole2D(FILE *f, int n, int m, int pole[n][m]) */
/* { */
/*     for (int i = 0; i < n; i++) { */
/*         for (int j = 0; j < m; j++) { */
/*             fprintf(f, "%d ", pole[i][j]); */
/*         } */
/*         fprintf(f, "\n"); */
/*     } */
/* } */

/* int main() */
/* { */
/*     int n = 3; */
/*     int m = 3; */
/*     int pole[n][m]; */

/*     int poleTestovaci[3][3] = { */
/*         {1, 2, 3}, */
/*         {4, 5, 6}, */
/*         {7, 8, 9} */
/*     }; */

/*     // ze vstupu */
/*     printf("Zadej matici s rozmery 3x3:\n"); */
/*     nactiPole2D(stdin, 3, 3, pole); */
/*     vypisPole2D(stdout, 3, 3, pole); */
    
/*     // Testovaci pole vytisk */
/*     /1* vypisPole2D(stdout, poleTestovaci, 3, 3); *1/ */


/*     // ze souboru */
/*     /1* FILE * f = fopen("matice.txt", "r"); *1/ */
/*     /1* if (f == NULL) { *1/ */
/*     /1*     printf("Nepodařilo se otevřít soubor\n"); *1/ */
/*     /1*     return -1; *1/ */
/*     /1* } *1/ */
/*     /1* nactiPole2D(f, pole, 3, 3); *1/ */
/*     /1* /2* vypisPole2D(stdout, pole, 3, 3); *2/ *1/ */
/*     /1* vypisPole2D(stdout, 3, 3, pole); *1/ */
/*     /1* fclose(f); *1/ */

/*     return 0; */
/* } */
