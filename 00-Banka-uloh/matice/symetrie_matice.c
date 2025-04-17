#include <stdio.h>
#include <stdbool.h>

typedef struct _matice {
    int radku;
    int sloupcu;
    int prvek[50][50];
} TMatice;


void nactiMatici(FILE *f, TMatice *m)
{
    if (fscanf(f, "%d%d", &m->radku, &m->sloupcu) != 2)  {
        return;
    }

    for (int i = 0; i < m->radku; i++) {
        for (int j = 0; j < m->sloupcu; j++) {
            if (fscanf(f, "%d", &m->prvek[i][j]) != 1)  {
                return;
            }
        }
    }
}

void vypisMatici(FILE *f, TMatice m)
{
    fprintf(f, "%d %d\n", m.radku, m.sloupcu);

    for (int i = 0; i < m.radku; i++) {
        for (int j = 0; j < m.sloupcu; j++) {
            fprintf(f, "%d ", m.prvek[i][j]);
        }
        fprintf(f, "\n");
    }
}


// zjisti, zda je matice vertikálně, či horizontálně symetrická
bool jeSymetricka(TMatice m, char typ) {
    if (typ == 'v') { // vertikální
        for (int i = 0; i < m.radku; i++)
            for (int j = 0; j < m.sloupcu / 2; j++)
                if (m.prvek[i][j] != m.prvek[i][m.sloupcu - j - 1]) return false;
    } else if (typ == 'h') { // horizontální
        for (int i = 0; i < m.radku / 2; i++)
            for (int j = 0; j < m.sloupcu; j++)
                if (m.prvek[i][j] != m.prvek[m.radku - i - 1][j]) return false;
    } else if (typ == 'd') { // diagonalne
        for (int i = 0; i < m.radku; i++)
            for (int j = i + 1; j < m.sloupcu; j++)
                if (m.prvek[i][j] != m.prvek[j][i]) return false;
    }
    return true;
}

// zjisti, zda je matice diagonalne symetricka
bool symetrickaDiagonalne(TMatice m)
{
    if (m.sloupcu != m.radku) {
        return false; // neni ctvercova matice
    }
    for (int i = 0; i < m.radku; i++) {
        for (int j = i + 1; j < m.sloupcu; j++) {
            if (m.prvek[i][j] != m.prvek[j][i]) {
                return false;
            }
        }
    }
    return true;
}

// zjisti, zda je matice vertikálně, či horizontálně symetrická
bool symetrickaVertikalne(TMatice m)
{
    for (int i = 0; i < m.radku; i++) {
        for (int j = 0; j < m.sloupcu/2; j++) {
            if (m.prvek[i][j] != m.prvek[i][m.sloupcu - j - 1]) {
                return false;
            }
        }
    }
    return true;
}

// zjisti, zda je matice vertikálně, či horizontálně symetrická
bool symetrickaHorizontalne(TMatice m)
{
    for (int i = 0; i < m.radku/2; i++) {
        for (int j = 0; j < m.sloupcu; j++) {
            if (m.prvek[i][j] != m.prvek[m.radku - i - 1][j]) {

                return false;
            }
        }
    }

    return true;
}

// zjisti, zda je matice vertikálně, či horizontálně symetrická
bool jeSymetrickaGeneral(TMatice m, char typ)
{
    if (typ == 'v') {
        return symetrickaVertikalne(m);
    } else if (typ == 'h') {
        return symetrickaHorizontalne(m);
    } else if (typ == 'd') {
        return symetrickaDiagonalne(m);
    }
    return false;  // Pokud je typ neznámý
}

int main(int argc, char *argv[])
{
    TMatice m = {
        .radku = 4,
        .sloupcu = 4,
        .prvek = {
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4}
        }
    };


    vypisMatici(stdout, m);
    if (jeSymetricka(m, 'v')) {
        printf("Symetricka vertikalne\n");
    }
    if (jeSymetricka(m, 'h')) {
        printf("Symetricka horizontalne\n");
    }
    if (jeSymetricka(m, 'd')) {
        printf("Symetricka diagonalne\n");
    }
    vypisMatici(stdout, m);


    return 0;
}

