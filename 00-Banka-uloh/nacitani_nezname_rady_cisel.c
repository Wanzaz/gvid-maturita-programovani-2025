#include <stdio.h>



// čti ze vstupu řadu číselných hodnot předem neznámé délky (až do konce vstupu – EOF) a vypiš posledních N hodnot, součet posledních N hodnot, vypiš posledních N hodnot v opačném pořadí


int nacitaniZeSouboruDelka(FILE* f, int pole[])
{
    int i = 0;
    while ((fscanf(f, "%d", &pole[i])) == 1) {
        i++;
    }

    return i;
}

void vypisPoslednichNHodnot(FILE *f, int pole[], int delka, int n)
{
    for (int i = delka - n; i < delka; i++) {
        fprintf(f, "%d ", pole[i]);
    }
}

void vypisPoslednichNHodnotObracene(FILE *f, int pole[], int delka, int n)
{
    for (int i = delka - 1; i >= delka - n; i--) {
        fprintf(f, "%d ", pole[i]);
    }
}

int soucetPoslednichNHodnot(int pole[], int delka, int n)
{
    int sum = 0;
    for (int i = delka - n; i < delka; i++) {
        sum += pole[i];
    }

    return sum;
}


int main(int argc, char *argv[])
{
    FILE * f = fopen("rada_cisel.txt", "r");
    if (f == NULL) {
        return -1;
    }

    int pole[100];
    int delka = nacitaniZeSouboruDelka(f, pole);
    int n = 5;

    vypisPoslednichNHodnot(stdout, pole, delka, n);
    printf("\n");
    vypisPoslednichNHodnotObracene(stdout, pole, delka, n);
    printf("Soucet poslednich %d hodnot: %d\n", n, soucetPoslednichNHodnot(pole, delka, n));


    fclose(f);
    return 0;
}
