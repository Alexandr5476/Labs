#include <iostream>
#include <complex>
#include "complex.h"
#include "test.h"
#include <sstream>
#include <string>
#include <vector>

int main()
{
    setlocale (LC_CTYPE, "Russian");

    /* Операции с двумя комплексными числами */
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

    /* Операции с комплексным и вещественным числом */
    testr(45.8, 19,    -8.31 );
    testr(45.8, 19,     0    );
    testr(0,    0,     -8    );
    testr(12.6, 0,      9.5  );
    testr(-13, -9.2,   -13.7 );
    testr(61.9, 15,     48.51);

    /* Операции с комлексным и веществееным числом (комбинации из 0 и 1 длины 3) */
    for (unsigned i = 1; i < 16; ++i)
    {
        test(((i & 8) >> 3), ((i & 4) >> 2),  ((i & 2) >> 1), (i & 1));
    }

    /* Операции с двумя комлексным числами (комбинации из 0 и 1 длины 4) */
    for (unsigned i = 1; i < 8; ++i)
    {
        testr(((i & 4) >> 2),  ((i & 2) >> 1), (i & 1));
    }

    /* Проверка сравнений, унарных + и -, сопряжённого и модуля */
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
                    COMP(x1.conj(), std::conj(y1), "сопряжённое");
                    COMP(-x1, -y1, "унарный -"); COMP(+x1, +y1, "унарный +");
                }
            }
        }
    }

    /* Длинное выражение */
    complex x1(132.4,  -0.23), x2(-93.3281, 13);
    std::complex<double> y1(132.4,  -0.23), y2(-93.3281, 13);
    x1 += (x2 * x1 - x2 + 7. / (x2 -= (x1 *= 6.)) - (4. * (x1 /= 5.)));
    y1 += (y2 * y1 - y2 + 7. / (y2 -= (y1 *= 6.)) - (4. * (y1 /= 5.)));
    COMP(x1, y1, "длинное выражение");
    COMP(x2, y2, "длинное выражение");

    /* Ввод и вывод */
    IOTEST(complex( 2,  3), "2 + 3i" , "2 3"  );
    IOTEST(complex(-2,  3), "-2 + 3i", "-2 3" );
    IOTEST(complex( 2, -3), "2 - 3i" , "2 -3" );
    IOTEST(complex(-2, -3), "-2 - 3i", "-2 -3");
    IOTEST(complex( 5,  0), "5"      , "5 0"  );
    IOTEST(complex(-5,  0), "-5"     , "-5 0" );
    IOTEST(complex( 0,  4), "4i"     , "0 4"  );
    IOTEST(complex( 0, -4), "-4i"    , "0 -4" );
    IOTEST(complex( 1,  0), "1"      , "1 0"  );
    IOTEST(complex(-1,  0), "-1"     , "-1 0" );
    IOTEST(complex( 0,  1), "i"      , "0 1"  );
    IOTEST(complex( 0, -1), "-i"     , "0 -1" );
    IOTEST(complex( 1,  8), "1 + 8i" , "1 8"  );
    IOTEST(complex( 7,  1), "7 + i"  , "7 1"  );
    IOTEST(complex( 7, -1), "7 - i"  , "7 -1" );
    IOTEST(complex( 0,  0), "0"      , "0 0"  );


    std::cout << "Success" << std::endl;

    complex a;
    int b;
    std::cout << "Введите число: ";
    std::cin >> a;
    std::cout << "Введите степень: ";
    std::cin >> b;
    std::cout << std::endl << a << " в степени " << b << ": "<< a.pow(b) << std::endl;

    std::vector<complex> array(b);
    array = a.sqrt(b);
    std::cout << std::endl << "Корни степени " << b << " из числа " << a << ":" << std::endl;
    for(auto& i: array)
        std::cout << i << std::endl;


    return 0;

}
