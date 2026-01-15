#include <stdio.h>
#include <stdlib.h>
#include "../include/sort.h"
#include "../include/structs.h"

static int *read_file(const char *filename, int *size)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    int capacity = 16;
    int count = 0;
    int *arr = malloc(sizeof(int) * capacity);
    if (!arr) {
        fclose(fp);
        return NULL;
    }

    while (fscanf(fp, "%d", &arr[count]) == 1) {
        count++;
        if (count >= capacity) {
            capacity *= 2;
            int *tmp = realloc(arr, sizeof(int) * capacity);
            if (!tmp) {
                free(arr);
                fclose(fp);
                return NULL;
            }
            arr = tmp;
        }
    }

    fclose(fp);
    *size = count;
    return arr;
}

static void print_array(const int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = 0;
    int *arr = read_file(argv[1], &n);
    if (!arr)
        return EXIT_FAILURE;

    printf("Original array:\n");
    print_array(arr, n);

    Stat stat = bubble_sort(arr, n);   // change here to test other sorts

    printf("Sorted array:\n");
    print_array(arr, n);
    if (stat) {
        printf("Comparisons: %d\n", stat->comparisons);
        printf("Swaps: %d\n", stat->swaps);
        free(stat);
    }

    free(arr);
    return EXIT_SUCCESS;
}
