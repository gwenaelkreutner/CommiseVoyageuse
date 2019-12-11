#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "town.h"
#include "road.h"

struct list * new () {
    struct list * L = (struct list *) calloc( 1, sizeof(struct list));

    L->head = NULL;
    L->tail = NULL;
    L->len = 0;

    return L;
}

bool isempty ( struct list * L ) {
    return L->len == 0;
}

void dellist ( struct list * L, void (*ptrF) () ) {
    struct elmlist * iterator = L->head;
    struct elmlist * next;
    int len = L->len;

    if ( ptrF == NULL ) { // ne supprime pas les données
        while (len--) {
            next = iterator->suc;
            free(iterator);
            iterator = next;
        }
    } else { // suppression complète
        while (len--) {
            next = iterator->suc;
            void* d1 = iterator->data;
            (*ptrF) ( d1 );
            free(iterator);
            iterator = next;
        }
    }
    free(L);
}

void viewlist ( struct list * L, void (*ptrF) () ) {
    struct elmlist * next = L->head;

    while ( next ) {
        void* d1 = next->data;
        (*ptrF) ( d1 );
        next = next->suc;
    }

}

void cons ( struct list * L, void * data ) {
    struct elmlist * E = (struct elmlist *) calloc( 1, sizeof(struct elmlist));

    E->data = data;
    E->pred = NULL;
    E->suc = L->head;
    if (isempty(L)){
        L->tail = E;
    } else{
        L->head->pred = E;
    }
    
    L->head = E;
    L->len++;
}

void insert_after(struct list * L, void * data, struct elmlist * ptrelm) {
    struct elmlist * E = (struct elmlist *) calloc( 1, sizeof(struct elmlist));
    
    if (ptrelm == NULL){
        cons(L, data);
    } else {
        E->pred = ptrelm;
        E->suc = ptrelm->suc;
        E->data = data;
        ptrelm->suc = E;
        if (E->suc != NULL){
            E->suc->pred = E;
        }
        if (L->tail == ptrelm){
            L->tail = E;
        }
    
        L->len++;
    }
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
