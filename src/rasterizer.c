#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <SDL.h>

#include "rasterizer.h"

void multTransforms(struct transform* dest, struct transform* mat1, struct transform* mat2) {
	struct transform tmp;
	int row;
	int col;
	for (row = 0; row < 4; row++) {
		for (col = 0; col < 4; col++) {
			tmp.matrix[(4 * row) + col] = mat1->matrix[4 * row] * mat2->matrix[col] +
											mat1->matrix[(4 * row) + 1] * mat2->matrix[col + 4] +
											mat1->matrix[(4 * row) + 2] * mat2->matrix[col + 8] +
											mat1->matrix[(4 * row) + 3] * mat2->matrix[col + 12];
		}
	}
	memcpy(dest, &tmp, sizeof(struct transform));
}

void transformPoint(struct point* dest, struct transform* trans, struct point* pnt) {
	struct point tmp;
	int row;
	for (row = 0; row < 4; row++) {
			tmp.matrix[row] =	trans->matrix[4 * row] * pnt->matrix[0] +
								trans->matrix[(4 * row) + 1] * pnt->matrix[1] +
								trans->matrix[(4 * row) + 2] * pnt->matrix[2] +
								trans->matrix[(4 * row) + 3] * pnt->matrix[3];
	}
	memcpy(dest, &tmp, sizeof(struct point));
}

void getProjectionMat(struct transform* mat, float nearPlane, float farPlane) {
	int i;
	for (i = 0; i < 16; i++) {
		mat->matrix[i] = 0;
	}
	mat->matrix[0] = 1;
	mat->matrix[5] = 1;
	mat->matrix[10] = -((farPlane) / (farPlane - nearPlane));
	mat->matrix[11] = -1;
	mat->matrix[14] = -((farPlane*nearPlane) / (farPlane - nearPlane));
}


void getTranslateMat(struct transform* mat, float objx, float objy, float objz) {
	int i;
	for (i = 0; i < 16; i++) {
		mat->matrix[i] = 0;
	}
	mat->matrix[0] = 1;
	mat->matrix[3] = objx;
	mat->matrix[5] = 1;
	mat->matrix[7] = objy;
	mat->matrix[10] = 1;
	mat->matrix[11] = objz;
	mat->matrix[15] = 1;
}

void printMatrix(struct transform* mat) {
	int i;
	for (i = 0; i < 4; i++) {
		printf("%f %f %f %f\n", mat->matrix[0 + 4 * i],
			mat->matrix[1 + 4 * i],
			mat->matrix[2 + 4 * i],
			mat->matrix[3 + 4 * i]);
	}
	printf("\n");
}

void printPoints(struct point* pts, int count) {
	int i;
	for (i = 0; i < count; i++) {
		printf("%f %f %f %f\n", pts[i].matrix[0],
			pts[i].matrix[1],
			pts[i].matrix[2],
			pts[i].matrix[3]);
	}
	printf("\n");
}
