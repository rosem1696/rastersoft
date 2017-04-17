#ifndef rast_vector_h
#define rast_vector_h

<<<<<<< HEAD
#include "rast_defines.h"

DLL_EXPORT struct arrayList {
=======
#include <stddef.h>

struct arrayList {
>>>>>>> jhFixes/master
	void **data;
	size_t size;	//< Current size of array
	size_t length;	//< Number of elements in list
	size_t dataSize;
};

<<<<<<< HEAD
DLL_EXPORT void arrayList_init(struct arrayList* list, int dataSize);
DLL_EXPORT void arrayList_init_length(struct arrayList* list, int dataSize, int initialLength);
DLL_EXPORT void arrayList_add(struct arrayList* list, void* data);
DLL_EXPORT int arrayList_set(struct arrayList* list, void* data, int index);
DLL_EXPORT void* arrayList_get(struct arrayList* list, int index);
DLL_EXPORT int arrayList_remove(struct arrayList* list, int index);
DLL_EXPORT void arrayList_clear(struct arrayList* list);
DLL_EXPORT void arrayList_free(struct arrayList* list);

#endif



=======
void arrayList_init(struct arrayList* list, size_t dataSize);
void arrayList_init_length(struct arrayList* list, size_t dataSize, size_t initialLength);
void arrayList_add(struct arrayList* list, void* data);
int arrayList_set(struct arrayList* list, void* data, size_t index);
void* arrayList_get(struct arrayList* list, size_t index);
int arrayList_remove(struct arrayList* list, size_t index);
void arrayList_clear(struct arrayList* list);
void arrayList_free(struct arrayList* list);

#endif  
>>>>>>> jhFixes/master
