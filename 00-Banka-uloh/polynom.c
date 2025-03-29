#include <stdio.h>

// načti ze vstupu stupeň a koeficienty polynomu, dále načti hodnotu x a vypočítej Hornerovým schématem hodnotu polynomu v daném bodě

void nactiPolynom(FILE *f, int koef[], int stupen)
{
    for (int i = 0; i <= stupen; i++) {
        fscanf(f, "%d", &koef[i]); // POZOR ne naivne "%d " - BEZ MEZERY
    }
}

void vytiskniPolynom(FILE *f, int koef[], int stupen)
{
    for (int i = 0; i <= stupen; i++) {
        fprintf(f, "%d ", koef[i]);
    }
}

int horner(int koef[], int x, int stupen)
{
    int sum = 0;
    for (int i = 0; i <= stupen; i++) {
        sum = sum*x + koef[i];
    }

    return sum;
}


int main(int argc, char *argv[])
{
    int koef[100];
    int stupen;
    int x;


    printf("Zadej stupen polynomu: ");
    scanf("%d", &stupen);
    printf("Zadej bod pro vycisleni: ");
    scanf("%d", &x);
    printf("\nZadej koeficienty polynomu: \n");
    nactiPolynom(stdin, koef, stupen);

    printf("Vycisleni polynomu v bode %d: %d\n", x, horner(koef, x, stupen));
    /* vytiskniPolynom(stdout, koef, stupen); */

    return 0;
}
