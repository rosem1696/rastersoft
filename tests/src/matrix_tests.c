#define TEST_NO_MAIN

#include <stdbool.h>

#include "acutest.h"
#include "rastersoft.h"
#include "rast_matrix.h"

//Helper
bool vector_eq(struct RastVector * v1, struct RastVector * v2) {
	bool ret = true;
	int i;
	for (i = 0; i < 4 && ret; i++) {
		ret = v1->matrix[i] == v2->matrix[i];
	}
	return ret;
}

bool transform_eq(struct RastTransform * t1, struct RastTransform * t2) {
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
	struct RastTransform transform;
	rast_oneTransform(&transform);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			TEST_CHECK(transform.matrix[i][j] == 1);
		}
	}
}

void test_matrix_transformZero() {
	struct RastTransform transform;
	rast_zeroTransform(&transform);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			TEST_CHECK(transform.matrix[i][j] == 0);
		}
	}
}

void test_matrix_identity() {
	struct RastTransform transform;
	rast_identityTransform(&transform);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			(i == j)	?	TEST_CHECK(transform.matrix[i][j] == 1) 
						:	TEST_CHECK(transform.matrix[i][j] == 0);
		}
	}
}

//Vector generation tests
void  test_matrix_oneVector() {
	struct RastVector vector;
	rast_oneVector(&vector);
	int i;
	for (i = 0; i < 4; i++) {
		TEST_CHECK(vector.matrix[i] == 1);
	}
}


void  test_matrix_zeroVector() {
	struct RastVector vector;
	rast_zeroVector(&vector);
	int i;
	for (i = 0; i < 4; i++) {
		TEST_CHECK(vector.matrix[i] == 0);
	}
}

//Transform Operations
void test_matrix_addTransforms(void) {
	struct RastTransform t1;
	struct RastTransform t2;
	struct RastTransform t3;
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
	struct RastTransform t1;
	struct RastTransform t2;
	struct RastTransform t3;
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

//Vector Operations
void test_matrix_dotProduct(void) {
	struct RastVector v1;
	struct RastVector v2;
	rast_zeroVector(&v1);
	rast_oneVector(&v2);
	TEST_CHECK(rast_dotProduct(&v1, &v2) == 0);
	rast_oneVector(&v1);
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

void test_matrix_addVectors(void) {
	struct RastVector v1;
	struct RastVector v2;
	struct RastVector v3;
	rast_zeroVector(&v1);
	rast_zeroVector(&v2);
	rast_addVectors(&v3, &v1, &v2);
	TEST_CHECK(vector_eq(&v3, &v1));
	rast_oneVector(&v1);
	rast_addVectors(&v3, &v1, &v2);
	TEST_CHECK(vector_eq(&v3, &v1));
	int i;
	for (i = 0; i < 4; i++) {
		v1.matrix[i] = i;
		v2.matrix[i] = 2 * i;
		v3.matrix[i] = 3 * i;
	}
	rast_addVectors(&v1, &v1, &v2);
	TEST_CHECK(vector_eq(&v3, &v1));
}

void test_matrix_subVectors(void) {
	struct RastVector v1;
	struct RastVector v2;
	struct RastVector v3;
	rast_zeroVector(&v1);
	rast_zeroVector(&v2);
	rast_subVectors(&v3, &v1, &v2);
	TEST_CHECK(vector_eq(&v3, &v1));
	rast_oneVector(&v1);
	rast_subVectors(&v1, &v1, &v1);
	TEST_CHECK(vector_eq(&v2, &v1));
	int i;
	for (i = 0; i < 4; i++) {
		v1.matrix[i] = i;
		v2.matrix[i] = 4 * i;
		v3.matrix[i] = 3 * i;
	}
	rast_subVectors(&v1, &v2, &v1);
	TEST_CHECK(vector_eq(&v3, &v1));
}

//Matrix Multiplication
void test_matrix_multTrans(void) {
	struct RastTransform t1;
	struct RastTransform t2;
	struct RastTransform t3;
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

void test_matrix_transVector(void) {
	struct RastTransform t;
	struct RastVector v1;
	struct RastVector v2;
	rast_oneTransform(&t);
	rast_zeroVector(&v1);
	rast_transVector(&v2, &v1, &t);
	TEST_CHECK(vector_eq(&v1, &v2));
	rast_oneVector(&v1);
	int i, j;
	for (i = 0; i < 4; i++) {
		v2.matrix[i] = 4;
	}
	rast_transVector(&v1, &v1, &t);
	TEST_CHECK(vector_eq(&v1, &v2));
	rast_identityTransform(&t);
	rast_transVector(&v1, &v2, &t);
	TEST_CHECK(vector_eq(&v2, &v1));
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			t.matrix[i][j] = (4 * i) + j;
		}
	}
	for (i = 0; i < 4; i++) {
		v1.matrix[i] = i;
	}
	v2.matrix[0] = 56; v2.matrix[1] = 62; v2.matrix[2] = 68; v2.matrix[3] = 74;
	rast_transVector(&v1, &v1, &t);
	TEST_CHECK(vector_eq(&v1, &v2));
}