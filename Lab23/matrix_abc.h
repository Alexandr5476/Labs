#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <stdio.h>

struct matrix;
typedef struct matrix matrix;


/** �������� �������
 *  h - ���������� �����, w - ���������� ��������
 *  ���������� ��������� �� ������� ��� NULL, ���� ��������� ������ �� �������
 *  ��������� ����� matrix_free, ����� ���������� �������
 */
matrix * matrix_alloc (size_t h, size_t w);


/** ������������ ������� */
void matrix_free (matrix *m);


/** ��������� ������� ������� ��� ���������� �������� ���������
 *  m - ��������� �� �������, h - ����� ���������� �����, w - ����� ���������� ��������
 *  ���������� m ��� NULL, ���� ��������� ������ �� �������
 */
matrix * matrix_resize (matrix *m, size_t h, size_t w);


/** ������ � �������� ������� �� ������� (��������� � 0)
 *  m - ��������� �� �������, i - ����� ������, j - ����� �������
 *  ���������� ��������� �� �������
 */
double * matrix_get (matrix *m, size_t i, size_t j);


/** ������ � �������� ������� �� ������� (��������� � 0)
 *  m - ��������� �� �������, i - ����� ������, j - ����� �������
 *  ���������� ����������� ��������� �� �������
 */
const double * matrix_cget (const matrix *m, size_t i, size_t j);


/** ���������� ���������� ����� � ������� m */
size_t matrix_height (const matrix *m);


/** ���������� ���������� �������� � ������� m */
size_t matrix_width (const matrix *m);

#endif // MATRIX_H_INCLUDED
