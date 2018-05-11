#include "acutest.h"
#include "matrix_tests.h"

TEST_LIST = {
	//Matrix Tests
	{ "matrix_transformOne", test_matrix_transformOne },
	{ "matrix_transformZero", test_matrix_transformZero },
	{ "matrix_identity", test_matrix_identity },
	{ "matrix_oneVertex", test_matrix_oneVertex },
	{ "matrix_zeroVertex", test_matrix_zeroVertex },
	{ "matrix_addTransforms", test_matrix_addTransforms},
	{ "matrix_subTransforms", test_matrix_subTransforms},
	{ "matrix_dotProduct", test_matrix_dotProduct },
	{ "matrix_addVertexs", test_matrix_addVertexs },
	{ "matrix_subVertexs", test_matrix_subVertexs },
	{ "matrix_multTrans", test_matrix_multTrans },
	{ "matrix_transVertex", test_matrix_transVertex},
	{ NULL, NULL }
};