#ifndef rast_matrix_h
#define rast_matrix_h

#include <stdint.h>
#include <stdbool.h>

struct transform {
	float matrix[16];
};

struct point {
	float matrix[4];
};

struct face {
	int p1;
	int p2;
	int p3;
};

struct object {
	struct point* points;
	struct face* faces;
};


void multTransforms(struct transform* dest, struct transform* mat1, struct transform* mat2);
void transformPoint(struct point* dest, struct transform* trans, struct point* pnt);
void getProjectionMat(struct transform* mat, float nearPlane, float farPlane);
void getTranslateMat(struct transform* mat, float objx, float objy, float objz);
void printMatrix(struct transform* mat);
void printPoints(struct point* pts, int count);

#endif
