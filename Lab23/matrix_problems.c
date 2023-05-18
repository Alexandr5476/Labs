#include "matrix_problems.h"
#include "matrix_operations.h"
#include "matrix_init.h"
#include "matrix_abc.h"
#include <stdlib.h>
#include <math.h>

matrix * matrix_gauss_method (const matrix *m, const matrix *m_right, matrix *answer)
{
    size_t s = matrix_height(m), *index = malloc(sizeof(*index) * s);
    matrix *m_tmp = matrix_clone(m), *r_tmp = matrix_clone(m_right);

    if((!m_tmp) || (!index) || (!r_tmp) || (s != matrix_width(m)) ||
        s != matrix_height(m_right) || matrix_width(m_right) != 1)
    {
        if (m_tmp) matrix_free(m_tmp);
        if (r_tmp) matrix_free(r_tmp);
        if (index) free(index);
        return NULL;
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
        if (!min1)  /* Если min1 - 0, то матрица необратима */
        {
            matrix_free(m_tmp);
            matrix_free(r_tmp);
            free(index);
            return NULL;
        }

        /* Перестановка индексов строк */
        for (size_t *p = index + column, *q = p, *e = index + s; p < e; ++p)
            if (*p == str)
            {
                *p = *q;
                *q = str;
                break;
            }
        /* Деление найденой строки на min1, чтобы получить 1 на месте (str, column)
         * Делить нужно только те элементы, которые правее текущего столбца,
         * потому что левее только нули
         */
        for (size_t j = column; j < s; ++j)
            *(matrix_get(m_tmp, str, j)) /= min1;

        *(matrix_get(r_tmp, str, 0)) /= min1; // В столбце правых частей тоже нужно разделить на min1 элемент на месте str

        /* Вычитание из каждой строки (ниже str) строки str, умноженной на соответствующее число,
         * чтобы получить нули в текущем столбце (ниже строки str)
         * Цикл по строкам в порядке индексов строк из массива индексов
         */
        for (size_t *q = index + column, *p = q + 1, *e = index + s; p < e; ++p)
        {
            double x = *matrix_cget(m_tmp, *p, column); // Первый (ненулевой) элемент из текущей строки

            /* Само вычитание строк, т.е из каждого элемента текущей строки нужно
             * вычесть соответствующий элемент из строки str, умноженный на x
             * начинаем с текущего столбца, потому что левее только нули
             */
            for (size_t j = column; j < s; ++j)
                *matrix_get(m_tmp, *p, j) -= *matrix_cget(m_tmp, str, j) * x;

            *matrix_get(r_tmp, *p, 0) -= *matrix_cget(r_tmp, str, 0) * x; // Тоже самое в столбце правых частей
        }
    }

    /* Теперь на главной диогонали только единицы, под диогональю нули
     * Нужно получить нули над диогональю, единицы на диогонали при этом сохранятся,
     * поэтому можно изменять только столбец правых частей
     */
    for (size_t *p = index + s - 1, column = s - 1; p >= index; --p, --column)
    { /* Цикл снизу вверх */

        double x = *matrix_cget(r_tmp, *p, 0); // Элемент из текущей строки в столбце правых частей

        for (size_t *i = index; i < p; ++i)
            /* Вычитание из каждой (выше текущей) строки столбца правых частей
             * соответствующего элемента над главной диогональю матрицы
             */
            *matrix_get(r_tmp, *i, 0) -= *matrix_cget(m_tmp, *i, column) * x;
    }
    /* Запись ответа */
    for (size_t *p = index, str = 0; str < s; ++p, ++str)
        *matrix_get(answer, str, 0) = *matrix_cget(r_tmp, *p, 0);

    matrix_free(m_tmp);
    matrix_free(r_tmp);
    free(index);

    /* Проверка на правильность ответа */
    m_tmp = matrix_clone(m);
    if (!matrix_multipl(m_tmp, answer))
    {
        matrix_free(m_tmp);
        return NULL;
    }

    if (matrix_norm(matrix_subtr(m_tmp, m_right)) > 0.001)
    {
        matrix_free(m_tmp);
        return NULL;
    }
    matrix_free(m_tmp);

    return answer;
}

matrix * matrix_inverse(const matrix *m)
{
    size_t s = matrix_height(m), *index = malloc(sizeof(*index) * s);
    matrix *m_tmp = matrix_clone(m), *r_tmp = matrix_alloc_identity(s), *check = NULL;

    if((!m_tmp) || (!index) || (!r_tmp) || (s != matrix_width(m)))
    {
        if (m_tmp) matrix_free(m_tmp);
        if (r_tmp) matrix_free(r_tmp);
        if (index) free(index);
        return NULL;
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
        if (!min1)  /* Если min1 - 0, то матрица необратима */
        {
            matrix_free(m_tmp);
            matrix_free(r_tmp);
            free(index);
            return NULL;
        }

        /* Перестановка индексов строк */
        for (size_t *p = index + column, *q = p, *e = index + s; p < e; ++p)
            if (*p == str)
            {
                *p = *q;
                *q = str;
                break;
            }
        /* Деление найденой строки на min1, чтобы получить 1 на месте (str, column) */
        for (size_t j = 0; j < s; ++j)
        {
            *(matrix_get(m_tmp, str, j)) /= min1;
            *(matrix_get(r_tmp, str, j)) /= min1;
        }

        /* Вычитание из каждой строки (ниже str) строки str, умноженной на соответствующее число,
         * чтобы получить нули в текущем столбце (ниже строки str)
         * Цикл по строкам в порядке индексов строк из массива индексов
         */
        for (size_t *q = index + column, *p = q + 1, *e = index + s; p < e; ++p)
        {
            double x = *matrix_cget(m_tmp, *p, column);

            for (size_t j = 0; j < s; ++j)
            {
                *matrix_get(m_tmp, *p, j) -= *matrix_cget(m_tmp, str, j) * x;
                *matrix_get(r_tmp, *p, j) -= *matrix_cget(r_tmp, str, j) * x;
            }

        }
    }

    /* Теперь на главной диогонали только единицы, под диогональю нули
     * Нужно получить нули над диогональю, единицы на диогонали при этом сохранятся,
     * поэтому можно изменять только матрицу, которая станет обратной
     */
    for (size_t *p = index + s - 1, column = s - 1; p >= index; --p, --column)
    {
        for (size_t *i = index; i < p; ++i)
        {
            double x = *matrix_cget(m_tmp, *i, column);

            for (size_t j = 0; j < s; ++j)
                *matrix_get(r_tmp, *i, j) -= *matrix_cget(r_tmp, *p, j) * x;
        }
    }
    /* Настоящая перестановка строк */
    for (size_t *i = index, *e = index + s, k = 0; i < e; ++i, ++k)
        if (*i != k)
        {
            matrix_str_swop(r_tmp, *i, k);
            for (size_t *j = i; j < e; ++j)
                if (*j == k)
                {
                    *j = *i;
                    *i = k;
                    break;
                }
        }

    free(index);

    /* Проверка на правильность ответа */
    m_tmp = matrix_clone(m);
    if ((!matrix_multipl(m_tmp, r_tmp)) || (!(check = matrix_alloc_identity(s))))
    {
        matrix_free(m_tmp);
        matrix_free(r_tmp);
        if (check) matrix_free(check);
        return NULL;
    }

    if (matrix_norm(matrix_subtr(m_tmp, check)) > 0.001)
    {
        matrix_free(r_tmp);
        matrix_free(m_tmp);
        matrix_free(check);
        return NULL;
    }
    matrix_free(check);
    matrix_free(m_tmp);

    return r_tmp;
}

matrix * matrix_exp(const matrix *m)
{
    size_t s = matrix_height(m);
    matrix *e = matrix_alloc_identity(s), *sum = matrix_alloc_identity(s);

    if ((!e) || (!sum) || (s != matrix_width(m)))
    {
        if (e) matrix_free(e);
        if (sum) matrix_free(sum);
        return NULL;
    }

    for (int n = 1; matrix_norm(e) > 0.001; ++n)
    {
        matrix_multipl(e, m);
        matrix_multipl_scal(e, 1. / n);

        matrix_add(sum, e);
    }

    matrix_free(e);

    return sum;
}



