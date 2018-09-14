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
#include "rast_matrix.h"


/*** Structs ***/

struct RastTextureCoord {
	double u;
	double v;
	double w;
};

struct RastFace {
	int v1; int vt1; int vn1;
    int v2; int vt2; int vn2;
    int v3; int vt3; int vn3;
};

struct RastObject {
	struct RastArraylist vertices;
	struct RastArraylist vertexNormals;
	struct RastArraylist textureCoords;
	struct RastArraylist faces;
};

/*** Exported Functions ***/

void rast_object_init(struct RastObject* obj);

void rast_object_add_vertex(struct RastObject* obj, struct RastVector* v);

void rast_object_add_normal(struct RastObject* obj, struct RastVector* vn);

void rast_object_add_txcoord(struct RastObject* obj, struct RastTextureCoord* vt);

void rast_object_add_face(struct RastObject* obj, struct RastFace* f);

bool rast_object_parse_line(struct RastObject* obj, char* line);

void rast_object_clear(struct RastObject* obj);

void rast_object_destroy(struct RastObject* obj);

#endif //template_h