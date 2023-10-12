#include "complex.h"
#include <istream>
#include <ostream>
#include <cmath>
#include <vector>
#include <numbers>

complex::complex (double a, double b): real(a), imag(b) {} // Конструктор


complex& complex::operator += (const complex& b) // Операция += для комплексного типа
{
    real += b.real;
    imag += b.imag;
    return *this;
}

complex& complex::operator += (const double& b) // Операция += для вещественного типа
{
    real += b;
    return *this;
}

complex& complex::operator -= (const complex& b) // Операция -= для комплексного типа
{
    real -= b.real;
    imag -= b.imag;
    return *this;
}

complex& complex::operator -= (const double& b) // Операция -= для вещественного типа
{
    real -= b;
    return *this;
}

complex& complex::operator *= (const complex& b) // Операция *= для комплексного типа
{
    double r = real * b.real - imag * b.imag;
    imag = real * b.imag + imag * b.real;
    real = r;
    return *this;
}

complex& complex::operator *= (const double& b) // Операция *= для вещественного типа
{
    real *= b;
    imag *= b;
    return *this;
}

complex& complex::operator /= (const complex& b) // Операция /= для комплексного типа
{
    double r = (real * b.real + imag * b.imag) / (b.real * b.real + b.imag * b.imag);
    imag = (imag * b.real - real * b.imag) / (b.real * b.real + b.imag * b.imag);
    real = r;
    return *this;
}

complex& complex::operator /= (const double& b) // Операция /= для вещественного типа
{
    real /= b;
    imag /= b;
    return *this;
}


complex complex::operator + (const complex& b) const // Бинарная операция + для комплексного типа
{
    complex r = *this;
    return r += b;
}

complex complex::operator + (const double& b) const // Бинарная операция + для вещественного типа
{
    complex r = *this;
    return r += b;
}

complex complex::operator - (const complex& b) const // Бинарная операция - для комплексного типа
{
    complex r = *this;
    return r -= b;
}

complex complex::operator - (const double& b) const // Бинарная операция - для вещественного типа
{
    complex r = *this;
    return r -= b;
}

complex complex::operator * (const complex& b) const // Бинарная операция * для комплексного типа
{
    complex r = *this;
    return r *= b;
}

complex complex::operator * (const double& b) const // Бинарная операция * для вещественного типа
{
    complex r = *this;
    return r *= b;
}

complex complex::operator / (const complex& b) const // Бинарная операция / для комплексного типа
{
    complex r = *this;
    return r /= b;
}

complex complex::operator / (const double& b) const // Бинарная операция / для вещественного типа
{
    complex r = *this;
    return r /= b;
}


complex operator + (const double& a, const complex& b) // Бинарная операция + для вещественного типа c другой стороны
{
    return b + a;
}

complex operator - (const double& a, const complex& b) // Бинарная операция - для вещественного типа c другой стороны
{
    return a + (-b);
}

complex operator * (const double& a, const complex& b) // Бинарная операция * для вещественного типа c другой стороны
{
    return b * a;
}

complex operator / (const double& a, const complex& b) // Бинарная операция / для вещественного типа c другой стороны
{
    return complex ((a * b.real) / (b.real * b.real + b.imag * b.imag),
                    -(a * b.imag) / (b.real * b.real + b.imag * b.imag));
}

std::vector<complex> complex::sqrt(int n) const // Извлечение корня степени n
{
    double mod = std::sqrt(real * real + imag * imag),
           arg = std::atan2(imag, real); // atan2 вычисляет угол между двумя векторами

    mod = std::pow(mod, 1. / n);

    std::vector<complex> array(n);
    int k = 0;
    for (auto& i: array)
    {
        i = complex(mod * std::cos((arg + 2 * std::numbers::pi * k) / n),
                    mod * std::sin((arg + 2 * std::numbers::pi * k) / n));
        ++k;
    }
    return array;
}

complex complex::pow(int n) const // Возведение в целую степень
{
    complex r(1, 0), x = *this;
    if (n < 0)
    {
        x = 1 / x;
        n = -n;
    }

    while (1)
    {
        if (n & 1) // Остаток от деления на 2
            r *= x;

        n >>= 1; // Деление на 2
        if (!n)
            break;

        x *= x;
    }

    return r;
}

std::istream& operator >> (std::istream& stream, complex& a) // Ввод
{
    return (stream >> a.real >> a.imag);
}

std::ostream& operator << (std::ostream& stream, const complex& a) // Вывод
{
    if (a.imag == 0)
        return stream << a.real;



    if (a.imag == 1)
    {
        if (a.real == 0)
            return stream << "i";
        return stream << a.real << " + i";
    }

    if (a.imag < 0)
    {
        if (a.imag == -1)
        {
            if (a.real == 0)
                return stream << "-i";
            return stream << a.real << " - i";
        }

        if (a.real == 0)
            return stream << a.imag << "i";

        return stream << a.real << " - " << -a.imag << "i";
    }

    if (a.real == 0)
        return stream << a.imag << "i";

    return stream << a.real << " + " << a.imag << "i";
}
