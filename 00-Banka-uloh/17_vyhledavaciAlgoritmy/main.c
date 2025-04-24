#include <stdio.h>
#include <stdbool.h>


/* typedef struct { */
/*     int klic; */
/*     char jmeno[50]; */
/* }Tpolozka; */

/* Načti ze vstupu pole N celých čísel a hledanou hodnotu (ze vstupu nebo přes parametr */
/* příkazového řádku. */
/* • Vytvoř podprogram, který v tomto poli vyhledá zadanou hodnotu algoritmem */
/* ◦ sekvenčního hledání bez zarážky / se zarážkou v neseřazeném poli */
/* • Ověř pomocí své funkce, zda je vstupní pole seřazeno. Vytvoř podprogram pro */
/* vyhledání v tomto poli algoritmem */
/* ◦ sekvenčního hledání bez zarážky / se zarážkou v seřazeném poli */
/* ◦ binárního vyhledávání */

#include <stdio.h>
#include <stdbool.h>

typedef struct _pole {
    int delka;
    int prvek[51];  // prostor pro zarážku navíc
    int hledany;
} Tpole;

int nactiHledaneCislo(const char *zprava) {
    int cislo;
    printf("%s", zprava);
    scanf("%d", &cislo);
    return cislo;
}

void nactiPole(FILE* f, Tpole *p) {
    fscanf(f, "%d", &p->delka);
    for (int i = 0; i < p->delka; i++) {
        fscanf(f, "%d", &p->prvek[i]);
    }
    p->hledany = nactiHledaneCislo("Zadej hledanou hodnotu: ");
}

int sekvencniVyhledavaniBezZarazky(const Tpole p) {
    int i = 0;
    while (i < p.delka && p.hledany != p.prvek[i]) {
        i++;
    }
    return (i < p.delka) ? i : -1;
}

int sekvencniVyhledavaniSeZarazkou(Tpole p) {
    p.prvek[p.delka] = p.hledany;  // zarážka
    int i = 0;
    while (p.hledany != p.prvek[i]) {
        i++;
    }
    return (i < p.delka) ? i : -1;
}

bool jePoleSerazene(const Tpole p) {
    for (int i = 0; i < p.delka - 1; i++) {
        if (p.prvek[i] > p.prvek[i + 1]) {
            return false;
        }
    }
    return true;
}

int sekvencniVyhledavaniVSerazenem(const Tpole p) {
    int i = 0;
    while (i < p.delka && p.prvek[i] < p.hledany) {
        i++;
    }
    if (i < p.delka && p.prvek[i] == p.hledany) {
        return i;
    }
    return -1;
}

int binarniVyhledavani(const Tpole pole, int l, int p) {
    while (l <= p) {
        int s = (l + p) / 2;
        if (pole.prvek[s] == pole.hledany) {
            return s;
        }
        if (pole.prvek[s] < pole.hledany) {
            l = s + 1;
        } else {
            p = s - 1;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    Tpole p = {
        .delka = 5,
        .prvek = {3, 4, 10, 15, 50},
        .hledany = 4
    };

    printf("=== Sekvenční vyhledávání bez zarážky ===\n");
    int index1 = sekvencniVyhledavaniBezZarazky(p);
    printf("Výsledek: %d\n", index1);

    printf("=== Sekvenční vyhledávání se zarážkou ===\n");
    int index2 = sekvencniVyhledavaniSeZarazkou(p);
    printf("Výsledek: %d\n", index2);

    if (jePoleSerazene(p)) {
        printf("=== Pole je seřazené ===\n");

        printf("=== Sekvenční vyhledávání v seřazeném ===\n");
        int index3 = sekvencniVyhledavaniVSerazenem(p);
        printf("Výsledek: %d\n", index3);

        printf("=== Binární vyhledávání ===\n");
        int index4 = binarniVyhledavani(p, 0, p.delka - 1);
        printf("Výsledek: %d\n", index4);
    } else {
        printf("Pole není seřazené – přeskočeno binární/seřazené hledání.\n");
    }

    return 0;
}

