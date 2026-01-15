#include <stdlib.h>
#include "../include/sort.h"
#include "../include/utils.h"
#include "../include/structs.h"


/* ================= SELECTION SORT ================= */

Stat selection_sort(int *arr, int n)
{
    if (!arr || n <= 1)
        return NULL;

    Stat stat = stat_constructor();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        
        for (int j = i + 1; j < n; j++) {
            stat -> comparisons++;
            if (arr[j] < arr[min])
                min = j;
        }
        if (min != i) {
            stat -> swaps++;
            swap_int(&arr[i], &arr[min]);
        }
    }
    return stat;
}

/* ================= INSERTION SORT ================= */

Stat insertion_sort(int *arr, int n)
{
    if (!arr || n <= 1)
        return NULL;

    Stat stat = stat_constructor();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            stat->comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                stat->swaps++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
    return stat;
}


/* ================= BUBBLE SORT ================= */

Stat bubble_sort(int *arr, int n)
{
    if (!arr || n <= 1)
        return NULL;
    
    Stat stat = stat_constructor();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            stat -> comparisons++;
            if (arr[j] > arr[j + 1]) {
                stat -> swaps++;
                swap_int(&arr[j], &arr[j + 1]);
            }
        }
    }
    return stat;
}

/* ================= MERGE SORT ================= */

static void merge(int *arr, int *tmp, int left, int mid, int right, Stat stat)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        stat->comparisons++;
        if (arr[i] <= arr[j])
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    }

    while (i <= mid)
        tmp[k++] = arr[i++];

    while (j <= right)
        tmp[k++] = arr[j++];
}


static void merge_sort_rec(int *arr, int *tmp, int left, int right, Stat stat)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    merge_sort_rec(arr, tmp, left, mid, stat);
    merge_sort_rec(arr, tmp, mid + 1, right, stat);
    merge(arr, tmp, left, mid, right, stat);

    for (int i = left; i <= right; i++)
        arr[i] = tmp[i];
}


Stat merge_sort(int *arr, int n)
{
    if (!arr || n <= 1)
        return NULL;
    Stat stat = stat_constructor();

    int *tmp = malloc(sizeof(int) * n);
    if (!tmp) {
        free(stat);
        return NULL;
    }

    merge_sort_rec(arr, tmp, 0, n - 1, stat);
    free(tmp);
    return stat;
}

/* ================= QUICK SORT ================= */

static int partition(int *arr, int left, int right, Stat stat)
{
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        stat->comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap_int(&arr[i], &arr[j]);
            stat->swaps++;
        }
    }
    swap_int(&arr[i + 1], &arr[right]);
    stat->swaps++;

    return i + 1;
}


static void quick_sort_rec(int *arr, int left, int right, Stat stat)
{
    if (left < right) {
        int p = partition(arr, left, right, stat);
        quick_sort_rec(arr, left, p - 1, stat);
        quick_sort_rec(arr, p + 1, right, stat);
    }
}

Stat quick_sort(int *arr, int n)
{
    if (!arr || n <= 1)
        return NULL;
    Stat stat = stat_constructor();
    quick_sort_rec(arr, 0, n - 1, stat);
    return stat;
}
