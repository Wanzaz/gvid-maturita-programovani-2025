#include <stdio.h>

void nactiRetezec(FILE *f, char retezec[], int n)
{
    int i;
    for (i = 0; i < n - 1; i++) {
        int ch = fgetc(f);
        if (ch == '\n' || ch == EOF) {
            break;
        }
        retezec[i] = (char)ch;
    }
    retezec[i] = '\0';  // POZOR - správné zakončení řetězce
}

void vytiskniRetezec(FILE *f, char retezec[], int n)
{
    for (int i = 0; retezec[i] != '\0' && i < n; i++) {
        fprintf(f, "%c", retezec[i]);
    }
}



int main(int argc, char *argv[])
{
    // testovaci retez
    /* char retezec[10] = {'a', 'b', 'c', 'd', 'e', 'f'}; */

    char retezec[100];
    int n = 10;

    printf("Zadej retezec: ");
    nactiRetezec(stdin, retezec, n);
    vytiskniRetezec(stdout, retezec, n);




}
