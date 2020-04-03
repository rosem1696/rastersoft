#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "rast_matrix.h"


//Matrix Multiplication
void rast_multTrans(struct RastTransform* dest, struct RastTransform* mat1, struct RastTransform* mat2) {
	struct RastTransform tmp;
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			tmp.matrix[i][j] = 0;
			for (k = 0; k < 4; k++) {
				tmp.matrix[i][j] += mat1->matrix[i][k] * mat2->matrix[k][j];
			}
		}
	}
	memcpy(dest, &tmp, sizeof(struct RastTransform));
}

void rast_transVector(struct RastVector* dest, struct RastVector* v, struct RastTransform* trans) {
	struct RastVector tmp;
	int i, j;
	for (i = 0; i < 4; i++) {
		tmp.matrix[i] = 0;
		for (j = 0; j < 4; ++j) {
			tmp.matrix[i] += v->matrix[j] * trans->matrix[j][i];
		}
	}
	memcpy(dest, &tmp, sizeof(struct RastVector));
}


//Vector Operations
float rast_dotProduct(struct RastVector* v1, struct RastVector* v2) {
	return (v1->matrix[0] * v2->matrix[0]) + (v1->matrix[1] * v2->matrix[1]) + (v1->matrix[2] * v2->matrix[2]) + (v1->matrix[3] * v2->matrix[3]);
}

void rast_addVectors(struct RastVector* dest, struct RastVector* v1, struct RastVector* v2) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = v1->matrix[i] + v2->matrix[i];
	}
}

void rast_subVectors(struct RastVector* dest, struct RastVector* v1, struct RastVector* v2) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = v1->matrix[i] - v2->matrix[i];
	}
}

//Transform Operations
void rast_addTransforms(struct RastTransform* dest, struct RastTransform* mat1, struct RastTransform* mat2) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			dest->matrix[i][j] = mat1->matrix[i][j] + mat2->matrix[i][j];
		}
	}
}

void rast_subTransforms(struct RastTransform* dest, struct RastTransform* mat1, struct RastTransform* mat2) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			dest->matrix[i][j] = mat1->matrix[i][j] - mat2->matrix[i][j];
		}
	}
}

//Vector Generation
void rast_oneVector(struct RastVector* dest) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = 1;
	}
}

void rast_zeroVector(struct RastVector* dest) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = 0;
	}
}

//Transform Generation
void rast_identityTransform(struct RastTransform* dest) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (i == j) {
				dest->matrix[i][j] = 1;
			} else {
				dest->matrix[i][j] = 0;
			}
		}
	}
}

void rast_oneTransform(struct RastTransform* dest) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			dest->matrix[i][j] = 1;
		}
	}
}

void rast_zeroTransform(struct RastTransform* dest) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			dest->matrix[i][j] = 0;
		}
	}
}
