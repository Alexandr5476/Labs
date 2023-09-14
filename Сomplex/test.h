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
        "  File: " << __FILE__  << std::endl;                                                              \
        exit(-1);                                                                                          \
    }                                                                                                      \
}

void test(double re1, double im1, double re2, double im2);

void testr(double re1, double im1, double num);

#endif // TEST_H_INCLUDED
