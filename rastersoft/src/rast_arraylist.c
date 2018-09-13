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
#include "rast_arraylist.h"

/*** Local Functions ***/
void ensureSize(struct RastArraylist* list) {
	if (list->length == list->allocated) {
		list->allocated *= 2;
		void* doubled_list = realloc(list->list, list->allocated * list->item_size);
		list->list = doubled_list;
	}
}

void* getIndexPointer(struct RastArraylist* list, int index) {
	return (((char*) list->list) + (list->item_size * index));
}

/*** Exported Functions ***/

void rast_arraylist_init(struct RastArraylist* list, size_t item_size) {
	list->item_size = item_size;
	list->length = 0;
	list->allocated = 10;
	list->list = malloc(list->item_size * list->allocated);
}

void rast_arraylist_initSize(struct RastArraylist* list, size_t item_size, unsigned int total_length) {
	if (total_length > 0) {
		list->item_size = item_size;
		list->length = 0;
		list->allocated = total_length;
		list->list = malloc(list->item_size * list->allocated);
	}
}

void rast_arraylist_insert(struct RastArraylist* list, unsigned int index, void* item) {
	if (item) {
		if (index < list->length) {
			ensureSize(list);
			void * indexPtr = getIndexPointer(list, index);
			void * moveDest = getIndexPointer(list, index + 1);
			memmove(moveDest, indexPtr, list->item_size * (list->length - index));
			memcpy(indexPtr, item, list->item_size);
			list->length++;
		} else if (index == list->length) {
			rast_arraylist_push(list, item);
		}
	}
}

void rast_arraylist_remove(struct RastArraylist* list, unsigned int index) {
	if (index < list->length - 1) {
		void * moveDest = getIndexPointer(list, index);
		void * moveStart = getIndexPointer(list, index + 1);
		memmove(moveDest, moveStart, list->item_size * (list->length - index - 1));
		list->length--;
	} else if (index == list->length - 1) {
		list->length--;
	}
}

void rast_arraylist_push(struct RastArraylist* list, void* item) {
	if (item) {
		ensureSize(list);
		memcpy(getIndexPointer(list, list->length), item, list->item_size);
		list->length++;
	}
}

void rast_arraylist_pop(struct RastArraylist* list, void* dest) {
	if (list->length > 0) {
		memcpy(dest, getIndexPointer(list, list->length - 1), list->item_size);
		list->length--;
	}
}

void* rast_arraylist_get(struct RastArraylist* list, unsigned int index) {
	return (index < list->length)
		? getIndexPointer(list, index)
		: NULL;
}

void rast_arraylist_clear(struct RastArraylist* list) {
	list->length = 0;
}

void rast_arraylist_destroy(struct RastArraylist* list) {
	free(list->list);
}