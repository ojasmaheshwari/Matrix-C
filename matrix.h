#pragma once
#include <stdint.h>

typedef uint64_t u64;

typedef struct {
  u64 r; // rows
  u64 c; // columns
} order;

typedef struct {
  int *arr;
  order order;
} matrix;

matrix createZeroMatrix(order *);

matrix createIdentityMatrix(order *);

int size(matrix *);

void scalarMult(matrix *, int);

matrix matrixMult(matrix *, matrix *);

void displayMatrix(matrix *);

matrix CustomMatrix(int *, order *);
