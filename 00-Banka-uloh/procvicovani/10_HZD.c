#include <stdio.h>
#include <string.h>

typedef struct _idJmeno {
    int id;
    char jmeno[20];
} TIDJmeno;

typedef struct _idEmail {
    int id_uzivatel;
    char jmeno[20];
} TIDEmail;

void najdiEmailyPodleJmena(FILE *a, FILE *b, char* hledaneJmeno)
{
    TIDJmeno uzivatel;
    TIDEmail email;
    int id;

    printf("Vysledek pro jmeno %s:\n", hledaneJmeno);
    while (fscanf(a, "%d %19s", &uzivatel.id, uzivatel.jmeno) == 2) {
        if (strcmp(uzivatel.jmeno, hledaneJmeno) == 0) {
            while (fscanf(b, "%d %19s", &email.id_uzivatel, email.jmeno) == 2) {
                if (uzivatel.id == email.id_uzivatel) {
                    printf("%d %s %s\n", uzivatel.id, uzivatel.jmeno, email.jmeno);
                }
            }
        }
    }
}


int main(int argc, char *argv[])
{
    FILE *a = fopen("jmena.txt", "r");
    FILE *b = fopen("emaily.txt", "r");

    if (a == NULL || b == NULL) {
        printf("Neporadirilo se otevrit soubor");
    }

    char hledaneJmeno[20];
    printf("Zadej hledane jmeno: ");
    scanf("%19s", hledaneJmeno);

    najdiEmailyPodleJmena(a, b, hledaneJmeno);

    fclose(a);
    fclose(b);

    return 0;
}
