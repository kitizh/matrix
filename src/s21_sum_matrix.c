#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (A && B && !(s21_check_matrix(A)) && !(s21_check_matrix(B))) {
    err = s21_create_matrix(A->rows, A->columns, result);
    if (!err && A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else if (err) {
      err = INCORRECT;
    } else {
      err = ERROR;
    }
    if (err) {
      s21_remove_matrix(result);
    }
  } else {
    err = INCORRECT;
  }
  return err;
}
