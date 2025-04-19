#include <stdio.h>
#include <stdlib.h>


// čti ze vstupu řadu číselných hodnot předem neznámé délky (až do konce vstupu – EOF) a vypiš posledních N hodnot, součet posledních N hodnot, vypiš posledních N hodnot v opačném pořadí


#define UINT unsigned int
#define N 5

// Funkce pro kruhové indexování
UINT modulo(UINT x, UINT n) {
    return x % n;
}

UINT nactiZeSouboru(FILE *f, int buffer[]) {
    UINT pocetNactenych = 0;
    int num;

    while (fscanf(f, "%d", &num) == 1) {
        buffer[modulo(pocetNactenych, N)] = num;
        pocetNactenych++;
    }

    return pocetNactenych;
}

// Vypisuje posledních N hodnot
void vypisPoslednichNHodnot(FILE *f, int buffer[], UINT pocetNactenych, UINT pocetPoslednich) {
    for (UINT i = 0; i < pocetPoslednich; i++) {
        UINT idx = modulo(pocetNactenych - pocetPoslednich + i, N);
        fprintf(f, "%d ", buffer[idx]);
    }
}

// Vypisuje posledních N hodnot v opačném pořadí
void vypisPoslednichNHodnotObracene(FILE *f, int buffer[], UINT pocetNactenych, UINT pocetPoslednich) {
    for (UINT i = 0; i < pocetPoslednich; i++) {
        UINT idx = modulo(pocetNactenych - i - 1, N);
        fprintf(f, "%d ", buffer[idx]);
    }
}

// Počítá součet posledních N hodnot
int soucetPoslednichNHodnot(int buffer[], UINT pocetNactenych, UINT pocetPoslednich) {
    int sum = 0;
    for (UINT i = 0; i < pocetPoslednich; i++) {
        UINT idx = modulo(pocetNactenych - pocetPoslednich + i, N);
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

    int buffer[N] = {0};
    UINT pocetNactenych = nactiZeSouboru(f, buffer);
    fclose(f);

    if (pocetNactenych == 0) {
        printf("Nebyla nalezena žádná čísla nebo soubor je prázdný.\n");
        return 0;
    }

    UINT pocetKZobrazeni = (pocetNactenych < N) ? pocetNactenych : N;

    printf("Posledních %u hodnot: ", pocetKZobrazeni);
    vypisPoslednichNHodnot(stdout, buffer, pocetNactenych, pocetKZobrazeni);
    printf("\n");

    printf("Posledních %u hodnot obráceně: ", pocetKZobrazeni);
    vypisPoslednichNHodnotObracene(stdout, buffer, pocetNactenych, pocetKZobrazeni);
    printf("\n");

    printf("Součet posledních %u hodnot: %d\n", pocetKZobrazeni, soucetPoslednichNHodnot(buffer, pocetNactenych, pocetKZobrazeni));

    return 0;
}

