#define t_queue_elem int

typedef struct queue queue;

queue* queue_new (int maxsize);

void queue_free (queue* q);

int queue_getsize (queue* q);

int queue_getmaxsize (queue* q);

int queue_isfull (queue* q);

int queue_isempty (queue* q);

void enqueue (queue* q, t_queue_elem elem);

t_queue_elem dequeue (queue* q);

t_queue_elem peek (queue* q);
