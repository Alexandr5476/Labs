#ifndef RB_TREE_H_INCLUDED
#define RB_TREE_H_INCLUDED
#include <stdio.h>


typedef struct
{
    int x, y;
} place;

/** ���� �����
 *  RB_NIL ������������ ������ ���� ��� � ������� ��������
 *  ������������� ����������������� NIL-����, ����� ��� ����������
 */
typedef enum {RB_RED, RB_BLACK, RB_NIL} rb_color;


typedef int key_t; /// ��� ����� key_t


typedef struct rb_node /// ���� ������
{
    key_t    key;
    rb_color color;
    /* ��������� �� ����� � ������ ���������, NULL ���� ��� nil-����;
     * ��������� �� ������������ �������, NULL ��� �����
     */
    struct rb_node *left, *right, *parent;
    place pos; // ���������� ������ ����; ����������� �� ����� ���������
} rb_node;


typedef struct rb_tree /// ������
{
    rb_node *root; /* NULL ��� ������� ������ �� ������ nil-���� */
} rb_tree;


/** �������� ������
 *  ���������� ��������� �� ���� ��� NULL, ���� ������ �� ����������
 */
rb_tree *rb_alloc();


/** ����������� ������� ����������� ���� � ������ ���� */
void rb_node_clear (rb_node *n);

/** �������� ������ �� ������ */
void rb_free(rb_tree *t);


/** ����� ����� � ������
 *  ���������� ��������� �� ���� � ������ ��� NULL, ���� ����� � ������ ���
 */
rb_node * rb_search (rb_tree *t, key_t key);


/** ����� ������������ ����� � ������
 *  ���������� ��������� �� ���� � ����������� ������
 */
rb_node * rb_min (rb_tree *t);


/** ����� ������������� ����� � ������
 *  ���������� ��������� �� ���� � ������������ ������
 */
rb_node * rb_max (rb_tree *t);


/** ����������� ������ ������ ��� ���������
 *  n - ��������� �� ����, ������� � �������� ���� ���������� ������
 *  ���������� ������ (0, ���� n - NULL)
 */
size_t rb_hight (rb_node *n);


/** ����� �������� ������ t ������ ���� x */
void rb_rotate_left (rb_tree *t, rb_node *x);


/** ������ �������� ������ t ������ ���� x */
void rb_rotate_right (rb_tree *t, rb_node *x);


/** ������� �������� � ������ key � ������ t ��� � ������� ������ ������
 *  ���������� ��������� �� ����������� ������� ��� NULL � ������ �������
 *  ������������� ����� ���������, ���������� NULL ���� ���� ������������
 */
rb_node *rb_bst_insert (rb_tree *t, key_t key);


/** ������� �������� � ������ key s � ������ t
 *  ���������� 0 � ������ ������, ��������� �������� � ������ �������
 */
int rb_insert (rb_tree *t, key_t key);


/** �������� �������� � ������ key �� ������ t
 *  ���������� 0, ���� ������� ������, ��������� ��������, ���� �������� ���
 */
int rb_delete (rb_tree *t, key_t key);


/** ������ ������ */
void rb_print(const rb_node *t);


#endif // RB_TREE_H_INCLUDED
