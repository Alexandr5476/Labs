#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include <stdio.h>

typedef struct
{
    char *name; // Ќазвание улицы
    double length; // ƒлина улицы
    int houses; //  оличество домов на улице
} street;


/** ¬ставл€ет в конец массива структур street новый элемент и заполн€ет пол€ структуры
 *  list - указатель на массив, len - длинна массива, n_name, n_length, n_houses - значени€ полей
 *  ≈сли пам€ть под новый элемент выдилась, то возвращаетс€ новый указатель на массив, иначе NULL
 *  ≈сли list = NULL и len = 0, то создатс€ новый массив и заполнитс€ первый элемент
 */
street * street_insert (street * list, size_t len, char *n_name, double n_length, int n_houses);


/** ”дал€ет из массив структур street один элемент
 *  list - указатель на массив, len - длинна массива, place - индекс элемента, который нужно удалить
 */
void street_delete (street *list, size_t len, size_t place);


/** ќчищает массив структур street
 *  list - указатель на массив, len - длинна массива
 */
void street_free (street *list, size_t len);

#endif // DATABASE_H_INCLUDED
