#ifndef rast_matrix_h
#define rast_matrix_h

#include "rast_defines.h"

struct RastTransform {
	float matrix[4][4];
};

struct RastVector {
	float matrix[4];
};

//Matrix Multiplication
DLL_EXPORT void rast_multTrans(struct RastTransform* dest, struct RastTransform* mat1, struct RastTransform* mat2);
DLL_EXPORT void rast_transVector(struct RastVector* dest, struct RastVector* v, struct RastTransform* trans);

//Vertex Operations
DLL_EXPORT float rast_dotProduct(struct RastVector* v1, struct RastVector* v2);
DLL_EXPORT void rast_addVectors(struct RastVector* dest, struct RastVector* v1, struct RastVector* v2);
DLL_EXPORT void rast_subVectors(struct RastVector* dest, struct RastVector* v1, struct RastVector* v2);

//Transform Operations
DLL_EXPORT void rast_addTransforms(struct RastTransform* dest, struct RastTransform* mat1, struct RastTransform* v2);
DLL_EXPORT void rast_subTransforms(struct RastTransform* dest, struct RastTransform* mat1, struct RastTransform* mat2);

//Vertex Generation
DLL_EXPORT void rast_oneVector(struct RastVector * dest);
DLL_EXPORT void rast_zeroVector(struct RastVector * dest);

//Transform Generation
DLL_EXPORT void rast_identityTransform(struct RastTransform * dest);
DLL_EXPORT void rast_oneTransform(struct RastTransform * dest);
DLL_EXPORT void rast_zeroTransform(struct RastTransform * dest);

#endif