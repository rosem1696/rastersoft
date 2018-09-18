#define TEST_NO_MAIN

#include "acutest.h"
#include "rastersoft.h"
#include "rast_matrix.h"
#include "rast_arraylist.h"
#include "rast_object.h"

#define COMMENT_LINE "# This is a comment"
#define JUNK_INPUT "asdljksdvoisdmwe asdlslvjpov asdfn120wef08"

#define VERTEX_1 "v 1.2 35.6 17.254"
#define VERTEX_1_RESULT { 1.2, 35.6, 17.254, 1}
#define VERTEX_2 "v 5.6 4 0.0 1423.5"
#define VERTEX_2_RESULT { 5.6, 4, 0, 1423.5 }
#define VERTEX_BAD "v 10 2.1"

#define NORMAL "vn 1.5 6 7.2"
#define NORMAL_RESULT { 1.5, 6.0, 7.2, 1 }
#define NORMAL_BAD "vn 1.2 bad"

#define TEXTURE_1 "vt 0.5 0.75"
#define TEXTURE_1_RESULT { 0.5, 0.75, 0}
#define TEXTURE_2 "vt 1 0 0.5"
#define TEXTURE_2_RESULT { 1, 0, 0.5}
#define TEXTURE_BAD "vt asd"

#define FACE_1 "f 5/2/3 1/2/5 8/10/12"
#define FACE_1_RESULT { 4, 1, 2, 0, 1, 4, 7, 9, 11}
#define FACE_2 "f 1//3 5//7 4//8"
#define FACE_2_RESULT { 0, -1, 2, 4, -1, 6, 3, -1, 7}
#define FACE_3 "f 4/5 8/9 12/5"
#define FACE_3_RESULT { 3, 4, -1, 7, 8, -1, 11, 4, -1}
#define FACE_4 "f 1 2 3"
#define FACE_4_RESULT { 0, -1, -1, 1, -1, -1, 2, -1, -1}

void test_obj_parse_vertex(void) {
	//init
	int i;
	bool result;
	struct RastVector* v;
	struct RastObject obj;
	rast_object_init(&obj);
	
	//bad vertex input
	result = rast_object_parse_line(&obj, VERTEX_BAD);
	TEST_CHECK(!result);
	TEST_CHECK(obj.vertices.length == 0);
	
	//vertex without w component
	float testVertex1[4] = VERTEX_1_RESULT;
	result = rast_object_parse_line(&obj, VERTEX_1);
	TEST_CHECK(result);
	TEST_CHECK(obj.vertices.length == 1);
	v = rast_arraylist_get(&obj.vertices, 0);
	for (i = 0; i < 4; i++) {
		TEST_CHECK(v->matrix[i] == testVertex1[i]);
	}
	
	//vertex with w component 
	float testVertex2[4] = VERTEX_2_RESULT;
	result = rast_object_parse_line(&obj, VERTEX_2);
	TEST_CHECK(result);
	TEST_CHECK(obj.vertices.length == 2);
	v = rast_arraylist_get(&obj.vertices, 1);
	for (i = 0; i < 4; i++) {
		TEST_CHECK(v->matrix[i] == testVertex2[i]);
	}
}

void test_obj_parse_normal(void) {
	//init
	int i;
	bool result;
	struct RastVector* vn;
	struct RastObject obj;
	rast_object_init(&obj);

	//bad normal input
	result = rast_object_parse_line(&obj, NORMAL_BAD);
	TEST_CHECK(!result);
	TEST_CHECK(obj.vertexNormals.length == 0);

	//good normal input
	float testNormal[4] = NORMAL_RESULT;
	result = rast_object_parse_line(&obj, NORMAL);
	TEST_CHECK(result);
	TEST_CHECK(obj.vertexNormals.length == 1);
	vn = rast_arraylist_get(&obj.vertexNormals, 0);
	for (i = 0; i < 4; i++) {
		TEST_CHECK(vn->matrix[i] == testNormal[i]);
	}
}

void test_obj_parse_texture(void) {
	//init
	int i;
	bool result;
	struct RastTextureCoord* vt;
	struct RastObject obj;
	rast_object_init(&obj);

	//bad vertex input
	result = rast_object_parse_line(&obj, TEXTURE_BAD);
	TEST_CHECK(!result);
	TEST_CHECK(obj.textureCoords.length == 0);

	//vertex without w component
	float testTexture1[3] = TEXTURE_1_RESULT;
	result = rast_object_parse_line(&obj, TEXTURE_1);
	TEST_CHECK(result);
	TEST_CHECK(obj.textureCoords.length == 1);
	vt = rast_arraylist_get(&obj.textureCoords, 0);
	TEST_CHECK(vt->u == testTexture1[0]);
	TEST_CHECK(vt->v == testTexture1[1]);
	TEST_CHECK(vt->w == testTexture1[2]);

	//vertex with w component
	float testTexture2[3] = TEXTURE_2_RESULT;
	result = rast_object_parse_line(&obj, TEXTURE_2);
	TEST_CHECK(result);
	TEST_CHECK(obj.textureCoords.length == 2);
	vt = rast_arraylist_get(&obj.textureCoords, 1);
	TEST_CHECK(vt->u == testTexture2[0]);
	TEST_CHECK(vt->v == testTexture2[1]);
	TEST_CHECK(vt->w == testTexture2[2]);
}

bool checkFace(struct RastFace* f, int* testFace) {
	bool res = true;
	res = res && (f->v1 == testFace[0]);
	res = res && (f->vt1 == testFace[1]);
	res = res && (f->vn1 == testFace[2]);
	res = res && (f->v2 == testFace[3]);
	res = res && (f->vt2 == testFace[4]);
	res = res && (f->vn2 == testFace[5]);
	res = res && (f->v3 == testFace[6]);
	res = res && (f->vt3 == testFace[7]);
	res = res && (f->vn3 == testFace[8]);
	return res;
}

void test_obj_parse_face(void) {
	bool result;
	struct RastFace* f;
	struct RastObject obj;
	rast_object_init(&obj);
	
	int testFace1[9] = FACE_1_RESULT;
	result = rast_object_parse_line(&obj, FACE_1);
	TEST_CHECK(result);
	TEST_CHECK(obj.faces.length == 1);
	f = rast_arraylist_get(&obj.faces, 0);
	TEST_CHECK(checkFace(f, testFace1));

	int testFace2[9] = FACE_2_RESULT;
	result = rast_object_parse_line(&obj, FACE_2);
	TEST_CHECK(result);
	TEST_CHECK(obj.faces.length == 2);
	f = rast_arraylist_get(&obj.faces, 1);
	TEST_CHECK(checkFace(f, testFace2));

	int testFace3[9] = FACE_3_RESULT;
	result = rast_object_parse_line(&obj, FACE_3);
	TEST_CHECK(result);
	TEST_CHECK(obj.faces.length == 3);
	f = rast_arraylist_get(&obj.faces, 2);
	TEST_CHECK(checkFace(f, testFace3));

	int testFace4[9] = FACE_4_RESULT;
	result = rast_object_parse_line(&obj, FACE_4);
	TEST_CHECK(result);
	TEST_CHECK(obj.faces.length == 4);
	f = rast_arraylist_get(&obj.faces, 3);
	TEST_CHECK(checkFace(f, testFace4));
}

void test_obj_parse_misc(void) {
	bool result;
	struct RastObject obj;
	rast_object_init(&obj);
	
	result = rast_object_parse_line(&obj, COMMENT_LINE);
	TEST_CHECK(!result);
	TEST_CHECK(obj.faces.length == 0);
	TEST_CHECK(obj.vertices.length == 0);
	TEST_CHECK(obj.vertexNormals.length == 0);
	TEST_CHECK(obj.textureCoords.length == 0);
	
	rast_object_init(&obj);
	result = rast_object_parse_line(&obj, JUNK_INPUT);
	TEST_CHECK(!result);
	TEST_CHECK(obj.faces.length == 0);
	TEST_CHECK(obj.vertices.length == 0);
	TEST_CHECK(obj.vertexNormals.length == 0);
	TEST_CHECK(obj.textureCoords.length == 0);
}