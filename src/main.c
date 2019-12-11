#include <stdlib.h>
#include <stdio.h> 

#include "graph.h"

void printInteger ( int * i ) {
  	printf( "La valeur est entière et vaut : %d\n",(*i));
}

int main() {
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

    return EXIT_SUCCESS;

}

