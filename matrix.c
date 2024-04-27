#include "matrix.h"
#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

matrix ZeroMatrix(order *o) {
	u64 *r = &(o->r);
	u64 *c = &(o->c);
	int* arr = malloc(*r * *c * sizeof(int));
	if (arr == NULL) {
		printf("Could not allocate memory for matrix\n");
	}
	for (int i=0; i<(*r * *c); i++) {
		arr[i] = 0;
	}
	matrix m;
	m.arr = arr;

	m.order = *o;
	return m;
}

matrix IdentityMatrix(order *o) {
	u64 *r = &(o->r);
	u64 *c = &(o->c);
	int* arr = malloc(*r * *c * sizeof(int));
	if (arr == NULL) {
		printf("Could not allocate memory for matrix\n");
	}
	for (int i=0; i < *r; i++) {
		for (int j=0; j < *c; j++) {
			if ( i == j  ) {
				arr[i * *c + j] = 1;
			}
		}
	}
	matrix m;
	m.arr = arr;

	m.order = *o;
	return m;
}

void displayMatrix(matrix* m) {
	u64 *r = &(m->order.r);
	u64 *c = &(m->order.c);

	for (int i=0; i < *r; i++) {
		for (int j=0; j < *c; j++) {
			printf("%d ", m->arr[i * *c + j]);
		}
		printf("\n");
	}
}

int size(matrix *m) {
	return (sizeof(int*) + m->order.r * m->order.c * sizeof(int));
}

void scalarMult(matrix *m, int scalar) {
	u64 *r = &(m->order.r);
	u64 *c = &(m->order.c);

	for (int i=0; i < (*r * *c); i++) {
		m->arr[i] *= scalar;
	}
}

matrix matrixMult(matrix * m1, matrix * m2) {
	u64 *r1 = &(m1->order.r);
	u64 *c1 = &(m1->order.c);
	u64 *r2 = &(m2->order.r);
	u64 *c2 = &(m2->order.c);
	if (*c1 != *r2)
		printf("Matrices cannot be multiplied\n");
	order o3 = {*r1, *c2};
	order *op = &o3;
	int* arr = malloc(o3.r * o3.c * sizeof(int));
	if (arr == NULL)
		printf("Could not allocate memory for matrix\n");
	for (int i=0; i < *r1; i++) {
		for (int j=0; j < *c2; j++) {
			arr[i * o3.c + j] = 0;	
			for (int k=0; k < *c1; k++) {
			arr[i * o3.c + j]  += m1->arr[i * *c1 + k] * m2->arr[k * *c2 + j];
			}
		}
	}
	matrix m;
	m.arr = arr;
	m.order = o3;
	return m;
}

matrix CustomMatrix(int* arr, order *o) {
	u64 *r = &(o->r);
	u64 *c = &(o->c);
	int* marr = malloc(*r * *c * sizeof(int));
	if (marr == NULL) {
		printf("Could not allocate memory for matrix\n");
	}
	for (int i=0; i<(*r * *c); i++) {
		marr[i] = arr[i];
	}
	matrix m;
	m.arr = marr;

	m.order = *o;
	return m;
}
int main(int argc, char* argv[]) {

	matrix m1 = IdentityMatrix(&(order){3, 3});
	displayMatrix(&m1);
	
	free(m1.arr);
	return 0;
}
