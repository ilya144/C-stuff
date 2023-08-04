#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils/utils.h"

void quickSort(int* arr, int arraySize);

int* immutableQuickSort(int* arr, int arraySize){
    int pivotIndex = arraySize / 2;
    int pivot = arr[pivotIndex];

    int leftSize = 0;
    int rightSize = 0;

    int* result = calloc(arraySize, sizeof(int));
    int* innerPtr = result;
    memcpy(result, arr, arraySize * sizeof(int));

    for (int i = 0; i < arraySize; i++){
        if (arr[i] < pivot) {
            *innerPtr = arr[i];
            innerPtr++;
            leftSize++;
        }
    }
    for (int i = 0; i < arraySize; i++){
        if (arr[i] == pivot) {
            *innerPtr = arr[i];
            innerPtr++;
        }
    }
    for (int i = 0; i < arraySize; i++){
        if (arr[i] > pivot) {
            *innerPtr = arr[i];
            innerPtr++;
            rightSize++;
        }
    }

    quickSort(result, leftSize);
    quickSort(result + (arraySize - rightSize), rightSize);

    return result;
}

void quickSort(int* arr, int arraySize){
    if (arraySize < 2) return;
    int pivotIndex = arraySize / 2;
    int pivot = arr[pivotIndex];

    int leftSize = 0;
    int rightSize = 0;

    int innerArr[arraySize];
    int* innerPtr = innerArr;
    memcpy(innerArr, arr, arraySize * sizeof(int));

    for (int i = 0; i < arraySize; i++){
        if (arr[i] < pivot) {
            *innerPtr = arr[i];
            innerPtr++;
            leftSize++;
        }
    }
    for (int i = 0; i < arraySize; i++){
        if (arr[i] == pivot) {
            *innerPtr = arr[i];
            innerPtr++;
        }
    }
    for (int i = 0; i < arraySize; i++){
        if (arr[i] > pivot) {
            *innerPtr = arr[i];
            innerPtr++;
            rightSize++;
        }
    }

    memcpy(arr, innerArr, arraySize * sizeof(int));

    quickSort(arr, leftSize);
    quickSort(arr + (arraySize - rightSize), rightSize);
}

int main(){
    int arr[100];
    fillRandomArray(arr, 10, 228);

    printArray(arr, 100);

    int* sorted = immutableQuickSort(arr, sizeof(arr) / sizeof(int));

    printArray(sorted, 100);
}