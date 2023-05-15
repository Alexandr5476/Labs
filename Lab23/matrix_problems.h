#ifndef MATRIX_PROBLEMS_H_INCLUDED
#define MATRIX_PROBLEMS_H_INCLUDED
#include <stdio.h>
#include "matrix_abc.h"

/** ������ ������� �������� ��������� ������� ������
 *  m - ������� �������������, m_right - ������� ������ ������, answer - ������� ��� ������ ������
 *  ���������� answer ��� NULL, ���� �� ������� �������� ������, ��� ������� �� ��������,
 *  ��� ������� �� ����������� �������
 */
matrix * matrix_gauss_method (const matrix *m, const matrix *m_right, matrix *answer);


/** �������� ������� m
 *  ���������� �������� ������� ��� NULL, ���� ������� �� �������� ��� �� ������� �������� ������
 *  ��������� ����� matrix_free, ����� ���������� �������
 */
matrix * matrix_inverse(const matrix *m);


/** ���������� ��������� ���������� ������� m
 *  ��� NULL, ���� ������� �� ���������� ��� �� ������� �������� ������
 *  ��������� ����� matrix_free, ����� ���������� �������
 */
matrix * matrix_exp(const matrix *m);

#endif // MATRIX_PROBLEMS_H_INCLUDED
