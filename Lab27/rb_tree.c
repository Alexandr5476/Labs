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
    rb_node *y = x->right;         /* находим новый корень поддерева                         */
    assert (y);                    /* проверка возможности вращения, отладочно               */
                                   /* недопустимое вращение не должно вызываться алгоритмами */

    x->right = y->left;            /* левый потомок y становится правым потомком x           */
    if (y->left)
        y->left->parent = x;       /* если это внутренний узел, устанавливается его родитель */

    if (!x->parent)                /* если поворот вокруг корня                              */
        t->root = y;               /* установили новый корень                                */
    else                           /* если поворот не вокруг корня                           */
    {
        if (x == x->parent->left)  /* если x - левый ребенок                                 */
            x->parent->left = y;   /* y становится левым поддеревом родителя точки вращения  */
        else                       /* если x - правый ребенок                                */
            x->parent->right = y;  /* y становится правым поддеревом родителя точки вращения */

    }
    y->parent = x->parent;         /* установка родителя y                                   */

    y->left = x;                   /* x становится левым потомком y,                         */
    x->parent = y;                 /* а y - родителем x                                      */
}

void rb_rotate_right (rb_tree *t, rb_node *x)
{
    rb_node *y = x->left;          /* находим новый корень поддерева                         */
    assert (y);                    /* проверка возможности вращения, отладочно               */
                                   /* недопустимое вращение не должно вызываться алгоритмами */

    x->left = y->right;            /* правый потомок y становится левым потомком x           */
    if (y->right)
        y->right->parent = x;      /* если это внутренний узел, устанавливается его родитель */

    if (!x->parent)                /* если поворот вокруг корня                              */
        t->root = y;               /* установили новый корень                                */
    else                           /* если поворот не вокруг корня                           */
    {
        if (x == x->parent->left)  /* если x - левый ребенок                                 */
            x->parent->left = y;   /* y становится левым поддеревом родителя точки вращения  */
        else                       /* если x - правый ребенок                                */
            x->parent->right = y;  /* y становится правым поддеревом родителя точки вращения */

    }
    y->parent = x->parent;         /* установка родителя y                                   */

    y->right = x;                  /* x становится правым потомком y,                        */
    x->parent = y;                 /* а y - родителем x                                      */
}

rb_node *rb_bst_insert (rb_tree *t, key_t key)
{
    rb_node *y = NULL, *x = t->root,
            *z = malloc (sizeof(rb_node)); /* вставляемый узел                      */
    if (!z) return NULL;

    z->key   = key;
    z->color = RB_RED;                     /* вставляемый узел - красный            */
    z->left  = z->right   = NULL;

    while (x)
    {
        y = x;
        if (z->key == x->key)              /* ключ уже присутствует                 */
        {
            free(z);
            return NULL;
        }

        x = z->key < x->key ? x->left      /* Спускаемся до листа влево или вправо  */
                            : x->right;    /* в зависимости от ключа item           */
    }

    z->parent = y;
    if (!y)                                /* Если вставляли в корень               */
        t->root = z;
    else
    {
        if (z->key < y->key)               /* Левым или правым ребенком будет z?    */
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

    /* Проблема если у узла x красный родитель:
     * указатель x перемещается вверх до корня или узла с черным родителем
     */
    while (x != t->root && x->parent->color == RB_RED)
    {
        /* находим дядю в зависимости от того, является ли родитель x
         * правый или левым ребенком своего родителя
         */
        rb_node *y = x->parent == x->parent->parent->left ? x->parent->parent->right
                                                          : x->parent->parent->left;

        if (y && y->color == RB_RED)              /* случай "красный дядя"                         */
        {
            x->parent->color         = RB_BLACK;  /* перекраска                                    */
            y->color                 = RB_BLACK;
            x->parent->parent->color = RB_RED;
            x = x->parent->parent;             /* перемещение x вверх                           */
                                               /* ( дедушка есть, так как родитель x - красный, */
                                               /*   а значит имеет родителя )                   */
        }
        else                                   /* случай "черный дядя"                          */
        {
            if (x->parent == x->parent->parent->left && x == x->parent->right)
            {   /* случай x - правый ребенок, а его родитель - левый                            */
                x = x->parent;
                rb_rotate_left(t, x);
            }
            else if (x->parent == x->parent->parent->right && x == x->parent->left)
            {   /* случай x - левый ребенок, а его родитель - правый     */
                x = x->parent;
                rb_rotate_right(t, x);
            }

            /* случай, когда путь от дедушки x к x в одном направлении  */
            x->parent->color         = RB_BLACK; /* перекраска */
            x->parent->parent->color = RB_RED;
            /* вращение вокруг дедушки в зависимости от того,
             * в каком направлении путь от дедушки к x
             */
            x == x->parent->left ? rb_rotate_right(t, x->parent->parent)
                                 : rb_rotate_left (t, x->parent->parent);
        }
    }

    t->root->color = RB_BLACK;   /* поддержка условия черноты корня */
    return 0;
}

int rb_delete (rb_tree *t, key_t key)
{
    rb_node *x, *y, *z = t->root, *n = NULL;

    /* Шаг 1 - удаление элемента из дерева поиска */

    while (z && z->key != key)
        z = key < z->key ? z->left      /* Спускаемся до листа влево или вправо  */
                         : z->right;    /* в зависимости от ключа                */

    if (!z) return -1;                  /* элемент не найден                     */

    /* находим узел y, который будет фактически удален из дерева */
    if (!z->left || !z->right)
         y = z;
    else
    {
        rb_tree r;
        r.root = z->right;
        y = rb_min (&r);

        z->key  = y->key;                /* копируем ключ                        */
    }

    /* находим единственного потомка фактически удаляемого узла */

    x = y->left ? y->left : y->right;

    if (!x) /* если x - NIL-узел, актуализируем его */
    {
        n         = malloc(sizeof(rb_node));
        n->color  = RB_BLACK;
        x         = n;
    }

    x->parent = y->parent;               /* x будет новым ребенком родителя y   */

    if (!y->parent)                      /* если удаляется корень               */
        t->root = x;                     /* устанавливаем корень                */
    else                                 /* иначе удаляется новый ребенок       */
    {                                    /* родителя удаленного узла            */
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    if (y->color == RB_BLACK)            /* Если удален черный элемент,         */
    {                                    /* надо восстановить RB-свойства       */
        /* x объявляется "дважды черной вершиной", без отражения в памяти
         * x всегда будет указывать на дважды черную вершину, поднимаясь вверх до корня
         *   или пока не окажется красной вершиной
         */
        while (x != t->root && x->color == RB_BLACK)
        {
            rb_node *w = x == x->parent->left ? x->parent->right /* w - брат    */
                                              : x->parent->left; /* вершины x   */

            if (w->color == RB_RED)                   /* случай "брат - красный"   */
            {
                w->color         = RB_BLACK;          /* перекраска                */
                x->parent->color = RB_RED;

                if (x == x->parent->left)          /* нужный поворот и новый w  */
                {                                  /* в зависимости от того,    */
                    rb_rotate_left(t, x->parent);  /* левым или правым ребенком */
                    w = x->parent->right;          /* является x                */
                }
                else
                {
                    rb_rotate_right(t, x->parent);
                    w = x->parent->left;
                }
            }
            if ((!w->left  || w->left->color  == RB_BLACK) &&
                (!w->right || w->right->color == RB_BLACK)
               )                                   /* случай "оба племянники --- черные"     */
            {                                      /* в т.ч. NIL-узел считается черным       */
                w->color = RB_RED;                 /* перекраска и смена x                   */
                x = x->parent;                     /* добавляем черноту родителю x           */
                if (x->color == RB_RED)            /* если он был красный - завершение цикла */
                {
                    x->color = RB_BLACK;
                    x = t->root;
                }
            }
            else
            {
                if ((x == x->parent->left  && (!w->right || w->right->color == RB_BLACK)) ||
                    (x == x->parent->right && (!w->left  || w->left->color  == RB_BLACK))
                   ) /* случай "противоположный племянник черный" */
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
                /* случай "ближний племянник черный" */
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

                x = t->root;   /* выход из цикла */
            }
        }

        x->color = RB_BLACK;
    }

    free (y);  /* удаляем элемент из памяти */
    if (n)     /* исключаем и удаляем       */
    {
        if (n == t->root)                  /* если удалялся последний элемент */
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

