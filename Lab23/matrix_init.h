#ifndef MATRIX_INIT_H_INCLUDED
#define MATRIX_INIT_H_INCLUDED
#include <stdio.h>
#include "matrix_abc.h"

/** Заполняет матрицу m нулями
 *  Возвращает указатель на заполненную матрицу
 */
matrix * matrix_set_zero (matrix *m);


/** Создаёт матрицу и заполняет её нулями
 *  h - количество строк, w - количество столбцов
 *  Возвращает указатель на матрицу или NULL, если выделение памяти не удалось
 *  Требуется вызов matrix_free, чтобы освободить матрицу
 */
matrix * matrix_alloc_zero (size_t h, size_t w);


/** Делает из m единичную матрицу
 *  Возвращает m или NULL, если матрица не квадратная
 */
matrix * matrix_set_identity (matrix *m);


/** Создаёт единичную матрицу
 *  s - количество строк и столбцов
 *  Возвращает указатель на матрицу или NULL, если выделение памяти не удалось
 *  Требуется вызов matrix_free, чтобы освободить матрицу
 */
matrix * matrix_alloc_identity (size_t s);


/** Копирует матрицу m
 *  Возвращает указатель на новыую матрицу или NULL, если выделение памяти не удалось
 *  Требуется вызов matrix_free, чтобы освободить копию
 */
matrix * matrix_clone (const matrix *m);

#endif // MATRIX_INIT_H_INCLUDED
