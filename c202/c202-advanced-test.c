
/****************************** c202-test.c ***********************************/
/*  P�edm�t: Algoritmy (IAL) - FIT VUT v Brn�                                 */
/*  �kol: c202 - Z�sobn�k znak� v poli                                        */
/*  Vytvo�il: V�clav Topinka, z��� 2005                                       */
/*  �pravy: Bohuslav K�ena, z��� 2011                                         */
/* ************************************************************************** */

/* Z�kladn� testy pro c202.c */

#include "c202.h"

#include <stdio.h>
#include <stdlib.h>

tStack* ptrstack;                                        /* pracovn� z�sobn�k */
int STACK_SIZE;                               /* efektivn� velikost z�sobn�ku */
int err_flag;                                              /* indik�tor chyby */
int solved;                                        /* indik�tor �e�en� funkce */

/****************************************************************************** 
 * Speci�ln� o�et�en� testovan�ch funkc�.                                     *
 ******************************************************************************/

                                                 /* Vytiskne obsah z�sobn�ku. */
void stackPrint( tStack* ptrstack) {
	int maxi = ptrstack->top;
	if ( ptrstack->top > STACK_SIZE-1 ) {
		printf ( "Warning: ptrstack->top (value: %i) is out of range STACK_SIZE (%i).\n", ptrstack->top, STACK_SIZE );
		maxi = STACK_SIZE-1;
	}
	printf ("--- BOTTOM [ ");
	for ( int i=0; i<=maxi; i++ )
		putchar ( ptrstack->arr[i] );
	printf (" ] TOP ---\n");
}

            /* Nastav� hodnoty pole, ve kter�m je definov�n zasobn�k, na '?'. */
void stackUndef ( tStack* ptrstack ) {
	for ( int i=0; i<MAX_STACK; ptrstack->arr[i++] = '?' );
}

         /* Zavol� funkci stackInit a v p��pad�, �e nebyla �e�ena, ohl�s� to. */
void use_stack_init ( tStack* ptrstack ) {
	solved = 1;
	stackInit( ptrstack );
	if ( ! solved )
		printf("[W] Funkce stackInit nebyla implementov�na.\n");
}

                             /* Zavol� funkci stackEmpty a vytiskne v�sledek. */
void use_stack_empty ( tStack* ptrstack ) {
	solved = 1;
	int i =stackEmpty( ptrstack );
	if ( ! solved )
		printf("[W] Funkce stackEmpty nebyla implementov�na.\n");
	else
		printf("stackEmpty returned '%s'\n", i ? "TRUE" : "FALSE" );
}

                              /* Zavol� funkci stackFull a vytiskne v�sledek. */
void use_stack_full ( tStack* ptrstack ) {
	solved = 1;
	int i = stackFull( ptrstack );
	if ( ! solved )
		printf("[W] Funkce stackFull nebyla implementov�na.\n");
	else
		printf("stackFull returned '%s'\n", i ? "TRUE" : "FALSE" );
}

                               /* Zavol� funkci stackTop a vytiskne v�sledek. */
void use_stack_top ( tStack* ptrstack ) {
	solved = 1;
	err_flag = 0;
	char c;
  stackTop( ptrstack, &c );
	if ( ! solved )
		printf("[W] Funkce stackTop nebyla implementov�na.\n");
	else if ( !err_flag )
		printf("stackTop returned '%c'\n", c );
}

                                                   /* Zavol� funkci stackPop. */
void use_stack_pop ( tStack* ptrstack ) {
	solved = 1;
	stackPop( ptrstack );
	if ( ! solved )
		printf("[W] Funkce stackPop nebyla implementov�na.\n");
}

                                                  /* Zavol� funkci stackPush. */
void use_stack_push ( tStack* ptrstack, char c ) {
	solved = 1;
	stackPush( ptrstack, c );
	if ( ! solved )
		printf("[W] Funkce stackPush nebyla implementov�na.\n");
}

/****************************************************************************** 
 * Vlastn� testov�n�                                                          *
 ******************************************************************************/

int main (int argc, char* argv[]) {
	printf ("C202 - Stack Implemented Using an Array - Basic Tests\n");
	printf ("-----------------------------------------------------\n");
	
	ptrstack = NULL;

	printf("\n[TEST00] Crashing Stack initialization\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_init(ptrstack);
	
	STACK_SIZE = 8;
	ptrstack = (tStack*) malloc(sizeof(tStack));
	stackUndef(ptrstack);

	printf("\n[TEST01] Stack initialization\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_init(ptrstack);
	stackPrint(ptrstack);

	printf("\n[TEST02] Checking a state of the stack\n" );
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(ptrstack);
	use_stack_full(ptrstack);

	printf("\n[TEST03] Pop over an empty stack\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_pop(ptrstack);
	stackPrint(ptrstack);

	printf("\n[TEST04] Checking a state of the stack again\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(ptrstack);
	use_stack_full(ptrstack);
	
	printf("\n[TEST05] Pushing items from '0' to '7'\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i=0; i<8; i++)
		use_stack_push(ptrstack, '0'+i);
	stackPrint(ptrstack);

	printf("\n[TEST06] Pushing item 8 \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_push(ptrstack, '8');
	stackPrint(ptrstack);

	printf("\n[TEST07] Checking a state of the stack again\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(ptrstack);
	use_stack_full(ptrstack);

	printf("\n[TEST08] Cleaning the stack\n" );
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i=0; i<8; i++) {
	  use_stack_top(ptrstack);
	  use_stack_pop(ptrstack);
	}
	stackPrint(ptrstack);
	
	printf("\n[TEST09] Checkin' again\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(ptrstack);
	use_stack_full(ptrstack);

	printf("\n[TEST10] Performing top on an empty stack\n" );
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_top(ptrstack);
	use_stack_full(ptrstack);
	stackPrint(ptrstack);

	
	printf("\n[TEST11] Final check of the stack\n" );
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	use_stack_empty(ptrstack);
	use_stack_full(ptrstack);
	
	printf("\n\n----- C202 - The End of Basic Tests -----\n");
 
	printf("\n\n----- This test should cover all advanced testings and error situations -----\n");
	//printf("\n\n----- Created for fituska.eu -----\n");

	free(ptrstack);
	return(0);
}

/* Konec c202-test.c */
