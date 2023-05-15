#ifndef SAVING_H_INCLUDED
#define SAVING_H_INCLUDED
#include "database.h"

/** Заполняет массив структур street из файла, созданного с помощью функции saving
 *  len - адрес переменной, в которую запишется длинна массива
 *  filename - имя файла, из которого заполнять
 *  Возвращает указатель на массив или NULL в случае ошибки
 */
street * loading(size_t *len, const char *filename);


/** Сохраняет в файл с именем filename данные из массива list длины len */
void saving (street *list, size_t len, const char *filename);

#endif // SAVING_H_INCLUDED
