#include "notation.h"

#include "stack.h"

// Очистка Стека:
void free_stack_double(Node_2 **head_double) {
  while (*head_double != NULL) {
    Node_2 *buff = (*head_double)->next;
    free(*head_double);
    *head_double = buff;
  }
}

// Добавление Узла и его Значения в Стек:
void push_node_double(Node_2 **head_double, double value) {
  Node_2 *new_node = (Node_2 *)malloc(sizeof(Node_2));
  if (new_node == NULL) {
    free_stack_double(head_double);
    exit(1);
  }
  new_node->next = *head_double;
  new_node->value = value;
  *head_double = new_node;
}

// Удаление Узла и Возврат его Значения:
double pop_node_double(Node_2 **head_double) {
  double res_value = (*head_double)->value;
  Node_2 *buff = (*head_double)->next;
  free(*head_double);
  *head_double = buff;
  return res_value;
}

// Проверка: 1 -> Стек не пуст || 0 -> Стек пуст:
int is_empty_double(Node_2 **head_double) {
  int res_empty = 1;
  if (*head_double == NULL) {
    res_empty = 0;
  }
  return res_empty;
}

// Возврат Значения Узла без его Удаления из Стека:
double peek_node_double(Node_2 **head_double) { return (*head_double)->value; }

// Проверка Длины Строки Инфиксного Выражения:
// // 1-> OK || 0 -> FALSE:
int string_length(char *inficks) { return strlen(inficks) > 255 ? 0 : 1; }

// Проверка на Валидность Скобок:
// 1 -> Скобки Валидны || 0 -> Скобки не Валидны:
int brackets(char *inficks) {
  int res_brackets = 1;
  Node *head = NULL;
  for (int i = 0; inficks[i] != '\0'; i++) {
    if (inficks[i] == '(') {
      push_node(&head, inficks[i]);
    } else if (inficks[i] == ')') {
      if (is_empty(&head) == 0) {
        res_brackets = 0;
        break;
      } else {
        pop_node(&head);
      }
    }
  }
  if (is_empty(&head) == 1) {
    res_brackets = 0;
  }
  free_stack(&head);
  return res_brackets;
}

// Проверка Символа:
// 1-> Символ Цифра || 0 -> Символ не Цифра:
int is_symbol_number(char symbol) {
  return symbol >= 48 && symbol <= 57 ? 1 : 0;
}

// Проверка Строки:
// 1 -> Строка Валидна || 0 -> Строка не Валидна:
int is_valid_string(char *inficks) {
  int res_is_valid_string = 1;
  if (string_length(inficks) == 0) {
    res_is_valid_string = 0;
  } else {
    int dot_count = 0;
    for (int i = 0; inficks[i] != '\0'; i++) {
      if ((inficks[i] == '+' || inficks[i] == '-' || inficks[i] == '*' ||
           inficks[i] == '/' || inficks[i] == '^') &&
          (inficks[i + 1] == '+' || inficks[i + 1] == '-' ||
           inficks[i + 1] == '*' || inficks[i + 1] == '/' ||
           inficks[i + 1] == '^')) {
        res_is_valid_string = 0;
      }
      if (inficks[0] == '+' || inficks[0] == '/' || inficks[0] == '*' ||
          inficks[0] == 'm' || inficks[0] == '.' || inficks[0] == '^') {
        res_is_valid_string = 0;
      }
      if (inficks[i] == '.') {
        dot_count++;
        if (dot_count > 1) {
          res_is_valid_string = 0;
        }
      }
      if (inficks[i] == '+' || inficks[i] == '-' || inficks[i] == '*' ||
          inficks[i] == '/') {
        dot_count = 0;
      }
      if (inficks[i] == '.' && inficks[i + 1] == '.') {
        res_is_valid_string = 0;
      }
      if (inficks[strlen(inficks) - 1] == '+' ||
          inficks[strlen(inficks) - 1] == '-' ||
          inficks[strlen(inficks) - 1] == '*' ||
          inficks[strlen(inficks) - 1] == '/' ||
          inficks[strlen(inficks) - 1] == 'm' ||
          inficks[strlen(inficks) - 1] == '^') {
        res_is_valid_string = 0;
      }
      if (inficks[i] == 'm' && inficks[i + 1] == 'm') {
        res_is_valid_string = 0;
      }
      if (inficks[i] == '(' && inficks[i + 1] == ')') {
        res_is_valid_string = 0;
      }
      if (inficks[i] == '(' &&
          (inficks[i + 1] == '+' || inficks[i + 1] == '*' ||
           inficks[i + 1] == '/' || inficks[i + 1] == 'm' ||
           inficks[i + 1] == '^')) {
        res_is_valid_string = 0;
      }
      if (inficks[i] == ')' &&
          (inficks[i - 1] == '+' || inficks[i - 1] == '-' ||
           inficks[i - 1] == '*' || inficks[i - 1] == '/' ||
           inficks[i - 1] == 'm' || inficks[i - 1] == '^')) {
        res_is_valid_string = 0;
      }
      if (inficks[i] == 'm' &&
          (inficks[i - 1] == '+' || inficks[i - 1] == '-' ||
           inficks[i - 1] == '/' || inficks[i - 1] == '*' ||
           inficks[i - 1] == '^')) {
        res_is_valid_string = 0;
      }
      if (inficks[i] == 'm' &&
          (inficks[i + 1] == '+' || inficks[i + 1] == '-' ||
           inficks[i + 1] == '/' || inficks[i + 1] == '*' ||
           inficks[i + 1] == '^')) {
        res_is_valid_string = 0;
      }
      if (is_symbol_number(inficks[i]) && inficks[i + 1] == '(') {
        res_is_valid_string = 0;
      }
      if (i != 0 && inficks[i] == ')' &&
          (is_symbol_number(inficks[i + 1]) || inficks[i + 1] == 's' ||
           inficks[i + 1] == 'c' || inficks[i + 1] == 't' ||
           inficks[i + 1] == 'C' || inficks[i + 1] == 'S' ||
           inficks[i + 1] == 'T' || inficks[i + 1] == 'q' ||
           inficks[i + 1] == 'l' || inficks[i + 1] == 'L')) {
        res_is_valid_string = 0;
      }
      if (inficks[i] == '.' && is_symbol_number(inficks[i - 1]) != 1) {
        res_is_valid_string = 0;
      }
      if (is_symbol_number(inficks[i]) &&
          (inficks[i + 1] == 's' || inficks[i + 1] == 'c' ||
           inficks[i + 1] == 't' || inficks[i + 1] == 'C' ||
           inficks[i + 1] == 'S' || inficks[i + 1] == 'T' ||
           inficks[i + 1] == 'q' || inficks[i + 1] == 'l' ||
           inficks[i + 1] == 'L')) {
        res_is_valid_string = 0;
      }
      if (inficks[i] == '.' && inficks[i + 1] == '(') {
        res_is_valid_string = 0;
      }
      if (inficks[i] == '.' &&
          (inficks[i + 1] == 's' || inficks[i + 1] == 'c' ||
           inficks[i + 1] == 't' || inficks[i + 1] == 'C' ||
           inficks[i + 1] == 'S' || inficks[i + 1] == 'T' ||
           inficks[i + 1] == 'q' || inficks[i + 1] == 'l' ||
           inficks[i + 1] == 'L')) {
        res_is_valid_string = 0;
      }
    }
  }
  return res_is_valid_string;
}

// Приоритет Математических Операций:
int precedency_operations(char symbol) {
  int res_precedency = 0;
  switch (symbol) {
  case '+':
    res_precedency = 1;
    break;
  case '-':
    res_precedency = 1;
    break;
  case '*':
    res_precedency = 2;
    break;
  case '/':
    res_precedency = 2;
    break;
  case 'm':
    res_precedency = 2;
    break; // mod
  case '^':
    res_precedency = 4;
    break; // pow
  // Тригонометрия:
  case 'c':
    res_precedency = 5;
    break; // cos(x)
  case 's':
    res_precedency = 5;
    break; // sin(x)
  case 't':
    res_precedency = 5;
    break; // tan(x)
  case 'C':
    res_precedency = 5;
    break; // acos(x)
  case 'S':
    res_precedency = 5;
    break; // asin(x)
  case 'T':
    res_precedency = 5;
    break; // atan(x)
  case 'q':
    res_precedency = 5;
    break; // sqrt(x)
  case 'l':
    res_precedency = 5;
    break; // ln(x)
  case 'L':
    res_precedency = 5;
    break; // log(x)
  case '~':
    res_precedency = 3;
    break; // Унарный минус
  }
  return res_precedency;
}

// Преобразование Инфиксной Строки в Обратную Польскую Нотацию:
int str_polish_notation(char *inficks, char *polskya) {
  int res_str_polish_notation = 1;
  int polskya_index = 0;
  Node *head = NULL;
  for (int i = 0; inficks[i] != '\0'; i++) {
    if (is_symbol_number(inficks[i]) || inficks[i] == '.') {
      while (is_symbol_number(inficks[i]) || inficks[i] == '.') {
        polskya[polskya_index++] = inficks[i];
        i++;
      }
      i--;
      polskya[polskya_index++] = ' ';
    } else if ((i == 0 && inficks[i] == '-') ||
               (i > 0 && inficks[i - 1] == '(' && inficks[i] == '-')) {
      push_node(&head, '~');
    } else if (precedency_operations(inficks[i]) > 0) {
      while (head != NULL && ((inficks[i] != '^' &&
                               precedency_operations(inficks[i]) <=
                                   precedency_operations(peek_node(&head))) ||
                              (inficks[i] == '^' &&
                               precedency_operations(inficks[i]) <
                                   precedency_operations(peek_node(&head))))) {
        polskya[polskya_index++] = pop_node(&head);
        polskya[polskya_index++] = ' ';
      }
      push_node(&head, inficks[i]);
    } else if (inficks[i] == '(') {
      push_node(&head, inficks[i]);
    } else if (inficks[i] == ')') {
      while (head != NULL && peek_node(&head) != '(') {
        polskya[polskya_index++] = pop_node(&head);
        polskya[polskya_index++] = ' ';
      }
      if (peek_node(&head) == '(') {
        pop_node(&head);
      }
    }
  }
  while (head != NULL) {
    polskya[polskya_index++] = pop_node(&head);
    polskya[polskya_index++] = ' ';
  }
  polskya[polskya_index] = '\0';
  free_stack(&head);
  return res_str_polish_notation;
}

double execute(char op, double first, double second) {
  double result = 0.0;
  switch (op) {
  case '+':
    result = first + second;
    break;
  case '-':
    result = first - second;
    break;
  case '*':
    result = first * second;
    break;
  case '/':
    result = first / second;
    break;
  case 'm':
    result = fmod(first, second);
    break; // mod
  case '^':
    result = pow(first, second);
    break; // pow
  case '~':
    result = -first;
    break; // Унарный минус
  }
  return result;
}

double execute_trig(char op, double first) {
  double result = 0.0;
  switch (op) {
  case 'c':
    result = cos(first);
    break; // cos(x)
  case 's':
    result = sin(first);
    break; // sin(x)
  case 't':
    result = tan(first);
    break; // tan(x)
  case 'C':
    result = acos(first);
    break; // acos(x)
  case 'S':
    result = asin(first);
    break; // asin(x)
  case 'T':
    result = atan(first);
    break; // atan(x)
  case 'q':
    result = sqrt(first);
    break; // sqrt(x)
  case 'l':
    result = log(first);
    break; // ln(x)
  case 'L':
    result = log10(first);
    break; // log(x)
  }
  return result;
}

// Вычисление Выражения Польской Нотации:
double polish_notation_expression(char *polskya) {
  Node_2 *head = NULL;
  for (int i = 0; polskya[i] != '\0'; i++) {
    if (is_symbol_number(polskya[i])) {
      char number[255];
      int j = 0;
      while (is_symbol_number(polskya[i]) || polskya[i] == '.') {
        number[j] = polskya[i];
        i++;
        j++;
      }
      number[j] = '\0';
      push_node_double(&head, atof(number));
    } else if (precedency_operations(polskya[i]) != 0) {
      if (polskya[i] == '~') {
        double last = is_empty_double(&head) == 0 ? 0 : pop_node_double(&head);
        push_node_double(&head, execute('-', 0, last));
      } else if (polskya[i] == '+' || polskya[i] == '-' || polskya[i] == '*' ||
                 polskya[i] == '/' || polskya[i] == '^' || polskya[i] == 'm') {
        double second =
            is_empty_double(&head) == 0 ? 0 : pop_node_double(&head);
        double first = is_empty_double(&head) == 0 ? 0 : pop_node_double(&head);
        push_node_double(&head, execute(polskya[i], first, second));
      } else {
        double first = is_empty_double(&head) == 0 ? 0 : pop_node_double(&head);
        push_node_double(&head, execute_trig(polskya[i], first));
      }
    }
  }
  double result = 0.0;
  if (is_empty_double(&head)) {
    result = pop_node_double(&head);
  }
  free_stack_double(&head);
  return result;
}