#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include <stdio.h>

typedef struct
{
    char *name; // �������� �����
    double length; // ����� �����
    int houses; // ���������� ����� �� �����
} street;

typedef struct
{
    street *street_list;
    size_t len;
} dtb;

typedef int (*fnc_comp) (const void *, const void *);

typedef double (*fnc_divide) (const street *, const street *);

typedef double (*fnc_sum) (dtb list);

typedef double (*fnc_divide_num) (const street *, double);


/** ��������� � ����� ���� ������ ����� �������
 *  list - ��������� �� ���� ������, n_name, n_length, n_houses - �������� ����� ������ ��������
 *  ������������ 0 � ������ �����, ��� 1, ���� �� ������� �������� ������
 *  ���� list->street_list - NULL � list->len - 0, �� �������� ����� ������ � ���������� ������ �������
 */
int street_insert (dtb *list, char *n_name, double n_length, int n_houses);


/** ������� �� ���� ������ list ���� ������� � �������� place
 *  ������������ 0 � ������ �����, ��� 1, ���� �� ������� �������� ������ ��� ���� �����
 */
int street_delete (dtb *list, size_t place);


/** ������� ���� ������ list
 *  ����������� NULL � ���� street_list, 0 � len
 */
void street_free (dtb *list);


/** ���������� ��������� a � b (��� ������ - street) �� ���� length
 *  ���������� 1, ���� a > b, ����� 0
 */
int cmp_length_incr (const void *a, const void *b);


/** ���������� ��������� a � b (��� ������ - street) �� ���� houses
 *  ���������� 1, ���� a > b, ����� 0
 */
int cmp_houses_incr (const void *a, const void *b);


/** ���������� ��������� a � b (��� ������ - street) �� ���� name
 *  ���������� 1, ���� a ������ � ��������, ��� b, ����� 0
 */
int cmp_name_incr (const void *a, const void *b);


/** ���������� ��������� a � b (��� ������ - street) �� ���� length
 *  ���������� 1, ���� a < b, ����� 0
 */
int cmp_length_decr (const void *a, const void *b);


/** ���������� ��������� a � b (��� ������ - street) �� ���� houses
 *  ���������� 1, ���� a < b, ����� 0
 */
int cmp_houses_decr (const void *a, const void *b);


/** ���������� ��������� a � b (��� ������ - street) �� ���� name
 *  ���������� 1, ���� a ������ � ��������, ��� b, ����� 0
 */
int cmp_name_decr (const void *a, const void *b);


/** ��������� ������ ������ ���� ������
 *  array - ��������� �� ������, len - ������ �������, size - ������ ������ �������� �������
 *  cmp - ������� ��������� ���� ��������� �������
 *  ���� cmp ���������� 1, ����� ������ ������� ������, �� ������ ����� ������������ �� �����������, ����� �� ��������
 */
void sort(void *array, size_t len, size_t size, fnc_comp cmp);


/** ���������� ������������ ������� �� ���� ������
 *  cmp - ������� ��������� ���� ��������� �� dtb.street_list , ������� ������
 *  ���������� 1, ���� a < b, ����� 0
 */
street * maximum (dtb list, fnc_comp cmp);


/** ���������� ����� ���� ���� �� ���� ������ list */
double sum_length (dtb list);


/** ���������� ��������� ���������� ����� �� ������ �� ���� ������ list */
double sum_houses (dtb list);


/** ���������� ��������� ������� ����� �� ����� houses �������� � � b */
double divide_houses (const street *a, const street *b);


/** ���������� ��������� ������� ����� �� ����� length �������� � � b */
double divide_length (const street *a, const street *b);


/** ���������� ��������� ������� ������ �� ���� houses ��������� a �� ����� b */
double divide_houses_num (const street *a, double b);


/** ���������� ��������� ������� ������ �� ���� length ��������� a �� ����� b */
double divide_length_num (const street *a, double b);

#endif // DATABASE_H_INCLUDED
