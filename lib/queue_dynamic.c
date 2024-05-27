#include <stdio.h>
#include <stdlib.h>
#include "queue_dynamic.h"

typedef struct queue_node {
  t_queue_elem value;
  struct queue_node *next;
} queue_node;

typedef struct queue {
  queue_node *head;
  queue_node *tail;
  int maxsize;
  int count;
} queue;

queue* queue_new (int maxsize) {
  queue* q = malloc(sizeof(queue));

  q->head = NULL;
  q->tail = NULL;
  q->maxsize = maxsize;
  q->count = 0;

  return q;
}

void queue_free (queue* q) {
  queue_node* aux;

  while (q->head != NULL) {
    aux = q->head;
    q->head = q->head->next;
    free(aux);
  }

  free(q);
}

int queue_getsize (queue* q) {
  return q->count;
}

int queue_getmaxsize (queue* q) {
  return q->maxsize;
}

int queue_isfull (queue* q) {
  return q->count == q->maxsize;
}

int queue_isempty (queue* q) {
  return q->count == 0;
}

void enqueue (queue* q, t_queue_elem elem) {    
  if (queue_isfull(q)){
    printf("Queue overflow\n");
    exit(1);
  }

  queue_node* new_node = (queue_node*) malloc(sizeof(queue_node));

  new_node->value = elem;
  new_node->next = NULL;

  if (q->head == NULL) {
    q->head = new_node;
  } else {
    q->tail->next = new_node;
  }

  q->tail = new_node;
  q->count++;
}

t_queue_elem dequeue (queue* q) {
  if (queue_isempty(q)){
    printf("Queue underflow\n");
    exit(1);
  }

  queue_node* aux = q->head;
  t_queue_elem elem = q->head->value;

  q->head = q->head->next;
  q->count--;

  if (q->count == 0) {
    q->tail = NULL;
  }

  free(aux);

  return elem;
}

t_queue_elem peek (queue* q) {
  if (queue_isempty(q)){
    printf("Queue underflow\n");
    exit(1);
  }

  return q->head->value;
}