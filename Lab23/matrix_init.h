#ifndef MATRIX_INIT_H_INCLUDED
#define MATRIX_INIT_H_INCLUDED
#include <stdio.h>
#include "matrix_abc.h"

/** ��������� ������� m ������
 *  ���������� ��������� �� ����������� �������
 */
matrix * matrix_set_zero (matrix *m);


/** ������ ������� � ��������� � ������
 *  h - ���������� �����, w - ���������� ��������
 *  ���������� ��������� �� ������� ��� NULL, ���� ��������� ������ �� �������
 *  ��������� ����� matrix_free, ����� ���������� �������
 */
matrix * matrix_alloc_zero (size_t h, size_t w);


/** ������ �� m ��������� �������
 *  ���������� m ��� NULL, ���� ������� �� ����������
 */
matrix * matrix_set_identity (matrix *m);


/** ������ ��������� �������
 *  s - ���������� ����� � ��������
 *  ���������� ��������� �� ������� ��� NULL, ���� ��������� ������ �� �������
 *  ��������� ����� matrix_free, ����� ���������� �������
 */
matrix * matrix_alloc_identity (size_t s);


/** �������� ������� m
 *  ���������� ��������� �� ������ ������� ��� NULL, ���� ��������� ������ �� �������
 *  ��������� ����� matrix_free, ����� ���������� �����
 */
matrix * matrix_clone (const matrix *m);

#endif // MATRIX_INIT_H_INCLUDED
