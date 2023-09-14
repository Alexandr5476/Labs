#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED

#include <istream>
#include <ostream>
#include <cmath>

class complex
{
public:
    complex (double a = 0, double b = 0); // Конструктор

    complex& operator += (const complex& b); // Операция += для комплексного  типа
    complex& operator += (const  double& b); // Операция += для вещественного типа
    complex& operator -= (const complex& b); // Операция -= для комплексного  типа
    complex& operator -= (const  double& b); // Операция -= для вещественного типа
    complex& operator *= (const complex& b); // Операция *= для комплексного  типа
    complex& operator *= (const  double& b); // Операция *= для вещественного типа
    complex& operator /= (const complex& b); // Операция /= для комплексного  типа
    complex& operator /= (const  double& b); // Операция /= для вещественного типа

    complex operator + (const complex& b) const; // Бинарная операция + для комплексного  типа
    complex operator + (const  double& b) const; // Бинарная операция + для вещественного типа
    complex operator - (const complex& b) const; // Бинарная операция - для комплексного  типа
    complex operator - (const  double& b) const; // Бинарная операция - для вещественного типа
    complex operator * (const complex& b) const; // Бинарная операция * для комплексного  типа
    complex operator * (const  double& b) const; // Бинарная операция * для вещественного типа
    complex operator / (const complex& b) const; // Бинарная операция / для комплексного  типа
    complex operator / (const  double& b) const; // Бинарная операция / для вещественного типа

    friend complex operator + (const  double& a, const complex& b); // Бинарная операция + для вещественного типа c другой стороны
    friend complex operator - (const  double& a, const complex& b); // Бинарная операция - для вещественного типа c другой стороны
    friend complex operator * (const  double& a, const complex& b); // Бинарная операция * для вещественного типа c другой стороны
    friend complex operator / (const  double& a, const complex& b); // Бинарная операция / для вещественного типа c другой стороны

    complex operator +() {return *this;} // Унарный +
    complex operator -() const {return complex(-real, -imag);} // Унарный -

    bool operator == (const complex& b) const {return real == b.real && imag == b.imag;} // Операция == для комплексного  типа
    bool operator == (const double& b)  const {return real == b      && imag == 0     ;} // Операция == для вещественного типа
    friend bool operator == (const double& a, const complex b) {return  b.real == a && b.imag == 0;} // Операция == для вещественного типа c другой стороны

    double getre () const {return real;} // Геттер вещественной части
    double getim () const {return imag;} // Геттер мнимой части

    double abs () const {return sqrt(real * real + imag * imag);} // Модуль
    complex conj () const {return complex (real, -imag);}; // Сопряжённое

    friend std::istream& operator >> (std::istream& stream, complex& a); // Ввод
    friend std::ostream& operator << (std::ostream& stream, const complex& a); // Вывод

private:
    double real, imag;
};

#endif // COMPLEX_H_INCLUDED
