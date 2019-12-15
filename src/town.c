#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "town.h"
#include "road.h"

struct town * createTown(char * name) {
  struct town * T = (struct town *)calloc(1, sizeof(struct town));

  T->name=(char *)calloc(strlen(name)+1, sizeof(char));
  strcpy(T->name, name);
  T->alist = new();

  return T;
}

void freeTown ( struct town * T ) {
  if (T) {
    free(T->name);
    dellist(getAList(T), NULL);
    free(T);
  }
  
}

char * getTownName(struct town * T) {
  return T->name;
}

struct list * getAList(struct town * T) {
  return T->alist;
}

void viewTown (struct town * T) {
    struct elmlist * iterator = T->alist->head;

    printf("%s est connecté a : \n", getTownName(T));
    while(iterator){
        struct town * roadU = getURoad(iterator->data);

        struct town * roadUV = (roadU == T) ? getVRoad(iterator->data) : roadU;
        printf("%s\n", roadUV->name);

        iterator = iterator->suc;
    }
}

void printTownName ( struct town * T ) {
    printf("%s | ", getTownName(T));
}

struct list * readFileFromTown ( char * filename ) {
    struct list * L = new();
    FILE * file = fopen(filename, "r");
    int nbVille;

    if (file == NULL)
    {
        printf("Le fichier %s n'a pas pu être ouvert\n", filename);
        exit(1);
    }

    fscanf(file, " %d", &nbVille);

    for ( int i = 0; i < nbVille; i++ ) {
    char txtVille[BUFSIZ];

    fscanf(file, " %s", txtVille);
    int buffLen = strlen(txtVille) + 1;
    char * name = ( char * ) calloc(buffLen, sizeof(char));
    strcpy(name, txtVille);
    struct town * T = createTown(name);
    insert_ordered(L, T, NULL);
    }
    fclose(file);

    return L;
}