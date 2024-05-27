#include "graph.h"

typedef struct _dijsktra_result dijsktra_result;

dijsktra_result* dijsktra_result_new (int size);
int* dijsktra_result_get_dist (dijsktra_result* r);
int* dijsktra_result_get_prev (dijsktra_result* r);
void dijsktra_result_free (dijsktra_result* r);
void dijsktra_result_print (dijsktra_result* r, graph* g);
void dijsktra_result_print_path (dijsktra_result* r, graph* g, int start, int end);
int dijsktra(graph* g, int start, int end, dijsktra_result* r);
