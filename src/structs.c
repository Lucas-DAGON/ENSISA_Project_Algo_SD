#include <stdlib.h>
#include "../include/structs.h"

/* ================= Stat constructor ================= */
Stat stat_constructor(void)
{
    Stat s = malloc(sizeof(Sstat));
    s->comparisons = 0;
    s->swaps = 0;
    return s;
}

Station* station_constructor(int id, int degree)
{
    Station *s = malloc(sizeof(Station));
    if (!s)
        return NULL;

    s->id_station = id;
    s->degree = degree;
    return s;
}
