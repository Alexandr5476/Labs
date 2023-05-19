#ifndef SAVING_H_INCLUDED
#define SAVING_H_INCLUDED
#include "database.h"

/** Заполняет базу данных list из файла, созданного с помощью функции saving
 *  filename - имя файла, из которого заполнять
 *  Возвращает 1 в случае ошибки, иначе 0
 */
int loading (dtb *list, const char *filename);


/** Сохраняет в файл с именем filename данные из базы данных list */
void saving (dtb list, const char *filename);

#endif // SAVING_H_INCLUDED
