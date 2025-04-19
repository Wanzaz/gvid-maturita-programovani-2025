#include <math.h>
#include<stdio.h>


typedef struct {
    double* exponents;
    int degree;
} TPolynomial;


// POZOR na implentaci hornerova schemata

// DEGREE - stupen polynomu !!!!!
double horner(TPolynomial* polynomial, double value)
{
    double result = 0;
    for (int i = 0; i <= polynomial->degree; i++) {
        result = result * value + polynomial->exponents[i];
    }

    return result;
}

double solveBisekce(TPolynomial* polynomial, double a, double b, double eps)
{
    double fa = horner(polynomial, a);
    double fb = horner(polynomial, b);

    // Kontrola, zda jsou hodnoty na koncích intervalu opačných znamének
    if (fa * fb >= 0) {
        return 0.0 / 0.0; // Vrací NAN, pokud není kořen v intervalu
    }

    double c = (b + a) / 2;
    double fc;

    while (fabs(fc = horner(polynomial, c)) >= eps) {
        if (fa * fc < 0) {
            b = c;
        } else {
            fa = fc;
            a = c; 
        }

        c = (b + a) / 2;
    }

    return c;
}


// metoda Tetiv
double solveRegula(TPolynomial* polynomial, double a, double b, double eps)
{
    double fa = horner(polynomial, a);
    double fb = horner(polynomial, b);
    double fc;

    if (fa * fb >= 0) {
        return NAN; // Vrací NAN, pokud není kořen v intervalu
    }

    double c = (a * fb - b * fa) / (fb - fa);

    while (fabs(fc = horner(polynomial, c)) >= eps) {
        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
        c = (a * fb - b * fa) / (fb - fa);
    }

    return c;
}

double solveSecen(TPolynomial* polynomial, double a, double b, double eps)
{
    double fa = horner(polynomial, a);
    double fb = horner(polynomial, b);
    double c = (a * fb - b * fa) / (fb - fa);
    double fc;
    int i = 0;

    while (fabs(fc = horner(polynomial, c)) >= eps) {
        if (i >= 1000) {
            // Pokud překročíme maximální počet iterací, vrátíme nějakou hodnotu indikující chybu
            return NAN; // NAN značí "Not a Number", což indikuje nedefinovaný výsledek
        }
        fa = fb;
        a = b;
        fb = fc;
        b = c;
        c = (a * fb - b * fa) / (fb - fa);
    }

    return c;
}


double solveNewton(TPolynomial* polynomial, TPolynomial* derivative, double x, double eps) {
    int i = 0; // Počítadlo iterací

    while (fabs(horner(polynomial, x)) >= eps) {
        if (i >= 1000) {
            // Pokud překročíme maximální počet iterací, vrátíme nějakou hodnotu indikující chybu
            return NAN; // NAN značí "Not a Number", což indikuje nedefinovaný výsledek
        }
        if (horner(derivative, x) == 0) {
            // Pokud je derivace nulová, metoda nemůže pokračovat
            return NAN;
        }

        x = x - horner(polynomial, x) / horner(derivative, x); // Aktualizujeme bod pomocí Newtonova vzorce

        i++; // Zvýšíme počítadlo iterací
    }

    return x; // Návrat nalezeného kořene
}


int main(void)
{
    double exponents[7] = {12, 0.7, 3, 0, 6, 22, 4.62};
    TPolynomial p = {
        .exponents = exponents,
        .degree = 6,
    };

    double de[6] = {72, 3.5, 12, 0, 12, 22};
    TPolynomial dp = {
        .exponents = de, 
        .degree = 5,
    };

    printf("%f\n", horner(&p, 7.1));
    printf("%f\n", solveBisekce(&p, -1, -0.9, 0.0000001));
    printf("%f\n", solveRegula(&p, -1, -0.9, 0.0000001));
    printf("%f\n", solveSecen(&p, -1, -0.9, 0.0000001));
    printf("%f\n", solveNewton(&p, &dp, -1, 0.0000001));
}
