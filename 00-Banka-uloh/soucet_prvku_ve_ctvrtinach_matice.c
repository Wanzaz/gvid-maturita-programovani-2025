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

// zjisti součet prvků ve čtvrtinách matice, když každý rozměr rozdělíš celočíselným dělením 2
//
// Prvni myslenka -> 4 funkce, kazda rozdilna ctvrtina
int sumHorniLevo(int n, int m, int pole[n][m])
{
    int sum = 0;
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < m/2; j++) {
            sum += pole[i][j];
        }
    }

    return sum;
}

int sumHorniPravo(int n, int m, int pole[n][m])
{
    int sum = 0;
    for (int i = 0; i < n/2; i++) {
        for (int j = m/2; j < m; j++) {
            sum += pole[i][j];
        }
    }

    return sum;
}

int sumDolniLevo(int n, int m, int pole[n][m])
{
    int sum = 0;
    for (int i = n/2; i < n; i++) {
        for (int j = 0; j < m/2; j++) {
            sum += pole[i][j];
        }
    }

    return sum;
}

int sumDolniPravo(int n, int m, int pole[n][m])
{
    int sum = 0;
    for (int i = n/2; i < n; i++) {
        for (int j = m/2; j < m; j++) {
            sum += pole[i][j];
        }
    }

    return sum;
}



// Jednodussi reseni
int sumCtvrtiny(int n, int m, int pole[n][m], int ctvrtina) {
    int sum = 0;

    int ri = (ctvrtina < 2) ? 0 : n / 2;        // řádkový index začátku
    int rf = (ctvrtina < 2) ? n / 2 : n;        // řádkový index konce
    int ci = (ctvrtina % 2 == 0) ? 0 : m / 2;   // sloupcový index začátku
    int cf = (ctvrtina % 2 == 0) ? m / 2 : m;   // sloupcový index konce

    for (int i = ri; i < rf; i++) {
        for (int j = ci; j < cf; j++) {
            sum += pole[i][j];
        }
    }

    return sum;
}

int main(int argc, char *argv[])
{
    int pole[4][4] = {
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4}
    };
    
    vypis2DPole(4, 4, pole);
    printf("\nHorni levo: %d\n", sumHorniLevo(4, 4, pole));
    printf("Horni pravo: %d\n", sumHorniPravo(4, 4, pole));
    printf("Dolni levo: %d\n", sumDolniLevo(4, 4, pole));
    printf("Dolni pravo: %d\n", sumDolniPravo(4, 4, pole));


    return 0;
}
