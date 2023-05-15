#include "matrix_init.h"
#include "matrix_abc.h"

matrix * matrix_set_zero (matrix *m)
{
    size_t h = matrix_height(m), w = matrix_width(m);

    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
        {
            double *e = matrix_get(m, i, j);
            *e = 0;
        }

    return m;
}

matrix * matrix_alloc_zero (size_t h, size_t w)
{
    matrix *m = matrix_alloc(h, w);
    if (!m) return NULL;

    return matrix_set_zero(m);
}

matrix * matrix_set_identity (matrix *m)
{
    size_t s = matrix_height(m);

    if (s != matrix_width(m)) return NULL;

    for (size_t i = 0; i < s; ++i)
        for (size_t j = 0; j < s; ++j)
        {
            double *e = matrix_get(m, i, j);
            if (i == j) *e = 1;
            else *e = 0;
        }
    return m;
}

matrix * matrix_alloc_identity (size_t s)
{
    matrix *m = matrix_alloc(s, s);
    if (!m) return NULL;

    return matrix_set_identity(m);
}

matrix * matrix_clone (const matrix *m)
{
    size_t h = matrix_height(m), w = matrix_width(m);
    matrix *m_clone = matrix_alloc(h, w);
    if (!m_clone) return NULL;

    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
        {
            double e = *(matrix_cget(m, i, j)), *e_clone = matrix_get(m_clone, i, j);
            *e_clone = e;
        }

    return m_clone;
}
