#define t_list_elem int
#define bool int
#define true 1
#define false 0

typedef struct _list list;

list *list_new(int maxsize);

bool list_isempty(list *L);

bool list_isfull(list *L);

int list_length(list *L);

t_list_elem list_get(list *L, int index);

int list_search(list *L, t_list_elem elem);

void list_insert(list *L, int index, t_list_elem elem);

void list_delete(list *L, int index);

t_list_elem list_remove(list *L, int index);

void list_traverse(list *L, bool look(t_list_elem elem, int index, void *ctx), void *ctx);