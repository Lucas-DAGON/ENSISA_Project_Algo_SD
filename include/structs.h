#pragma once
#include <stdlib.h>


/* ================= statistics structure ================= */
// Keep track of statistics in sorting algorithms
typedef struct Sstat {
    int comparisons;
    int swaps;
} Sstat;

typedef Sstat* Stat;

/* ================= Struct constructor (prototype) ================= */
Stat stat_constructor(void);