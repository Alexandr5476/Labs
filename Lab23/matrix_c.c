#include "matrix_abc.h"
#include "stdlib.h"

struct matrix
{
    size_t height, width;
    double *array;
};

matrix * matrix_alloc (size_t h, size_t w)
{
    matrix *m = malloc(sizeof(matrix));
    if (!m) return NULL;

    if(!(m->array = malloc(h * w * sizeof(double))))
    {
        free(m);
        return NULL;
    }

    m->height = h;
    m->width = w;

    return m;
}

void matrix_free (matrix *m)
{
    free(m->array);
    free(m);
}

matrix * matrix_resize (matrix *m, size_t h, size_t w)
{
    free(m->array);
    if(!(m->array = malloc(h * w * sizeof(double)))) return NULL;

    m->height = h;
    m->width = w;

    return m;
}

double * matrix_get (matrix *m, size_t i, size_t j)
{
    return (m->array) + (i * m->width) + j;
}

const double * matrix_cget (const matrix *m, size_t i, size_t j)
{
    return (m->array) + (i * m->width) + j;
}

size_t matrix_height (const matrix *m)
{
    return m->height;
}

size_t matrix_width (const matrix *m)
{
    return m->width;
}
