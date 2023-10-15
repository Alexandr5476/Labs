#include <iostream>
#include "queue.h"
#include <assert.h>
#include <vector>

int main()
{
    setlocale (LC_CTYPE, "Russian");
    queue q;

    std::cout << "���������� ���������: " << q.push(5).push(7).push(9).push(-4).push(2).push(3) << std::endl;
    
    std::cout << "�������� ��� ���������: " << q.clean(3) << std::endl;

    queue q_copy(q);
    std::cout << "�����: " << q_copy << std::endl;
    
    std::cout << "���������� �������� ���� ���������: " << q.clean_safe(12) << std::endl;

    std::cout << "���������� ���������: " << q.push(5).push(7).push(9).push(-4).push(2).push(3) << std::endl;

    std::cout << "�������� ��� ��������� � �����: " << q.rclean(3) << std::endl;
    std::cout << "�������� ��� ��������� � �����: " << q.rclean(3) << std::endl;

    std::cout << "���������� ���������: " << q.push(5).push(7).push(9) << std::endl;
    std::cout << "�������� �������� � �����: " << q.rclean(1) << std::endl;
    std::cout << "�������� �������� � �����: " << q.rclean(1) << std::endl;
    std::cout << "�������� �������� � �����: " << q.rclean(1) << std::endl;

    std::cout << "���������� ���������: " << q.push(31).push(22) << std::endl;

    std::cout << "����������� ����: " << (q += q) << std::endl;
    queue r = q + q_copy;
    std::cout << "���������� � ������: " << r << std::endl;

    std::cout << "���������: " << r.reverse() << std::endl;

    std::cout << "�������������: " << r.mix() << std::endl;

    assert(q < r);     assert(!(r < q));  assert(!(r < r));
    assert(q <= r);    assert(!(r <= q)); assert(r <= r);
    assert(!(q > r));  assert(r > q);     assert(!(r > r));
    assert(!(q >= r)); assert(r >= q);    assert(r >= r);
    assert(!(q == r)); assert(!(r == q)); assert(r == r);

    r.clean();
    std::cout << "���������� ������ ���������: " << r.insert_safe(1, 2).insert_safe(3, 2).insert_safe(-1, 2)
    .insert_safe(9, 2).insert_safe(2, 0).insert_safe(-5, 10) <<std::endl;
    while (r.is_not_empty())
    {
        int e;
        r.remove_safe(5, e);
        std::cout << "��������� ����� ������� � �������� 5" << " (" << e << ")"<< ": " << r << std::endl;
    } 

    std::cout << "������ ��������� (push): " << r.push(1).push(3).push(-1).push(9).push(2).push(-5) <<std::endl;
    while (r.is_not_empty())
    {
        int e;
        r.pop(e);
        std::cout << "�������� �������� (pop)" << " (" << e << ")"<< ": " << r << std::endl;
    }

    std::cout << "������ ��������� � head (insert): " << r.insert(1).insert(3).insert(-1).insert(9).insert(2).insert(-5) <<std::endl;
    while (r.is_not_empty())
    {
        int e;
        r.remove(e);
        std::cout << "�������� �������� �� tail (remove)" << " (" << e << ")"<< ": " << r << std::endl;
    }

    std::cout << "������ ��������� (insert � ��������� �������): " << r.insert(1, 0).insert(3, 1).insert(-1, 2).insert(9, 3).insert(2, 2).insert(-5, 1) <<std::endl;
    int t = 5;
    while (t > 1)
    {
        --t;
        int e;
        r.remove(2, e);
        std::cout << "�������� �������� (remove ������ 2)" << " (" << e << ")"<< ": " << r << std::endl;
    }
    int e;
    r.remove(1, e); std::cout << "�������� �������� (remove ������ 1)" << " (" << e << ")"<< ": " << r << std::endl;
    r.remove(0, e); std::cout << "�������� �������� (remove ������ 0)" << " (" << e << ")"<< ": " << r << std::endl;


    /* ����� ��������� �������� */
    std::vector<int> a(10);
    queue ss;
    ss.push(9);ss.push(8);ss.push(7);ss.push(6);ss.push(5);ss.push(4);ss.push(3);ss.push(2);ss.push(1);ss.push(0);
    std::cout << "�������: " << ss.reverse() << std::endl;

    a.clear(); a.insert(a.end(), {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}); TEST(0, 100, 1, ss, a);

    a.clear(); a.insert(a.end(), {0, 2, 4, 6, 8});                TEST(0, 100, 2, ss, a);

    a.clear(); a.insert(a.end(), {0, 3, 6, 9});                   TEST(0, 100, 3, ss, a);

    a.clear(); a.insert(a.end(), {1, 2, 3, 4, 5, 6, 7});          TEST(1, 7, 1, ss, a);

    a.clear(); a.insert(a.end(), {1, 2, 3, 4, 5, 6, 7});          TEST(7, 1, 1, ss, a);

    a.clear(); a.insert(a.end(), {1, 3, 5, 7});                   TEST(1, 7, 2, ss, a);

    a.clear(); a.insert(a.end(), {1, 4, 7});                      TEST(1, 7, 3, ss, a);

    a.clear(); a.insert(a.end(), {2, 3, 4, 5, 6, 7, 8, 9});       TEST(-8, 9, 1, ss, a);

    a.clear(); a.insert(a.end(), {2, 4, 6, 8});                   TEST(-8, 9, 2, ss, a);

    a.clear(); a.insert(a.end(), {2, 5, 8});                      TEST(-8, 9, 3, ss, a);

    a.clear(); a.insert(a.end(), {0, 1, 2, 3});                   TEST(-23, -7, 1, ss, a);

    a.clear(); a.insert(a.end(), {0, 2});                         TEST(-23, -7, 2, ss, a);

    a.clear(); a.insert(a.end(), {0, 3});                         TEST(-23, -7, 3, ss, a);

    a.clear(); a.insert(a.end(), {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}); TEST(0, 100, -1, ss, a);

    a.clear(); a.insert(a.end(), {9, 7, 5, 3, 1});                TEST(0, 100, -2, ss, a);

    a.clear(); a.insert(a.end(), {9, 6, 3, 0});                   TEST(0, 100, -3, ss, a);

    a.clear(); a.insert(a.end(), {7, 6, 5, 4, 3, 2, 1});          TEST(1, 7, -1, ss, a);

    a.clear(); a.insert(a.end(), {7, 6, 5, 4, 3, 2, 1});          TEST(7, 1, -1, ss, a);

    a.clear(); a.insert(a.end(), {7, 5, 3, 1});                   TEST(1, 7, -2, ss, a);

    a.clear(); a.insert(a.end(), {7, 5, 3, 1});                   TEST(7, 1, -2, ss, a);

    a.clear(); a.insert(a.end(), {7, 4, 1});                      TEST(1, 7, -3, ss, a);

    a.clear(); a.insert(a.end(), {9, 8, 7, 6, 5, 4, 3, 2});       TEST(-8, 9, -1, ss, a);

    a.clear(); a.insert(a.end(), {9, 7, 5, 3});                   TEST(-8, 9, -2, ss, a);

    a.clear(); a.insert(a.end(), {9, 6, 3});                      TEST(-8, 9, -3, ss, a);

    a.clear(); a.insert(a.end(), {9, 6, 3});                      TEST(9, -8, -3, ss, a);

    a.clear(); a.insert(a.end(), {3, 2, 1, 0});                   TEST(-23, -7, -1, ss, a);

    a.clear(); a.insert(a.end(), {3, 1});                         TEST(-23, -7, -2, ss, a);

    a.clear(); a.insert(a.end(), {3, 0});                         TEST(-23, -7, -3, ss, a);

    a.clear(); a.insert(a.end(), {3, 0});                         TEST(-7, -23, -3, ss, a);

    std::cout << "�����: Success" << std::endl << std::endl;

    queue q_new;
    std::cout << "��������� �� -4 ������� " << (q_new = q_copy) << ":  " << (q_new *= -4) << std::endl;
    std::cout << "������� �� 3 :  " << (q_new /= 3) << std::endl;
    r = q_new * 2;
    std::cout << "��������� �� 2 :  " << r << std::endl;

    return 0;
}
