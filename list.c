#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() {

  List *lista = (List *)malloc(sizeof(List));

  lista->head = NULL;
  lista->tail = NULL;
  lista->current = NULL;

  return lista;
}

void *firstList(List *list) {
  if (list == NULL || list->head == NULL) return NULL;

  list->current = list->head;
  return list->head->data;
}

void *nextList(List *list) {
  if (list == NULL || list->current == NULL || list->current->next == NULL) return NULL;

  list->current = list->current->next;

  return list->current->data;
}

void *lastList(List *list) {
  if (list == NULL || list->tail == NULL) return NULL;

  list->current = list->tail;

  return list->tail->data;
}

void *prevList(List *list) {
  if (list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;

  list->current = list->current->prev;

  return list->current->data;
}

void pushFront(List *list, void *data) {

  Node *nodoNuevo = createNode(data);

  if (list->head == NULL) {
    list->head = list->tail = nodoNuevo;
  } else {
    nodoNuevo->next = list->head;
    list->head->prev = nodoNuevo;
    list->head = nodoNuevo;
  }
}

void pushBack(List *list, void *data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void pushCurrent(List *list, void *data) {
  // insertar un elemento dsps de list->current
  Node *nodoNuevo = createNode(data);
  nodoNuevo->next = list->current->next;
  nodoNuevo->prev = list->current;

  if (list->current->next == NULL)
    list->tail = nodoNuevo;
  else
    list->current->next->prev = nodoNuevo;

  list->current->next = nodoNuevo;
}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) {

  Node *curr = list->current;
  void *data = curr->data;

  if (curr->prev != NULL) curr->prev->next = curr->next;
  else list->head = curr->next;

  if (curr->next != NULL) curr->next->prev = curr->prev;
  else list->tail = curr->prev;

  list->current = curr->next;
  free(curr);

  return data;
}

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}
