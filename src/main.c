#include <stdlib.h>
#include "graph.h"

int main() {
  graph G = readmap ();

  viewmap ( G );

  freeGraph ( G );

  return EXIT_SUCCESS;
}

