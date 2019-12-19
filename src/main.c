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

    graph G = readmap ();
	viewmap ( G );
	freeGraph ( G );

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

    /*
     * Main town
     * 
     * 
    struct list * L = new();
	L = readFileFromTown("data/town.txt");
	void (*ptrPrintTown) (struct town *);
	ptrPrintTown = &printTownName;

    insert_ordered(L, createTown("Gwen"), NULL);

	viewlist(L, ptrPrintTown);

	void (*ptrFreeTown) (struct town *);
	ptrFreeTown = &freeTown;
	dellist(L, ptrFreeTown);

    */

   /*
     * Main road
     * 
     * 
    struct list * L = new();
	L = readFileFromRoad("data/road.txt");
	struct town * villeA = createTown("Metz");
	struct town * villeB = createTown("Paris");
	
	struct road * Road1 = createRoad(villeA,villeB);
	
	void (*ptrPrintRoad) (struct road * T);
	ptrPrintRoad = &viewRoad;
	viewlist(L,ptrPrintRoad);
    */

    /*
     * Main insert_ordered
     * 
     * 

	struct list * L = new();

	struct town * villeA = createTown("A");
	struct town * villeB = createTown("B");
	struct town * villeC = createTown("C");
	struct town * villeD = createTown("D");
	struct town * villeP = createTown("E");

	struct road * RAB = createRoad(villeA, villeB);
	struct road * RAC = createRoad(villeA, villeC);
	struct road * RBC = createRoad(villeA, villeD);
	struct road * RTP = createRoad(villeA, villeP);


	void (*ptrPrintR) (struct road * R);
	ptrPrintR = &viewRoad;

	insert_ordered(L, RTP, villeA);
	insert_ordered(L, RAC, villeA);
	insert_ordered(L, RAC, villeA);
	insert_ordered(L, RAB, villeA);

	viewlist(L, ptrPrintR);
	*/

    return EXIT_SUCCESS;
}

