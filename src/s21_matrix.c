#include "s21_matrix.h"

int s21_fill_not_crossed(matrix_t *A, matrix_t *result, int i, int j) {
  int err = 0;
  if (A && result && !s21_check_matrix(A)) {
    if (i < A->rows && j < A->columns && A->rows == A->columns && A->rows > 1) {
      err = s21_create_matrix(A->rows - 1, A->columns - 1, result);
      if (!err) {
        for (int n = 0; n < i; n++) {
          for (int m = 0; m < j; m++) {
            result->matrix[n][m] = A->matrix[n][m];
          }
          for (int m = j + 1; m < A->columns; m++) {
            result->matrix[n][m - 1] = A->matrix[n][m];
          }
        }
        for (int n = i + 1; n < A->rows; n++) {
          for (int m = 0; m < j; m++) {
            result->matrix[n - 1][m] = A->matrix[n][m];
          }
          for (int m = j + 1; m < A->columns; m++) {
            result->matrix[n - 1][m - 1] = A->matrix[n][m];
          }
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

int s21_simple_det(matrix_t *A, double *result) {
  int err = 0;
  if (A && result && !s21_check_matrix(A)) {
    if (A->rows == A->columns && A->columns == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      err = ERROR;
    }
  } else {
    err = INCORRECT;
  }
  return err;
}

int s21_copy_matrix(matrix_t *A, matrix_t *B) {
  int err = 0;
  if (!s21_check_matrix(A) && !s21_check_matrix(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          B->matrix[i][j] = A->matrix[i][j];
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

int s21_check_matrix(matrix_t *A) {
  int err = 0;
  if (!A || !A->matrix || A->rows < 1 || A->columns < 1) {
    err = INCORRECT;
  }
  return err;
}
