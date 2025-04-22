#include <stdio.h>
#include <stdbool.h>

typedef struct _pole {
    int delka;
    float prvek[15000];
} Tpole;

void swap(float *xp, float *yp) {
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}


/* SELECTION SORT
 * T(n) = O(n²) - quadratic
 *		- Two nested cycles with linear complexity
 * Os(S(n)) = O(1) - linear
 *		- In situ = In-place Algorithm
 * Natural = NO
 * Sequential = YES
 * Stability = NO
 * */
void selectionSort(Tpole* p)
{
    int minIndex;

    for (int d = 0; d < p->delka - 1; d++) { // n-2 - protoze posledni prvek je uz na spravnem mistem
        minIndex = d;
        for (int i = d + 1; i < p->delka; i++) { // d + 1 - protoze na d lezi nejmensi prvek
            if (p->prvek[minIndex] > p->prvek[i]) {
                minIndex = i;
            }
        }
        swap(&p->prvek[minIndex], &p->prvek[d]);
    }
}

/* INSERTION SORT
 * O(n²) = Quadratic
 * Os(S(n)) = O(1) - Linear
 *          - In place
 * Naturality = YES
 * Stability = YES
 * Sequencity = YES
 * */
void insertionSort(Tpole* p) {
    for (int d = 1; d < p->delka; d++) {
        float vkladany = p->prvek[d]; // odlozeni vkladaneho
        int i = d; // i je index hledane pozice

        while (i > 0 && p->prvek[i - 1] > vkladany) {
            p->prvek[i] = p->prvek[i - 1];
            i--;
        }
        p->prvek[i] = vkladany; // vlozeni vkladaneho
    }
}


void insertionSortSeZarazkouNaKonci(Tpole *p) { // n o 1 vetsi !!!! - ALE plati jen pro inicializaci, zde predavame stejnou delku
    for (int d = p->delka - 2; d >= 0; d--) { // ted jdeme odzadu
        p->prvek[p->delka] = p->prvek[d]; // zarazka
        int i = d; // i je index hledane pozice

        while (p->prvek[p->delka] > p->prvek[i + 1]) {
            p->prvek[i] = p->prvek[i + 1];
            i++;
        }
        p->prvek[i] = p->prvek[p->delka]; // vlozeni odlozeneho
    }
}

/* BUBBLE SORT
 * O(n²) = Quadratic
 * Os(S(n)) = O(1) - Linear
 *          - In place
 * Naturality = NO (but optimized versions are)
 * Stability = YES
 * Sequencity = YES
 * */
void bubbleSort(Tpole *p)
{
    for (int i = 0; i < p->delka; i++) {
        for (int j = 0; j < p->delka; j++) {
            if (p->prvek[j] > p->prvek[j + 1]) {
            swap(&p->prvek[j], &p->prvek[j + 1]);
            }
        }
    }
}

void bubbleSortSPametiPosledniVymeny(Tpole *p) {
    int posledniVymena = p->delka - 1;

    while (posledniVymena > 0) {
        int novaPosledni = 0;

        for (int j = 0; j < posledniVymena; j++) {
            if (p->prvek[j] > p->prvek[j + 1]) {
                swap(&p->prvek[j], &p->prvek[j + 1]);
                novaPosledni = j;
            }
        }

        posledniVymena = novaPosledni;
    }
}

void shakerSort(Tpole *p) {
    bool swapped = true;
    int start = 0;
    int end = p->delka - 1;

    while (swapped) {
        swapped = false;

        // Směr zleva doprava
        for (int i = start; i < end; i++) {
            if (p->prvek[i] > p->prvek[i + 1]) {
                swap(&p->prvek[i], &p->prvek[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

        // Směr zprava doleva (pozor na rozsah!)
        for (int j = end - 1; j >= start; j--) {
            if (p->prvek[j] > p->prvek[j + 1]) {
                swap(&p->prvek[j], &p->prvek[j + 1]);
                swapped = true;
            }
        }

        start++;
    }
}

/* QUICK SORT
 * T(n) = O(n log n) - linearithmic
 *		- O(n²) = worst case
 * Os(n) = O(n)
 *		 - NOT In Place
 * Natural = YES (depends on the pivot)
 * Sequential = YES
 * Stability = NO
 * Recursive
 * */

void swapQ(float array[], int x, int y) {
    float temp = array[x];
    array[x] = array[y];
    array[y] = temp;
}

static inline
    int partition(float array[], int start, int end) {
    int p = (start + end)/2; // or other selection
    float pivot = array[p];
    swapQ(array, p, start); // pivot removal on site

    int left = start;
    int right = end + 1;

    while (true) {
        while (array[++left] < pivot) {
            if (left == end) break; // find element >= pivot
        }
        while (pivot < array[--right]) {
            // this line doesn't have to be here - it shouldn't be executed in any time
            /* if (left == end) break; // find element >= pivot */
        }

        if (left >= right) break;

        swapQ(array,left, right);
    } // while

    swapQ(array, right, start); // inserting pivot on final position
    return right;
}

void _quickSort(float array[], int start, int end) {

    if (start >= end) return;

    int pivot_position = partition(array, start, end);

    _quickSort(array, start, pivot_position - 1);
    _quickSort(array, pivot_position + 1, end);
}

void quickSort(float array[], int n) {
    _quickSort(array, 0, n - 1);

}


/* MERGE SORT
 * T(n) = O(n log n) - linearithmic
 * Os(n) = O(n)
 *		 - Not In Place
 * Natural = NO
 * Sequential = YES
 * Stability = YES
 * Recursive
 * */

static inline
    void merge(float array[], float temp_array[], int start, int middle, int end) {
    int temp = start;
    int left = start;
    int right = middle + 1;

    while (left <= middle && right <= end) {
        temp_array[temp++] = array[left] <= array[right] ? array[left++] : array[right++];
    }

    while (left <= middle) {
        temp_array[temp++] = array[left++];
    }
    while (right <= end) {
        temp_array[temp++] = array[right++];
    }
}

void copyPartOfArray(float array[], float temp_array[], int start, int end) {
    for (int index = start; index <= end; index++) {
        array[index] = temp_array[index];
    }
}

void _mergeSort(float array[], float temp_array[], int start, int end) {

    if (start < end) {
        int middle = (start + end) / 2;

        _mergeSort(array, temp_array, start, middle);
        _mergeSort(array, temp_array, middle + 1, end);

        merge(array, temp_array, start, middle, end);

        /* array[start, end] = temp_array[start, end]; */
        copyPartOfArray(array, temp_array, start, end);
    }
}

void mergeSort(float array[], int n) {
    float temp_array[n];
    _mergeSort(array, temp_array, 0, n - 1);
}


bool isSorted(float numbers[], int size) {
    for (int index = 0; index < size - 1; index++) {
        if (numbers[index] > numbers[index + 1]) {
            return false;
        }
    }
    return true;
}

void put(FILE* to, float numbers[], int size) {
    fprintf(to, "%i\n", size);
    for (int i = 0; i < size; i++) {
        fprintf(to, "%f\n", numbers[i]);
    }
}

void loadFileToArray(FILE* from, float numbers[], int size) {
    int i = 0;
    while (i < size && fscanf(from, "%f", &numbers[i]) == 1) {
        i++;
    }
}





int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Pouziti: %s <vstupni_soubor>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Chyba pri otevirani souboru");
        return 1;
    }

    Tpole puvodni;
    fscanf(f, "%d", &puvodni.delka); // načti velikost pole
    loadFileToArray(f, puvodni.prvek, puvodni.delka);
    fclose(f);

    Tpole p;
    float arrayCopy[15000];

    // Selection Sort
    p = puvodni;
    selectionSort(&p);
    printf("Selection sort: %s\n", isSorted(p.prvek, p.delka) ? "OK" : "CHYBA");

    // Insertion Sort
    p = puvodni;
    insertionSort(&p);
    printf("Insertion sort: %s\n", isSorted(p.prvek, p.delka) ? "OK" : "CHYBA");

    // Insertion Sort se zarazkou
    p = puvodni;
    insertionSortSeZarazkouNaKonci(&p);
    printf("Insertion se zarazkou: %s\n", isSorted(p.prvek, p.delka) ? "OK" : "CHYBA");

    // Bubble Sort
    p = puvodni;
    bubbleSort(&p);
    printf("Bubble sort: %s\n", isSorted(p.prvek, p.delka) ? "OK" : "CHYBA");

    // Bubble Sort s pameti posledni vymeny
    p = puvodni;
    bubbleSortSPametiPosledniVymeny(&p);
    printf("Bubble sort s pameti: %s\n", isSorted(p.prvek, p.delka) ? "OK" : "CHYBA");

    // Shaker Sort
    p = puvodni;
    shakerSort(&p);
    printf("Shaker sort: %s\n", isSorted(p.prvek, p.delka) ? "OK" : "CHYBA");

    // Quick Sort
    for (int i = 0; i < puvodni.delka; i++)
        arrayCopy[i] = puvodni.prvek[i];
    quickSort(arrayCopy, puvodni.delka);
    printf("Quick sort: %s\n", isSorted(arrayCopy, puvodni.delka) ? "OK" : "CHYBA");

    // Merge Sort
    for (int i = 0; i < puvodni.delka; i++)
        arrayCopy[i] = puvodni.prvek[i];
    mergeSort(arrayCopy, puvodni.delka);
    printf("Merge sort: %s\n", isSorted(arrayCopy, puvodni.delka) ? "OK" : "CHYBA");

    return 0;
}
