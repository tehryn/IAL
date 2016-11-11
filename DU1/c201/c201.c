
/* c201.c *********************************************************************}
{* Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Bohuslav Křena, říjen 2016
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu tList.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
** 
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu před prvním použitím,
**      DisposeList ... zrušení všech prvků seznamu,
**      InsertFirst ... vložení prvku na začátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zruší první prvek seznamu,
**      PostDelete .... ruší prvek za aktivním prvkem,
**      PostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na další prvek seznamu,
**      Active ........ zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální proměnná -- příznak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
//	L = malloc(sizeof(tList)); // alokace paměti
	if (L == NULL) { // chybny ukazatel
		Error();
		return;
	}
	L->First = L->Act = NULL; //inicializace ukazatelu
}

void DisposeList (tList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Veškerá paměť používaná prvky seznamu L bude korektně
** uvolněna voláním operace free.
***/
	struct tElem *temp; // pomocna promena
	while (L->First != NULL) { // Kontrola existence prvku pro smazani
		temp = L->First->ptr; // zachovani ukazatele na 2. polozku seznamu
		free(L->First); // uvolneni prvni polozky
		L->First = temp; // nastaveni puvodne 2. polozky jako 1. polozku seznamu
	}
	L->Act = NULL; // zruseni aktivity seznamu (pokud aktivni nebyl, operace paseku nenadela)
}

void InsertFirst (tList *L, int val) {
/*
** Vloží prvek s hodnotou val na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci Error().
**/
	struct tElem *item; // nova polozka seznamu
	item = malloc(sizeof(struct tElem)); // alokace pameti
	if (item == NULL) { // kontrola uspesnosti alokace
		Error();
		return;
	} 
	item->data = val; // inicializace uzitecnych dat
	item->ptr = L->First; // navazani seznamu
	L->First = item; // nastaveni teto polozky jako prvni polozku seznamu

}

void First (tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný příkaz, aniž byste testovali,
** zda je seznam L prázdný.
**/
	L->Act = L->First;
}

void CopyFirst (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/
	if (L->First != NULL) // kontrola zda neni seznam prazdny
		*val = L->First->data; // prirazeni uzitecnych
	else // pokud je seznam prazdny... chyba...
		Error();
}

void DeleteFirst (tList *L) {
/*
** Zruší první prvek seznamu L a uvolní jím používanou paměť.
** Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se neděje.
**/
	if (L->First != NULL) { // kontrola zda neni seznam prazdny
		struct tElem *temp; // pomocna promena
		temp = L->First->ptr; // zachovani ukazatele
		if (L->Act == L->First) // zruseni aktivity souboru pokud byl aktivni prvni prvek seznamu
			L->Act = NULL;
		free(L->First); // uvolneni pameti
		L->First = temp; // nastaveni puvodne 2. polozky seznamu jako prvni polozku
	}
}	

void PostDelete (tList *L) {
/* 
** Zruší prvek seznamu L za aktivním prvkem a uvolní jím používanou paměť.
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se neděje.
**/
	if (L->Act == NULL || L->Act->ptr == NULL) return; // kontrola aktivity seznamu a existence nasledujiciho prvku
	struct tElem *temp; // pomocna promena
	temp = L->Act->ptr->ptr; // zachovani ukazatele
	free(L->Act->ptr); // uvolneni pameti
	L->Act->ptr = temp; // navazani seznamu
	
}

void PostInsert (tList *L, int val) {
/*
** Vloží prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje!
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** zavolá funkci Error().
**/
	if (L->Act == NULL) return; // kontrola aktivity seznamu
	struct tElem *item; // pomocna promena
	item = malloc(sizeof(struct tElem)); // alokace pameti
	if (item == NULL) { // kontrola uspesnosti alokace pameti
		Error();
		return;
	}
	item->ptr = L->Act->ptr; // navazani zbytku seznamu
	item->data = val; // inicializace uzitecnych dat
	L->Act->ptr = item; // vlozeni prvku do seznamu
}

void Copy (tList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
	if (L->Act == NULL) { // kontrola aktivity seznamu
		Error();
		return;
	}
	*val = L->Act->data; // prirazeni uzitecnych dat
}

void Actualize (tList *L, int val) {
/*
** Přepíše data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedělá nic!
**/
	if (L->Act == NULL) return; // kontrola aktivity seznamu
	L->Act->data = val;	// aktualizace uzitecnych dat
	
}

void Succ (tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
** Pokud není předaný seznam L aktivní, nedělá funkce nic.
**/
	if (L->Act == NULL) return; // kontrola aktivity seznamu
	L->Act = L->Act->ptr; // posunuti aktivity (popripade ztrata aktivity, pokud byl aktivni posledni prvek)
}

int Active (tList *L) {		
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Tuto funkci je vhodné implementovat jedním příkazem return. 
**/
	return L->Act!=NULL;
}

/* Konec c201.c */
