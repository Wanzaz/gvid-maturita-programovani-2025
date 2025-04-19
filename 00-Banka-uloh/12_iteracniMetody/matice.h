/* Modul pro práci s maticemi.
 *
 * Copyright (c) David Martinek, 2018--2024
 *
 * Verze: 2.1
 * Errata:
 * - maticeVymenRadky: Opravena chybná podmínka testující, zda zadané indexy
     nejsou záporné.
 * - maticeCtiZeSouboru - Opraveno nevhodné rozhraní, kdy se matice vracela
 *   přes parametr a musela tak být vytvořena ještě před přečtením rozměrů
 *   ze souboru. Nově funkce matici sama vyrobí, načte a vrátí ukazatel na ni
 *   jako svou funkční hodnotu. Chybový kód operace lze nově zpracovat pomocí
 *   funkce maticeChybovyStav a maticeChyboveHlaseni a maticeAktualniChyboveHlaseni.
 * - maticeCtiZeVstupu - Vyřešen stejný problém jako u funkce maticeCtiZeSouboru.
 *
 * Nové:
 * - Přidány funkce pro práci s chybovými stavy
 * -- maticeChybovyStav, maticeChyboveHlaseni, maticeAktualniChyboveHlaseni
 *
 *
 */

#ifndef MATICE_H_GUARD
#define MATICE_H_GUARD

#include <stdio.h>

#define LIB_VARIANT "Matice - pevna varianta"

#define MATICE_MAX_VELIKOST 100

/** \brief Deklarace typu Tmatice pro statickou matici.
 *
 * <p>Struktura zde obaluje pole pevné délky a skutečně využívané rozměry.
 * Výhodou takové stuktury je, že se snadno předává jako parametr a zvyšuje
 * přehlednost při práci s více maticemi. Nevýhodou je omezená maximální
 * velikost matice a zbytečné paměťové nároky při práci s menšími maticemi.
 * Z toho důvodu předáváme tuto strukturu vždy odkazem, nikdy hodnotou.</p>
 */
typedef struct
{
  float prvek[MATICE_MAX_VELIKOST][MATICE_MAX_VELIKOST]; /**< Dvourozměrné pole prvků. */
  int radku;   /**< Počet řádků matice. */
  int sloupcu; /**< Počet sloupců matice */
} Tmatice;


/** \brief Vytvoří matici zadaných rozměrů.
 *
 * \param matice Tmatice* Ukazatel na neinicializovanou proměnnou typu Tmatice.
 * \param radku uint      Počet řádků nové matice.
 * \param sloupcu uint    Počet sloupců nové matice.
 * \return Tmatice*       Ukazatel na strukturu s maticí nebo NULL.
 *
 * <p>Pokud je matice vyráběna staticky, musí být rozměry menší
 * než hodnota MATICE_MAX_SIZE, jinak funkce vrací NULL.</p>
 *
 * <p>Funkce končí s chybou i v případě, že zadané rozměry jsou nulové.</p>
 */
Tmatice * maticeAlokuj(int radku, int sloupcu);


/** \brief Zruší zadanou matici.
 *
 * \param matice Tmatice* Ukazatel na ničenou matici.
 *
 * <p>Uvolní alokovanou paměť.</p>
 */
void maticeUvolni(Tmatice *matice);


/** \brief Inicializuje všechny prvky matice počáteční hodnotou.
 *
 * \param matice Tmatice*   Ukazatel na alokovanou matici.
 * \param hodnota float    Nová hodnota všech prvků.
 *
 * <p>Inicializovaná matice již musí být vytvořena pomocí maticeAlokuj. Při
 * pokusu o inicializaci matice, která nebyla řádně vytvořena, může dojít
 * k havárii, zvláště u dynamicky vytvořené matice.</p>
 */
void maticeNastavPrvky(Tmatice *matice, float hodnota);


/** \brief Vytvoří duplikát zadané matice.
 *
 * \param zdroj const Tmatice* Zdrojová matice.
 * \return Tmatice* Vrací ukazatel na nově vyrobenou matici nebo NULL, když
 *                  není dost paměti.
 *
 */
Tmatice * maticeDuplikat(const Tmatice *zdroj);


/** \brief Inicializuje všechny prvky matice náhodnými hodnotami.
 *
 * \param matice Tmatice* Ukazatel na alokovanou matici.
 *
 * <p>Inicializovaná matice již musí být vytvořena pomocí maticeAlokuj. Při
 * pokusu o inicializaci matice, která nebyla řádně vytvořena, může dojít
 * k havárii, zvláště u dynamicky vytvořené matice.</p>
 */
void maticeRandom(Tmatice *matice);


/** \brief Inicializuje všechny prvky matice na zadanou hodnotu.
 *
 * \param matice Tmatice* Ukazatel na alokovanou matici.
 * \param hodnota float Hodnota, na kterou budou všechny prvky matice nastaveny.
 *
 * <p>Inicializovaná matice již musí být vytvořena pomocí maticeAlokuj. Při
 * pokusu o inicializaci matice, která nebyla řádně vytvořena, může dojít
 * k havárii. Tato funkce je užitečná například při přípravě vstupních dat
 * pro numerické metody nebo při resetování hodnot matice na výchozí stav.</p>
 */
void inicializujMatici(Tmatice *matice, float hodnota);


/** \brief Vytiskne matici na obrazovku.
 *
 * \param matice const Tmatice* Ukazatel na řádně vyrobenou matici.
 * \return void
 *
 * <p>Matice se tiskne ve formátu "počet_řádků počet_sloupců prvky". Tento
 * formát je kompatibilní s funkcemi pro čtení matice.</p>
 *
 * <p>Matice musí být správně vytvořena. Při pokusu o tisk matice, která nebyla
 * řádně vytvořena, může dojít k havárii, zvláště u dynamicky vytvářené matice.
 * </p>
 */
void maticeTiskni(const Tmatice *matice);


/** \brief Vytiskne matici do souboru.
 *
 * \param soubor FILE*           Soubor otevřený pro zápis.
 * \param matice const Tmatice*  Ukazatel na řádně vyrobenou matici.
 *
 * <p>Matice se tiskne ve formátu "počet_řádků počet_sloupců prvky". Tento
 * formát je kompatibilní s funkcemi pro čtení matice.</p>
 *
 * <p>Matice musí být řádně vytvořena. Při pokusu o tisk matice, která nebyla
 * řádně vytvořena, může dojít k havárii, zvláště u dynamicky vytvářené matice.
 * </p>
 *
 * <p>Soubor musí být řádně otevřen pro zápis, jinak dojde při tisku k havárii.
 * </p>
 *
 * <p>Poznámka: Všimni si, že zde se předává otevřený soubor, ne jméno souboru.
 * Takto je totiž možné sem místo souboru předat stdout a tisknout na standardní
 * výstup. </p>
 */
void maticeTiskniSoubor(FILE *soubor, const Tmatice *matice);


/** \brief Přečte data ze stdin a vrátí je jako nově vyrobenou matici.
 *
 * \return Tmatice*  Ukazatel na nově alokovanou matici nebo NULL.
 *
 * <p>Matice se čte ve formátu "počet_řádků počet_sloupců prvky". Tento
 * formát je kompatibilní s funkcemi pro zápis matice.</p>
 *
 * <p>Může generovat chyby EMREAD a EMCREATE. V takových případech vrací NULL.
 * S chybovými kódy lze pracovat pomocí funkcí maticeChybovyStav
 * a maticeChyboveHlaseni.</p>
 */
Tmatice * maticeCtiZeVstupu(void);


/** \brief Přečte data ze souboru a vrátí je jako nově vyrobenou matici.
 *
 * \param file FILE* Soubor otevřený pro čtení.
 * \return Tmatice*  Ukazatel na nově alokovanou matici nebo NULL.
 *
 * <p>Pokud nebude soubor řádně otevřen pro čtení, dojde při pokusu o čtení
 * k havárii.</p>
 *
 * <p>Matice se čte ve formátu "počet_řádků počet_sloupců prvky". Tento
 * formát je kompatibilní s funkcemi pro zápis matice.</p>
 *
 * <p>Může generovat chyby EMREAD a EMCREATE. V takových případech vrací NULL.
 * S chybovými kódy lze pracovat pomocí funkcí maticeChybovyStav
 * a maticeChyboveHlaseni.</p>
 *
 * <p>Poznámka: Všimni si, že zde se předává otevřený soubor, ne jméno souboru.
 * Takto je totiž možné sem místo souboru předat stdin a číst ze standardního
 * vstupu. </p>
 */
Tmatice * maticeCtiZeSouboru(FILE *file);


/** \brief Vymění v matici řádky zadané pomocí indexů.
 *
 * <p>Pokud některý z indexů bude mimo matici nebo budou oba indexy totožné,
 * operace nic neudělá.</p>
 *
 * \param m Tmatice* Ukazatel na řádně alokovanou matici.
 * \param r1 int     Index prvního řádku.
 * \param r2 int     Index druhého řádku.
 */
void maticeVymenRadky(Tmatice *m, int r1, int r2);





/** \brief Deklarace chybových kódů pro jednotlivé operace. */
enum maticeErrors {
  EMOK,          /**< Kód pro stav bez chyby. */
  EMCREATE,      /**< Kód chyby při vytváření matice v paměti.  */
  EMREAD,        /**< Kód chyby při čtení ze souboru. */
  EMVYMENA,      /**< Kód chyby při chybné výměně řádků. */
  EMUNKNOWN,     /**< Kód neznámé chyby. */
};

/** \brief Vrací aktuální chybový stav.
 *
 * <p>Tento chybový stav se ukládá ve skryté proměnné vyrobené uvnitř modulu.
 * Tuto proměnnou nastavují všechny operace, které pracují s maticí a mohou
 * produkovat nějakou detekovatelnou chybu z výčtu maticeErrors.</p>
 *
 * <p>Chce-li uživatel zjistit chybový kód, musí tuto funkci zavolat okamžitě po
 * provedení dané operace.</p>
 */
int maticeChybovyStav(void);

/** \brief Tiskne chybové hlášení odpovídající aktuálnímu chybovému stavu.
 *
 * <p>Chybový stav je uložen v proměnné skryté uvnitř modulu.
 * Funkce je určena pro volání ihned po zavolání operace s maticí, která
 * produkuje nějakou detekovatelnou chybu.</p>
 *
 * \param errStream FILE* Soubor nebo datový proud pro tisk chybových hlášení.
 *    Tato funkce se bude typicky volat s argumentem stderr.
 */
void maticeAktualniChyboveHlaseni(FILE * errStream);

/** \brief Vytiskne hlášení podle zadaného chybového kódu.
 *
 * <p>Pokud si uživatel zapamatuje chybový kód operace vrácený funkcí
 * maticeChybovyStav, může odpovídající chybové hlášení vytisknout pomocí této
 * funkce později na místě, které mu více vyhovuje.</p>
 *
 * \param errStream FILE* Soubor nebo datový proud pro tisk chybových hlášení.
 * \param errCode int Chybový kód získaný funkcí maticeChybovyStav.
 */
void maticeChyboveHlaseni(FILE * errStream, int errCode);



#endif // MATICE_H_GUARD
