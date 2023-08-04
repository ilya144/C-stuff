#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"

void printArray(int* arr, int arraySize){
    puts("\n------------\n");
    puts("Array: \n");
    puts("[ ");
    for (int i = 0; i < arraySize; i++){
        printf("%d ", arr[i]);
    }
    puts(" ]");
    puts("\n------------\n");
};

void recursiveFill(int* arr, int arraySize, int rand_max){
    if (arraySize == 0) return;
    *arr = rand() % rand_max;
    recursiveFill(++arr, --arraySize, rand_max);
}

void fillRandomArray(int* arr, int arraySize, int rand_max){
    srand(time(NULL));
    recursiveFill(arr, arraySize, rand_max);
};
