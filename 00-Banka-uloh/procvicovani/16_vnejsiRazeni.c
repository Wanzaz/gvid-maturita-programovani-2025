#include <stdio.h>
#include <stdbool.h>

bool nactiZnak(FILE* f, char *znak)
{
    return fscanf(f,"%c", znak) == 1;
}

bool vytiskniZnak(FILE* f, char znak)
{
    return fprintf(f,"%c", znak) > 0;
}


void rozdelPoNticich(FILE* input, FILE *a, FILE *b, int n)
{
    int i = 0;
    bool flag = true;

    char znak;
    bool inputAOkay = nactiZnak(input, &znak);

    while (inputAOkay) {

        if (flag) {
            vytiskniZnak(a, znak);
        } else {
            vytiskniZnak(b, znak);
        }

        i++;
        if (i == n) {
            vytiskniZnak(a, ' ');
            vytiskniZnak(b, ' ');
            i = 0;
            flag = !flag;
        }
        inputAOkay = nactiZnak(input, &znak);
    }


}



int main(int argc, char *argv[])
{
    FILE *input = fopen("input.txt", "r");
    FILE *a = fopen("a.txt", "w");
    FILE *b = fopen("b.txt", "w");

    if (input == NULL || a == NULL || b == NULL) {
        printf("Chyba pri otevreni souboru\n");
        return -1;
    }

    int n;
    printf("Zadej velikost N-tice: ");
    scanf("%d", &n);

    rozdelPoNticich(input, a, b, n);

    fclose(a);
    fclose(b);
    fclose(input);
    return 0;
}
