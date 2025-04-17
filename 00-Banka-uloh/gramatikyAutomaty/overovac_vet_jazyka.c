#include <stdio.h>
#include <stdbool.h>

// Je dána množina znaků Σ (zadá uživatel). Napiš funkci, která ověří, zda se na vstupu/v textovém řetězci nachází pouze věta jazyka Σ* (případně Σ+) a vrátí po-
// zici prvního místa, které již do zadaného jazyka nepatří. Pozice vstupu počítej od hodnoty 1 a v případě, že celý vstup patří do tohoto jazyka, vrať nulu.

#define N 50

typedef struct {
    char znak[N];
} TRetezec;



int overeniVetJazyka(TRetezec mnozinaZnaku, TRetezec r)
{
    bool nalezen;
    for (int i = 0; r.znak[i] != '\0'; i++) {
        nalezen = false;
        for (int j = 0 ; mnozinaZnaku.znak[j] != '\0'; j++) {
            if (r.znak[i] == mnozinaZnaku.znak[j]) { // || r.znak[i] == ' '
                nalezen = true;
            }
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
