#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int err = 0;
  double temp_result = 0;
  matrix_t temp_matrix;
  if (A && result && !s21_check_matrix(A)) {
    if (A->rows == A->columns) {
      if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else if (A->rows == 2) {
        err = s21_simple_det(A, result);
      } else {
        *result = 0;
        for (int j = 0; j < A->columns && !err; j++) {
          s21_fill_not_crossed(A, &temp_matrix, 0, j);
          err = s21_determinant(&temp_matrix, &temp_result);
          s21_remove_matrix(&temp_matrix);
          if (err) {
            break;
          }
          if (j % 2 == 1) {
            temp_result = temp_result * -1;
          }
          *result += A->matrix[0][j] * temp_result;
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
