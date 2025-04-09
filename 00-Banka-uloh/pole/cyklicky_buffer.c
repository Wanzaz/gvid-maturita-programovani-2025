#include <stdio.h>
#include <stdlib.h>

// čti ze vstupu řadu číselných hodnot předem neznámé délky (až do konce vstupu – EOF) a vypiš posledních N hodnot, součet posledních N hodnot, vypiš posledních N hodnot v opačném pořadí

#define N 5


// Kruhovy seznam, princip kruhove indexace
int modulo(int x, int n)
{
    int m = x % n;
    if (m < 0) {
        return (n < 0) ? m - n : m + n; // n < 0 vzacny pripad
    }

    return m;
}

int nactiZeSouboru(FILE *f, int buffer[]) {
    int pocetNactenych = 0;
    int num;

    while (fscanf(f, "%d", &num) == 1) {
        buffer[modulo(pocetNactenych, N)] = num;
        pocetNactenych++;
    }

    return pocetNactenych;
}

// Vypisuje posledních N hodnot
void vypisPoslednichNHodnot(FILE *f, int buffer[], int pocetNactenych, int pocetPoslednich) {
    int idx;
    for (int i = 0; i < pocetPoslednich; i++) {
        idx = modulo(pocetNactenych - pocetPoslednich + i, N);
        fprintf(f, "%d ", buffer[idx]);
    }
}

// Vypisuje posledních N hodnot v opačném pořadí
void vypisPoslednichNHodnotObracene(FILE *f, int buffer[], int pocetNactenych, int pocetPoslednich) {
    int idx;
    for (int i = pocetPoslednich - 1; i >= 0; i--) {
        idx = modulo(pocetNactenych - pocetPoslednich + i, N);
        fprintf(f, "%d ", buffer[idx]);
    }
}

// Počítá součet posledních N hodnot
int soucetPoslednichNHodnot(int buffer[], int pocetNactenych, int pocetPoslednich) {
    int idx;
    int sum = 0;

    for (int i = 0; i < pocetPoslednich; i++) {
        idx = modulo(pocetNactenych - pocetPoslednich + i, N);
        sum += buffer[idx];
    }

    return sum;
}

int main() {
    FILE *f = fopen("rada_cisel.txt", "r");
    if (f == NULL) {
        perror("Chyba při otevírání souboru");
        return -1;
    }

    int buffer[N] = {0}; // Cyklující buffer
    int pocetNactenych = nactiZeSouboru(f, buffer);

    fclose(f);

    if (pocetNactenych == 0) {
        printf("Nebyla nalezena žádná čísla nebo soubor je prázdný.\n");
        return 0;
    }

    printf("Posledních %d hodnot: ", N);
    vypisPoslednichNHodnot(stdout, buffer, pocetNactenych, N);
    printf("\n");

    printf("Posledních %d hodnot obráceně: ", N);
    vypisPoslednichNHodnotObracene(stdout, buffer, pocetNactenych, N);
    printf("\n");

    printf("Součet posledních %d hodnot: %d\n", N, soucetPoslednichNHodnot(buffer, pocetNactenych, N));

    return 0;
}

