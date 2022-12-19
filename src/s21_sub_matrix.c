#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  matrix_t temp;
  if (A && B && !(s21_check_matrix(A)) && !(s21_check_matrix(B))) {
    if (A->rows == B->rows && A->columns == B->columns) {
      err = s21_mult_number(B, -1, &temp);
      if (!err) {
        err = s21_sum_matrix(A, &temp, result);
        s21_remove_matrix(&temp);
      }
    } else {
      err = ERROR;
    }
  } else {
    err = INCORRECT;
  }
  return err;
}
