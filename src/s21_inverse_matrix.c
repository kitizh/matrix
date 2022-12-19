#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = 0;
  double det = 0;
  matrix_t calc_result;
  matrix_t transpose_result;
  if (A && result && !s21_check_matrix(A)) {
    err = s21_determinant(A, &det);
    if (det != 0 && !err && A->columns == A->rows && A->rows > 1) {
      det = 1 / det;
      if (!err) {
        err = s21_calc_complements(A, &calc_result);
        if (!err) {
          err = s21_transpose(&calc_result, &transpose_result);
          s21_remove_matrix(&calc_result);
          if (!err) {
            s21_mult_number(&transpose_result, det, result);
            s21_remove_matrix(&transpose_result);
          }
        }
      }
    } else if (!err) {
      err = ERROR;
    }
  } else {
    err = INCORRECT;
  }
  return err;
}
