/* Téma matice a moduly - varianta s polem pevných rozměrů
 *
 * Autor: Podepiš se
 * Datum: today (+ Ctrl+J)
 *
 * Verze: 2.1
 * Errata:
 * - maticeVymenRadky: viz záhlaví souboru matice.h
 * - maticeCtiZeSouboru: viz záhlaví souboru matice.h
 * - maticeCtiZeVstupu: viz záhlaví souboru matice.h
 * - testFileRW: Opraveno nesmyslné alokování prázdné matice před čtením
 *   ze souboru.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include <time.h>

#include "matice.h"

enum gemErrors {
    OK,          /**< Kód pro stav bez chyby. */
    CHYBA_RESENI,      /**< Kód chyby kdyz na diagonale je 0.  */
};



/** \brief Otestuje operace maticeAlokuj, maticeRandom a maticeTiskni. */
void testInit(void)
{
  printf("==========================================\n");
  printf("Test vytvoreni a inicializace matice\n");
  Tmatice * matice = maticeAlokuj(50000000, 30000000);
//  Tmatice * matice = maticeAlokuj(5, 3);
//  maticeNastavPrvky(matice, 1.2);
  if (matice == NULL)
  { // Matici se nepovedlo vytvořit, tak vytisknu proč a skončím.
    maticeAktualniChyboveHlaseni(stderr);
    return;
  }
  maticeRandom(matice);
  maticeTiskni(matice);

  maticeUvolni(matice);

  printf("==========================================\n");
}






/** \brief Otestuje funkce pro čtení ze a zápis do souboru.
 *
 * \param input char*   Jméno vstupního souboru nebo NULL
 * \param output char*  Jméno výstupního souboru nebo NULL
 * \return int Vrací EXIT_FAILURE v případě chyby při práci se soubory.
 *
 * <p>Pokud je místo jména vstupního nebo výstupního souboru prázdný ukazatel
 * NULL, použije se soubor stdin nebo stdout.</p>
 *
 */
void testFileRW(char *input, char *output)
{
  printf("==========================================\n");
  printf("Test cteni a zapisu ze a do souboru\n");
  FILE *fin = stdin;
  FILE *fout = stdout;

  if (input != NULL)
    fin = fopen(input, "r");

  if (output != NULL)
    fout = fopen(output, "w");

  if (fin == NULL)
  {
    fprintf(stderr, "Chybny nazev vstupniho souboru.");
    fin = stdin;
    input = NULL;
  }

  if (fout == NULL)
  {
    fprintf(stderr, "Chybny nazev vystupniho souboru.");
    fout = stdout;
    output = NULL;
  }

  // Tady teď není potřeba volat funkci maticeAlokuj, protože to se už dělá
  // uvnitř funkce maticeCtiZeSouboru.
  Tmatice * m = maticeCtiZeSouboru(fin);
  if (m != NULL)
  { // Není chyba => zpracuji načtenou matici.
    maticeTiskniSoubor(fout, m);
    maticeUvolni(m);
  }
  else
  { // Při chybě tisknu chybové hlášení, zavřu soubory a končím.
    maticeAktualniChyboveHlaseni(stderr);
  }

  if (input != NULL) fclose(fin);
  if (output != NULL) fclose(fout);
  printf("==========================================\n");
  return;
}


/** \brief Vynásobí dvě matice a výsledek uloží do třetí nové matice.
 *
 * \param a const Tmatice* První vstupní matice.
 * \param b const Tmatice* Druhá vstupní matice.
 * \param c Tmatice* Výsledná, zatím nevytvořená matice.
 * \return bool Vrací true, pokud se operace povedla, jinak false.
 *
 * <p>Parametr c musí ukazovat na prozatím nevytvořenou matici, jinak dojde ke
 * ztrátě dat.</p>
 *
 * <p>Pokud jsou vstupní matice kompatibilní, tj. a->sloupcu == b->radku, dojde
 * k vytvoření výsledné matice o rozměrech c->radku = a-radku a c->sloupcu = b->sloupcu.
 * Do této matice pak bude uložen výsledek násobení a*b v tomto pořadí.</p>
 *
 * <p>Pozor! Operace maticového násobení není komutativní, tudíž záleží na
 * pořadí operandů.</p>
 */
Tmatice * maticeMult(const Tmatice *a, const Tmatice *b)
{
  if (a->sloupcu != b->radku)
    return NULL;

  Tmatice * c = maticeAlokuj(a->radku, b->sloupcu);
  if (c == NULL)
    return NULL;

  for (int row = 0; row < c->radku ; ++row)
  {
    for (int col = 0; col < c->sloupcu ; ++col)
    {
      double ssum;
      ssum = 0.0;
      for (int k = 0; k < a->sloupcu ; ++k)
      {
        ssum += a->prvek[row][k] * b->prvek[k][col];
      }
      c->prvek[row][col] = ssum;
    }
  }
  return c;

//  Poznámka: Všimni si, že operace se sama stará o alokaci výsledku a ošetření
//  chyb, které to může generovat. Jako autor takové operace nemůžu chtít po
//  uživateli (této funkce), aby před samotným spuštěním funkce prováděl nějaké
//  kroky nutné pro správné chování této funkce. Programy, které toto vyžadují,
//  jsou takzvaně "křehké", což je protiklad k programům "robustním".
}

/** \brief Test operací maticeRandom a maticeMult. */
void testMult(void)
{
  printf("==========================================\n");
  printf("Test nasobeni nahodnych matic\n");
  Tmatice * a = maticeAlokuj(4, 2);
  Tmatice * b = maticeAlokuj(2, 3);

  maticeRandom(a);
  maticeRandom(b);

  maticeTiskni(a);
  printf("*\n");
  maticeTiskni(b);
  printf("=\n");
  Tmatice * c = maticeMult(a, b);
  if (c != NULL)
  {
    maticeTiskni(c);
    maticeUvolni(c);
  }
  else
    printf("Tohle nejde!\n");

  maticeUvolni(a);
  maticeUvolni(b);
  printf("==========================================\n");
}




/** \brief Vrátí index řádku s pivotem.
 *
 * Poznámka: Použij funkci fabs pro práci s absolutní hodnotou.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \param r int Index referenčního řádku (a sloupce)
 * \return int Index řádku s pivotem.
 *
 */
int maxAbsPivot(Tmatice *m, int r)
{
    int maxi = r;
    for (int radek = r + 1; radek <= m->radku - 1; ++radek) {
        if (fabs(m->prvek[radek][r]) > fabs(m->prvek[maxi][r])) {
            maxi = radek;
        }
    }

    return maxi;
}


/** \brief Testuje, zda je zadaná soustava ve tvaru horní trojúhelníkové matice.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \return bool Vrací logickou hodnotu.
 *
 */
bool jeHorni(Tmatice *m)
{
    // Procházíme všechny řádky
    for (int radek = 0; radek < m->radku - 1; ++radek) {
        // Kontrola diagonálního prvku
        if (m->prvek[radek][radek] == 0.0 ) {
            return false;  // Pokud je jakýkoli diagonální prvek 0, vrátíme false
        }
        // Procházíme prvky pod diagonálou
        for (int sloupec = 0; sloupec < radek; ++sloupec) {
            // Pokud najdeme prvek pod diagonálou, který není 0, vrátíme false
            if (m->prvek[radek][sloupec] != 0.0) {
                return false;
            }
        }
    }
    // Pokud jsou všechny podmínky splněny, matice je horní trojúhelníková a diagonální prvky jsou nenulové
    return true;
}


/** \brief vraci jestli je matice upravena funkci GJEM == je nulova krome diagonaly
 *
 * \param Tmatrix *m
 * \return true false
 *
 */
bool jePoGJEM(Tmatice *m)
{
    for(int r = 0; r < m->radku; r++)
    {
        if (m->prvek[r][r] == 0.0) return false;

        for(int s = 0 ; s < m->sloupcu - 1; s++)
        {
            if(r != s && m->prvek[r][s] != 0.0)
            {
                return false;
            }

        }
    }

    return true;
}


/** \brief Provadi radkove upravy v matici
 *
 * \param m Tmatice* Ukazatel na alokovanou matici.
 * \param radku int  Radek na kterem probehne uprava
 * \return void
 */
void radkoveUpravy(Tmatice *m, int r)
{
    for (int radek = r + 1; radek < m->radku; ++radek) {
        float koeficient = m->prvek[radek][r] / m->prvek[r][r]; // koeficient pro úpravu řádku
        m->prvek[radek][r] = 0.0;  // Nulování prvků pod diagonálním prvkem

        // Úprava zbývajících sloupců
        for (int sloupec = r + 1; sloupec < m->sloupcu; ++sloupec) {
            m->prvek[radek][sloupec] = m->prvek[r][sloupec] * koeficient - m->prvek[radek][sloupec];
        }
    }
}


/** \brief Provede přímý chod GEM.
 *
 * Změní vstupní matici na ekvivalentní horní trojúhelníkovou matici. Využije
 * přitom pivotování a ekvivalentních úprav.
 *
 * Poznámka: Vytvoř si samostatnou funkci pro pivotování a samostatnou funkci
 * pro aplikaci ekvivalentních úprav (nulování prvků pod diagonálním prvkem),
 * které zde zavoláš.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \return int Vrací kód chyby.
 */
int gemPrimy(Tmatice *m)
{
    for (int r = 0; r < m->radku; ++r) { // Jedu do radku n - 2

        int p = maxAbsPivot(m, r); // index pivota
        if (m->prvek[p][r] == 0.0) { // 0 nesmí být na diagonále
            return CHYBA_RESENI;
        }

        if (r != p) { // aby se neměnily stejné řádky..
            maticeVymenRadky(m, r, p);
        }

        radkoveUpravy(m, r);
    }

    return OK;
}

/**
 * \brief Provádí úpravy v matici nad zadaným řádkem (pivotem)
 *
 * \param m Tmatice* Ukazatel na alokovanou matici.
 * \param r int Index řádku, na kterém proběhne úprava (pivot).
 * \return void
 */
void radkoveUpravyJordan(Tmatice *m, int r)
{
    // Jeden for cyklus pro úpravu všech řádků nad i pod r-tým řádkem
    for (int radek = 0; radek < m->radku; radek++) {
        if (radek == r) { // Přeskočíme úpravu diagonálního řádku
            continue;
        }

        float konstanta = m->prvek[radek][r] / m->prvek[r][r];
        m->prvek[radek][r] = 0.0; // Nastavíme nulu v aktuálním sloupci

        // Druhý for cyklus pro úpravu všech sloupců
        for (int s = r + 1; s < m->sloupcu; s++) {
            m->prvek[radek][s] = m->prvek[radek][s] - konstanta * m->prvek[r][s];
        }
    }
}

void radkoveUpravyJordan2(Tmatice *m,int r)
{
    for(int i = r+1; i<m->radku;i++)
    {
        float konstanta = m->prvek[i][r]/m->prvek[r][r];
        m->prvek[i][r] = 0.0;
        for(int s = r+1; s<m->sloupcu;s++)
        {
            m->prvek[i][s] = konstanta * m->prvek[r][s] - m->prvek[i][s];
        }
    }
    for(int k =r-1;  k >=0; k--){
        float c = m->prvek[k][r] / m->prvek[r][r];
        for(int s = r; s< m->sloupcu; s++){
            m->prvek[k][s] = m->prvek[k][s] - c * m->prvek[r][s];
        }
        m->prvek[k][r] = 0;
    }
}


/** \brief Provede přímý chod GJEM.
 *
 * Změní vstupní matici na ekvivalentní diagonální matici.
 *
 * Poznámka: Výsledná matice může, ale nemusí být jednotková.
 *
 * Poznámka: Funkci vytvoříš úpravou funkce gemPrimy.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 */
int gjemPrimy(Tmatice *m)
{
    for (int r = 0; r < m->radku; r++) {
        int pivot = maxAbsPivot(m, r);
        if (m->prvek[r][r] == 0) {
            return CHYBA_RESENI;
        }

        if (pivot != r) {
            maticeVymenRadky(m, pivot, r);
        }

        radkoveUpravyJordan(m, r);
    }
    return OK;
}


/** \brief Test přímého chodu, tj. operací gemPrimy a gjemPrimy.
 *
 * Zadání:
 * Pro řešení využij funkce z modulu matice.h a funkce gemPrimy a gjemPrimy.
 * 1. Načti soubor s maticí (nebo si ji inicializuj přímo tady ve funkci).
 *    Pomocí funkce maticeDuplikat si vyrob její duplikát.
 * 2. Proveď na ní přímý chod GEM a vytiskni výsledek.
 * 2. Na duplikátu vstupní matice proveď přímý chod GJEM a vytiskni výsledek.
 * 3. Ukliď po sobě.
 */
void testPrimehoChodu(char *jmenoSouboru)
{
    printf("==========================================\nTest přímého chodu GJEM a GEM\n==========================================\n");

    FILE *f = fopen(jmenoSouboru, "r");
    if (!f) {
        fprintf(stderr, "Chyba: Soubor se nepodařilo otevřít.\n");
        return;
    }

    Tmatice *m = maticeCtiZeSouboru(f);
    fclose(f);
    if (!m) {
        fprintf(stderr, "Chyba: Nepodařilo se načíst matici.\n");
        return;
    }

    Tmatice *m2 = maticeDuplikat(m);
    if (!m2) {
        fprintf(stderr, "Chyba: Nepodařilo se vytvořit duplikát matice.\n");
        maticeUvolni(m);
        return;
    }

    if (gjemPrimy(m) == CHYBA_RESENI) printf("Chyba: GJEM - Matice nemá řešení.\n");
    if (gemPrimy(m2) == CHYBA_RESENI) printf("Chyba: GEM - Matice nemá řešení.\n");

    printf("Původní matice po GJEM:\n");
    maticeTiskni(m);
    printf("================================================\nDuplikát matice po GEM:\n");
    maticeTiskni(m2);

    maticeUvolni(m);
    maticeUvolni(m2);
    printf("==========================================\n");
}



/** \brief Vrací počet řešení upravené soustavy po provedení přímého chodu GEM.
 *
 * Součástí testu jsou i správné rozměry.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \return bool Vrací hodnotu 1, když matice je rozšířenou maticí soustavy
 *              ve tvaru po provedení přímého chodu Gaussovy eliminační metody
 *              a soustava je dále řešitelná. Hodnotu 0 vrací, když soustava
 *              není ve tvaru horní trojúhelníkové matice nebo nemá žádné
 *              řešení. Hodnotu -1 vrací, když má soustava nekonečně mnoho
 *              řešení.
 */
/** \brief Vrací počet řešení upravené soustavy po provedení přímého chodu GJEM.
 *
 * Součástí testu jsou i správné rozměry.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 * \return bool Vrací hodnotu 1, když matice je rozšířenou maticí soustavy
 *              ve tvaru po provedení přímého chodu Gauss-Jordanovy eliminační
 *              metody a soustava je dále řešitelná. Hodnotu 0 vrací, když
 *              soustava není ve tvaru diagonální matice nebo nemá žádné
 *              řešení. Hodnotu -1 vrací, když má soustava nekonečně mnoho
 *              řešení.
 */
int gemGjemPoPrimem(Tmatice *m)
{
    // Zkontroluj, zda je matice ve tvaru horní trojúhelníkové matice
    if (m->sloupcu != m->radku + 1 || m->sloupcu < 0 || m->radku < 0 || !jeHorni(m)) {
        return 0;
    }

    // Pokud poslední prvek před pravou stranou není nulový, soustava má jedno řešení
    if (m->prvek[m->radku - 1][m->sloupcu - 2] != 0) {
        return 1; // Jedno řešení
    }

    // Pokud poslední prvek je nulový, soustava má nekonečně mnoho řešení
    if (m->prvek[m->radku - 1][m->sloupcu - 1] == 0) {
        return -1; // Nekonečně mnoho řešení
    }

    return 0; // Žádné řešení
}


/** \brief Test matic po přímém chodu
 *
 * Zadání:
 * Pro řešení využij předchozí hotové funkce.
 * 1. Načti soubor s maticí (nebo si ji inicializuj přímo tady ve funkci).
 * 2. Otestuj ji a vytiskni, zda jde o matici po provedení přímého chodu GEM nebo GJEM.
 * 3. Pokud nejde o upravenou matici, proveď přímý chod GEM, GJEM (funkce pro
 *    to už máš hotové).
 * 4. Výsledek znovu otestuj.
 * 5. Vypiš, kolik řešení zadaná soustava má (0, 1, nekonečno).
 */
void testMaticePoPrimemChodu(char *jmenoSouboru)
{
    printf("==========================================\n");
    printf("Test matice po přímém chodu\n");
    printf("==========================================\n");

    FILE *f = fopen(jmenoSouboru, "r");
    if (f == NULL) {
        printf("Soubor se nepodařilo otevřít.\n");
        return;
    }

    Tmatice *m = maticeCtiZeSouboru(f);
    fclose(f);
    if (m == NULL) {
        printf("Nepovedlo se načíst matici.\n");
        return;
    }

    if (!jePoGJEM(m)) {
        maticeTiskni(m);
        printf("\nMatice není upravena na požadovaný tvar.\n");
        printf("Probíhá GJEM...\n\n");
        if (gjemPrimy(m) == -1) {
            printf("\nNelze upravit tuto matici.\n");
            maticeUvolni(m);
            return;
        }
    }

    maticeTiskni(m);

    // Testování počtu řešení po GEM
    if (jePoGJEM(m)) {
        printf("\nTvar matice odpovídá tvaru po provedení přímého chodu GJEM.\n");

        // Testování počtu řešení GEM
        int reseniGEM = gemGjemPoPrimem(m);
        if (reseniGEM == -1) {
            printf("\nMatice má nekonečno řešení.\n");
        } else {
            printf("\nMatice má %d řešení (GJEM).\n", reseniGEM);
        }
    } else {
        printf("Chyba: Matice není ve správném tvaru po GJEM.\n");
    }

    // Zde se přidá testování počtu řešení po GEM
    printf("\nProvádím přímý chod GEM...\n");
    Tmatice *m2 = maticeDuplikat(m); // Vytvoření duplikátu pro GEM
    if (gemPrimy(m2) == -1) {
        printf("\nMatice má nekonečno řešení (GEM).\n");
    } else {
        int reseniGEM = gemGjemPoPrimem(m2);
        printf("\nMatice má %d řešení (GEM).\n", reseniGEM);
    }

    // Vytisknutí matice po GEM
    printf("\nMatice po GEM:\n");
    maticeTiskni(m2);

    maticeUvolni(m);
    maticeUvolni(m2);
}


/** \brief Provede zpětný chod GEM.
 *
 * Hodnoty neznámých nastaví do posledního sloupce rozšířené matice soustavy.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 */
void gemZpetny(Tmatice *m)
{
    // Procházej od posledního řádku k prvnímu
    for (int radek = m->radku - 1; radek >= 0; --radek) {
        // Inicializuj proměnnou pro uložení hodnoty
        float suma = 0.0;

        // Procházej sloupce v aktuálním řádku, kromě posledního
        for (int sloupec = radek + 1; sloupec < m->sloupcu - 1; ++sloupec) {
            // Odečti hodnoty neznámých násobené koeficienty z aktuálního řádku
            suma += m->prvek[radek][sloupec] * m->prvek[sloupec][m->radku];
        }

        // Vypočítaná hodnota se uloží do posledního sloupce
        m->prvek[radek][m->sloupcu - 1] = (m->prvek[radek][m->sloupcu - 1] - suma) / m->prvek[radek][radek];
    }
}

/** \brief Provede zpětný chod GEM na i-tem radku (predpoklada se, ze na dalsich radsich jiz vypocet probehl)
 *
 * Hodnoty neznámých nastaví do posledního sloupce rozšířené matice soustavy.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 */
void gemZpetnyNaRadku(Tmatice *m, int radek)
{
    // Inicializuj proměnnou pro uložení hodnoty
    float suma = 0.0;

    // Procházej sloupce v aktuálním řádku, kromě posledního
    for (int sloupec = radek + 1; sloupec < m->sloupcu - 1; ++sloupec) {
        // Odečti hodnoty neznámých násobené koeficienty z aktuálního řádku
        suma += m->prvek[radek][sloupec] * m->prvek[sloupec][m->radku];
    }

    // Vypočítaná hodnota se uloží do posledního sloupce
    m->prvek[radek][m->sloupcu - 1] = (m->prvek[radek][m->sloupcu - 1] - suma) / m->prvek[radek][radek];
}


/** \brief Provede zpětný chod GJEM.
 *
 * Hodnoty neznámých nastaví do posledního sloupce rozšířené matice soustavy.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 */
void gjemZpetny(Tmatice *m)
{
    for (int r = m->radku - 1; r >= 0; r--) {
        m->prvek[r][m->sloupcu - 1] /= m->prvek[r][r];
    }
}


/** \brief Tiskne řešení soustavy rovnic, které je uloženo v posledním sloupci rozšířené matice soustavy.
 *
 * \param m Tmatice* Ukazatel na rozšířenou matici soustavy.
 */
void tiskReseni(Tmatice *m)
{
  printf("Reseni soustavy rovnic:\n");
  for (int r = 0; r < m->radku; ++r)
  {
    printf("x%d = %f\n", r, m->prvek[r][m->sloupcu-1]);
  }
}


/** \brief Vyřeší upravenou soustavu rovnic.
 *
 * Zadání:
 * Pro řešení využij funkce z modulu matice.h a funkce gemPoPrimem, gjemPoPrimem, gemZpetny a gjemZpetny.
 * 1. Načti soubor s maticí.
 * 1a. Uprav ji do požadovaného tvaru pro zpětný chod.
 * 2. Otestuj zda jde o matici s jedním řešením po provedení přímého chodu GEM nebo GJEM.
 * 3. Vyřeš ji.
 * 4. Vypiš řešení soustavy pomocí funkce tiskReseni.
 */
void testZpetnyChod(char *jmenoSouboru)
{
    printf("==========================================\n");
    printf("Test zpětného chodu GJEM a GEM na matici\n");
    printf("==========================================\n");

    // Test pro GJEM
    FILE *f = fopen(jmenoSouboru, "r");
    if (f == NULL) {
        printf("Soubor se nepodařilo otevřít.\n");
        return;
    }
    Tmatice *m = maticeCtiZeSouboru(f);
    fclose(f);
    if (m == NULL) {
        printf("\nNepovedlo se načíst matici.\n");
        return;
    }
    maticeTiskni(m);
    if (!jePoGJEM(m)) {
        printf("\nProbíhá GJEM...\n\n");
        gjemPrimy(m);
        maticeTiskni(m);
    }

    int pocetReseniGJEM = gemGjemPoPrimem(m);
    if (pocetReseniGJEM == 1) {
        gjemZpetny(m);
        tiskReseni(m);
    } else if (pocetReseniGJEM == 0) {
        printf("\nMatice nemá žádné řešení (GJEM).\n");
    } else {
        printf("\nMatice má nekonečno řešení (GJEM).\n");
    }

    maticeUvolni(m);

    // Test pro GEM
    printf("==========================================\n");
    printf("Test zpětného chodu GEM na matici\n");
    printf("==========================================\n");

    f = fopen(jmenoSouboru, "r");
    if (f == NULL) {
        printf("Soubor se nepodařilo otevřít.\n");
        return;
    }
    Tmatice *m2 = maticeCtiZeSouboru(f);
    fclose(f);
    if (m2 == NULL) {
        printf("\nNepovedlo se načíst matici.\n");
        return;
    }
    maticeTiskni(m2);
    if (!jeHorni(m2)) {
        printf("\nProbíhá GEM...\n\n");
        gemPrimy(m2);
        maticeTiskni(m2);
    }

    int pocetReseniGEM = gemGjemPoPrimem(m2);
    if (pocetReseniGEM == 1) {
        gemZpetny(m2);
        tiskReseni(m2);
    } else if (pocetReseniGEM == 0) {
        printf("\nMatice nemá žádné řešení (GEM).\n");
    } else {
        printf("\nMatice má nekonečno řešení (GEM).\n");
    }

    maticeUvolni(m2);
    printf("==========================================\n");
}




/** Startovní bod programu. */
int main(void)
{
  // srand(time(NULL));
  // testInit();
  // testFileRW("A.txt", NULL); // NULL -> bude zapisovat na stdout
  // testMult();

  testPrimehoChodu("A.txt");
  testMaticePoPrimemChodu("A.txt");
  testZpetnyChod("A.txt");
  return EXIT_SUCCESS;
}
