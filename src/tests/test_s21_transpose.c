#include "test.h"

// НЕКОРРЕКТНАЯ МАТРИЦА

// Не инициализированая матрица
START_TEST(test_s21_transpose_1_1) {
  matrix_t *A = NULL;
  matrix_t *result = NULL;
  int status = s21_transpose(A, result);
  ck_assert_int_eq(status, INCORRECT);
}
END_TEST

// Матрица с 0 строк 
START_TEST(test_s21_transpose_1_2) {
  matrix_t A, result;
  s21_create_matrix(0, 4, &A);
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// Матрица с 0 столбцов 
START_TEST(test_s21_transpose_1_3) {
  matrix_t A, result;
  s21_create_matrix(3, 0, &A);
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// НОРМАЛЬНАЯ МАТРИЦА

// Матрица размера 1x1
START_TEST(test_s21_transpose_3_1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2.0;
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq(result.matrix[0][0], 2.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Матрица с одним заполненным элементом
START_TEST(test_s21_transpose_3_2) {
  matrix_t A, result;
  s21_create_matrix(3, 2, &A);
  A.matrix[2][0] = 2.0;
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_double_eq(result.matrix[0][2], 2.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Матрица со всеми заполненными элементами
START_TEST(test_s21_transpose_3_3) {
  matrix_t A, result;
  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_double_eq(result.matrix[0][0], 1.0);
  ck_assert_double_eq(result.matrix[1][0], 2.0);
  ck_assert_double_eq(result.matrix[0][1], 3.0);
  ck_assert_double_eq(result.matrix[1][1], 4.0);
  ck_assert_double_eq(result.matrix[0][2], 5.0);
  ck_assert_double_eq(result.matrix[1][2], 6.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

void test_s21_transpose(SRunner *runner) {
  Suite *tests = suite_create("test_s21_transpose");
  // НЕКОРРЕКТНАЯ МАТРИЦА
  tests = add_test(tests, test_s21_transpose_1_1);
  tests = add_test(tests, test_s21_transpose_1_2);
  tests = add_test(tests, test_s21_transpose_1_3);
  // НОРМАЛЬНАЯ РАЗМЕРА
  tests = add_test(tests, test_s21_transpose_3_1);
  tests = add_test(tests, test_s21_transpose_3_2);
  tests = add_test(tests, test_s21_transpose_3_3);
  srunner_add_suite(runner, tests);
}