#ifndef SAVING_H_INCLUDED
#define SAVING_H_INCLUDED
#include "database.h"

/** ��������� ���� ������ list �� �����, ���������� � ������� ������� saving
 *  filename - ��� �����, �� �������� ���������
 *  ���������� 1 � ������ ������, ����� 0
 */
int loading (dtb *list, const char *filename);


/** ��������� � ���� � ������ filename ������ �� ���� ������ list */
void saving (dtb list, const char *filename);

#endif // SAVING_H_INCLUDED
