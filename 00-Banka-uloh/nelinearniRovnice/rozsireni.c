#include <math.h>
#include <stdio.h>

typedef float (*Tfun)(float);
typedef float (*Talg)(float, float, float, Tfun);

// Struktura pro testovací případ
typedef struct {
    const char *name;    // Název funkce
    Tfun func;           // Testovaná funkce
    float a;             // Dolní mez intervalu
    float b;             // Horní mez intervalu
    float expected;      // Očekávaný výsledek (NAN pro žádný kořen)
    float epsilon;       // Přesnost
} TestCase;

// Struktura pro testovací funkce - Newton
typedef struct {
    const char* nazev;
    Tfun f;
    Tfun df;
    float x0;
} TestCaseN;

typedef struct {
    float koef[100];
    int rad;
} Tpoly;

// 1. Kvadratická funkce: x^2 - 4 (má kořeny ±2)
float quadratic(float x) {
    return x * x - 4;
}

// 2. Lineární funkce: 2x - 6 (má kořen 3)
float linear(float x) {
    return 2 * x - 6;
}

// 3. Trigonometrická funkce: sin(x) (má nekonečně mnoho kořenů, použijte omezený interval)
float sine(float x) {
    return sin(x);
}

// 4. Funkce bez kořene v daném intervalu: x^2 + 1 (nemá žádný reálný kořen)
float no_root(float x) {
    return x * x + 1;
}

// Derivace: f'(x) = 2x
float quadratic_derivative(float x) {
    return 2 * x;
}

// Derivace: f'(x) = 2
float linear_derivative(float x) {
    return 2;
}

// Derivace: f'(x) = cos(x)
float sine_derivative(float x) {
    return cos(x);
}

// Derivace: f'(x) = 2x
float no_root_derivative(float x) {
    return 2 * x;
}


// POZOR na implentaci hornerova schemata

// DEGREE - stupen polynomu !!!!!
float hornerScheme(float coef[], int degree, float x)
{
    float sum = 0.0;
    for (int i = 0; i <= degree; i++) {
        sum  = sum*x + coef[i];
    }

    return sum;
}

// POCET KOEFICIENTU v poli....
/* float hornerScheme(float coef[], int pocet_koeficientu, float x) */
/* { */
/*     float sum = 0.0; */
/*     for (int i = 0; i < pocet koeficientu; i++) { */
/*         sum  = sum*x + coef[i]; */
/*     } */

/*     return sum; */
/* } */

float bisekce(float a, float b, float eps, Tfun func)
{
    float fa = func(a); // vycisleni f
    float fb = func(b); // vycisleni f

    // Kontrola, zda jsou hodnoty na koncích intervalu opačných znamének
    if (fa * fb >= 0) {
        return 0.0 / 0.0; // Vrací NAN, pokud není kořen v intervalu
    }

    float c = (a + b) / 2;
    float fc;

    while (fabs(fc = func(c)) >= eps) {
        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
            fa = fc;
        }
        c = (a + b) / 2;
     }

    return c;
}


// metoda tetiv
float regulaFalsi(float a, float b, float eps, Tfun func)
{
    float fa = func(a);
    float fb = func(b);
    float fc;

    if (fa * fb >= 0) {
        return NAN; // Vrací NAN, pokud není kořen v intervalu
    }

    float c = a + fa*(b - a)/(fa - fb);

    while (fabs(fc = func(c)) >= eps) {
        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
        c = a + fa*(b - a)/(fa - fb);
    }

    return c;
}

// float metodaSecen(float a, float b, float eps, Tfun func)
// {
    // float fa = func(a);
    // float fb = func(b);
    // float fc;

    // while (fabs(fc = func(b)) >= eps) {
        // // Vypočítáme nový bod pomocí vzorce metody sečen
        // float c = b - fb * (b - a) / (fb - fa);

        // // Posuneme hodnoty pro další iteraci
        // a = b;
        // fa = fb;
        // b = c;
        // fb = fc;
    // }

    // return b;  // Návrat posledního odhadu kořene
// }

float metodaSecen(float a, float b, float eps, Tfun func)
{
    float fa = func(a);
    float fb = func(b);
    float c, fc;
    int i = 0;

    while (fabs(fb) >= eps) {
        if (i >= 1000) {
            // Pokud překročíme maximální počet iterací, vrátíme nějakou hodnotu indikující chybu
            return NAN; // NAN značí "Not a Number", což indikuje nedefinovaný výsledek
        }
        // Vypočítáme nový bod pomocí vzorce metody sečen
        c = b - fb * (b - a) / (fb - fa);
        fc = func(c);

        // Posuneme hodnoty pro další iteraci
        a = b;     // Posuneme bod 'a' na původní 'b'
        fa = fb;   // Aktualizujeme f(a)
        b = c;     // Posuneme bod 'b' na nový bod 'c'
        fb = fc;   // Aktualizujeme f(b)

        i++;
    }

    return b;  // Návrat posledního odhadu kořene
}

float f(float x){
    float koef[]={1.0,5.0,6.0};
    return hornerScheme(koef,2,x);
}

float fd(float x){
    float koef[]={2.0,5.0};
    return hornerScheme(koef,1,x);
}

float newtonovaMetoda(float x, float eps, Tfun func, Tfun dfunc) {
    int i = 0; // Počítadlo iterací

    while (fabs(func(x)) >= eps) {
        if (i >= 1000) {
            // Pokud překročíme maximální počet iterací, vrátíme nějakou hodnotu indikující chybu
            return NAN; // NAN značí "Not a Number", což indikuje nedefinovaný výsledek
        }
        if (dfunc(x) == 0) {
            // Pokud je derivace nulová, metoda nemůže pokračovat
            return NAN;
        }

        x = x - func(x) / dfunc(x); // Aktualizujeme bod pomocí Newtonova vzorce

        i++; // Zvýšíme počítadlo iterací
    }

    return x; // Návrat nalezeného kořene
}

void testNewtonovaMetoda() {
    float pocatecniOdhad = 1.0; // Počáteční odhad
    float tolerance = 0.0001;     // Přesnost

    float koren = newtonovaMetoda(pocatecniOdhad, tolerance, f, fd);

    if (isnan(koren)) {
        printf("Newtonova metoda selhala nebo překročila maximální počet iterací.\n");
    } else {
        printf("Nalezený kořen: %f\n", koren);
    }
}


void test_horner_scheme() {
    printf("Spouštím testy pro Hornerovo schéma...\n\n");

    // Testovací případy
    float coef1[] = {1.0, -4.0, 4.0};      // x^2 - 4x + 4
    float coef2[] = {1.0, 2.0, 1.0, 1.0};  // x^3 + 2x^2 + x + 1
    float coef3[] = {3.0, 1.0, -2.0, 7.0, -4.0}; // 3x^4 + x^3 - 2x^2 + 7x - 4
    float coef4[] = {5.0};                 // Konstanta 5

    // Testy
    printf("Test 1: x^2 - 4x + 4 při x = 2\n");
    printf("  Výsledek: %f (očekávaný: 0.000000)\n", hornerScheme(coef1, 2, 2.0));

    printf("Test 2: x^3 + 2x^2 + x + 1 při x = 1\n");
    printf("  Výsledek: %f (očekávaný: 5.000000)\n", hornerScheme(coef2, 3, 1.0));

    printf("Test 3: 3x^4 + x^3 - 2x^2 + 7x - 4 při x = 2\n");
    printf("  Výsledek: %f (očekávaný: 58.000000)\n", hornerScheme(coef3, 4, 2.0));

    printf("Test 4: Konstanta 5 při x = 10\n");
    printf("  Výsledek: %f (očekávaný: 5.000000)\n", hornerScheme(coef4, 0, 10.0));

    printf("\nTesty Hornerova schématu dokončeny.\n");
}

void test(Talg func) {
    TestCase tests[] = {
        {"Kvadratická (x^2 - 4)", quadratic, -5, 0, -2.0, 0.001},
        {"Lineární (2x - 6)", linear, 0, 5, 3.0, 0.001},
        {"Trigonometrická (sin(x))", sine, 3, 4, 3.14159, 0.001},
        {"Bez kořene (x^2 + 1)", no_root, -2, 2, NAN, 0.001}
    };

    size_t num_tests = sizeof(tests) / sizeof(TestCase);

    for (size_t i = 0; i < num_tests; i++) {
        TestCase test = tests[i];
        printf("Test %zu: %s v intervalu <%f, %f>\n", i + 1, test.name, test.a, test.b);

        float result = func(test.a, test.b, test.epsilon, test.func);

        if (isnan(test.expected)) {
            if (isnan(result)) {
                printf("  Test úspěšný: Nenalezen žádný kořen, jak očekáváno.\n");
            } else {
                printf("  Selhání: Neočekávaný kořen nalezen: %f\n", result);
            }
        } else {
            if (fabs(result - test.expected) <= test.epsilon) {
                printf("  Test úspěšný: Nalezený kořen: %f (očekávaný: %f)\n", result, test.expected);
            } else {
                printf("  Selhání: Nalezený kořen: %f (očekávaný: %f)\n", result, test.expected);
            }
        }
    }

    printf("\nTesty dokončeny.\n\n\n\n");
}


void testNewton() {
    TestCaseN testy[] = {
        {"Kvadratická (x^2 - 4)", quadratic, quadratic_derivative, 1.0},
        {"Lineární (2x - 6)", linear, linear_derivative, 1.0},
        {"Sinusová (sin(x))", sine, sine_derivative, 0.5},
        {"Funkce bez kořene (x^2 + 1)", no_root, no_root_derivative, 1.0}
    };

    int pocetTestu = sizeof(testy) / sizeof(TestCase);

    printf("====================================\n");
    printf("Spouštím testy pro funkci Newtonova metoda...\n\n");
    printf("====================================\n");

    for (int i = 0; i < pocetTestu; i++) {
        float root = newtonovaMetoda(testy[i].x0, 0.0001, testy[i].f, testy[i].df);

        printf("[%d] %s\n", i + 1, testy[i].nazev);
        if (isnan(root)) {
            printf("    ❌ Newtonova metoda selhala (žádný reálný kořen nebo derivace = 0)\n");
        } else {
            printf("    ✅ Nalezený kořen: %.6f\n", root);
        }
        printf("------------------------------------\n");
    }
}


int main()
{
    // V tomto případě se změní způsob, jakým předáváme polynom do funkcí, protože místo použití jednotlivých koeficientů pro výpočty použijeme strukturu Tpoly, která obsahuje jak pole koeficientů, tak stupeň polynomu.
    Tpoly p={
        .koef={-2.1,0.0,22.4,0.0,-3.0},
        .rad=4
    };

    test_horner_scheme();

    printf("Spouštím testy pro funkci Bisekce...\n\n");
    test(bisekce);
    printf("Spouštím testy pro funkci Regula Falsi...\n\n");
    test(regulaFalsi);
    printf("Spouštím testy pro funkci Metoda secen...\n\n");
    test(metodaSecen);
    testNewton();
    return 0;
}
