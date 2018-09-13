/**
* @file rast_object.h
* @author Mitchell Rose
* @date 10 Sep 2018
* @brief Header wavefront obj file defined 3d models
* @copyright Copyright (c) 2018 Mitchell Rose
* @license MIT License
*/

#ifndef template_h
#define template_h

/*** Headers***/
#include <stdbool.h>
#include "rast_arraylist.h"


/*** Structs ***/

struct RastVertex {
	double x;
	double y;
	double z;
	double w;
};

struct RastVertexNormal {
	double x;
	double y;
	double z;
};

struct RastTextureCoord {
	double u;
	double v;
	double w;
};

struct RastFace {
	unsigned int v1; unsigned int vt1; unsigned int vn1;
    unsigned int v2; unsigned int vt2; unsigned int vn2;
    unsigned int v3; unsigned int vt3; unsigned int vn3;
};

struct RastObject {
	struct RastArraylist vertices;
	struct RastArraylist vertexNormals;
	struct RastArraylist textureCoords;
	struct RastArraylist faces;
};

/*** Exported Functions ***/

void rast_object_init(struct RastObject* obj);
void rast_object_add_vertex(struct RastObject* obj, struct RastVertex* v);
void rast_object_add_vertex(struct RastObject* obj, double x, double y, double z);
void rast_object_add_vertex(struct RastObject* obj, double x, double y, double z, double w);
void rast_object_add_normal(struct RastObject* obj, double x, double y, double z);
void rast_object_add_normal(struct RastObject* obj, struct RastVertexNormal vn);
void rast_object_add_txcoord(struct RastObject* obj, double u, double v, double w);
void rast_object_add_face(struct RastObject* obj, struct RastFace* f);
bool rast_object_parse_line(struct RastObject* obj, char* line);
void rast_object_clear(struct RastObject* obj);
#endif //template_h