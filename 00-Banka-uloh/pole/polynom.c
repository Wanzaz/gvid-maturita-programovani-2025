#include <stdio.h>

typedef struct _polynom {
    int stupen;
    int koef[50];
} TPolynom;

// načti ze vstupu stupeň a koeficienty polynomu, dále načti hodnotu x a vypočítej Hornerovým schématem hodnotu polynomu v daném bodě

void nactiPolynom(FILE *f, TPolynom* p)
{
    fscanf(f, "%d", &p->stupen); // Nejprve načteme stupeň!
    for (int i = 0; i <= p->stupen; i++) {
        fscanf(f, "%d", &p->koef[i]); // POZOR ne naivne "%d " - BEZ MEZERY
    }
}

void vytiskniPolynom(FILE *f, TPolynom p)
{
    for (int i = 0; i <= p.stupen; i++) {
        fprintf(f, "%d ", p.koef[i]);
    }
}

int horner(TPolynom p, int x)
{
    int sum = 0;
    for (int i = 0; i <= p.stupen; i++) {
        sum = sum*x + p.koef[i];
    }

    return sum;
}


int main(int argc, char *argv[])
{
    TPolynom p;
    int x;


    printf("Zadej bod pro vycisleni: ");
    scanf("%d", &x);
    printf("\nZadej stupen polynomu a koeficienty polynomu: \n");
    nactiPolynom(stdin, &p);

    printf("Vycisleni polynomu v bode %d: %d\n", x, horner(p, x));

    return 0;
}
