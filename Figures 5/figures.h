#ifndef FIGURES_H_INCLUDED
#define FIGURES_H_INCLUDED

#include <ostream>
#include <istream>
#include <iostream>
#include <vector>
#include <graphics.h>
#include <initializer_list>
#include <execution>

typedef enum {shown = 1, hidden = 0} st;
typedef struct point {int x; int y;} point;

inline point& operator / (point& a, int b) {return a = {a.x / b, a.y / b};}
inline point& operator - (point& a, int b) {return a = {a.x - b, a.y - b};}

class figure
{
public:

    figure (st stat, size_t s): status(stat), size(s) {}

    void show () {paint(color); status = shown; std::cout << "show" << color << "(" <<WHITE <<")";} // Отображение фигуры 

    void hide () {paint(WHITE); status = hidden;} // Отображение фигуры

    figure& set_color (int new_color) {color = new_color; if (status) paint(color); return *this;} // Изменение цвета фигуры

    figure& set_color (int red, int green, int blue) {color = rgb(red, green, blue); if (status) paint(color); return *this;} // Изменение цвета фигуры

    const int& get_color () const {return color;} // Получение цвета фигуры (const)
    
    figure& set_pos (int x, int y); // Изменение координат опорной точки фигуры

    const point& get_pos () const {return pos;} // Получение координат опорной точки фигуры (const)

    const size_t& len_param () const {return size;} // Получение количества параметров

    figure& set_param (size_t i, double value); // Изменение параметра фигуры

    const double& operator [] (size_t i) const 
    {if (i >= size) throw std::runtime_error("Ошибка: получение несуществующего параметра"); return param[i];} // Получение параметра фигуры (const)

    const std::string& operator () (size_t i) const 
    {if (i > size) throw std::runtime_error("Ошибка: получение имени несуществующего параметра"); return param_str[i];} // Получение  названия параметра фигуры (const)

//protected:
    st status; // Статус фигуры (показана или нет)
    point pos = {400, 300}; // Координаты опорной точки
    int color = rgb(0, 102, 102); // Цвет фигуры
    size_t size; // Количество параметров
    std::vector<double> param; // Массив параметров
    std::vector<std::string> param_str; // Массив названий параметров

    virtual void paint (int color_ = rgb(0, 102, 102)) const = 0;  // Рисование фигуры
};


class circl : public figure
{
public:
    circl (double radius, st stat = hidden): figure(stat, 1) {param.push_back(radius); param_str.push_back("Круг"); param_str.push_back("Радиус");}

//private:
    void paint (int color = rgb(0, 102, 102)) const override {setcolor(color); setlinestyle(0, 0, THICK_WIDTH); circle(pos.x, pos.y, param[0]); std::cout << std::endl <<"paint" << std::endl;}
};

#endif // FIGURES_H_INCLUDED