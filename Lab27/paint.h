#ifndef PAINT_H_INCLUDED
#define PAINT_H_INCLUDED
#include <stdio.h>
#include "rb_tree.h"


/** Делает тоже самое, что функция rb_bst_insert (файл rb_tree.h)
 *  Но также выделяет путь от корня к месту вставки узла
 *  Если узел с ключом key уже был в дереве, то выводит об этом сообщение около узла
 */
rb_node *rb_paint_bst_insert (rb_tree *t, key_t key);


/** Делает тоже самое, что функция rb_insert (файл rb_tree.h)
 *  Но также визуализирует алгоритмы вставки
 */
int rb_paint_insert (rb_tree *t, key_t key, place tree_pos);


/** Делает тоже самое, что функция rb_delete (файл rb_tree.h)
 *  Но также визуализирует алгоритмы удаления
 */
int rb_paint_delete (rb_tree *t, key_t key, place tree_pos);


#endif // PAINT_H_INCLUDED
