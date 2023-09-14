#include "test.h"
#include "complex.h"
#include <complex>

void test(double re1, double im1, double re2, double im2)
{
    complex x1((re1), (im1)), x2((re2), (im2)), x;
    std::complex<double> y1((re1), (im1)), y2((re2), (im2)), y;

    x = x1 + x2; y = y1 + y2; COMP(x, y, "+");
    x = x1 - x2; y = y1 - y2; COMP(x, y, "-");
    x = x1 * x2; y = y1 * y2; COMP(x, y, "*");
    if (x2 != complex(0, 0))
    {
        x = x1 / x2; y = y1 / y2; COMP(x, y, "/");
        x = x1; y = y1; x /= x2; y /= y2; COMP(x, y, "/=");
    }

    x = x1; y = y1; x += x2; y += y2; COMP(x, y, "+=");
    x = x1; y = y1; x -= x2; y -= y2; COMP(x, y, "-=");
    x = x1; y = y1; x *= x2; y *= y2; COMP(x, y, "*=");
}


void testr(double re1, double im1, double num)
{
    complex x1((re1), (im1)), x;
    std::complex<double> y1((re1), (im1)), y;

    x = x1 + num; y = y1 + num; COMP(x, y, "+");
    x = x1 - num; y = y1 - num; COMP(x, y, "-");
    x = x1 * num; y = y1 * num; COMP(x, y, "*");
    if (num != 0)
    {
        x = x1 / num; y = y1 / num; COMP(x, y, "/");
        x = x1; y = y1; x /= num; y /= num; COMP(x, y, "/=");
    }

    x = x1; y = y1; x += num; y += num; COMP(x, y, "+=");
    x = x1; y = y1; x -= num; y -= num; COMP(x, y, "-=");
    x = x1; y = y1; x *= num; y *= num; COMP(x, y, "*=");

    x = num + x1; y = num + y1; COMP(x, y, "+");
    x = num - x1; y = num - y1; COMP(x, y, "-");
    x = num * x1; y = num * y1; COMP(x, y, "*");
    if (x1 != complex(0, 0))
    {
        x = num / x1; y = num / y1; COMP(x, y, "/");
        x = num; y = num; x /= x1; y /= y1; COMP(x, y, "/=");
    }

    x = num; y = num; x += x1; y += y1; COMP(x, y, "+=");
    x = num; y = num; x -= x1; y -= y1; COMP(x, y, "-=");
    x = num; y = num; x *= x1; y *= y1; COMP(x, y, "*=");
}
