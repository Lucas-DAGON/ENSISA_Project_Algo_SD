#include "..\include\utils.h"

void swap_int(int *a, int *b)
{
    // swap two elements
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool is_sorted_nondecreasing(int *arr, int n)
{
    // check if array is sorted, if yes return true
    for (int i = 0; i < n; i++){
        if (arr[i] > arr[i+1]) return false;
    }

    return true;
}

void copy_array(int *src, int *dst, int n)
{
    // copy array elements src into dst
    for (int i = 0; i < n; i++){
        dst[i] = src[i];
    }
}