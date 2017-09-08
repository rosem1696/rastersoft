#ifndef rast_vector_h
#define rast_vector_h

#include "rast_defines.h"
#include <stddef.h>

struct arrayList {
	void **data;
	size_t size;	//< Current size of array
	size_t length;	//< Number of elements in list
	size_t dataSize;
};

DLL_EXPORT void arrayList_init(struct arrayList* list, size_t dataSize);
DLL_EXPORT void arrayList_init_length(struct arrayList* list, size_t dataSize, size_t initialLength);
DLL_EXPORT void arrayList_add(struct arrayList* list, void* data);
DLL_EXPORT int arrayList_set(struct arrayList* list, void* data, size_t index);
DLL_EXPORT void* arrayList_get(struct arrayList* list, size_t index);
DLL_EXPORT int arrayList_remove(struct arrayList* list, size_t index);
DLL_EXPORT void arrayList_clear(struct arrayList* list);
DLL_EXPORT void arrayList_free(struct arrayList* list);

#endif
