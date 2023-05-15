#include "rb_tree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

rb_tree *rb_alloc()
{
    rb_tree *r = malloc (sizeof(rb_tree));
    if (!r) return NULL;

    r->root = NULL;
    return r;
}

void rb_node_clear (rb_node *n)
{
    if (!n) return;
    rb_node_clear (n->left);
    rb_node_clear (n->right);
    free(n);
}

void rb_free(rb_tree *t)
{
    rb_node_clear (t->root);
    free(t);
}

rb_node * rb_search (rb_tree *t, key_t key)
{
    rb_node *x = t->root;

    while (x)
    {
        if      (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else return x;
    }

    return NULL;
}

rb_node * rb_min (rb_tree *t)
{
    rb_node *x = t->root;
    if (!x) return NULL;
    while (x->left) x = x->left;
    return x;
}

rb_node * rb_max (rb_tree *t)
{
    rb_node *x = t->root;
    if (!x) return NULL;
    while (x->right) x = x->right;
    return x;
}

size_t rb_hight (rb_node *n)
{
    if (!n) return 0;
    size_t a = rb_hight(n->left), b = rb_hight(n->right);
    return (1 + (a > b ? a : b));
}

void rb_rotate_left (rb_tree *t, rb_node *x)
{
    rb_node *y = x->right;         /* ������� ����� ������ ���������                         */
    assert (y);                    /* �������� ����������� ��������, ���������               */
                                   /* ������������ �������� �� ������ ���������� ����������� */

    x->right = y->left;            /* ����� ������� y ���������� ������ �������� x           */
    if (y->left)
        y->left->parent = x;       /* ���� ��� ���������� ����, ��������������� ��� �������� */

    if (!x->parent)                /* ���� ������� ������ �����                              */
        t->root = y;               /* ���������� ����� ������                                */
    else                           /* ���� ������� �� ������ �����                           */
    {
        if (x == x->parent->left)  /* ���� x - ����� �������                                 */
            x->parent->left = y;   /* y ���������� ����� ���������� �������� ����� ��������  */
        else                       /* ���� x - ������ �������                                */
            x->parent->right = y;  /* y ���������� ������ ���������� �������� ����� �������� */

    }
    y->parent = x->parent;         /* ��������� �������� y                                   */

    y->left = x;                   /* x ���������� ����� �������� y,                         */
    x->parent = y;                 /* � y - ��������� x                                      */
}

void rb_rotate_right (rb_tree *t, rb_node *x)
{
    rb_node *y = x->left;          /* ������� ����� ������ ���������                         */
    assert (y);                    /* �������� ����������� ��������, ���������               */
                                   /* ������������ �������� �� ������ ���������� ����������� */

    x->left = y->right;            /* ������ ������� y ���������� ����� �������� x           */
    if (y->right)
        y->right->parent = x;      /* ���� ��� ���������� ����, ��������������� ��� �������� */

    if (!x->parent)                /* ���� ������� ������ �����                              */
        t->root = y;               /* ���������� ����� ������                                */
    else                           /* ���� ������� �� ������ �����                           */
    {
        if (x == x->parent->left)  /* ���� x - ����� �������                                 */
            x->parent->left = y;   /* y ���������� ����� ���������� �������� ����� ��������  */
        else                       /* ���� x - ������ �������                                */
            x->parent->right = y;  /* y ���������� ������ ���������� �������� ����� �������� */

    }
    y->parent = x->parent;         /* ��������� �������� y                                   */

    y->right = x;                  /* x ���������� ������ �������� y,                        */
    x->parent = y;                 /* � y - ��������� x                                      */
}

rb_node *rb_bst_insert (rb_tree *t, key_t key)
{
    rb_node *y = NULL, *x = t->root,
            *z = malloc (sizeof(rb_node)); /* ����������� ����                      */
    if (!z) return NULL;

    z->key   = key;
    z->color = RB_RED;                     /* ����������� ���� - �������            */
    z->left  = z->right   = NULL;

    while (x)
    {
        y = x;
        if (z->key == x->key)              /* ���� ��� ������������                 */
        {
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

int rb_insert (rb_tree *t, key_t key)
{
    rb_node *x = rb_bst_insert(t, key);
    if (!x) return 1;

    /* �������� ���� � ���� x ������� ��������:
     * ��������� x ������������ ����� �� ����� ��� ���� � ������ ���������
     */
    while (x != t->root && x->parent->color == RB_RED)
    {
        /* ������� ���� � ����������� �� ����, �������� �� �������� x
         * ������ ��� ����� �������� ������ ��������
         */
        rb_node *y = x->parent == x->parent->parent->left ? x->parent->parent->right
                                                          : x->parent->parent->left;

        if (y && y->color == RB_RED)              /* ������ "������� ����"                         */
        {
            x->parent->color         = RB_BLACK;  /* ����������                                    */
            y->color                 = RB_BLACK;
            x->parent->parent->color = RB_RED;
            x = x->parent->parent;             /* ����������� x �����                           */
                                               /* ( ������� ����, ��� ��� �������� x - �������, */
                                               /*   � ������ ����� �������� )                   */
        }
        else                                   /* ������ "������ ����"                          */
        {
            if (x->parent == x->parent->parent->left && x == x->parent->right)
            {   /* ������ x - ������ �������, � ��� �������� - �����                            */
                x = x->parent;
                rb_rotate_left(t, x);
            }
            else if (x->parent == x->parent->parent->right && x == x->parent->left)
            {   /* ������ x - ����� �������, � ��� �������� - ������     */
                x = x->parent;
                rb_rotate_right(t, x);
            }

            /* ������, ����� ���� �� ������� x � x � ����� �����������  */
            x->parent->color         = RB_BLACK; /* ���������� */
            x->parent->parent->color = RB_RED;
            /* �������� ������ ������� � ����������� �� ����,
             * � ����� ����������� ���� �� ������� � x
             */
            x == x->parent->left ? rb_rotate_right(t, x->parent->parent)
                                 : rb_rotate_left (t, x->parent->parent);
        }
    }

    t->root->color = RB_BLACK;   /* ��������� ������� ������� ����� */
    return 0;
}

int rb_delete (rb_tree *t, key_t key)
{
    rb_node *x, *y, *z = t->root, *n = NULL;

    /* ��� 1 - �������� �������� �� ������ ������ */

    while (z && z->key != key)
        z = key < z->key ? z->left      /* ���������� �� ����� ����� ��� ������  */
                         : z->right;    /* � ����������� �� �����                */

    if (!z) return -1;                  /* ������� �� ������                     */

    /* ������� ���� y, ������� ����� ���������� ������ �� ������ */
    if (!z->left || !z->right)
         y = z;
    else
    {
        rb_tree r;
        r.root = z->right;
        y = rb_min (&r);

        z->key  = y->key;                /* �������� ����                        */
    }

    /* ������� ������������� ������� ���������� ���������� ���� */

    x = y->left ? y->left : y->right;

    if (!x) /* ���� x - NIL-����, ������������� ��� */
    {
        n         = malloc(sizeof(rb_node));
        n->color  = RB_BLACK;
        x         = n;
    }

    x->parent = y->parent;               /* x ����� ����� �������� �������� y   */

    if (!y->parent)                      /* ���� ��������� ������               */
        t->root = x;                     /* ������������� ������                */
    else                                 /* ����� ��������� ����� �������       */
    {                                    /* �������� ���������� ����            */
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    if (y->color == RB_BLACK)            /* ���� ������ ������ �������,         */
    {                                    /* ���� ������������ RB-��������       */
        /* x ����������� "������ ������ ��������", ��� ��������� � ������
         * x ������ ����� ��������� �� ������ ������ �������, ���������� ����� �� �����
         *   ��� ���� �� �������� ������� ��������
         */
        while (x != t->root && x->color == RB_BLACK)
        {
            rb_node *w = x == x->parent->left ? x->parent->right /* w - ����    */
                                              : x->parent->left; /* ������� x   */

            if (w->color == RB_RED)                   /* ������ "���� - �������"   */
            {
                w->color         = RB_BLACK;          /* ����������                */
                x->parent->color = RB_RED;

                if (x == x->parent->left)          /* ������ ������� � ����� w  */
                {                                  /* � ����������� �� ����,    */
                    rb_rotate_left(t, x->parent);  /* ����� ��� ������ �������� */
                    w = x->parent->right;          /* �������� x                */
                }
                else
                {
                    rb_rotate_right(t, x->parent);
                    w = x->parent->left;
                }
            }
            if ((!w->left  || w->left->color  == RB_BLACK) &&
                (!w->right || w->right->color == RB_BLACK)
               )                                   /* ������ "��� ���������� --- ������"     */
            {                                      /* � �.�. NIL-���� ��������� ������       */
                w->color = RB_RED;                 /* ���������� � ����� x                   */
                x = x->parent;                     /* ��������� ������� �������� x           */
                if (x->color == RB_RED)            /* ���� �� ��� ������� - ���������� ����� */
                {
                    x->color = RB_BLACK;
                    x = t->root;
                }
            }
            else
            {
                if ((x == x->parent->left  && (!w->right || w->right->color == RB_BLACK)) ||
                    (x == x->parent->right && (!w->left  || w->left->color  == RB_BLACK))
                   ) /* ������ "��������������� ��������� ������" */
                {
                    w->color = RB_RED;
                    if (x == x->parent->left)
                    {
                        w->left->color = RB_BLACK;
                        rb_rotate_right(t, w);
                        w = x->parent->right;
                    }
                    else
                    {
                        w->right->color = RB_BLACK;
                        rb_rotate_left(t, w);
                        w = x->parent->left;
                    }
                }
                /* ������ "������� ��������� ������" */
                w->color         = x->parent->color;
                x->parent->color = RB_BLACK;

                if (x == x->parent->left)
                {
                    w->right->color = RB_BLACK;
                    rb_rotate_left(t, x->parent);
                }
                else
                {
                    w->left->color = RB_BLACK;
                    rb_rotate_right(t, x->parent);
                }

                x = t->root;   /* ����� �� ����� */
            }
        }

        x->color = RB_BLACK;
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
            else
                n->parent->right = NULL;
        }
        free (n);
    }
    return 0;
}

void rb_print(const rb_node *t)
{
    if (t)
    {
        rb_print(t->left);

        printf ("%i - %s", t->key, t->color == RB_RED ? "RED" : "BLACK");
        if (t->parent) printf(", parent = %i", t->parent->key); else printf(", root");
        if (t->left) printf(", left = %i", t->left->key);
        if (t->right) printf(", right = %i", t->right->key);
        printf ("\n");

        rb_print(t->right);
    }
}

