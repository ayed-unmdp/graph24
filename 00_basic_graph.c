#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/graph.h"

typedef struct _graph_prt_ctx{
    int first;    
} graph_prt_ctx;


int graph_prt_visit (t_graph_elem elem, int index, void* ctx){
    if (((graph_prt_ctx*)ctx)->first == 1){
        printf("\n%s", elem);
        ((graph_prt_ctx*)ctx)->first = 0;
    } else {
        printf(" -> %s", elem);
    }    
    return 1;
}

int _strcmp (t_graph_elem a, t_graph_elem b){
    return strcmp( (char*)a, (char*)b);
}

int graph_matrix_print (graph* g){
    int z = graph_vertex_count(g);
    printf("\n   ");
    for (int i = 0; i < z; i++){
        printf("  %s ", graph_vertex_get(g, i));
    }
    for (int i = 0; i < z; i++){
        printf("\n  %s ", graph_vertex_get(g, i));
        for (int j = 0; j < z; j++){
            printf(" %d  ", graph_is_edge(g, i, j));
        }        
    }
    return 1;
}


int main (int argc, char *argv[]) {
        
    graph* g = graph_new();
    graph_add_vertex(g, "A");
    graph_add_vertex(g, "B");
    graph_add_vertex(g, "C");
    graph_add_vertex(g, "D");
    graph_add_vertex(g, "E");
    graph_add_vertex(g, "F");
    graph_add_vertex(g, "G");
    graph_add_vertex(g, "H");
    graph_add_vertex(g, "I");
    graph_add_vertex(g, "J");

    graph_add_edge_byname(g, "A", "B", 1, _strcmp);
    graph_add_edge_byname(g, "A", "C", 1, _strcmp);
    graph_add_edge_byname(g, "A", "D", 1, _strcmp);
    graph_add_edge_byname(g, "B", "E", 1, _strcmp);
    graph_add_edge_byname(g, "B", "F", 1, _strcmp);
    graph_add_edge_byname(g, "C", "G", 1, _strcmp);
    graph_add_edge_byname(g, "C", "H", 1, _strcmp);
    graph_add_edge_byname(g, "D", "I", 1, _strcmp);
    graph_add_edge_byname(g, "D", "J", 1, _strcmp);
    graph_add_edge_byname(g, "F", "A", 1, _strcmp);
    graph_add_edge_byname(g, "F", "B", 1, _strcmp);
    graph_add_edge_byname(g, "F", "G", 1, _strcmp);
    graph_add_edge_byname(g, "G", "F", 1, _strcmp);
    graph_add_edge_byname(g, "G", "H", 1, _strcmp);
    graph_add_edge_byname(g, "G", "D", 1, _strcmp);
    graph_add_edge_byname(g, "H", "A", 1, _strcmp);
    graph_add_edge_byname(g, "H", "I", 1, _strcmp);
    graph_add_edge_byname(g, "H", "J", 1, _strcmp);
    graph_add_edge_byname(g, "J", "B", 1, _strcmp);
    graph_add_edge_byname(g, "J", "E", 1, _strcmp);
    graph_add_edge_byname(g, "J", "G", 1, _strcmp);
    

    graph_prt_ctx* ctx = (graph_prt_ctx*) malloc(sizeof(graph_prt_ctx));

    graph_matrix_print(g);

    printf("\n\nBFS:");
    ctx->first = 1;
    graph_bfs(g, 0, graph_prt_visit, ctx);

    printf("\n\nDFS:");
    ctx->first = 1;
    graph_dfs(g, 0, graph_prt_visit, ctx);


    printf("\n\nDFS (desde J):");
    ctx->first = 1;
    graph_dfs(g, graph_vertex_index (g, "J", _strcmp) , graph_prt_visit, ctx);    

    printf("\n\n");
    return 0;
}