#include "matrix.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
	matrix m1 = IdentityMatrix(&(order){3,3});
	displayMatrix(&m1);
	free(m1.arr);
	return 0;
}
