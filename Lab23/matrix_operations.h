#ifndef MATRIX_OPERATIONS_H_INCLUDED
#define MATRIX_OPERATIONS_H_INCLUDED
#include <stdio.h>
#include "matrix_abc.h"

/** �������� ������� m */
void matrix_print (const matrix *m);


/** ������������ ������� m2 � ������� m1
 *  ���� ������� �� ���������, �� ������ ������� m1 ����� ������
 *  ���������� ����� m1 ��� NULL, ���� �� ������� �������� ������ m1
 */
matrix * matrix_assign (matrix *m1, const matrix *m2);


/** ���������� 1, ���� ������� m1 � m2 �����, ����� - 0 */
int matrix_equal(const matrix *m1, const matrix *m2);


/** ��������� m1 += m2
 *  ���������� ����� m1 ��� NULL, ���� ������� ������ �� ���������
 */
matrix * matrix_add (matrix *m1, const matrix *m2);


/** ���������� � m ����� ������ m1 � m2
 *  ���������� m ��� NULL, ���� m1 � m2 ������ �������� ��� �� ������� �������� ������ m
 *  �������� ������ m, ���� �����
 */
matrix * matrix_sum (matrix *m, const matrix *m1, const matrix *m2);


/** ��������� m1 -= m2
 *  ���������� ����� m1 ��� NULL, ���� ������� ������ �� ���������
 */
matrix * matrix_subtr (matrix *m1, const matrix *m2);


/** ���������� � m �������� ������ m1 � m2
 *  ���������� m ��� NULL, ���� m1 � m2 ������ �������� ��� �� ������� �������� ������ m
 *  �������� ������ m, ���� �����
 */
matrix * matrix_dif (matrix *m, const matrix *m1, const matrix *m2);


/** ��������� m1 *= m2
 *  �������� ������ ������� m1
 *  ���������� ������ m1 ��� NULL, ���� ���������� �������� m1 � ����� m2 ������ ��� �� ������� �������� ������
 */
matrix * matrix_multipl (matrix *m1, const matrix *m2);


/** ��������� ������� m �� ������ scalar
 *  ���������� ����� m
 */
matrix * matrix_multipl_scal (matrix *m, double scalar);


/** ������������� ������������� ������� m
 *  ���������� ����� m ��� NULL, ���� �� ������� �������� � ������
 */
matrix * matrix_transp_rec(matrix *m);


/** ������������� ���������� ������� m
 *  ���������� ����� m
 */
matrix * matrix_transp_squ(matrix *m);


/** ������������� ����� ������� m
 *  ���������� ����������������� ������� ��� NULL, ���� �������� ����� ������� �� �������
 *  ��������� ����� matrix_free, ����� ���������� ����������������� �������
 */
matrix * matrix_transp(const matrix *m);


/** ��������� ������ i �� ����� x � ������� m
 *  ��������� ����� � 0
 *  ���������� ����� m
 */
matrix * matrix_str_multipl (matrix *m, size_t i, double x);


/** ����������� � ������ i1 ������ i2 � ������� m
 *  ��������� ����� � 0
 *  ���������� ����� m
 */
matrix * matrix_str_add (matrix *m, size_t i1, size_t i2);


/** ������������ ����� i1 � i2 � ������� m
 *  ��������� ����� � 0
 *  ���������� ����� m
 */
matrix * matrix_str_swop (matrix *m, size_t i1, size_t i2);


/** ��������� ���������� �� m2 � m1 � ����������� ����� - h, �������� - w
 *  �������� ������ m1, ���� �����
 *  ����������� ���������� ��� NULL, ���� �� ������� �������� ������
 */
matrix * matrix_submatrix (matrix *m1, const matrix *m2, size_t h, size_t w);


/** ���������� ����� ������� m (�������� ����� ������� ��������� ������ �� ���� �������) */
double matrix_norm (const matrix *m);


/** ���������� ������������ ������� m ��� �� �����, ����
 *  ������� �� ����������� ��� �� ������� ��������� ������
 */
double matrix_det (const matrix *m);

#endif // MATRIX_OPERATIONS_H_INCLUDED
