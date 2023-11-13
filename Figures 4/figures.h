#ifndef FIGURES_H_INCLUDED
#define FIGURES_H_INCLUDED

#include <ostream>
#include <istream>
#include <numbers>
#include <cmath>

class figures // Абстрактный класс "фигура"
{
public:
    virtual double area () const = 0; // Площадь
    virtual double perimeter () const = 0; // Периметр
    friend std::ostream& operator << (std::ostream& stream, const figures& f) {f.print(stream); return stream;} // Вывод

    virtual figures& operator = (const figures& f) = 0;
protected:
    virtual void print (std::ostream& stream) const = 0; // Печать
};

inline figures& figures::operator = (const figures& f) = default;


class circle : public figures // Круг (наследование от фигуры)
{
public:
    circle (double r): radius(r) {} // Конструктор
    double area () const override {return std::numbers::pi * radius * radius;}  // Площадь
    double perimeter () const override {return 2 * std::numbers::pi * radius;} // Периметр
    double get_radius () const {return radius;} // Получение радиуса
    void set_radius (double new_radius) {radius = new_radius;} // Установка радиуса

    circle& operator = (const figures& f) // Присваивание из ссылки на фигуру
    {
        if (this == &f) return *this; // Самоприсванивание
        const circle& c = dynamic_cast <const circle&> (f); // Приведение ссылки к ссылке на окружность
        *this = c; // Присваивание окружности
        return *this;
    }

    circle& operator = (const circle& c) = default; // Присваивание из ссылки на окружность

private:
    void print (std::ostream& stream) const override {stream << "круг радиуса " << radius;} // Печать
    double radius; // Радиус круга
};


class square : public figures // Квадрат (наследование от фигуры)
{
public:
    square (double s): side(s) {} // Конструктор
    double area () const override {return side * side;}  // Площадь
    double perimeter () const override {return side * 4;} // Периметр длины стороны
    void set_side (double new_side) {side = new_side;} // Установка длины стороны


    square& operator = (const figures& f)
    {
        if (this == &f) return *this; // Самоприсванивание
        const square& c = dynamic_cast <const square&> (f); // Приведение ссылки к орружности
        *this = c;
        return *this;
    }
    square& operator = (const square& c) = default;

private:
    void print (std::ostream& stream) const override {stream << "Квадрат со стороной " << side;} // Печать
    double side; // Сторона квадрата
};


class rectangle : public figures // Прямоугольник (наследование от фигуры)
{
public:
    rectangle (double w, double h): width(w), height(h) {} // Конструктор
    double area () const override {return width * height;}  // Площадь
    double perimeter () const override {return 2 * (width + height);} // Периметр
    double get_width () const {return width;} // Получение ширины
    void set_width (double new_width) {width = new_width;} // Установка ширины
    double get_height () const {return height;} // Получение высоты
    void set_height (double new_height) {height = new_height;} // Установка высоты


    rectangle& operator = (const figures& f)
    {
        if (this == &f) return *this; // Самоприсванивание
        const rectangle& c = dynamic_cast <const rectangle&> (f); // Приведение ссылки к орружности
        *this = c;
        return *this;
    }

    rectangle& operator = (const rectangle& c) = default;

private:
    void print (std::ostream& stream) const override {stream << "Прямоугольник высоты " << width << ", ширины " << height;} // Печать
    double width, height; // Ширина и высота прмяоугольника
};


class ellipse : public figures // Эллипс (наследование от фигуры)
{
public:
    ellipse (double a_, double b_): a(a_), b(b_) {} // Конструктор
    double area () const override {return std::numbers::pi * a * b;}  // Площадь
    double perimeter () const override {return std::numbers::pi * std::sqrt(2 * (a * a + b * b));} // Периметр
    double get_a () const {return a;} // Получение a
    void set_a (double new_a) {a = new_a;} // Установка a
    double get_b () const {return b;} // Получение b
    void set_b (double new_b) {b = new_b;} // Установка b


    ellipse& operator = (const figures& f)
    {
        if (this == &f) return *this; // Самоприсванивание
        const ellipse& c = dynamic_cast <const ellipse&> (f); // Приведение ссылки к орружности
        *this = c;
        return *this;
    }
    ellipse& operator = (const ellipse& c) = default;

private:
    void print (std::ostream& stream) const override {stream << "эллипс: a = " << a << ", b = " << b;} // Печать
    double a, b; // a и b эллипса
};



#endif // FIGURES_H_INCLUDED
