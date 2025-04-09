#include <stdio.h>

// Je dána množina znaků Σ (zadá uživatel). Napiš funkci, která ověří, zda se na vstupu/v textovém řetězci nachází pouze věta jazyka Σ* (případně Σ+) a vrátí po-
// zici prvního místa, které již do zadaného jazyka nepatří. Pozice vstupu počítej od hodnoty 1 a v případě, že celý vstup patří do tohoto jazyka, vrať nulu.

#define N 50

typedef struct {
    char znak[N];
} TRetezec;



int overeniVetJazyka(TRetezec  mnozinaZnaku, TRetezec r)
{
    for (int i = 0; r.znak[i] != '\0'; i++) {
        for (int j = 0 ; mnozinaZnaku.znak[i] != '\0'; j++) {
            if (r.znak[i] != mnozinaZnaku.znak[j]) { // || r.znak[i] = ' '
                return i;
            }
        }
    }

    return 0;
}


void nactiRetezec(TRetezec *r)
{

}











int main(int argc, char *argv[])
{

    return 0;
}
