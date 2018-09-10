#include "acutest.h"
#include "matrix_tests.h"
#include "arraylist_tests.h"

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
	//Arraylist Tests
	{ "arraylist_init", test_arraylist_init },
	{ "arraylist_push_get", test_arraylist_push_get },
	{ "arraylist_pop", test_arraylist_pop },
	{ "arraylist_insert", test_arraylist_insert },
	{ "arraylist_remove", test_arraylist_remove },
	{ "arraylist_clear", test_arraylist_clear },
	{ NULL, NULL }
};