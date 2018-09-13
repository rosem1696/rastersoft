#include "acutest.h"
#include "matrix_tests.h"
#include "arraylist_tests.h"

TEST_LIST = {
	//Matrix Tests
	{ "matrix_transformOne", test_matrix_transformOne },
	{ "matrix_transformZero", test_matrix_transformZero },
	{ "matrix_identity", test_matrix_identity },
	{ "matrix_oneVector", test_matrix_oneVector },
	{ "matrix_zeroVector", test_matrix_zeroVector },
	{ "matrix_addTransforms", test_matrix_addTransforms},
	{ "matrix_subTransforms", test_matrix_subTransforms},
	{ "matrix_dotProduct", test_matrix_dotProduct },
	{ "matrix_addVectors", test_matrix_addVectors },
	{ "matrix_subVectors", test_matrix_subVectors },
	{ "matrix_multTrans", test_matrix_multTrans },
	{ "matrix_transVector", test_matrix_transVector},
	//Arraylist Tests
	{ "arraylist_init", test_arraylist_init },
	{ "arraylist_push_get", test_arraylist_push_get },
	{ "arraylist_pop", test_arraylist_pop },
	{ "arraylist_insert", test_arraylist_insert },
	{ "arraylist_remove", test_arraylist_remove },
	{ "arraylist_clear", test_arraylist_clear },
	{ NULL, NULL }
};