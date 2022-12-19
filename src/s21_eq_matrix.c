#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = 1;
  if (A && B && A->matrix && B->matrix && A->rows == B->rows &&
      A->columns == B->columns) {
    for (int i = 0; i < A->rows && result; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          result = 0;
          break;
        }
      }
    }
  } else {
    result = 0;
  }
  return result;
}
