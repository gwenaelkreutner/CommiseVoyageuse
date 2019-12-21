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

bool presence ( struct elmlist * E, void * data ) {
    if (E == NULL){
        return false;
    } else if ( E->data == data ){
        return true;
    } else {
        return presence(E->suc, data);
    }
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


void insert_ordered ( struct list * L, void * data, struct town * departure ) {
    if( L->head == NULL) {
        cons(L, data);
    } else {
        struct elmlist * iterator = L->head;

        if( departure == NULL) { // C'est la liste des villes
            /* TODO  avec strcmp sur T->name et data->name */
            char * name = getTownName(data);
            bool cont = true;
            while(iterator && cont) {
                cont = strcmp(getTownName(iterator->data),name) < 0;
                if( cont )
                    iterator = iterator->suc;
            }
        } else { // C'est une liste d'ajacence, une liste de routes
            struct town * townU = getURoad(data);
            struct town * townV = getVRoad(data);
            struct town * arrival = (townU == departure) ? townV : townU;
            
            char * name = getTownName(arrival);
            bool cont = true;
            while(iterator && cont){
                struct town * iteratorU = getURoad(iterator->data);
                struct town * iteratorV = getVRoad(iterator->data);
                if(departure == iteratorU){
                    cont = strcmp(getTownName(iteratorV),name) < 0;
                    if( cont )
                        iterator = iterator->suc;
                } else {
                    cont = strcmp(getTownName(iteratorU),name) < 0;
                    if( cont )
                        iterator = iterator->suc;
                }
            }
        }

        if ( iterator == NULL ) { // Ajout en queue
            insert_after(L, data, L->tail);
        } else if ( iterator == L->head ) { // Ajout en Tête
            cons(L, data);
        } else { // On insère avant l'élément pointé
            insert_after(L, data, iterator->pred);
        }
    }
}
