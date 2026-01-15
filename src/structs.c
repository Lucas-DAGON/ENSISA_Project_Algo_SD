#include <stdlib.h>
#include "../include/structs.h"

/* ================= Stat constructor ================= */
Stat stat_constructor(void)
{
    Stat s = malloc(sizeof(Sstat));
    if (!s)
        return NULL;
    s->comparisons = 0;
    s->swaps = 0;
    return s;
}