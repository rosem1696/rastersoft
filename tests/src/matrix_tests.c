#define TEST_NO_MAIN

#include <stdbool.h>

#include "acutest.h"
#include "rastersoft.h"
#include "rast_matrix.h"

//Helper
bool vertex_eq(struct rast_vertex * v1, struct rast_vertex * v2) {
	bool ret = true;
	int i;
	for (i = 0; i < 4 && ret; i++) {
		ret = v1->matrix[i] == v2->matrix[i];
	}
	return ret;
}

bool transform_eq(struct rast_transform * t1, struct rast_transform * t2) {
	bool ret = true;
	int i, j;
	for (i = 0; i < 4 && ret; i++) {
		for (j = 0; j < 4 && ret; j++) {
			ret = t1->matrix[i][j] == t2->matrix[i][j];
		}
	}
	return ret;
}

// Transform generation tests
void test_matrix_transformOne() {
	struct rast_transform transform;
	rast_oneTransform(&transform);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			TEST_CHECK(transform.matrix[i][j] == 1);
		}
	}
}

void test_matrix_transformZero() {
	struct rast_transform transform;
	rast_zeroTransform(&transform);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			TEST_CHECK(transform.matrix[i][j] == 0);
		}
	}
}

void test_matrix_identity() {
	struct rast_transform transform;
	rast_identityTransform(&transform);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			(i == j)	?	TEST_CHECK(transform.matrix[i][j] == 1) 
						:	TEST_CHECK(transform.matrix[i][j] == 0);
		}
	}
}

//Vertex generation tests
void  test_matrix_oneVertex() {
	struct rast_vertex vertex;
	rast_oneVertex(&vertex);
	int i;
	for (i = 0; i < 4; i++) {
		TEST_CHECK(vertex.matrix[i] == 1);
	}
}


void  test_matrix_zeroVertex() {
	struct rast_vertex vertex;
	rast_zeroVertex(&vertex);
	int i;
	for (i = 0; i < 4; i++) {
		TEST_CHECK(vertex.matrix[i] == 0);
	}
}

//Transform Operations
void test_matrix_addTransforms(void) {
	struct rast_transform t1;
	struct rast_transform t2;
	struct rast_transform t3;
	rast_oneTransform(&t1);
	rast_zeroTransform(&t2);
	rast_addTransforms(&t3, &t1, &t2);
	TEST_CHECK(transform_eq(&t3, &t1));
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			t3.matrix[i][j] = 2;
		}
	}
	rast_addTransforms(&t1, &t1, &t1);
	TEST_CHECK(transform_eq(&t3, &t1));
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			t1.matrix[i][j] = 4 * i + j;
			t2.matrix[i][j] = 2 * ( 4 * i + j);
			t3.matrix[i][j] = 3 * (4 * i + j);
		}
	}
	rast_addTransforms(&t1, &t1, &t2);
	TEST_CHECK(transform_eq(&t3, &t1));
	rast_identityTransform(&t1);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			t2.matrix[i][j] = 2 * t1.matrix[i][j];
		}
	}
	rast_addTransforms(&t1, &t1, &t1);
	TEST_CHECK(transform_eq(&t1, &t2));
}

void test_matrix_subTransforms(void) {
	struct rast_transform t1;
	struct rast_transform t2;
	struct rast_transform t3;
	rast_oneTransform(&t1);
	rast_zeroTransform(&t2);
	rast_subTransforms(&t1, &t1, &t1);
	TEST_CHECK(transform_eq(&t1, &t2));
	rast_identityTransform(&t1);
	rast_subTransforms(&t1, &t1, &t1);
	TEST_CHECK(transform_eq(&t1, &t2));
	rast_oneTransform(&t1);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			t2.matrix[i][j] = 2;
			t3.matrix[i][j] = -1;
		}
	}
	rast_subTransforms(&t1, &t1, &t2);
	TEST_CHECK(transform_eq(&t1, &t3));
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			t1.matrix[i][j] = 4 * i + j;
			t2.matrix[i][j] = 10 * (4 * i + j);
			t3.matrix[i][j] = (10 * (4 * i + j)) - (4 * i + j);
		}
	}
	rast_subTransforms(&t1, &t2, &t1);
	TEST_CHECK(transform_eq(&t1, &t3));
}

//Vertex Operations
void test_matrix_dotProduct(void) {
	struct rast_vertex v1;
	struct rast_vertex v2;
	rast_zeroVertex(&v1);
	rast_oneVertex(&v2);
	TEST_CHECK(rast_dotProduct(&v1, &v2) == 0);
	rast_oneVertex(&v1);
	TEST_CHECK(rast_dotProduct(&v1, &v2) == 4);
	int i;
	int t = 0;
	for (i = 0; i < 4; i++) {
		v1.matrix[i] = i;
		v2.matrix[i] = 4 + i;
		t += i * (4 + i);
	}
	TEST_CHECK(rast_dotProduct(&v1, &v2) == t);
}

void test_matrix_addVertexs(void) {
	struct rast_vertex v1;
	struct rast_vertex v2;
	struct rast_vertex v3;
	rast_zeroVertex(&v1);
	rast_zeroVertex(&v2);
	rast_addVertexs(&v3, &v1, &v2);
	TEST_CHECK(vertex_eq(&v3, &v1));
	rast_oneVertex(&v1);
	rast_addVertexs(&v3, &v1, &v2);
	TEST_CHECK(vertex_eq(&v3, &v1));
	int i;
	for (i = 0; i < 4; i++) {
		v1.matrix[i] = i;
		v2.matrix[i] = 2 * i;
		v3.matrix[i] = 3 * i;
	}
	rast_addVertexs(&v1, &v1, &v2);
	TEST_CHECK(vertex_eq(&v3, &v1));
}

void test_matrix_subVertexs(void) {
	struct rast_vertex v1;
	struct rast_vertex v2;
	struct rast_vertex v3;
	rast_zeroVertex(&v1);
	rast_zeroVertex(&v2);
	rast_subVertexs(&v3, &v1, &v2);
	TEST_CHECK(vertex_eq(&v3, &v1));
	rast_oneVertex(&v1);
	rast_subVertexs(&v1, &v1, &v1);
	TEST_CHECK(vertex_eq(&v2, &v1));
	int i;
	for (i = 0; i < 4; i++) {
		v1.matrix[i] = i;
		v2.matrix[i] = 4 * i;
		v3.matrix[i] = 3 * i;
	}
	rast_subVertexs(&v1, &v2, &v1);
	TEST_CHECK(vertex_eq(&v3, &v1));
}

//Matrix Multiplication
void test_matrix_multTrans(void) {
	struct rast_transform t1;
	struct rast_transform t2;
	struct rast_transform t3;
	rast_oneTransform(&t1);
	rast_zeroTransform(&t2);
	rast_multTrans(&t1, &t1, &t2);
	TEST_CHECK(transform_eq(&t1, &t2));
	rast_oneTransform(&t1);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			t2.matrix[i][j] = 4;
		}
	}
	rast_multTrans(&t1, &t1, &t1);
	TEST_CHECK(transform_eq(&t1, &t2));
	rast_identityTransform(&t1);
	rast_multTrans(&t3, &t1, &t2);
	TEST_CHECK(transform_eq(&t2, &t3));
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			t1.matrix[i][j] = (4 * i) + j;
			t2.matrix[i][j] = 16 + (4 * i) + j;
		}
	}
	t3.matrix[0][0] = 152;	t3.matrix[0][1] = 158;	t3.matrix[0][2] = 164;	t3.matrix[0][3] = 170;
	t3.matrix[1][0] = 504;	t3.matrix[1][1] = 526;	t3.matrix[1][2] = 548;	t3.matrix[1][3] = 570;
	t3.matrix[2][0] = 856;	t3.matrix[2][1] = 894;	t3.matrix[2][2] = 932;	t3.matrix[2][3] = 970;
	t3.matrix[3][0] = 1208; t3.matrix[3][1] = 1262; t3.matrix[3][2] = 1316;	t3.matrix[3][3] = 1370;
	rast_multTrans(&t1, &t1, &t2);
	TEST_CHECK(transform_eq(&t1, &t3));
}

void test_matrix_transVertex(void) {
	struct rast_transform t;
	struct rast_vertex v1;
	struct rast_vertex v2;
	rast_oneTransform(&t);
	rast_zeroVertex(&v1);
	rast_transVertex(&v2, &v1, &t);
	TEST_CHECK(vertex_eq(&v1, &v2));
	rast_oneVertex(&v1);
	int i, j;
	for (i = 0; i < 4; i++) {
		v2.matrix[i] = 4;
	}
	rast_transVertex(&v1, &v1, &t);
	TEST_CHECK(vertex_eq(&v1, &v2));
	rast_identityTransform(&t);
	rast_transVertex(&v1, &v2, &t);
	TEST_CHECK(vertex_eq(&v2, &v1));
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			t.matrix[i][j] = (4 * i) + j;
		}
	}
	for (i = 0; i < 4; i++) {
		v1.matrix[i] = i;
	}
	v2.matrix[0] = 56; v2.matrix[1] = 62; v2.matrix[2] = 68; v2.matrix[3] = 74;
	rast_transVertex(&v1, &v1, &t);
	TEST_CHECK(vertex_eq(&v1, &v2));
}