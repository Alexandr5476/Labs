#include "figures.h"

figure& figure::set_param (size_t i, double value) // Получение параметра фигуры
{
    if (i >= size) throw std::runtime_error("Ошибка: изменение несуществующего параметра");
    if (status) 
    {
        paint(WHITE); 
        param[i] = value; 
        paint(color);
    } 
    else param[i] = value; 
    return *this;
}

figure& figure::set_pos (int x, int y) // Изменение координат опорной точки фигуры
{
    if (status) 
    {
        paint(WHITE); 
        pos = {x, y}; 
        paint(color);
    } 
    else pos = {x, y}; 
    return *this;
}