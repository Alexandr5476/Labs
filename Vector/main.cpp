#include <iostream>
#include "vector.h"

int main()
{
    setlocale (LC_CTYPE, "Russian");

    std::cout << "Введите два вектора: ";
    vector<double, 4> v1, v2;
    std::cin >> v1 >> v2;

    std::cout << std::endl;
    std::cout << "Cумма: " << v1 + v2 << std::endl <<
                 "Разность: " << v1 - v2 << std::endl <<
                 "Умножение на скаляр: " << v1 * 5 << std::endl <<
                 "Деление на скаляр: " << v1 / 2 << std::endl <<
                 "Скалярное произведение: " << v1 * v2  << std::endl <<
                 "Унарный + для первого: " << (+v1) << std::endl <<
                 "Унарный + для второго: " << (+v2) << std::endl <<
                 "Унарный - для первого: " << (-v1) << std::endl <<
                 "Унарный - для второго: " << (-v2) << std::endl <<
                 "Равенство: " << (v1 == v2 ? "да" : "нет") << std::endl <<
                 "Не равенство: " << (v1 != v2 ? "да" : "нет") << std::endl <<
                 "Норма первого: " << v1.norm() << std::endl <<
                 "Норма второго: " << v2.norm() << std::endl <<
                 "Расстояние: " << v1.dist(v2) << std::endl <<
                 "Угол: " << v1.angle(v2) << std::endl;
    return 0;
}
