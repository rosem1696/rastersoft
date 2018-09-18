#define TEST_NO_MAIN

#include "acutest.h"
#include "rastersoft.h"
#include "rast_arraylist.h"

void test_arraylist_init(void) {
	struct RastArraylist testList;
	//test default init
	rast_arraylist_init(&testList, sizeof(int));
	TEST_CHECK(testList.allocated == 10);
	TEST_CHECK(testList.length == 0);
	TEST_CHECK(testList.item_size == sizeof(int));
	//test specific init
	rast_arraylist_destroy(&testList);
	rast_arraylist_initSize(&testList, sizeof(char), 50);
	TEST_CHECK(testList.allocated == 50);
	TEST_CHECK(testList.length == 0);
	TEST_CHECK(testList.item_size == sizeof(char));
}

void test_arraylist_push_get(void) {
	//initialize
	struct RastArraylist testList;
	rast_arraylist_init(&testList, sizeof(int));
	//add items
	int i;
	for (i = 0; i < 40; i++) {
		rast_arraylist_push(&testList, &i);
	}
	//test length & allocated
	TEST_CHECK(testList.length == 40);
	TEST_CHECK(testList.allocated >= 40);
	//test retrieval
	for (i = 0; i < 40; i++) {
		int* ptr = (int*) rast_arraylist_get(&testList, i);
		TEST_CHECK(*ptr == i);
	}
	//test out of bounds index
	int* ptr = rast_arraylist_get(&testList, testList.length);
	TEST_CHECK(ptr == NULL);
	//test null push
	rast_arraylist_get(&testList, NULL);
	TEST_CHECK(testList.length == 40);
	TEST_CHECK(testList.allocated >= 40);
}

void test_arraylist_pop(void) {
	//initialize
	struct RastArraylist testList;
	rast_arraylist_init(&testList, sizeof(int));
	//add items
	int i;
	for (i = 0; i < 40; i++) {
		rast_arraylist_push(&testList, &i);
	}
	//test pop retrieval & removal
	for (i = 0; i < 40; i++) {
		int num;
		rast_arraylist_pop(&testList, &num);
		TEST_CHECK(num == (39 - i));
		TEST_CHECK(testList.length == (39 - i));
	}
}

void test_arraylist_insert(void) {
	//initialize
	struct RastArraylist testList;
	rast_arraylist_init(&testList, sizeof(int));
	//add items
	int i;
	for (i = 0; i < 10; i++) {
		rast_arraylist_push(&testList, &i);
	}
	//insert into middle
	i = 11;
	rast_arraylist_insert(&testList, 5, &i);
	//test insert
	int num = *(int*) rast_arraylist_get(&testList, 5);
	TEST_CHECK(num == 11);
	TEST_CHECK(testList.length == 11);
	num = *(int*)rast_arraylist_get(&testList, 6);
	TEST_CHECK(num == 5);
}

void test_arraylist_remove(void) {
	//initialize
	struct RastArraylist testList;
	rast_arraylist_init(&testList, sizeof(int));
	//add items
	int i;
	for (i = 0; i < 10; i++) {
		rast_arraylist_push(&testList, &i);
	}
	//remove from middle
	rast_arraylist_remove(&testList, 5);
	//test removal
	TEST_CHECK(testList.length == 9);
	int num = *(int*) rast_arraylist_get(&testList, 5);
	TEST_CHECK(num == 6);
	num = *(int*) rast_arraylist_get(&testList, 4);
	TEST_CHECK(num == 4);
}

void test_arraylist_clear(void) {
	//initialize
	struct RastArraylist testList;
	rast_arraylist_init(&testList, sizeof(int));
	//add items
	int i;
	for (i = 0; i < 10; i++) {
		rast_arraylist_push(&testList, &i);
	}
	//clear
	rast_arraylist_clear(&testList);
	//test empty
	TEST_CHECK(testList.length == 0);
	void* ptr = rast_arraylist_get(&testList, 0);
	TEST_CHECK(ptr == NULL);
}