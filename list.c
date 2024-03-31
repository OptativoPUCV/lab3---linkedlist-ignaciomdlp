#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList(){
  List *L = (List*)malloc(sizeof(List));
  if (L == NULL) exit(EXIT_FAILURE);
  L->head = NULL;
  L->tail = NULL;
  L->current = NULL;
  return L;
}

void * firstList(List * list){
  if (list->head != NULL) {
      list->current = list->head;
      return list->current->data;
  } else {
      return NULL;
  }
}

void * nextList(List * list){
  if(list->current != NULL && list->current->next != NULL){
    list->current = list->current->next;
    return list->current->data;
  }
  else return NULL;
}

void * lastList(List * list){
  if (list->tail != NULL){
    list->current = list->tail;
    return list->current->data;
  }
  else return NULL;
}

void * prevList(List * list){
  if (list->current != NULL && list->current->prev != NULL){
    list->current = list->current->prev;
    return list->current->data;
  }
  else return NULL;
}

void pushFront(List * list, void * data){
  Node *nodo = createNode(data);
  if (list->head == NULL){
    list->head = nodo;
    list->tail = nodo;
  }
  else{
    nodo->next = list->head;
    list->head->prev = nodo;
    list->head = nodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data){
  if(list == NULL) exit(EXIT_FAILURE);
  
  Node *nodo = createNode(data);
  
  nodo->prev = list->current;
  nodo->next = list->current->next;
  nodo->prev->next = nodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list){
  if(list == NULL) exit(EXIT_FAILURE);

  Node noNodo = list->current;
  void *data = noNodo->data;
  
  if(noNodo == list->head && noNodo == list->tail){
    list->head = NULL;
    list->tail = NULL;
  }
  else if(noNodo == list->head){
    list->head = list->head->prev;
    list->head->next = NULL;
  }
  else if(noNodo == list->tail){
    list->tail = list->tail->next;
    list->tail->prev = NULL;
  }
  else{
    noNodo->prev->next = noNodo->next;
    noNodo->next->prev = noNodo->prev;
  }
  list->current = noNodo->next;
  free(noNodo);
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}