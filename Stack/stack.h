#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <ostream>
#include <istream>
#include <iostream>

class stack
{
public:
    stack (): top(NULL) {} // Конструктор по умолчанию ?

    stack (const stack& orig); // Конструктор копирования

    stack (stack&& orig): top(orig.top) {orig.top = NULL;} // Конструктор перемещения

    ~stack () {this->clean();} // Деструктор ?

    stack& operator = (const stack& orig); // Операция присваивания

    stack& operator = (stack&& orig); // Операция присваивания по перемещению

    bool is_empty () {if (top) return false; return true;} // Проверка на пустоту

    int get_front () const {return top->element;} // Получение элемента из вершины

    stack& push (int e); // Добавление элемента

    stack& pop (); // Удаление элемента

    stack& pop (int& e) {e = this->get_front(); return this->pop();} // Получение и удаление элемента

    friend std::ostream& operator << (std::ostream& stream, const stack& s); // Вывод

    friend std::istream& operator >> (std::istream& stream, stack& s); // Ввод

    stack& clean (); // Очистка стека

    size_t size () const {size_t i = 0; for (node *n = top; n; n = n->next) ++i; return i;} // Количесво элементов в стеке

    stack& reverse (); // Переворот стека

    /* stack& add (const stack& added); // Соединение двух стеков */

    /* Индекс вершины --- 0 */
    stack& insert (int e, size_t i = 0); // Вставка элемента по индексу (вставляемый элемент будет иметь этот индекс)

    /* Вставка элемента по индексу с проверкой (если индекс выходит за конец стека, то элемент вставится в конец) */
    stack& insert_safe (int e, size_t i = 0) {size_t len = this->size(); if (i >= len) i = len - 1; return this->insert(e, i);}

    stack& remove (size_t i = 0); // Удаление элемента по индексу

    stack& substack (size_t beg, size_t end, size_t step = 1); // Выделение подстека (индексы beg и end должны быть внутри стека)

    /* отрицательная индексация с другой стороны (-1 --- индекс последнего элемента стека)
     * отрицательный шаг --- подстек начинает выделятся с конца в обратную сторону
     * если индекс end левее beg, то они меняются местами
     * если beg указывает за начало, ты выделение начинается с вершины стека
     * если end указывает за конец стека, то стек выделятся до конца
     * если step = 0, то стек очищается
     */
    stack& substack_safe (long long beg, long long end, long long step = 1); // Выделение подстека с проверками

    bool operator == (const stack& s) const; // Сравнение (применение операции == ко всем элементам)

private:
    class node // Узел
    {
    public:
        node (): next(NULL) {} // Конструктор по умолчанию
        node *next; // Указатель на седующий элемент
        int element; // Данные узла
    };
    node *top; // Указатель на вершину
};


stack::stack (const stack& orig): top(new (node)) /// Конструктор копирования
{
    node **in_copy = &top; // Указатель на указатель, куда будет помещён новый узел

    for (node *n = orig.top; n; n = n->next)
    {
        *in_copy = new node; // Выделение памяти под новый узел
        (*in_copy)->element = n->element; // Копирование данных
        in_copy = &((*in_copy)->next); // Присваивание адреса указателя на следующий узел
    }
    /* Последний указатель на следующий узел будет NULL, потому что конструктор для этого узла вызывался в new node */
}


stack& stack::operator = (const stack& orig) /// Операция присваивания
{
    if (&orig == this) return *this; // Контроль самоприсваивания

    //std::cout << std::endl << *this << std::endl;

    this->clean(); // Удаление всех узлов

    node **in_copy = &top; // Указатель на указатель, куда будет помещён новый узел

    for (node *n = orig.top; n; n = n->next)
    {
        *in_copy = new node; // Выделение памяти под новый узел
        (*in_copy)->element = n->element; // Копирование данных
        in_copy = &((*in_copy)->next); // Присваивание адреса указателя на следующий узел
    }
    /* Последний указатель на следующий узел будет NULL, потому что конструктор для этого узла вызывался в new node */

    return *this;
}


stack& stack::operator = (stack&& orig) /// Операция присваивания по перемещению
{
    if (&orig == this) return *this; // Контроль самоприсваивания

    this->clean(); // Удаление всех узлов

    top = orig.top;
    orig.top = NULL;

    return *this;
}


stack& stack::push (int e) /// Добавление элемента
{
    node *n = new node;
    n->element = e;
    n->next = top; // Если стек был пустым, то n->next останется NULL
    top = n;
    return *this;
}


stack& stack::pop() /// Удаление элемента
{
    if (!top) return *this; // Если стек пустой

    node *del = top;
    top = del->next; // Если в стеке был
    delete del;
    return *this;
}


std::ostream& operator << (std::ostream& stream, const stack& s) /// Вывод
{
    if (!(s.top))
    {
        stream << "стек пустой";
        return stream;
    }

    for (stack::node *n = (s.top); n; n = n->next)
    {
        stream << n->element << " ";
    }
    return stream;
}


std::istream& operator >> (std::istream& stream, stack& s) /// Ввод
{
    int e;
    std::cin >> e;
    s.push(e);
    return stream;
}


stack& stack::clean () /// Очистка стека
{
    if (!top) return *this;
    node *n = top, *n_next;
    while ((n_next = n->next))
    {
        //std::cout << n->element << std::endl;
        delete n;
        n = n_next;
    }
    delete n;

    top = NULL;
    return *this;
}


stack& stack::insert (int e, size_t i) /// Вставка элемента по индексу
{
    node *n = top, *new_n = new node;

    new_n->element = e;

    for (size_t j = 0; j < i - 1; ++j) n = n->next;

    node *n_next = n->next; // Если вставляют в конец стека, то n->next будет NULL
    n->next = new_n;
    new_n->next = n_next;

    return *this;
}


stack& stack::remove (size_t i) /// Удаление элемента по индексу
{
    if (!top) return *this; // Если стек пустой

    node *n = top;

    for (size_t j = 0; j < i - 1; ++j) n = n->next;

    node *del = n->next;
    n->next = del->next;
    delete del;
    return *this;
}


stack& stack::reverse () /// Переворот стека
{
    node *n = top, *n_next = n->next, *n_prev = NULL;

    while (n_next)
    {
        n->next = n_prev;
        n_prev = n;
        n = n_next;
        n_next = n->next;
    }
    n->next = n_prev;
    top = n;
    return *this;
}


stack& stack::substack (size_t beg, size_t end, size_t step) /// Выделение подстека
{
    size_t i = 0; // Текущий индекс
    node *n = top, *n_next, *cur; // n --- текущий узел, n_next --- для удаления, cur --- последний оставленный узел

    for (; i < beg; ++i) // Проходим до начала, удаляя всё на пути
    {
        n_next = n->next;
        delete n;
        n = n_next;
    }
    /* теперь n указывает на первый узел, который нужно оставить */

    cur = top = n;

    for(size_t j = i + step; i < end; j += step) // j --- индекс следующего элемента, который надо оставить (если он < end)
    { // считаем, что индекс end не может указывать за пределы стека

        /* Переходим на следующий узел после оставленного */
        ++i;
        n = n->next;

        for (; (i < j) && (i < end); ++i) // Проходим до следующего узла, который нужно оставить, удаляя всё на пути
        { // считаем, что индекс end не может указывать за пределы стека
            n_next = n->next;
            delete n;
            n = n_next;
        }

        if (j <= end) cur = cur->next = n; // Если мы ещё не прошли конец, то привязываем узел к последнему оставленному
    }

    /* Удаляем все оставшиеся элементы */
    if (n == cur) n = n->next;
    if (n)
    {
        while ((n_next = n->next))
        {
            delete n;
            n = n_next;
        }
        delete n;
        cur->next = NULL;
    }

    return *this;
}


stack& stack::substack_safe (long long beg, long long end, long long step) /// Выделение подстека с проверками
{
    if (!step) return this->clean();

    long long len = this->size();
    if (beg < 0) beg += len;
    if (end < 0) end += len;

    if (beg > end) std::swap(beg, end);

    if (beg < 0) beg = 0;
    if (end >= len) end = len - 1;

    if (step < 0)
    {
        step = -step;
        this->reverse();
        long long tmp = len - beg - 1;
        beg = len - end - 1;
        end = tmp;
    }

    return this->substack(beg, end, step);

}


bool stack::operator == (const stack& s) const /// Сравнение (применение операции == ко всем элементам)
{
    node *n1 = top, *n2 = s.top;

    for (; n1 && n2; n1 = n1->next, n2 = n2->next)
        if (n1->element != n2->element)
            return false;

    if (n1 || n2)
        return false;

    return true;
}


/* beg, end, step --- аргументы метода substack_safe
 * x --- стек, для которого вызывается substack_safe
 * y --- std::vector с элементами, которые должны быть в подстеке
 */
#define TEST(beg, end, step, x, y)                                     \
{                                                                      \
   stack copy_s(x), yes;                                               \
   for (auto& i: y)                                                    \
        yes.push(i);                                                   \
    yes.reverse();                                                     \
                                                                       \
   if (yes != copy_s.substack_safe(beg, end, step))                    \
   {                                                                   \
        std::cout << copy_s << "   instead of   " << yes << std::endl; \
        exit (-1);                                                     \
   }                                                                   \
                                                                       \
}

#define U a.clear(); a.insert(a.end(), {

#endif // STACK_H_INCLUDED
