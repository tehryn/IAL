
/* ******************************* c202.h *********************************** */
/*  P�edm�t: Algoritmy (IAL) - FIT VUT v Brn�                                 */
/*  �kol: c202 - Z�sobn�k znak� v poli                                        */
/*  Hlavi�kov� soubor pro c202.c                                              */
/*  Vytvo�il: V�clav Topinka, z��� 2005                                       */
/*  �pravy: Bohuslav K�ena, z��� 2011                                         */
/* ************************************************************************** */

/* TENTO SOUBOR, PROS�ME, NEUPRAVUJTE! */

#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>

#define MAX_STACK 20
extern int STACK_SIZE; 
/* 
 * Hodnota MAX_STACK ud�v� skute�nou velikost statick�ho pole pro ulo�en�
 * hodnot z�sobn�ku. P�i implementaci operac� nad ADT z�sobn�k v�ak
 * p�edpokl�dejte, �e velikost tohoto pole je pouze STACK_SIZE. Umo�n� to
 * jednodu�e m�nit velikost z�sobn�ku v pr�b�hu testov�n�. P�i implementaci
 * tedy hodnotu MAX_STACK v�bec nepou��vejte. 
 */

extern int solved;                      /* Indikuje, zda byla operace �e�ena. */
extern int err_flag;                   /* Indikuje, zda operace volala chybu. */

                                        /* Chybov� k�dy pro funkci stackError */
#define MAX_SERR    3                                   /* po�et mo�n�ch chyb */
#define SERR_INIT   1                                  /* chyba p�i stackInit */
#define SERR_PUSH   2                                  /* chyba p�i stackPush */
#define SERR_TOP    3                                   /* chyba p�i stackTop */

                             /* ADT z�sobn�k implementovan� ve statick�m poli */
typedef struct {
	char arr[MAX_STACK];                             /* pole pro ulo�en� hodnot */
	int top;                                /* index prvku na vrcholu z�sobn�ku */
} tStack;

                                  /* Hlavi�ky funkc� pro pr�ci se z�sobn�kem. */
void stackError ( int error_code );
void stackInit ( tStack* s );
int stackEmpty ( const tStack* s );
int stackFull ( const tStack* s );
void stackTop ( const tStack* s, char* c );
void stackPop ( tStack* s );
void stackPush ( tStack* s, char c );

#endif

/* Konec hlavi�kov�ho souboru c202.h */
