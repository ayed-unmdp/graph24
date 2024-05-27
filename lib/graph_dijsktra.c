#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "list.h"
#include "graph_dijsktra.h"

typedef struct _dijsktra_result {
    int* dist;
    int* prev;
    int count;
} dijsktra_result;

dijsktra_result* dijsktra_result_new (int size){
    dijsktra_result* r = (dijsktra_result*)malloc(sizeof(dijsktra_result));
    r->dist = (int*)malloc(sizeof(int)*size);
    r->prev = (int*)malloc(sizeof(int)*size);
    r->count = size;
    for (int i = 0; i < size; i++){
        r->dist[i] = t_graph_weight_max;
        r->prev[i] = i;
    }
    return r;
}

int* dijsktra_result_get_dist (dijsktra_result* r){
    return r->dist;
}

int* dijsktra_result_get_prev (dijsktra_result* r){
    return r->prev;
}

void dijsktra_result_free (dijsktra_result* r){
    free(r->dist);
    free(r->prev);
    free(r);
}

void dijsktra_result_print (dijsktra_result* r, graph* g){
    printf("Distancias y previos\n");
    printf("%-10s | %5s | %-10s \n", "Origen", "Dist.", "Previo");
    printf("---------------------------\n");

    for (int i = 0; i < r->count; i++){
        printf("%-10s | %5d | %-10s \n", graph_vertex_get(g, i), r->dist[i], graph_vertex_get(g, r->prev[i]));
    }
}


void dijsktra_result_print_path (dijsktra_result* r, graph* g, int start, int end){
    if (start != end) {
        dijsktra_result_print_path(r, g, start, r->prev[end]);
        printf(" -> %s", graph_vertex_get(g, end));
    } else {
        printf("%s", graph_vertex_get(g, end));
    }
}

int dijsktra(graph* g, int start, int end, dijsktra_result* r){
    int* visited = (int*)calloc(graph_vertex_count(g), sizeof(int));

    int* d = dijsktra_result_get_dist(r); //array of distances
    int* p = dijsktra_result_get_prev(r); //array of indexes of previous vertex

    int current = start;
    d[current] = 0;
    while (current != -1 && current != end){
        visited[current] = 1;

        list* l = graph_vertex_adjacent_list(g, current);
        while (!list_isempty(l)){
            int to_vertex = list_remove(l, 0);
            int weight = graph_get_edge_weight(g, current, to_vertex);
            if (visited[to_vertex] == 0){
                if (d[to_vertex] > d[current] + weight){
                    d[to_vertex] = d[current] + weight;
                    p[to_vertex] = current;
                }
            }            
        }    

        int min = -1;
        for (int i = 0; i < graph_vertex_count(g); i++){
            if (visited[i] == 0 && (min == -1 || d[i] < d[min])){
                min = i;                
            }
        }
        
        current = min;
    }
    free(visited);
    return d[end];
}

