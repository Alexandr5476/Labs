#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <istream>
#include <ostream>
#include <cmath>

template <class T, size_t N>
class vector
{
public:
    vector<T, N> (); //  ����������� �� ���������
    vector (const T array[]); // ����������� � �����������

    T& operator [] (size_t i) {return vec[i];} // �������� [] ��� const
    const T& operator [] (size_t i) const {return vec[i];} // �������� [] � const

    vector<T, N>& operator += (const vector<T, N>& v2); // �������� += ��� ���������� ����
    vector<T, N>& operator -= (const vector<T, N>& v2); // �������� -= ��� ���������� ����

    vector<T, N> operator + (const vector<T, N>& v2) const; // �������� + ��� ���������� ����
    vector<T, N> operator - (const vector<T, N>& v2) const; // �������� - ��� ���������� ����

    vector<T, N>& operator *= (const T& a); // �������� *= ��� ���������� ���� (��������� �� ������)
    vector<T, N>& operator /= (const T& a); // �������� /= ��� ���������� ���� (������� �� ������)

    vector<T, N> operator * (const T& a) const; // �������� * ��� ���������� ���� (��������� �� ������)
    vector<T, N> operator / (const T& a) const; // �������� / ��� ���������� ���� (������� �� ������)

    T operator * (const vector<T, N>& v2) const; // ��������� ���������

    bool operator == (const vector<T, N>&) const; // �������� �� ���������

    vector<T, N> operator + () const {return *this;} // ������� +
    vector<T, N> operator - () const; // ������� -

    template<typename H, size_t M>
    friend std::istream& operator >> (std::istream& stream, vector<H, M>& v); // �����

    template<typename H, size_t M>
    friend std::ostream& operator << (std::ostream& stream, const vector<H, M>& v); // �����

    T norm () const {return sqrt((*this) * (*this));} // �����
    T dist (const vector<T, N>& v2) const {return (*this - v2).norm();} // ���������� ����� ���������
    T angle (const vector<T, N>& v2) const {return acos((*this * v2) / (this->norm() * v2.norm()));} // ���� ����� ���������

private:
    T vec[N];
};

template <class T, size_t N>
vector<T, N>::vector () //  ����������� �� ���������
{
    for (size_t i = 0; i < N; ++i)
        vec[i] = 0;
}

template <class T, size_t N>
vector<T, N>::vector (const T array[]) // ����������� � �����������
{
    for (size_t i = 0; i < N; ++i)
        vec[i] = array[i];
}

template <class T, size_t N>
vector<T, N>& vector<T, N>::operator += (const vector<T, N>& v2) // �������� += ��� ����������� ����
{
    for (size_t i = 0; i < N; ++i)
        vec[i] += v2[i];

    return *this;
}

template <class T, size_t N>
vector<T, N>& vector<T, N>::operator -= (const vector<T, N>& v2) // �������� -= ��� ����������� ����
{
    for (size_t i = 0; i < N; ++i)
        vec[i] -= v2[i];

    return *this;
}

template <class T, size_t N>
vector<T, N> vector<T, N>::operator + (const vector<T, N>& v2) const // �������� + ��� ����������� ����
{
    vector r = *this;
    return r += v2;
}

template <class T, size_t N>
vector<T, N> vector<T, N>::operator - (const vector<T, N>& v2) const // �������� - ��� ����������� ����
{
    vector r = *this;
    return r -= v2;
}

template <class T, size_t N>
vector<T, N>& vector<T, N>::operator *= (const T& a) // �������� *= ��� ���������� ���� (��������� �� ������)
{
    for (size_t i = 0; i < N; ++i)
        vec[i] *= a;

    return *this;
}

template <class T, size_t N>
vector<T, N>& vector<T, N>::operator /= (const T& a) // �������� /= ��� ���������� ���� (������� �� ������)
{
    for (size_t i = 0; i < N; ++i)
        vec[i] /= a;

    return *this;
}

template <class T, size_t N>
vector<T, N> vector<T, N>::operator * (const T& a) const
{
    vector r = *this;
    return r *= a;
}

template <class T, size_t N>
vector<T, N> vector<T, N>::operator / (const T& a) const
{
    vector r = *this;
    return r /= a;
}

template <class T, size_t N>
T vector<T, N>::operator * (const vector<T, N>& v2) const // ��������� ���������
{
    T r = 0;
    for (size_t i = 0; i < N; ++i)
        r += (vec[i] * v2[i]);

    return r;
}

template <class T, size_t N>
bool vector<T, N>::operator == (const vector<T, N>& v2) const
{
    for (size_t i = 0; i < N; ++i)
        if (vec[i] != v2[i])
            return false;

    return true;
}

template <class T, size_t N>
vector<T, N> vector<T, N>::operator - () const // ������� -
{
    vector<T, N> r;
    for (size_t i = 0; i < N; ++i)
        r[i] = -vec[i];

    return r;
}

template <class T, size_t N>
std::istream& operator >> (std::istream& stream, vector<T, N>& v) // ����
{
    for (size_t i = 0; i < N; ++i)
        std::cin >> v[i];

    return stream;
}

template <class T, size_t N>
std::ostream& operator << (std::ostream& stream, const vector<T, N>& v) // �����
{
    stream << "(" << v[0];
    for (size_t i = 1; i < N; ++i)
        stream << ", " << v[i];

    return stream << ")";
}

#endif // VECTOR_H_INCLUDED
