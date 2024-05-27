#define t_stack_elem int

typedef struct stack stack;

stack* stack_new(int maxsize);

void stack_free(stack* s);

int stack_getsize(stack* s);

int stack_getmaxsize(stack* s);

void push(stack* s, t_stack_elem elem);

t_stack_elem pop(stack* s);

t_stack_elem top(stack* s);

int stack_isempty(stack* s);

int stack_isfull(stack* s);

void stack_destroy(stack* s, void elem_free(t_stack_elem));