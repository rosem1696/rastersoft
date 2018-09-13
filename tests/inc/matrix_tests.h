#ifndef matrix_tests_h
#define matrix_tests_h

//Transform Generation
void test_matrix_transformOne(void);
void test_matrix_transformZero(void);
void test_matrix_identity(void);

//Vector Generation
void  test_matrix_oneVector(void);
void  test_matrix_zeroVector(void);

//Transform Operations
void test_matrix_addTransforms(void);
void test_matrix_subTransforms(void);

//Vector Operations
void test_matrix_dotProduct(void);
void test_matrix_addVectors(void);
void test_matrix_subVectors(void);

//Matrix Multiplication
void test_matrix_multTrans(void);
void test_matrix_transVector(void);

#endif