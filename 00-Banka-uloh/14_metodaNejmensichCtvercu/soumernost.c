#include <stdio.h>
#include <stdbool.h>

#define N 50

typedef struct _matice {
    int delka;
    float prvek[N][N];
} Tmatice;


/* Načti ze vstupu čtvercovou matici. Ověř, zda je matice souměrná podle */
/* ◦ hlavní/vedlejší diagonály */
/* ◦ vodorovné/svislé osy */



bool soumernaPodleHlavniDiagonaly(Tmatice m)
{
    for (int i = 0; i < m.delka; i++) {
        for (int j = 0; j < m.delka; j++) {
            if (i == j) {
                continue;;
            }

            if (m.prvek[i][j] != m.prvek[j][i]) {
                return false;
            }
        }
    }

    return true;
}

bool soumernaPodleVedlejsiDiagonaly(Tmatice m)
{
    for (int i = 0; i < m.delka; i++) {
        for (int j = 0; j < m.delka; j++) {
            if (i == m.delka - j - 1) {
                continue;;
            }

            if (m.prvek[i][m.delka - j - 1] != m.prvek[j][m.delka - i - 1]) {
                return false;
            }
        }
    }

    return true;
}

bool soumernaPodleSvisleOsy(Tmatice m)
{
    for (int i = 0; i < m.delka; i++) {
        for (int j = 0; j < m.delka/2; j++) {
            if (m.prvek[i][j] != m.prvek[i][m.delka - j - 1]) {
                return false;
            }
        }
    }

    return true;
}

bool soumernaPodleVododorovneOsy(Tmatice m)
{
    for (int i = 0; i < m.delka/2; i++) {
        for (int j = 0; j < m.delka; j++) {
            if (m.prvek[i][j] != m.prvek[m.delka - i - 1][j]) {
                return false;
            }
        }
    }

    return true;
}

bool nactiCtvercovouMatici(FILE* f, Tmatice* m)
{
    if (fscanf(f, "%d", &m->delka)) {
        return false;
    }

    for (int i = 0; i < m->delka; i++) {
        for (int j = 0; j < m->delka; j++) {
            if (fscanf(f, "%f", &m->prvek[i][j]) != 1) {
                return false;
            }
        }
    }
    return true;
}


int main(int argc, char *argv[])
{
    Tmatice m = {
        .delka = 4,
        .prvek = {
            {4, 4, 4, 4},
            {4, 4, 4, 4},
            {4, 4, 4, 4},
            {4, 4, 4, 4}
        }
    };

    if (soumernaPodleHlavniDiagonaly(m)) {
        printf("Matice je soumerna podle hlavni diagonaly\n");
    }
    if (soumernaPodleVedlejsiDiagonaly(m)) {
        printf("Matice je soumerna podle vedlejsi diagonaly\n");
    }
    if (soumernaPodleVododorovneOsy(m)) {
        printf("Matice je soumerna podle hlavni diagonaly\n");
    }
    if (soumernaPodleSvisleOsy(m)) {
        printf("Matice je soumerna podle vedlejsi diagonaly\n");
    }

    return 0;
}
