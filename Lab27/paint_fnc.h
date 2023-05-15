#ifndef PAINT_FNC_H_INCLUDED
#define PAINT_FNC_H_INCLUDED
#include <stdio.h>
#include "rb_tree.h"

#define MY_LIGHTGREEN (_getabsolutecolor(_LIGHTGREEN))


/** ���������� ������ ������ � ���������� ����������� ���������� ����� � ���� pos (��������� rb_node)
 *  n - ��������� �� ����, ������� ��������� �� ������� ���� ��������, pos - ��� ����������,
 *  beg, end - ��������� (������ ������ � ������� ����������� ��������� �����) ��� ���������� ������� ���������� ����
 */
void rb_paint_req (rb_node *n, place pos, size_t beg, size_t end);


/** ������� ����� � ������ ������, ���� ��� �� ������
 *  t - ��������� �� ������, tree_pos - ���������� �����
 */
void rb_paint (rb_tree *t, place tree_pos);


/** �������� ����� ������ ���� ������ � ������������ pos
 *  ��� 1 �������
 */
void rb_select(place pos);


/** �������� ����� ������ ���� n � ����� ������ ��������, ���� �� ����
 *  ��� 0,7 �������
 */
void rb_select_insert (const rb_node *n);


/** ������ ��������� ������ ������ ���� � ������������ pos
 *  ��� 4 �������
 */
void rb_select_rotate_right (place pos);


/** ������ ������� ����� ������ ���� � ������������ pos
 *  ��� 4 �������
 */
void rb_select_rotate_left (place pos);


/** ������� ����� �� ����� ���� ������ �� ���� � ������������ x, y
 *  str1 - ��������� �� ������ ������ ������, str2 - ��������� �� ������ ������ ������ (����� ���� NULL)
 *  ��� 5 ������, ���� ������ ������ ����, ����� 2 �������
 */
void rb_text_right (int x, int y, const char *str1, const char *str2);


/** ������� ����� �� ����� ���� ����� �� ���� � ������������ x, y
 *  str1 - ��������� �� ������ ������ ������, str2 - ��������� �� ������ ������ ������ (����� ���� NULL)
 *  ��� 5 ������, ���� ������ ������ ����, ����� 2 �������
 */
void rb_text_left (int x, int y, const char *str1, const char *str2);


/** �������� ������� rb_select � ���������� pos,
 *  ����� rb_text_right � ����������� pos.x, pos.y, str1, str2
 */
void rb_stext_right (place pos, const char *str1, const char *str2);


/** �������� ������� rb_select � ���������� pos,
 *  ����� rb_text_left � ����������� pos.x, pos.y, str1, str2
 */
void rb_stext_left (place pos, const char *str1, const char *str2);


/** ������� ����� 'x' ����� �� ���� x, ���� �� ����� ������
 *  ������, ���� �� ������ ��� ������ ������
 */
void rb_inscr_x (const rb_node *x);


/** ������� ����� 'x' ������ �� ���� x, ���� �� ����� ������
 *  �����, ���� �� ������ ��� ������ ������
 */
void rb_inscr_x2 (const rb_node *x);


/** ������������� (������ �� �������) ���� n � ���� new_color � �������� ��� ������ ������
 *  ��� 1,3 ������
 *  ������ ������������� NIL-����
 */
void rb_select_repaint (const rb_node *n, int new_color);


/** ���������� ����������� ������� � ������ t ��� NULL, ���� ������ ������
 *  �������� ���� ������
 */
rb_node * rb_paint_min (rb_tree *t);


/** �������� (������ �� �������) ���� �� ���� n_old � ���� n_new
 *  ������ ������� �� ������� ���� � ������ � �������� ����� ���� ������ ������
 *  ��� 1,3 �������
 */
void rb_select_copy (const rb_node *n_old, const rb_node *n_new);


/** ������ ������ ����� ������ ���� � ������������ pos */
void rb_select_double_black (place pos);


#endif // PAINT_FNC_H_INCLUDED
