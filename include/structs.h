#pragma once
#include <stdlib.h>


/* ================= Structure ================= */
// Keep track of statistics in sorting algorithms
typedef struct Sstat {
    int comparisons;
    int swaps;
} Sstat;

typedef Sstat* Stat;

typedef struct {
    int id_station;
    int degree;
} Station;




/* ================= Struct constructor ================= */
Stat stat_constructor();
Station* station_constructor(int id, int degree);