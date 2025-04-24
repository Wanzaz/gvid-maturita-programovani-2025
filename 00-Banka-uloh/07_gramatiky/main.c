#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool jeVPoli(char pole[], char znak)
{
    for (int i = 0; pole[i] != '\0'; i++) {
        if (pole[i] == znak) {
            return true;
        }
    }

    return false;
}

bool jeTypu2(char pravidlo[], char sigma[], char N[])
{
    char l;
    if (sscanf(pravidlo, "%c->", &l) != 1) {
        return false;
    }

    if (!jeVPoli(N, l)) {
        return false;
    }

    int i;
    for (i = 3; pravidlo[i] != '\0'; i++) {
        if (!jeVPoli(sigma, pravidlo[i]) && !jeVPoli(N, pravidlo[i])) {
            return false;
        }
    }

    return i > 3;
}

bool jeTypu3(char pravidlo[], char sigma[], char N[])
{
    char l;
    if (sscanf(pravidlo, "%c->", &l) != 1) {
        return false;
    }

    if (!jeVPoli(N, l)) {
        return false;
    }

    if (strlen(pravidlo) < 4) {
        return false;
    }

    if (jeVPoli(sigma, pravidlo[3])) {
        return
            pravidlo[4] == '\0' 
            || (jeVPoli(N, pravidlo[4]) && pravidlo[5] == '\0')
        ;
    }

    if (jeVPoli(N, pravidlo[3])) {
        return 
            pravidlo[4] == '\0' 
            || (jeVPoli(sigma, pravidlo[4]) && pravidlo[5] == '\0')
        ;
    }

    return false;
}

void vygenerujNVet(FILE* vystup, int n)
{
    for (int i = 1; i <= n; i++) {
        char veta[2 + 2*i];
        veta[0] = 'a';
        int j;
        for (j = 1; j < i*2; j++) {
            veta[j++] = 'b';
            veta[j] = 'c';
        }
        veta[j] = '\0';
        fprintf(vystup, "%s\n", veta);
    }
}

int main(void)
{
    printf("%i\n", jeTypu3("S->aA", "a", "SABC"));
    printf("%i\n", jeTypu3("S->a", "a", "SABC"));
    printf("%i\n", jeTypu3("S->A", "a", "SABC"));
    printf("%i\n", jeTypu3("S->Aa", "a", "SABC"));
    printf("%i\n", jeTypu3("a->Aa", "a", "SABC"));
    printf("%i\n", jeTypu3("AA->Aa", "a", "SABC"));
    printf("%i\n", jeTypu3("A->", "a", "SABC"));
    printf("%i\n", jeTypu3("A->aa", "a", "SABC"));
    printf("%i\n", jeTypu3("A->aAa", "a", "SABC"));
    printf("%i\n", jeTypu2("S->Aa", "a", "SABC"));
    printf("%i\n", jeTypu2("a->Aa", "a", "SABC"));
    printf("%i\n", jeTypu2("AA->Aa", "a", "SABC"));
    printf("%i\n", jeTypu2("A->", "a", "SABC"));
    printf("%i\n", jeTypu2("A->aa", "a", "SABC"));
    printf("%i\n", jeTypu2("A->aAa", "a", "SABC"));
    vygenerujNVet(stdout, 10);
}
