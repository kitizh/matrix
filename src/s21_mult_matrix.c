#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  matrix_t temp_result;

  if (A && B && result && !s21_check_matrix(A) && !s21_check_matrix(B)) {
    err = s21_create_matrix(A->rows, B->columns, &temp_result);
    if (!err && A->rows == B->columns) {
      err = s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows && !err; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            temp_result.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
      if (!err) {
        s21_copy_matrix(&temp_result, result);
      }
    } else if (!err) {
      err = ERROR;
    }
    s21_remove_matrix(&temp_result);
  } else {
    err = INCORRECT;
  }
  return err;
}
