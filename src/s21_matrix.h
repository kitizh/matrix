#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT 1
#define ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
int s21_check_matrix(matrix_t *A);
int s21_minor(matrix_t *A, double *result);
int s21_copy_matrix(matrix_t *A, matrix_t *B);
int s21_simple_det(matrix_t *A, double *result);
int s21_fill_not_crossed(matrix_t *A, matrix_t *result, int i, int j);
int s21_crop_matrix(matrix_t *A, int row, int column, matrix_t *result);
void s21_free_matrix(matrix_t *A);
int s21_is_correct_matrix(matrix_t *A);

#endif  // SRC_S21_MATRIX_H_
