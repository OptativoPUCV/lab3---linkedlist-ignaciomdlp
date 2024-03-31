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
  if(list == NULL) return;
  
  Node* nodo = createNode(data);
  
  nodo->prev = list->current;
  nodo->next = list->current->next;
  nodo->prev->next = nodo;

  if(list->current == list->tail){
    list->tail = nodo;
  } 
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
  
  Node *nodoPrev = list->current->prev;
  Node *nodoNext = list->current->next;

  if(list->current == list->head){
    list->head = nodoNext;
  }
  if(list->current == list->tail){
    list->tail = nodoPrev;
  }
  if(nodoPrev != NULL){
    nodoPrev->next = nodoNext;
  }
  if(nodoNext != NULL){
    nodoNext->prev = nodoPrev;
  }
  void *data = list->current->data;

  free(list->current);
  list->current = NULL;
  
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}