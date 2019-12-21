#ifndef _GRAPH_
#define _GRAPH_

/**
   @brief
   Undirected weighted graph modeled by a list of towns.
   Every town has a name and a list of roads connected
   to it that is modeled by an adjacency list.
*/

#include "list.h"

/**
 * @note
 * Le graphe est une liste de villes
 * Chaque ville possède une liste d'ajacence
 * qui sont les routes qui lui sont connexes.
 */
typedef struct list * graph;

/**
 * @brief
 * Construit le graphe décrivant la carte routière
 * (1) La liste des villes est contuite dans l'ordre lexicographique
 * (2) La liste des routes est construite,
 * (3) Les listes d'adjacence des villes sont construites,
 *       Pour chaque ville V, la liste d'adjacence est ordonnée selon les villes d'arrivées.
 * (4) La liste des routes est supprimée sans que les routes le soient !
 */
graph readmap();

/**
 * @brief
 * Visualiser la carte routière
 */
void viewmap ( graph G );

/**
 * @brief
 * Libérer le graphe
 */
void freeGraph ( graph ptrG );

struct list * prim( graph ptrG, struct town * ptrS );

void viewPrim ( struct list * L );

#endif // _GRAPH_