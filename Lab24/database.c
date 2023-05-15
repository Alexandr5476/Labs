#include "database.h"
#include <stdio.h>
#include <stdlib.h>

street * street_insert (street * list, size_t len, char * n_name, double n_length, int n_houses)
{
    street *a = realloc (list, (len + 1) * sizeof(street)), *b = a;
    if (!a) return NULL;
    b += len;

    b->houses = n_houses;
    b->name = n_name;
    b->length = n_length;

    return a;
}

void street_delete (street *list, size_t len, size_t place)
{
    street *p = list + place;
    free(p->name);
    for (street *q = p + 1, *e = list + len; q < e; ++p, ++q) *p = *q;
}

void street_free (street *list, size_t len)
{
    for (street *p = list, *e = list + len; p < e; ++p) free(p->name);
    free (list);
}
