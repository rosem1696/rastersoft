#include "acutest.h"
#include "matrix_tests.h"

TEST_LIST = {
	//Matrix Tests
	{ "matrix_transformOne", test_matrix_transformOne },
	{ "matrix_transformZero", test_matrix_transformZero },
	{ "matrix_identity", test_matrix_identity },
	{ NULL, NULL }
};