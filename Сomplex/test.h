#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <cmath>
#include <iostream>

#define COMP(x, y, oper)                                                                                   \
{                                                                                                          \
    if ((abs(((x).getre()) - ((y).real())) > 0.00001) || (abs(((x).getim()) - ((y).imag())) > 0.00001))    \
    {                                                                                                      \
        std::cout << "Test ERROR:\n  My: " << (x) <<                                                       \
        std::endl << "  Std: " << (y) << std::endl <<                                                      \
        "  Operator: " << oper << std::endl <<                                                             \
        "  Line: " << __LINE__ << std::endl <<                                                             \
        "  File: " << __FILE__ << std::endl;                                                               \
        exit(-1);                                                                                          \
    }                                                                                                      \
}

#define IOTEST(x, out, in)                                                                                 \
{                                                                                                          \
    std::stringstream ss;                                                                                  \
    ss << x;                                                                                               \
    if (ss.str() != out)                                                                                   \
    {                                                                                                      \
        std::cout << "Out test error: "                                                                    \
        << #x << "  ---  " << "'" << ss.str() << "'"                                                       \
        << "  instead of  " << "'" << out << "'"                                                           \
        << "  (" << "line: " << __LINE__ << ")"<< std::endl;                                               \
    }                                                                                                      \
                                                                                                           \
    ss.str(in);                                                                                            \
    complex x_in;                                                                                          \
    ss >> x_in;                                                                                            \
    if (x_in != x)                                                                                         \
    {                                                                                                      \
        std::cout << "In test error: "                                                                     \
        << #x << "  ---  " << x_in                                                                         \
        << "  instead of  " << x                                                                           \
        << "  (" << "line: " << __LINE__ << ")" << std::endl;                                              \
    }                                                                                                      \
}

void test(double re1, double im1, double re2, double im2);

void testr(double re1, double im1, double num);

#endif // TEST_H_INCLUDED
