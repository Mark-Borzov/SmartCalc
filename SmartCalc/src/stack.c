#include "stack.h"

// Очистка стека
void free_stack(Node **head) {
  while (*head != NULL) {
    Node *buff = (*head)->next;
    free(*head);
    *head = buff;
  }
}

// Добавление узла и его значения в стек
void push_node(Node **head, char value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    free_stack(head);
    exit(1);
  }
  new_node->next = *head;
  new_node->value = value;
  *head = new_node;
}

// Удаление узла и взятие его значения
char pop_node(Node **head) {
  char res_value = (*head)->value;
  Node *buff = (*head)->next;
  free(*head);
  *head = buff;
  return res_value;
}

// Проверка на пустой стек
// 1 -> Стек не пуст || 0 -> Стек пуст
int is_empty(Node **head) {
  int res_empty = 1;
  if (*head == NULL) {
    res_empty = 0;
  }
  return res_empty;
}

// Взятие значения узла без его удаления из стека
char peek_node(Node **head) { return (*head)->value; }

// // Печать стека (Для отладки)
// void print_stack(Node **head) {
//     Node *current = *head;
//     while (current != NULL) {
//         printf("Node value: %c\n", current->value);
//         current = current->next;
//     }
// }