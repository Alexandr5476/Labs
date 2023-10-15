#include "queue.h"
#include <iostream>
#include <vector>
#include <time.h>

queue::queue (const queue& orig): head(NULL), tail(NULL) /// Конструктор копирования
{
    for (node *n = orig.head; n; n = n->next)
        this->push(n->element);
}


queue& queue::clean () /// Очистка очереди
{
    if (!head) return *this;

    node *n = head, *n_next;

    while ((n_next = n->next))
    {
        delete n;
        n = n_next;
    }
    delete n;

    head = tail = NULL;
    return *this;
}

queue& queue::clean (size_t len) /// Удаление len узлов из очереди (len должно быть не больше длины очереди)
{
    node *n = head, *n_next;

    for (size_t i = 0; i < len; ++i)
    {
        n_next = n->next;
        delete n;
        n = n_next;
    }
    if(!(head = n)) tail = NULL;
    return *this;
}

queue& queue::clean_safe (size_t len) /// Безопасное удаление len узлов из очереди
{
    if (!head) return *this;

    node *n = head, *n_next;

    size_t i = 0;
    for (; (n_next = n->next) && (i < len); ++i)
    {
        delete n;
        n = n_next;
    }
    if (i < len) 
    {
        delete n;
        head = tail = NULL;
        return *this;
    }
    head = n;
    return *this;
}

queue& queue::rclean (size_t len) // Удаление последних len узлов (если len больше длины очереди, то удалятся все узлы)
{
    if (!head) return *this;

    if (len == 1)
    {
        if (!head->next)
        {
            delete head;
            head = tail = NULL;
            return *this;
        }
        node *n = head, *tmp;
        while ((tmp = n->next)->next) n = tmp;
        delete n->next;
        n->next = NULL;
        tail = n;
        return *this;
    }

    size_t size = this->size();
    if (len >= size) return this->clean();
    
    size_t beg = size - len;

    node *n = head;
    for (size_t i = 0; i < beg - 1; ++i) n = n->next; // Проходим до последнего оставляемого элемента

    node *n_next = n->next;
    tail = n;
    n->next = NULL;
    n = n_next;
    while((n_next = n->next))
    {
        delete n;
        n = n_next;
    }
    delete n;
    return *this;
}


queue& queue::operator = (queue& orig) /// Операция присваивания
{
    if (&orig == this) return *this;
    this->clean();

    for (node *n = orig.head; n; n = n->next)
        this->push(n->element);

    return *this;
}

queue& queue::operator = (queue&& orig) //. Операция присваивания по перемещению
{
    this->clean();

    tail = orig.tail;
    head = orig.head;

    orig.tail = orig.head = NULL;
    return *this;
}

std::ostream& operator << (std::ostream& stream, queue q) // Вывод
{
    if (!q.head) stream << "Очередь пустая";
    for (queue::node *n = q.head; n; n = n->next)
        stream << n->element << " ";
    return stream;
}

std::istream& operator >> (std::istream& stream, queue q) /// Ввод
{
    int e;
    stream >> e;
    q.push(e);
    return stream;
}


queue& queue::operator+= (queue& b) // Добавление очереди b (head останется тем же, tail будет тот, который у очереди b)
{
    if (&b == this)
    {
        queue b2(b);
        return (*this += b2);
    }

    if(!tail)
    {
        tail = b.tail;
        head = b.head;
    }
    else tail->next = b.head;
    b.head = b.tail = NULL;
    return *this;
}

queue queue::operator + (const queue& b) const /// Соединение очередей (у очереди a + b head будет как у очереди а, tail как b)
{
    queue q(*this);
    node *n = b.head;
    do {q.push(n->element);} while ((n = n->next));
    return q;
}

bool queue::operator > (const queue& b) const /// Операция > (по количеству элементов)
{
    node *n1 = head, *n2 = b.head;

    while (n1 && n2)
    {
        n1 = n1->next;
        n2 = n2->next;
    }

    return (n1 && !n2);
}

bool queue::operator >= (const queue& b) const /// Операция > (по количеству элементов)
{
    node *n1 = head, *n2 = b.head;

    while (n1 && n2)
    {
        n1 = n1->next;
        n2 = n2->next;
    }

    return ((n1 && !n2) || (!n1 && !n2));
}

bool queue::operator == (const queue& b) const /// Операция == по количеству элементов
{
    node *n1 = head, *n2 = b.head;

    while (n1 && n2)
    {
        n1 = n1->next;
        n2 = n2->next;
    }
    
    return (!(n1 || n2));
}

queue& queue::push(int e) /// Добавление элемента
{
    node *n = new node;

    n->element = e;
    if (!head) head = n;
    else tail->next = n;
    tail = n;
    
    return *this;
}

queue& queue::pop() /// Удаление элемента
{
    if (!head) return *this;

    node *del = head;

    if(!(head = head->next)) tail = NULL;
    delete del;
    return *this;
}

bool queue::comp (const queue& q) const /// Применение операции === ко всем элементам
{
    node *n1 = head, *n2 = q.head;

    for (; n1 && n2; n1 = n1->next, n2 = n2->next)
        if (n1->element != n2->element)
            return false;

    return (!(n1 || n2));
}

queue& queue::reverse () /// Переворот очереди
{
    node *n = head, *n_next = head->next, *n_prev = NULL;

    std::swap(head, tail);
    while(n_next)
    {
        n->next = n_prev;
        n_prev = n;
        n = n_next;
        n_next = n->next;
    }
    n->next = n_prev;
    
    return *this;
}

queue& queue::mix() // Перемешивание узлов в случайном порядке
{
    std::vector<node *> array;
    size_t len = 0;

    /* Складываем адреса узлов в массив */
    for(node *n = head; n; n = n->next, ++len)
        array.push_back(n);

    srand(time(NULL)); // Начально значение для генерации случайных чисел
    /* Перемешивание узлов */
    for (auto &i: array)
        std::swap(i, array[rand() % len]);

    /* Установка всех указателей */
    auto i = array.begin();
    head = *i;
    for (; i != array.end() - 1; ++i)
        (*i)->next = *(i + 1);

    (tail = *i)->next = NULL;
    return *this; 
}

queue& queue::insert (int e, size_t i) /// Вставка элемента по индексу (вставляемый элемент будет иметь этот индекс)
{
    if (!i) return this->push(e);

    node *n = head;

    for (size_t j = 0; j < i - 1; ++j) n = n->next; // Доходим до узла, который будет перед вставляемым

    node *n_next = n->next, *new_n = new node;
    n->next = new_n;
    new_n->element = e;
    if (!(new_n->next = n_next)) tail = new_n;

    return *this;
}

queue& queue::insert (int e) /// Вставка элемента после head
{
    node *new_n = new node;
    new_n->element = e;

    if (!(new_n->next = head)) tail = new_n;
    head = new_n;

    return *this;
}

queue& queue::insert_safe (int e, size_t i) // Безопасная вставка элемента по индексу
{
    if (!i) return this->insert(e);

    node *n = head, *tmp, *new_n = new node;
    new_n->element = e;

    if (n) for (size_t j = 0; (tmp = n->next) && (j < i - 1); ++j) n = tmp; // Доходим до узла, который будет перед вставляемым (если очередь не пустая)
    else
    {
        tail = head = new_n;
        return *this;
    }

    node *n_next = n->next;
    n->next = new_n;
    if (!(new_n->next = n_next)) tail = new_n;

    return *this;
}


queue& queue::remove (size_t i) // Удаление элемента по индексу (i не выходит за конец очереди)
{
    if (!i) return this->pop();

    node *n = head;

    for (size_t j = 0; j < i - 1; ++j) n = n->next; // Доходим до узла, который будет перед удаляемым

    node *del = n->next, *n_next = del->next;
    delete del;
    if (!(n->next = n_next)) tail = n;

    return *this;
}

queue& queue::remove (size_t i, int& e) // Удаление и получение элемента по индексу (i не выходит за конец очереди)
{
    if (!i) return this->pop(e);

    node *n = head;

    for (size_t j = 0; j < i - 1; ++j) n = n->next; // Доходим до узла, который будет перед удаляемым

    node *del = n->next, *n_next = del->next;
    delete del;
    e = del->element;
    if (!(n->next = n_next)) tail = n;

    return *this;
}

queue& queue::remove_safe (size_t i) // Удаление элемента по индексу (i не выходит за конец очереди)
{
    if (!i) return this->pop();
    if (!head) return *this;

    node *n = head, *tmp;

    /* Если в очереди больше одного элемента, то доходим до того, который перед удаляемым, или до предпоследнего */
    if (head->next) for (size_t j = 0; ((tmp = n->next)->next) && (j < i - 1); ++j) n = tmp;
    else
    {
        delete head;
        head = tail = NULL;
        return *this;
    }

    node *del = n->next, *n_next = del->next;
    delete del;
    if (!(n->next = n_next)) tail = n;

    return *this;
}

queue& queue::remove_safe (size_t i, int& e) // Удаление элемента по индексу (i не выходит за конец очереди)
{
    if (!i) return this->pop(e);
    if (!head) return *this;

    node *n = head, *tmp;

    /* Если в очереди больше одного элемента, то доходим до того, который перед удаляемым или до предпоследнего */
    if (head->next) for (size_t j = 0; ((tmp = n->next)->next) && (j < i - 1); ++j) n = tmp;
    else
    {
        e = head->element;
        delete head;
        head = tail = NULL;
        return *this;
    }

    node *del = n->next, *n_next = del->next;
    e = del->element;
    delete del;
    if (!(n->next = n_next)) tail = n;

    return *this;
}


queue& queue::subqueue (size_t beg, size_t end, size_t step) /// Выделение подсочереди
{
    size_t i = 0; // Текущий индекс
    node *n = head, *n_next, *cur; // n --- текущий узел, n_next --- для удаления, cur --- последний оставленный узел

    for (; i < beg; ++i) // Проходим до начала, удаляя всё на пути
    {
        n_next = n->next;
        delete n;
        n = n_next;
    }
    /* теперь n указывает на первый узел, который нужно оставить */

    cur = head = n;

    for(size_t j = i + step; i < end; j += step) // j --- индекс следующего элемента, который надо оставить (если он < end)
    { // считаем, что индекс end не может указывать за пределы очереди

        /* Переходим на следующий узел после оставленного */
        ++i;
        n = n->next;

        for (; (i < j) && (i < end); ++i) // Проходим до следующего узла, который нужно оставить, удаляя всё на пути
        { // считаем, что индекс end не может указывать за пределы очереди
            n_next = n->next;
            delete n;
            n = n_next;
        }

        if (j <= end) cur = cur->next = n; // Если мы ещё не прошли конец, то привязываем узел к последнему оставленному
    }

    tail = cur;

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
    this->reverse(); // !?

    return *this;
}


queue& queue::subqueue_safe (long long beg, long long end, long long step) /// Выделение подстека с проверками
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

    return this->subqueue(beg, end, step);

}
