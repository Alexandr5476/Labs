#include "matrix_abc.h"
#include "stdlib.h"

struct matrix
{
    size_t height, width;
    double **array;
};

matrix * matrix_alloc (size_t h, size_t w)
{
    matrix *m = malloc(sizeof(matrix));
    double **array;

    if (!m) return NULL;

    if (!(array = m->array = malloc(h * sizeof(double *))))
    {
        free(m);
        return NULL;
    }

    for (double **i = array, **e = array + h; i < e; ++i)
    {
        if (!(*i = malloc(w * sizeof(double))))
        {
            for (double **j; j < i; ++j) free(*j);
            free(array);
            free(m);
            return NULL;
        }
    }

    m->height = h;
    m->width = w;

    return m;
}

void matrix_free (matrix *m)
{
    for (double **i = m->array, **e = i + m->height; i < e; ++i) free(*i);
    free(m->array);
    free(m);
}

matrix * matrix_resize (matrix *m, size_t h, size_t w)
{
    double **array;

    for (double **i = m->array, **e = i + m->height; i < e; ++i) free(*i);
    free(m->array);

    if (!(array = m->array = malloc(h * sizeof(double *))))
    {
        free(m);
        return NULL;
    }

    for (double **i = array, **e = array + h; i < e; ++i)
    {
        if (!(*i = malloc(w * sizeof(double))))
        {
            for (double **j; j < i; ++j) free(*j);
            free(array);
            free(m);
            return NULL;
        }
    }

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
