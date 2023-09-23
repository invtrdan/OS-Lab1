// list/list.c
// 
// Implementation for linked list.
//
// Danielle McIntosh

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

list_t *list_alloc() {
  list_t* mylist = (list_t *)malloc(sizeof(list_t));
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  while (l->head != NULL) {
    node_t *temp = l->head;
    l->head = l->head->next;
    free(temp);
  }
  free(l);
}

void list_print(list_t *l) {
  node_t *curr = l->head;
  while (curr != NULL) {
    printf("%d->", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}

char *listToString(list_t *l) {
  char *buf = (char *)malloc(sizeof(char) * 1024);
  char tbuf[20];
  strcpy(buf, "");

  node_t *curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    strcat(buf, tbuf);
    curr = curr->next;
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) {
  int length = 0;
  node_t *curr = l->head;
  while (curr != NULL) {
    length++;
    curr = curr->next;
  }
  return length;
}

void list_add_to_back(list_t *l, elem value) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;

  if (l->head == NULL) {
    l->head = new_node;
  } else {
    node_t *curr = l->head;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = new_node;
  }
}

void list_add_to_front(list_t *l, elem value) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = l->head;
  l->head = new_node;
}

void list_add_at_index(list_t *l, elem value, int index) {
  if (index < 0)
    return;

  if (index == 0) {
    list_add_to_front(l, value);
    return;
  }

  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;

  int current_index = 0;
  node_t *curr = l->head;
  while (curr != NULL && current_index < index - 1) {
    curr = curr->next;
    current_index++;
  }

  if (curr == NULL)
    return;

  new_node->next = curr->next;
  curr->next = new_node;
}

elem list_remove_from_back(list_t *l) {
  if (l->head == NULL)
    return -1;

  if (l->head->next == NULL) {
    elem value = l->head->value;
    free(l->head);
    l->head = NULL;
    return value;
  }

  node_t *curr = l->head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }

  elem value = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  return value;
}

elem list_remove_from_front(list_t *l) {
  if (l->head == NULL)
    return -1;

  elem value = l->head->value;
  node_t *temp = l->head;
  l->head = l->head->next;
  free(temp);
  return value;
}

elem list_remove_at_index(list_t *l, int index) {
  if (l->head == NULL || index < 0)
    return -1;

  if (index == 0)
    return list_remove_from_front(l);

  int current_index = 0;
  node_t *curr = l->head;
  while (curr != NULL && current_index < index - 1) {
    curr = curr->next;
    current_index++;
  }

  if (curr == NULL || curr->next == NULL)
    return -1;

  elem value = curr->next->value;
  node_t *temp = curr->next;
  curr->next = curr->next->next;
  free(temp);
  return value;
}

bool list_is_in(list_t *l, elem value) {
  node_t *curr = l->head;
  while (curr != NULL) {
    if (curr->value == value)
      return true;
    curr = curr->next;
  }
  return false;
}

elem list_get_elem_at(list_t *l, int index) {
  if (l->head == NULL || index < 0)
    return -1;

  int current_index = 0;
  node_t *curr = l->head;
  while (curr != NULL && current_index < index) {
    curr = curr->next;
    current_index++;
  }

  if (curr == NULL)
    return -1;

  return curr->value;
}

int list_get_index_of(list_t *l, elem value) {
  int index = 0;
  node_t *curr = l->head;
  while (curr != NULL) {
    if (curr->value == value)
      return index;
    curr = curr->next;
    index++;
  }
  return -1;
}


