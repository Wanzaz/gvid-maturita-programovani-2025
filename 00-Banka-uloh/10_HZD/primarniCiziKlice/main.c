#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define JMENO_DELKA 10
#define EMAIL_DELKA 20
#define BUFFER_SIZE 256

typedef struct {
    int id;
    char jmeno[JMENO_DELKA + 1];
} TUzivatel;

typedef struct {
    int id_uzivatele;
    char email[EMAIL_DELKA + 1];
} TEmailZaznam;

void vypisEmailProJmeno(const char *jmeno_k_vyhledani, FILE *f_uzivatelu, FILE *f_emailu) {
    char radek_uzivatelu[BUFFER_SIZE];
    char radek_emailu[BUFFER_SIZE];
    TUzivatel uzivatel;
    TEmailZaznam email_zaznam;

    printf("Výsledky pro jméno '%s':\n", jmeno_k_vyhledani);

    while (fgets(radek_uzivatelu, BUFFER_SIZE, f_uzivatelu) != NULL) {
        if (sscanf(radek_uzivatelu, "%d %10s", &uzivatel.id, uzivatel.jmeno) == 2) {
            if (strcmp(uzivatel.jmeno, jmeno_k_vyhledani) == 0) {
                rewind(f_emailu);
                while (fgets(radek_emailu, BUFFER_SIZE, f_emailu) != NULL) {
                    if (sscanf(radek_emailu, "%d %20s", &email_zaznam.id_uzivatele, email_zaznam.email) == 2) {
                        if (email_zaznam.id_uzivatele == uzivatel.id) {
                            printf("%d %s %s\n", uzivatel.id, uzivatel.jmeno, email_zaznam.email);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    char soubor_uzivatelu[256];
    char soubor_emailu[256];
    char hledane_jmeno[JMENO_DELKA + 1];
    FILE *f_uzivatelu = NULL;
    FILE *f_emailu = NULL;

    printf("Zadejte název souboru s uživateli: ");
    if (scanf("%255s", soubor_uzivatelu) != 1) {
        fprintf(stderr, "Chyba při načítání názvu souboru s uživateli.\n");
        return 1;
    }

    printf("Zadejte název souboru s e-maily: ");
    if (scanf("%255s", soubor_emailu) != 1) {
        fprintf(stderr, "Chyba při načítání názvu souboru s e-maily.\n");
        return 1;
    }

    printf("Zadejte jméno uživatele k vyhledání: ");
    if (scanf("%10s", hledane_jmeno) != 1) {
        fprintf(stderr, "Chyba při načítání hledaného jména.\n");
        return 1;
    }

    f_uzivatelu = fopen(soubor_uzivatelu, "r");
    f_emailu = fopen(soubor_emailu, "r");

    if (f_uzivatelu == NULL || f_emailu == NULL) {
        perror("Chyba při otevírání souborů");
        if (f_uzivatelu != NULL) fclose(f_uzivatelu);
        if (f_emailu != NULL) fclose(f_emailu);
        return 1;
    }

    vypisEmailProJmeno(hledane_jmeno, f_uzivatelu, f_emailu);

    fclose(f_uzivatelu);
    fclose(f_emailu);

    return 0;
}
