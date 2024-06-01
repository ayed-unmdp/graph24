#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct _matrix{
    t_matrix_elem* a;
    int rows;
    int columns;
} matrix;

// Crea la matriz con el tamaño apropiado según las dimensiones establecidas.
matrix* matrix_new(int rows, int columns){
     matrix* result = (matrix*)malloc(sizeof(matrix));
     result->a = (t_matrix_elem*)malloc(sizeof(t_matrix_elem) * rows * columns);
     result->rows = rows;
     result->columns = columns;
     for (int i = 0; i < rows; i++) {
         for (int j = 0; j < columns; j++) {
             matrix_set(result, i, j, t_matrix_elem_default);
         }
     }
     return result;
}

// Elimina la matriz
void matrix_free(matrix* m){
    free(m);
}

// Elimina la matriz y libera la memoria de los elementos
void matrix_destroy(matrix* m, void elem_free(t_matrix_elem)){
    for (int i = 0; i < matrix_rows(m); i++) {
        for (int j = 0; j < matrix_columns(m); j++) {
            elem_free(matrix_get(m, i, j));
        }
    }
    matrix_free(m);
}

// Permite obtener la cantidad de filas
int matrix_rows(matrix* m){
     return m->rows;
}

// Permite obtener la cantidad de columnas
int matrix_columns(matrix* m){
     return m->columns;
}

// Permite obtener el valor de una posición de la matriz
t_matrix_elem matrix_get(matrix* m, int row, int col){
    if (row < 0 || row >= m->rows || col < 0 || col >= m->columns)
        return t_matrix_elem_default;
    return m->a[row * m->columns + col];
}

// Permite reemplazar o asignar un elemento a la matriz
void matrix_set(matrix* m, int row, int col, t_matrix_elem value){
     m->a[row * m->columns + col] = value;
}

// Permite imprimir una matriz por consola
void matrix_print(matrix* m, void prt(t_matrix_elem)){
     for(int i = 0; i < m->rows; i++){
         for(int j = 0; j < m->columns; j++){
             prt(matrix_get(m, i, j));
         }
         printf("\n");
     }
}
