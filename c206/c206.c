	
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Bohuslav Křena, říjen 2016
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu, 
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek, 
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku, 
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu, 
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem, 
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu, 
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
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

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
//    L = malloc(sizeof(tDLList)); // alokace pameti
    if (L == NULL) { // chybny ukazatel
    	DLError();
    	return;
    }
    L->First = L->Last = L->Act = NULL; // inicializace ukazetelu
	
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/

	struct tDLElem *temp; // pomocna promena
	while(L->First != NULL) { // dokud nebudou smazany vsechny polozky (dokud existuje 1. polozka)
		temp = L->First->rptr; // zachovani ukazatele
		free(L->First); // uvolneni ukazatele
		L->First = temp; // posunuti seznamu
	}
	L->First = L->Last = L->Act = NULL; // nastaveni dat na vychozi
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	struct tDLElem *item; // nova polozka
	item = malloc(sizeof(struct tDLElem)); // alokace pameti
	if (item == NULL) { // chyba alokace
		DLError();
		return;
	}
	item->data = val; // nastaveni uzitecnyh dat
	item->lptr = NULL; // inicializace leveho ukazatele
	if (L->Last == L->First) { // Pokud je v seznamu zadna nebo jedna polozka
		if(L->First == NULL) { // pokud je v seznamu zadna polozka
			item->rptr = NULL; // inicializace praveho ukazatele
			L->First = L->Last = item; // nastaveni noveho prvku jako prvni a posledni prvek
		}
		else { // pokud je v seznamu jedna polozka
			item->rptr = L->Last; // inicializace praveho ukazatele
			L->Last->lptr = item; // nastaveni ukazatele vedlejsi polozky
			L->First = item; // nastaveni noveho prvku seznamu
		}
	}
	else { // pokud je v seznamu 2 a vice polozek
		item->rptr = L->First; // inicializace praveho ukazatele
		L->First->lptr = item; // nastaveni ukazatele vedlejsi polozky
		L->First = item; // nastaveni noveho prvniho prvku seznamu
	}
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/ 	
	struct tDLElem *item; // nova polozka
	item = malloc(sizeof(struct tDLElem)); // alokace pameti
	if (item == NULL) { // chyna alokace pameti
		DLError();
		return;
	}
	item->data = val; // nastaveni uzitecnych dat
	item->rptr = NULL; // inicializace praveho ukazatele
	if (L->Last == L->First) { // v seznamu je jedna nebo zadna polozka
		if(L->Last == NULL) { // v seznamu je zadna polozka
			item->lptr = NULL; // inicializace leveho ukazatele
			L->First = L->Last = item; // nastaveni prvniho a posledniho ukazatele na novou polozku
		}
		else { // v seznamu je jedna polozka
			item->lptr = L->First; // nastaveni leveho ukazatele
			L->First->rptr = item; // nastaveni ukazatele vedlejsi polozky
			L->Last = item; // nastaveni posledniho ukazatele
		}
	}
	else { // v seznamu je 2 a vice polozek
		item->lptr = L->Last; // nastaveni leveho ukazatele
		L->Last->rptr = item; // nastaveni ukazatele vedlejsi polozky
		L->Last = item; // nastaveni posledni polozky
	}
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	L->Act = L->First; // nastaveni aktualni polozky
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	L->Act = L->Last; // nastaveni aktualni polozky na posledni
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
	if (L->First == NULL) { // kontrola pritomnosti alespon jednoho prvku
		DLError();
		return;
	}
	*val = L->First->data; // navraceni uzitecnych dat odkazem
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
	if (L->Last == NULL) { // kontrola pritomnosti alespon jednoho prvku
		DLError();
		return;
	}
	*val = L->Last->data; // navraceni uzitecnych dat odkazem
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
	if (L->First == NULL) return;  // kontrola pritomnosti alespon jednoho prvku
	if (L->First == L->Act) L->Act = NULL; // zruseni aktivity na prvnim prvku seznamu
	struct tDLElem *item; // pomocna promena
	item = L->First->rptr; // zachovani ukazatele
	free(L->First); // uvolneni prvniho prvku
	if (item != NULL) { // pokud neni novy seznam prazdny
		item->lptr = NULL; // nastaveni leveho ukazatele
		L->First = item; // nastaveni noveho prvniho prvku seznamu
	}
	else { // pokud je novy seznam prazdny
		L->Last = L->First = NULL; // "uzemneni" ukazatelu seznamu
	}
	
}	

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/ 
	if (L->Last == NULL) return; // kontrola pritomnosti alespon jednoho prvku
	if (L->Last == L->Act) L->Act = NULL; // zruseni aktivity posledniho prvku seznamu
	struct tDLElem *item; // pomocna promena
	item = L->Last->lptr; // zachovani ukazatele
	free(L->Last); // uvolneni pameti
	if (item != NULL) { // pokud novy seznam neni prazdny
		item->rptr = NULL; // nastaveni praveho ukazatele noveho posledniho prvku seznamu
		L->Last = item; // nastaveni noveho posledniho prvku
	}
	else { // novy seznam je prazdny
		L->Last = L->First = NULL; // "uzemneni" ukazatelu seznamu
	}
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
	if (L->Act == NULL || L->Act == L->Last) return; // test existence polozky na zruseni
	struct tDLElem *item; // pomocna promena
	item = L->Act->rptr->rptr; // zachovani ukazatele
	if (L->Act->rptr == L->Last) // pokud se rusi posledni polozka
		L->Last = L->Act; // nastaveni nove posledni polozky
	free(L->Act->rptr); // uvolneni pameti
	if (item != NULL) // pokud nebyla zrusena posledni polozka
		item->lptr = L->Act; // znovu navazani seznamu
	L->Act->rptr = item; // znovu navazani seznamu
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
	if (L->Act == NULL || L->Act == L->First) return; // kontrola existence polozky na zruseni
	struct tDLElem *item; // pomocna promena
	item = L->Act->lptr->lptr; // zachovani ukazatele
	if (L->Act->lptr == L->First) // pokud se rusi prvni polozka 
		L->First = L->Act; // nastaveni nove polozky jako prvni}
	free(L->Act->lptr); // uvolneni polozky
	if (item != NULL) // pokud nebyla zrusena prvni polozka
		item->rptr = L->Act; // znovu navazani seznamu
	L->Act->lptr = item; // znovu navazani seznamu
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	if (L->Act == NULL) return; // kontrola aktivity seznamu
	struct tDLElem *item; // nova polozka
	item = malloc(sizeof(struct tDLElem)); // alokace pameti
	if (item == NULL) { // kontrola alokace pameti
		DLError();
		return;
	}
	item->data = val; // inicializace uzitecnych dat
	item->lptr = L->Act; // inicializace leveho ukazatele
	item->rptr = L->Act->rptr; // inicializace praveho ukazatele
	L->Act->rptr = item; // vlozeni noveho prvku do seznamu
	if (L->Act == L->Last)
		L->Last = item;	
	else
		item->rptr->lptr = item; // nastaveni noveho ukazatele prvku nasledujiciho po nove polozce
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	if (L->Act == NULL) return; // kontrola aktivity seznamu
	struct tDLElem *item; // nova polozka
	item = malloc(sizeof(struct tDLElem)); // aokace pameti
	if (item == NULL) { // kontrola alokace pameti
		DLError();
		return;
	}
	item->data = val; // inicializace uzitecnych dat
	item->rptr = L->Act; // inicializace praveho ukazatele
	item->lptr = L->Act->lptr; // inicializace leveho ukazatele
	L->Act->lptr = item; // vlozeni polozky do seznamu
	if (L->Act == L->First)
		L->First = item;
	else
		item->lptr->rptr = item; // nastaveni ukazatele sousedni polozky
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
	if (L->Act == NULL) { // kontrola aktivity seznamu
		DLError();
		return;
	}
	*val = L->Act->data; // navraceni uzitecnych dat odkazem
}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
	if(L->Act == NULL) return; // kontrola aktivity seznamu
	L->Act->data = val;	// aktualizace uzitecnych dat
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
	if(L->Act == NULL) return; // kontrola aktivity seznamu
	L->Act = L->Act->rptr; // posunuti aktivity seznamu
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/
	if(L->Act == NULL) return;
	L->Act = L->Act->lptr;	
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
	return (L->Act == NULL)?0:1;	
}

/* Konec c206.c*/
