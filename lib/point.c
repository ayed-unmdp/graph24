#include <stdio.h>
#include <stdlib.h>
#include "point.h"

typedef struct _point {
    char c;
    int x;
    int y;
} point;

// crea punto con las coordenadas y el caracter especificado
point* point_new(char c, int x, int y){
    point* result = (point*)malloc(sizeof(point));
    result->c = c;
    result->x = x;
    result->y = y;
    return result;
}

// libera la memoria del punto
void point_free(void* p){
    free(p);
}

// establece el caracter del punto
void point_c_set(point* p, char c){
    p->c = c;
}

// obtiene el caracter del punto
char point_c(point* p){
    return p->c;
}

// obtiene la coordenada x del punto
int point_x(point* p){
    return p->x;
}

// obtiene la coordenada y del punto
int point_y(point* p){
    return p->y;
}

// verifica si el punto es un espacio movible
int point_is_mov(point* p){
    return p->c == SPACE || p->c == SOURCE || p->c == TARGET;
}

// imprime el punto
void point_print(void* p) {
    if (p == NULL) {
        printf("%c", ' ');
    } else {
        printf("%c", ((point*)p)->c);
    }
}

// imprime la descripción del punto
void point_print_descr(void* p) {
    if (p == NULL) {
        printf("point(x,y) = ? \n");
    } else {
        printf("point(%d,%d) = %c \n", ((point*)p)->y, ((point*)p)->x, ((point*)p)->c);
    }
}


int point_cmp(point* p1, point* p2) {
    return !(((point*)p1)->x == ((point*)p2)->x && ((point*)p1)->y == ((point*)p2)->y);
}



