#include "stack.h"
#include <vector>
#include <time.h>

stack::stack (const stack& orig): top(NULL) /// Конструктор копирования
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


stack& stack::clean () /// Очистка стека
{
    if (!top) return *this;

    node *n = top, *n_next;
    while ((n_next = n->next))
    {
        delete n;
        n = n_next;
    }
    delete n;

    top = NULL;
    return *this;
}


stack& stack::clean (size_t len) /// Удаление первых len узлов (len должно быть не больше длины стека)
{
    node *n = top, *n_next;
    for (size_t i = 0; i < len; ++i)
    {
        n_next = n->next;
        delete n;
        n = n_next;
    }

    top = n;
    return *this;
}


stack& stack::clean_safe (size_t len) /// Безопасное удаление первых len узлов
{
    if (!top) return *this;

    node *n = top, *n_next;
    for (size_t i = 0; i < len; ++i)
    {
        if (!(n_next = n->next)) i = len;
        delete n;
        n = n_next;
    }

    top = n; // n будет NULL, если удалён весь стек
    return *this;
}


stack& stack::rclean (size_t len) /// Удаление последних len узлов
{
    if (!top) return *this;

    if (len == 1) // Отдельно удаляем последний элемент, чтобы не проходить стек лишний раз, в этом случае
    {
        if (!top->next) // Если в стеке один элемент
        {
            delete top;
            top = NULL;
            return *this;
        }
        node *n = top, *tmp;
        while ((tmp = n->next)->next) n = tmp;
        delete n->next;
        n->next = NULL;
        return *this; 
    }

    size_t size = this->size();
    if (len >= size) return this->clean();
    
    node *n = top;
    for (size_t i = 0; i < size - len - 1; ++i) n = n->next; // Проходим до первого оставляемого узла

    node *n_next = n->next;
    n->next = NULL;
    n = n_next;
    while ((n_next = n->next))
    {
        delete n;
        n = n_next;
    }
    delete n;

    return *this;
}


stack& stack::operator = (const stack& orig) /// Операция присваивания
{
    if (&orig == this) return *this; // Контроль самоприсваивания

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
    this->clean(); // Удаление всех узлов

    top = orig.top;
    orig.top = NULL;

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
    stream >> e;
    s.push(e);
    return stream;
}


stack& stack::operator += (stack& b) /// Добавление одного стека к другому
{
    if (&b == this)
    {
        stack b2(b);
        return b += b2;
    }

    node *n = top, *tmp;
    if (top)
    {
        while ((tmp = n->next)) n = tmp;
        n->next = b.top;
    }
    else top = b.top;
    b.top = NULL;
    return *this;
}


stack stack::operator + (const stack& b) const /// Соединение двух стеков
{
    stack new_stack;
    node **in_new = &new_stack.top; // Указатель на указатель, куда будет помещён новый узел

    for (node *n = top; n; n = n->next) // Копирование из первого стека
    {
        *in_new = new node; // Выделение памяти под новый узел
        (*in_new)->element = n->element; // Копирование данных
        in_new = &((*in_new)->next); // Присваивание адреса указателя на следующий узел
    }

    for (node *n = b.top; n; n = n->next) // Копирование из второго стека
    {
        *in_new = new node; // Выделение памяти под новый узел
        (*in_new)->element = n->element; // Копирование данных
        in_new = &((*in_new)->next); // Присваивание адреса указателя на следующий узел
    }
    /* Последний указатель на следующий узел будет NULL, потому что конструктор для этого узла вызывался в new node */

    return new_stack;
}


stack stack::operator *= (int m) /// Умножение на число (добавить очередь к себе m раз; если m < 0, то перевёрнутую очередь; если m = 0, то очистить очередь)
{
    if (!m) return this->clean();
    if (m < 0) this->reverse(), m = -m;
    stack r(*this);
    for (int i = 1; i < m; ++i) r = r + *this;
    return (*this = r);
}


bool stack::operator > (const stack& s) const /// Операция > (по количеству элементов в стеке)
{
    node *n1 = top, *n2 = s.top;

    while (n1 && n2) 
    {
        n1 = n1->next; 
        n2 = n2->next;
    }

    return (n1 && !n2);
}


bool stack::operator >= (const stack& s) const /// Операция >= (по количеству элементов в стеке)
{
    node *n1 = top, *n2 = s.top;

    while (n1 && n2) 
    {
        n1 = n1->next; 
        n2 = n2->next;
    }

    return ((n1 && !n2) || (!n1 && !n2));
}


bool stack::operator == (const stack& s) const /// Операция == (по количеству элементов в стеке)
{
    node *n1 = top, *n2 = s.top;

    while (n1 && n2) 
    {
        n1 = n1->next; 
        n2 = n2->next;
    }

    return (!(n1 || n2));
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
    top = del->next; // Если в стеке был один элемент, то top станет NULL
    delete del;
    return *this;
}


bool stack::comp (const stack& s) const /// Применение операции == ко всем элементам
{
    node *n1 = top, *n2 = s.top;

    for (; n1 && n2; n1 = n1->next, n2 = n2->next)
        if (n1->element != n2->element)
            return false;

    return (!(n1 || n2));
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


stack& stack::mix () // Перемешивание стека
{
    std::vector<node*> array;
    size_t len = 0;

    /* Складываем адреса узлов в массив */
    for (node *n = top; n; n = n->next, ++len)
        array.push_back(n);

    srand(time(NULL)); // Начальное значение для генерации случайных чисел
    /* Перемешивание адресов узлов */
    for (auto &i: array) 
        std::swap(i, array[rand() % len]);

    /* Перестановка указателей на узлы */
    auto i = array.begin();
    top = *i; 
    for (; i != array.end() - 1; ++i) 
        (*i)->next = *(i + 1);
    (*i)->next = NULL;

    return *this;
}


stack& stack::insert (int e, size_t i) /// Вставка элемента по индексу
{
    if (!i) return this->push(e);

    node *n = top;

    for (size_t j = 0; j < i - 1; ++j) n = n->next; // Доходим до узла, который будет перед вставляемым

    node *n_next = n->next, // Если вставляют в конец стека, то n->next будет NULL
         *new_n = new node;
    n->next = new_n;
    new_n->next = n_next;
    new_n->element = e;

    return *this;
}


stack& stack::insert (int e) /// Вставка элемента в конец
{
    node *new_n = new node; 
    new_n->element = e;

    if (!top) top = new_n;
    else
    {
        node *n = top, *tmp = n;
        while ((tmp = n->next)) n = tmp;
        n->next = new_n;
    }

    return *this;
}


stack& stack::insert_safe (int e, size_t i) /// Безопасная вставка элемента по индексу
{
    if (!i) return this->push(e);
    node *n = top, *new_n = new node, *tmp = n;

    new_n->element = e;

    if (n) for (size_t j = 0; (tmp = n->next) && (j < i - 1); ++j) n = tmp; // Если стек не пустой, то доходим до узла, который будет перед вставляемым
    else 
    {
        top = new_n;
        return *this;
    }
    
    node *n_next = n->next; // Если вставляют в конец стека, то n->next будет NULL
    n->next = new_n;
    new_n->next = n_next;

    return *this;
}


stack& stack::remove (int& e) /// Удаление и получение элемента из конца
{
    if (!top) return *this; 

    node *n = top, *tmp;

    if (top->next) while ((tmp = n->next)->next) n = tmp; // Если в стеке больше одного элемента, то доходим до предпоследнего
    else
    {
        e = top->element;
        delete top;
        top = NULL;
        return *this;
    }
    node *del = n->next;
    n->next = NULL;
    e = del->element;
    delete del;
    return *this;
}


stack& stack::remove (size_t i) /// Удаление элемента по индексу
{
    if (!i) return this->pop();

    node *n = top;

    for (size_t j = 0; j < i - 1; ++j) n = n->next; // Доходим до элемента перед удаляемым

    node *del = n->next;
    n->next = del->next;
    delete del;
    return *this;
}


stack& stack::remove (size_t i, int& e) /// Удаление и получение элемента по индексу
{
    if (!i) return this->pop(e);

    node *n = top;

    for (size_t j = 0; j < i - 1; ++j) n = n->next; // Доходим до элемента перед удаляемым

    node *del = n->next;
    n->next = del->next;
    e = del->element;
    delete del;
    return *this;
}


stack& stack::remove_safe (size_t i) /// Безопасное удаление элемента по индексу
{
    if (!i) return this->pop();
    if (!top) return *this;

    node *n = top, *tmp = n;
    
    /* Если в стеке больше одного элемента, то доходим до того, который перед удаляемым, или до предпоследнего */
    if (top->next) for (size_t j = 0; ((tmp = n->next)->next) && (j < i - 1); ++j) n = tmp;
    else
    {
        delete top;
        top = NULL;
        return *this;
    }

    node *del = n->next;
    n->next = del->next; // Если удаляемый элемент последний, то n->next станет NULL
    delete del;
    return *this;
}


stack& stack::remove_safe (size_t i, int& e) /// Безопасное удаление элемента по индексу c получением элемента
{
    if (!i) return this->pop(e);
    if (!top) return *this; 

    node *n = top, *tmp = n;

    /* Если в стеке больше одного элемента, то доходим до того, который перед удаляемым, или до предпоследнего */
    if (top->next) for (size_t j = 0; ((tmp = n->next)->next) && (j < i - 1); ++j) n = tmp;
    else
    {
        e = top->element;
        delete top;
        top = NULL;
        return *this;
    }

    node *del = n->next;
    n->next = del->next; // Если удаляемый элемент последний, то n->next станет NULL
    e = del->element;
    delete del;
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
