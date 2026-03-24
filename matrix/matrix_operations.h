#ifndef MATRIX_OPERATIONS_H_INCLUDED
#define MATRIX_OPERATIONS_H_INCLUDED
#include <stdio.h>
#include "matrix_abc.h"

/** Печатает матрицу m */
void matrix_print (const matrix *m);


/** Присваивание матрицы m2 в матрицу m1
 *  Если размеры не совпадают, то размер матрицы m1 будет изменён
 *  Возвращает новую m1 или NULL, если не удалось изменить размер m1
 */
matrix * matrix_assign (matrix *m1, const matrix *m2);


/** Возваращет 1, если матрицы m1 и m2 равны, иначе - 0 */
int matrix_equal(const matrix *m1, const matrix *m2);


/** Выполняет m1 += m2
 *  Возвращает новую m1 или NULL, если размеры матриц не совпадают
 */
matrix * matrix_add (matrix *m1, const matrix *m2);


/** Записывает в m сумму матриц m1 и m2
 *  Возвращает m или NULL, если m1 и m2 разных размеров или не удалось изменить размер m
 *  Изменяет размер m, если нужно
 */
matrix * matrix_sum (matrix *m, const matrix *m1, const matrix *m2);


/** Выполняет m1 -= m2
 *  Возвращает новую m1 или NULL, если размеры матриц не совпадают
 */
matrix * matrix_subtr (matrix *m1, const matrix *m2);


/** Записывает в m разность матриц m1 и m2
 *  Возвращает m или NULL, если m1 и m2 разных размеров или не удалось изменить размер m
 *  Изменяет размер m, если нужно
 */
matrix * matrix_dif (matrix *m, const matrix *m1, const matrix *m2);


/** Выполняет m1 *= m2
 *  Изменяет размер матрицы m1
 *  Возвращает новоую m1 или NULL, если количество столбцов m1 и строк m2 разное или не удалось выделить память
 */
matrix * matrix_multipl (matrix *m1, const matrix *m2);


/** Умножение матрицы m на скаляр scalar
 *  Возвращает новую m
 */
matrix * matrix_multipl_scal (matrix *m, double scalar);


/** Транспонирует прямоугольную матрицу m
 *  Возвращает новую m или NULL, если не удалось изменить её размер
 */
matrix * matrix_transp_rec(matrix *m);


/** Транспонирует квадратную матрицу m
 *  Возвращает новую m
 */
matrix * matrix_transp_squ(matrix *m);


/** Транспонирует любую матрицу m
 *  Возвращает транспонированную матрицу или NULL, если создание новой матрицы не удалось
 *  Требуется вызов matrix_free, чтобы освободить транспонированную матрицу
 */
matrix * matrix_transp(const matrix *m);


/** Умножение строки i на число x в матрице m
 *  Нумерация строк с 0
 *  Возвращает новую m
 */
matrix * matrix_str_multipl (matrix *m, size_t i, double x);


/** Прибавление к строке i1 строки i2 в матрице m
 *  Нумерация строк с 0
 *  Возвращает новую m
 */
matrix * matrix_str_add (matrix *m, size_t i1, size_t i2);


/** Перестановка строк i1 и i2 в матрице m
 *  Нумерация строк с 0
 *  Возвращает новую m
 */
matrix * matrix_str_swop (matrix *m, size_t i1, size_t i2);


/** Выделение подматрицы из m2 в m1 с количеством строк - h, столбцов - w
 *  Изменяет размер m1, если нужно
 *  Возврращает подматрицу или NULL, если не удалось изменить размер
 */
matrix * matrix_submatrix (matrix *m1, const matrix *m2, size_t h, size_t w);


/** Возвращает норму матрицы m (максимум суммы модулей элементов строки по всем строкам) */
double matrix_norm (const matrix *m);


/** Возвращает определитель матрицы m или не число, если
 *  матрица не квадтратная или не удалось выделение памяти
 */
double matrix_det (const matrix *m);

#endif // MATRIX_OPERATIONS_H_INCLUDED
