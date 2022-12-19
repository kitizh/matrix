#include "test.h"

// НЕКОРРЕКТНЫЕ МАТРИЦЫ

// Не инициализированная матрица
START_TEST(test_s21_create_matrix_1_1) {
  matrix_t *A = NULL;
  int status = s21_create_matrix(1, 1, A);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(A);
}
END_TEST

// Матрица 0 строк 
START_TEST(test_s21_create_matrix_1_2) {
  matrix_t A;
  int status = s21_create_matrix(0, 4, &A);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// Матрица 0 столбцов 
START_TEST(test_s21_create_matrix_1_3) {
  matrix_t A;
  int status = s21_create_matrix(3, 0, &A);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// НОРМАЛЬНЫЕ МАТРИЦЫ

// Матрица 1 на 1
START_TEST(test_s21_create_matrix_2_1) {
  matrix_t A;
  int status = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.rows, 1);
  ck_assert_int_eq(A.columns, 1);
  ck_assert_double_eq(A.matrix[0][0], 0.0);
  s21_remove_matrix(&A);
}
END_TEST

// Квадратная матрица
START_TEST(test_s21_create_matrix_2_2) {
  matrix_t A;
  int status = s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);
  ck_assert_double_eq(A.matrix[0][0], 0.0);
  ck_assert_double_eq(A.matrix[2][2], 0.0);
  s21_remove_matrix(&A);
}
END_TEST

// Прямоугольная матрица
START_TEST(test_s21_create_matrix_2_3) {
  matrix_t A;
  int status = s21_create_matrix(3, 4,  &A);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 4);
  ck_assert_double_eq(A.matrix[0][0], 0.0);
  ck_assert_double_eq(A.matrix[2][3], 0.0);
  s21_remove_matrix(&A);
}
END_TEST

void test_s21_create_matrix(SRunner *runner) {
  Suite *tests = suite_create("test_s21_create_matrix");
  // НЕКОРРЕКТНЫЕ МАТРИЦЫ
  tests = add_test(tests, test_s21_create_matrix_1_1);
  tests = add_test(tests, test_s21_create_matrix_1_2);
  tests = add_test(tests, test_s21_create_matrix_1_3);
  // НОРМАЛЬНЫЕ МАТРИЦЫ
  tests = add_test(tests, test_s21_create_matrix_2_1);
  tests = add_test(tests, test_s21_create_matrix_2_2);
  tests = add_test(tests, test_s21_create_matrix_2_3);
  srunner_add_suite(runner, tests);
}
