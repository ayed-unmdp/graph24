#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/graph_dijsktra.h"
#include "lib/matrix.h"
#include "lib/point.h"

// Load a labyrinth from a file into a matrix
matrix* labyrinth_load(char* filename) {
    FILE* lth_file;
    char linea[256];

    if ((lth_file = fopen(filename, "r")) == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    // primera pasada, calcula el tamaño de la matriz.
    int rows = 0;
    int cols = 0;
    while (fgets(linea, 256, lth_file) != NULL) {
        rows++;
        if (cols < strlen(linea) - 1) {
            cols = strlen(linea) - 1;
        }
    }

    fclose(lth_file);
    fopen(filename, "r");
    matrix* m = matrix_new(rows, cols);

    // segunda pasada, carga la matriz.
    int i = 0;
    while (fgets(linea, 256, lth_file) != NULL) {
        int j = 0;
        int n = strlen(linea);
        while (j < n && linea[j] != '\n') {
            point* p = point_new(linea[j], i, j);
            matrix_set(m, i, j, p);
            j++;
        }
        i++;
    }
    fclose(lth_file);

    return m;
}

graph* create_graph_from_labyrinth(matrix* m, int* origin, int* destiny) {
    graph* g = graph_new();
    for (int i = 0; i < matrix_rows(m); i++) {
        for (int j = 0; j < matrix_columns(m); j++) {
            point* p = matrix_get(m, i, j);
            if (p != NULL && point_is_mov(p)) {
                int index = graph_add_vertex(g, p);
                if (point_c(p) == SOURCE) {
                    *origin = index;
                } else if (point_c(p) == TARGET) {
                    *destiny = index;
                }
            }
        }
    }

    for (int i = 0; i < graph_vertex_count(g); i++) {
        point* p = graph_vertex_get(g, i);

        point* aux;
        aux = matrix_get(m, point_x(p) - 1, point_y(p));
        if (aux != NULL && point_is_mov(aux)) {
            graph_add_edge_byname(g, p, aux, 1, point_cmp);
        }
        aux = matrix_get(m, point_x(p) + 1, point_y(p));
        if (aux != NULL && point_is_mov(aux)) {
            graph_add_edge_byname(g, p, aux, 1, point_cmp);
        }
        aux = matrix_get(m, point_x(p), point_y(p) + 1);
        if (aux != NULL && point_is_mov(aux)) {
            graph_add_edge_byname(g, p, aux, 1, point_cmp);
        }
        aux = matrix_get(m, point_x(p), point_y(p) - 1);
        if (aux != NULL && point_is_mov(aux)) {
            graph_add_edge_byname(g, p, aux, 1, point_cmp);
        }

    }
    return g;
}

int main(int argc, char* argv[]) {

    // valida invocación del programa 
    if (argc < 2) {
        printf("Uso: %s <archivo>\n", argv[0]);
        exit(1);
    }
    
    char* filename = argv[1];
    //char* filename = "labyrinths\\long.lth";

    // crea laberinto en una matriz
    matrix* labyrinth = labyrinth_load(filename);

    // imprime el laberinto
    system("cls");
    matrix_print(labyrinth, point_print);

    // crea grafo a partir del laberinto
    int source = 0; // index of source vertex
    int target = 0; // index of target vertex
    graph* g = create_graph_from_labyrinth(labyrinth, &source, &target);
    
    printf ("Cantidad de vertices: %d\n", graph_vertex_count(g));
    point_print_descr(graph_vertex_get(g, source));
    point_print_descr(graph_vertex_get(g, target));
    
    dijsktra_result* r = dijsktra_result_new (graph_vertex_count(g));
    int cost = dijsktra(g, source, target, r);    

    // se verifica si hay camino
    if (cost == t_graph_weight_max) {
        printf ("No hay camino\n");
        
    } else {
        printf ("Costo: %d\n", cost);

        // obtiene el camino de dijsktra 
        // y cambia el char del point por un '.'
        int count = 0;
        int* prev = dijsktra_result_get_prev(r);
        target = prev[target];
        while (source != target) {
            point* p = graph_vertex_get(g, target);
           point_c_set (p,PATH_WAY);
            target = prev[target];
            count++;
        }
        printf ("pasos: %d\n", count);

        // se reimprime la matriz con la solución
        system("pause");
        system("cls");

        matrix_print(labyrinth, point_print);
        printf ("Cantidad de vertices: %d\n", graph_vertex_count(g));
        printf ("-pasos: %d\n", count);

    }

    dijsktra_result_free(r);
    graph_destroy(g);
    matrix_destroy(labyrinth, point_free);
    return 0;
}