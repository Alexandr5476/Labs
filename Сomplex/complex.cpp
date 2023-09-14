#include "complex.h"
#include <istream>
#include <ostream>

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
    double save_im = imag, save_re = real;
    real = save_re * b.real - save_im * b.imag;
    imag = save_re * b.imag + save_im * b.real;
    return *this;
}

complex& complex::operator *= (const double& b) // �������� *= ��� ������������� ����
{
    real *= b;
    imag *= b;
    return *this;
}

complex& complex::operator /= (const complex& b) // �������� /= ��� ������������ ����
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

        return stream << a.real << " - " << -a.imag << "i";
    }

    if (a.real == 0)
        return stream << a.imag << "i";

    return stream << a.real << " + " << a.imag << "i";
}
