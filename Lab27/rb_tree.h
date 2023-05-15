#ifndef RB_TREE_H_INCLUDED
#define RB_TREE_H_INCLUDED
#include <stdio.h>


typedef struct
{
    int x, y;
} place;

/** Цвет узлов
 *  RB_NIL используется только один раз в функции удаления
 *  присваивается актуализированому NIL-узлу, чтобы его нарисовать
 */
typedef enum {RB_RED, RB_BLACK, RB_NIL} rb_color;


typedef int key_t; /// Тип ключа key_t


typedef struct rb_node /// Узел дерева
{
    key_t    key;
    rb_color color;
    /* указатель на левое и правое поддерево, NULL если это nil-узел;
     * указатель на родительский элемент, NULL для корня
     */
    struct rb_node *left, *right, *parent;
    place pos; // Координаты центра узла; Заполняются во время рисования
} rb_node;


typedef struct rb_tree /// Дерево
{
    rb_node *root; /* NULL для пустого дерева из одного nil-узла */
} rb_tree;


/** Создание дерева
 *  Возвращает указатель на него или NULL, если память не выделилась
 */
rb_tree *rb_alloc();


/** Рекурсивная очистка поддеревьев узла и самого узла */
void rb_node_clear (rb_node *n);

/** Удаление дерева из памяти */
void rb_free(rb_tree *t);


/** Поиск ключа в дереве
 *  Возвращает указатель на узел с ключом или NULL, если ключа в дереве нет
 */
rb_node * rb_search (rb_tree *t, key_t key);


/** Поиск минимального ключа в дереве
 *  Возвращает указатель на узел с минимальным ключом
 */
rb_node * rb_min (rb_tree *t);


/** Поиск максимального ключа в дереве
 *  Возвращает указатель на узел с максимальным ключом
 */
rb_node * rb_max (rb_tree *t);


/** Определение высоты дерева или поддерева
 *  n - указатель на узел, начиная с которого надо определить высоту
 *  Возвращает высоту (0, если n - NULL)
 */
size_t rb_hight (rb_node *n);


/** Левое вращение дерева t вокруг узла x */
void rb_rotate_left (rb_tree *t, rb_node *x);


/** Правое вращение дерева t вокруг узла x */
void rb_rotate_right (rb_tree *t, rb_node *x);


/** Вставка элемента с ключом key в дерево t как в простое дерево поиска
 *  Возвращает указатель на вставленный элемент или NULL в случае неудачи
 *  Дублирующиеся ключи запрещены, возвращает NULL если ключ присутствует
 */
rb_node *rb_bst_insert (rb_tree *t, key_t key);


/** Вставка элемента с ключом key s в дерево t
 *  Возвращает 0 в случае успеха, ненулевое значение в случае провала
 */
int rb_insert (rb_tree *t, key_t key);


/** Удаление элемента с ключом key из дерева t
 *  Возвращает 0, если элемент удален, ненулевое значение, если элемента нет
 */
int rb_delete (rb_tree *t, key_t key);


/** Печать дерева */
void rb_print(const rb_node *t);


#endif // RB_TREE_H_INCLUDED
