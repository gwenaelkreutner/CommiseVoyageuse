#include <stdlib.h>
#include <stdio.h> 

#include "graph.h"
#include "list.h"
#include "town.h"
#include "road.h"


void printInteger ( int * i ) {
  	printf( "La valeur est entière et vaut : %d\n",(*i));
}

int main() {
    /* 
     *  Main liste
     * 
    int a = 8, b = 4, * ptra = &a, * ptrb = &b, c = 12, d = 9, * ptrc = &c, *ptrd = &d;
	  struct list * L = new();

    cons(L, ptra);
    cons(L, ptrb);
    cons(L, ptrc);

    void (*ptrInteger) (int*);
    ptrInteger = &printInteger;

    viewlist(L, ptrInteger);

    insert_after(L, ptrd, NULL);

    printf("\n");
    viewlist(L, ptrInteger);

    */

    struct list * L = new();
	L = readFileFromTown("data/town.txt");
	void (*ptrPrintTown) (struct town *);
	ptrPrintTown = &printTownName;

    insert_ordered(L, createTown("Gwen"), NULL);

	viewlist(L, ptrPrintTown);

	void (*ptrFreeTown) (struct town *);
	ptrFreeTown = &freeTown;
	dellist(L, ptrFreeTown);
    
    return EXIT_SUCCESS;
}

