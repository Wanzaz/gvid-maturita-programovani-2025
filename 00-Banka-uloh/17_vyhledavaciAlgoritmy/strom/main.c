#include <stdio.h>
#include <stdlib.h>
// #include <string.h>  // pro praci s textovymi retezci
#include <stdbool.h> // pro praci s typem bool a konstantami true a false
#include <ctype.h>   // isalpha, isspace, islower, isupper, ...
 #include <time.h>    // funkce time a dalsi pro praci s casem
#include "SuperTisk.h"
#include "strom.h"

/**
Doplň program (bude k dispozici kostra programu) pro práci s binárním vyhledávacím
stromem obsahujícím celočíselné klíče. Napiš podprogram pro
• nalezení minimálního / maximálního prvku ve stromu
• nalezení zadaného klíče
• výpis klíčů seřazených vzestupně / sestupně
• přidání nového klíče do stromu
• výpis všech klíčů menších / větších než zadaný klíč
• zrušení celého stromu
• zrušení listu
• výpočet váhy stromu (počtu prvků ve stromu)
• výpočet výšky stromu (největší vzdálenost kořen – list) **/

/** Uzel binárního stromu. Dvojice klic-data je zde int-float. 
typedef struct _tuzel Tuzel;
// Vnitřek typu Tuzel je ukryt v souboru strom.c.


// Struktura reprezentující celý strom. 
typedef struct _strom Tstrom;

// Tohle uživatel vidět nemusí. Ještě by mi do toho vlezl a něco mi tu poničil.
struct _tuzel
{
    int klic;           //< Klíč pro vyhledávání -- zde celé číslo
    float data;         //< Data vázaná na klíč -- zde desetinné číslo
    Tuzel* levy;   //< Ukazatel na levý podstrom
    Tuzel* pravy;  //< Ukazatel na pravý podstrom
};

struct _strom
{
    Tuzel* koren;
    int vaha;
};
**/

/* nalezení minimálního ve stromu*/
Tuzel *_najdiMinimum(Tuzel *u)
{
    if (u == NULL) return NULL;
    if (u->levy == NULL) return u;
    return _najdiMinimum(u->levy);
}

Tuzel *najdiMinimum(Tstrom *strom)
{
    if (strom == NULL || strom->koren == NULL) return NULL;
    return _najdiMinimum(strom->koren);
}


/* maximálního prvku ve stromu */
Tuzel *_najdiMaximum(Tuzel *u)
{
    if (u == NULL) return NULL;
    if (u->pravy == NULL) return u;
    return _najdiMaximum(u->pravy);
}

Tuzel *najdiMaximum(Tstrom *strom)
{
    if (strom == NULL || strom->koren == NULL) return NULL;
    return _najdiMaximum(strom->koren);
}

// výpis klíčů seřazených vzestupně
void _inOrder(Tuzel * u)
{
    if (u == NULL) { return; }

    _inOrder(u->levy);
    printf("%d - %f\n", u->klic, u->data);
    _inOrder(u->pravy);
}

void vypisInOrder(Tstrom * strom)
{
    _inOrder(strom->koren);
}

// výpis klíčů seřazených vzestupně / sestupně
void _inOrderReverse(Tuzel * u)
{
    if (u == NULL) { return; }

    _inOrderReverse(u->pravy);
    printf("%d - %f\n", u->klic, u->data);
    _inOrderReverse(u->levy);
}

void vypisInOrderReverse(Tstrom * strom)
{
    _inOrderReverse(strom->koren);
}

// výpočet váhy stromu (počtu prvků ve stromu)
int _vaha(Tuzel * u)
{
    if (u == NULL) { return 0; }

    return 1 + _vaha(u->levy) + _vaha(u->pravy);

}

int bvsPruchodVaha(Tstrom * strom)
{
    return _vaha(strom->koren);
}

// nebo chytre
int bvsVaha(Tstrom* strom)
{
    return strom->vaha;
}


// výpočet výšky stromu (největší vzdálenost kořen – list) **/
int _vyska(Tuzel *u)
{
    if (u == NULL) return -1;

    int leva = _vyska(u->levy);
    int prava = _vyska(u->pravy);

    return 1 + (leva > prava ? leva : prava);
}

int vyskaStromu(Tstrom *strom)
{
    return _vyska(strom->koren);
}

void operaceH_vahaVyska(Tstrom *strom)
{
    if (bvsVaha(strom) == bvsPruchodVaha(strom)) {
        printf("\nVyska stromu: %d\n", bvsVaha(strom));
    } else {
        printf("Neco se pokazilo. Utikej!!!\n");
    }
}

// zrušení celého stromu
// klasicky POSTORDER
void _bvsZrus(Tuzel *u)
{
    if (u == NULL) return;
    _bvsZrus(u->levy);
    _bvsZrus(u->pravy);
    free(u);
}

void bvsZrus(Tstrom *strom)
{
    _bvsZrus(strom->koren);
    free(strom);
}

Tuzel *_novyUzel(int klic, float data)
{
    Tuzel *u = malloc(sizeof(Tuzel));
    if (u == NULL) return NULL;
    u->klic = klic;
    u->data = data;
    u->levy = u->pravy = NULL;
    return u;
}

bool _bvsVloz(Tuzel **u, int klic, float data)
{
    Tuzel* pom = *u; // pomucka pro eliminaci *, POZOR!!!
    
    if (pom == NULL) {
        if ((pom = _novyUzel(klic, data)) == NULL) { return false; }

        *u = pom; // NUTNE!!! pom je lokalni
        return true;
    }
    // nevkladame nahodou duplicitni klic? ne nevkladamae protoze tady si
    // na duplicitni klice nehrajeme
    //if (klic == pom->klic) return false
    
    // patri v levo nebo pravo
    /* if (klic < pom->klic) { */
    /*     return _bvsVloz(&pom->levy, klic, data); */
    /* } else { */
    /*     return _bvsVloz(&pom->pravy, klic, data); */
    /* } */
    
    // lepsi zapsani swag
    return _bvsVloz(klic < pom->klic ? &pom->levy : &pom->pravy, klic, data);
}

bool bvsVloz(Tstrom *strom, int klic, float data)
{
    if (_bvsVloz(&strom->koren, klic, data))
    {
        strom->vaha += 1;
        return true;
    }
    return false;
}
/* zrušení (vybraného) listu */
bool _zrusVybranyList(Tuzel **u, int klic)
{
    if (*u == NULL) return false;

    Tuzel *pom = *u;

    if (pom->klic == klic) {
        if (pom->levy == NULL && pom->pravy == NULL) {
            free(pom);
            *u = NULL;
            return true;
        } else {
            return false;
        }
    }

    return _zrusVybranyList(klic < pom->klic ? &pom->levy : &pom->pravy, klic);
}

bool zrusVybranyList(Tstrom *strom, int klic)
{
    if (strom == NULL || strom->koren == NULL) return false;

    if (_zrusVybranyList(&strom->koren, klic))
    {
        strom->vaha -= 1;
        return true;
    }
    return false;
}

/* zrušení prvního listu */
bool _zrusPrvniList(Tuzel **u)
{
    if (*u == NULL) return false;

    Tuzel *pom = *u;

    if (pom->levy == NULL && pom->pravy == NULL)
    {
        free(pom);
        *u = NULL; // Nastavíme ukazatel na NULL
        return true;
    }

    if (pom->levy != NULL) {
        if (_zrusPrvniList(&pom->levy)) {
            return true;
        }
    }

    if (pom->pravy != NULL) {
        if (_zrusPrvniList(&pom->pravy)) {
            return true;
        }
    }

    return false;
}


// nalezení zadaného klíče
Tuzel* _bvsNajdi(Tuzel *u, int klic)
{
    if (u == NULL) return NULL;

    if (u->klic == klic) {
        return u; // Nalezeno!
    }

    return _bvsNajdi(klic < u->klic ? u->levy : u->pravy, klic);
}

Tuzel* bvsNajdi(Tstrom *strom, int klic)
{
    if (strom == NULL) return NULL;
    return _bvsNajdi(strom->koren, klic);
}


// výpis všech klíčů menších než zadaný klíč
void _mensiNez(Tuzel *u, int klic)
{
    if (u == NULL) { return; }

    _mensiNez(u->levy, klic);
    if (klic > u->klic) { printf("%d - %f\n", u->klic, u->data); }
    _mensiNez(u->pravy, klic);
}

void vypisMensiNez(Tstrom *strom, int klic)
{
    _mensiNez(strom->koren, klic);
}

// výpis všech klíčů větších než zadaný klíč
void _vetsiNez(Tuzel *u, int klic)
{
    if (u == NULL) { return; }

    _vetsiNez(u->levy, klic);
    if (klic < u->klic) { printf("%d - %f\n", u->klic, u->data); }
    _vetsiNez(u->pravy, klic);
}

void vypisVetsiNez(Tstrom *strom, int klic)
{
    _vetsiNez(strom->koren, klic);
}

void vlozeni10Uzlu(Tstrom *strom)
{
    // automaticky vlozit 10 uzlu zdrzuje - FINTAAAAA
    srand(time(NULL));
    for (int i = 10; i > 0; i--) {
        bvsVloz(strom, rand() % 100, i + 0.5); // rand() % 100
    }
}




void menu(void)
{
    printf(
        "\n"
        "============== Hlavní menu ==============\n"
        "I - Inicializace / zruseni stromu\n"
        "T - Tisk stromu\n"
        "V - Vlozeni noveho prvku\n"
        "O - Odebrani prvku podle klice\n"
        "K - Konec programu\n"
        "-----------------------------------------\n"
        "Rozsirene operace:\n"
        "8 - Najdi minimum\n"
        "9 - Najdi maximum\n"
        "A - Najdi konkretni klic\n"
        "B - Vypis vsechny klíče < nez zadany\n"
        "C - Vypis vsechny klíče > nez zadany\n"
        "D - Smaz list podle klice\n"
        "E - Vypis klíčů vzestupne (in-order)\n"
        "F - Vypis klíčů sestupne (reverse in-order)\n"
        "H - Vypocet vahy a vysky stromu\n"
        "-----------------------------------------\n"
        "Tva volba: "
    );
}


/** Volba pro obsluhu menu. */
char zjistiVolbu(void)
{
    char volba;
    scanf(" %c", &volba);

    int c;
    while((c = getchar()) != EOF && c != '\n') {}

    return volba;
}

int main(void)
{
    Tstrom *strom = bvsInit();
    int klic = 4;

    char volba;
    int konec = 0;

    do {
        menu();  // Zobrazí uživatelské menu
        volba = zjistiVolbu();
        switch (toupper(volba))
        {
            case '8': {
                Tuzel *u = najdiMinimum(strom);
                if (u != NULL)
                    printf("Nejmensi prvek: %f\n", u->data);
                else
                    printf("Strom je prazdny.\n");
                break;
            }
            case '9': {
                Tuzel *u = najdiMaximum(strom);
                if (u != NULL)
                    printf("Nejmensi prvek: %f\n", u->data);
                else
                    printf("Strom je prazdny.\n");
                break;
            }
            case 'A': {
                Tuzel *u = bvsNajdi(strom, klic);
                if (u != NULL)
                    printf("Nejmensi prvek: %f\n", u->data);
                else
                    printf("Strom je prazdny.\n");
                break;
            }
            case 'B':
                vypisMensiNez(strom, klic);
                break;

            case 'C':
                vypisVetsiNez(strom, klic);
                break;

            case 'D':
                if (zrusVybranyList(strom, klic)) {
                    printf("List byl zrusen\n");
                } else {
                    printf("List se nepodarilo zrusit\n");
                }
                break;

            case 'E':
                vypisInOrder(strom);
                break;

            case 'F':
                vypisInOrderReverse(strom);
                break;

            case 'H':
                printf("Vaha stromu: %d\n Vyska stromu: %d\n", bvsPruchodVaha(strom), vyskaStromu(strom));
                break;

            case 'I':
                bvsZrus(strom);
                strom = bvsInit();
                vlozeni10Uzlu(strom);
                printf("Strom byl zrusen a znovu inicializovan.\n");
                break;

            case 'T':
                printf("Aktualni podoba stromu:\n");
                SuperTisk(stdout, strom->koren);
                printf("Pocet uzlu stromu: %d\n", bvsVaha(strom));
                break;

            case 'V':
                {
                    printf("Zadej hodnotu klice pro vlozeni (kladne cele cislo):\n");
                    int klic;
                    float data;
                    scanf(" %d", &klic);

                    printf("Zadej data ke klici %d (kladne desetinne cislo):\n", klic);
                    scanf(" %f", &data);

                    if (data < 0) data = -data;

                    if (bvsVloz(strom, klic, data))
                        printf("Uspech. Par (%d - %g) byl uspesne vlozen.\n", klic, data);
                    else
                        printf("Neuspech. Par (%d - %g) nebyl vlozen (duplikat?).\n", klic, data);
                }
                break;

            case 'O':
                {
                    printf("Zadej hodnotu klice listu, ktery chces odebrat:\n");
                    int klic;
                    scanf(" %d", &klic);

                    if (zrusVybranyList(strom, klic))
                        printf("Uspech. Klic %d byl odebran ze stromu.\n", klic);
                    else
                        printf("Neuspech. Klic %d nebyl ve stromu nalezen.\n", klic);
                }
                break;

            case 'K':
                printf("Rusim strom a koncim.\n");
                konec = 1;
                break;

            default:
                printf("Neznamy prikaz. Zkus to znovu.\n");
                break;
        }

    } while (!konec);

    bvsZrus(strom);
    return EXIT_SUCCESS;
}

