#include "test.h"

// НЕКОРРЕКТНЫЕ РЕЗУЛЬТАТЫ

// Не инициализированная матрица
START_TEST(test_s21_crop_matrix_1_1) {
  matrix_t *A = NULL;
  matrix_t result;
  int status = s21_crop_matrix(A, 1, 1, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(A);
}
END_TEST

// Матрица 1 на 1
START_TEST(test_s21_crop_matrix_1_2) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  int status = s21_crop_matrix(&A, 0, 0, &result);
  ck_assert_int_eq(status, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// Прямоугольная матрица
START_TEST(test_s21_crop_matrix_1_3) {
  matrix_t A, result;
  s21_create_matrix(3, 4, &A);
  int status = s21_crop_matrix(&A, 0, 0, &result);
  ck_assert_int_eq(status, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// Вырезаемая колонка больше размера
START_TEST(test_s21_crop_matrix_1_4) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  int status = s21_crop_matrix(&A, 2, 0, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// Вырезаемая строка больше размера
START_TEST(test_s21_crop_matrix_1_5) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  int status = s21_crop_matrix(&A, 0, 2, &result);
  ck_assert_int_eq(status, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

// НОРМАЛЬНЫЕ МАТРИЦЫ

// Матрица 2x2
START_TEST(test_s21_crop_matrix_2_1) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  int status = s21_crop_matrix(&A, 0, 0, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq(result.matrix[0][0], 0.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Квадратная матрица 3x3
START_TEST(test_s21_crop_matrix_2_2) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);
  int status = s21_crop_matrix(&A, 1, 1, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq(result.matrix[0][0], 0.0);
  ck_assert_double_eq(result.matrix[1][1], 0.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST


void test_s21_matrix(SRunner *runner) {
  Suite *tests = suite_create("test_s21_matrix");
  // НЕКОРРЕКТНЫЕ РЕЗУЛЬТАТЫ
  tests = add_test(tests, test_s21_crop_matrix_1_1);
  tests = add_test(tests, test_s21_crop_matrix_1_2);
  tests = add_test(tests, test_s21_crop_matrix_1_3);
  tests = add_test(tests, test_s21_crop_matrix_1_4);
  tests = add_test(tests, test_s21_crop_matrix_1_5);
  // НОРМАЛЬНЫЕ МАТРИЦЫ
  tests = add_test(tests, test_s21_crop_matrix_2_1);
  tests = add_test(tests, test_s21_crop_matrix_2_2);
  srunner_add_suite(runner, tests);
}