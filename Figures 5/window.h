#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <ostream>
#include <istream>
#include <iostream>
#include <graphics.h>
#include "figures.h"
#include <map>
#include <string>



class text
{
public:
    text(std::string s, int x, int y, bool fr = true, int fr_width = 0, int fr_height = 0);
    text(std::string s, point p, bool fr = true, int fr_width = 0, int fr_height = 0);
    text(const char *s, int x, int y, bool fr = true, int fr_width = 0, int fr_height = 0);
    text(const char *s, point p, bool fr = true, int fr_width = 0, int fr_height = 0);
    void put(int color = BLACK);
    void change_fr(int thickness);
    std::string str;
    point pos;
    bool frame;
    int width, height, fr_width, fr_height;
};

class window
{
public:
    window (int width = 1200, int height = 700); // Конструктор по умолчанию
    point max, center;

private:
     
     text txt1 = text("Список фигур", center); // "Список фигур"

};

class edit_list
{   
public:
    edit_list(figure& f, std::string name_ = "Без имени"); // Конструктор
    void go_next(); // Перейти на следующую ячейку
    void go_prev(); // Перейти на предыдущую ячейку
    void loop (figure& f); // Работа списка
    std::string str_input(int w, const std::string& value); // Ввод строкого значения ячейки списка
    double double_input (int w, const double& value); // Ввод числового значения ячейки списка

    point pos = {(getmaxx() / 2) - 170, (getmaxy() / 2) - 170}; // Положение списка
    int sep = 30; // Расстояние между строками
    int width = 340, height = 340; // Ширина и высота списка
    std::string name; // Пользовательское название фигуы
    std::vector<text> figure_params; // Список ячеек
    size_t len; // Длина списка ячеек
    size_t cur; // Индекс текущей для пользователья ячейки 
};

#endif // WINDOW_H_INCLUDED