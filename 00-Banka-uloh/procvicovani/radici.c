#include <stdio.h>


typedef struct _pole {
    float prvek[50];
    int delka;
} Tpole;


void swap(float *a, float *b)
{
    float h = *a;
    *a = *b;
    *b = h;
}

void selectionSort(Tpole *p)
{
    int minIndex = 0;

    for (int d = 0; d < p->delka - 1; d++) {
        minIndex = d;
        for (int i = d + 1; i < p->delka; i++) {
            if (p->prvek[minIndex] > p->prvek[i]) {
                minIndex = i;
            }
        }
        swap(&p->prvek[minIndex], &p->prvek[d]);
    }
}

void insertionSort(Tpole *p)
{
    for (int d = 1; d < p->delka; d++) {
        int vkladany = p->prvek[d];
        int i = d;

        while (i > 0 && vkladany < p->prvek[i - 1]) {
            p->prvek[i] = p->prvek[i - 1];
            i--;
        }
        p->prvek[i] = vkladany;
    }
}

void insertionSortBreak(Tpole *p)
{
    for (int d = p->delka - 1; d >= 0; d--) {
        p->prvek[p->delka] = p->prvek[d];

        int i = d;
        while (p->prvek[p->delka] > p->prvek[i + 1]) {
            p->prvek[i] = p->prvek[i + 1];
            i++;
        }

        p->prvek[i] = p->prvek[p->delka];
    }
}

void bublinovka(Tpole *p)
{
    int posledniVymena = p->delka - 1;

    for (int i = p->delka - 1; posledniVymena > 0; i--) {
        int vymena = 0;
        for (int j = 0; j < posledniVymena; j++) {
            if (p->prvek[j] > p->prvek[j + 1]) {
                float h = p->prvek[j];
                p->prvek[j] = p->prvek[j + 1];
                p->prvek[j + 1] = h;
                vymena = j;
            }
        }
        posledniVymena = vymena;
    }
}

void mergeSort(int pole[], int tmp_pole[], int start, int middle, int end)
{
    int i = start;
    int j = middle;
    int k = start;

    while (i < middle && j < end) {
        if (pole[i] <= pole[j]) {
            tmp_pole[k] = pole[i];
            i++;
        } else {
            tmp_pole[k] = pole[j];
            j++;
        }
        k++;
    }

    while (i < middle) {
        tmp_pole[k++] = pole[i];
        i++;
    }

    while (j < end) {
        tmp_pole[k++] = pole[j];
        j++;
    }
}
