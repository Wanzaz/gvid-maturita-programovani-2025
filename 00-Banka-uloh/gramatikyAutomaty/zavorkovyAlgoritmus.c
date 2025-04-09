#include <stdio.h>
#include <stdbool.h>


// Vytvoř logickou funkci, která zjistí, zda v zadaném textovém řetězci/na vstupu
// odpovídá počet levých a pravých hranatých závorek []. Funkce musí zároveň ově-
// řit, zda jsou závorky správně zanořeny. Například toto je správně „[a]b[ ][c[]d]e“, ale toto „a[b]c]d[e[f]g]“ správně není. Význam ostatních znaků neřeš.





// Vytvoření logické funkce, která zjistí, zda jsou závorky správně uzavřeny a zanořeny.
enum Estavy {TEXT, KOMENTAR};

bool spravneUzavreneHranateZavorky() {
    // Proměnná pro uchování vstupních znaků
    int znak;
    // Stavová proměnná pro kontrolu párování závorek
    enum Estavy stav = TEXT;

    while ((znak = getchar()) != EOF) { // Čteme až do konce vstupu
        switch (stav) {
            case TEXT:
                if (znak == '[') { 
                    stav = KOMENTAR;  // Přepneme do stavu KOMENTAR, kde očekáváme uzavření
                }
                break;

            case KOMENTAR:
                if (znak == ']') {
                    stav = TEXT;  // Po uzavření závorky přecházíme zpět do stavu TEXT
                }
                break;
        }
    }

    // Pokud máme stále otevřené závorky, znamená to, že nebyly správně uzavřeny
    if (stav != TEXT) {
        return false;
    }

    return true;
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
