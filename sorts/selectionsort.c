#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int* immutableSelectionSort(int* array, int arraySize){
    int* resultArray = calloc(arraySize, sizeof(int));
    memcpy(resultArray, array, arraySize * sizeof(int));

    for (int i = 0; i < arraySize; i++){
        int minVal = resultArray[i];
        int minValIndex = i;
        for (int j = i + 1; j < arraySize; j++){
            if (resultArray[j] < minVal){
                minVal = resultArray[j];
                minValIndex = j;
            }
        }
        if (minValIndex != i){
            resultArray[minValIndex] = resultArray[i];
            resultArray[i] = minVal;
        };
    };

    return resultArray;
}

void selectionSort(int* array, int arraySize){
    for (int i = 0; i < arraySize; i++){
        int minVal = array[i];
        int minValIndex = i;
        for (int j = i + 1; j < arraySize; j++){
            if (array[j] < minVal){
                minVal = array[j];
                minValIndex = j;
            }
        }
        if (minValIndex != i){
            array[minValIndex] = array[i];
            array[i] = minVal;
        };
    };
}

int main(){
    int arr[] = {5, 1, 6, 10, 2, 17, 3, 1};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    int * sorted = immutableSelectionSort(arr, sizeof(arr) / sizeof(int));
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++){
        printf("%d ", sorted[i]);
    }
    printf("\n");
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}