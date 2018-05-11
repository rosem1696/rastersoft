#ifndef matrix_tests_h
#define matrix_tests_h

//Transform Generation
void test_matrix_transformOne(void);
void test_matrix_transformZero(void);
void test_matrix_identity(void);

//Vertex Generation
void  test_matrix_oneVertex(void);
void  test_matrix_zeroVertex(void);

//Transform Operations
void test_matrix_addTransforms(void);
void test_matrix_subTransforms(void);

//Vertex Operations
void test_matrix_dotProduct(void);
void test_matrix_addVertexs(void);
void test_matrix_subVertexs(void);

//Matrix Multiplication
void test_matrix_multTrans(void);
void test_matrix_transVertex(void);

#endif