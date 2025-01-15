#include <check.h>

#include "notation.h"
#include "stack.h"

/**/
// ----ТЕСТЫ НА СТЕК ВЕЩЕСТВЕННЫХ ЧИСЕЛ----
START_TEST(stack_of_numbers_test_1) {
  Node_2 *head = NULL;
  push_node_double(&head, 1.0);
  free_stack_double(&head);
  int res = is_empty_double(&head);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(stack_of_numbers_test_2) {
  Node_2 *head = NULL;
  int res = is_empty_double(&head);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(stack_of_numbers_test_3) {
  Node_2 *head = NULL;
  push_node_double(&head, 1.0);
  int res = is_empty_double(&head);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(stack_of_numbers_test_4) {
  Node_2 *head = NULL;
  push_node_double(&head, 1.0);
  push_node_double(&head, 2.0);
  double res = peek_node_double(&head);
  ck_assert_double_eq(2.0, res);
}
END_TEST

START_TEST(stack_of_numbers_test_5) {
  Node_2 *head = NULL;
  int res = is_empty_double(&head);
  ck_assert_double_eq(0, res);
}
END_TEST

// ----ТЕСТЫ НА ВАЛИДНОСТЬ СКОБОК----

START_TEST(brackets_test_1) {
  char inficks[256] = "(1+2)";
  ck_assert_int_eq(1, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_2) {
  char inficks[256] = "(1+2)*(1+2)";
  ck_assert_int_eq(1, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_3) {
  char inficks[256] = "((1)+(1+2))";
  ck_assert_int_eq(1, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_4) {
  char inficks[256] = ")1+2(";
  ck_assert_int_eq(0, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_5) {
  char inficks[256] = ")1+3";
  ck_assert_int_eq(0, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_6) {
  char inficks[256] = "(1+3";
  ck_assert_int_eq(0, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_7) {
  char inficks[256] = "(1)+3";
  ck_assert_int_eq(1, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_8) {
  char inficks[256] = "(((1)-(1))*(1+(2)))";
  ck_assert_int_eq(1, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_9) {
  char inficks[256] = "(1)+((1-2)*((1)/(2)))";
  ck_assert_int_eq(1, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_10) {
  char inficks[256] = "(1)+(1)-(1)+(";
  ck_assert_int_eq(0, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_11) {
  char inficks[256] = "(((1)))";
  ck_assert_int_eq(1, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_12) {
  char inficks[256] = "(-1)*(4*4)+((1)/2)-1+(2)";
  ck_assert_int_eq(1, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_13) {
  char inficks[256] = "(-1)*(4*4)+((1)/2)-1+(2))";
  ck_assert_int_eq(0, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_14) {
  char inficks[256] = "(-1)*(4*4)+((1)/2)-1+(2()";
  ck_assert_int_eq(0, brackets(inficks));
}
END_TEST

START_TEST(brackets_test_15) {
  char inficks[256] = "(1+2*(1))";
  ck_assert_int_eq(1, brackets(inficks));
}
END_TEST

// ----ТЕСТЫ ПЕРЕВОДА ИНФИКСНОЙ ЗАПИСИ В ОБРАТНУЮ ПОЛЬСКУЮ НОТАЦИЮ----

START_TEST(polish_notation_test_1) {
  char inficks[256] = "1+2";
  char polskya[512];
  char result[512] = "1 2 + ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_2) {
  char inficks[256] = "11+22*3/(sin(1))";
  char polskya[512];
  char result[512] = "11 22 3 * 1 s / + ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_3) {
  char inficks[256] = "(22.2+12)";
  char polskya[512];
  char result[512] = "22.2 12 + ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_4) {
  char inficks[256] = "2/(3+2)*5";
  char polskya[512];
  char result[512] = "2 3 2 + / 5 * ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_5) {
  char inficks[256] = "123m12";
  char polskya[512];
  char result[512] = "123 12 m ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_6) {
  char inficks[256] = "s(1^2)*c(1^2)";
  char polskya[512];
  char result[512] = "1 2 ^ s 1 2 ^ c * ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_7) {
  char inficks[256] = "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
                      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  char polskya[512];
  char result[512] =
      "15 7 1 1 + - / 3 * 2 1 1 + + 15 * 7 200 1 + - / 3 * - 2 1 1 + + 15 7 1 "
      "1 + - / 3 * 2 1 1 + + - 15 7 1 1 + - / 3 * + 2 1 1 + + - * - ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_8) {
  char inficks[256] = "-(1)-5.3*(-22-2)/10";
  char polskya[512];
  char result[512] = "1 ~ 5.3 22 ~ 2 - * 10 / - ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_9) {
  char inficks[256] = "-1+2*(-1)/(-1)*76";
  char polskya[512];
  char result[512] = "1 ~ 2 1 ~ * 1 ~ / 76 * + ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_10) {
  char inficks[256] = "s(1^3)*c(1^2^3^4)";
  char polskya[512];
  char result[512] = "1 3 ^ s 1 2 3 4 ^ ^ ^ c * ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_11) {
  char inficks[256] = "(5+5)*~2";
  char polskya[512];
  char result[512] = "5 5 + 2 ~ * ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_12) {
  char inficks[256] = "(10+10*2)/~3";
  char polskya[512];
  char result[512] = "10 10 2 * + 3 ~ / ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_13) {
  char inficks[256] = "2.0/(3.0+2.0)*5.0";
  char polskya[512];
  char result[512] = "2.0 3.0 2.0 + / 5.0 * ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_14) {
  char inficks[256] = "~5 + ~4 * ~2";
  char polskya[512];
  char result[512] = "5 ~ 4 ~ 2 ~ * + ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

START_TEST(polish_notation_test_15) {
  char inficks[256] = "1.0 / 2.0 * ( 2.0 - 1.0 )";
  char polskya[512];
  char result[512] = "1.0 2.0 / 2.0 1.0 - * ";
  str_polish_notation(inficks, polskya);
  int equals = strcmp(result, polskya);
  // Если строки равны strcmp возвращает -> 0
  ck_assert_int_eq(0, equals);
}
END_TEST

// ----ТЕСТЫ НА ВЫЧИСЛЕНИЕ ВЫРАЖЕНИЯ В ОБРАТНОЙ ПОЛЬСКОЙ НОТАЦИИ----

START_TEST(expression_value_test_1) {
  double res_value = 0.0;
  char inficks[256] = "(5+5)*(-2)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -20.000000, 6);
}
END_TEST

START_TEST(expression_value_test_2) {
  double res_value = 0.0;
  char inficks[256] = "(10+10*2)/(-3)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -10.000000, 6);
}
END_TEST

START_TEST(expression_value_test_3) {
  double res_value = 0.0;
  char inficks[256] = "2.0/(3.0+2.0)*5.0";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 2.000000, 6);
}
END_TEST

START_TEST(expression_value_test_4) {
  double res_value = 0.0;
  char inficks[256] = "10.0+10.0*10.0";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 110.000000, 6);
}
END_TEST

START_TEST(expression_value_test_5) {
  double res_value = 0.0;
  char inficks[256] = "-5+(-4*(-2))";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 3.000000, 6);
}
END_TEST

START_TEST(expression_value_test_6) {
  double res_value = 0.0;
  char inficks[256] = "-5.0m(-3.0)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -2.000000, 6);
}
END_TEST

START_TEST(expression_value_test_7) {
  double res_value = 0.0;
  char inficks[256] = "1.0/2.0*(2.0-1.0)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 0.500000, 6);
}
END_TEST

START_TEST(expression_value_test_8) {
  double res_value = 0.0;
  char inficks[256] = "1.1+2.0+(3.0*4.0)+(5.0+6.8)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 26.900000, 6);
}
END_TEST

START_TEST(expression_value_test_9) {
  double res_value = 0.0;
  char inficks[256] = "1.1+2.0+(3.0-5.5)*(1.5-6.5)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 15.600000, 6);
}
END_TEST

START_TEST(expression_value_test_10) {
  double res_value = 0.0;
  char inficks[256] = "6.6-1.1-2.2-3.3-4.4-5.5";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -9.900000, 6);
}
END_TEST

START_TEST(expression_value_test_11) {
  double res_value = 0.0;
  char inficks[256] = "1.1-2.2-3.3-4.4-5.5+6.6";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -7.7000000, 6);
}
END_TEST

START_TEST(expression_value_test_12) {
  double res_value = 0.0;
  char inficks[256] = "(-1.1* 5)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq(res_value, -5.5);
}
END_TEST

START_TEST(expression_value_test_13) {
  double res_value = 0.0;
  char inficks[256] = "2^2";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq(res_value, 4.000000);
}
END_TEST

START_TEST(expression_value_test_14) {
  double res_value = 0.0;
  char inficks[256] = "5^3";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq(res_value, 125.000000);
}
END_TEST

START_TEST(expression_value_test_15) {
  double res_value = 0.0;
  char inficks[256] = "-5+3*2^2";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq(res_value, 7.000000);
}
END_TEST

START_TEST(expression_value_test_16) {
  double res_value = 0.0;
  char inficks[256] = "5mod(-1.5)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq(res_value, 0.500000);
}
END_TEST

START_TEST(expression_value_test_17) {
  double res_value = 0.0;
  char inficks[256] = "(5mod(-1.5)*4)^2";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq(res_value, 4.000000);
}
END_TEST

START_TEST(expression_value_test_18) {
  double res_value = 0.0;
  char inficks[256] = "s(30)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -0.988032, 6);
}
END_TEST

START_TEST(expression_value_test_19) {
  double res_value = 0.0;
  char inficks[256] = "s(45)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 0.850904, 6);
}
END_TEST

START_TEST(expression_value_test_20) {
  double res_value = 0.0;
  char inficks[256] = "s(60)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -0.304811, 6);
}
END_TEST

START_TEST(expression_value_test_21) {
  double res_value = 0.0;
  char inficks[256] = "s(90)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 0.893997, 6);
}
END_TEST

START_TEST(expression_value_test_22) {
  double res_value = 0.0;
  char inficks[256] = "s(120)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 0.580611, 6);
}
END_TEST

START_TEST(expression_value_test_23) {
  double res_value = 0.0;
  char inficks[256] = "s(180)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -0.801153, 6);
}
END_TEST

START_TEST(expression_value_test_24) {
  double res_value = 0.0;
  char inficks[256] = "s(270)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -0.176046, 6);
}
END_TEST

START_TEST(expression_value_test_25) {
  double res_value = 0.0;
  char inficks[256] = "s(360)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 0.958916, 6);
}
END_TEST

START_TEST(expression_value_test_26) {
  double res_value = 0.0;
  char inficks[256] = "s(0)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 0.000000, 6);
}
END_TEST

START_TEST(expression_value_test_27) {
  double res_value = 0.0;
  char inficks[256] = "c(30)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 0.154251, 6);
}
END_TEST

START_TEST(expression_value_test_28) {
  double res_value = 0.0;
  char inficks[256] = "c(45)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 0.525322, 6);
}
END_TEST

START_TEST(expression_value_test_29) {
  double res_value = 0.0;
  char inficks[256] = "c(90)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -0.448074, 6);
}
END_TEST

START_TEST(expression_value_test_30) {
  double res_value = 0.0;
  char inficks[256] = "c(120)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 0.814181, 6);
}
END_TEST

START_TEST(expression_value_test_31) {
  double res_value = 0.0;
  char inficks[256] = "c(180)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -0.598460, 6);
}
END_TEST

START_TEST(expression_value_test_32) {
  double res_value = 0.0;
  char inficks[256] = "c(270)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 0.984382, 6);
}
END_TEST

START_TEST(expression_value_test_33) {
  double res_value = 0.0;
  char inficks[256] = "c(360)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -0.283691, 6);
}
END_TEST

START_TEST(expression_value_test_34) {
  double res_value = 0.0;
  char inficks[256] = "c(0)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, 1.000000, 6);
}
END_TEST

START_TEST(expression_value_test_35) {
  double res_value = 0.0;
  char inficks[256] = "t(90)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -1.995200, 6);
}
END_TEST

START_TEST(expression_value_test_36) {
  double res_value = 0.0;
  char inficks[256] = "t(90)*s(30)+(c(45)^2)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq_tol(res_value, -1.695358, 6);
}
END_TEST

START_TEST(expression_value_test_37) {
  double res_value = 0.0;
  char inficks[256] = "2^2^3";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq(res_value, 256.000000);
}
END_TEST

START_TEST(expression_value_test_38) {
  double res_value = 0.0;
  char inficks[256] = "(2^2)^3";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq(res_value, 64.000000);
}
END_TEST

START_TEST(expression_value_test_39) {
  double res_value = 0.0;
  char inficks[256] = "(2^2^3-200)/2";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_double_eq(res_value, 28.000000);
}
END_TEST

START_TEST(expression_value_test_40) {
  double res_value = 0.0;
  char inficks[256] = "(s(45)+c(30)+t(45)+t(90))*2";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 1.25946, 6);
}
END_TEST

START_TEST(expression_value_test_41) {
  double res_value = 0.0;
  char inficks[256] = "t(180)^2";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 1.792091, 6);
}
END_TEST

START_TEST(expression_value_test_42) {
  double res_value = 0.0;
  char inficks[256] = "S(0.5)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 1.25946, 6);
}
END_TEST

START_TEST(expression_value_test_43) {
  double res_value = 0.0;
  char inficks[256] = "C(0.5)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 1.047198, 6);
}
END_TEST

START_TEST(expression_value_test_44) {
  double res_value = 0.0;
  char inficks[256] = "C(1)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 0.000000, 6);
}
END_TEST

START_TEST(expression_value_test_45) {
  double res_value = 0.0;
  char inficks[256] = "T(0)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 0.000000, 6);
}
END_TEST

START_TEST(expression_value_test_46) {
  double res_value = 0.0;
  char inficks[256] = "T(1)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 0.785398, 6);
}
END_TEST

START_TEST(expression_value_test_47) {
  double res_value = 0.0;
  char inficks[256] = "q(100)/q(25)*q(121)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 22.000000, 6);
}
END_TEST

START_TEST(expression_value_test_48) {
  double res_value = 0.0;
  char inficks[256] = "l(5)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 1.609438, 6);
}
END_TEST

START_TEST(expression_value_test_49) {
  double res_value = 0.0;
  char inficks[256] = "l(5)+q(22)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 6.299853, 6);
}
END_TEST

START_TEST(expression_value_test_50) {
  double res_value = 0.0;
  char inficks[256] = "(-5.0)mod(-3.0)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, -2.000000, 6);
}
END_TEST

START_TEST(expression_value_test_51) {
  double res_value = 0.0;
  char inficks[256] = "L(10)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 1.000000, 6);
}
END_TEST

START_TEST(expression_value_test_52) {
  double res_value = 0.0;
  char inficks[256] = "1.0/2.0*(2.0-1.0)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 0.500000, 6);
}
END_TEST

START_TEST(expression_value_test_53) {
  double res_value = 0.0;
  char inficks[256] = "1.1+2.0+(3.0*4.0)+(5.0+6.8)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 26.880000, 6);
}
END_TEST

START_TEST(expression_value_test_54) {
  double res_value = 0.0;
  char inficks[256] = "10^10";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 10000000000.000000, 6);
}
END_TEST

START_TEST(expression_value_test_55) {
  double res_value = 0.0;
  char inficks[256] = "10000000000-10000000000";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 0.000000, 6);
}
END_TEST

START_TEST(expression_value_test_56) {
  double res_value = 0.0;
  char inficks[256] = "1+2+3+4+5+6+7+8+9+10+100-3-2-10-3*2+12+15+16+17+18/2";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 203.000000, 6);
}
END_TEST

START_TEST(expression_value_test_57) {
  double res_value = 0.0;
  char inficks[256] = "1+1";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 2.000000, 6);
}
END_TEST

START_TEST(expression_value_test_58) {
  double res_value = 0.0;
  char inficks[256] = "1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 1.000000, 6);
}
END_TEST

START_TEST(expression_value_test_59) {
  double res_value = 0.0;
  char inficks[256] = "c(5)+l(10)-s(89)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 1.726178, 6);
}
END_TEST

START_TEST(expression_value_test_60) {
  double res_value = 0.0;
  char inficks[256] = "c(13)*c(4)+s(5)-T(8)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, -2.998512, 6);
}
END_TEST

START_TEST(expression_value_test_61) {
  double res_value = 0.0;
  char inficks[256] = "-12.22+c(14)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, -12.083262, 6);
}
END_TEST

START_TEST(expression_value_test_62) {
  double res_value = 0.0;
  char inficks[256] = "1.222-5.66/(1*8.2)+c(4)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, -0.121887, 6);
}
END_TEST

START_TEST(expression_value_test_63) {
  double res_value = 0.0;
  char inficks[256] = "C(0.2132+0.12)-12";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, -10.768899, 6);
}
END_TEST

START_TEST(expression_value_test_64) {
  double res_value = 0.0;
  char inficks[256] = "4.36*5.32/9+(c(8)*s(8))";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 2.433292, 6);
}
END_TEST

START_TEST(expression_value_test_65) {
  double res_value = 0.0;
  char inficks[256] = "89*54+1.3256-8*(7/9)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 4801.103377, 6);
}
END_TEST

START_TEST(expression_value_test_66) {
  double res_value = 0.0;
  char inficks[256] = "q(45)*s(8)*l(12)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 16.491870, 6);
}
END_TEST

START_TEST(expression_value_test_67) {
  double res_value = 0.0;
  char inficks[256] = "q(45)*s(8)*l(12)*C(0.5)+1.22/0.1+6";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 35.470246, 6);
}
END_TEST

START_TEST(expression_value_test_68) {
  double res_value = 0.0;
  char inficks[256] = "-12+(-1.2+1)/23";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, -12.008695, 6);
}
END_TEST

START_TEST(expression_value_test_69) {
  double res_value = 0.0;
  char inficks[256] = "(-1)*(-1)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 1.000000, 6);
}
END_TEST

START_TEST(expression_value_test_70) {
  double res_value = 0.0;
  char inficks[256] = "(-1)*(-1)+(-2)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, -1.000000, 6);
}
END_TEST

START_TEST(expression_value_test_71) {
  double res_value = 0.0;
  char inficks[256] = "s(1)*c(1)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 0.4546487, 7);
}
END_TEST

START_TEST(expression_value_test_72) {
  double res_value = 0.0;
  char inficks[256] = "12.366666*1.6*(c(4)+t(8))";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, -147.4770444, 7);
}
END_TEST

START_TEST(expression_value_test_73) {
  double res_value = 0.0;
  char inficks[256] = "7.83+9.32*8+(20*c(15))+T(0.1)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 67.2959103, 7);
}
END_TEST

START_TEST(expression_value_test_74) {
  double res_value = 0.0;
  char inficks[256] = "S(0.5)*C(0.22+0.1)+1";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 1.6519154, 7);
}
END_TEST

START_TEST(expression_value_test_75) {
  double res_value = 0.0;
  char inficks[256] = "T(0.82)*(1.2+1.3)-89*(-4+6)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, -176.2829558, 7);
}
END_TEST

START_TEST(expression_value_test_76) {
  double res_value = 0.0;
  char inficks[256] = "C(0.1)+S(0.1)+T(0.99)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 2.3511694, 7);
}
END_TEST

START_TEST(expression_value_test_77) {
  double res_value = 0.0;
  char inficks[256] = "l(25)+c(89)/2.5+5*(c(5)+s(0.25))*2.3+C(0.65)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 10.3934191, 7);
}
END_TEST

START_TEST(expression_value_test_78) {
  double res_value = 0.0;
  char inficks[256] = "4*9/0.222*8+C(0.1)*1-10000+3*c(4+0.1)";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, -8702.9565456, 7);
}
END_TEST

START_TEST(expression_value_test_79) {
  double res_value = 0.0;
  char inficks[256] = "70*6+c(5)*s(0.1)/1/2/3*10.223*s(3.0)+1.222222222222222";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 421.2223772, 7);
}
END_TEST

START_TEST(expression_value_test_80) {
  double res_value = 0.0;
  char inficks[256] = "c(1)*s(1)^0.1";
  char polskya[512];
  str_polish_notation(inficks, polskya);
  res_value = polish_notation_expression(polskya);
  ck_assert_ldouble_eq_tol(res_value, 0.6669900, 7);
}
END_TEST

// ----ТЕСТЫ НА НЕВАЛИДНОСТЬ ИНФИКСНОГО ВЫРАЖЕНИЯ----

START_TEST(invalid_expression_test_1) {
  char inficks[256] = "*1+2";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_2) {
  char inficks[256] = "+1+2*(1+2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_3) {
  char inficks[256] = "-1+2*(1+2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_4) {
  char inficks[256] = "^1+2*(1+2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_5) {
  char inficks[256] = "/1+2*(1+2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_6) {
  char inficks[256] = "m1+2*(1+2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_7) {
  char inficks[256] = "1..2+2*(1+2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_8) {
  char inficks[256] = "1.2+2*()";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_9) {
  char inficks[256] = "1.2+2*(1+2).";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_10) {
  char inficks[256] = "1.2+2*(1+2)m";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_11) {
  char inficks[256] = "1.2+2*(1+2)^";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_12) {
  char inficks[256] = "1.2+2*(1+2)/";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_13) {
  char inficks[256] = "1.2+2*(1+2)+";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_14) {
  char inficks[256] = "1.2+2*(1+2)-";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_15) {
  char inficks[256] = "1.2+2*(1+2)*";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_16) {
  char inficks[256] = "()";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_17) {
  char inficks[256] = "(1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_18) {
  char inficks[256] = "(-1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_19) {
  char inficks[256] = "(*1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_20) {
  char inficks[256] = "(/1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_21) {
  char inficks[256] = "(^1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_22) {
  char inficks[256] = "(m1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_23) {
  char inficks[256] = "1.+1.";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_24) {
  char inficks[256] = "1(1+2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_25) {
  char inficks[256] = "(1+2)1";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_26) {
  char inficks[256] = "(1+2)+1";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_27) {
  char inficks[256] = "(1+2)+1.-";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_28) {
  char inficks[256] = "s(^)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_29) {
  char inficks[256] = "s(1^2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_30) {
  char inficks[256] = "s(1^2/)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_31) {
  char inficks[256] = "1m2";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_32) {
  char inficks[256] = "1mm2";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_33) {
  char inficks[256] = "1-m2";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_34) {
  char inficks[256] = "1m*2";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_35) {
  char inficks[256] = "1^m/2";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_36) {
  char inficks[256] = "1.(1+2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_37) {
  char inficks[256] = "1c(1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_38) {
  char inficks[256] = "1+c(1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_39) {
  char inficks[256] = "12+1.2*(1++2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_40) {
  char inficks[256] = "12+1.2*(1+2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_41) {
  char inficks[256] =
      "123232+1232+232131+123223*123213213+131232213/"
      "12321321*(123213+2312312)-123232+1232+232131+123223*123213213+131232213/"
      "12321321*(123213+2312312)*123232+1232+232131+123223*123213213+131232213/"
      "12321321*(123213+2312312)*1232133231-21321322+1232133-123213+12323";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_42) {
  char inficks[256] =
      "123232+132+232131+123223*123213213+131232213/"
      "12321321*(123213+2312312)-123232+1232+232131+123223*123213213+131232213/"
      "12321321*(123213+2312312)*123232+1232+232131+123223*123213213+131232213/"
      "12321321*(123213+2312312)*1232133231-21321322+1232133-123213+12323";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_43) {
  char inficks[256] = "12+1.2*(1+2)^^1";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_44) {
  char inficks[256] = "c(.)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_45) {
  char inficks[256] = "c(-.1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_46) {
  char inficks[256] = "c(1)s(1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_47) {
  char inficks[256] = "c(1)-s(1)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(invalid_expression_test_48) {
  char inficks[256] = "())-2+sin(x)*(+(-2)*2)^2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_49) {
  char inficks[256] = "(0.2.2))-2+sin(x)*(+(-2)*2)^2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_50) {
  char inficks[256] = "(0.2))-2+sin(x)*(+(-2)*2)^2)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_51) {
  char inficks[256] = "2.s(0.5)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_52) {
  char inficks[256] = "2.0s(0.5)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_53) {
  char inficks[256] = "2.0c(0.5)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_54) {
  char inficks[256] = "2.0t(0.5)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

START_TEST(invalid_expression_test_55) {
  char inficks[256] = "2.0l(0.5)";
  int res = is_valid_string(inficks);
  ck_assert_int_eq(0, res);
}
END_TEST

// Набор тестов на стек вещественных чисел
Suite *stack_of_numbers_suite() {
  Suite *selection;
  TCase *test_core;
  selection = suite_create("stack_of_numbers");
  test_core = tcase_create("core");
  tcase_add_test(test_core, stack_of_numbers_test_1);
  tcase_add_test(test_core, stack_of_numbers_test_2);
  tcase_add_test(test_core, stack_of_numbers_test_3);
  tcase_add_test(test_core, stack_of_numbers_test_4);
  tcase_add_test(test_core, stack_of_numbers_test_5);
  suite_add_tcase(selection, test_core);
  return selection;
}

// Набор тестов на валидность скобок
Suite *brackets_suite() {
  Suite *selection;
  TCase *test_core;
  selection = suite_create("brackets");
  test_core = tcase_create("core");
  tcase_add_test(test_core, brackets_test_1);
  tcase_add_test(test_core, brackets_test_2);
  tcase_add_test(test_core, brackets_test_3);
  tcase_add_test(test_core, brackets_test_4);
  tcase_add_test(test_core, brackets_test_5);
  tcase_add_test(test_core, brackets_test_6);
  tcase_add_test(test_core, brackets_test_7);
  tcase_add_test(test_core, brackets_test_8);
  tcase_add_test(test_core, brackets_test_9);
  tcase_add_test(test_core, brackets_test_10);
  tcase_add_test(test_core, brackets_test_11);
  tcase_add_test(test_core, brackets_test_12);
  tcase_add_test(test_core, brackets_test_13);
  tcase_add_test(test_core, brackets_test_14);
  tcase_add_test(test_core, brackets_test_15);
  suite_add_tcase(selection, test_core);
  return selection;
}

// Набор тестов перевода инфиксной записи в обратную польскую нотацию
Suite *polish_notation_suite() {
  Suite *selection;
  TCase *test_core;
  selection = suite_create("polish_notation");
  test_core = tcase_create("core");
  tcase_add_test(test_core, polish_notation_test_1);
  tcase_add_test(test_core, polish_notation_test_2);
  tcase_add_test(test_core, polish_notation_test_3);
  tcase_add_test(test_core, polish_notation_test_4);
  tcase_add_test(test_core, polish_notation_test_5);
  tcase_add_test(test_core, polish_notation_test_6);
  tcase_add_test(test_core, polish_notation_test_7);
  tcase_add_test(test_core, polish_notation_test_8);
  tcase_add_test(test_core, polish_notation_test_9);
  tcase_add_test(test_core, polish_notation_test_10);
  tcase_add_test(test_core, polish_notation_test_11);
  tcase_add_test(test_core, polish_notation_test_12);
  tcase_add_test(test_core, polish_notation_test_13);
  tcase_add_test(test_core, polish_notation_test_14);
  tcase_add_test(test_core, polish_notation_test_15);
  suite_add_tcase(selection, test_core);
  return selection;
}

// Набор тестов для вычисления выражений в обратной польской нотации
Suite *expression_value_suite() {
  Suite *selection;
  TCase *test_core;
  selection = suite_create("expression_value");
  test_core = tcase_create("core");
  tcase_add_test(test_core, expression_value_test_1);
  tcase_add_test(test_core, expression_value_test_2);
  tcase_add_test(test_core, expression_value_test_3);
  tcase_add_test(test_core, expression_value_test_4);
  tcase_add_test(test_core, expression_value_test_5);
  tcase_add_test(test_core, expression_value_test_6);
  tcase_add_test(test_core, expression_value_test_7);
  tcase_add_test(test_core, expression_value_test_8);
  tcase_add_test(test_core, expression_value_test_9);
  tcase_add_test(test_core, expression_value_test_10);
  tcase_add_test(test_core, expression_value_test_11);
  tcase_add_test(test_core, expression_value_test_12);
  tcase_add_test(test_core, expression_value_test_13);
  tcase_add_test(test_core, expression_value_test_14);
  tcase_add_test(test_core, expression_value_test_15);
  tcase_add_test(test_core, expression_value_test_16);
  tcase_add_test(test_core, expression_value_test_17);
  tcase_add_test(test_core, expression_value_test_18);
  tcase_add_test(test_core, expression_value_test_19);
  tcase_add_test(test_core, expression_value_test_20);
  tcase_add_test(test_core, expression_value_test_21);
  tcase_add_test(test_core, expression_value_test_22);
  tcase_add_test(test_core, expression_value_test_23);
  tcase_add_test(test_core, expression_value_test_24);
  tcase_add_test(test_core, expression_value_test_25);
  tcase_add_test(test_core, expression_value_test_26);
  tcase_add_test(test_core, expression_value_test_27);
  tcase_add_test(test_core, expression_value_test_28);
  tcase_add_test(test_core, expression_value_test_29);
  tcase_add_test(test_core, expression_value_test_30);
  tcase_add_test(test_core, expression_value_test_31);
  tcase_add_test(test_core, expression_value_test_32);
  tcase_add_test(test_core, expression_value_test_33);
  tcase_add_test(test_core, expression_value_test_34);
  tcase_add_test(test_core, expression_value_test_35);
  tcase_add_test(test_core, expression_value_test_36);
  tcase_add_test(test_core, expression_value_test_37);
  tcase_add_test(test_core, expression_value_test_38);
  tcase_add_test(test_core, expression_value_test_39);
  tcase_add_test(test_core, expression_value_test_40);
  tcase_add_test(test_core, expression_value_test_41);
  tcase_add_test(test_core, expression_value_test_42);
  tcase_add_test(test_core, expression_value_test_43);
  tcase_add_test(test_core, expression_value_test_44);
  tcase_add_test(test_core, expression_value_test_45);
  tcase_add_test(test_core, expression_value_test_46);
  tcase_add_test(test_core, expression_value_test_47);
  tcase_add_test(test_core, expression_value_test_48);
  tcase_add_test(test_core, expression_value_test_49);
  tcase_add_test(test_core, expression_value_test_50);
  tcase_add_test(test_core, expression_value_test_51);
  tcase_add_test(test_core, expression_value_test_52);
  tcase_add_test(test_core, expression_value_test_53);
  tcase_add_test(test_core, expression_value_test_54);
  tcase_add_test(test_core, expression_value_test_55);
  tcase_add_test(test_core, expression_value_test_56);
  tcase_add_test(test_core, expression_value_test_57);
  tcase_add_test(test_core, expression_value_test_58);
  tcase_add_test(test_core, expression_value_test_59);
  tcase_add_test(test_core, expression_value_test_60);
  tcase_add_test(test_core, expression_value_test_61);
  tcase_add_test(test_core, expression_value_test_62);
  tcase_add_test(test_core, expression_value_test_63);
  tcase_add_test(test_core, expression_value_test_64);
  tcase_add_test(test_core, expression_value_test_65);
  tcase_add_test(test_core, expression_value_test_66);
  tcase_add_test(test_core, expression_value_test_67);
  tcase_add_test(test_core, expression_value_test_68);
  tcase_add_test(test_core, expression_value_test_69);
  tcase_add_test(test_core, expression_value_test_70);
  tcase_add_test(test_core, expression_value_test_71);
  tcase_add_test(test_core, expression_value_test_72);
  tcase_add_test(test_core, expression_value_test_73);
  tcase_add_test(test_core, expression_value_test_74);
  tcase_add_test(test_core, expression_value_test_75);
  tcase_add_test(test_core, expression_value_test_76);
  tcase_add_test(test_core, expression_value_test_77);
  tcase_add_test(test_core, expression_value_test_78);
  tcase_add_test(test_core, expression_value_test_79);
  tcase_add_test(test_core, expression_value_test_80);
  suite_add_tcase(selection, test_core);
  return selection;
}

// Набор тестов на проверку невалидного выражения
Suite *invalid_expression_suite() {
  Suite *selection;
  TCase *test_core;
  selection = suite_create("invalid_expression");
  test_core = tcase_create("core");
  tcase_add_test(test_core, invalid_expression_test_1);
  tcase_add_test(test_core, invalid_expression_test_2);
  tcase_add_test(test_core, invalid_expression_test_3);
  tcase_add_test(test_core, invalid_expression_test_4);
  tcase_add_test(test_core, invalid_expression_test_5);
  tcase_add_test(test_core, invalid_expression_test_6);
  tcase_add_test(test_core, invalid_expression_test_7);
  tcase_add_test(test_core, invalid_expression_test_8);
  tcase_add_test(test_core, invalid_expression_test_9);
  tcase_add_test(test_core, invalid_expression_test_10);
  tcase_add_test(test_core, invalid_expression_test_11);
  tcase_add_test(test_core, invalid_expression_test_12);
  tcase_add_test(test_core, invalid_expression_test_13);
  tcase_add_test(test_core, invalid_expression_test_14);
  tcase_add_test(test_core, invalid_expression_test_15);
  tcase_add_test(test_core, invalid_expression_test_16);
  tcase_add_test(test_core, invalid_expression_test_17);
  tcase_add_test(test_core, invalid_expression_test_18);
  tcase_add_test(test_core, invalid_expression_test_19);
  tcase_add_test(test_core, invalid_expression_test_20);
  tcase_add_test(test_core, invalid_expression_test_21);
  tcase_add_test(test_core, invalid_expression_test_22);
  tcase_add_test(test_core, invalid_expression_test_23);
  tcase_add_test(test_core, invalid_expression_test_24);
  tcase_add_test(test_core, invalid_expression_test_25);
  tcase_add_test(test_core, invalid_expression_test_26);
  tcase_add_test(test_core, invalid_expression_test_27);
  tcase_add_test(test_core, invalid_expression_test_28);
  tcase_add_test(test_core, invalid_expression_test_29);
  tcase_add_test(test_core, invalid_expression_test_30);
  tcase_add_test(test_core, invalid_expression_test_31);
  tcase_add_test(test_core, invalid_expression_test_32);
  tcase_add_test(test_core, invalid_expression_test_33);
  tcase_add_test(test_core, invalid_expression_test_34);
  tcase_add_test(test_core, invalid_expression_test_35);
  tcase_add_test(test_core, invalid_expression_test_36);
  tcase_add_test(test_core, invalid_expression_test_37);
  tcase_add_test(test_core, invalid_expression_test_38);
  tcase_add_test(test_core, invalid_expression_test_39);
  tcase_add_test(test_core, invalid_expression_test_40);
  tcase_add_test(test_core, invalid_expression_test_41);
  tcase_add_test(test_core, invalid_expression_test_42);
  tcase_add_test(test_core, invalid_expression_test_43);
  tcase_add_test(test_core, invalid_expression_test_44);
  tcase_add_test(test_core, invalid_expression_test_45);
  tcase_add_test(test_core, invalid_expression_test_46);
  tcase_add_test(test_core, invalid_expression_test_47);
  tcase_add_test(test_core, invalid_expression_test_48);
  tcase_add_test(test_core, invalid_expression_test_49);
  tcase_add_test(test_core, invalid_expression_test_50);
  tcase_add_test(test_core, invalid_expression_test_51);
  tcase_add_test(test_core, invalid_expression_test_52);
  tcase_add_test(test_core, invalid_expression_test_53);
  tcase_add_test(test_core, invalid_expression_test_54);
  tcase_add_test(test_core, invalid_expression_test_55);
  suite_add_tcase(selection, test_core);
  return selection;
}

void case_tests(Suite *selection, int *fail) {
  SRunner *runner = srunner_create(selection);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int fail = 0;
  case_tests(stack_of_numbers_suite(), &fail);
  case_tests(brackets_suite(), &fail);
  case_tests(polish_notation_suite(), &fail);
  case_tests(expression_value_suite(), &fail);
  case_tests(invalid_expression_suite(), &fail);
  return 0;
}

// int main() {
//   // Отладочный main
//   char inficks[256] = "x+2-x+1*(s(x)";
//   char polskya[512];
//   if (brackets(inficks) && is_valid_string(inficks)) {
//     str_polish_notation(inficks, polskya);
//     double res = polish_notation_expression(polskya);
//     printf("%s\n", polskya);
//     printf("%f", res);
//   } else {
//     printf("Error");
//   }
//   return 0;
// }