/**
* @file rast_arraylist.h
* @author Mitchell Rose
* @date 15 May 2018
* @brief Simple arraylist implementation for use with Rastersoft
* @copyright Copyright (c) 2018 Mitchell Rose
* @license MIT License
*/

#ifndef rast_arraylist_h
#define rast_arraylist_h

/*** Headers ***/

#include <stdint.h>

#include "rast_defines.h"

/*** Structs ***/

/* Arraylist datastructure
 * item_size : size in bytes of single item
 * length : number of items in list
 * allocated : number of items list can currently hold
 */
struct RastArraylist {
	void * list;
	size_t item_size;
	uint64_t length;
	size_t allocated;
};

/*** Exported Functions ***/

DLL_EXPORT void rast_arraylist_init(struct RastArraylist* list, size_t item_size);
DLL_EXPORT void rast_arraylist_initSize(struct RastArraylist* list, size_t item_size, uint64_t total_length);
DLL_EXPORT void rast_arraylist_insert(struct RastArraylist* list, uint64_t index, void * item);
DLL_EXPORT void rast_arraylist_remove(struct RastArraylist* list, uint64_t index);
DLL_EXPORT void rast_arraylist_push(struct RastArraylist* list, void * item);
DLL_EXPORT void rast_arraylist_pop(struct RastArraylist* list, void * dest);
DLL_EXPORT void* rast_arraylist_get(struct RastArraylist* list, uint64_t index);
DLL_EXPORT void rast_arraylist_clear(struct RastArraylist* list);
DLL_EXPORT void rast_arraylist_destroy(struct RastArraylist* list);

#endif //rast_arraylist_h