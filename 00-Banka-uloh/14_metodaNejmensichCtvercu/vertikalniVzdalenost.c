#include <stdio.h>

double naDruhou(double x) {
    return x * x;
}

// Vrátí součet čtverců vertikálních rozdílů mezi hodnotami y a funkcí y = ax + b
double soucetCtvercuChyb(double x[], double y[], int N, double a, double b) {
    double suma = 0.0;

    for (int i = 0; i < N; i++) {
        double chyba = y[i] - (a * x[i] + b);
        suma += naDruhou(chyba);
    }

    return suma;
}

int main() {
    // Naměřená data
    double x[] = {1.0, 2.0, 3.0, 4.0};
    double y[] = {2.0, 4.1, 5.9, 8.2};

    int N = sizeof(x) / sizeof(x[0]);

    // Parametry přímky: y = a*x + b
    double a = 2.0;
    double b = 0.0;

    double vysledek = soucetCtvercuChyb(x, y, N, a, b);
    printf("Součet čtverců chyb: %.3f\n", vysledek);

    return 0;
}

