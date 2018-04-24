#ifndef rast_matrix_h
#define rast_matrix_h

#include "rast_defines.h"


struct rast_transform {
	float matrix[4][4];
};

struct rast_vector {
	float matrix[4];
};


//Matrix Multiplication
DLL_EXPORT void rast_multTrans(struct rast_transform* dest, struct rast_transform* mat1, struct rast_transform* mat2);
DLL_EXPORT void rast_transVector(struct rast_vector* dest, struct rast_transform* trans, struct rast_vector* vec);

//Vertex Operations
DLL_EXPORT float rast_dotProduct(struct rast_vector* vec1, struct rast_vector* vec2);
DLL_EXPORT void rast_addVectors(struct rast_vector* dest, struct rast_vector* vec1, struct rast_vector* vec2);
DLL_EXPORT void rast_subVectors(struct rast_vector* dest, struct rast_vector* vec1, struct rast_vector* vec2);

//Transform Operations
DLL_EXPORT void rast_addTransforms(struct rast_transform* dest, struct rast_transform* mat1, struct rast_transform* vec2);
DLL_EXPORT void rast_subTransforms(struct rast_transform* dest, struct rast_transform* mat1, struct rast_transform* mat2);

//Vector Generation
DLL_EXPORT void rast_oneVector(struct rast_vector * dest);
DLL_EXPORT void rast_zeroVector(struct rast_vector * dest);

//Transform Generation
DLL_EXPORT void rast_identityTransform(struct rast_transform * dest);
DLL_EXPORT void rast_oneTransform(struct rast_transform * dest);
DLL_EXPORT void rast_zeroTransform(struct rast_transform * dest);

#endif