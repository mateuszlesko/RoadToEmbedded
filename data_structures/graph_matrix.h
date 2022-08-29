#ifndef GRAPH_MATRIX_H_
#define GRAPH_MATRIX_H_
typedef struct graph_matrix{
  int numnodes;
  unsigned int **edges;
} graph;
graph *create_graph(int num_nodes);
void destroy_graph(graph* g);
void print_graph(graph *g);
unsigned int add_edge(graph* g, unsigned int from_node, unsigned int to_node);
unsigned int has_edge(graph* g,unsigned int from_node, unsigned int to_node);

#endif