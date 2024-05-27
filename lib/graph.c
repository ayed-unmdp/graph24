#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "list.h"
#include "queue_dynamic.h"
#include "stack_dynamic.h"

typedef struct _edge{
    int to_vertex; //index of the vertex
    int weight;
    struct _edge* next;
} edge;

typedef struct _graph{
    t_graph_elem* vertex; //array of vertices
    edge** adj_list; //adjacency list
    int vertex_count;
    int vertex_max_count;
} graph;

// Create a new graph
graph* graph_new(){
    int ini_size = 16;
    graph* g = (graph*) malloc(sizeof(graph));    
    g->vertex = (t_graph_elem*)malloc(sizeof(t_graph_elem)*ini_size);
    g->adj_list = (edge**)malloc(sizeof(edge*)*ini_size);
    g->vertex_count = 0;
    g->vertex_max_count = 16;    
} 

// Destroy a graph
void graph_destroy(graph* g){
    for (int i = 0; i < g->vertex_count; i++){
        edge* e = g->adj_list[i];
        while (e != NULL){
            edge* next = e->next;
            free(e);
            e = next;
        }
    }
    free(g->adj_list);
    free(g->vertex);
    free(g);
} 


// Add a vertex to the graph
int graph_add_vertex(graph* g, t_graph_elem vertex){
    if (g->vertex_count == g->vertex_max_count){
        g->vertex_max_count *= 2;
        g->vertex = (t_graph_elem*)realloc(g->vertex, sizeof(t_graph_elem)*g->vertex_max_count);
        g->adj_list = (edge**)realloc(g->adj_list, sizeof(edge*)*g->vertex_max_count);
    }
    g->vertex[g->vertex_count] = vertex;
    g->adj_list[g->vertex_count] = NULL;
    g->vertex_count++;
    return g->vertex_count - 1;
} 

// Get vertex by index
t_graph_elem graph_vertex_get(graph* g, int index){
    return g->vertex[index];
} 

// Get the index of a vertex
int graph_vertex_index(graph* g, t_graph_elem vertex, int cmp (t_graph_elem, t_graph_elem)){
    int i = 0;
    while (i < g->vertex_count && cmp(g->vertex[i], vertex) != 0)
        i++;
    return (i == g->vertex_count) ? -1 : i;
} 

// Add an edge to the graph
int graph_add_edge(graph* g, int v1, int v2, int weight){
    if (v1 >= g->vertex_count || v2 >= g->vertex_count || v1 == -1 || v2 == -1)
        return 0;
    edge* e = (edge*)malloc(sizeof(edge));
    e->to_vertex = v2;
    e->weight = weight;
    e->next = g->adj_list[v1];
    g->adj_list[v1] = e;
    return 1;
} 

// Add an edge to the graph by name
int graph_add_edge_byname(graph* g, t_graph_elem v1, t_graph_elem v2, int weight, int cmp (t_graph_elem, t_graph_elem)){
    int i1 = graph_vertex_index(g, v1, cmp);
    int i2 = graph_vertex_index(g, v2, cmp);
    return graph_add_edge(g, i1, i2, weight);
}

// Remove an edge from the graph
int graph_remove_edge(graph* g, int v1, int v2, int weight){
    if (v1 >= g->vertex_count || v2 >= g->vertex_count || v1 == -1 || v2 == -1)
        return 0;
    int result = 0;
    edge** e = &g->adj_list[v1];
    while (*e != NULL && (*e)->to_vertex != v2 && (*e)->weight != weight)
        e = &(*e)->next;
    if (*e != NULL) {
        edge* tmp = *e;
        *e = (*e)->next;
        free(tmp);
        result = 1;
    }
    return result;
}

// Remove a vertex from the graph
t_graph_elem graph_remove_vertex(graph* g, int v){
    if (v >= g->vertex_count || v == -1)
        return 0;

    // devuelve el dato del vertice. 
    t_graph_elem result = g->vertex[v];

    // recorre todas las listas de adyacencia
    for (int i = 0; i < g->vertex_count; i++){
        edge** e = &g->adj_list[i];
        if (i == v){
            // si es la lista que corresponde al vertice buscado, la elimina
            while (*e != NULL){
                edge* tmp = *e;
                *e = (*e)->next;
                free(tmp);
            }            
        } else {
            // si no es la lista que corresponde al vertice buscado, 
            // elimina las aristas que apuntan al vertice buscado
            while (*e != NULL){
                if ((*e)->to_vertex == v){
                    edge* tmp = *e;
                    *e = (*e)->next;
                    free(tmp);
                } else {
                    e = &(*e)->next;
                }
            }
        }
    }

    // realiza los corrimientos en los vectores de vertices y listas de adyacencia
    for (int i = v; i < g->vertex_count - 1; i++){
        g->vertex[i] = g->vertex[i+1];
        g->adj_list[i] = g->adj_list[i+1];
    }

    g->vertex_count--;
    return result;

} 

// Get the weight of an edge
int graph_get_edge_weight(graph* g, int v1, int v2){
    if (v1 >= g->vertex_count || v2 >= g->vertex_count || v1 == -1 || v2 == -1) return 0;
    
    edge* e = g->adj_list[v1];
    while (e != NULL && e->to_vertex != v2)
        e = e->next;

    return (e != NULL) ? e->weight : 0;
} 

// Get the cost of an edge
int graph_get_edge_cost(graph* g, int v1, int v2){
    if (v1 >= g->vertex_count || v2 >= g->vertex_count || v1 == -1 || v2 == -1) return t_graph_weight_max;
    
    edge* e = g->adj_list[v1];
    while (e != NULL && e->to_vertex != v2)
        e = e->next;

    return (e != NULL) ? e->weight : t_graph_weight_max; 
} 

// Return 1 if exists an edge between v1 and v2, 0 otherwise
int graph_is_edge (graph* g, int v1, int v2){
    return (graph_get_edge_weight(g,v1,v2) > 0)? 1 : 0;
} 

// Get the vertex count
int graph_vertex_count(graph* g){
    return g->vertex_count;
} 

// Get the degree of a vertex (7.2.a)
// ojo devuelve el grado de salida
int graph_vertex_degree(graph* g, int v){
    int degree = 0;
    edge* e = g->adj_list[v];
    while (e != NULL){
        degree++;
        e = e->next;
    }
    return degree;
}

// Get ayencency list of a vertex (7.2.b) 
list* graph_vertex_adjacent_list(graph* g, int v){
    list* L = list_new(g->vertex_count);
    edge* e = g->adj_list[v];
    while (e != NULL){
        list_insert(L, list_length(L), e->to_vertex);
        e = e->next;
    }
    return L;
}

// Search Breadth First Search 
void graph_bfs(graph* g, int v, int visit(t_graph_elem, int, void*), void* ctx){
    int* visited = (int*)calloc(g->vertex_count, sizeof(int));
    queue* q = queue_new(g->vertex_count);
    enqueue(q, v);
    visited[v] = 1;
    int goon = 1;
    while (!queue_isempty(q) && goon){
        int u = dequeue(q);
        goon = visit(g->vertex[u], u, ctx);
        edge* e = g->adj_list[u];
        while (e != NULL && goon){
            if (visited[e->to_vertex] == 0){
                enqueue(q, e->to_vertex);   
                visited[e->to_vertex] = 1;
            }             
            e = e->next;
        }
    }
    free(visited);
    queue_free(q);
}

// Search Depth First Search 
void graph_dfs(graph* g, int v, int visit(t_graph_elem, int, void*), void* ctx){
    int* visited = (int*)calloc(g->vertex_count, sizeof(int));
    stack* s = stack_new(g->vertex_count);
    push(s, v);
    visited[v] = 1;
    int goon = 1;
    while (!stack_isempty(s) && goon){
        int u = pop(s);
        goon = visit(g->vertex[u], u, ctx);
        edge* e = g->adj_list[u];
        while (e != NULL && goon){
            if (visited[e->to_vertex] == 0){
                push(s, e->to_vertex);                
                visited[e->to_vertex] = 1;
            }
            e = e->next;
        }
    }
    free(visited);
    stack_free(s);
}