#ifndef MATRIX_PROBLEMS_H_INCLUDED
#define MATRIX_PROBLEMS_H_INCLUDED
#include <stdio.h>
#include "matrix_abc.h"

/** Решает систему линейных уравнений методом Гаусса
 *  m - матрица коэффициентов, m_right - столбец правых частей, answer - столбец для записи ответа
 *  Возвращает answer или NULL, если не удалось выделить память, или матрица не обратима,
 *  или матрицы не правильного размера
 */
matrix * matrix_gauss_method (const matrix *m, const matrix *m_right, matrix *answer);


/** Обращает матрицу m
 *  Возвращает обратную матрицу или NULL, если матрица не обратима или не удалось выделить память
 *  Требуется вызов matrix_free, чтобы освободить матрицу
 */
matrix * matrix_inverse(const matrix *m);


/** Возвращает матричную экспоненту матрицы m
 *  или NULL, если матрица не квадратная или не удалось выделить память
 *  Требуется вызов matrix_free, чтобы освободить матрицу
 */
matrix * matrix_exp(const matrix *m);

#endif // MATRIX_PROBLEMS_H_INCLUDED
