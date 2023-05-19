#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int street_insert (dtb *list, char *n_name, double n_length, int n_houses)
{
    street *a = realloc(list->street_list, (list->len + 1) * sizeof(*a)), *b = a;
    if (!a) return 1;

    b += list->len;
    b->houses = n_houses;
    b->name = n_name;
    b->length = n_length;

    list->street_list = a;
    ++list->len;

    return 0;
}

int street_delete (dtb *list, size_t place)
{
    street *l, *a;
    char *name;
    int houses;
    double length;

    if (!list->len)
        return 1;

    if (list->len == 1)
    {
        free(list->street_list->name);
        list->len = 0;
        return 0;
    }

    l = list->street_list + place;

    name = l->name;
    houses = l->houses;
    length = l->length;

    for (street *p = l, *q = p + 1, *e = list->street_list + list->len; q < e; ++p, ++q) *p = *q;



    if(!(a = realloc(list->street_list, (list->len - 1) * sizeof(*a))))
    {

        for (street *p = l, *q = l + 1, *e = list->street_list + list->len; q < e; ++p, ++q) *q = *p;

        l->name = name;
        l->houses = houses;
        l->length = length;

        return 1;
    }
    list->street_list = a;

    --list->len;

    free(name);

    return 0;
}

void street_free (dtb *list)
{
    for (street *p = list->street_list, *e = p + list->len; p < e; ++p) free(p->name);
    free(list->street_list);

    list->len = 0;
    list->street_list = NULL;
}

int cmp_length_incr (const void *a, const void *b)
{
    return ((street*)a)->length > ((street*)b)->length;
}

int cmp_houses_incr (const void *a, const void *b)
{
    return ((street*)a)->houses > ((street*)b)->houses;
}

int cmp_name_incr (const void *a, const void *b)
{
    char *x = (((street*)a)->name), *y = (((street*)b)->name);
    for (; *x && *y; ++x, ++y) if (*x != *y) return *x > *y;
    return *x > *y;
}

int cmp_length_decr (const void *a, const void *b)
{
    return ((street*)a)->length < ((street*)b)->length;
}

int cmp_houses_decr (const void *a, const void *b)
{
    return ((street*)a)->houses < ((street*)b)->houses;
}

int cmp_name_decr (const void *a, const void *b)
{
    char *x = (((street*)a)->name), *y = (((street*)b)->name);
    for (; *x && *y; ++x, ++y) if (*x != *y) return *x < *y;
    return *x < *y;
}

void sort(void *array, size_t len, size_t size, fnc_comp cmp)
{
    void *t = malloc(size);
    if (!t) exit(-1);
    char *i, *j, *e2 = array + len * size, *e1 = e2 - size;

    for (i = (char*) array; i < e1; i += size)
    {
        char *k = i;

        for (j = i + size; j < e2; j += size) if (cmp(k, j)) k = j;

        if (k != i)
        {
            memcpy (t, k, size);
            memcpy (k, i, size);
            memcpy (i, t, size);
        }
    }

    free(t);
}

street * maximum (dtb list, fnc_comp cmp)
{
    street *max = list.street_list;
    for (street *p = max, *e = p + list.len; p < e; ++p)
        if (cmp(max, p)) max = p;

    return max;
}

double sum_length (dtb list)
{
    double sum = 0;
    for (street *p = list.street_list, *e = p + list.len; p < e; ++p)
        sum += p->length;

    return sum;
}

double sum_houses (dtb list)
{
    double sum = 0;
    for (street *p = list.street_list, *e = p + list.len; p < e; ++p)
        sum += p->houses;

    return sum;
}

double divide_houses (const street *a, const street *b)
{
    return ((double)(a->houses) / b->houses);
}

double divide_length (const street *a, const street *b)
{
    return ((double)(a->length) / b->length);
}

double divide_houses_num (const street *a, double b)
{
    return ((a->houses) / b);
}

double divide_length_num (const street *a, double b)
{
    return ((a->length) / b);
}
