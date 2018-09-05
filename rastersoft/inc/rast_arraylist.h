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

/*** Standard Library ***/
#include <stdbool.h>

/*** External Libraries ***/
/*** Local Headers ***/
/*** Global Defines ***/
/*** Global Enums ***/

/*** Global Structs ***/

/* Arraylist datastructure
 * length : number of items in list
 * allocated : number of items list can currently hold
 */
struct rast_arraylist {
	void * data;
	unsigned int length;
	unsigned int allocated;
};

/*** Extern Variables ***/

/*** Global Functions ***/

void rast_arraylist_init(struct rast_arraylist* list);
bool rast_arraylist_initSize(struct rast_arraylist* list, unsigned int item_size, unsigned int total_length);
bool rast_arraylist_insert(struct rast_arraylist* list, unsigned int index, void * item);
bool rast_arraylist_remove(struct rast_arraylist* list, unsigned int index);
void rast_arraylist_push(struct rast_arraylist* list, void * item);
void* rast_arraylist_pop(struct rast_arraylist* list, void * item);
void* rast_arraylist_get(struct rast_arraylist* list, unsigned int index, void * item);
void rast_arraylist_clear(struct rast_arraylist* list, unsigned int index, void * item);
void rast_arraylist_destroy(struct rast_arraylist* list, unsigned int index, void * item);

#endif //rast_arraylist_h