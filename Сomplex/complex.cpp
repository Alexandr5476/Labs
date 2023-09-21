#include "complex.h"
#include <istream>
#include <ostream>
#include <cmath>
#include <vector>
#include <numbers>

complex::complex (double a, double b): real(a), imag(b) {} // �����������


complex& complex::operator += (const complex& b) // �������� += ��� ������������ ����
{
    real += b.real;
    imag += b.imag;
    return *this;
}

complex& complex::operator += (const double& b) // �������� += ��� ������������� ����
{
    real += b;
    return *this;
}

complex& complex::operator -= (const complex& b) // �������� -= ��� ������������ ����
{
    real -= b.real;
    imag -= b.imag;
    return *this;
}

complex& complex::operator -= (const double& b) // �������� -= ��� ������������� ����
{
    real -= b;
    return *this;
}

complex& complex::operator *= (const complex& b) // �������� *= ��� ������������ ����
{
    double save_im = imag, save_re = real, b_imag = b.imag, b_real = b.real;
    real = save_re * b_real - save_im * b_imag;
    imag = save_re * b_imag + save_im * b_real;
    return *this;
}

complex& complex::operator *= (const double& b) // �������� *= ��� ������������� ����
{
    real *= b;
    imag *= b;
    return *this;
}

complex& complex::operator /= (const complex b) // �������� /= ��� ������������ ����
{
    double save_im = imag, save_re = real;
    real = (save_re * b.real + save_im * b.imag) / (b.real * b.real + b.imag * b.imag);
    imag = (save_im * b.real - save_re * b.imag) / (b.real * b.real + b.imag * b.imag);
    return *this;
}

complex& complex::operator /= (const double& b) // �������� /= ��� ������������� ����
{
    real /= b;
    imag /= b;
    return *this;
}


complex complex::operator + (const complex& b) const // �������� �������� + ��� ������������ ����
{
    complex r = *this;
    return r += b;
}

complex complex::operator + (const double& b) const // �������� �������� + ��� ������������� ����
{
    complex r = *this;
    return r += b;
}

complex complex::operator - (const complex& b) const // �������� �������� - ��� ������������ ����
{
    complex r = *this;
    return r -= b;
}

complex complex::operator - (const double& b) const // �������� �������� - ��� ������������� ����
{
    complex r = *this;
    return r -= b;
}

complex complex::operator * (const complex& b) const // �������� �������� * ��� ������������ ����
{
    complex r = *this;
    return r *= b;
}

complex complex::operator * (const double& b) const // �������� �������� * ��� ������������� ����
{
    complex r = *this;
    return r *= b;
}

complex complex::operator / (const complex& b) const // �������� �������� / ��� ������������ ����
{
    complex r = *this;
    return r /= b;
}

complex complex::operator / (const double& b) const // �������� �������� / ��� ������������� ����
{
    complex r = *this;
    return r /= b;
}


complex operator + (const double& a, const complex& b) // �������� �������� + ��� ������������� ���� c ������ �������
{
    return b + a;
}

complex operator - (const double& a, const complex& b) // �������� �������� - ��� ������������� ���� c ������ �������
{
    return a + (-b);
}

complex operator * (const double& a, const complex& b) // �������� �������� * ��� ������������� ���� c ������ �������
{
    return b * a;
}

complex operator / (const double& a, const complex& b) // �������� �������� / ��� ������������� ���� c ������ �������
{
    return complex ((a * b.real) / (b.real * b.real + b.imag * b.imag),
                    -(a * b.imag) / (b.real * b.real + b.imag * b.imag));
}

std::vector<complex> complex::sqrt(int n) const
{
    double mod = std::sqrt(real * real + imag * imag),
           arg = std::acos(real / mod);

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

complex complex::pow(int n) const
{
    complex r(1, 0), x = *this;
    if (n < 0)
    {
        x = 1 / x;
        n = -n;
    }

    while (1)
    {
        if (n & 1) // ������� �� ������� �� 2
            r *= x;

        n >>= 1; // ������� �� 2
        if (!n)
            break;

        x *= x;
    }

    return r;
}

std::istream& operator >> (std::istream& stream, complex& a) // ����
{
    return (stream >> a.real >> a.imag);
}

std::ostream& operator << (std::ostream& stream, const complex& a) // �����
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
