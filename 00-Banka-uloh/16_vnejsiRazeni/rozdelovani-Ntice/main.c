#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool readChar(FILE *file, char *ch) {
    return fscanf(file, "%c", ch) == 1;
}

bool writeChar(FILE *file, char ch) {
    return fprintf(file, "%c", ch) > 0;
}

void splitIntoNTuples(FILE *input, FILE *output1, FILE *output2, int N) {
    char ch;
    int count = 0;

    // Pro každý znak ve vstupním souboru
    while (readChar(input, &ch)) {
        // Zapisujeme do prvního souboru pro první N znaků
        if (count < N) {
            writeChar(output1, ch); // První část N-tice do output1
        } else {
            writeChar(output2, ch); // Druhá část N-tice do output2
        }
        
        count++;

        // Po každých N znacích přepneme soubor
        if (count == 2 * N) {
            count = 0;
            writeChar(output1, ' ');
            writeChar(output2, ' ');
        }
    }
}

int main(void) {
    FILE *input = fopen("input.txt", "r");
    FILE *output1 = fopen("output1.txt", "w");
    FILE *output2 = fopen("output2.txt", "w");

    int N = 4;  // Parametr pro velikost N-tice

    if (input == NULL || output1 == NULL || output2 == NULL) {
        perror("File open error");
        return -1;
    }

    splitIntoNTuples(input, output1, output2, N);

    fclose(input);
    fclose(output1);
    fclose(output2);

    return 0;
}

