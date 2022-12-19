#include "test.h"

// НЕКОРРЕКТНАЯ МАТРИЦА

// Не инициализированая матрица
START_TEST(test_s21_determinant_1_1) {
  matrix_t *A = NULL;
  double result;
  int status = s21_determinant(A, &result);
  ck_assert_int_eq(status, INCORRECT);
}
END_TEST

// Матрица с 0 строк 
START_TEST(test_s21_determinant_1_2) {
  matrix_t A;
  double result;
  s21_create_matrix(0, 4, &A);
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// Матрица с 0 столбцов 
START_TEST(test_s21_determinant_1_3) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 0, &A);
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// Прямоугольная матрица 
START_TEST(test_s21_determinant_1_4) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 2, &A);
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// НОРМАЛЬНАЯ МАТРИЦА

// Матрица размера 1x1
START_TEST(test_s21_determinant_2_1) {
  matrix_t A;
  double result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq(result, 2.0);
  s21_remove_matrix(&A);
}
END_TEST

// Матрица 2x2 с одним заполненным элементом
START_TEST(test_s21_determinant_2_2) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);
  A.matrix[1][0] = 2.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq(result, 0.0);
  s21_remove_matrix(&A);
}
END_TEST

// Матрица 2x2 со всеми заполненными элементами
START_TEST(test_s21_determinant_2_3) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq(result, -2.0);
  s21_remove_matrix(&A);
}
END_TEST

// Матрица 3x3 из задания
START_TEST(test_s21_determinant_2_4) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq(result, 0.0);
  s21_remove_matrix(&A);
}
END_TEST

// Другая матрица 3x3 с отличным от 0 детерминантом
START_TEST(test_s21_determinant_2_5) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 3.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq(result, -8.0);
  s21_remove_matrix(&A);
}
END_TEST

// Матрица 4x4
START_TEST(test_s21_determinant_2_6) {
  matrix_t A;
  double result;
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[0][2] = 5.0;
  A.matrix[0][3] = 11.0;
  A.matrix[1][0] = 5.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 9.0;
  A.matrix[1][3] = 8.0;
  A.matrix[2][0] = 2.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 5.0;
  A.matrix[2][3] = 4.0;
  A.matrix[3][0] = 3.0;
  A.matrix[3][1] = 2.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 0.0;
  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq(result, 593.0);
  s21_remove_matrix(&A);
}
END_TEST

void test_s21_determinant(SRunner *runner) {
  Suite *tests = suite_create("test_s21_determinant");
  // НЕКОРРЕКТНАЯ МАТРИЦА
  tests = add_test(tests, test_s21_determinant_1_1);
  tests = add_test(tests, test_s21_determinant_1_2);
  tests = add_test(tests, test_s21_determinant_1_3);
  tests = add_test(tests, test_s21_determinant_1_4);
  // НОРМАЛЬНАЯ РАЗМЕРА
  tests = add_test(tests, test_s21_determinant_2_1);
  tests = add_test(tests, test_s21_determinant_2_2);
  tests = add_test(tests, test_s21_determinant_2_3);
  tests = add_test(tests, test_s21_determinant_2_4);
  tests = add_test(tests, test_s21_determinant_2_5);
  tests = add_test(tests, test_s21_determinant_2_6);
  srunner_add_suite(runner, tests);
}
