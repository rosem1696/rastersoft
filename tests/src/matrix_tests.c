#define TEST_NO_MAIN
#include "acutest.h"
#include "rastersoft.h"
#include "rast_matrix.h"

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
void  test_matrix_oneVector() {

}

//Vertex generation tests
void  test_matrix_oneVector() {

}