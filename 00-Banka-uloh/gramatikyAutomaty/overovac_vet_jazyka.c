#include <stdio.h>
#include <stdbool.h>

// Je dána množina znaků Σ (zadá uživatel). Napiš funkci, která ověří, zda se na vstupu/v textovém řetězci nachází pouze věta jazyka Σ* (případně Σ+) a vrátí po-
// zici prvního místa, které již do zadaného jazyka nepatří. Pozice vstupu počítej od hodnoty 1 a v případě, že celý vstup patří do tohoto jazyka, vrať nulu.

#define N 50

typedef struct {
    char znak[N];
} TRetezec;



// Majkluv zpusob: 
bool jeVPoli1(char pole[], int pocet, char znak)
{
    for (int i = 0; i < pocet; i++) {
        if (pole[i] == znak) {
            return true;
        }
    }

    return false;
}

int jeVeta(char sigma[], int pocetZnaku, FILE* vstup, char konec)
{
    char c;
    int i = 0;
    while ((c = fgetc(vstup)) != konec) {
        if (!jeVPoli1(sigma, pocetZnaku, c)) {
            return i;
        }
        i++;
    }

    return -1;
}
// :Majkluv zpusob

bool jeVPoli(TRetezec pole, char znak)
{
    for (int i = 0; i < N; i++) {
        if (pole.znak[i] == znak) {
            return true;
        }
    }

    return false;
}

int overeniVetJazyka(TRetezec sigma, TRetezec r)
{
    bool nalezen;
    for (int i = 0; r.znak[i] != '\0'; i++) {
        nalezen = false;
        if (jeVPoli(sigma, r.znak[i])) {
            nalezen = true;
        }

        if (!nalezen) {
            return i + 1; // indexovani od 1
        }
    }


    return 0;
}

int main(int argc, char *argv[])
{
    TRetezec abeceda;
    /* printf("Zadej abecedu jazyka: "); */
    /* scanf("%49s", abeceda.znak); */

    printf("Zadej abecedu jazyka (muze obsahovat mezeru): ");
    fgets(abeceda.znak, N, stdin);
    // odstraneni '\n' z konce
    for (int i = 0; abeceda.znak[i] != '\0'; i++) {
        if (abeceda.znak[i] == '\n') {
            abeceda.znak[i] = '\0';
            break;
        }
    }

    TRetezec retezec = {'a', 'b', 'c'};

    int overeni = overeniVetJazyka(abeceda, retezec);
    if (overeni == 0) {
        printf("Retezec: %s je vetou jazyka\n", retezec.znak);
    } else {
        printf("Retezec: %s neni vetou jazyka, chyba je na indexu %d\n", retezec.znak, overeni);
    }

    return 0;
}
