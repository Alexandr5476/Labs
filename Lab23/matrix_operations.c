#include "matrix_operations.h"
#include "matrix_init.h"
#include "matrix_abc.h"
#include <stdlib.h>
#include <math.h>

void matrix_print (const matrix *m)
{
    size_t h = matrix_height(m), w = matrix_width(m);

    for (size_t i = 0; i < h; ++i)
    {
        for (size_t j = 0; j < w; ++j) printf("%3lg ", *(matrix_cget(m, i, j)));

        printf("\n\n");
    }
}

matrix * matrix_assign (matrix *m1, const matrix *m2)
{
    size_t h = matrix_height(m2), w = matrix_width(m2);
    if (h != matrix_height(m1) || w != matrix_width(m1))
        if (!matrix_resize(m1, h, w))
            return NULL;

    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
        {
            double e2 = *(matrix_cget(m2, i, j)), *e1 = matrix_get(m1, i, j);
            *e1 = e2;
        }

    return m1;
}

int matrix_equal(const matrix *m1, const matrix *m2)
{
    size_t h = matrix_height(m2), w = matrix_width(m2);

    if (h != matrix_height(m1) || w != matrix_width(m1))
        return 0;

    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
            if ((*matrix_cget(m1, i, j)) != (*matrix_cget(m2, i, j)))
                return 0;
    return 1;
}

matrix * matrix_add (matrix *m1, const matrix *m2)
{
    size_t h = matrix_height(m2), w = matrix_width(m2);

    if (h != matrix_height(m1) || w != matrix_width(m1))
        return NULL;

    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
        {
            double e2 = *(matrix_cget(m2, i, j)), *e1 = matrix_get(m1, i, j);
            *e1 += e2;
        }

    return m1;
}

matrix * matrix_sum (matrix *m, const matrix *m1, const matrix *m2)
{
    size_t h = matrix_height(m2), w = matrix_width(m2);

    if (h != matrix_height(m1) || w != matrix_width(m1))
        return NULL;

    if (h != matrix_height(m) || w != matrix_width(m))
        if (!matrix_resize(m, h, w))
            return NULL;

    matrix_assign(m, m1);
    matrix_add(m, m2);

    return m;
}

matrix * matrix_subtr (matrix *m1, const matrix *m2)
{
    size_t h = matrix_height(m2), w = matrix_width(m2);

    if (h != matrix_height(m1) || w != matrix_width(m1))
        return NULL;

    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
        {
            double e2 = *(matrix_cget(m2, i, j)), *e1 = matrix_get(m1, i, j);
            *e1 -= e2;
        }

    return m1;
}

matrix * matrix_dif (matrix *m, const matrix *m1, const matrix *m2)
{
    size_t h = matrix_height(m2), w = matrix_width(m2);

    if (h != matrix_height(m1) || w != matrix_width(m1))
        return NULL;

    if (h != matrix_height(m) || w != matrix_width(m))
        if (!matrix_resize(m, h, w))
            return NULL;

    matrix_assign(m, m1);
    matrix_subtr(m, m2);

    return m;
}

matrix * matrix_multipl (matrix *m1, const matrix *m2)
{
    size_t h = matrix_height(m2), w = matrix_width(m2), h1 = matrix_height(m1);
    matrix *m_tmp;

    if (h != matrix_width(m1))
        return NULL;

    if (!(m_tmp = matrix_clone(m1)))
        return NULL;

    if (h != w)
        if (!matrix_resize(m1, h1, w))
            return NULL;

    for (size_t i = 0; i < h1; ++i)
        for (size_t j = 0; j < w; ++j)
        {
            double *e = matrix_get(m1, i, j);
            *e = 0;
            for (size_t k = 0; k < h; ++k)
            {
                double e1 = *(matrix_cget(m_tmp, i, k)), e2 = *(matrix_cget(m2, k, j));
                *e += (e1 * e2);
            }
        }

    matrix_free(m_tmp);

    return m1;

}

matrix * matrix_multipl_scal (matrix *m, double scalar)
{
    size_t h = matrix_height(m), w = matrix_width(m);

    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
        {
            double *e = matrix_get(m, i, j);
            *e *= scalar;
        }

    return m;
}

matrix * matrix_transp_rec (matrix *m)
{
    size_t h = matrix_height(m), w = matrix_width(m);
    matrix *m_tmp = matrix_clone(m);

    if (!m_tmp) return NULL;
    if (!matrix_resize(m, w, h)) return NULL;

    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
        {
            double *e = matrix_get(m, j, i);
            *e = (*matrix_cget(m_tmp, i, j));
        }
    matrix_free(m_tmp);

    return m;}

matrix * matrix_transp_squ (matrix *m)
{
    size_t s = matrix_height(m);

    for (size_t i = 0; i < s; ++i)
        for (size_t j = 0; j < s; ++j)
            if (i < j)
            {
                double *e1 = matrix_get(m, i, j), *e2 = matrix_get(m, j, i), x = *e1;
                //printf("e1 = %lg, e2 = %lg, x = %lg -> ", *e1, *e2, x);
                *e1 = *e2;
                *e2 = x;
                //printf("e1 = %lg, e2 = %lg, x = %lg\n", *e1, *e2, x);
            }

    return m;
}

matrix * matrix_transp (const matrix *m)
{
    size_t h = matrix_height(m), w = matrix_width(m);
    matrix *m_transp = matrix_alloc(w, h);

    if (!m_transp) return NULL;

    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
        {
            double *e = matrix_get(m_transp, j, i);
            *e = (*matrix_cget(m, i, j));
        }
    return m_transp;
}

matrix * matrix_str_multipl (matrix *m, size_t i, double x)
{
    size_t w = matrix_width(m);

    for (size_t j = 0; j < w; ++j)
        *(matrix_get(m, i, j)) *= x;

    return m;
}

matrix * matrix_str_add (matrix *m, size_t i1, size_t i2)
{
    size_t w = matrix_width(m);

    for (size_t j = 0; j < w; ++j)
        *(matrix_get(m, i1, j)) += *(matrix_cget(m, i2, j));

    return m;
}

matrix * matrix_str_swop (matrix *m, size_t i1, size_t i2)
{
    size_t w = matrix_width(m);

    for (size_t j = 0; j < w; ++j)
    {
        double *e1 = matrix_get(m, i1, j), *e2 = matrix_get(m, i2, j), x = *e1;
        *e1 = *e2;
        *e2 = x;
    }

    return m;
}

matrix * matrix_submatrix (matrix *m1, const matrix *m2, size_t h, size_t w)
{
    if (h != matrix_height(m1) || w != matrix_width(m1))
        if (!matrix_resize(m1, h, w))
            return NULL;

    for (size_t i = 0; i < h; ++i)
        for (size_t j = 0; j < w; ++j)
            *(matrix_get(m1, i, j)) = *(matrix_cget(m2, i, j));

    return m1;
}

double matrix_norm (const matrix *m)
{
    size_t h = matrix_height(m), w = matrix_width(m);
    double norm = 0;

    for (size_t i = 0; i < h; ++i)
    {
        double n = 0;
        for (size_t j = 0; j < w; ++j)
            n += fabs(*(matrix_cget(m, i, j)));

        if (n > norm) norm = n;
    }

    return norm;
}


double matrix_det (const matrix *m)
{
    size_t s = matrix_height(m), *index = malloc(sizeof(*index) * s); matrix *m_tmp = matrix_clone(m);
    double det = 1;

    if((!m_tmp) || (!index) || (s != matrix_width(m)))
    {
        if (m_tmp) matrix_free(m_tmp);
        if (index) free(index);
        return 0/0.;;
    }

    /* index - массив индексов строк */
    for (size_t i = 0, *p = index; i < s; ++i, ++p)
        *p = i;

    for (size_t column = 0; column < s; ++column) // Цикл по столбцам
    {
        size_t str = index[column];
        double min1 = *matrix_cget(m_tmp, str, column), e;
        /* min1 - число из текущего столбца, ближайшее к 1 и не равное 0
         * str - соответствующая строка (в которой находится min1)
         */
        for (size_t *p = index + column + 1, *z = index + s; p < z; ++p)
            if (((fabs(1 - (e = *matrix_cget(m_tmp, *p, column))) < fabs(1 - min1)) && e) || !min1)
            {
                min1 = e;
                str = *p;
            }

        if (!min1)
        {
            matrix_free(m_tmp);
            free(index);
            return min1;
        }

        for (size_t *q = index + column, *p = q + 1, *e = index + s; p < e; ++p)
            if (*p == str)
            {
                *p = *q;
                *q = str;
                det = -det;
                break;
            }
        /* Деление найденой строки на min1, чтобы получить 1 на месте (str, column) */
        for (size_t j = column; j < s; ++j)
            *(matrix_get(m_tmp, str, j)) /= min1;

        det *= min1;

        /* Вычитание из каждой строки (ниже str) строки str, умноженной на соответствующее число,
         * чтобы получить нули в текущем столбце (ниже строки str)
         * Цикл по строкам в порядке индексов строк из массива индексов
         */
        for (size_t *q = index + column, *p = q + 1, *e = index + s; p < e; ++p)
        {
            double x = *matrix_cget(m_tmp, *p, column);

            for (size_t j = column; j < s; ++j)
                *matrix_get(m_tmp, *p, j) -= *matrix_cget(m_tmp, str, j) * x;
        }
    }
    matrix_free(m_tmp);
    free(index);
    return det;
}
