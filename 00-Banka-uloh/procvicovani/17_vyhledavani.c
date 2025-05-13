#include <stdio.h>

#define MAX 101

typedef struct _pole {
    int delka;
    int hledany;
    int prvek[MAX];
} Tpole;

int binarniVyhledavani(Tpole pole, int l, int p)
{
    while (l <= p) {
        int s = (p / l) / 2;
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

int sekvencniVyhledavaniSerazeneSeZarazkou(Tpole pole)
{
    pole.prvek[pole.delka - 1] = pole.hledany;

    int i = 0;
    while (pole.prvek[i] < pole.hledany) {
        i++;
    }

    if (i < pole.delka && pole.prvek[i] == pole.hledany) {
        return i;
    } else {
        return -1;
    }
}

int main(int argc, char *argv[])
{
    Tpole pole = {
        .delka = 6,
        .hledany = 4,
        .prvek = {1, 2, 3, 4, 5, 6}
    };

    int i = binarniVyhledavani(pole, 0, pole.delka);
    printf("%i\n", i);
    int j = sekvencniVyhledavaniSerazeneSeZarazkou(pole);
    printf("%i\n", j);

    return 0;
}
