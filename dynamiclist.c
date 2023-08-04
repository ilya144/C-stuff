#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// https://stackoverflow.com/a/1810295
typedef int data_elem_t[2];
typedef struct DynamicArray DynamicArray;

const int INITIAL_ALLOCATION_SIZE = 1;

struct DynamicArray {
    data_elem_t* data;
    int length;
    int allocated;
    void (*push)(DynamicArray *self, data_elem_t data);
    int* (*pop)(DynamicArray *self);
    void (*map)(DynamicArray *self, void (*callback)(data_elem_t elem, int index, data_elem_t* array));
    int* (*get)(DynamicArray *self, int index);
};

void __DynamicArray__push(DynamicArray *self, data_elem_t data){
    printf("%d ", data[0]);
    printf("%d \n", data[1]);
    if (self->length == self->allocated) {
        self->allocated = self->allocated * 2;
        self->data = realloc(
            self->data, 
            self->allocated * sizeof(data_elem_t)
        );
    }
    memcpy(self->data[self->length], data, sizeof(data_elem_t));
    self->length = self->length + 1;
}

int* __DynamicArray__pop(DynamicArray *self){
    if (self->length == 0) return NULL;
    self->length--;

    return self->data[self->length];
}

void __DynamicArray__map(
    DynamicArray *self, void (*callback)(data_elem_t elem, int index, data_elem_t* array)
){
    for (int i = 0; i < self->length; i++){
        callback(self->data[i], i, self->data);
    }
}

int* __DynamicArray__get(DynamicArray *self, int index){
    if (index > self->length - 1 || index < 0) return NULL;
    
    return self->data[index];
}

DynamicArray* Array(){
    DynamicArray* array = malloc(sizeof(DynamicArray));
    data_elem_t* data = calloc(INITIAL_ALLOCATION_SIZE, sizeof(data_elem_t));
    array->data = data;
    array->length = 0;
    array->allocated = INITIAL_ALLOCATION_SIZE;
    array->push = __DynamicArray__push;
    array->pop = __DynamicArray__pop;
    array->map = __DynamicArray__map;
    array->get = __DynamicArray__get;

    return array;
}

void freeArray(DynamicArray* self){
    free(self->data);
    free(self);
}

void printCallback(data_elem_t elem, int index, data_elem_t* array){
    printf("value on index: %d is \n [0]: %d \n [1]: %d \n---------\n", index, elem[0], elem[1]);
}

void main(void){
    DynamicArray* arr = Array();

    
    data_elem_t first = { 0, 5 };
    data_elem_t second = { 77, 88 };

    arr->push(arr, first);
    arr->push(arr, second);
    arr->push(arr, (int[]){ 5, 10 });
    arr->push(arr, (int[]){ 99999, 999999 });
    arr->pop(arr);
    

    arr->map(arr, printCallback);

    freeArray(arr);

    puts("\n-------------\n");
}