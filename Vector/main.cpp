#include <iostream>
#include "vector.h"

int main()
{
    setlocale (LC_CTYPE, "Russian");

    std::cout << "������� ��� �������: ";
    vector<double, 4> v1, v2;
    std::cin >> v1 >> v2;

    std::cout << std::endl;
    std::cout << "C����: " << v1 + v2 << std::endl <<
                 "��������: " << v1 - v2 << std::endl <<
                 "��������� �� ������: " << v1 * 5 << std::endl <<
                 "������� �� ������: " << v1 / 2 << std::endl <<
                 "��������� ������������: " << v1 * v2  << std::endl <<
                 "������� + ��� �������: " << (+v1) << std::endl <<
                 "������� + ��� �������: " << (+v2) << std::endl <<
                 "������� - ��� �������: " << (-v1) << std::endl <<
                 "������� - ��� �������: " << (-v2) << std::endl <<
                 "���������: " << (v1 == v2 ? "��" : "���") << std::endl <<
                 "�� ���������: " << (v1 != v2 ? "��" : "���") << std::endl <<
                 "����� �������: " << v1.norm() << std::endl <<
                 "����� �������: " << v2.norm() << std::endl <<
                 "����������: " << v1.dist(v2) << std::endl <<
                 "����: " << v1.angle(v2) << std::endl;
    return 0;
}
