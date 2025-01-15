#include "stack.h"

// Очистка Стека:
void free_stack(Node **head) {
  while (*head != NULL) {
    Node *buff = (*head)->next;
    free(*head);
    *head = buff;
  }
}

// Добавление Узла и его Значения в Стек:
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

// Удаление Узла и Взятие его Значения:
char pop_node(Node **head) {
  char res_value = (*head)->value;
  Node *buff = (*head)->next;
  free(*head);
  *head = buff;
  return res_value;
}

// Проверка:
// 1 -> Стек не Пуст || 0 -> Стек Пуст:
int is_empty(Node **head) {
  int res_empty = 1;
  if (*head == NULL) {
    res_empty = 0;
  }
  return res_empty;
}

// Взятие значения Узла без его Удаления из Стека:
char peek_node(Node **head) { return (*head)->value; }

// // Вывод Стека (Отладка):
// void print_stack(Node **head) {
//     Node *current = *head;
//     while (current != NULL) {
//         printf("Node value: %c\n", current->value);
//         current = current->next;
//     }
// }