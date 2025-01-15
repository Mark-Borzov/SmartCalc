#ifndef STACK_H
#define STACK_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Стек для Перевода Инфиксной Нотации в Обратную Польскую:
typedef struct Node {
  char value;
  struct Node *next;
} Node;

void free_stack(Node **head);
void push_node(Node **head, char value);
char pop_node(Node **head);
int is_empty(Node **head);
char peek_node(Node **head);
void print_stack(Node **head);

#endif