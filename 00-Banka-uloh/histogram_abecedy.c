#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define BLOK 10

typedef struct _retezec {
    int delka;
    int kapacita;
    char *znak;
} TRetezec;



// čti vstup neznámé délky po znacích a vrať pole reprezentující histogram, poté
// z něj vypiš absolutní četnosti malých znaků anglické abecedy (počty znaků na vstupu)

void nactiRetezec(FILE *f, TRetezec *r)
{
    r->delka = 0;
    r->kapacita = BLOK;

    r->znak = malloc(sizeof(char) * r->kapacita);
    if (r->znak == NULL) {
        printf("Chyba při alokaci paměti!\n");
        exit(-1);
    }

    int c;
    while ((c = fgetc(f)) != EOF) {
        if (r->delka >= r->kapacita) {
            r->kapacita *= 2;
            char *temp = realloc(r->znak, sizeof(char) * r->kapacita);
            if (temp == NULL) {
                printf("Chyba při realokaci paměti!\n");
                free(r->znak);
                exit(-1);
            }
            r->znak = temp;
        }

        r->znak[r->delka++] = c;
    }
}

// vytvoř histogram a vypiš četnosti malých písmen
void vytvorAHistogram(TRetezec *r)
{
    int histogram[26] = {0};

    for (int i = 0; i < r->delka; i++) {
        char ch = r->znak[i];
        if (ch >= 'a' && ch <= 'z') {
            histogram[ch - 'a']++;
        }
    }

    printf("Histogram malych pismen:\n");
    for (int i = 0; i < 26; i++) {
        if (histogram[i] > 0) {
            printf("%c: %d\n", 'a' + i, histogram[i]);
        }
    }
}



int main(int argc, char *argv[])
{

    TRetezec r;

    printf("Zadej text :\n");
    nactiRetezec(stdin, &r);
    vytvorAHistogram(&r);

    // Uklidit alokovanou paměť
    free(r.znak);


    return 0;
}
