#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _prvek TPrvek;
typedef struct _fronta TFronta;

struct _prvek {
    float hodnota;
    TPrvek *dalsi;
};

struct _fronta {
    TPrvek *prvni;
    TPrvek *posledni;
    int delka;
    int max;
};

TFronta * inicializujFrontu(int max)
{
    TFronta *f = malloc(sizeof(TFronta));
    if (f == NULL) {
        return NULL;
    }

    f->prvni = NULL;
    f->posledni = NULL;
    f->delka = 0;
    f->max = max;

    return f;
}

bool enqueue(TFronta *f, float data)
{
    TPrvek *novy = malloc(sizeof(TPrvek));
    if (novy == NULL) {
        return false;
    }
    novy->hodnota = data;
    novy->dalsi = NULL;

    if (f->prvni == NULL) {
        f->prvni = novy;
        f->posledni = novy;
    } else {
        f->posledni->dalsi = novy;
        f->posledni = novy;
    }

    f->delka++;
    return true;
}

bool dequeue(TFronta *f, float *d)
{
    if (f->prvni == NULL) {
        return false;
    }

    TPrvek *kOdebrani = f->prvni;
    *d = kOdebrani->hodnota;
    f->prvni = kOdebrani->dalsi;

    free(kOdebrani);

    if (f->prvni == NULL) {
        f->posledni = NULL;
    }

    f->delka--;
    return true;
}

bool omezenePridej(TFronta* f, float hodnota)
{
    if (f->delka == f->max) {
        float zahod;
        dequeue(f, &zahod);
    }

    return enqueue(f, hodnota);
}

void vypisFrontu(TFronta* f)
{
    float prvek;
    while (f->prvni != NULL) {
        dequeue(f, &prvek);
        printf("%.3f\n", prvek);
    }
}

void znicFrontu(TFronta* f)
{
    float zahod;
    while (dequeue(f, &zahod));
    free(f);
}

TFronta* posledniZeSouboru(FILE* soubor, int n)
{
    TFronta* f = inicializujFrontu(n);
    float c;
    while (fscanf(soubor, "%f", &c) == 1) {
        omezenePridej(f, c);
    }
    return f;
}

int main(void)
{
    FILE *soubor = fopen("data10k.txt", "r");
    TFronta* f = posledniZeSouboru(soubor, 40);
    vypisFrontu(f);
    znicFrontu(f);
}

