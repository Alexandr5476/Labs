#include "paint.h"
#include "rb_tree.h"
#include "paint_fnc.h"
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

rb_node *rb_paint_bst_insert (rb_tree *t, key_t key)
{
    rb_node *y = NULL, *x = t->root,
            *z = malloc (sizeof(rb_node)); /* ����������� ����                      */
    if (!z) return NULL;

    z->key   = key;
    z->color = RB_RED;                     /* ����������� ���� - �������            */
    z->left  = z->right   = NULL;

    while (x)
    {
        rb_select_insert(x); // �������� ����

        y = x;
        if (z->key == x->key)              /* ���� ��� ������������                 */
        {
            rb_stext_right(x->pos, "������� ��� ���� � ������", NULL);
            free(z);
            return NULL;
        }

        x = z->key < x->key ? x->left      /* ���������� �� ����� ����� ��� ������  */
                            : x->right;    /* � ����������� �� ����� item           */
    }

    z->parent = y;
    if (!y)                                /* ���� ��������� � ������               */
        t->root = z;
    else
    {
        if (z->key < y->key)               /* ����� ��� ������ �������� ����� z?    */
            y->left = z;
        else
            y->right = z;
    }

    return z;
}

int rb_paint_insert (rb_tree *t, key_t key, place tree_pos)
{
    rb_node *x = rb_paint_bst_insert(t, key); // ������� ��� � �������� ������ ������ � ���������� ����
    if (!x) return 1;

    rb_paint(t, tree_pos); // ���������� �������, ����� ���� ����� ����������� ����

    rb_inscr_x(x); // ������� 'x' ����� ������ ����
    rb_select(x->pos); // ��������� ���� x

    /* ����� ������ ����� �� ���� x ��� ������� ����� ��� ���� �������� ������ */
    if (!x->parent)
    {
        rb_stext_left(x->pos, "������ ������� -> ����������� � ������", NULL);
        rb_select_repaint(x, BLACK); // ���������� �� ������� (��������� ���������� � ����� �������)
    }
    else if (x->parent->color == RB_BLACK)
        rb_stext_left(x->parent->pos, "�������� ������ -> �����", NULL);

    /* �������� ���� � ���� x ������� ��������:
     * ��������� x ������������ ����� �� ����� ��� ���� � ������ ���������
     */
    while (x != t->root && x->parent->color == RB_RED)
    {
        /* ����� ������ ������ ��� ����� �� �������� x ���, ����� �� ��������� ���� x */
        if (x->parent == x->parent->parent->right)
            rb_stext_right(x->parent->pos, "�������� ������� -> ���������� ���� ����", NULL);
        else
            rb_stext_left(x->parent->pos, "�������� ������� -> ���������� ���� ����", NULL);

        /* ������� ���� � ����������� �� ����, �������� �� �������� x
         * ������ ��� ����� �������� ������ ��������
         */
        rb_node *y = x->parent == x->parent->parent->left ? x->parent->parent->right
                                                          : x->parent->parent->left;


        if (y && y->color == RB_RED)              /* ������ "������� ����" */
        {
            /* ����� ������ ������ ��� ����� �� ���� x ���, ����� �� ��������� �������� x */
            if (y == y->parent->right)
                rb_stext_right(y->pos, "���� ������� -> ����������� �������� � ���� �",
                                       "������, ������� � �������; ������� - ����� x");
            else
                rb_stext_left(y->pos, "���� ������� -> ����������� �������� � ���� �",
                                      "������, ������� � �������; ������� - ����� x");


            x->parent->color = RB_BLACK; // ����������
            rb_select_repaint(x->parent, BLACK); // ��������� ����� ���� �� �������

            y->color = RB_BLACK;
            rb_select_repaint(y, BLACK);

            x->parent->parent->color = RB_RED;
            rb_select_repaint(x->parent->parent, LIGHTRED);

            delay(3000);

            x = x->parent->parent; // ����������� x �����
            rb_paint(t, tree_pos); // ���������� �������, ����� ������ ��� ������� � ���������
            rb_inscr_x(x); // ������� 'x' ����� ������ ����
            rb_select(x->pos); // ��������� ���� x
            /* ����� ������, ���� ���� ���������� */
            if (!x->parent)
            {
                rb_stext_left(x->pos, "������ ������� -> ����-",
                                      "������� � ������; �����");
                rb_select_repaint(x, BLACK);
            }

            else if (x->parent->color == RB_BLACK)
                rb_stext_left(x->parent->pos, "�������� ������ -> �����", NULL);
        }

        else                                      /* ������ "������ ����" */
        {
            /* ����� ������ ������ ��� ����� �� ���� ��� �������� x � ����������� �� ���� ���� nil ��� ��� */
            if (y)
            {
                if (y == y->parent->right)
                    rb_stext_right(y->pos, "���� ������ -> ��������� ����-",
                                           "�������������� ���� �� �������");
                else
                    rb_stext_left(y->pos, "���� ������ -> ��������� ����-",
                                          "�������������� ���� �� �������");
            }
            else
            {
                if (x->parent == x->parent->parent->right)
                    rb_stext_left(x->parent->pos, "���� nil, �.�. ������ -> ���������",
                                                  "������������������ ���� �� �������");
                else
                    rb_stext_right(x->parent->pos, "���� nil, �.�. ������ -> ���������",
                                                   "������������������ ���� �� �������");
            }
            delay(2000);

            rb_paint(t, tree_pos); // ���������� �������, ����� ������ ��� ������� � ���������
            rb_inscr_x(x); // ������� 'x'
            /* ��������� �������, �������� � ������ x, ����� �������� ������������������ */
            rb_select(x->parent->parent->pos);
            rb_select(x->parent->pos);
            rb_select(x->pos);

            if (x->parent == x->parent->parent->left && x == x->parent->right)
            {   /* ������ x - ������ �������, � ��� �������� - ����� */

                /* ����� ������ ����� (������ ����� ����� x) */
                rb_stext_left(x->pos, "x - ������ �������, ��� �������� - �����",
                                      "-> ����� �������� ������ �������� x");

                x = x->parent;
                rb_select_rotate_left(x->pos); // ������� ����� ����� ����, ������ �������� ����� ��������
                rb_rotate_left(t, x);

                rb_paint (t, tree_pos); // ���������� �������, ����� �������� ����� ������ (����� ��������)
                rb_inscr_x(x); // ������� 'x'
                /* ��������� �������, �������� � ������ x, ����� �������� ������������������ */
                rb_select(x->parent->parent->pos);
                rb_select(x->parent->pos);
                rb_select(x->pos);
            }
            else if (x->parent == x->parent->parent->right && x == x->parent->left)
            {   /* ������ x - ����� �������, � ��� �������� - ������ */

                /* ����� ������ ������ (����� ����� ����� x) */
                rb_stext_right(x->pos, "x - ����� �������, ��� �������� - ������",
                                       "-> ������ �������� ������ �������� x");

                x = x->parent;
                rb_select_rotate_right(x->pos); // ������� ������ ����� ����, ������ �������� ����� ��������
                rb_rotate_right(t, x);

                rb_paint (t, tree_pos); // ���������� �������, ����� �������� ����� ������ (����� ��������)
                rb_inscr_x(x); // ������� 'x'
                /* ��������� �������, �������� � ������ x, ����� �������� ������������������ */
                rb_select(x->parent->parent->pos);
                rb_select(x->parent->pos);
                rb_select(x->pos);

            }

            /* ������, ����� ���� �� ������� x � x � ����� �����������  */

            /* ����� ������ ���, ����� �� ����������� ����, ������� ����� �������� ��� �������� */
            if (x == x->parent->right)
                rb_stext_left(x->pos, "������������������ ���� -> �����������",
                                      "�������� � ������, ������� � �������");
            else
                rb_stext_right(x->pos, "������������������ ���� -> �����������",
                                       "�������� � ������, ������� � �������");

            x->parent->color = RB_BLACK; // ����������
            rb_select_repaint(x->parent, BLACK); // ��������� ����� ���� �� �������

            x->parent->parent->color = RB_RED;
            rb_select_repaint(x->parent->parent, LIGHTRED);

            delay(2000);

            rb_paint(t, tree_pos); // ���������� �������, ����� ������ ��� ������� � ���������
            rb_inscr_x(x); // ������� 'x'

            /* �������� ������ ������� � ����������� �� ����,
             * � ����� ����������� ���� �� ������� � x
             */
            if (x == x->parent->left)
            {
                rb_select(x->parent->parent->pos);
                rb_select(x->parent->pos);

                rb_stext_left(x->parent->pos, "����������� ���� - ����� -> ������",
                                              "�������� ������ �������; �����");

                rb_select_rotate_right(x->parent->parent->pos); // ������� ������ ����� ����, ������ �������� ��������
                rb_rotate_right(t, x->parent->parent);

                delay(2000);
            }
            else
            {

                rb_select(x->parent->parent->pos);
                rb_select(x->parent->pos);

                rb_stext_right(x->parent->pos, "����������� ���� - ������ -> �����",
                                               "�������� ������ �������; �����");

                rb_select_rotate_left(x->parent->parent->pos); // ������� ����� ����� ����, ������ �������� ��������
                rb_rotate_left (t, x->parent->parent);

                delay(2000);
            }
        }
    }

    t->root->color = RB_BLACK;   /* ��������� ������� ������� ����� */

    return 0;
}

int rb_paint_delete (rb_tree *t, key_t key, place tree_pos)
{
    rb_node *x, *y, *z = t->root, *n = NULL;

    /* ��� 1 - �������� �������� �� ������ ������ */

    /* ���������� �� ����� ����� ��� ������ � ����������� �� ����� */
    while (z && z->key != key)
    {
        rb_select_insert(z); // �������� ����

        if (key < z->key)
        {
            if (!(z->left)) /* ���� �������� ��� */
            {
                rb_text_left(z->pos.x, z->pos.y + 35, "������� �� ������", NULL);
                return -1;
            }
            z = z->left;
        }
        else
        {
            if (!(z->right))
            {
                rb_text_right(z->pos.x, z->pos.y + 35, "������� �� ������", NULL);
                return -1;
            }
            z = z->right;
        }
    }
    rb_select_insert(z); // ���� ������� ������, �� �������� ���

    /* ������� ���� y, ������� ����� ���������� ������ �� ������ */
    if (!z->left || !z->right)
    {/* ���� ��������� ���� � ��� �������� ���������� ���������, �� ������� �����. ����� */

        if (z->left || z->right)
            rb_stext_left(z->pos, "���� ������ ���� ��������� ->",
                                  "��� ���������� ��������� ����");
        else
            rb_stext_left(z->pos, "����� ����������� ��� -> ���",
                                  "���������� ��������� ����");
        y = z;
    }
    else
    {
        rb_stext_left(z->pos, "���� ��� ��������� -> ����� ����-",
                              "������� ������� � ������ ���������");
        rb_tree r;
        r.root = z->right;
        y = rb_paint_min (&r); // ���� ����������� ������� � ������ ��������� � ���������� ����
        rb_stext_left(y->pos, "��� ���������� ��������� ���� ->",
                              "����������� ������ � ������ ����");
        rb_select_copy(y, z); // �������� ���� �� �������
        z->key = y->key; // �������� ����
    }

    if (y == t->root)
    {
        rb_stext_right(y->pos, "��������� ������ -> ������",
                               "������ ������; �����");
        free(y);
        t->root = NULL;
        return 0;
    }

    /* ������� ������������� ������� ���������� ���������� ���� */
    x = y->left ? y->left : y->right;

    if (!x) /* ���� x - NIL-����, ������������� ��� */
    {
        n         = malloc(sizeof(rb_node));
        n->color  = RB_NIL; // ����������� ����, ����� ���� ���� ����� ���� ����������
        n->left   = NULL; /* ����� ���������� ����� NULL, �����  */
        n->right  = NULL; /* ���������� �������� ��� ��������� */
        x         = n;
    }

    x->parent = y->parent;          /* x ����� ����� �������� �������� y   */

  if (!y->parent)                   /* ���� ��������� ������               */
        t->root = x;                /* ������������� ������                */
    else                            /* ����� ��������� ����� �������       */
    {                               /* �������� ���������� ����            */
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    if (y->color == RB_BLACK)
    {   /*   ���� ������ ������ �������, ���� ������������ RB-��������
         * x ����������� "������ ������ ��������", ��� ��������� � ������
         * x ������ ����� ��������� �� ������ ������ �������, ���������� ����� �� �����
         *   ��� ���� �� �������� ������� ��������
         */
        rb_stext_right(y->pos, "�������� ��������� ���� �� ���",
                               "������; ���������� ������ 'x'");

        /* ���� x - ����������������� NIL-����, �� �� ���� ����� */
        if(x->color == RB_NIL)
        {
            rb_text_left(y->pos.x, y->pos.y + 35, "������ - nil", NULL);
            delay(1400);
        }
        rb_paint(t, tree_pos); // ��������� �������, ����� ������ ������ ��� ���������� ��������
        rb_inscr_x2(x); // ������� 'x'

        while (x != t->root && x->color != RB_RED)
        {
            int l = 0;
            rb_node *w = x == x->parent->left ? x->parent->right /* w - ����    */
                                              : x->parent->left; /* ������� x   */

            /* ������� ����� ���, ����� �� ��������� ����� */
            if (x == x->parent->left)
                rb_stext_left(x->pos, "x ������ -> �������� ��� ������",
                                      "������; ���������� ���� �����");
            else
                rb_stext_right(x->pos, "x ������ -> �������� ��� ������",
                                       "������; ���������� ���� �����");

            rb_select_double_black(x->pos); // ��������� ������� ������� �� �������
            delay(1300);

            if (w->color == RB_RED)                   /* ������ "���� - �������"  */
            {
                /* ������� ����� ���, ����� �� ��������� x */
                if (w == w->parent->left)
                    rb_stext_left(w->pos, "���� ������� -> ����������� ���",
                                          "� ������, �������� � �������");
                else
                    rb_stext_right(w->pos, "���� ������� -> ����������� ���",
                                           "� ������, �������� � �������");

                w->color         = RB_BLACK; // ����������
                rb_select_repaint(w, BLACK); // ���������� �� �������

                x->parent->color = RB_RED;
                rb_select_repaint(x->parent, LIGHTRED);

                if (x == x->parent->left)          /* ������ ������� � ����� w � ����������� ��  */
                {                                  /* ����, ����� ��� ������ �������� �������� x */
                    rb_text_left(x->pos.x, x->pos.y + 35, "x - ����� ������ -> �����",
                                                          "�������� ������ ��������");
                    rb_select_rotate_left(x->parent->pos); // ������� ����� ����� ����, ������ �������� ��������
                    rb_rotate_left(t, x->parent);
                    w = x->parent->right;
                }
                else
                {

                    rb_text_right(x->pos.x, x->pos.y + 35, "x - ����� ������ -> ������",
                                                           "�������� ������ ��������");
                    rb_select_rotate_right(x->parent->pos); // ������� ������ ����� ����, ������ �������� ��������
                    rb_rotate_right(t, x->parent);
                    w = x->parent->left;
                }

                rb_paint(t, tree_pos); // ���������� ������� ����� ��������
                rb_select_double_black(x->pos); // ��������� ������� ������� �� �������
                rb_inscr_x2(x); // ������� 'x'
                ++l;
            }
            /* ���� ���� (��� ��� ����������) ������ (��������� � ������� l)
             * ������� ����� ���, ����� �� ��������� x
             */
            if (l)
            {
                if (w == w->parent->left)
                    rb_stext_left(w->pos, "������ ���� ������ ->",
                                          "���������� ���� �����������");
                else
                    rb_stext_right(w->pos, "������ ���� ������ ->",
                                           "���������� ���� �����������");
            }
            else
            {
                if (w == w->parent->left)
                    rb_stext_left(w->pos, "���� ������ -> ������-",
                                          "���� ���� �����������");
                else
                    rb_stext_right(w->pos, "���� ������ -> ������-",
                                           "���� ���� �����������");
            }
            if ((!w->left  || w->left->color  == RB_BLACK) && /* ������ "��� ���������� - ������" */
                (!w->right || w->right->color == RB_BLACK)    /* � �.�. NIL-���� ��������� ������ */
               )
            {
                /* ������� ����� � ����������� �� ����� �����������
                 * ���, ����� ������ �� ���������, � �������� ����� �� ��� �����,
                 * ����� �� ������� ������ ����� � ������
                 */
                if (w == w->parent->right)
                {
                    if (w->right)
                    {
                        if (w->left)
                        {
                            rb_select(w->left->pos);
                            rb_stext_right(w->right->pos,                        "��� ���������� ������ ->",
                                                                                 "����������� ����� � �������,");
                            rb_select_repaint(w, LIGHTRED); // ���������� �� �������
                            rb_text_right(w->right->pos.x, w->right->pos.y + 30, "������ ������� �������� ��������", NULL);
                            delay(3000);
                        }
                        else
                        {
                            rb_stext_right(w->right->pos,                        "��� ���������� ������ (�����",
                                                                                 "- nil, �.� ������) ->");
                            rb_text_right(w->right->pos.x, w->right->pos.y + 35, "����������� ����� � �������,",
                                                                                 "������ ������� �������� ��������");
                            rb_select_repaint(w, LIGHTRED); // ���������� �� �������
                            delay(2000);
                        }
                    }
                    else
                    {
                        if (w->left)
                        {
                            rb_stext_left(w->left->pos,                       "��� ���������� ������ (������",
                                                                              "- nil, �.� ������) ->");
                            rb_text_left(w->left->pos.x, w->left->pos.y + 35, "����������� ����� � �������,",
                                                                              "������ ������� �������� ��������");
                            rb_select_repaint(w, LIGHTRED); // ���������� �� �������
                            delay(2000);
                        }
                        else
                        {
                            rb_text_right(w->pos.x, w->pos.y + 35, "��� ���������� nil, �.�. ������",
                                                                   "-> ����������� ����� � �������,");
                            rb_select_repaint(w, LIGHTRED); // ���������� �� �������
                            rb_text_right(w->pos.x, w->pos.y + 65, "������ ������� �������� ��������", NULL);
                            delay(3000);
                        }
                    }
                }
                else
                {
                    if (w->right)
                    {
                        if (w->left)
                        {
                            rb_select(w->right->pos);
                            rb_stext_left(w->left->pos,                       "��� ���������� ������ ->",
                                                                              "����������� ����� � �������,");
                            rb_select_repaint(w, LIGHTRED); // ���������� �� �������
                            rb_text_left(w->left->pos.x, w->left->pos.y + 30, "������ ������� �������� ��������", NULL);
                            delay(3000);
                        }
                        else
                        {
                            rb_stext_right(w->right->pos,                        "��� ���������� ������ (�����",
                                                                                 "- nil, �.� ������) ->");
                            rb_text_right(w->right->pos.x, w->right->pos.y + 35, "����������� ����� � �������,",
                                                                                 "������ ������� �������� ��������");
                            rb_select_repaint(w, LIGHTRED); // ���������� �� �������
                            delay(2000);
                        }
                    }
                    else
                    {
                        if (w->left)
                        {
                            rb_stext_left(w->left->pos,                       "��� ���������� ������ (������",
                                                                              "- nil, �.� ������) ->");
                            rb_text_left(w->left->pos.x, w->left->pos.y + 35, "����������� ����� � �������,",
                                                                              "������ ������� �������� ��������");
                            rb_select_repaint(w, LIGHTRED); // ���������� �� �������
                            delay(2000);
                        }
                        else
                        {
                            rb_text_left(w->pos.x, w->pos.y + 35, "��� ���������� nil, �.�. ������",
                                                                  "-> ����������� ����� � �������,");
                            rb_select_repaint(w, LIGHTRED); // ���������� �� �������
                            rb_text_left(w->pos.x, w->pos.y + 65, "������ ������� �������� ��������", NULL);
                            delay(3000);
                        }
                    }
                }

                /* ���������� � ����� x */
                w->color = RB_RED;
                                                 /* ��������� ������� �������� x, ���� �� ��� ������� */
                if (x->parent->color == RB_RED)  /* - ���������� �����, � ���������� �� �� �������   */
                {
                    rb_paint(t, tree_pos); // ���������� �������
                    rb_inscr_x2(x); // ������� 'x'
                    rb_select_double_black(x->parent->pos); // ��������� ������ ������� � �������� �������� �� �������

                    rb_text_right (x->parent->pos.x, x->parent->pos.y, "�������� ������� -> ����-",
                                                                       "������� � ������; �����");
                    x->parent->color = RB_BLACK; // ����������
                    rb_select_repaint(x->parent, BLACK); // ���������� �� �������
                    x = t->root;
                }
                else
                {
                    /* ����������������� NIL-���� ������ �� �����, ������� ��������
                     * ��� �� ������, ����� �� �������� � ��������� ��������� �����
                     * (������ ������������� ����� �����)
                     */
                    if (x->color == RB_NIL)
                    {
                        if (x == x->parent->left)
                            x->parent->left = NULL;
                        else
                            x->parent->right = NULL;
                    }

                    x = x->parent;
                    rb_paint(t, tree_pos); // ���������� �������
                    rb_inscr_x2(x); // ������� 'x'
                    /* ������� �����, ���� x - ������ */
                    if (!x->parent)
                    {
                        rb_select_double_black(x->pos);
                        rb_text_right(x->pos.x, x->pos.y, "������ ������ ������ ->",
                                                          "����������� � ������; �����");
                    }
                }
            }

            else /* ���� ���� �� ����������� ������� */
            {
                int k = 0;

                if ((x == x->parent->left  && (!w->right || w->right->color == RB_BLACK)) ||
                    (x == x->parent->right && (!w->left  || w->left->color  == RB_BLACK))
                   ) /* ������ "��������������� ��������� ������" */
                {
                    w->color = RB_RED; // ���������� �����
                    /* ������ �������� � ��������� ������, � ����������� �� ���� x - ����� ��� ������ ������ */
                    if (x == x->parent->left)
                    {
                        /* ������� ����� ����� ������� ����������, ���� �� ����, ��� ����� �����
                         * ��������� ����� �� ��� �����, ����� �� ������� ������ ����� � ������
                         */
                        if (w->right)
                        {
                            rb_stext_right(w->right->pos,                        "������� ��������� �������,",
                                                                                 "��������������� - ������ ->");
                            rb_text_right(w->right->pos.x, w->right->pos.y + 35, "����������� ����� � �������,",
                                                                                 "�������� ���������� � ������");
                        }
                        else
                        {
                            rb_text_right(w->pos.x, w->pos.y + 35, "������� ��������� �������, �������-",
                                                                   "�������� ��������� nil, �.�. ������ ->");
                            rb_text_right(w->pos.x, w->pos.y + 70, "����������� ����� � �������,",
                                                                   "�������� ���������� � ������");
                        }

                        rb_select_repaint(w, LIGHTRED); // ���������� ����� �� ������� ����� ������ ������

                        w->left->color = RB_BLACK; // ���������� �������� ����������
                        rb_select_repaint(w->left, BLACK); // ���������� �� �������

                        rb_text_left(x->pos.x, x->pos.y + 35, "x - ����� ������ -> ������",
                                                              "�������� ������ �����");
                        rb_select_rotate_right(w->pos); // ������� ������ ����� ����, ������ �������� ��������
                        rb_rotate_right(t, w);

                        w = x->parent->right; // ���������� ����� ����� ��������
                    }
                    else /* x - ������ ������ */
                    {
                        if (w->left)
                        {
                            rb_stext_left(w->left->pos,                       "������� ��������� �������,",
                                                                              "��������������� - ������ ->");
                            rb_text_left(w->left->pos.x, w->left->pos.y + 35, "����������� ����� � �������,",
                                                                              "�������� ���������� � ������");
                        }
                        else
                        {
                            rb_text_left(w->pos.x, w->pos.y + 35, "������� ��������� �������, �������-",
                                                                  "�������� ��������� nil, �.�. ������ ->");
                            rb_text_left(w->pos.x, w->pos.y + 70, "����������� ����� � �������,",
                                                                  "�������� ���������� � ������");
                        }

                        rb_select_repaint(w, LIGHTRED); // ���������� ����� �� ������� ����� ������ ������

                        w->right->color = RB_BLACK; // ���������� �������� ����������
                        rb_select_repaint(w->right, BLACK); // ���������� �� �������

                        rb_text_right(x->pos.x, x->pos.y + 35, "x - ������ ������ -> �����",
                                                               "�������� ������ �����");
                        rb_select_rotate_left(w->pos); // ������� ����� ����� ����, ������ �������� ��������
                        rb_rotate_left(t, w);

                        w = x->parent->left; // ���������� ����� ����� ��������
                    }

                    rb_paint(t, tree_pos); // ���������� �������
                    rb_select_double_black(x->pos); // ��������� ������� ������� �� �������
                    rb_inscr_x2(x); // ������� 'x'
                    ++k; // ����� ������ ����� ���������� ������� ��� ���
                }

                /* ������ "��������������� ��������� �������" (���� �������� �� ����� ��������) */

                if (x == x->parent->left)
                {
                    rb_stext_right (w->right->pos, "��������������� ��������� �������,",  /* ����� ������� �� ��� */
                                                   "���� �������� �� ����� �������� ->"); /* �����, ����� �������� */
                                                                                          /* ������ ����� � ������ */
                    rb_text_right(w->right->pos.x, w->right->pos.y + 35, "����������� ����� � ���� ��������,",
                                                                         "�������� � ���������� - � ������");

                    rb_select_repaint(w, x->parent->color == RB_RED ? LIGHTRED : BLACK);

                    /* ��������� ���������� ������ ����� ������ ������ � ���������� �� ������� */
                    w->color = x->parent->color;


                    x->parent->color = RB_BLACK; // ����������
                    rb_select_repaint(x->parent, BLACK); // ���������� �� �������

                    w->right->color = RB_BLACK;
                    rb_select_repaint(w->right, BLACK);

                    /* ���� ������� ����������, �� ����� ����� ���� x �� ������ ���������� �������
                     * ����� ������ � ����� �������� ����� ����� ����
                     */
                    if (k)
                        rb_text_left(x->pos.x, x->pos.y, "x - ����� ������ -> �����",
                                                         "�������� ������ ��������; �����");
                    else
                        rb_text_left(x->pos.x, x->pos.y + 35, "x - ����� ������ -> �����",
                                                              "�������� ������ ��������; �����");
                    --k;

                    rb_select_rotate_left(x->parent->pos); // ������� ����� ����� ����, ������ �������� ��������
                    rb_rotate_left(t, x->parent);
                }
                else
                {
                    rb_stext_left(w->left->pos, "��������������� ��������� �������,",   /* ����� ������� �� ��� */
                                                 "���� �������� �� ����� �������� ->"); /* �����, ����� �������� */
                                                                                        /* ������ ����� � ������ */
                    rb_text_left(w->left->pos.x, w->left->pos.y + 35, "����������� ����� � ���� ��������,",
                                                                       "�������� � ���������� - � ������");
                    /* ��������� ���������� ������ ����� ������ ������ � ���������� �� ������� */
                    rb_select_repaint(w, x->parent->color == RB_RED ? LIGHTRED : BLACK);
                    w->color = x->parent->color;


                    x->parent->color = RB_BLACK; // ����������
                    rb_select_repaint(x->parent, BLACK); // ���������� �� �������

                    w->left->color = RB_BLACK;
                    rb_select_repaint(w->left, BLACK);

                    /* ���� ������� ����������, �� ����� ����� ���� x �� ������ ���������� �������
                     * ����� ������ � ����� �������� ����� ����� ����
                     */
                    if (k)
                        rb_text_right(x->pos.x, x->pos.y, "x - ����� ������ -> �����",
                                                          "�������� ������ ��������; �����");
                    else
                        rb_text_right(x->pos.x, x->pos.y + 35, "x - ����� ������ -> �����",
                                                               "�������� ������ ��������; �����");
                    --k;

                    rb_select_rotate_right(x->parent->pos); // ������� ������ ����� ����, ������ �������� ��������
                    rb_rotate_right(t, x->parent);
                }

                x = t->root; // ����� �� �����

            } // ����� ������ "���� �� ����������� �������"
        } // ����� �����

        /* ���� ������ ���������� ���� ��� �������, �� �����
         * ����������� ��� � ������ ��� �������������� RB-������� */
        if (x->color == RB_RED)
        {
            rb_paint(t, tree_pos); // ���������� �������
            rb_inscr_x2(x); // ������� 'x'
            delay(1500);
            if (x == x->parent->left)
                rb_stext_left(x->pos, "x - ������� -> ����-",
                                      "������� � ������; �����");
            else
                rb_stext_right(x->pos, "x - ������� -> ����-",
                                       "������� � ������; �����");
            rb_select_repaint(x, BLACK); // ���������� �� �������
        }

       x->color = RB_BLACK;

    } // ����� ������� "��������� ���� - ������"
    else
    {
        rb_stext_right(y->pos, "�������� ��������� ���� �� ���",
                               "������; ���� ������� -> �����");
        if(!y->left && !y->right)
        {
            rb_text_right(y->pos.x, y->pos.y + 35, "������ - nil", NULL);
            delay(1400);
        }
    }

    free (y);  /* ������� ������� �� ������ */
    if (n)     /* ��������� � �������       */
    {
        if (n == t->root)                  /* ���� �������� ��������� ������� */
            t->root = NULL;
        else
        {
            if (n == n->parent->left)
                n->parent->left  = NULL;
            if (n == n->parent->right)   /* ������ ������������ else, �.�. � ����� n ��� ����  */
                n->parent->right = NULL; /* ��� ������� �� ������ (����� �� �������� NIL-����) */
        }
        free (n); // ������������ ������ � ����� �� ����
    }

    return 0;
}
