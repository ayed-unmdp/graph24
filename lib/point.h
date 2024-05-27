
#define SOURCE   'S'
#define TARGET   'T'
#define SPACE    ' '
#define PATH_WAY '.'

typedef struct _point point;

// crea punto con las coordenadas y el caracter especificado
point* point_new(char c, int x, int y);

// libera la memoria del punto
void point_free(void* p);

// establece el caracter del punto
void point_c_set(point* p, char c);

// obtiene el caracter del punto
char point_c(point* p);

// obtiene la coordenada x del punto
int point_x(point* p);

// obtiene la coordenada y del punto
int point_y(point* p);

// verifica si el punto es un espacio movible
int point_is_mov(point* p);

// imprime el punto
void point_print(void* p);

// imprime la descripción del punto
int point_cmp(point* p1, point* p2);

