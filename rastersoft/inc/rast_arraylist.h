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

#include "rast_defines.h"

/*** Structs ***/

/* Arraylist datastructure
 * item_size : size in bytes of single item
 * length : number of items in list
 * allocated : number of items list can currently hold
 */
struct rast_arraylist {
	void * list;
	unsigned int item_size;
	unsigned int length;
	unsigned int allocated;
};

/*** Exported Functions ***/

DLL_EXPORT void rast_arraylist_init(struct rast_arraylist* list, size_t item_size);
DLL_EXPORT void rast_arraylist_initSize(struct rast_arraylist* list, size_t item_size, unsigned int total_length);
DLL_EXPORT void rast_arraylist_insert(struct rast_arraylist* list, unsigned int index, void * item);
DLL_EXPORT void rast_arraylist_remove(struct rast_arraylist* list, unsigned int index);
DLL_EXPORT void rast_arraylist_push(struct rast_arraylist* list, void * item);
DLL_EXPORT void rast_arraylist_pop(struct rast_arraylist* list, void * dest);
DLL_EXPORT void* rast_arraylist_get(struct rast_arraylist* list, unsigned int index);
DLL_EXPORT void rast_arraylist_clear(struct rast_arraylist* list);
DLL_EXPORT void rast_arraylist_destroy(struct rast_arraylist* list);

#endif //rast_arraylist_h