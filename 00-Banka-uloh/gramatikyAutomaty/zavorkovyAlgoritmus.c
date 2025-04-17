#include <stdio.h>
#include <stdbool.h>


// Vytvoř logickou funkci, která zjistí, zda v zadaném textovém řetězci/na vstupu
// odpovídá počet levých a pravých hranatých závorek []. Funkce musí zároveň ově-
// řit, zda jsou závorky správně zanořeny. Například toto je správně „[a]b[ ][c[]d]e“, ale toto „a[b]c]d[e[f]g]“ správně není. Význam ostatních znaků neřeš.





// Vytvoření logické funkce, která zjistí, zda jsou závorky správně uzavřeny a zanořeny.
bool spravneUzavreneHranateZavorky() {
    int znak;
    int hloubka = 0;

    while ((znak = getchar()) != EOF && znak != '\n') {
        if (znak == '[') {
            hloubka++;
        } else if (znak == ']') {
            hloubka--;
            if (hloubka < 0) {
                return false; // více pravých než levých závorek
            }
        }
    }

    return hloubka == 0; // všechny závorky musí být uzavřené
}

int main() {
    printf("Zadej retezec: ");
    if (spravneUzavreneHranateZavorky()) {
        printf("Spravne zadane parove zavorky []\n");
    } else {
        printf("Nespravne zadane parove zavorky []\n");
    }

    return 0;
}
