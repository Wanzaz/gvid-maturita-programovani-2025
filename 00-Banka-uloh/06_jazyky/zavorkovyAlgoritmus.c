#include <stdio.h>
#include <stdbool.h>


// Vytvoř logickou funkci, která zjistí, zda v zadaném textovém řetězci/na vstupu
// odpovídá počet levých a pravých hranatých závorek []. Funkce musí zároveň ově-
// řit, zda jsou závorky správně zanořeny. Například toto je správně „[a]b[ ][c[]d]e“, ale toto „a[b]c]d[e[f]g]“ správně není. Význam ostatních znaků neřeš.

// Vytvoření logické funkce, která zjistí, zda jsou závorky správně uzavřeny a zanořeny.
bool spravneUzavreneHranateZavorky(FILE *in) {
    int znak;
    int hloubka = 0;

    while ((znak = fgetc(in)) != EOF) {
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


// Vytvoř logickou funkci jako v minulé úloze, ale nevíc ber v úvahu i jiné typy závorek: kulaté (), složené {}, úhlové <>.
char uzaviraci(char zavorka)
{
    switch (zavorka) {
        case '[': return ']'; break;
        case '{': return '}'; break;
        case '<': return '>'; break;
        case '(': return ')'; break;
        default: return zavorka;
    }
}

bool jeZaviraci(char zavorka)
{
    return 
        zavorka == ']'
        || zavorka == '}'
        || zavorka == '>'
        || zavorka == ')';
}

bool zavorkyFull(FILE* vstup, char konec)
{
    char c;
    char zavorka;
    while ((c = fgetc(vstup)) != konec) {
        if (c == EOF) {
            return false;
        }

        if (jeZaviraci(c)) {
            return false;
        }

        zavorka = uzaviraci(c); // Např. '(' → ')'
        if (zavorka == c) {
            continue; // Není otevírací závorka – ignorujeme
        }

        if (!zavorkyFull(vstup, zavorka)) {
            return false;
        }
        
    }

    return true;
}

/* Volání 1: zavorkyFull(vstup, '\n')   ← hlavní volání */
/*   čte: '{'                          → zavorka = '}' */
/*   zanořuje se do: */

/*     Volání 2: zavorkyFull(vstup, '}')   ← kvůli '{' */
/*       čte: '['                        → zavorka = ']' */
/*       zanořuje se do: */

/*         Volání 3: zavorkyFull(vstup, ']')   ← kvůli '[' */
/*           čte: '('                      → zavorka = ')' */
/*           zanořuje se do: */

/*             Volání 4: zavorkyFull(vstup, ')')   ← kvůli '(' */
/*               čte: ')'                  → znak == konec → ✅ návrat true */

/*           návrat true z Volání 4 */
/*           čte: ']'                      → znak == konec → ✅ návrat true */

/*       návrat true z Volání 3 */
/*       čte: '}'                          → znak == konec → ✅ návrat true */

/*   návrat true z Volání 2 */

/* návrat true z Volání 1 → 🎉 Závorky jsou správně uzavřené */

int main() {
    printf("Zadej retezec: ");
    /* if (spravneUzavreneHranateZavorky(stdin)) { */
    /*     printf("Spravne zadane parove zavorky []\n"); */
    /* } else { */
    /*     printf("Nespravne zadane parove zavorky []\n"); */
    /* } */


    if (zavorkyFull(stdin, EOF)) {
        printf("Spravne zadane parove zavorky\n");
    } else {
        printf("Nespravne zadane parove zavorky\n");
    }

    return 0;
}
