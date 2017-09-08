#ifndef rast_matrix_h
#define rast_matrix_h

#include "rast_defines.h"


struct transform {
	float matrix[4][4];
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


DLL_EXPORT void multTransforms(struct transform* dest, struct transform* mat1, struct transform* mat2);
DLL_EXPORT void transformPoint(struct point* dest, struct transform* trans, struct point* pnt);
DLL_EXPORT void getProjectionMat(struct transform* mat, float nearPlane, float farPlane);
DLL_EXPORT void getTranslateMat(struct transform* mat, float objx, float objy, float objz);
DLL_EXPORT void printMatrix(struct transform* mat);
DLL_EXPORT void printPoints(struct point* pts, int count);

#endif
