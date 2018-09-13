/**
* @file rast_object.c
* @author Mitchell Rose
* @date 10 Sep 2018
* @brief Functions for loading & interactiong with wavefront obj 
*        file defined 3d models
* @copyright Copyright (c) 2018 Mitchell Rose
* @license MIT License
*/

/*** Headers ***/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "rast_object.h"
#include "rast_arraylist.h"

/*** Local Functions ***/

/*** Exported Functions ***/

void rast_object_init(struct RastObject* obj) {
    rast_arraylist_init(&obj->vertices, sizeof(struct RastVertex));
    rast_arraylist_init(&obj->vertexNormals, sizeof(struct RastVertexNormal));
    rast_arraylist_init(&obj->textureCoords, sizeof(struct RastTextureCoord));
    rast_arraylist_init(&obj->faces, sizeof(struct RastFace));
}

void rast_object_add_vertex(struct RastObject* obj, struct RastVertex* v) {
    rast_arraylist_push(&obj->vertices, v);
}

void rast_object_add_vertex(struct RastObject* obj, double x, double y, double z) {
    struct RastVertex v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = 1;
    rast_arraylist_push(&obj->vertices, &v);
}

void rast_object_add_vertex(struct RastObject* obj, double x, double y, double z, double w) {
    struct RastVertex v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    rast_arraylist_push(&obj->vertices, &v);
}

void rast_object_add_normal(struct RastObject* obj, double x, double y, double z) {
    struct RastVertexNormal vn;
    vn.x = x;
    vn.y = y;
    vn.z = z;
}

void rast_object_add_normal(struct RastObject* obj, struct RastVertexNormal vn) {

}

void rast_object_add_txcoord(struct RastObject* obj, double u, double v, double w) {

}

void rast_object_add_face(struct RastObject* obj, struct RastFace* f) {
    rast_arraylist_push(&obj->faces, f);
}

bool rast_object_parse_line(struct RastObject* obj, char* line) {
    char * tok = strtok(line, " ");
    
}