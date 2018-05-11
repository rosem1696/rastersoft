#include <math.h>
#include <stdlib.h>

#include "rast_matrix.h"


//Matrix Multiplication
void rast_multTrans(struct rast_transform* dest, struct rast_transform* mat1, struct rast_transform* mat2) {
	struct rast_transform tmp;
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			tmp.matrix[i][j] = 0;
			for (k = 0; k < 4; k++) {
				tmp.matrix[i][j] += mat1->matrix[i][k] * mat2->matrix[k][j];
			}
		}
	}
	memcpy(dest, &tmp, sizeof(struct rast_transform));
}

void rast_transVertex(struct rast_vertex* dest, struct rast_vertex* v, struct rast_transform* trans) {
	struct rast_vertex tmp;
	int i, j;
	for (i = 0; i < 4; i++) {
		tmp.matrix[i] = 0;
		for (j = 0; j < 4; ++j) {
			tmp.matrix[i] += v->matrix[j] * trans->matrix[j][i];
		}
	}
	memcpy(dest, &tmp, sizeof(struct rast_vertex));
}


//Vertex Operations
float rast_dotProduct(struct rast_vertex* v1, struct rast_vertex* v2) {
	return (v1->matrix[0] * v2->matrix[0]) + (v1->matrix[1] * v2->matrix[1]) + (v1->matrix[2] * v2->matrix[2]) + (v1->matrix[3] * v2->matrix[3]);
}

void rast_addVertexs(struct rast_vertex* dest, struct rast_vertex* v1, struct rast_vertex* v2) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = v1->matrix[i] + v2->matrix[i];
	}
}

void rast_subVertexs(struct rast_vertex* dest, struct rast_vertex* v1, struct rast_vertex* v2) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = v1->matrix[i] - v2->matrix[i];
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

//Vertex Generation
void rast_oneVertex(struct rast_vertex* dest) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = 1;
	}
}

void rast_zeroVertex(struct rast_vertex* dest) {
	int i;
	for (i = 0; i < 4; i++) {
		dest->matrix[i] = 0;
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
