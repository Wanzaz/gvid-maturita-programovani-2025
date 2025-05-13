#include <stdio.h>
#include <stdbool.h>


bool jeToOveriraciZvorka(char znak)
{
    return znak == '<' || znak == '[' || znak == '{' || znak == '(';
}

bool jeToZaviraciZavorka(char znak)
{
    return znak == '>' || znak == ']' || znak == '}' || znak == ')';
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
