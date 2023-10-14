#include "stack.h"
#include <vector>
#include <time.h>

stack::stack (const stack& orig): top(NULL) /// ����������� �����������
{
    node **in_copy = &top; // ��������� �� ���������, ���� ����� ������� ����� ����

    for (node *n = orig.top; n; n = n->next)
    {
        *in_copy = new node; // ��������� ������ ��� ����� ����
        (*in_copy)->element = n->element; // ����������� ������
        in_copy = &((*in_copy)->next); // ������������ ������ ��������� �� ��������� ����
    }
    /* ��������� ��������� �� ��������� ���� ����� NULL, ������ ��� ����������� ��� ����� ���� ��������� � new node */
}


stack& stack::clean () /// ������� �����
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


stack& stack::clean (size_t len) /// �������� ������ len �����
{
    if (!top) return *this;

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


stack& stack::clean_safe (size_t len) /// ���������� �������� ������ len �����
{
    if (!top) return *this;

    node *n = top, *n_next;
    for (size_t i = 0; i < len; ++i)
    {
        if (!(n_next = n->next)) i = len;
        delete n;
        n = n_next;
    }

    top = n; // n ����� NULL, ���� ����� ���� ����
    return *this;
}


stack& stack::rclean (size_t len) /// �������� ��������� len �����
{
    if (!top) return *this;

    if (len == 1) // �������� ������� ��������� �������, ����� �� ��������� ���� ������ ���
    {
        if (!top->next->next)
        {
            delete top->next;
            top = NULL;
            return *this;
        }
        node *n = top, *tmp;
        while ((tmp = n->next)->next) n = tmp;
        node *del = n->next;
        n->next = NULL;
        delete del;
        return *this; 
    }

    size_t size = this->size();
    if (len > size) return this->clean();

    size_t beg = size - len;
    
    node *n = top;
    for (size_t i = 0; i < beg - 1; ++i) n = n->next;

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


stack& stack::operator = (const stack& orig) /// �������� ������������
{
    if (&orig == this) return *this; // �������� ����������������

    this->clean(); // �������� ���� �����

    node **in_copy = &top; // ��������� �� ���������, ���� ����� ������� ����� ����

    for (node *n = orig.top; n; n = n->next)
    {
        *in_copy = new node; // ��������� ������ ��� ����� ����
        (*in_copy)->element = n->element; // ����������� ������
        in_copy = &((*in_copy)->next); // ������������ ������ ��������� �� ��������� ����
    }
    /* ��������� ��������� �� ��������� ���� ����� NULL, ������ ��� ����������� ��� ����� ���� ��������� � new node */

    return *this;
}


stack& stack::operator = (stack&& orig) /// �������� ������������ �� �����������
{
    this->clean(); // �������� ���� �����

    top = orig.top;
    orig.top = NULL;

    return *this;
}


std::ostream& operator << (std::ostream& stream, const stack& s) /// �����
{
    if (!(s.top))
    {
        stream << "���� ������";
        return stream;
    }

    for (stack::node *n = (s.top); n; n = n->next)
    {
        stream << n->element << " ";
    }
    return stream;
}


std::istream& operator >> (std::istream& stream, stack& s) /// ����
{
    int e;
    stream >> e;
    s.push(e);
    return stream;
}


stack& stack::operator += (stack& b) /// ���������� ������ ����� � �������
{
    node *n = top, *tmp;
    while ((tmp = n->next)) n = tmp;
    n->next = b.top;
    b.top = NULL;
    return *this;
}


stack stack::operator + (const stack& b) const /// ���������� ���� ������
{
    stack new_stack;
    node **in_new = &new_stack.top; // ��������� �� ���������, ���� ����� ������� ����� ����

    for (node *n = top; n; n = n->next) // ����������� �� ������� �����
    {
        *in_new = new node; // ��������� ������ ��� ����� ����
        (*in_new)->element = n->element; // ����������� ������
        in_new = &((*in_new)->next); // ������������ ������ ��������� �� ��������� ����
    }

    for (node *n = b.top; n; n = n->next) // ����������� �� ������� �����
    {
        *in_new = new node; // ��������� ������ ��� ����� ����
        (*in_new)->element = n->element; // ����������� ������
        in_new = &((*in_new)->next); // ������������ ������ ��������� �� ��������� ����
    }
    /* ��������� ��������� �� ��������� ���� ����� NULL, ������ ��� ����������� ��� ����� ���� ��������� � new node */

    return new_stack;
}


bool stack::operator > (const stack& s) const /// �������� > (�� ���������� ��������� � �����)
{
    node *n1 = top, *n2 = s.top;

    while (n1 && n2) 
    {
        n1 = n1->next; 
        n2 = n2->next;
    }

    if (n1 && !n2)
        return true;

    return false;
}


bool stack::operator >= (const stack& s) const /// �������� >= (�� ���������� ��������� � �����)
{
    node *n1 = top, *n2 = s.top;

    while (n1 && n2) 
    {
        n1 = n1->next; 
        n2 = n2->next;
    }

    if ((n1 && !n2) || (!n1 && !n2))
        return true;

    return false;
}


bool stack::operator == (const stack& s) const /// �������� == (�� ���������� ��������� � �����)
{
    node *n1 = top, *n2 = s.top;

    while (n1 && n2) 
    {
        n1 = n1->next; 
        n2 = n2->next;
    }

    if (n1 || n2)
        return false;

    return true;
}


stack& stack::push (int e) /// ���������� ��������
{
    node *n = new node;
    n->element = e;
    n->next = top; // ���� ���� ��� ������, �� n->next ��������� NULL
    top = n;
    return *this;
}


stack& stack::pop() /// �������� ��������
{
    if (!top) return *this; // ���� ���� ������

    node *del = top;
    top = del->next; // ���� � ����� ��� ���� �������, �� top ������ NULL
    delete del;
    return *this;
}


bool stack::comp (const stack& s) const /// ���������� �������� == �� ���� ���������
{
    node *n1 = top, *n2 = s.top;

    for (; n1 && n2; n1 = n1->next, n2 = n2->next)
        if (n1->element != n2->element)
            return false;

    if (n1 || n2)
        return false;

    return true;
}


stack& stack::reverse () /// ��������� �����
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


stack& stack::mix () // ������������� �����
{
    std::vector<node*> array;
    size_t len = 0;

    /* ���������� ������ ����� � ������ */
    for (node *n = top; n; n = n->next, ++len)
        array.push_back(n);

    srand(time(NULL)); // ��������� �������� ��� ��������� ��������� �����
    /* ������������� ������� ����� */
    for (auto &i: array) 
        std::swap(i, array[rand() % len]);

    /* ������������ ���������� �� ���� */
    auto i = array.begin();
    top = *i; 
    for (; i != array.end() - 1; ++i) 
        (*i)->next = *(i + 1);
    (*i)->next = NULL;

    return *this;
}


stack& stack::insert (int e, size_t i) /// ������� �������� �� �������
{
    node *n = top, *new_n = new node;

    new_n->element = e;

    for (size_t j = 0; j < i - 1; ++j) n = n->next;

    node *n_next = n->next; // ���� ��������� � ����� �����, �� n->next ����� NULL
    n->next = new_n;
    new_n->next = n_next;

    return *this;
}


stack& stack::insert_safe (int e, size_t i) /// ���������� ������� �������� �� �������
{
    node *n = top, *new_n = new node, *tmp = n;

    new_n->element = e;

    for (size_t j = 0; (tmp = n->next) && (j < i - 1); ++j) n = tmp;

    node *n_next = n->next; // ���� ��������� � ����� �����, �� n->next ����� NULL
    n->next = new_n;
    new_n->next = n_next;

    return *this;
}


stack& stack::remove (size_t i) /// �������� �������� �� �������
{
    if (!top) return *this; // ���� ���� ������

    node *n = top;

    for (size_t j = 0; j < i - 1; ++j) n = n->next;

    node *del = n->next;
    n->next = del->next;
    delete del;
    return *this;
}


stack& stack::remove_safe (size_t i) /// ���������� �������� �������� �� �������
{
    if (!top) return *this; // ���� ���� ������

    node *n = top, *tmp = n;

    for (size_t j = 0; ((tmp = n->next)->next) && (j < i - 1); ++j) n = tmp;

    node *del = n->next;
    if (del) n->next = del->next;
    else n->next = NULL;
    delete del;
    return *this;
}


stack& stack::substack (size_t beg, size_t end, size_t step) /// ��������� ��������
{
    size_t i = 0; // ������� ������
    node *n = top, *n_next, *cur; // n --- ������� ����, n_next --- ��� ��������, cur --- ��������� ����������� ����

    for (; i < beg; ++i) // �������� �� ������, ������ �� �� ����
    {
        n_next = n->next;
        delete n;
        n = n_next;
    }
    /* ������ n ��������� �� ������ ����, ������� ����� �������� */

    cur = top = n;

    for(size_t j = i + step; i < end; j += step) // j --- ������ ���������� ��������, ������� ���� �������� (���� �� < end)
    { // �������, ��� ������ end �� ����� ��������� �� ������� �����

        /* ��������� �� ��������� ���� ����� ������������ */
        ++i;
        n = n->next;

        for (; (i < j) && (i < end); ++i) // �������� �� ���������� ����, ������� ����� ��������, ������ �� �� ����
        { // �������, ��� ������ end �� ����� ��������� �� ������� �����
            n_next = n->next;
            delete n;
            n = n_next;
        }

        if (j <= end) cur = cur->next = n; // ���� �� ��� �� ������ �����, �� ����������� ���� � ���������� ������������
    }

    /* ������� ��� ���������� �������� */
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


stack& stack::substack_safe (long long beg, long long end, long long step) /// ��������� �������� � ����������
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