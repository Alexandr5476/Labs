#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <cmath>
#include <iostream>


/** x - моё комплексное чилсо, y --- стандартное комплексное число
  * строка oper - операция, с помощью которой получились эти числа (просто чтобы вывести её при ошибке)
  * Макрос сравнивает x и y, если они не равны, то выводит сообщение об ошибке и завершает работу программы
  */
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


/** Тест ввода-вывода
  * x - комплексное число,
  * out - строка, в которой содержится то, что должно быть выведено при выводе x
  * in - строка, в которой содержится то, что должно быть введено для ввода x
  */
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


/** Тестирует бинарные операции с двумя комплексными числами,
  * сравнивая результаты с тем, что получается
  * при использовании стандартной библиотеки
  */
void test(double re1, double im1, double re2, double im2);


/** Тестирует бинарные операции с комплексным и вещественным числом (с обоих сторон)
  * сравнивая результаты с тем, что получается
  * при использовании стандартной библиотеки
  */
void testr(double re1, double im1, double num);

#endif // TEST_H_INCLUDED
