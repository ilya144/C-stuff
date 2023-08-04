#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int* immutableBubbleSort(int* array, int arraySize){
    int* resultArray = calloc(arraySize, sizeof(int));
    memcpy(resultArray, array, arraySize * sizeof(int));

    for (int i = 0; i < arraySize - 1; i++){
        for (int j = i + 1; j < arraySize; j++){
            if (resultArray[i] > resultArray[j]){
                int swap = resultArray[i];
                resultArray[i] = resultArray[j];
                resultArray[j] = swap;
            }
        }
    }

    return resultArray;
}

void bubbleSort(int* array, int arraySize){
    for (int i = 0; i < arraySize - 1; i++){
        for (int j = i + 1; j < arraySize; j++){
            if (array[i] > array[j]){
                int swap = array[i];
                array[i] = array[j];
                array[j] = swap;
            }
        }
    }
}


int main(){
    int arr[] = {5, 1, 6, 10, 2, 17, 3, 1};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    int * sorted = immutableBubbleSort(arr, sizeof(arr) / sizeof(int));
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++){
        printf("%d ", sorted[i]);
    }
    printf("\n");
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}