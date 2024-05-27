#include <stdio.h>
#include <stdlib.h>

#define t_matrix_elem void*
#define t_matrix_elem_default NULL

typedef struct _matrix matrix;

// Crea la matriz con el tamaño apropiado según las dimensiones establecidas.
matrix* matrix_new(int rows, int columns);

// Elimina la matriz
void matrix_free(matrix* m);

// Elimina la matriz y libera la memoria de los elementos
void matrix_destroy(matrix* m, void elem_free(t_matrix_elem));

// Permite obtener la cantidad de filas
int matrix_rows(matrix* m);

// Permite obtener la cantidad de columnas
int matrix_columns(matrix* m);

// Permite obtener el valor de una posición de la matriz
t_matrix_elem matrix_get(matrix* m, int row, int col);

// Permite reemplazar o asignar un elemento a la matriz
void matrix_set(matrix* m, int row, int col, t_matrix_elem value);

// Permite imprimir una matriz por consola
void matrix_print(matrix* m, void prt(t_matrix_elem));
