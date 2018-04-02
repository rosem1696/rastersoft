#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "rast_matrix.h"


//Matrix Multiplication
void rast_multTrans(struct rast_transform* dest, struct rast_transform* mat1, struct rast_transform* mat2) {
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			dest->matrix[i][j] = 0;
			for (k = 0; k < 4; k++) {
				dest->matrix[i][j] += mat1->matrix[i][k] * mat2->matrix[k][j];
			}
		}
	}
}

void rast_transVector(struct rast_vector* dest, struct rast_transform* trans, struct rast_vector* vec) {
	int i, j;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = 0;
		for (j = 0; j < 4; ++j) {
			dest->matrix[i] += trans->matrix[i][j] * vec->matrix[j];
		}
	}
}


//Vector Operations
float rast_dotProduct(struct rast_vector* vec1, struct rast_vector* vec2) {
	return (vec1->matrix[0] * vec2->matrix[0]) + (vec1->matrix[1] * vec2->matrix[1]) + (vec1->matrix[2] * vec2->matrix[2]) + (vec1->matrix[3] * vec2->matrix[3]);
}

void rast_addVectors(struct rast_vector* dest, struct rast_vector* vec1, struct rast_vector* vec2) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = vec1->matrix[i] + vec2->matrix[i];
	}
}

void rast_subVectors(struct rast_vector* dest, struct rast_vector* vec1, struct rast_vector* vec2) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = vec1->matrix[i] - vec2->matrix[i];
	}
}

//Transform Operations
void rast_addTransforms(struct rast_transform* dest, struct rast_transform* mat1, struct rast_transform* mat2) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			dest->matrix[i][j] = mat1->matrix[i][j] + mat2->matrix[i][j];
		}
	}
}

void rast_subTransforms(struct rast_transform* dest, struct rast_transform* mat1, struct rast_transform* mat2) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			dest->matrix[i][j] = mat1->matrix[i][j] - mat2->matrix[i][j];
		}
	}
}

//Vector Generation
void rast_oneVector(struct rast_vector* dest) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = 1;
	}
}

void rast_zeroVector(struct rast_vector* dest) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = 1;
	}
}

//Transform Generation
void rast_identityTransform(struct rast_transform* dest) {
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

void rast_oneTransform(struct rast_transform* dest) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			dest->matrix[i][j] = 1;
		}
	}
}

void rast_zeroTransform(struct rast_transform* dest) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			dest->matrix[i][j] = 0;
		}
	}
}
