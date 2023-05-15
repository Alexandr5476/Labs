#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <stdio.h>

struct matrix;
typedef struct matrix matrix;


/** Создание матрици
 *  h - количество строк, w - количество столбцов
 *  Возвращает указатель на матрицу или NULL, если выделение памяти не удалось
 *  Требуется вызов matrix_free, чтобы освободить матрицу
 */
matrix * matrix_alloc (size_t h, size_t w);


/** Освобождение матрицы */
void matrix_free (matrix *m);


/** Изменение размера матрицы без сохранения значений элементов
 *  m - указатель на матрицу, h - новое количество строк, w - новое количество столбцов
 *  Возвращает m или NULL, если выделение памяти не удалось
 */
matrix * matrix_resize (matrix *m, size_t h, size_t w);


/** Доступ к элементу матрицы по индексу (нумерация с 0)
 *  m - указатель на матрицу, i - номер строки, j - номер столбца
 *  Возвращает указатель на элемент
 */
double * matrix_get (matrix *m, size_t i, size_t j);


/** Доступ к элементу матрицы по индексу (нумерация с 0)
 *  m - указатель на матрицу, i - номер строки, j - номер столбца
 *  Возвращает константный указатель на элемент
 */
const double * matrix_cget (const matrix *m, size_t i, size_t j);


/** Возвращает количество строк в матрице m */
size_t matrix_height (const matrix *m);


/** Возвращает количество столбцов в матрице m */
size_t matrix_width (const matrix *m);

#endif // MATRIX_H_INCLUDED
