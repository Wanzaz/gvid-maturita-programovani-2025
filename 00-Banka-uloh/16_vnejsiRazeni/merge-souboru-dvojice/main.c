#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
• Dva vstupní soubory obsahují znaky. Sluč je do třetího výstupního souboru tak,
aby v něm byly znaky seřazeny po dvojicích.
**/

// Funkce pro čtení jednoho znaku ze souboru
bool readChar(FILE *file, char *ch) {
    return fscanf(file, "%c", ch) == 1;
}

// Funkce pro zápis jednoho znaku do souboru
bool writeChar(FILE *file, char ch) {
    return fprintf(file, "%c", ch) > 0;
}

void mergeTwoSortedFiles(FILE *inputa, FILE *inputb, FILE *output) {
    char a, b;
    bool aokay = readChar(inputa, &a);
    bool bokay = readChar(inputb, &b);

    while (aokay || bokay) {
        if (aokay && bokay) {
            if (a <= b) {
                writeChar(output, a);
                aokay = readChar(inputa, &a);
                writeChar(output, b);
                bokay = readChar(inputb, &b);
            } else {
                writeChar(output, b);
                bokay = readChar(inputb, &b);
                writeChar(output, a);
                aokay = readChar(inputa, &a);
            }
        }
        // Pokud máme pouze znak z jednoho souboru, zapíšeme ho
        else if (aokay) {
            writeChar(output, a);
            aokay = readChar(inputa, &a);
        }
        else if (bokay) {
            writeChar(output, b);
            bokay = readChar(inputb, &b);
        }

        // Pokud máme alespoň 2 znaky, přidáme mezeru mezi dvojicemi
        if (aokay || bokay) {
            writeChar(output, ' ');
        }
    }
}

int main(void) {
    FILE *input1 = fopen("input1.txt", "r");
    FILE *input2 = fopen("input2.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input1 == NULL || input2 == NULL || output == NULL) {
        perror("File open error");
        return -1;
    }

    mergeTwoSortedFiles(input1, input2, output);

    fclose(input1);
    fclose(input2);
    fclose(output);

    return 0;
}

