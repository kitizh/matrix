#include "test.h"

// НЕКОРРЕКТНЫЕ МАТРИЦЫ

// Не инициализированые матрицы
START_TEST(test_s21_mult_matrix_1_1) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *result = NULL;
  int status = s21_mult_matrix(A, B, result);
  ck_assert_int_eq(status, INCORRECT);
}
END_TEST

// Матрицы в 0 строк 
START_TEST(test_s21_mult_matrix_1_2) {
  matrix_t A, B, result;
  s21_create_matrix(0, 4, &A);
  s21_create_matrix(0, 4, &B);
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Матрицы 0 столбцов 
START_TEST(test_s21_mult_matrix_1_3) {
  matrix_t A, B, result;
  s21_create_matrix(3, 0, &A);
  s21_create_matrix(3, 0, &B);
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// НЕКОРРЕКТНАЯ МАТРИЦА И НОРМАЛЬНАЯ МАТРИЦА

// Не инициализированая матрица и нормальная
START_TEST(test_s21_mult_matrix_2_1) {
  matrix_t A, result;
  matrix_t *B = NULL;
  s21_create_matrix(1, 1, &A);
  int status = s21_mult_matrix(&A, B, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// Матрица в 0 строк и нормальная 
START_TEST(test_s21_mult_matrix_2_2) {
  matrix_t A, B, result;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(0, 4, &B);
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Матрица в 0 столбцов и нормальная 
START_TEST(test_s21_mult_matrix_2_3) {
  matrix_t A, B, result;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(3, 0, &B);
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// НЕ СТЫКУЮЩИЕСЯ МАТРИЦЫ

// Матрицы 3х2 и 3х2
START_TEST(test_s21_mult_matrix_3_1) {
  matrix_t A, B, result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Матрицы разного размера 3х3 и 2х2
START_TEST(test_s21_mult_matrix_3_2) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &B);
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// МАТРИЦЫ РАЗМЕРА 1х1

// Сумма матриц A={0.0}, B={0.0}
START_TEST(test_s21_mult_matrix_4_1) {
  matrix_t A, B, result;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq(result.matrix[0][0], 0.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Сумма матриц A={0.0}, B={1.0}
START_TEST(test_s21_mult_matrix_4_2) {
  matrix_t A, B, result;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  B.matrix[0][0] = 1.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq(result.matrix[0][0], 0.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Сумма матриц A={1.0}, B={0.0}
START_TEST(test_s21_mult_matrix_4_3) {
  matrix_t A, B, result;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq(result.matrix[0][0], 0.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Сумма матриц A={1.0}, B={2.0}
START_TEST(test_s21_mult_matrix_4_4) {
  matrix_t A, B, r;
  matrix_t *result = &r;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1.0;
  B.matrix[0][0] = 2.0;
  int status = s21_mult_matrix(&A, &B, result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result->rows, 1);
  ck_assert_int_eq(result->columns, 1);
  ck_assert_double_eq(result->matrix[0][0], 2.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(result);
}
END_TEST

// МАТРИЦЫ БОЛЬШЕГО РАЗМЕРА

// Матрицы с одним заполненным элементом
START_TEST(test_s21_mult_matrix_5_1) {
  matrix_t A, B, result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  A.matrix[2][0] = 4.0;
  B.matrix[0][2] = 5.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_double_eq(result.matrix[2][2], 20.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Матрицы из задания
START_TEST(test_s21_mult_matrix_5_2) {
  matrix_t A, B, result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 4.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 5.0;
  A.matrix[2][0] = 3.0;
  A.matrix[2][1] = 6.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = -1.0;
  B.matrix[0][2] = 1.0;
  B.matrix[1][0] = 2.0;
  B.matrix[1][1] = 3.0;
  B.matrix[1][2] = 4.0;
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_double_eq(result.matrix[0][0], 9.0);
  ck_assert_double_eq(result.matrix[0][1], 11.0);
  ck_assert_double_eq(result.matrix[0][2], 17.0);
  ck_assert_double_eq(result.matrix[1][0], 12.0);
  ck_assert_double_eq(result.matrix[1][1], 13.0);
  ck_assert_double_eq(result.matrix[1][2], 22.0);
  ck_assert_double_eq(result.matrix[2][0], 15.0);
  ck_assert_double_eq(result.matrix[2][1], 15.0);
  ck_assert_double_eq(result.matrix[2][2], 27.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Квадратные матрицы одинакового размера
START_TEST(test_s21_mult_matrix_5_3) {
  matrix_t A, B, result;
  int statusA = s21_create_matrix(3, 3, &A);
  int statusB = s21_create_matrix(3, 3, &B);
  if (statusA == OK) {
    A.matrix[0][0] = 1.0;
    A.matrix[0][1] = 2.0;
    A.matrix[0][2] = 3.0;
    A.matrix[1][0] = 4.0;
    A.matrix[1][1] = 5.0;
    A.matrix[1][2] = 6.0;
    A.matrix[2][0] = 7.0;
    A.matrix[2][1] = 8.0;
    A.matrix[2][2] = 9.0;
  }
  if (statusB == OK) {
    B.matrix[0][0] = 1.0;
    B.matrix[0][1] = 2.0;
    B.matrix[0][2] = 3.0;
    B.matrix[1][0] = 4.0;
    B.matrix[1][1] = 5.0;
    B.matrix[1][2] = 6.0;
    B.matrix[2][0] = 7.0;
    B.matrix[2][1] = 8.0;
    B.matrix[2][2] = 9.0;
  }
  int status = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_double_eq(result.matrix[0][0], 30.0);
  ck_assert_double_eq(result.matrix[0][1], 36.0);
  ck_assert_double_eq(result.matrix[0][2], 42.0);
  ck_assert_double_eq(result.matrix[1][0], 66.0);
  ck_assert_double_eq(result.matrix[1][1], 81.0);
  ck_assert_double_eq(result.matrix[1][2], 96.0);
  ck_assert_double_eq(result.matrix[2][0], 102.0);
  ck_assert_double_eq(result.matrix[2][1], 126.0);
  ck_assert_double_eq(result.matrix[2][2], 150.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

void test_s21_mult_matrix(SRunner *runner) {
  Suite *tests = suite_create("test_s21_mult_matrix");
  // НЕКОРРЕКТНЫЕ МАТРИЦЫ
  tests = add_test(tests, test_s21_mult_matrix_1_1);
  tests = add_test(tests, test_s21_mult_matrix_1_2);
  tests = add_test(tests, test_s21_mult_matrix_1_3);
  // НОРМАЛЬНАЯ МАТРИЦА И НЕКОРРЕКТНАЯ МАТРИЦА
  tests = add_test(tests, test_s21_mult_matrix_2_1);
  tests = add_test(tests, test_s21_mult_matrix_2_2);
  tests = add_test(tests, test_s21_mult_matrix_2_3);
  // НЕ СТЫКУЮЩИЕСЯ МАТРИЦЫ
  tests = add_test(tests, test_s21_mult_matrix_3_1);
  tests = add_test(tests, test_s21_mult_matrix_3_2);
  // МАТРИЦЫ РАЗМЕРА 1х1
  tests = add_test(tests, test_s21_mult_matrix_4_1);
  tests = add_test(tests, test_s21_mult_matrix_4_2);
  tests = add_test(tests, test_s21_mult_matrix_4_3);
  tests = add_test(tests, test_s21_mult_matrix_4_4);
  // МАТРИЦЫ БОЛЬШЕГО РАЗМЕРА
  tests = add_test(tests, test_s21_mult_matrix_5_1);
  tests = add_test(tests, test_s21_mult_matrix_5_2);
  tests = add_test(tests, test_s21_mult_matrix_5_3);
  srunner_add_suite(runner, tests);
}
