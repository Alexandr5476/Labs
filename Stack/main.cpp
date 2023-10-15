#include <iostream>
#include "stack.h"
#include <vector>
#include <assert.h>

int main()
{
    setlocale (LC_CTYPE, "Russian");

    stack s;

    s.push(1);s.push(2);s.push(3);s.push(4);
    std::cout << "Стек: " << s << std::endl;

    stack s_copy(s);
    std::cout << "Копия стека: " << s_copy << std::endl;

    stack s_new;
    s_new.push(11);s_new.push(12);
    std::cout << "Присваивание в другой стек: " << (s_new = s) << std::endl;

    std::cout << "Введите элемент: ";
    std::cin >> s;
    std::cout << "Добавление введённого элемента: " << s << std::endl;

    std::cout << "Количество элементов: " << s.size() << std::endl;

    s.clean();
    std::cout << "После clean: " << s << std::endl;
    std::cout << "Количество элементов: " << s.size() << std::endl;

    s.push(7);
    std::cout << "Добавили один элемент: " << s << std::endl;
    std::cout << "Количество элементов: " << s.size() << std::endl;

    s.push(8);s.push(9);s.push(10);s.push(11);s.push(12);s.push(13);
    std::cout << "Добавление элементов: " << s << std::endl;

    s.insert(-61, 5);
    std::cout << "Добавление элемента 61 на 5 место: " << s << std::endl;

    s.remove(5);
    std::cout << "Удаление элемента на 5 месте: " << s << std::endl;

    s.insert_safe(-61, 193);
    std::cout << "Безопасное добавление элемента в конец: " << s <<std::endl;

    s.remove_safe(179);
    std::cout << "Безопасное удаление элемента из конца: " << s << std::endl;

    s.reverse();
    std::cout << "Переворот: " << s << std::endl;

    s += s_copy;
    std::cout << "Соединение с последней копией: " << s << std::endl;
    std::cout << "Копия теперь: " << s_copy << std::endl;


    stack r(s_copy + s);
    std::cout << "Соединение с копией (в новый стек r): " << r <<std::endl;

    r = r + r;
    std::cout << "Соединение двух r: " << r << std::endl;

    r.get_front() = -9;
    std::cout << "Изменение элемента в вершине: " << r << std::endl;

    r[7] = -15;
    std::cout << "Изменение элемента c индексом 7: " << r << std::endl;

    r(137) = -4;
    std::cout << "Безопасное изменение последнего элемента: " << r << std::endl;

    r.mix();
    std::cout << "Перемешивание: " << r << std::endl;


   /* Тесты опрераций сравнения */
    assert(!(s > r));     assert(r > s);        assert(!(r > r));
    assert(!(s >= r));    assert(r >= s);       assert(r >= r);
    assert(s < r);        assert(!(r < s));     assert(!(r < r));
    assert(s <= r);       assert(!(r <= s));    assert(r <= r);
    assert(!(s == r));    assert(!(r == s));    assert(r == r);

    r.clean(5);
    std::cout << "Удаление первых 5 элементов: " << r << std::endl;

    r.rclean(3);
    std::cout << "Удаление последних 3 элементов: " << r << std::endl;

    r.rclean(1);
    std::cout << "Удаление последнего элемента: " << r << std::endl;

    r.insert(-91);
    std::cout << "Добение элемента в конец: " << r << std::endl;
    std::cout << "Элемент в конце: " << r() << std::endl;

    int e;
    r.remove(e);
    std::cout << "Удаление элеметна " << e << " (из конца): " << r <<std::endl; 

    assert(r.is_not_empty());

    r.clean_safe(821);
    std::cout << "Безопасное удаление всех элементов: " << r << std::endl;

    assert(r.is_empty());

    while(s.is_not_empty()) s.pop(); 
    std::cout << "Удаление с помощью pop: " << s << std::endl;

    std::cout << "Добавление двух элементов: "<< s.push(6).push(7) << std::endl;
    std::cout << "Удаление с конца: "<< s.rclean(1) << std::endl;
    std::cout << "Ещё раз удаление с конца: " << s.rclean(1) << std::endl;

    
    std::cout << "Добавление трёх элементов: "<< s.push(6).push(7).push(8) << std::endl;
    std::cout << "Удаление с конца трёх элементов: "<< s.rclean(3) << std::endl;

    std::cout << "Безопасная вставка элемнтa: " << s.insert_safe(1, 9).insert_safe(2, 1).insert_safe(3, 0).insert_safe(0, 3) << std::endl;
    while (s.is_not_empty())
    {
        s.remove_safe(2, e);
        std::cout << "Безопасно удалён элемент с индексом 2 (" << e << "): " << s <<std::endl;
    }

    /* Тесты выделения подстека */
    std::vector<int> a(10);
    stack ss;
    ss.push(9);ss.push(8);ss.push(7);ss.push(6);ss.push(5);ss.push(4);ss.push(3);ss.push(2);ss.push(1);ss.push(0);

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

    std::cout << "Тесты: Success" << std::endl << std::endl;

    r.clean();
    std::cout << "Безопасная вствка элементов: " << r.insert_safe(1, 2).insert_safe(3, 2).insert_safe(-1, 2)
    .insert_safe(9, 2).insert_safe(2, 0).insert_safe(-5, 10) <<std::endl;
    while (r.is_not_empty())
    {
        int e;
        r.remove_safe(5, e);
        std::cout << "Безопасно удалён элемент с индексом 5" << " (" << e << ")"<< ": " << r << std::endl;
    } 

    std::cout << "Вствка элементов (push): " << r.push(1).push(3).push(-1).push(9).push(2).push(-5) <<std::endl;
    while (r.is_not_empty())
    {
        int e;
        r.pop(e);
        std::cout << "Удаление элемента (pop)" << " (" << e << ")"<< ": " << r << std::endl;
    }

    std::cout << "Вствка элементов в конец (insert): " << r.insert(1).insert(3).insert(-1).insert(9).insert(2).insert(-5) <<std::endl;
    while (r.is_not_empty())
    {
        int e;
        r.remove(e);
        std::cout << "Удаление элемента из конца (remove)" << " (" << e << ")"<< ": " << r << std::endl;
    }

    std::cout << "Вствка элементов (insert с указанием индекса): " << r.insert(1, 0).insert(3, 1).insert(-1, 2).insert(9, 3).insert(2, 2).insert(-5, 1) <<std::endl;
    int t = 5;
    while (t > 1)
    {
        --t;
        int e;
        r.remove(2, e);
        std::cout << "Удаление элемента (remove индекс 2)" << " (" << e << ")"<< ": " << r << std::endl;
    }

    r.remove(1, e); std::cout << "Удаление элемента (remove индекс 1)" << " (" << e << ")"<< ": " << r << std::endl;
    r.remove(0, e); std::cout << "Удаление элемента (remove индекс 0)" << " (" << e << ")"<< ": " << r << std::endl << std::endl;

    std::cout << "Умножение на -3 стека " << s_new << ":  " << (s_new *= -3) << std::endl;
    std::cout << "Деление на 4 :  " << (s_new /= 4) << std::endl;
    r = s_new * 5;
    std::cout << "Умножение на 5 :  " << r << std::endl;


    return 0;
}
