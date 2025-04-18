/* Modul pro práci s maticemi.
 *
 * Copyright (c) David Martinek, 2018--2024
 */

#include "matice.h"
#include <stdio.h>
#include <stdlib.h>

// Skrytá globální proměnná modulu, která slouží pro uchování chybového stavu
// po poslední provedené operaci s maticí.
int _chybovyStav = EMOK;

// Skrytá globální konstanta modulu s chybovými hlášeními odpovídajícími
// chybovým kódům.
const char * _CHYBOVE_HLASENI[] = {
  [EMOK     ] = "To je divne! Neregistruji zadnou chybu.",
  [EMCREATE ] = "Malo pameti pro vytvoreni matice.",
  [EMREAD   ] = "Chyba pri cteni vstupnich dat.",
  [EMVYMENA ] = "Chybne zadane indexy pro vymenu radku.",
  [EMUNKNOWN] = "Neznama chyba! Vezmi nohy na ramena a utec!",
};

/** \brief Vrací aktuální chybový stav. */
int maticeChybovyStav(void)
{
  return _chybovyStav; // Takto jde chybový stav přečíst, ale ne nastavit.
}

void maticeChyboveHlaseni(FILE * errStream, int errCode)
{
  if (errCode < 0 || errCode > EMUNKNOWN)
    errCode = EMUNKNOWN;
  fprintf(errStream, "Maticova chyba: %s\n", _CHYBOVE_HLASENI[errCode]);

}

/** \brief Tiskne chybové hlášení odpovídající aktuálnímu chybovému stavu. */
void maticeAktualniChyboveHlaseni(FILE * errStream)
{
  maticeChyboveHlaseni(errStream, _chybovyStav);
}






/** \brief Vytvoří matici zadaných rozměrů.*/
Tmatice * maticeAlokuj(int radku, int sloupcu)
{
  if (radku <= 0 || radku > MATICE_MAX_VELIKOST ||
      sloupcu <= 0 || sloupcu > MATICE_MAX_VELIKOST)
  {
    _chybovyStav = EMCREATE;
    return NULL;
  }

  // Tady se dynamicky alokuje jen struktura typu Tmatice.
  // Samotné pole uvnitř má v této implementaci pevné rozměry, přičemž
  // my z něj využijeme jen část odpovídající rozměrům radku a sloupcu.
  // Skutečně dynamická 2D matice se dělá jinak.
  Tmatice * m = malloc(sizeof(Tmatice));
  if (m == NULL)
  {
    _chybovyStav = EMCREATE;
    return NULL;
  }

  m->radku = radku;
  m->sloupcu = sloupcu;

  return m;
}


/** \brief Zruší zadanou matici.*/
void maticeUvolni(Tmatice *matice)
{
  // Takto jednoduše to jde jen v naší primitivní implementaci. Skutečné
  // 2D dynamické pole by se muselo rušit postupně po řádcích.
  free(matice);
  _chybovyStav = EMOK;
}


/** \brief Inicializuje všechny prvky matice počáteční hodnotou.*/
void maticeNastavPrvky(Tmatice *matice, float initValue)
{
  for (int r = 0; r < matice->radku ; ++r)
  {
    for (int s = 0; s < matice->sloupcu ; ++s)
    {
      matice->prvek[r][s] = initValue;
    }
  }
  _chybovyStav = EMOK;
}


/** \brief Vytvoří duplikát zadané matice. */
Tmatice * maticeDuplikat(const Tmatice *zdroj)
{
  Tmatice *m = maticeAlokuj(zdroj->radku, zdroj->sloupcu);
  if (m != NULL)
  {
    for (int r = 0; r < zdroj->radku; ++r)
    {
      for (int s = 0; s < zdroj->sloupcu; ++s)
      {
        m->prvek[r][s] = zdroj->prvek[r][s];
      }
    }
    _chybovyStav = EMOK;
  }

  return m;
}


/** \brief Inicializuje všechny prvky matice náhodnými hodnotami. */
void maticeRandom(Tmatice *matice)
{
  for (int r = 0; r < matice->radku ; ++r)
  {
    for (int s = 0; s < matice->sloupcu ; ++s)
    {
      {
        matice->prvek[r][s] = (float)((rand()%2000)-1000) / 100;
      }
    }
  }
  _chybovyStav = EMOK;
}

/** \brief Inicializuje danou matici na konkrétní hodnotu */
void inicializujMatici(Tmatice *matice, float hodnota) {
    if (matice == NULL) {
        printf("Chyba: Matice je NULL.\n");
        return;
    }

    for (int r = 0; r < matice->radku; ++r) {
        for (int s = 0; s < matice->sloupcu; ++s) {
            matice->prvek[r][s] = hodnota;
        }
    }
    _chybovyStav = EMOK;
}







/** \brief Vytiskne matici na obrazovku.*/
void maticeTiskni(const Tmatice *matice)
{
  maticeTiskniSoubor(stdout, matice);
}


/** \brief Vytiskne matici do souboru.*/
void maticeTiskniSoubor(FILE *file, const Tmatice *matice)
{
  fprintf(file, "%u %u\n", matice->radku, matice->sloupcu);
  for (int r = 0; r < matice->radku ; ++r)
  {
    for (int s = 0; s < matice->sloupcu ; ++s)
    {
      fprintf(file, "%7.2f ", matice->prvek[r][s]);
    }
    fprintf(file, "\n");
  }
  _chybovyStav = EMOK;
}






/** \brief Přečte data ze stdin a vrátí je jako nově vyrobenou matici. */
Tmatice * maticeCtiZeVstupu(void)
{
  return maticeCtiZeSouboru(stdin);
}


/** \brief Přečte data ze souboru a vrátí je jako nově vyrobenou matici. */
Tmatice * maticeCtiZeSouboru(FILE *file)
{
  int radku, sloupcu;
  int ecode =  fscanf(file, "%d %d", &radku, &sloupcu);
  if (ecode != 2)
  { _chybovyStav = EMREAD;  return NULL; }

  Tmatice *m = maticeAlokuj(radku, sloupcu);
  if (m == NULL)
  { _chybovyStav = EMCREATE; return NULL; }

  for (int r = 0; r < m->radku ; ++r)
  {
    for (int s = 0; s < m->sloupcu ; ++s)
    {
      ecode = fscanf(file, "%f ", &m->prvek[r][s]);
      if (ecode != 1)
      { _chybovyStav = EMREAD;  return NULL; }
    }
  }

  _chybovyStav = EMOK;
  return m;
}






/** \brief Vymění v matici řádky zadané pomocí indexů.*/
void maticeVymenRadky(Tmatice *m, int r1, int r2)
{
  if (r1 == r2 || r1 < 0 || r2 < 0 || r1 >= m->radku || r2 >= m->radku)
  { _chybovyStav = EMVYMENA;  return; }

  for (int s = 0; s < m->sloupcu; ++s)
  {
    float pom = m->prvek[r1][s];
    m->prvek[r1][s] = m->prvek[r2][s];
    m->prvek[r2][s] = pom;
  }
  _chybovyStav = EMOK;
}


