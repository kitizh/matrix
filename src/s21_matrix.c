#include "s21_matrix.h"

#include <string.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = 0;
  if (!result) {
    return INCORRECT;
  }
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
      result->rows = 0;
      result->columns = 0;
    }
  } else {
    err = INCORRECT;
    result->matrix = NULL;
    result->rows = 0;
    result->columns = 0;
  }
  return err;
}

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  if (A) {
    A->rows = 0;
    A->columns = 0;
    A = NULL;
  }
}

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

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (!A || !B) {
    return INCORRECT;
  }
  err = s21_create_matrix(A->rows, A->columns, result);
  if (!(s21_check_matrix(A)) && !(s21_check_matrix(B)) && !err) {
    if (A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      err = ERROR;
      s21_remove_matrix(result);
    }
  } else {
    err = INCORRECT;
    s21_remove_matrix(result);
  }
  return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (!A || !B) {
    return INCORRECT;
  }
  matrix_t temp;
  if (!(s21_check_matrix(A)) && !(s21_check_matrix(B))) {
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

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err = 0;
  if (A && !s21_check_matrix(A)) {
    err = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && !err; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    err = INCORRECT;
  }
  return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (!A || !B || !result) {
    return INCORRECT;
  }
  matrix_t temp_result;
  err = s21_create_matrix(A->rows, B->columns, &temp_result);
  if (!s21_check_matrix(A) && !s21_check_matrix(B) && !err) {
    if (A->rows == B->columns) {
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
    } else {
      err = ERROR;
    }
  } else {
    err = INCORRECT;
  }
  s21_remove_matrix(&temp_result);
  return err;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = 0;
  if (!A || !result) {
    return INCORRECT;
  }
  matrix_t temp_result;
  err = s21_create_matrix(A->columns, A->rows, &temp_result);
  if (!s21_check_matrix(A) && !err) {
    err = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->columns && !err; i++) {
      for (int j = 0; j < A->rows; j++) {
        temp_result.matrix[i][j] = A->matrix[j][i];
      }
    }
    if (!err) {
      s21_copy_matrix(&temp_result, result);
      s21_remove_matrix(&temp_result);
    }
  } else {
    err = INCORRECT;
  }
  return err;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!A || !result) {
    return INCORRECT;
  }
  int err = 0;
  double minor = 0;
  matrix_t temp_matrix;
  matrix_t temp_result;

  if (!s21_check_matrix(A)) {
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

int s21_determinant(matrix_t *A, double *result) {
  if (!A || !result) {
    return INCORRECT;
  }
  int err = 0;
  double temp_result = 0;
  matrix_t temp_matrix;
  if (!s21_check_matrix(A)) {
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
            return INCORRECT;
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

int s21_fill_not_crossed(matrix_t *A, matrix_t *result, int i, int j) {
  int err = 0;
  if (!A || !result) {
    return INCORRECT;
  }
  err = s21_create_matrix(A->rows - 1, A->columns - 1, result);
  if (!s21_check_matrix(A) && !err) {
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
  } else {
    err = INCORRECT;
  }
  return err;
}

int s21_simple_det(matrix_t *A, double *result) {
  if (!A || !result) {
    return INCORRECT;
  }
  int err = 0;
  if (!s21_check_matrix(A)) {
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

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!A || !result) {
    return INCORRECT;
  }
  int err = 0;
  int err2 = 0;
  double det = 0;
  matrix_t calc_result;
  matrix_t transpose_result;
  if (!s21_check_matrix(A)) {
    err = s21_determinant(A, &det);
    if (det != 0 && !err && A->columns == A->rows && A->rows > 1) {
      det = 1 / det;
      if (!err && !err2) {
        err = s21_calc_complements(A, &calc_result);
        if (!err) {
          err = s21_transpose(&calc_result, &transpose_result);
          if (!err) {
            s21_mult_number(&transpose_result, det, result);
          }
        }
        s21_remove_matrix(&transpose_result);
        s21_remove_matrix(&calc_result);
      }
    } else if (!err) {
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
  if (!A->matrix || A == NULL || A->rows < 1 || A->columns < 1) {
    err = INCORRECT;
  }
  return err;
}

void s21_free_matrix(matrix_t *A) {
  for (int row = 0; row < A->rows; row++) {
    free(A->matrix[row]);
  }
  free(A->matrix);
  A->matrix = NULL;
}

int s21_crop_matrix(matrix_t *A, int row, int column, matrix_t *result) {
  int status;
  if (!s21_is_correct_matrix(A)) {
    status = INCORRECT;
  } else if (row >= A->rows) {
    status = INCORRECT;
  } else if (column >= A->columns) {
    status = INCORRECT;
  } else if (A->rows != A->columns) {
    status = ERROR;
  } else if (A->rows == 1) {
    status = ERROR;
  } else {
    int size = A->rows - 1;
    status = s21_create_matrix(size, size, result);
    for (int r = 0; r < size; r++) {
      for (int c = 0; c < size; c++) {
        int r_offset = (r < row) ? 0 : 1;
        int c_offset = (c < column) ? 0 : 1;
        result->matrix[r][c] = A->matrix[r + r_offset][c + c_offset];
      }
    }
  }
  return status;
}

int s21_is_correct_matrix(matrix_t *A) {
  int status;
  if (!A) {
    status = FAILURE;
  } else if (!A->matrix) {
    status = FAILURE;
  } else if (A->rows <= 0) {
    status = FAILURE;
  } else if (A->columns <= 0) {
    status = FAILURE;
  } else {
    status = SUCCESS;
  }
  return status;
}
