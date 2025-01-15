#ifndef NOTATION_H
#define NOTATION_H

// Стек для Вычисления Выражения Обратной Польской Нотации:
typedef struct Node_2 {
  double value;
  struct Node_2 *next;
} Node_2;

void free_stack_double(Node_2 **head_double);
void push_node_double(Node_2 **head_double, double value);
double pop_node_double(Node_2 **head_double);
int is_empty_double(Node_2 **head_double);
double peek_node_double(Node_2 **head_double);
int string_length(char *inficks);
int brackets(char *inficks);
int is_valid_string(char *inficks);
int precedency_operations(char symbol);
int is_symbol_number(char symbol);
int str_polish_notation(char *inficks, char *polskya);
double polish_notation_expression(char *polskya);

#endif