/* Téma matice a moduly - varianta s polem pevných rozměrů
 *
 * Autor: Ondrej Pazourek
 * Datum: 30.11.2024
 *
 * Verze: 2.1
 * Errata:
 * - maticeVymenRadky: viz záhlaví souboru matice.h
 * - maticeCtiZeSouboru: viz záhlaví souboru matice.h
 * - maticeCtiZeVstupu: viz záhlaví souboru matice.h
 * - testFileRW: Opraveno nesmyslné alokování prázdné matice před čtením
 *   ze souboru.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include <time.h>

#include "matice.h"


bool rozmery(int radku, int sloupcu) {
     return radku > 0 && radku <= MATICE_MAX_VELIKOST &&
        sloupcu > 0 && sloupcu <= MATICE_MAX_VELIKOST &&
        radku + 1 == sloupcu;
}

Tmatice * maticeCtiZeSouboruManualne(FILE *file)
{
    int radku, sloupcu;
    if (fscanf(file, "%d %d", &radku, &sloupcu) != 2) {
        printf("Doslo k chybe pri cteni rozmeru matice\n");
        exit(-1);
    }

    if (!rozmery(radku, sloupcu)) {
        printf("Spatne rozmery m x n matice\n");
        exit(-1);
    }

    Tmatice *m = malloc(sizeof(Tmatice));

    if (m == NULL) {
        printf("Nepodarilo se alokovat matici\n");
        exit(-1);
    }

    m->radku = radku;
    m->sloupcu = sloupcu;



    for (int r = 0; r < m->radku ; r++) {
        for (int s = 0; s < m->sloupcu ; ++s) {
            if (fscanf(file, "%f", &m->prvek[r][s]) != 1) {
                printf("Chyba pri nacitani matice\n");
                exit(-1);
            }
        }
    }

    return m;
}


bool jeDDM(Tmatice *m)
{
    for (int r = 0; r < m->radku; ++r) {
        float sum = 0.0;
        for (int s = 0; s < m->sloupcu - 1; ++s) {
            if (s != r) {
                sum += fabs(m->prvek[r][s]);
            }
        }

        if (fabs(m->prvek[r][r]) <= sum) {
            return false;
        }
    }

    return true;
}

void upravaMatice(Tmatice *m)
{
    for (int r = 0; r < m->radku; ++r) {
        for (int s = 0; s < m->sloupcu; ++s) {
            if (r != s) {
                m->prvek[r][s] /= m->prvek[r][r]; // vydelime kazdy prvek diagonalnim prvkem
            }
        }
        m->prvek[r][r] = 0.0;
    }
}

// Neni uz moc potreba kvuli tomu, ze to delame v upraveMatice
void nulovaniDiagonaly(Tmatice *m)
{
    for(int r = 0; r < m->radku; r++)
    {
        m->prvek[r][r] = 0.0;
    }
}


void gaussSeidlova(Tmatice *m, float eps, Tmatice *x) // x muze byt i jen 1D pole a nemusi byt zbytecne 2D pole
{
    bool jePresny = false; // na zacatku zaciname pesimisticky
    float xpred = 0.0;
    float sum = 0.0;

    while (!jePresny) {
        jePresny = true; // na zacatku kazde iterace - nastavit optimisticky
        for (int r = 0; r < m->radku; ++r) { // kazdy radek matice -> pocitame Xr
            xpred = x->prvek[r][0];

            for (int s = 0; s < m->sloupcu - 1; ++s) {
                sum += m->prvek[r][s] * x->prvek[s][0]; // používají staré hodnoty x pro všechny prvky x, kromě aktuálního řádku r
            }

            x->prvek[r][0] = m->prvek[r][m->sloupcu - 1] - sum; // nova hodnota podle vzorce

            sum = 0.0;
            jePresny = jePresny && (fabs(x->prvek[r][0] - xpred) < eps);
        }
    }
}

void jacobiho(Tmatice *m, float eps, Tmatice *xpred)
{
    Tmatice *xnovy = maticeAlokuj(m->radku, 1); // 1D pole
    if (xnovy == NULL) {
        printf("\nChyba pri alokaci pomocne matice.\n");
        return;
    }

    bool jePresny = false; // na zacatku zaciname pesimisticky
    float sum = 0.0;

    while (!jePresny){ // stejne jako gs metoda
        jePresny = true;

        for (int r = 0; r < m->radku; ++r){
            for (int s = 0; s < m->sloupcu - 1; ++s) {
                sum += m->prvek[r][s] * xpred->prvek[s][0];
            }

            xnovy->prvek[r][0] = m->prvek[r][m->sloupcu - 1] - sum; // priradit novou hodnotu podle vzorce
            sum = 0.0;

            jePresny = jePresny && fabs(xnovy->prvek[r][0] - xpred->prvek[r][0]) < eps;
        }

        for (int r = 0; r < m->radku; r++) {
            xpred->prvek[r][0] = xnovy->prvek[r][0]; // Po kazde iteraci prepisovani predchozich vysledku novymi
        }
    }

    maticeUvolni(xnovy);
}

void tiskReseni(Tmatice *m)
{
    for(int r = 0; r < m->radku; r++){
        printf("x%d = %.7f\n", r, m->prvek[r][0]);
    }
}


void testJ(char * adresaSouboru, float eps)
{
    printf("------ Jacobiho metoda ------\n");
    FILE* f = fopen(adresaSouboru,"r");
    if(f == NULL){
        printf("\nChyba pri otevirani souboru.\n");
        return;
    }

    Tmatice *m = maticeCtiZeSouboru(f);
    fclose(f);

    if(m == NULL){
        printf("\nChyba pri alokaci matice.\n");
        return;
    }

    Tmatice * x = maticeAlokuj(m->radku, 1);
    if(x == NULL){
        printf("\nChyba pri alokaci vysledkove matice.\n");
        return;
    }
    inicializujMatici(x, 0.0);

    maticeTiskni(m);

    if(!jeDDM(m)){
        printf("\nMatice neni DDM.\n");
        return;
    }

    upravaMatice(m);
    nulovaniDiagonaly(m);
    jacobiho(m, eps, x);

    tiskReseni(x);
    maticeUvolni(x);
    maticeUvolni(m);
}


void testGS(char * adresaSouboru, float eps)
{
    printf("------ Gauss-Seidelova metoda ------\n");
    FILE* f = fopen(adresaSouboru,"r");
    if(f == NULL){
        printf("\nChyba pri otevirani souboru.\n");
        return;
    }

    Tmatice *m = maticeCtiZeSouboru(f);
    fclose(f);

    if(m == NULL){
        printf("\nChyba pri alokaci matice.\n");
        return;
    }

    Tmatice * x = maticeAlokuj(m->radku, 1);
    if(x == NULL){
        printf("\nChyba pri alokaci vysledkove matice.\n");
        return;
    }
    inicializujMatici(x, 0.0);

    maticeTiskni(m);

    if(!jeDDM(m)){
        printf("\nMatice neni DDM.\n");
        return;
    }

    upravaMatice(m);
    nulovaniDiagonaly(m);
    gaussSeidlova(m, eps, x);

    tiskReseni(x);
    maticeUvolni(x);
    maticeUvolni(m);
}

void testDDM(char *adresaSouboru)
{
    FILE* f = fopen(adresaSouboru,"r");
    if(f == NULL){
        printf("\nChyba pri otevirani souboru.\n");
        return;
    }

    Tmatice * m = maticeCtiZeSouboru(f);
    fclose(f);

    if(m == NULL){
        printf("Chyba pri zpracovani matice.\n");
        return;
    }

    maticeTiskni(m);

    printf("\nMatice %s\n", jeDDM(m) ? "je DDM." : "neni diagonalne dominantni.");

    upravaMatice(m);
    maticeTiskni(m);

    maticeUvolni(m);
}


int main(void)
{
    float eps = 0.001;
    // testDDM("B.txt");
    testGS("A.txt", eps);
    printf("\n====================================================\n\n");
    testJ("A.txt", eps);

    return EXIT_SUCCESS;
}
