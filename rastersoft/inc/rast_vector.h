#ifndef rast_vector_h
#define rast_vector_h

#include "rast_defines.h"

DLL_EXPORT struct arrayList {
	void **data;
	int size; //Current size of array
	int length; //Number of elements in list
	int dataSize
};

DLL_EXPORT void arrayList_init(struct arrayList* list, int dataSize);
DLL_EXPORT void arrayList_init_length(struct arrayList* list, int dataSize, int initialLength);
DLL_EXPORT void arrayList_add(struct arrayList* list, void* data);
DLL_EXPORT int arrayList_set(struct arrayList* list, void* data, int index);
DLL_EXPORT void* arrayList_get(struct arrayList* list, int index);
DLL_EXPORT int arrayList_remove(struct arrayList* list, int index);
DLL_EXPORT void arrayList_clear(struct arrayList* list);
DLL_EXPORT void arrayList_free(struct arrayList* list);

#endif



