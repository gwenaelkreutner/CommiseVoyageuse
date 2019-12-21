#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"
#include "road.h"
#include "town.h"

graph readmap() {
  FILE * fd;
  char fname[20];

  printf(" file name of the map :");
  scanf("%s", fname);
  if((fd = fopen(fname, "rt")) == NULL) {
    fprintf(stderr, "Error while opening %s\n", fname);
    exit(EXIT_FAILURE);
  }

  int nb;

  // Construction de la liste des villes
  //  qui sont les sommets du graphe
  graph G = new (); 

  fscanf(fd, " %d", &nb);
  for ( int i = 0; i < nb; i++ ) {
    char txtbuf[BUFSIZ];
    int buflen;

    fscanf(fd, " %s", txtbuf);
    buflen = strlen(txtbuf) + 1;
    char * name = (char *) calloc(buflen, sizeof(char));
    strcpy(name, txtbuf);

    struct town * T = createTown(name);

    insert_ordered(G, T, NULL);
  }

  // Construction de la liste des routes
  //  dont les villes sont des références
  //  aux villes enregistrées auparavant
  // Les routes sont les arêtes du graphe
  struct list * edges = new ();

  fscanf ( fd, " %d", &nb );
  for ( int i = 0; i < nb; i++ ) {
    char T1[20], T2[20];
    double km;
    fscanf ( fd, " ( %s , %s , %lf)", T1, T2 , &km);

    struct elmlist * iterator = G->head;
    while ( strcmp(getTownName(iterator->data), T1) != 0 ) {
      iterator = iterator->suc;
    }
    if ( iterator == NULL ) exit ( EXIT_FAILURE );

    struct town * u = iterator->data;

    iterator = G->head;
    while ( strcmp(getTownName(iterator->data), T2) != 0 ) {
      iterator = iterator->suc;
    }
    if ( iterator == NULL ) exit ( EXIT_FAILURE );

    struct town * v = iterator->data;

    struct road * R = createRoad(u, v, km);

    cons ( edges, R ); // un simple ajout en tête
  }

  // Construction des listes d'adjacences
  //  en parcourant la liste de routes
  for(struct elmlist * roads = edges->head; roads; roads = roads->suc) {
    struct town * u = getURoad(roads->data);
    struct town * v = getVRoad(roads->data);

    if( u == NULL || v == NULL) exit ( EXIT_FAILURE );

    insert_ordered(u->alist, roads->data, u); // insertion ordonnée de ville de départ u
    insert_ordered(v->alist, roads->data, v); // insertion ordonnée de ville de départ v
  }

  // Libérer la liste des arêtes mais pas les routes
  dellist ( edges, NULL );

  fclose ( fd );
  return G;
}
  
void viewmap ( graph G ) {
    int nb = G->len;
    printf("%d villes -->\n", nb);
    struct elmlist * iterator = G->head;

    while(iterator){
        viewTown(iterator->data);
        iterator = iterator->suc;
    }
}

void freeGraph ( graph ptrG ) {
    /** TODO 
     * Il faut malgré tout supprimer les villes ET les routes.
     * 
     * Faites attention que les routes ne sont référencées que par
     * les listes d'adjacence des villes.
     * 
     * Vous devez parcourir les villes (le graphe G)
     *  Pour chaque ville V, parcourez sa liste d'adjance
     *    (liste des routes auxquelles V est connexe)
     *    Pour chaque route R de la liste d'adjacence,
     *      vous devez déréférencer (NUll) la ville V
     *      Si les deux villes U et V de R sont déréférencées
     *      Alors vous pouvez supprimer la route R
     */
    struct elmlist * iterator = ptrG->head;
  
    while (iterator){
        struct town * V = ((struct town*) iterator->data);
        struct elmlist * iteratorRoad = getAList(V)->head;

        while (iteratorRoad){
            struct road * R = ((struct road*) iteratorRoad->data);
            if (getURoad(R) == (iterator->data)){
                setURoad(R, NULL);
            } else if(getVRoad(R) == (iterator->data)){
                setVRoad(R, NULL);
            }
            if (getURoad(R) == NULL && getVRoad(R) == NULL){
                freeRoad(R);
            }
            iteratorRoad = iteratorRoad->suc;
        }
        iterator = iterator->suc;
    }

    void (*ptrFreeTown) (struct town * T);
    ptrFreeTown = &freeTown;
    dellist(ptrG, ptrFreeTown);
}

struct list * prim( graph ptrG, struct town * ptrS ){
    /*
     * E corrrespond a l'ensemble des sommets appartenant a l'ACM
     * CE correspond aux sommets non encore selectionner ( Ensemble complementaire )
     * 
    */
    struct list * E = new(), * CE = new();
    cons(E, ptrS);

    struct elmlist * iteratorAdd = ptrG->tail;

    for (size_t i = 0; i < ptrG->len; i++) {
        if (iteratorAdd->data != ptrS) {
            cons(CE, iteratorAdd->data);
        }  
        iteratorAdd = iteratorAdd->pred;
    }
    
    while (CE->len > 0){
        struct town * S;
        struct elmlist * iteratorTown = E->head;
        double min;
        bool first = true;
        // Recherche de la ville S la plus proche
        for (size_t i = 0; i < E->len; i++) {
            struct town * townI = iteratorTown->data;
            struct elmlist * iteratorAdjacency = getAList(townI)->head;
            struct road * iteratorRoad = iteratorAdjacency->data;
            for (int j = 0; j < townI->alist->len; j++) {
                struct town * townU = getURoad(iteratorRoad);
                struct town * townV = getVRoad(iteratorRoad);
                struct town * townUV = (townI == townU) ? townV : townU;
                if (presence(CE->head, townUV)) {
                    double temp = getKmRoad(iteratorRoad);
                    if (first){ // initialiser min si c'est le premier parcours
                        min = temp;
                        S = townUV;
                        first = false;
                    }
                    if (temp <= min){
                        min = temp;
                        S = townUV;                    
                    }
                }
            
                iteratorAdjacency = iteratorAdjacency->suc;
                if (iteratorAdjacency != NULL)
                    iteratorRoad = iteratorAdjacency->data;
            }
            iteratorTown = iteratorTown->suc;
        }
        // Ajout de la ville S la plus proche dans E
        insert_after(E, S, E->tail);

        // Suppression de la ville S dans CE
        struct elmlist * iteratorDelete = CE->head;
        struct town * iteratorDeleteTown = iteratorDelete->data;
        while (iteratorDelete && iteratorDeleteTown != S) {
            iteratorDelete = iteratorDelete->suc;
            if (iteratorDelete != NULL)
                iteratorDeleteTown = iteratorDelete->data;
        }
        
        if (iteratorDeleteTown) {
            if ( iteratorDelete->suc == NULL && iteratorDelete->pred == NULL ) {
                CE->head = NULL;
                CE->tail = NULL;
            } else if ( iteratorDelete->pred == NULL ) {
                iteratorDelete->suc->pred = NULL;
                CE->head = iteratorDelete->suc;
            } else if (iteratorDelete->suc == NULL) {
                iteratorDelete->pred->suc = NULL;
                CE->tail = iteratorDelete->pred;
            } else {
                iteratorDelete->pred->suc = iteratorDelete->suc;
                iteratorDelete->suc->pred = iteratorDelete->pred;
            }
            CE->len--;
            free(iteratorDelete);
        }
    }
    return E;
}

void viewPrim( struct list * L ){
    struct elmlist * iterator = L->head;
    printf("\n\tParcours préfixé de l'ACM ( Sommet de depart : %s ):  \n\n", getTownName(iterator->data));
    while (iterator) {
        printf("--> ( %s ) ", getTownName(iterator->data));
        iterator = iterator->suc;
    }
    printf("\n");
}