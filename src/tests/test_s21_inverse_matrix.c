#include "test.h"

// НЕКОРРЕКТНАЯ МАТРИЦА

// Не инициализированая матрица
START_TEST(test_s21_inverse_matrix_1_1) {
  matrix_t *A = NULL;
  matrix_t *result = NULL;
  int status = s21_inverse_matrix(A, result);
  ck_assert_int_eq(status, INCORRECT);
}
END_TEST

// Матрица с 0 строк 
START_TEST(test_s21_inverse_matrix_1_2) {
  matrix_t A, result;
  s21_create_matrix(0, 4, &A);
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// Матрица с 0 столбцов 
START_TEST(test_s21_inverse_matrix_1_3) {
  matrix_t A, result;
  s21_create_matrix(3, 0, &A);
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// НЕ ПОДХОДЯЩАЯ МАТРИЦА

// Матрица размера 1x1
START_TEST(test_s21_inverse_matrix_2_1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2.0;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// Прямоугольная матрица
START_TEST(test_s21_inverse_matrix_2_2) {
  matrix_t A, result;
  s21_create_matrix(3, 2, &A);
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// Матрица с нулевым детерминантом
START_TEST(test_s21_inverse_matrix_2_3) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 6.0;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// НОРМАЛЬНАЯ МАТРИЦА

// Матрица 2x2
START_TEST(test_s21_inverse_matrix_3_1) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], -2.0);
  ck_assert_double_eq(result.matrix[0][1], 1.0);
  ck_assert_double_eq(result.matrix[1][0], 1.5);
  ck_assert_double_eq(result.matrix[1][1], -0.5);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Матрица 3x3 из задания
START_TEST(test_s21_inverse_matrix_3_2) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_double_eq(result.matrix[0][0], 1.0);
  ck_assert_double_eq(result.matrix[0][1], -1.0);
  ck_assert_double_eq(result.matrix[0][2], 1.0);
  ck_assert_double_eq(result.matrix[1][0], -38.0);
  ck_assert_double_eq(result.matrix[1][1], 41.0);
  ck_assert_double_eq(result.matrix[1][2], -34.0);
  ck_assert_double_eq(result.matrix[2][0], 27.0);
  ck_assert_double_eq(result.matrix[2][1], -29.0);
  ck_assert_double_eq(result.matrix[2][2], 24.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

void test_s21_inverse_matrix(SRunner *runner) {
  Suite *tests = suite_create("test_s21_inverse_matrix");
  // НЕКОРРЕКТНАЯ МАТРИЦА
  tests = add_test(tests, test_s21_inverse_matrix_1_1);
  tests = add_test(tests, test_s21_inverse_matrix_1_2);
  tests = add_test(tests, test_s21_inverse_matrix_1_3);
  // НЕ ПОДХОДЯЩАЯ МАТРИЦА
  tests = add_test(tests, test_s21_inverse_matrix_2_1);
  tests = add_test(tests, test_s21_inverse_matrix_2_2);
  tests = add_test(tests, test_s21_inverse_matrix_2_3);
  // НОРМАЛЬНАЯ МАТРИЦА
  tests = add_test(tests, test_s21_inverse_matrix_3_1);
  tests = add_test(tests, test_s21_inverse_matrix_3_2);
  srunner_add_suite(runner, tests);
}