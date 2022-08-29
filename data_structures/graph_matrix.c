#include "graph_matrix.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

graph *create_graph(int numnodes) {
  struct graph_matrix *g = malloc(sizeof(struct graph_matrix));
  if (g == NULL) {
    return NULL;
  }
  g->numnodes = numnodes;

  // allocating metrix space
  g->edges = calloc(sizeof(unsigned int *), g->numnodes);
  if (g->edges == NULL) {
    free(g);
    return NULL;
  }

  for (int i = 0; i < g->numnodes; i++) {
    g->edges[i] = calloc(sizeof(unsigned int), g->numnodes);
    if(g->edges[i] == NULL){
      destroy_graph(g);
      return NULL;
    }
  }
  

  return g;
}

void destroy_graph(graph* g){
  if (g->edges == NULL){
    return;
  }
  for(int i = 0; i < g->numnodes; i++){
    if(g->edges[i] != NULL){
      free(g->edges[i]);
    }
  }
  free(g->edges);
}

unsigned int has_edge(graph *g,unsigned int from, unsigned int to){
  return g->edges[from][to] == 1;
}
unsigned int add_edge(graph *g, unsigned int from, unsigned int to){
  if (has_edge(g,from,to) == 1){
    return 1;
  }
  g->edges[from][to] = 1;
  return 0;
}

void print_graph(graph *g){
  printf("Diagraph {\n");
  for(int from = 0; from < g->numnodes; from++){
     for(int to = 0; to < g->numnodes; to++){
       //check if it's edge between nodes
       if(g->edges[from][to] == 1){
         printf("%d => %d; \n",from,to);
       }
     }
  }
  printf("}\n");
}