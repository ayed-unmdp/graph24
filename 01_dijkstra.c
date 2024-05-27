#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/graph_dijsktra.h"

#define MADRID   "Madrid"
#define LONDRES  "Londres"
#define PARIS    "Paris"
#define ZURICH   "Zurich"
#define BERLIN   "Berlin"
#define ROMA     "Roma"

int _strcmp (t_graph_elem a, t_graph_elem b){
    return strcmp( (char*)a, (char*)b);
}

int main (int argc, char *argv[]) {
    graph* g = graph_new();
    graph_add_vertex(g, MADRID);
    graph_add_vertex(g, LONDRES);
    graph_add_vertex(g, PARIS);
    graph_add_vertex(g, ZURICH);
    graph_add_vertex(g, BERLIN);
    graph_add_vertex(g, ROMA);

    graph_add_edge_byname(g, MADRID,   LONDRES,  28, _strcmp);    
    graph_add_edge_byname(g, MADRID,   PARIS,    14, _strcmp);
    graph_add_edge_byname(g, MADRID,   ROMA,     65, _strcmp);
    graph_add_edge_byname(g, LONDRES,  PARIS,    10, _strcmp);
    graph_add_edge_byname(g, LONDRES,  BERLIN,   14, _strcmp);
    graph_add_edge_byname(g, PARIS,    ZURICH,   12, _strcmp);
    graph_add_edge_byname(g, BERLIN,   ROMA,     24, _strcmp);
    
    // como debe ser grafo se agregan las aristas en ambos sentidos
    graph_add_edge_byname(g, LONDRES,  MADRID,   28, _strcmp);    
    graph_add_edge_byname(g, PARIS,    MADRID,   14, _strcmp);
    graph_add_edge_byname(g, ROMA,     MADRID,   65, _strcmp);
    graph_add_edge_byname(g, PARIS,    LONDRES,  10, _strcmp);
    graph_add_edge_byname(g, BERLIN,   LONDRES,  14, _strcmp);
    graph_add_edge_byname(g, ZURICH,   PARIS,    12, _strcmp);
    graph_add_edge_byname(g, ROMA,     BERLIN,   24, _strcmp);

    int start = graph_vertex_index(g, MADRID, _strcmp);
    int end = graph_vertex_index(g, ROMA, _strcmp);
    
    dijsktra_result* r = dijsktra_result_new(graph_vertex_count(g));

    int min_cost = dijsktra(g, start, end, r);

    printf("El costo minimo de %s a %s es %d\n", MADRID, ROMA, min_cost);
    dijsktra_result_print_path(r, g, start, end);

    printf("\n\n");

    dijsktra_result_print(r,g);
    dijsktra_result_free(r);
    graph_destroy(g);
    return 0;
}
