#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "rast_matrix.h"

void multTransforms(struct transform* dest, struct transform* mat1, struct transform* mat2) {
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

void transformPoint(struct point* dest, struct transform* trans, struct point* pnt) {
	int i, j;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = 0;
		for (j = 0; j < 4; ++j) {
			dest->matrix[i] += trans->matrix[i][j] * pnt->matrix[j];
		}
	}
}

void getProjectionMat(struct transform* mat, float nearPlane, float farPlane) {
	const float a = -((farPlane) / (farPlane - nearPlane));
	const float b = -((farPlane*nearPlane) / (farPlane - nearPlane));
	*mat = (struct transform){{
		{ 1, 0, 0,  0 },
		{ 0, 1, 0,  0 },
		{ 0, 0, a, -1 },
		{ 0, 0, b,  0 }
	}};
}

void getTranslateMat(struct transform* mat, float objx, float objy, float objz) {
	*mat = (struct transform){{
		{ 1, 0, 0, objx },
		{ 0, 1, 0, objy },
		{ 0, 0, 1, objz },
		{ 0, 0, 0,    1 }
	}};
}
