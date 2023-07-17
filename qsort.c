typedef int (*compare_fn)(int a, int b);

void arrcpy(int* dst, int* src, int size){
    for (int i = 0; i < size; i++){
        dst[i] = src[i];
    };
}

// recursive, mutable, with compare callback
void qsort(int arr[], int arr_length, compare_fn fn){
    if (arr_length <= 1) return;

    int result[arr_length];
    int pivot = arr[arr_length / 2];
    int r_pivot = 0;

    int result_idx = 0;

    for (int i = 0; i < arr_length; i++){
        if (fn(pivot, arr[i]) > 0) result[result_idx++] = arr[i];
    }
    for (int i = 0; i < arr_length; i++){
        if (fn(pivot, arr[i]) == 0) {
            result[result_idx] = arr[i];
            r_pivot = result_idx;
            result_idx++;
        }
    }
    for (int i = 0; i < arr_length; i++){
        if (fn(pivot, arr[i]) < 0) result[result_idx++] = arr[i];
    }

    int after_pivot = r_pivot + 1;
    qsort(result, r_pivot, fn);
    qsort(result + after_pivot, arr_length - after_pivot, fn);

    arrcpy(arr, result, arr_length);
}

int asc_sort(int a, int b){ return a - b; }
int desc_sort(int a, int b){ return b - a; }

