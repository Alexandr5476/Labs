#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <ostream>
#include <istream>

class stack
{
public:
    stack (): top(NULL) {} // ����������� �� ���������

    stack (const stack& orig); // ����������� �����������

    stack (stack&& orig): top(orig.top) {orig.top = NULL;} // ����������� �����������

    ~stack () {this->clean();} // ����������

    stack& clean (); // ������� �����

    stack& clean (size_t len); // �������� ������ len ����� (len ������ ���� �� ������ ����� �����)

    stack& clean_safe (size_t len); // �������� ������ len ����� � ��������� (���� l�n ������ ����� �����, �� �������� ��� ����)

    stack& rclean (size_t len); // �������� ��������� len ����� (���� len ������ ����� �����, �� �������� ��� ����)

    stack& operator = (const stack& orig); // �������� ������������

    stack& operator = (stack&& orig); // �������� ������������ �� �����������

    friend std::ostream& operator << (std::ostream& stream, const stack& s); // �����

    friend std::istream& operator >> (std::istream& stream, stack& s); // ����
    
    stack& operator += (stack& b); // �������� � ����� ���� b (��������� ���� ����� ���������� ����� ������� ����� b)

    stack operator + (const stack& b) const; // ���������� ������ (� ����� a + b �������� ����� ������� a, � ��������� ���� --- ���������� ���� b)

    bool operator > (const stack& s) const; // �������� > (�� ���������� ��������� � �����)

    bool operator < (const stack& s) const {return (s > *this);} // �������� < (�� ���������� ��������� � �����)

    bool operator >= (const stack& s) const; // �������� >= (�� ���������� ��������� � �����)
    
    bool operator <= (const stack& s) const {return (s >= *this);} // �������� <= (�� ���������� ��������� � �����)

    bool operator == (const stack& s) const; // �������� == (�� ���������� ��������� � �����)

    bool is_empty () {if (top) return false; return true;} // �������� �� �������

    int& get_front () const {return top->element;} // ��������� �������� �� �������

    stack& push (int e); // ���������� ��������

    stack& pop (); // �������� ��������

    stack& pop (int& e) {e = this->get_front(); return this->pop();} // ��������� � �������� ��������

    size_t size () const {size_t i = 0; for (node *n = top; n; n = n->next) ++i; return i;} // ��������� ��������� � �����

    bool comp (const stack& s) const; // ���������� �������� == �� ���� ���������

    stack& reverse (); // ��������� �����

    stack& mix (); // ������������� ����� � ��������� �������

    /** ������ � ���������. ������ ������� --- 0 */

    int& operator [] (size_t i) const {node *n = top; for (size_t j = 0; j < i; ++j) n = n->next; return n->element;} // ������ � �������� �� �������
    
    /* ������ � �������� �� ������� c ��������� (���� ������ ������� �� ����� �����, �� ������� ��������� �������) */
    int& operator () (size_t i) const {node *n = top, *tmp = top; for (size_t j = 0; (tmp = n -> next) && (j < i); ++j) n = tmp; return n->element;}

    stack& insert (int e, size_t); // ������� �������� �� ������� (����������� ������� ����� ����� ���� ������)

    stack& insert_safe (int e, size_t i); // ������� �������� �� ������� � ��������� (���� ������ ������� �� ����� �����, �� ������� ��������� � �����)

    stack& remove (size_t i); // �������� �������� �� �������

    stack& remove (size_t i, int& e) {e = top->element; return this->remove(i);} // �������� �������� �� ������� � ���������� ��������

    stack& remove_safe (size_t i); // �������� �������� �� ������� � ��������� (���� ������ ������� �� ����� �����, �� �������� ��������� �������)

    stack& remove_safe (size_t i, int& e) {e = top->element; return this->remove_safe(i);} // ���������� �������� �������� �� ������� � ���������� ��������

    stack& substack (size_t beg, size_t end, size_t step = 1); // ��������� �������� (������� beg � end ������ ���� ������ �����)

    /* ������������� ���������� � ������ ������� (-1 --- ������ ���������� �������� �����)
     * ������������� ��� --- ������� �������� ��������� � ����� � �������� �������
     * ���� ������ end ����� beg, �� ��� �������� �������
     * ���� beg ��������� �� ������, �� ��������� ���������� � ������� �����
     * ���� end ��������� �� ����� �����, �� ���� ��������� �� �����
     * ���� step = 0, �� ���� ���������
     */
    stack& substack_safe (long long beg, long long end, long long step = 1); // ��������� �������� � ����������

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
   if (!yes.comp(copy_s.substack_safe(beg, end, step)))                \
   {                                                                   \
        std::cout << copy_s << "   instead of   " << yes << std::endl; \
        exit (-1);                                                     \
   }                                                                   \
} 


#endif // STACK_H_INCLUDED
