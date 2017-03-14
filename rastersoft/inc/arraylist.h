#ifndef arraylist_h_ 
#define arraylist_h_

struct arrayList {
	void **data;
	int size; //Current size of array
	int length; //Number of elements in list
	int dataSize
};

void arrayList_init(struct arrayList* list, int dataSize);
void arrayList_init(struct arrayList* list, int dataSize, int initialLength);
void arrayList_add(struct arrayList* list, void* data);
int arrayList_set(struct arrayList* list, void* data, int index);
void* arrayList_get(struct arrayList* list, int index);
int arrayList_remove(struct arrayList* list, int index);
void arrayList_clear(struct arrayList* list);
void arrayList_free(struct arrayList* list);

#endif  





