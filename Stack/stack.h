#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <ostream>
#include <istream>
#include <iostream>

class stack
{
public:
    stack (): top(NULL) {} // ����������� �� ��������� ?

    stack (const stack& orig); // ����������� �����������

    stack (stack&& orig): top(orig.top) {orig.top = NULL;} // ����������� �����������

    ~stack () {this->clean();} // ���������� ?

    stack& operator = (const stack& orig); // �������� ������������

    stack& operator = (stack&& orig); // �������� ������������ �� �����������

    bool is_empty () {if (top) return false; return true;} // �������� �� �������

    int get_front () const {return top->element;} // ��������� �������� �� �������

    stack& push (int e); // ���������� ��������

    stack& pop (); // �������� ��������

    stack& pop (int& e) {e = this->get_front(); return this->pop();} // ��������� � �������� ��������

    friend std::ostream& operator << (std::ostream& stream, const stack& s); // �����

    friend std::istream& operator >> (std::istream& stream, stack& s); // ����

    stack& clean (); // ������� �����

    size_t size () const {size_t i = 0; for (node *n = top; n; n = n->next) ++i; return i;} // ��������� ��������� � �����

    stack& reverse (); // ��������� �����

    /* stack& add (const stack& added); // ���������� ���� ������ */

    /* ������ ������� --- 0 */
    stack& insert (int e, size_t i = 0); // ������� �������� �� ������� (����������� ������� ����� ����� ���� ������)

    /* ������� �������� �� ������� � ��������� (���� ������ ������� �� ����� �����, �� ������� ��������� � �����) */
    stack& insert_safe (int e, size_t i = 0) {size_t len = this->size(); if (i >= len) i = len - 1; return this->insert(e, i);}

    stack& remove (size_t i = 0); // �������� �������� �� �������

    stack& substack (size_t beg, size_t end, size_t step = 1); // ��������� �������� (������� beg � end ������ ���� ������ �����)

    /* ������������� ���������� � ������ ������� (-1 --- ������ ���������� �������� �����)
     * ������������� ��� --- ������� �������� ��������� � ����� � �������� �������
     * ���� ������ end ����� beg, �� ��� �������� �������
     * ���� beg ��������� �� ������, �� ��������� ���������� � ������� �����
     * ���� end ��������� �� ����� �����, �� ���� ��������� �� �����
     * ���� step = 0, �� ���� ���������
     */
    stack& substack_safe (long long beg, long long end, long long step = 1); // ��������� �������� � ����������

    bool operator == (const stack& s) const; // ��������� (���������� �������� == �� ���� ���������)

private:
    class node // ����
    {
    public:
        node (): next(NULL) {} // ����������� �� ���������
        node *next; // ��������� �� �������� �������
        int element; // ������ ����
    };
    node *top; // ��������� �� �������
};


stack::stack (const stack& orig): top(new (node)) /// ����������� �����������
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


stack& stack::operator = (const stack& orig) /// �������� ������������
{
    if (&orig == this) return *this; // �������� ����������������

    //std::cout << std::endl << *this << std::endl;

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
    if (&orig == this) return *this; // �������� ����������������

    this->clean(); // �������� ���� �����

    top = orig.top;
    orig.top = NULL;

    return *this;
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
    top = del->next; // ���� � ����� ���
    delete del;
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
    std::cin >> e;
    s.push(e);
    return stream;
}


stack& stack::clean () /// ������� �����
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


bool stack::operator == (const stack& s) const /// ��������� (���������� �������� == �� ���� ���������)
{
    node *n1 = top, *n2 = s.top;

    for (; n1 && n2; n1 = n1->next, n2 = n2->next)
        if (n1->element != n2->element)
            return false;

    if (n1 || n2)
        return false;

    return true;
}


/* beg, end, step --- ��������� ������ substack_safe
 * x --- ����, ��� �������� ���������� substack_safe
 * y --- std::vector � ����������, ������� ������ ���� � ��������
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
