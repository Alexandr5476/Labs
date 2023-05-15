#include "paint.h"
#include "rb_tree.h"
#include "paint_fnc.h"
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

rb_node *rb_paint_bst_insert (rb_tree *t, key_t key)
{
    rb_node *y = NULL, *x = t->root,
            *z = malloc (sizeof(rb_node)); /* вставляемый узел                      */
    if (!z) return NULL;

    z->key   = key;
    z->color = RB_RED;                     /* вставляемый узел - красный            */
    z->left  = z->right   = NULL;

    while (x)
    {
        rb_select_insert(x); // Выделяем путь

        y = x;
        if (z->key == x->key)              /* ключ уже присутствует                 */
        {
            rb_stext_right(x->pos, "Элемент уже есть в дереве", NULL);
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

int rb_paint_insert (rb_tree *t, key_t key, place tree_pos)
{
    rb_node *x = rb_paint_bst_insert(t, key); // Вставка как в двоичное дерево поиска с выделением пути
    if (!x) return 1;

    rb_paint(t, tree_pos); // Обновление рисунка, чтобы было видно вставляемый узел

    rb_inscr_x(x); // Надпись 'x' около нового узла
    rb_select(x->pos); // Выделение узла x

    /* Вывод текста слева от узла x при вставки корня или если родитель чёрный */
    if (!x->parent)
    {
        rb_stext_left(x->pos, "Корень красный -> перекрасить в чёрный", NULL);
        rb_select_repaint(x, BLACK); // Перекраска на рисунке (настоящая перекраска в конце функции)
    }
    else if (x->parent->color == RB_BLACK)
        rb_stext_left(x->parent->pos, "Родитель чёрный -> конец", NULL);

    /* Проблема если у узла x красный родитель:
     * указатель x перемещается вверх до корня или узла с черным родителем
     */
    while (x != t->root && x->parent->color == RB_RED)
    {
        /* Вывод текста справа или слева от родителя x так, чтобы не перекрыть дядю x */
        if (x->parent == x->parent->parent->right)
            rb_stext_right(x->parent->pos, "Родитель красный -> определить цвет дяди", NULL);
        else
            rb_stext_left(x->parent->pos, "Родитель красный -> определить цвет дяди", NULL);

        /* находим дядю в зависимости от того, является ли родитель x
         * правый или левым ребенком своего родителя
         */
        rb_node *y = x->parent == x->parent->parent->left ? x->parent->parent->right
                                                          : x->parent->parent->left;


        if (y && y->color == RB_RED)              /* случай "красный дядя" */
        {
            /* Вывод текста справа или слева от дяди x так, чтобы не перекрыть родителя x */
            if (y == y->parent->right)
                rb_stext_right(y->pos, "Дядя красный -> перекрасить родителя и дядю в",
                                       "чёрный, дедушку в красный; дедушка - новый x");
            else
                rb_stext_left(y->pos, "Дядя красный -> перекрасить родителя и дядю в",
                                      "чёрный, дедушку в красный; дедушка - новый x");


            x->parent->color = RB_BLACK; // Перекраска
            rb_select_repaint(x->parent, BLACK); // Изменение цвета узла на рисунке

            y->color = RB_BLACK;
            rb_select_repaint(y, BLACK);

            x->parent->parent->color = RB_RED;
            rb_select_repaint(x->parent->parent, LIGHTRED);

            delay(3000);

            x = x->parent->parent; // Перемещение x вверх
            rb_paint(t, tree_pos); // Обновление рисунка, чтобы убрать все надписи и выделения
            rb_inscr_x(x); // Надпись 'x' около нового узла
            rb_select(x->pos); // Выделение узла x
            /* Вывод текста, если цикл закончился */
            if (!x->parent)
            {
                rb_stext_left(x->pos, "Корень красный -> пере-",
                                      "красить в чёрный; конец");
                rb_select_repaint(x, BLACK);
            }

            else if (x->parent->color == RB_BLACK)
                rb_stext_left(x->parent->pos, "Родитель чёрный -> конец", NULL);
        }

        else                                      /* случай "черный дядя" */
        {
            /* Вывод текста справа или слева от дяди или родителя x в зависимости от того дядя nil или нет */
            if (y)
            {
                if (y == y->parent->right)
                    rb_stext_right(y->pos, "Дядя чёрный -> проверить одно-",
                                           "направленность пути от дедушки");
                else
                    rb_stext_left(y->pos, "Дядя чёрный -> проверить одно-",
                                          "направленность пути от дедушки");
            }
            else
            {
                if (x->parent == x->parent->parent->right)
                    rb_stext_left(x->parent->pos, "Дядя nil, т.е. чёрный -> проверить",
                                                  "однонаправленность пути от дедушки");
                else
                    rb_stext_right(x->parent->pos, "Дядя nil, т.е. чёрный -> проверить",
                                                   "однонаправленность пути от дедушки");
            }
            delay(2000);

            rb_paint(t, tree_pos); // Обновление рисунка, чтобы убрать все надписи и выделения
            rb_inscr_x(x); // Надпись 'x'
            /* Выделение дедушки, родителя и самого x, чтобы показать однонаправленность */
            rb_select(x->parent->parent->pos);
            rb_select(x->parent->pos);
            rb_select(x->pos);

            if (x->parent == x->parent->parent->left && x == x->parent->right)
            {   /* случай x - правый ребенок, а его родитель - левый */

                /* Вывод текста слева (справа стоит буква x) */
                rb_stext_left(x->pos, "x - правый ребенок, его родитель - левый",
                                      "-> левое вращение вокруг родителя x");

                x = x->parent;
                rb_select_rotate_left(x->pos); // Стрелка влево около узла, вокруг которого будет вращение
                rb_rotate_left(t, x);

                rb_paint (t, tree_pos); // Обновление рисунка, чтобы показать новое дерево (после вращения)
                rb_inscr_x(x); // Надпись 'x'
                /* Выделение дедушки, родителя и самого x, чтобы показать однонаправленность */
                rb_select(x->parent->parent->pos);
                rb_select(x->parent->pos);
                rb_select(x->pos);
            }
            else if (x->parent == x->parent->parent->right && x == x->parent->left)
            {   /* случай x - левый ребенок, а его родитель - правый */

                /* Вывод текста справа (слева стоит буква x) */
                rb_stext_right(x->pos, "x - левый ребенок, его родитель - правый",
                                       "-> правое вращение вокруг родителя x");

                x = x->parent;
                rb_select_rotate_right(x->pos); // Стрелка вправо около узла, вокруг которого будет вращение
                rb_rotate_right(t, x);

                rb_paint (t, tree_pos); // Обновление рисунка, чтобы показать новое дерево (после вращения)
                rb_inscr_x(x); // Надпись 'x'
                /* Выделение дедушки, родителя и самого x, чтобы показать однонаправленность */
                rb_select(x->parent->parent->pos);
                rb_select(x->parent->pos);
                rb_select(x->pos);

            }

            /* случай, когда путь от дедушки x к x в одном направлении  */

            /* Вывод текста так, чтобы не перекрывать узлы, которые будут меняться при вращении */
            if (x == x->parent->right)
                rb_stext_left(x->pos, "однонаправленность есть -> перекрасить",
                                      "родителя в чёрный, дедушку в красный");
            else
                rb_stext_right(x->pos, "однонаправленность есть -> перекрасить",
                                       "родителя в чёрный, дедушку в красный");

            x->parent->color = RB_BLACK; // Перекраска
            rb_select_repaint(x->parent, BLACK); // Изменение цвета узла на рисунке

            x->parent->parent->color = RB_RED;
            rb_select_repaint(x->parent->parent, LIGHTRED);

            delay(2000);

            rb_paint(t, tree_pos); // Обновление рисунка, чтобы убрать все надписи и выделения
            rb_inscr_x(x); // Надпись 'x'

            /* вращение вокруг дедушки в зависимости от того,
             * в каком направлении путь от дедушки к x
             */
            if (x == x->parent->left)
            {
                rb_select(x->parent->parent->pos);
                rb_select(x->parent->pos);

                rb_stext_left(x->parent->pos, "направление пути - влево -> правое",
                                              "вращение вокруг дедушки; конец");

                rb_select_rotate_right(x->parent->parent->pos); // Стрелка вправо около узла, вокруг которого вращение
                rb_rotate_right(t, x->parent->parent);

                delay(2000);
            }
            else
            {

                rb_select(x->parent->parent->pos);
                rb_select(x->parent->pos);

                rb_stext_right(x->parent->pos, "направление пути - вправо -> левое",
                                               "вращение вокруг дедушки; конец");

                rb_select_rotate_left(x->parent->parent->pos); // Стрелка влево около узла, вокруг которого вращение
                rb_rotate_left (t, x->parent->parent);

                delay(2000);
            }
        }
    }

    t->root->color = RB_BLACK;   /* поддержка условия черноты корня */

    return 0;
}

int rb_paint_delete (rb_tree *t, key_t key, place tree_pos)
{
    rb_node *x, *y, *z = t->root, *n = NULL;

    /* Шаг 1 - удаление элемента из дерева поиска */

    /* Спускаемся до листа влево или вправо в зависимости от ключа */
    while (z && z->key != key)
    {
        rb_select_insert(z); // Выделяем путь

        if (key < z->key)
        {
            if (!(z->left)) /* Если элемента нет */
            {
                rb_text_left(z->pos.x, z->pos.y + 35, "Элемент не найден", NULL);
                return -1;
            }
            z = z->left;
        }
        else
        {
            if (!(z->right))
            {
                rb_text_right(z->pos.x, z->pos.y + 35, "Элемент не найден", NULL);
                return -1;
            }
            z = z->right;
        }
    }
    rb_select_insert(z); // Если элемент найден, то выделяем его

    /* находим узел y, который будет фактически удален из дерева */
    if (!z->left || !z->right)
    {/* Если найденный узел и так является фактически удаляемым, то выводим соотв. текст */

        if (z->left || z->right)
            rb_stext_left(z->pos, "есть только одно поддерево ->",
                                  "это фактически удаляемый узел");
        else
            rb_stext_left(z->pos, "обоих поддеревьев нет -> это",
                                  "фактически удаляемый узел");
        y = z;
    }
    else
    {
        rb_stext_left(z->pos, "есть оба поддерева -> найти мини-",
                              "мальный элемент в правом поддереве");
        rb_tree r;
        r.root = z->right;
        y = rb_paint_min (&r); // Ищем минимальный элемент в правом поддереве с выделением пути
        rb_stext_left(y->pos, "это фактически удаляемый узел ->",
                              "переместить данные в первый узел");
        rb_select_copy(y, z); // Копируем ключ на рисунке
        z->key = y->key; // Копируем ключ
    }

    if (y == t->root)
    {
        rb_stext_right(y->pos, "Удаляется корень -> дерево",
                               "станет пустым; конец");
        free(y);
        t->root = NULL;
        return 0;
    }

    /* находим единственного потомка фактически удаляемого узла */
    x = y->left ? y->left : y->right;

    if (!x) /* если x - NIL-узел, актуализируем его */
    {
        n         = malloc(sizeof(rb_node));
        n->color  = RB_NIL; // Специальный цвет, чтобы этот узел можно было нарисовать
        n->left   = NULL; /* Нужно установить детям NULL, чтобы  */
        n->right  = NULL; /* остановить рекурсию при рисовании */
        x         = n;
    }

    x->parent = y->parent;          /* x будет новым ребенком родителя y   */

  if (!y->parent)                   /* если удаляется корень               */
        t->root = x;                /* устанавливаем корень                */
    else                            /* иначе удаляется новый ребенок       */
    {                               /* родителя удаленного узла            */
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    if (y->color == RB_BLACK)
    {   /*   Если удален черный элемент, надо восстановить RB-свойства
         * x объявляется "дважды черной вершиной", без отражения в памяти
         * x всегда будет указывать на дважды черную вершину, поднимаясь вверх до корня
         *   или пока не окажется красной вершиной
         */
        rb_stext_right(y->pos, "Заменить удаляемый узел на его",
                               "ребёнка; обозначить ребёнка 'x'");

        /* Если x - актуализированный NIL-узел, то об этом текст */
        if(x->color == RB_NIL)
        {
            rb_text_left(y->pos.x, y->pos.y + 35, "ребёнок - nil", NULL);
            delay(1400);
        }
        rb_paint(t, tree_pos); // Обновляем рисунок, чтобы видеть дерево без удаляемого элемента
        rb_inscr_x2(x); // Надпись 'x'

        while (x != t->root && x->color != RB_RED)
        {
            int l = 0;
            rb_node *w = x == x->parent->left ? x->parent->right /* w - брат    */
                                              : x->parent->left; /* вершины x   */

            /* Выводим текст так, чтобы не перекрыть брата */
            if (x == x->parent->left)
                rb_stext_left(x->pos, "x чёрный -> объявить его дважды",
                                      "чёрным; определить цвет брата");
            else
                rb_stext_right(x->pos, "x чёрный -> объявить его дважды",
                                       "чёрным; определить цвет брата");

            rb_select_double_black(x->pos); // Выделение двойной черноты на рисунке
            delay(1300);

            if (w->color == RB_RED)                   /* случай "брат - красный"  */
            {
                /* Выводим текст так, чтобы не перекрыть x */
                if (w == w->parent->left)
                    rb_stext_left(w->pos, "брат красный -> перекрасить его",
                                          "в чёрный, родителя в красный");
                else
                    rb_stext_right(w->pos, "брат красный -> перекрасить его",
                                           "в чёрный, родителя в красный");

                w->color         = RB_BLACK; // Перекраска
                rb_select_repaint(w, BLACK); // Перекраска на рисунке

                x->parent->color = RB_RED;
                rb_select_repaint(x->parent, LIGHTRED);

                if (x == x->parent->left)          /* нужный поворот и новый w в зависимости от  */
                {                                  /* того, левым или правым ребенком является x */
                    rb_text_left(x->pos.x, x->pos.y + 35, "x - левый ребёнок -> левое",
                                                          "вращение вокруг родителя");
                    rb_select_rotate_left(x->parent->pos); // Стрелка влево около узла, вокруг которого вращение
                    rb_rotate_left(t, x->parent);
                    w = x->parent->right;
                }
                else
                {

                    rb_text_right(x->pos.x, x->pos.y + 35, "x - левый ребёнок -> правое",
                                                           "вращение вокруг родителя");
                    rb_select_rotate_right(x->parent->pos); // Стрелка вправо около узла, вокруг которого вращение
                    rb_rotate_right(t, x->parent);
                    w = x->parent->left;
                }

                rb_paint(t, tree_pos); // Обновление рисунка после вращения
                rb_select_double_black(x->pos); // Выделение двойной черноты на рисунке
                rb_inscr_x2(x); // Надпись 'x'
                ++l;
            }
            /* Брат стал (или был изначально) чёрным (различаем с помощью l)
             * Выводим текст так, чтобы не перекрыть x
             */
            if (l)
            {
                if (w == w->parent->left)
                    rb_stext_left(w->pos, "теперь брат чёрный ->",
                                          "определить цвет племянников");
                else
                    rb_stext_right(w->pos, "теперь брат чёрный ->",
                                           "определить цвет племянников");
            }
            else
            {
                if (w == w->parent->left)
                    rb_stext_left(w->pos, "брат чёрный -> опреде-",
                                          "лить цвет племянников");
                else
                    rb_stext_right(w->pos, "брат чёрный -> опреде-",
                                           "лить цвет племянников");
            }
            if ((!w->left  || w->left->color  == RB_BLACK) && /* случай "оба племянники - черные" */
                (!w->right || w->right->color == RB_BLACK)    /* в т.ч. NIL-узел считается черным */
               )
            {
                /* Выводим текст в зависимости от цвета племянников
                 * так, чтобы ничего не перекрыть, и разделяя текст на две части,
                 * чтобы он занимал меньше место в ширину
                 */
                if (w == w->parent->right)
                {
                    if (w->right)
                    {
                        if (w->left)
                        {
                            rb_select(w->left->pos);
                            rb_stext_right(w->right->pos,                        "оба племянника чёрные ->",
                                                                                 "перекрасить брата в красный,");
                            rb_select_repaint(w, LIGHTRED); // Перекраска на рисунке
                            rb_text_right(w->right->pos.x, w->right->pos.y + 30, "вторую черноту передать родителю", NULL);
                            delay(3000);
                        }
                        else
                        {
                            rb_stext_right(w->right->pos,                        "оба племянника чёрные (левый",
                                                                                 "- nil, т.е чёрный) ->");
                            rb_text_right(w->right->pos.x, w->right->pos.y + 35, "перекрасить брата в красный,",
                                                                                 "вторую черноту передать родителю");
                            rb_select_repaint(w, LIGHTRED); // Перекраска на рисунке
                            delay(2000);
                        }
                    }
                    else
                    {
                        if (w->left)
                        {
                            rb_stext_left(w->left->pos,                       "оба племянника чёрные (правый",
                                                                              "- nil, т.е чёрный) ->");
                            rb_text_left(w->left->pos.x, w->left->pos.y + 35, "перекрасить брата в красный,",
                                                                              "вторую черноту передать родителю");
                            rb_select_repaint(w, LIGHTRED); // Перекраска на рисунке
                            delay(2000);
                        }
                        else
                        {
                            rb_text_right(w->pos.x, w->pos.y + 35, "оба племянника nil, т.е. чёрные",
                                                                   "-> перекрасить брата в красный,");
                            rb_select_repaint(w, LIGHTRED); // Перекраска на рисунке
                            rb_text_right(w->pos.x, w->pos.y + 65, "вторую черноту передать родителю", NULL);
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
                            rb_stext_left(w->left->pos,                       "оба племянника чёрные ->",
                                                                              "перекрасить брата в красный,");
                            rb_select_repaint(w, LIGHTRED); // Перекраска на рисунке
                            rb_text_left(w->left->pos.x, w->left->pos.y + 30, "вторую черноту передать родителю", NULL);
                            delay(3000);
                        }
                        else
                        {
                            rb_stext_right(w->right->pos,                        "оба племянника чёрные (левый",
                                                                                 "- nil, т.е чёрный) ->");
                            rb_text_right(w->right->pos.x, w->right->pos.y + 35, "перекрасить брата в красный,",
                                                                                 "вторую черноту передать родителю");
                            rb_select_repaint(w, LIGHTRED); // Перекраска на рисунке
                            delay(2000);
                        }
                    }
                    else
                    {
                        if (w->left)
                        {
                            rb_stext_left(w->left->pos,                       "оба племянника чёрные (правый",
                                                                              "- nil, т.е чёрный) ->");
                            rb_text_left(w->left->pos.x, w->left->pos.y + 35, "перекрасить брата в красный,",
                                                                              "вторую черноту передать родителю");
                            rb_select_repaint(w, LIGHTRED); // Перекраска на рисунке
                            delay(2000);
                        }
                        else
                        {
                            rb_text_left(w->pos.x, w->pos.y + 35, "оба племянника nil, т.е. чёрные",
                                                                  "-> перекрасить брата в красный,");
                            rb_select_repaint(w, LIGHTRED); // Перекраска на рисунке
                            rb_text_left(w->pos.x, w->pos.y + 65, "вторую черноту передать родителю", NULL);
                            delay(3000);
                        }
                    }
                }

                /* перекраска и смена x */
                w->color = RB_RED;
                                                 /* добавляем черноту родителю x, если он был красный */
                if (x->parent->color == RB_RED)  /* - завершение цикла, и отображаем всё на рисунке   */
                {
                    rb_paint(t, tree_pos); // Обновление рисунка
                    rb_inscr_x2(x); // Надпись 'x'
                    rb_select_double_black(x->parent->pos); // Выделение второй черноты у красного ролителя на рисунке

                    rb_text_right (x->parent->pos.x, x->parent->pos.y, "родитель красный -> пере-",
                                                                       "красить в чёрный; конец");
                    x->parent->color = RB_BLACK; // Перекраска
                    rb_select_repaint(x->parent, BLACK); // Перекраска на рисунке
                    x = t->root;
                }
                else
                {
                    /* Актуализированный NIL-узел больше не нужен, поэтому отрываем
                     * его от дерева, чтобы не рисовать в следующих итерациях цикла
                     * (память освобождается после цикла)
                     */
                    if (x->color == RB_NIL)
                    {
                        if (x == x->parent->left)
                            x->parent->left = NULL;
                        else
                            x->parent->right = NULL;
                    }

                    x = x->parent;
                    rb_paint(t, tree_pos); // Обновление рисунка
                    rb_inscr_x2(x); // Надпись 'x'
                    /* Выводим текст, если x - корень */
                    if (!x->parent)
                    {
                        rb_select_double_black(x->pos);
                        rb_text_right(x->pos.x, x->pos.y, "корень дважды чёрный ->",
                                                          "перекрасить в чёрный; конец");
                    }
                }
            }

            else /* Если один из племянников красный */
            {
                int k = 0;

                if ((x == x->parent->left  && (!w->right || w->right->color == RB_BLACK)) ||
                    (x == x->parent->right && (!w->left  || w->left->color  == RB_BLACK))
                   ) /* случай "противоположный племянник черный" */
                {
                    w->color = RB_RED; // Перекраска брата
                    /* Разные вращение и положение текста, в зависимости от того x - левый или правый ребёнок */
                    if (x == x->parent->left)
                    {
                        /* Выводим текст около нужного племянника, если он есть, или около брата
                         * Разделяем текст на две части, чтобы он занимал меньше места в ширину
                         */
                        if (w->right)
                        {
                            rb_stext_right(w->right->pos,                        "ближний племянник красный,",
                                                                                 "противоположный - чёрный ->");
                            rb_text_right(w->right->pos.x, w->right->pos.y + 35, "перекрасить брата в красный,",
                                                                                 "ближнего племянника в чёрный");
                        }
                        else
                        {
                            rb_text_right(w->pos.x, w->pos.y + 35, "ближний племянник красный, противо-",
                                                                   "положный племянник nil, т.е. чёрный ->");
                            rb_text_right(w->pos.x, w->pos.y + 70, "перекрасить брата в красный,",
                                                                   "ближнего племянника в чёрный");
                        }

                        rb_select_repaint(w, LIGHTRED); // Перекраска брата на рисунке после вывода текста

                        w->left->color = RB_BLACK; // Перекраска ближнего племянника
                        rb_select_repaint(w->left, BLACK); // Перекраска на рисунке

                        rb_text_left(x->pos.x, x->pos.y + 35, "x - левый ребёнок -> правое",
                                                              "вращение вокруг брата");
                        rb_select_rotate_right(w->pos); // Стрелка вправо около узла, вокруг которого вращение
                        rb_rotate_right(t, w);

                        w = x->parent->right; // Обновление брата после вращения
                    }
                    else /* x - правый ребёнок */
                    {
                        if (w->left)
                        {
                            rb_stext_left(w->left->pos,                       "ближний племянник красный,",
                                                                              "противоположный - чёрный ->");
                            rb_text_left(w->left->pos.x, w->left->pos.y + 35, "перекрасить брата в красный,",
                                                                              "ближнего племянника в чёрный");
                        }
                        else
                        {
                            rb_text_left(w->pos.x, w->pos.y + 35, "ближний племянник красный, противо-",
                                                                  "положный племянник nil, т.е. чёрный ->");
                            rb_text_left(w->pos.x, w->pos.y + 70, "перекрасить брата в красный,",
                                                                  "ближнего племянника в чёрный");
                        }

                        rb_select_repaint(w, LIGHTRED); // Перекраска брата на рисунке после вывода текста

                        w->right->color = RB_BLACK; // Перекраска ближнего племянника
                        rb_select_repaint(w->right, BLACK); // Перекраска на рисунке

                        rb_text_right(x->pos.x, x->pos.y + 35, "x - правый ребёнок -> левое",
                                                               "вращение вокруг брата");
                        rb_select_rotate_left(w->pos); // Стрелка влево около узла, вокруг которого вращение
                        rb_rotate_left(t, w);

                        w = x->parent->left; // Обновление брата после вращения
                    }

                    rb_paint(t, tree_pos); // Обновление рисунка
                    rb_select_double_black(x->pos); // Выделение двойной черноты на рисунке
                    rb_inscr_x2(x); // Надпись 'x'
                    ++k; // Чтобы дальше знать обновлялся рисунок или нет
                }

                /* случай "противоположный племянник красный" (цвет ближнего не имеет значения) */

                if (x == x->parent->left)
                {
                    rb_stext_right (w->right->pos, "противоположный племянник красный,",  /* Текст разделён на две */
                                                   "цвет ближнего не имеет значения ->"); /* части, чтобы занимать */
                                                                                          /* меньше места в ширину */
                    rb_text_right(w->right->pos.x, w->right->pos.y + 35, "перекрасить брата в цвет родителя,",
                                                                         "родителя и племянника - в чёрный");

                    rb_select_repaint(w, x->parent->color == RB_RED ? LIGHTRED : BLACK);

                    /* Настоящая перекраска только после вывода текста и перекраски на рисунке */
                    w->color = x->parent->color;


                    x->parent->color = RB_BLACK; // Перекраска
                    rb_select_repaint(x->parent, BLACK); // Перекраска на рисунке

                    w->right->color = RB_BLACK;
                    rb_select_repaint(w->right, BLACK);

                    /* Если рисунок обновлялся, то место около узла x не занято предыдущим текстом
                     * Иначе занято и нужно сдвинуть новый текст ниже
                     */
                    if (k)
                        rb_text_left(x->pos.x, x->pos.y, "x - левый ребёнок -> левое",
                                                         "вращение вокруг родителя; конец");
                    else
                        rb_text_left(x->pos.x, x->pos.y + 35, "x - левый ребёнок -> левое",
                                                              "вращение вокруг родителя; конец");
                    --k;

                    rb_select_rotate_left(x->parent->pos); // Стрелка влево около узла, вокруг которого вращение
                    rb_rotate_left(t, x->parent);
                }
                else
                {
                    rb_stext_left(w->left->pos, "противоположный племянник красный,",   /* Текст разделён на две */
                                                 "цвет ближнего не имеет значения ->"); /* части, чтобы занимать */
                                                                                        /* меньше места в ширину */
                    rb_text_left(w->left->pos.x, w->left->pos.y + 35, "перекрасить брата в цвет родителя,",
                                                                       "родителя и племянника - в чёрный");
                    /* Настоящая перекраска только после вывода текста и перекраски на рисунке */
                    rb_select_repaint(w, x->parent->color == RB_RED ? LIGHTRED : BLACK);
                    w->color = x->parent->color;


                    x->parent->color = RB_BLACK; // Перекраска
                    rb_select_repaint(x->parent, BLACK); // Перекраска на рисунке

                    w->left->color = RB_BLACK;
                    rb_select_repaint(w->left, BLACK);

                    /* Если рисунок обновлялся, то место около узла x не занято предыдущим текстом
                     * Иначе занято и нужно сдвинуть новый текст ниже
                     */
                    if (k)
                        rb_text_right(x->pos.x, x->pos.y, "x - левый ребёнок -> левое",
                                                          "вращение вокруг родителя; конец");
                    else
                        rb_text_right(x->pos.x, x->pos.y + 35, "x - левый ребёнок -> левое",
                                                               "вращение вокруг родителя; конец");
                    --k;

                    rb_select_rotate_right(x->parent->pos); // Стрелка вправо около узла, вокруг которого вращение
                    rb_rotate_right(t, x->parent);
                }

                x = t->root; // Выход из цикла

            } // Конец случая "один из племянников красный"
        } // Конец цикла

        /* Если ребёнок удаляемого узла был красным, то нужно
         * перекрасить его в чёрный для восстановления RB-свойств */
        if (x->color == RB_RED)
        {
            rb_paint(t, tree_pos); // Обновление рисунка
            rb_inscr_x2(x); // Надпись 'x'
            delay(1500);
            if (x == x->parent->left)
                rb_stext_left(x->pos, "x - красный -> пере-",
                                      "красить в чёрный; конец");
            else
                rb_stext_right(x->pos, "x - красный -> пере-",
                                       "красить в чёрный; конец");
            rb_select_repaint(x, BLACK); // Перекраска на рисунке
        }

       x->color = RB_BLACK;

    } // Конец условия "удаляемый узел - чёрный"
    else
    {
        rb_stext_right(y->pos, "Заменить удаляемый узел на его",
                               "ребёнка; узел красный -> конец");
        if(!y->left && !y->right)
        {
            rb_text_right(y->pos.x, y->pos.y + 35, "ребёнок - nil", NULL);
            delay(1400);
        }
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
            if (n == n->parent->right)   /* Нельзя использовать else, т.к. в цикле n мог быть  */
                n->parent->right = NULL; /* уже оторван от дерева (чтобы не рисовать NIL-узел) */
        }
        free (n); // Освобождения памяти в цикле не было
    }

    return 0;
}
