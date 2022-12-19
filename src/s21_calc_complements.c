#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = 0;
  double minor = 0;
  matrix_t temp_matrix;
  matrix_t temp_result;
  if (A && result && !s21_check_matrix(A)) {
    if (A->rows == A->columns && A->rows > 1) {
      err = s21_create_matrix(A->rows, A->columns, result);
      if (!err) {
        err = s21_create_matrix(A->rows, A->columns, &temp_result);
        if (!err) {
          for (int i = 0; i < A->rows && !err; i++) {
            for (int j = 0; j < A->columns && !err; j++) {
              s21_fill_not_crossed(A, &temp_matrix, i, j);
              err = s21_determinant(&temp_matrix, &minor);
              s21_remove_matrix(&temp_matrix);
              temp_result.matrix[i][j] = minor * pow(-1, i + j);
            }
          }
          s21_copy_matrix(&temp_result, result);
          s21_remove_matrix(&temp_result);
        }
      }
    } else {
      err = ERROR;
    }
  } else {
    err = INCORRECT;
  }
  return err;
}
