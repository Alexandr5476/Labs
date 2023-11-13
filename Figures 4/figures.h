#ifndef FIGURES_H_INCLUDED
#define FIGURES_H_INCLUDED

#include <ostream>
#include <istream>
#include <numbers>
#include <cmath>

class figures // ����������� ����� "������"
{
public:
    virtual double area () const = 0; // �������
    virtual double perimeter () const = 0; // ��������
    friend std::ostream& operator << (std::ostream& stream, const figures& f) {f.print(stream); return stream;} // �����

    virtual figures& operator = (const figures& f) = 0;
protected:
    virtual void print (std::ostream& stream) const = 0; // ������
};

inline figures& figures::operator = (const figures& f) = default;


class circle : public figures // ���� (������������ �� ������)
{
public:
    circle (double r): radius(r) {} // �����������
    double area () const override {return std::numbers::pi * radius * radius;}  // �������
    double perimeter () const override {return 2 * std::numbers::pi * radius;} // ��������
    double get_radius () const {return radius;} // ��������� �������
    void set_radius (double new_radius) {radius = new_radius;} // ��������� �������

    circle& operator = (const figures& f) // ������������ �� ������ �� ������
    {
        if (this == &f) return *this; // �����������������
        const circle& c = dynamic_cast <const circle&> (f); // ���������� ������ � ������ �� ����������
        *this = c; // ������������ ����������
        return *this;
    }

    circle& operator = (const circle& c) = default; // ������������ �� ������ �� ����������

private:
    void print (std::ostream& stream) const override {stream << "���� ������� " << radius;} // ������
    double radius; // ������ �����
};


class square : public figures // ������� (������������ �� ������)
{
public:
    square (double s): side(s) {} // �����������
    double area () const override {return side * side;}  // �������
    double perimeter () const override {return side * 4;} // �������� ����� �������
    void set_side (double new_side) {side = new_side;} // ��������� ����� �������


    square& operator = (const figures& f)
    {
        if (this == &f) return *this; // �����������������
        const square& c = dynamic_cast <const square&> (f); // ���������� ������ � ����������
        *this = c;
        return *this;
    }
    square& operator = (const square& c) = default;

private:
    void print (std::ostream& stream) const override {stream << "������� �� �������� " << side;} // ������
    double side; // ������� ��������
};


class rectangle : public figures // ������������� (������������ �� ������)
{
public:
    rectangle (double w, double h): width(w), height(h) {} // �����������
    double area () const override {return width * height;}  // �������
    double perimeter () const override {return 2 * (width + height);} // ��������
    double get_width () const {return width;} // ��������� ������
    void set_width (double new_width) {width = new_width;} // ��������� ������
    double get_height () const {return height;} // ��������� ������
    void set_height (double new_height) {height = new_height;} // ��������� ������


    rectangle& operator = (const figures& f)
    {
        if (this == &f) return *this; // �����������������
        const rectangle& c = dynamic_cast <const rectangle&> (f); // ���������� ������ � ����������
        *this = c;
        return *this;
    }

    rectangle& operator = (const rectangle& c) = default;

private:
    void print (std::ostream& stream) const override {stream << "������������� ������ " << width << ", ������ " << height;} // ������
    double width, height; // ������ � ������ ��������������
};


class ellipse : public figures // ������ (������������ �� ������)
{
public:
    ellipse (double a_, double b_): a(a_), b(b_) {} // �����������
    double area () const override {return std::numbers::pi * a * b;}  // �������
    double perimeter () const override {return std::numbers::pi * std::sqrt(2 * (a * a + b * b));} // ��������
    double get_a () const {return a;} // ��������� a
    void set_a (double new_a) {a = new_a;} // ��������� a
    double get_b () const {return b;} // ��������� b
    void set_b (double new_b) {b = new_b;} // ��������� b


    ellipse& operator = (const figures& f)
    {
        if (this == &f) return *this; // �����������������
        const ellipse& c = dynamic_cast <const ellipse&> (f); // ���������� ������ � ����������
        *this = c;
        return *this;
    }
    ellipse& operator = (const ellipse& c) = default;

private:
    void print (std::ostream& stream) const override {stream << "������: a = " << a << ", b = " << b;} // ������
    double a, b; // a � b �������
};



#endif // FIGURES_H_INCLUDED
