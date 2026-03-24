#include "matrix_abc.h"
#include "stdlib.h"

struct matrix
{
    size_t height, width;
    double **array, *data;
};

matrix * matrix_alloc (size_t h, size_t w)
{
    matrix *m = malloc(sizeof(matrix));
    double **array, *data;

    if (!m) return NULL;

    if(!(array = m->array = malloc(h * sizeof(double *))))
    {
        free(m);
        return NULL;
    }

    if (!(data = m->data = malloc(h * w * sizeof(double))))
    {
        free(array);
        free(m);
        return NULL;
    }

    for (double *i = data, *e = data + (h * w), **p = array; i < e; i += w, ++p) *p = i;

    m->height = h;
    m->width = w;

    return m;
}

void matrix_free (matrix *m)
{
    free(m->data);
    free(m->array);
    free(m);
}

matrix * matrix_resize (matrix *m, size_t h, size_t w)
{
    double **array, *data;

    free(m->array);
    free(m->data);

    if(!(array = m->array = malloc(h * sizeof(double *))))
    {
        free(m);
        return NULL;
    }

    if (!(data = m->data = malloc(h * w * sizeof(double))))
    {
        free(array);
        free(m);
        return NULL;
    }

    for (double *i = data, *e = data + (h * w), **p = array; i < e; i += w, ++p) *p = i;

    m->height = h;
    m->width = w;

    return m;
}

double * matrix_get (matrix *m, size_t i, size_t j)
{
    return (*((m->array) + i)) + j;
}

const double * matrix_cget (const matrix *m, size_t i, size_t j)
{
    return (*((m->array) + i)) + j;
}

size_t matrix_height (const matrix *m)
{
    return m->height;
}

size_t matrix_width (const matrix *m)
{
    return m->width;
}
