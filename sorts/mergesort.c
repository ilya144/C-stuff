#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void printArray(int* arr, int arraySize){
    printf("\n------------\n");
    printf("Array: \n");
    printf("[ ");
    for (int i = 0; i < arraySize; i++){
        printf("%d ", arr[i]);
    }
    printf("]");
    printf("\n------------\n");
};

void mergeSort(int* array, int arraySize);

int* immutableMergeSort(int* array, int arraySize){
    int halfSize = arraySize / 2;

    int* resultArray = calloc(arraySize, sizeof(int));
    int interArray[arraySize];
    memcpy(interArray, array, arraySize * sizeof(int));

    int leftArrSize = halfSize;
    int* leftArr = interArray;
    mergeSort(interArray, leftArrSize);

    int rightArrSize = arraySize - halfSize;
    int* rightArr = interArray + halfSize;
    mergeSort(interArray + halfSize, rightArrSize);

    for (int i = 0; i < arraySize; i++){
        if (leftArrSize && rightArrSize) {
            if (*leftArr < *rightArr){
                resultArray[i] = *leftArr;
                leftArr++;
                leftArrSize--;
            } else {
                resultArray[i] = *rightArr;
                rightArr++;
                rightArrSize--;
            }
        } else if (leftArrSize) {
            resultArray[i] = *leftArr;
            leftArr++;
            leftArrSize--;
        } else if (rightArrSize) {
            resultArray[i] = *rightArr;
            rightArr++;
            rightArrSize--;
        }
    }

    return resultArray;
}

void mergeSort(int* array, int arraySize){
    if (arraySize <= 1) return;

    int halfSize = arraySize / 2; 
    int interArray[arraySize];
    memcpy(interArray, array, arraySize * sizeof(int));

    int leftArrSize = halfSize;
    int* leftArr = interArray;
    mergeSort(interArray, leftArrSize);

    int rightArrSize = arraySize - halfSize;
    int* rightArr = interArray + halfSize;
    mergeSort(interArray + halfSize, rightArrSize);

    for (int i = 0; i < arraySize; i++){
        if (leftArrSize && rightArrSize) {
            if (*leftArr < *rightArr){
                array[i] = *leftArr;
                leftArr++;
                leftArrSize--;
            } else {
                array[i] = *rightArr;
                rightArr++;
                rightArrSize--;
            }
        } else if (leftArrSize) {
            array[i] = *leftArr;
            leftArr++;
            leftArrSize--;
        } else if (rightArrSize) {
            array[i] = *rightArr;
            rightArr++;
            rightArrSize--;
        }
    }
}

int main(){
    int arr[] = { 5, 1, 6, 10, 2, 17, 3, 1 };
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    mergeSort(arr, sizeof(arr) / sizeof(int));

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}