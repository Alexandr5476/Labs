#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include <stdio.h>

typedef struct
{
    char *name; // Название улицы
    double length; // Длина улицы
    int houses; // Количество домов на улице
} street;

typedef struct
{
    street *street_list;
    size_t len;
} dtb;

typedef int (*fnc_comp) (const void *, const void *);

typedef double (*fnc_divide) (const street *, const street *);

typedef double (*fnc_sum) (dtb list);

typedef double (*fnc_divide_num) (const street *, double);


/** Вставляет в конец базы данных новый элемент
 *  list - указатель на базу данных, n_name, n_length, n_houses - значения полей нового элемента
 *  Возвращается 0 в случае удачи, или 1, если не удалось выделить память
 *  Если list->street_list - NULL и list->len - 0, то создатся новый массив и заполнится первый элемент
 */
int street_insert (dtb *list, char *n_name, double n_length, int n_houses);


/** Удаляет из базы данных list один элемент с индексом place
 *  Возвращается 0 в случае удачи, или 1, если не удалось выделить память или база пуста
 */
int street_delete (dtb *list, size_t place);


/** Очищает базу данных list
 *  Присваевает NULL в поле street_list, 0 в len
 */
void street_free (dtb *list);


/** Сравнивает структуры a и b (тип данных - street) по полю length
 *  Возвращает 1, если a > b, иначе 0
 */
int cmp_length_incr (const void *a, const void *b);


/** Сравнивает структуры a и b (тип данных - street) по полю houses
 *  Возвращает 1, если a > b, иначе 0
 */
int cmp_houses_incr (const void *a, const void *b);


/** Сравнивает структуры a и b (тип данных - street) по полю name
 *  Возвращает 1, если a раньше в алфавите, чем b, иначе 0
 */
int cmp_name_incr (const void *a, const void *b);


/** Сравнивает структуры a и b (тип данных - street) по полю length
 *  Возвращает 1, если a < b, иначе 0
 */
int cmp_length_decr (const void *a, const void *b);


/** Сравнивает структуры a и b (тип данных - street) по полю houses
 *  Возвращает 1, если a < b, иначе 0
 */
int cmp_houses_decr (const void *a, const void *b);


/** Сравнивает структуры a и b (тип данных - street) по полю name
 *  Возвращает 1, если a раньше в алфавите, чем b, иначе 0
 */
int cmp_name_decr (const void *a, const void *b);


/** Сортирует массив любого типа данных
 *  array - указатель на массив, len - длинна массива, size - размер одного элемента массива
 *  cmp - функция сравнения двух элементов массива
 *  если cmp возвращает 1, когда первый элемент больше, то массив будет отсортирован по возрастанию, иначе по убыванию
 */
void sort(void *array, size_t len, size_t size, fnc_comp cmp);


/** Возвращает максимальный элемент из базы данных
 *  cmp - функция сравнения двух элементов из dtb.street_list , которая должна
 *  возвращать 1, если a < b, иначе 0
 */
street * maximum (dtb list, fnc_comp cmp);


/** Возвращает сумму длин улиц из базы данных list */
double sum_length (dtb list);


/** Возвращает суммарное количество домов на улицах из базы данных list */
double sum_houses (dtb list);


/** Возвращает результат деления чисел из полей houses структур а и b */
double divide_houses (const street *a, const street *b);


/** Возвращает результат деления чисел из полей length структур а и b */
double divide_length (const street *a, const street *b);


/** Возвращает результат деления чисела из поля houses структуры a на число b */
double divide_houses_num (const street *a, double b);


/** Возвращает результат деления чисела из поля length структуры a на число b */
double divide_length_num (const street *a, double b);

#endif // DATABASE_H_INCLUDED
