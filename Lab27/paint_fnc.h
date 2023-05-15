#ifndef PAINT_FNC_H_INCLUDED
#define PAINT_FNC_H_INCLUDED
#include <stdio.h>
#include "rb_tree.h"

#define MY_LIGHTGREEN (_getabsolutecolor(_LIGHTGREEN))


/** Рекурсивно рисует дерево и записывает вычисленные координаты узлов в поле pos (структуры rb_node)
 *  n - указатель на узел, который выводится на текущем шаге рекурсии, pos - его координаты,
 *  beg, end - параметры (высоты левого и правого поддеревьев следующих узлов) для вычисления позиции следующего узла
 */
void rb_paint_req (rb_node *n, place pos, size_t beg, size_t end);


/** Очищает экран и рисует дерево, если оно не пустое
 *  t - указатель на дерево, tree_pos - координаты корня
 */
void rb_paint (rb_tree *t, place tree_pos);


/** Выделяет синим цветом узел дерева с координатами pos
 *  Ждёт 1 секунду
 */
void rb_select(place pos);


/** Выделяет синим цветом узел n и серым цветом родителя, если он есть
 *  Ждёт 0,7 секунды
 */
void rb_select_insert (const rb_node *n);


/** Рисует стрелочку вправо вокруг узла с координатами pos
 *  Ждёт 4 секунды
 */
void rb_select_rotate_right (place pos);


/** Рисует стрелку влево вокруг узла с координатами pos
 *  Ждёт 4 секунды
 */
void rb_select_rotate_left (place pos);


/** Выводит текст на жёлтом фоне справа от узла с координатами x, y
 *  str1 - указатель на первую строку текста, str2 - указатель на вторую строку текста (может быть NULL)
 *  Ждёт 5 секунд, если вторая строка есть, иначе 2 секунды
 */
void rb_text_right (int x, int y, const char *str1, const char *str2);


/** Выводит текст на жёлтом фоне слева от узла с координатами x, y
 *  str1 - указатель на первую строку текста, str2 - указатель на вторую строку текста (может быть NULL)
 *  Ждёт 5 секунд, если вторая строка есть, иначе 2 секунды
 */
void rb_text_left (int x, int y, const char *str1, const char *str2);


/** Вызывает функцию rb_select с параметром pos,
 *  потом rb_text_right с параметрами pos.x, pos.y, str1, str2
 */
void rb_stext_right (place pos, const char *str1, const char *str2);


/** Вызывает функцию rb_select с параметром pos,
 *  потом rb_text_left с параметрами pos.x, pos.y, str1, str2
 */
void rb_stext_left (place pos, const char *str1, const char *str2);


/** Выводит букву 'x' слева от узла x, если он левый ребёнок
 *  Справа, если он корень или правый ребёнок
 */
void rb_inscr_x (const rb_node *x);


/** Выводит букву 'x' справа от узла x, если он левый ребёнок
 *  Слева, если он корень или правый ребёнок
 */
void rb_inscr_x2 (const rb_node *x);


/** Перекрашивает (только на рисунке) узел n в цвет new_color и выделяет его зелёным цветом
 *  Ждёт 1,3 секнды
 *  Нельзя перекрашивать NIL-узел
 */
void rb_select_repaint (const rb_node *n, int new_color);


/** Возвращает минимальный элемент в дереве t или NULL, если дерево пустое
 *  Выделяет путь поиска
 */
rb_node * rb_paint_min (rb_tree *t);


/** Копирует (только на рисунке) ключ из узла n_old в узел n_new
 *  Рисует стрелку от старого узла к новому и выделяет новый узел зелёным цветом
 *  Ждёт 1,3 секунды
 */
void rb_select_copy (const rb_node *n_old, const rb_node *n_new);


/** Рисует чёрную рамку вокруг узла с координатами pos */
void rb_select_double_black (place pos);


#endif // PAINT_FNC_H_INCLUDED
