#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rastersoft.h"
#include "rast_matrix.h"

void test_TransGen();

void run_matrix_tests() {
	printf("Testing Matrix Functions:\n");
	test_TransGen();

}

void test_TransGen() {
	printf("Testing Transform Generation");
	bool passed = true;
	struct rast_transform transform;
	
	//oneTransform
	rast_oneTransform(&transform);
	bool one_pass = true;
	int i, j;
	for (i = 0; i < 4 && one_pass; i++) {
		for (j = 0; j < 4 && one_pass; j++) {
			one_pass = transform.matrix[i][j] == 1;
		}
	}
	if (one_pass)
		printf("oneTransform Passed\n");
	else
		printf("oneTransform Failed\n");
	passed = passed && one_pass;

	//zeroTransform
	rast_zeroTransform(&transform);
	bool zero_pass = true;
	int i, j;
	for (i = 0; i < 4 && zero_pass; i++) {
		for (j = 0; j < 4 && zero_pass; j++) {
			zero_pass = transform.matrix[i][j] == 0;
		}
	}
	if (zero_pass)
		printf("zeroTransform Passed\n");
	else
		printf("zeroTransform Failed\n");
	passed = passed && zero_pass;

	//identityTransform
	rast_identityTransform(&transform);
	bool iden_pass = true;
	int i, j;
	for (i = 0; i < 4 && iden_pass; i++) {
		for (j = 0; j < 4 && iden_pass; j++) {
			if (i == j)
				iden_pass = transform.matrix[i][j] == 1;
			else
				iden_pass = transform.matrix[i][j] == 0;
		}
	}
	if (iden_pass)
		printf("identityTransform Passed\n");
	else
		printf("identityTransform Failed\n");
	passed = passed && iden_pass;
}