#include "test.h"

// НЕКОРРЕКТНЫЕ МАТРИЦЫ

// Удаление пустой структуры матрицы 
START_TEST(test_s21_remove_matrix_1_1) {
  matrix_t *A = NULL;
  s21_remove_matrix(A);
  ck_assert_ptr_null(A);
}
END_TEST

// Удаление пустой матрицы 
START_TEST(test_s21_remove_matrix_1_2) {
  matrix_t A;
  matrix_t *ptrA = &A;
  s21_create_matrix(3, 4, ptrA);
  s21_remove_matrix(ptrA); // Устанавливает матрицу в NULL
  s21_remove_matrix(ptrA);
  ck_assert_int_eq(ptrA->rows, 0);
  ck_assert_int_eq(ptrA->columns, 0);
  ck_assert_ptr_null(ptrA->matrix);
}
END_TEST

// НОРМАЛЬНЫЕ МАТРИЦЫ

// Удаление созданной матрицы 
START_TEST(test_s21_remove_matrix_2_1) {
  matrix_t A;
  s21_create_matrix(3, 4, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

void test_s21_remove_matrix(SRunner *runner) {
  Suite *tests = suite_create("test_s21_remove_matrix");
  // НЕКОРРЕКТНЫЕ МАТРИЦЫ
  tests = add_test(tests, test_s21_remove_matrix_1_1);
  tests = add_test(tests, test_s21_remove_matrix_1_2);
  // НОРМАЛЬНЫЕ МАТРИЦЫ
  tests = add_test(tests, test_s21_remove_matrix_2_1);
  srunner_add_suite(runner, tests);
}
