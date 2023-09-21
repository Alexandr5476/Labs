#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED

#include <istream>
#include <ostream>
#include <cmath>
#include <vector>

class complex
{
public:
    complex (double a = 0, double b = 0); // �����������

    complex& operator += (const complex& b); // �������� += ��� ������������  ����
    complex& operator += (const  double& b); // �������� += ��� ������������� ����
    complex& operator -= (const complex& b); // �������� -= ��� ������������  ����
    complex& operator -= (const  double& b); // �������� -= ��� ������������� ����
    complex& operator *= (const complex& b); // �������� *= ��� ������������  ����
    complex& operator *= (const  double& b); // �������� *= ��� ������������� ����
    complex& operator /= (const complex  b); // �������� /= ��� ������������  ����
    complex& operator /= (const  double& b); // �������� /= ��� ������������� ����

    complex operator + (const complex& b) const; // �������� �������� + ��� ������������  ����
    complex operator + (const  double& b) const; // �������� �������� + ��� ������������� ����
    complex operator - (const complex& b) const; // �������� �������� - ��� ������������  ����
    complex operator - (const  double& b) const; // �������� �������� - ��� ������������� ����
    complex operator * (const complex& b) const; // �������� �������� * ��� ������������  ����
    complex operator * (const  double& b) const; // �������� �������� * ��� ������������� ����
    complex operator / (const complex& b) const; // �������� �������� / ��� ������������  ����
    complex operator / (const  double& b) const; // �������� �������� / ��� ������������� ����

    friend complex operator + (const  double& a, const complex& b); // �������� �������� + ��� ������������� ���� c ������ �������
    friend complex operator - (const  double& a, const complex& b); // �������� �������� - ��� ������������� ���� c ������ �������
    friend complex operator * (const  double& a, const complex& b); // �������� �������� * ��� ������������� ���� c ������ �������
    friend complex operator / (const  double& a, const complex& b); // �������� �������� / ��� ������������� ���� c ������ �������

    const complex& operator +() const {return *this;} // ������� +
    complex operator -() const {return complex(-real, -imag);} // ������� -

    bool operator == (const complex& b) const {return real == b.real && imag == b.imag;} // �������� == ��� ������������  ����
    bool operator == (const double& b)  const {return real == b      && imag == 0     ;} // �������� == ��� ������������� ����
    friend bool operator == (const double& a, const complex b) {return  b.real == a && b.imag == 0;} // �������� == ��� ������������� ���� c ������ �������

    bool operator != (const complex& b) const {return real != b.real || imag != b.imag;} // �������� == ��� ������������  ����
    bool operator != (const double& b)  const {return real != b      || imag != 0     ;} // �������� == ��� ������������� ����
    friend bool operator != (const double& a, const complex b) {return  b.real != a || b.imag != 0;} // �������� == ��� ������������� ���� c ������ �������

    double getre () const {return real;} // ������ ������������ �����
    double getim () const {return imag;} // ������ ������ �����

    double abs () const {return std::sqrt(real * real + imag * imag);} // ������
    complex conj () const {return complex (real, -imag);}; // ����������
    complex pow(int n = 2) const; // ���������� � ����� �������
    std::vector<complex> sqrt(int n = 2) const; // ���������� ����� ������� n

    friend std::istream& operator >> (std::istream& stream, complex& a); // ����
    friend std::ostream& operator << (std::ostream& stream, const complex& a); // �����

private:
    double real, imag;
};

#endif // COMPLEX_H_INCLUDED
