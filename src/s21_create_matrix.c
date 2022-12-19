#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = 0;
  if (!result) {
    err = INCORRECT;
  } else {
    result->rows = rows;
    result->columns = columns;
    if (result->rows > 0 && result->columns > 0) {
      result->matrix = calloc(result->rows, sizeof(double *));
      if (result->matrix != NULL) {
        for (int i = 0; i < result->rows; i++) {
          result->matrix[i] = calloc(result->columns, sizeof(double));
          if (result->matrix[i] == NULL) {
            err = INCORRECT;
            break;
          }
        }
      } else {
        err = INCORRECT;
      }
    } else {
      err = INCORRECT;
    }
    if (err) {
      result->matrix = NULL;
      result->rows = 0;
      result->columns = 0;
    }
  }
  return err;
}
