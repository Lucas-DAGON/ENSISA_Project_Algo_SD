#include <stdlib.h>
#include "../include/sort.h"
#include "../include/utils.h"
#include "../include/structs.h"

/* ================= Swap station ================= */
static void swap_station(Station *a, Station *b)
{
    Station tmp = *a;
    *a = *b;
    *b = tmp;
}


/* ================= SELECTION SORT ================= */

static Stat selection_sort_station(Station *arr, int n)
{
    if (!arr || n <= 1)
        return NULL;

    Stat stat = stat_constructor();

    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            stat->comparisons++;
            if (arr[j].degree < arr[min].degree)
                min = j;
        }

        if (min != i) {
            swap_station(&arr[i], &arr[min]);
            stat->swaps++;
        }
    }
    return stat;
}


/* ================= INSERTION SORT ================= */

static Stat insertion_sort_station(Station *arr, int n)
{
    if (!arr || n <= 1)
        return NULL;

    Stat stat = stat_constructor();

    for (int i = 1; i < n; i++) {
        Station key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            stat->comparisons++;
            if (arr[j].degree > key.degree) {
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

static Stat bubble_sort_station(Station *arr, int n)
{
    if (!arr || n <= 1)
        return NULL;

    Stat stat = stat_constructor();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            stat->comparisons++;
            if (arr[j].degree > arr[j + 1].degree) {
                swap_station(&arr[j], &arr[j + 1]);
                stat->swaps++;
            }
        }
    }
    return stat;
}


/* ================= MERGE SORT ================= */

static void merge_station(
    Station *arr,
    Station *tmp,
    int left,
    int mid,
    int right,
    Stat stat
)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        stat->comparisons++;
        if (arr[i].degree <= arr[j].degree)
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    }

    while (i <= mid)
        tmp[k++] = arr[i++];

    while (j <= right)
        tmp[k++] = arr[j++];
}



static void merge_sort_station_rec(
    Station *arr,
    Station *tmp,
    int left,
    int right,
    Stat stat
)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    merge_sort_station_rec(arr, tmp, left, mid, stat);
    merge_sort_station_rec(arr, tmp, mid + 1, right, stat);
    merge_station(arr, tmp, left, mid, right, stat);

    for (int i = left; i <= right; i++)
        arr[i] = tmp[i];
}



static Stat merge_sort_station(Station *arr, int n)
{
    if (!arr || n <= 1)
        return NULL;

    Stat stat = stat_constructor();
    Station *tmp = malloc(sizeof(Station) * n);
    if (!tmp) {
        free(stat);
        return NULL;
    }

    merge_sort_station_rec(arr, tmp, 0, n - 1, stat);
    free(tmp);
    return stat;
}


/* ================= QUICK SORT ================= */

static int partition_station(Station *arr, int left, int right, Stat stat)
{
    Station pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        stat->comparisons++;
        if (arr[j].degree <= pivot.degree) {
            i++;
            swap_station(&arr[i], &arr[j]);
            stat->swaps++;
        }
    }
    swap_station(&arr[i + 1], &arr[right]);
    stat->swaps++;

    return i + 1;
}



static void quick_sort_station_rec(
    Station *arr,
    int left,
    int right,
    Stat stat
)
{
    if (left < right) {
        int p = partition_station(arr, left, right, stat);
        quick_sort_station_rec(arr, left, p - 1, stat);
        quick_sort_station_rec(arr, p + 1, right, stat);
    }
}


static Stat quick_sort_station(Station *arr, int n)
{
    if (!arr || n <= 1)
        return NULL;

    Stat stat = stat_constructor();
    quick_sort_station_rec(arr, 0, n - 1, stat);
    return stat;
}



/* ================= SORT STATIONS BY DEGREE ================= */
Stat sort_stations_by_degree(Station *stations, int n, int method)
{
    switch (method) {
        case 1:
            return selection_sort_station(stations, n);
        case 2:
            return insertion_sort_station(stations, n);
        case 3:
            return bubble_sort_station(stations, n);
        case 4:
            return merge_sort_station(stations, n);
        case 5:
            return quick_sort_station(stations, n);
        default:
            return NULL;
    }
}
