#include <stdio.h>
#include <stdlib.h>

// čti ze vstupu řadu číselných hodnot předem neznámé délky (až do konce vstupu – EOF) a vypiš posledních N hodnot, součet posledních N hodnot, vypiš posledních N hodnot v opačném pořadí

#define N 5

// Načítá čísla ze souboru do cyklického bufferu s kontrolou EOF
int nactiZeSouboru(FILE *f, int buffer[], int *start) {
    int count = 0, num;

    while (fscanf(f, "%d", &num) == 1) {
        buffer[(*start + count) % N] = num;
        if (count < N) {
            count++;
        } else {
            *start = (*start + 1) % N; // Posuneme start, pokud překročíme N prvků
        }
    }

    // Pokud jsme dosáhli EOF, ale nic jsme nenacetli, vracíme 0
    if (count == 0 && feof(f)) {
        return 0;
    }

    return count;
}

// Vypisuje posledních N hodnot
void vypisPoslednichNHodnot(FILE *f, int buffer[], int start, int count, int n) {
    int valid_n = (n < count) ? n : count; 
    for (int i = 0; i < valid_n; i++) {
        fprintf(f, "%d ", buffer[(start + i) % N]);
    }
}

// Vypisuje posledních N hodnot v opačném pořadí
void vypisPoslednichNHodnotObracene(FILE *f, int buffer[], int start, int count, int n) {
    int valid_n = (n < count) ? n : count;
    for (int i = valid_n - 1; i >= 0; i--) {
        fprintf(f, "%d ", buffer[(start + i) % N]);
    }
}

// Počítá součet posledních N hodnot
int soucetPoslednichNHodnot(int buffer[], int start, int count, int n) {
    int sum = 0;
    int valid_n = (n < count) ? n : count;
    for (int i = 0; i < valid_n; i++) {
        sum += buffer[(start + i) % N];
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
    int start = 0;
    int count = nactiZeSouboru(f, buffer, &start);

    fclose(f);

    if (count == 0) {
        printf("Nebyla nalezena žádná čísla nebo soubor je prázdný.\n");
        return 0;
    }

    printf("Posledních %d hodnot: ", N);
    vypisPoslednichNHodnot(stdout, buffer, start, count, N);
    printf("\n");

    printf("Posledních %d hodnot obráceně: ", N);
    vypisPoslednichNHodnotObracene(stdout, buffer, start, count, N);
    printf("\n");

    printf("Součet posledních %d hodnot: %d\n", N, soucetPoslednichNHodnot(buffer, start, count, N));

    return 0;
}

