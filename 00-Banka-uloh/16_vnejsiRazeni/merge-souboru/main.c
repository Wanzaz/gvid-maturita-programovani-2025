#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool readChar(FILE *file, char *ch) {
    return fscanf(file, "%c", ch) == 1;
}

bool writeChar(FILE *file, char ch) {
    return fprintf(file, "%c", ch) > 0;
}

void mergeTwoSortedFiles(FILE *inputa, FILE *inputb, FILE *output) {
    char a, b;
    bool aokay = readChar(inputa, &a);
    bool bokay = readChar(inputb, &b);

    while (aokay && bokay) {
        if (a <= b) {
            writeChar(output, a);
            aokay = readChar(inputa, &a);
        } else {
            writeChar(output, b);
            bokay = readChar(inputb, &b);
        }
    }

    while (aokay) {
        writeChar(output, a);
        aokay = readChar(inputa, &a);
    }

    while (bokay) {
        writeChar(output, b);
        bokay = readChar(inputb, &b);
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

