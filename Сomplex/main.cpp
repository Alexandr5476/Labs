#include <iostream>
#include <complex>
#include "complex.h"
#include "test.h"

int main()
{
    setlocale (LC_CTYPE, "Russian");

    test( 1,   2,      3,   4);
    test(-1,  -2,     -3,  -4);
    test( 1,  -2,      3,   4);
    test( 1,  -2,      3,  -4);
    test( 1,  -2,     -3,   4);
    test( 1,   2,     -3,   4);
    test(-1,  -2,      3,   4);
    test( 1,  -2,     -3,  -4);

    test( 3.2,     12,        -8,        9.281 );
    test( 132.4,  -0.23,      -93.3281,  3     );
    test(-67.819, -7.231,     -8.23,    -13.888);
    test(42.3,     12,         97.22,    143.11);

    testr(45.8, 19,    -8.31 );
    testr(45.8, 19,     0    );
    testr(0,    0,     -8    );
    testr(12.6, 0,      9.5  );
    testr(-13, -9.2,   -13.7 );
    testr(61.9, 15,     48.51);

    for (unsigned i = 1; i < 16; ++i)
    {
        test(((i & 8) >> 3), ((i & 4) >> 2),  ((i & 2) >> 1), (i & 1));
    }

    for (unsigned i = 1; i < 8; ++i)
    {
        testr(((i & 4) >> 2),  ((i & 2) >> 1), (i & 1));
    }

    for (int i1 = -5; i1 < 6; ++i1)
    {
        for (int i2 = -5; i2 < 6; ++i2)
        {
            for (int i3 = -5; i3 < 6; ++i3)
            {
                for (int i4 = -5; i4 < 6; ++i4)
                {
                    complex x1(i1, i2), x2(i3, i4);
                    std::complex<double> y1(i1, i2), y2(i3, i4);
                    if((x1 == x2) != (y1 == y2)) exit(-2);
                    if((x1 != x2) != (y1 != y2)) exit(-3);
                    if((x1 == (double)i1) != (y1 == (double)i1)) exit(-4);
                    if(((double)i2 == x2) != ((double)i2 == y2)) exit(-5);
                    if((x1 != (double)i1) != (y1 != (double)i1)) exit(-6);
                    if(((double)i2 != x2) != ((double)i2 != y2)) exit(-7);
                    if(x1.abs() != std::abs(y1)) exit(-8);
                    COMP(x1.conj(), std::conj(y1), "сопр€жЄнное");
                    COMP(-x1, -y1, "унарный -"); COMP(+x1, +y1, "унарный +");
                }
            }
        }
    }

    complex x1(132.4,  -0.23), x2(-93.3281, 13);
    std::complex<double> y1(132.4,  -0.23), y2(-93.3281, 13);

    x1 += (x2 * x1 - x2 + 7. / (x2 -= (x1 *= 6.)) - (4. * (x1 /= 5.)));
    y1 += (y2 * y1 - y2 + 7. / (y2 -= (y1 *= 6.)) - (4. * (y1 /= 5.)));
    COMP(x1, y1, "длинное выражение");
    COMP(x2, y2, "длинное выражение");

    std::cout << "Success" << std::endl;
    std::cout << "¬ведите число: ";
    complex t;
    std::cin >> t;
    std::cout << std::endl << "¬ведЄнное число: " << t << std::endl;

    return 0;
}
