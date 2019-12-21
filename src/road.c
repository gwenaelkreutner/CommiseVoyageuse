#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "road.h"
#include "town.h"

struct road * createRoad (struct town * U, struct town * V, double km) {
    struct road * R = (struct road *)calloc(1,sizeof(struct road));
    R->U = U;
    R->V = V;
    R->km = km;

    return R;
}

void freeRoad ( struct road * R ) {
    free(R);
}

struct town * getURoad(struct road * R) {
    return R->U;
}

void setURoad ( struct road * R, struct town * T ) {
    R->U = T;
}

struct town * getVRoad(struct road * R) {
    return R->V;
}

void setVRoad ( struct road * R, struct town * T ) {
    R->V = T;
}

double getKmRoad( struct road * R ){
    return R->km;
}

void viewRoad ( struct road * R ) {
    printf("%s <----> %s \n",getTownName(R->U),getTownName(R->V));
}

struct list * readFileFromRoad ( char * filename ){
    struct list * L = new();
    FILE * file = fopen(filename, "r");
    int nbRoute;

    if (file == NULL)
    {
        printf("Le fichier %s n'a pas pu être ouvert\n", filename);
        exit(1);
    }

    fscanf(file, " %d", &nbRoute);

    for ( int i = 0; i < nbRoute; i++ ) {
        char villeU[BUFSIZ], villeV[BUFSIZ];
        double km;
        fscanf(file," ( %s , %s , %lf)",villeU, villeV, &km);

        int buffLen = strlen(villeU) + 1;
        char * nameU = ( char * ) calloc(buffLen, sizeof(char));
        strcpy(nameU, villeU);

        buffLen = strlen(villeV) + 1;
        char * nameV = ( char * ) calloc(buffLen, sizeof(char));
        strcpy(nameV, villeV);
        
        struct road * R = createRoad(createTown(nameU),createTown(nameV), km);
        cons(L,R);
    }
    fclose(file);

    return L;
}