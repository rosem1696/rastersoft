/**
* @file rast_object.c
* @author Mitchell Rose
* @date 10 Sep 2018
* @brief Function for loading & interactiong with wavefront obj 
*		 file defined 3d models
* @copyright Copyright (c) 2018 Mitchell Rose
* @license MIT License
*/

/*** Headers ***/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "rast_object.h"
#include "rast_arraylist.h"
#include "rast_matrix.h"

/*** Local Functions ***/

bool parse_face_token(char * face_tok, int* v, int* vt, int* vn, int type) {
	switch (type) {
	case 0:
		return sscanf_s(face_tok, "%d/%d/%d", v, vt, vn) == 3;
	case 1:
		return sscanf_s(face_tok, "%d//%d", v, vn) == 2;
	case 2:
		return sscanf_s(face_tok, "%d/%d", v, vt) == 2;
	case 3:
		return sscanf_s(face_tok, "%d", v) == 1;
	default:
		return false;
	}
}

/*** Exported Functions ***/

void rast_object_init(struct RastObject* obj) {
    rast_arraylist_init(&obj->vertices, sizeof(struct RastVector));
    rast_arraylist_init(&obj->vertexNormals, sizeof(struct RastVector));
    rast_arraylist_init(&obj->textureCoords, sizeof(struct RastTextureCoord));
    rast_arraylist_init(&obj->faces, sizeof(struct RastFace));
}

void rast_object_add_vertex(struct RastObject* obj, struct RastVector* v) {
	rast_arraylist_push(&obj->vertices, v);
}

void rast_object_add_normal(struct RastObject* obj, struct RastVector* vn) {
	rast_arraylist_push(&obj->vertexNormals, vn);
}

void rast_object_add_txcoord(struct RastObject* obj, struct RastTextureCoord* vt) {
	rast_arraylist_push(&obj->textureCoords, vt);
}

void rast_object_add_face(struct RastObject* obj, struct RastFace* f) {
    rast_arraylist_push(&obj->faces, f);
}

bool rast_object_parse_line(struct RastObject* obj, char* line) {
    //Determine line type
	char* save;
	char * tok = strtok_s(line, " ", &save);
	if (strcmp(tok, "v") == 0) { //Vertex
		//parse xyz
		struct RastVector v;
		int i;
		for (i = 0; i < 3; i++) {
			tok = strtok_s(NULL, " ", &save);
			if (!tok)
				return false;
			float f;
			if (sscanf_s(tok, "%f", &f) != 1)
				return false;
			v.matrix[i] = f;
		}
		//check for w
		tok = strtok_s(NULL, " ", &save);
		if (tok) {
			float w;
			if (sscanf_s(tok, "%f", &w) != 1)
				return false;
			v.matrix[3] = w;
		} else {
			v.matrix[3] = 1;
		}
		rast_object_add_vertex(obj, &v);
		return true;
	} else if (strcmp(tok, "vn") == 0) { //Vertex Normal
		//parse xyz
		struct RastVector vn;
		int i;
		for (i = 0; i < 3; i++) {
			tok = strtok_s(NULL, " ", &save);
			if (!tok)
				return false;
			float f;
			if (sscanf_s(tok, "%f", &f) != 1)
				return false;
			vn.matrix[i] = f;
		}
		vn.matrix[3] = 1;
		rast_object_add_normal(obj, &vn);
		return true;
	} else if (strcmp(tok, "vt") == 0) { //Vertex Texture Coordinate
		//parse uv
		struct RastTextureCoord vt;
		int i;
		for (i = 0; i < 2; i++) {
			tok = strtok_s(NULL, " ", &save);
			if (!tok)
				return false;
			float f;
			if (sscanf_s(tok, "%f", &f) != 1)
				return false;
			if (i == 0)
				vt.u = f;
			else
				vt.v = f;
		}
		//check for w
		tok = strtok_s(NULL, " ", &save);
		if (tok) {
			float w;
			if (sscanf_s(tok, "%f", &w) != 1)
				return false;
			vt.w = w;
		} else {
			vt.w = 0;
		}
		rast_object_add_txcoord(obj, &vt);
		return true;
	} else if (strcmp(tok, "f") == 0) { //Face
		int type = -1;
		struct RastFace f;
		//find face component 1 & format type
		tok = strtok_s(NULL, " ", &save);
		for (int i = 0; i < 4 && type < 0; i++) {
			int v1 = 0;
			int vt1 = 0;
			int vn1 = 0;
			if (parse_face_token(tok, &v1, &vt1, &vn1, i)) {
				// Adjust to 0 indexed arrays	
				f.v1 = v1;
				f.vt1 = vt1;
				f.vn1 = vn1;
				type = i;
			}
		}
		//set 2nd and 3rd face compnents to 0
		f.v2 = 0; f.vt2 = 0; f.vn2 = 0;
		f.v3 = 0; f.vt3 = 0; f.vn3 = 0;
		//check that valid type was found
		if (type == -1)
			return false;
		//retrieve 2nd & 3rd faces using format
		tok = strtok_s(NULL, " ", &save);
		if (!parse_face_token(tok, &f.v2, &f.vt2, &f.vn2, type))
			return false;
		tok = strtok_s(NULL, " ", &save);
		if (!parse_face_token(tok, &f.v3, &f.vt3, &f.vn3, type))
			return false;
		//adjust all face elements to 0 index (unset to -1)
		f.v1 -= 1; f.vt1 -= 1; f.vn1 -= 1;
		f.v2 -= 1; f.vt2 -= 1; f.vn2 -= 1;
		f.v3 -= 1; f.vt3 -= 1; f.vn3 -= 1;

		//add face to object
		rast_arraylist_push(&obj->faces, &f);
		return true;
	} else { //Line is not valid, supported, or is comment
		return false;
	}
}

void rast_object_clear(struct RastObject* obj) {
	rast_arraylist_clear(&obj->vertices);
	rast_arraylist_clear(&obj->vertexNormals);
	rast_arraylist_clear(&obj->textureCoords);
	rast_arraylist_clear(&obj->faces);
}

void rast_object_destroy(struct RastObject* obj) {
	rast_arraylist_destroy(&obj->vertices);
	rast_arraylist_destroy(&obj->vertexNormals);
	rast_arraylist_destroy(&obj->textureCoords);
	rast_arraylist_destroy(&obj->faces);
}