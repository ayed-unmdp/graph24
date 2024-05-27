#include "list.h"

#define t_graph_elem void* 
#define t_graph_elem_default NULL
#define t_graph_elem_cmp strcmp
#define t_graph_weight_max 9999999

typedef struct _graph graph;

graph* graph_new(); 
// Create a new graph

void graph_destroy(graph* g); 
// Destroy a graph

int graph_add_vertex(graph* g, t_graph_elem vertex); 
// Add a vertex to the graph

t_graph_elem graph_vertex_get(graph* g, int index); 
// Get vertex by index

int graph_vertex_index(graph* g, t_graph_elem vertex, int cmp (t_graph_elem, t_graph_elem)); 
// Get the index of a vertex

int graph_add_edge(graph* g, int v1, int v2, int weight); 
// Add an edge to the graph

int graph_add_edge_byname(graph* g, t_graph_elem v1, t_graph_elem v2, int weight, int cmp (t_graph_elem, t_graph_elem));
// Add an edge to the graph by name

int graph_remove_edge(graph* g, int v1, int v2, int weight);
// Remove an edge from the graph

t_graph_elem graph_remove_vertex(graph* g, int v); 
// Remove a vertex from the graph

int graph_get_edge_weight(graph* g, int v1, int v2); 
// Get the weight of an edge

int graph_get_edge_cost(graph* g, int v1, int v2); 
// Get the cost of an edge

int graph_is_edge (graph* g, int v1, int v2); 
// Return 1 if exists an edge between v1 and v2, 0 otherwise

int graph_vertex_count(graph* g); 
// Get the vertex count

int graph_vertex_degree(graph* g, int v);
// Get the degree of a vertex (7.2.a)

list* graph_vertex_adjacent_list(graph* g, int v);
// Get ayencency list of a vertex (7.2.b) 

void graph_bfs(graph* g, int v, int visit(t_graph_elem, int, void*), void* ctx);
// Search Breadth First Search 

void graph_dfs(graph* g, int v, int visit(t_graph_elem, int, void*), void* ctx);
// Search Depth First Search 