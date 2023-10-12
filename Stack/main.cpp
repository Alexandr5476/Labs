#include <iostream>
#include "stack.h"
#include <vector>

int main()
{
    setlocale (LC_CTYPE, "Russian");

    stack s;

    s.push(1);s.push(2);s.push(3);s.push(4);
    std::cout << "����: " << s << std::endl;

    stack s_copy(s);
    std::cout << "����� �����: " << s_copy << std::endl;

    stack s_new;
    s_new.push(11);s_new.push(12);
    std::cout << "������������ � ������ ����: " << (s_new = s) << std::endl;

    std::cout << "������� �������: ";
    std::cin >> s;
    std::cout << "���������� ��������� ��������: " << s << std::endl;

    std::cout << "������� �� �������: " << s.get_front() << std::endl;

    std::cout << "���������� ���������: " << s.size() << std::endl;

    s.clean();
    std::cout << "����� clean: " << s << std::endl;
    std::cout << "���������� ���������: " << s.size() << std::endl;

    s.push(7);
    std::cout << "�������� ���� �������: " << s << std::endl;
    std::cout << "���������� ���������: " << s.size() << std::endl;

    s.push(8);s.push(9);s.push(10);s.push(11);s.push(12);s.push(13);
    std::cout << "���������� ���������: " << s << std::endl;

    s.insert(61, 5);
    std::cout << "���������� �������� 61 �� 5 �����: " << s << std::endl;

    s.remove(5);
    std::cout << "�������� �������� �� 5 �����: " << s << std::endl;

    s.reverse();
    std::cout << "���������: " << s << std::endl;

    s.substack_safe(4, 1, -1);
    std::cout << "������� (4,1,-1): " << s << std::endl;

    std::vector<int> a(10);
    stack ss;
    ss.push(9);ss.push(8);ss.push(7);ss.push(6);ss.push(5);ss.push(4);ss.push(3);ss.push(2);ss.push(1);ss.push(0);

    U 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}); TEST(0, 100, 1, ss, a);

    U 0, 2, 4, 6, 8});                TEST(0, 100, 2, ss, a);

    U 0, 3, 6, 9});                   TEST(0, 100, 3, ss, a);

    U 1, 2, 3, 4, 5, 6, 7});          TEST(1, 7, 1, ss, a);

    U 1, 2, 3, 4, 5, 6, 7});          TEST(7, 1, 1, ss, a);

    U 1, 3, 5, 7});                   TEST(1, 7, 2, ss, a);

    U 1, 4, 7});                      TEST(1, 7, 3, ss, a);

    U 2, 3, 4, 5, 6, 7, 8, 9});       TEST(-8, 9, 1, ss, a);

    U 2, 4, 6, 8});                   TEST(-8, 9, 2, ss, a);

    U 2, 5, 8});                      TEST(-8, 9, 3, ss, a);

    U 0, 1, 2, 3});                   TEST(-23, -7, 1, ss, a);

    U 0, 2});                         TEST(-23, -7, 2, ss, a);

    U 0, 3});                         TEST(-23, -7, 3, ss, a);

    U 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}); TEST(0, 100, -1, ss, a);

    U 9, 7, 5, 3, 1});                TEST(0, 100, -2, ss, a);

    U 9, 6, 3, 0});                   TEST(0, 100, -3, ss, a);

    U 7, 6, 5, 4, 3, 2, 1});          TEST(1, 7, -1, ss, a);

    U 7, 6, 5, 4, 3, 2, 1});          TEST(7, 1, -1, ss, a);

    U 7, 5, 3, 1});                   TEST(1, 7, -2, ss, a);

    U 7, 5, 3, 1});                   TEST(7, 1, -2, ss, a);

    U 7, 4, 1});                      TEST(1, 7, -3, ss, a);

    U 9, 8, 7, 6, 5, 4, 3, 2});       TEST(-8, 9, -1, ss, a);

    U 9, 7, 5, 3});                   TEST(-8, 9, -2, ss, a);

    U 9, 6, 3});                      TEST(-8, 9, -3, ss, a);

    U 9, 6, 3});                      TEST(9, -8, -3, ss, a);

    U 3, 2, 1, 0});                   TEST(-23, -7, -1, ss, a);

    U 3, 1});                         TEST(-23, -7, -2, ss, a);

    U 3, 0});                         TEST(-23, -7, -3, ss, a);

    U 3, 0});                         TEST(-7, -23, -3, ss, a);

    std::cout << "�����: Success" << std::endl;

    return 0;
}
