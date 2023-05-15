#ifndef PAINT_H_INCLUDED
#define PAINT_H_INCLUDED
#include <stdio.h>
#include "rb_tree.h"


/** ������ ���� �����, ��� ������� rb_bst_insert (���� rb_tree.h)
 *  �� ����� �������� ���� �� ����� � ����� ������� ����
 *  ���� ���� � ������ key ��� ��� � ������, �� ������� �� ���� ��������� ����� ����
 */
rb_node *rb_paint_bst_insert (rb_tree *t, key_t key);


/** ������ ���� �����, ��� ������� rb_insert (���� rb_tree.h)
 *  �� ����� ������������� ��������� �������
 */
int rb_paint_insert (rb_tree *t, key_t key, place tree_pos);


/** ������ ���� �����, ��� ������� rb_delete (���� rb_tree.h)
 *  �� ����� ������������� ��������� ��������
 */
int rb_paint_delete (rb_tree *t, key_t key, place tree_pos);


#endif // PAINT_H_INCLUDED
