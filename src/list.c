#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "town.h"
#include "road.h"

struct list * new () {
  /* TODO */
}

bool isempty ( struct list * L ) {
  /* TODO */
}

void dellist ( struct list * L, void (*ptrF) () ) {
  struct elmlist * iterator = L->head;

  if ( ptrF == NULL ) { // ne supprime pas les données
    /* TODO */
  } else { // suppression complète
    /* TODO */
  }
  /* TODO */
}

void viewlist ( struct list * L, void (*ptrF) () ) {
  /* TODO */
}

void cons ( struct list * L, void * data ) {
  struct elmlist * E = (struct elmlist *) calloc( 1, sizeof(struct elmlist));

  /* TODO */
}

void insert_after(struct list * L, void * data, struct elmlist * ptrelm) {
  struct elmlist * E = (struct elmlist *) calloc( 1, sizeof(struct elmlist));

  /* TODO */
}

void insert_ordered ( struct list * L, void * data, struct town * departure) {
 if( L->head == NULL) {
   /* TODO */
 } else {
    struct elmlist * iterator = L->head;

    if( departure == NULL) { // C'est la liste des villes
      /* TODO */
    } else { // C'est une liste d'ajacence, une liste de routes
      /* TODO */
    }
 
    if ( iterator == NULL) { // Ajout en queue
      /* TODO */
    } else if ( iterator == L->head ) { // Ajout en Tête
      /* TODO */
    } else {
      /* TODO */
    }
  }
}
