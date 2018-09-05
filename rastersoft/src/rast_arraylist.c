/**
* @file rast_arraylist.c
* @author Mitchell Rose
* @date 15 May 2018
* @brief Simple arraylist implementation for use with Rastersoft
* @copyright Copyright (c) 2018 Mitchell Rose
* @license MIT License
*/

/*** Standard Library ***/
#include <stdlib.h>
#include <stdbool.h>

/*** External Libraries ***/

/*** Local Headers ***/
#include "rast_arraylist.h"

/*** Local Defines ***/
/*** Local Enums ***/
/*** Local Structs ***/
/*** Local Variables ***/

/*** Local Functions ***/
void ensureSize(struct rast_arraylist* list) {
	if (list->length == list->allocated) {
		list->allocated *= 2;
		void * doubled_list = realloc(list->list, list->allocated * list->item_size);
		list->list = doubled_list;
	}
}

void* getIndexPointer(struct rast_arraylist* list, int index) {
	return ((char) list->list + (list->item_size * index));
}

/*** Function Implementations ***/

void rast_arraylist_init(struct rast_arraylist* list, unsigned int item_size) {
	list->item_size = item_size;
	list->length = 0;
	list->allocated = 10;
	list->list = malloc(list->item_size * list->allocated);
}

bool rast_arraylist_initSize(struct rast_arraylist* list, unsigned int item_size, unsigned int total_length) {
	if (total_length > 0) {
		list->item_size = item_size;
		list->length = 0;
		list->allocated = total_length;
		list->list = malloc(list->item_size * list->allocated);
		return true;
	} else {
		return false;
	}
}

bool rast_arraylist_insert(struct rast_arraylist* list, unsigned int index, void * item) {
	
}

bool rast_arraylist_remove(struct rast_arraylist* list, unsigned int index, void * item) {

}

void rast_arraylist_push(struct rast_arraylist* list, void * item) {
	ensureSize(list);
	memcpy(getIndexPointer(list, list->length), item, list->item_size);
}

void* rast_arraylist_pop(struct rast_arraylist* list, void * item) {

}

void* rast_arraylist_get(struct rast_arraylist* list, unsigned int index, void * item) {

}

void rast_arraylist_clear(struct rast_arraylist* list, unsigned int index, void * item) {

}

void rast_arraylist_destroy(struct rast_arraylist* list, unsigned int index, void * item) {

}