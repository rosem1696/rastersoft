#ifndef rast_matrix_h
#define rast_matrix_h

#include "rast_defines.h"

struct rast_transform {
	float matrix[4][4];
};

struct rast_vertex {
	float matrix[4];
};

//Matrix Multiplication
DLL_EXPORT void rast_multTrans(struct rast_transform* dest, struct rast_transform* mat1, struct rast_transform* mat2);
DLL_EXPORT void rast_transVertex(struct rast_vertex* dest, struct rast_vertex* v, struct rast_transform* trans);

//Vertex Operations
DLL_EXPORT float rast_dotProduct(struct rast_vertex* v1, struct rast_vertex* v2);
DLL_EXPORT void rast_addVertexs(struct rast_vertex* dest, struct rast_vertex* v1, struct rast_vertex* v2);
DLL_EXPORT void rast_subVertexs(struct rast_vertex* dest, struct rast_vertex* v1, struct rast_vertex* v2);

//Transform Operations
DLL_EXPORT void rast_addTransforms(struct rast_transform* dest, struct rast_transform* mat1, struct rast_transform* v2);
DLL_EXPORT void rast_subTransforms(struct rast_transform* dest, struct rast_transform* mat1, struct rast_transform* mat2);

//Vertex Generation
DLL_EXPORT void rast_oneVertex(struct rast_vertex * dest);
DLL_EXPORT void rast_zeroVertex(struct rast_vertex * dest);

//Transform Generation
DLL_EXPORT void rast_identityTransform(struct rast_transform * dest);
DLL_EXPORT void rast_oneTransform(struct rast_transform * dest);
DLL_EXPORT void rast_zeroTransform(struct rast_transform * dest);

#endif