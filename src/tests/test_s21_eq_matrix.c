#include "test.h"

// НЕКОРРЕКТНЫЕ МАТРИЦЫ

// Не инициализированые матрицы
START_TEST(test_s21_eq_matrix_1_1) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  int status = s21_eq_matrix(A, B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(A);
  s21_remove_matrix(B);
}
END_TEST

// Матрицы в 0 строк 
START_TEST(test_s21_eq_matrix_1_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(0, 4, &A);
  s21_create_matrix(0, 4, &B);
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Матрицы 0 столбцов 
START_TEST(test_s21_eq_matrix_1_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 0, &A);
  s21_create_matrix(3, 0, &B);
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Матрицы с NULL в качестве матрицы
START_TEST(test_s21_eq_matrix_1_4) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_free_matrix(&A); // Устанавливает матрицу в NULL
  s21_free_matrix(&B); // Устанавливает матрицу в NULL
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// НЕКОРРЕКТНАЯ МАТРИЦА И НОРМАЛЬНАЯ МАТРИЦА

// Не инициализированая матрица и нормальная
START_TEST(test_s21_eq_matrix_2_1) {
  matrix_t A;
  matrix_t *B = NULL;
  s21_create_matrix(1, 1, &A);
  int status = s21_eq_matrix(&A, B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(B);
}
END_TEST

// Матрица в 0 строк и нормальная 
START_TEST(test_s21_eq_matrix_2_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(0, 4, &B);
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Матрица в 0 столбцов и нормальная 
START_TEST(test_s21_eq_matrix_2_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(3, 0, &B);
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// НОРМАЛЬНЫЕ МАТРИЦЫ

// Одинаковые матрицы 1 на 1
START_TEST(test_s21_eq_matrix_3_1) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Разные матрицы A={0.0}, B={1.0}
START_TEST(test_s21_eq_matrix_3_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  B.matrix[0][0] = 1.0;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Разные матрицы A={1.0}, B={0.0}
START_TEST(test_s21_eq_matrix_3_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1.0;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Матрицы разного размера 3х3 и 3х2
START_TEST(test_s21_eq_matrix_3_4) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 2, &B);
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Матрицы разного размера 3х2 и 3х3
START_TEST(test_s21_eq_matrix_3_5) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 3, &B);
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Матрицы одинакового размера, с отличием в одном элементе
START_TEST(test_s21_eq_matrix_3_6) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  A.matrix[2][0] = 4.0;
  B.matrix[2][0] = 5.0;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// ТОЧНОСТЬ СРАВНЕНИЯ

// Одинаковые матрицы одного размера
START_TEST(test_s21_eq_matrix_4_1) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;
  B.matrix[2][0] = 5.0;
  B.matrix[2][1] = 6.0;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Похожие матрицы (отличия меньше 0.00000001)
START_TEST(test_s21_eq_matrix_4_2) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  B.matrix[0][0] = 1.00000001;
  B.matrix[0][1] = 2.00000005;
  B.matrix[1][0] = 3.00000009;
  B.matrix[1][1] = 3.99999991;
  B.matrix[2][0] = 4.99999995;
  B.matrix[2][1] = 5.99999999;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Похожие матрицы (отличия равны 0.00000001)
START_TEST(test_s21_eq_matrix_4_3) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  B.matrix[0][0] = 1.0000001;
  B.matrix[0][1] = 2.0000001;
  B.matrix[1][0] = 3.0000001;
  B.matrix[1][1] = 3.9999999;
  B.matrix[2][0] = 4.9999999;
  B.matrix[2][1] = 5.9999999;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Похожие матрицы (отличия больше 0.00000001)
START_TEST(test_s21_eq_matrix_4_4) {
  matrix_t A;
  matrix_t B;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  B.matrix[0][0] = 1.0000001;
  B.matrix[0][1] = 2.0000005;
  B.matrix[1][0] = 3.0000009;
  B.matrix[1][1] = 3.9999991;
  B.matrix[2][0] = 4.9999995;
  B.matrix[2][1] = 5.9999999;
  int status = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

void test_s21_eq_matrix(SRunner *runner) {
  Suite *tests = suite_create("test_s21_eq_matrix");
  // НЕКОРРЕКТНЫЕ МАТРИЦЫ
  tests = add_test(tests, test_s21_eq_matrix_1_1);
  tests = add_test(tests, test_s21_eq_matrix_1_2);
  tests = add_test(tests, test_s21_eq_matrix_1_3);
  tests = add_test(tests, test_s21_eq_matrix_1_4);
  // НОРМАЛЬНАЯ МАТРИЦА И НЕКОРРЕКТНАЯ МАТРИЦА
  tests = add_test(tests, test_s21_eq_matrix_2_1);
  tests = add_test(tests, test_s21_eq_matrix_2_2);
  tests = add_test(tests, test_s21_eq_matrix_2_3);
  // НОРМАЛЬНЫЕ МАТРИЦЫ
  tests = add_test(tests, test_s21_eq_matrix_3_1);
  tests = add_test(tests, test_s21_eq_matrix_3_2);
  tests = add_test(tests, test_s21_eq_matrix_3_3);
  tests = add_test(tests, test_s21_eq_matrix_3_4);
  tests = add_test(tests, test_s21_eq_matrix_3_5);
  tests = add_test(tests, test_s21_eq_matrix_3_6);
  // ТОЧНОСТЬ СРАВНЕНИЯ
  tests = add_test(tests, test_s21_eq_matrix_4_1);
  tests = add_test(tests, test_s21_eq_matrix_4_2);
  tests = add_test(tests, test_s21_eq_matrix_4_3);
  tests = add_test(tests, test_s21_eq_matrix_4_4);
  srunner_add_suite(runner, tests);
}
