#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct _prvek Tprvek;
typedef struct _zasobnik Tzasobnik;


struct _prvek {
    char hodnota;
    Tprvek *dalsi;
};

struct _zasobnik {
    int vyska;
    Tprvek *vrchol;
};


Tzasobnik *zasInit(void)
{
    Tzasobnik *z = malloc(sizeof(Tzasobnik));
    if (z == NULL) {
        return NULL;
    }

    z->vrchol = NULL;
    z->vyska = 0;

    return z;
}

bool zasIsEmpty(Tzasobnik *z)
{
    return z->vrchol == NULL;
}

bool zasPush(Tzasobnik* z, char data)
{
    Tprvek* novy = malloc(sizeof(Tprvek));
    if (novy == NULL) {
        return false;
    }

    novy->hodnota = data;
    novy->dalsi = z->vrchol;
    z->vrchol = novy;
    z->vyska++;


    return true;

}

bool zasPop(Tzasobnik* z, char *d)
{
    if (zasIsEmpty(z)) {
        return false;
    }

    Tprvek* odebrany = z->vrchol;
    *d = odebrany->hodnota;
    z->vrchol = odebrany->dalsi;
    free(odebrany);
    z->vyska--;

    return true;
}

void zasFree(Tzasobnik *z)
{
    while (!zasIsEmpty(z)) {
        char data;
        zasPop(z, &data);
    }

    free(z);
}


bool zasTop(Tzasobnik *z, char *d)
{
    if (zasIsEmpty(z)) {
        return false;
    }
    *d = z->vrchol->hodnota;

    return true;
}

bool jeToOteviraciZavorka(char znak)
{
    return znak == '(' ||
           znak == '[' ||
           znak == '{' ||
           znak == '<';
}

bool jeToZaviraciZavorka(char znak)
{
    return znak == ')' ||
           znak == ']' ||
           znak == '}' ||
           znak == '>';
}

int oteviraci2zaviraci(int znak)
{
    if (znak == '(') return ')';
    if (znak == '[') return ']';
    if (znak == '{') return '}';
    if (znak == '<') return '>';

    return znak;
}

bool testujZavorky(FILE *f, Tzasobnik *z)
{
    char znak;
    while (fscanf(f, "%c", &znak) == 1) {
        if (jeToOteviraciZavorka(znak)) {
            if (!zasPush(z, znak)) {
                return false;
            }
        } else if (jeToZaviraciZavorka(znak)) {
            if (zasIsEmpty(z)) {
                return false; // Unmatched closing bracket
            }
            char oteviraci = z->vrchol->hodnota;
            char ocekavanyZaviraci = oteviraci2zaviraci(oteviraci);

            if (znak != ocekavanyZaviraci) {
                return false; // Unmatched closing bracket
            } else {
                zasPop(z, &znak);
            }
        }
    }

    if (!zasIsEmpty(z)) {
        return false; // Unmatched opening bracket
    }

    return true;
}


bool zavorky(FILE *in)
{
    Tzasobnik *z = zasInit();


    int vysledek = testujZavorky(in, z);

    free(z);

    return vysledek;
}




int main(int argc, char *argv[])
{
    if (zavorky(stdin)) {
        printf("Zavorky jsou spravne uzavreny");
    } else {
        printf("Zavorky jsou nespravne uzavreny");
    }

    return 0;
}
