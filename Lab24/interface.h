#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "database.h"
#include <stdio.h>

typedef int (*fnc_comp) (void *, void *);

typedef double (*fnc_divide) (street *, street *);

typedef double (*fnc_sum) (street *, size_t len);

typedef double (*fnc_divide_num) (street *, double);


/** Очищает графическое окно, выводит массив структур list длинны len
 *  в виде таблицы, рисует кнопки "закрыть", "сохранить", "сохранить как"
 *  и кнопку "+" - добавление нового элемента в массив
 */
void table (street *list, size_t len);


/** Сравнивает структуры a и b (тип данных - street) по полю length
 *  Возвращает 1, если a > b, иначе 0
 */
int cmp_length_incr (void *a, void *b);


/** Сравнивает структуры a и b (тип данных - street) по полю houses
 *  Возвращает 1, если a > b, иначе 0
 */
int cmp_houses_incr (void *a, void *b);


/** Сравнивает структуры a и b (тип данных - street) по полю name
 *  Возвращает 1, если a раньше в алфавите, чем b, иначе 0
 */
int cmp_name_incr (void *a, void *b);


/** Сравнивает структуры a и b (тип данных - street) по полю length
 *  Возвращает 1, если a < b, иначе 0
 */
int cmp_length_decr (void *a, void *b);


/** Сравнивает структуры a и b (тип данных - street) по полю houses
 *  Возвращает 1, если a < b, иначе 0
 */
int cmp_houses_decr (void *a, void *b);


/** Сравнивает структуры a и b (тип данных - street) по полю name
 *  Возвращает 1, если a раньше в алфавите, чем b, иначе 0
 */
int cmp_name_decr (void *a, void *b);


/** Сортирует массив любого типа данных
 *  array - указатель на массив, len - длинна массива, size - размер одного элемента массива
 *  cmp - функция сравнения двух элементов массива
 *  если cmp возвращает 1, когда первый элемент больше, то массив будет отсортирован по возрастанию, иначе по убыванию
 */
void sort(void *array, size_t len, size_t size, fnc_comp cmp);


/** Ввод названия улицы в таблицу в графическом окне
 *  left, top, right, bottom - координаты изменяемой ячейки
 *  Возвращает указатель на строку с введённым названием
 *  или NULL, если ввод отменён или не удалось выделить память
 *  завершения ввода - Enter, отмена ввода - Home
 */
char * input_name (int left, int top, int right , int bottom);


/** Ввод длины улицы в таблицу в графическом окне
 *  left, top, right, bottom - координаты изменяемой ячейки
 *  Возвращает введённое число или NULL, если ввод отменён или не удалось выделить память
 *  завершения ввода - Enter, отмена ввода - Home
 */
double input_length (int left, int top, int right , int bottom);


/** Ввод количества домов на улице в таблицу в графическом окне
 *  left, top, right, bottom - координаты изменяемой ячейки
 *  Возвращает введённое число или NULL, если ввод отменён или не удалось выделить память
 *  завершения ввода - Enter, отмена ввода - Home
 */
double input_houses (int left, int top, int right , int bottom);


/** Ввод имени файла в графическом окне
 *  Возвращает указатель на строку с введённым именем
 *  или NULL, если ввод отменён или не удалось выделить память
 *  завершения ввода - Enter, отмена ввода - Home
 */
char * input_filename ();


/** Возвращает максимальный элемент в массиве list длины len
 *  cmp - функция сравнения двух элементов, которая должна
 *  возвращать 1, если a < b, иначе 0
 */
street * maximum (street *list, size_t len, fnc_comp cmp);


/** Возвращает сумму чисел из полей length элементов массива list длины len */
double sum_length (street *list, size_t len);


/** Возвращает сумму чисел из полей houses элементов массива list длины len */
double sum_houses (street *list, size_t len);


/** Возвращает результат деления чисел из полей houses структур а и b */
double divide_houses (street *a, street *b);


/** Возвращает результат деления чисел из полей length структур а и b */
double divide_length (street *a, street *b);


/** Возвращает результат деления чисела из поля houses структуры a на число b */
double divide_houses_num (street *a, double b);


/** Возвращает результат деления чисела из поля length структуры a на число b */
double divide_length_num (street *a, double b);


/** Рисует столбчатую диаграмму по элеметам массива list длины len
 *  cmp - функция сравнения двух элементов массива (возвращает 1, если a < b, иначе 0)
 *  div - функция деления двух элементов массива
 */
void bar_chart(street *list, size_t len, fnc_comp cmp, fnc_divide div);


/** Рисует круговую диаграмму по элеметам массива list длины len
 *  list_sum - функция суммирования всех элементов массива
 *  div - функция деления элемента массива на вещественное число
 */
void pie_chart(street *list, size_t len, fnc_sum list_sum, fnc_divide_num div);


/** Работа с массивом list длинны len_list в гравфическом окне
 *  Обрабатывает положение и нажатия мыши
 *  filename - имя файла, из которго прочитан массив list
 */
void interface (street *list, size_t len_list, const char *filename);

#endif // INTERFACE_H_INCLUDED
