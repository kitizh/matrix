#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = 0;
  matrix_t temp_result;
  if (A && result && !s21_check_matrix(A)) {
    err = s21_create_matrix(A->columns, A->rows, &temp_result);
    if (!err) {
      err = s21_create_matrix(A->columns, A->rows, result);
      if (!err) {
        for (int i = 0; i < A->columns && !err; i++) {
          for (int j = 0; j < A->rows; j++) {
            temp_result.matrix[i][j] = A->matrix[j][i];
          }
        }
        s21_copy_matrix(&temp_result, result);
        s21_remove_matrix(&temp_result);
      }
    }
  } else {
    err = INCORRECT;
  }
  return err;
}
