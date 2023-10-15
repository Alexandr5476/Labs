#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <ostream>
#include <istream>

class queue
{
public:
    queue (): head(NULL), tail(NULL) {} // ����������� �� ���������

    queue (const queue& orig); // ����������� �����������

    queue (queue&& orig): head(orig.head),  tail(orig.tail) {orig.head = NULL; orig.tail = NULL;} // ����������� �����������

    ~queue () {this->clean();} // ����������

    queue& clean (); // ������� �������

    queue& clean (size_t len); // �������� len ����� �� ������� (len ������ ���� �� ������ ����� �������)

    queue& clean_safe (size_t len); // �������� len ����� �� ������� c ��������� (���� len ������ ����� �������, �� �������� ��� ����)

    queue& rclean (size_t len); // �������� ��������� len ����� (���� len ������ ����� �������, �� �������� ��� ����)

    queue& operator = (queue& orig); // �������� ������������

    queue& operator = (queue&& orig); // �������� ������������ �� �����������

    friend std::ostream& operator << (std::ostream& stream, queue q); // �����

    friend std::istream& operator >> (std::istream& stream, queue q); // ����

    queue& operator += (queue& b); // ���������� ������� b (head ��������� ��� ��, tail ����� ���, ������� � ������� b)

    queue operator + (const queue& b) const; // ���������� �������� (� ������� a + b head ����� ��� � ������� �, tail ��� b)
    
    queue operator *= (int m); // ��������� �� ����� (�������� ������� � ���� m ���; ���� m < 0, �� ����������� �������; ���� m = 0, �� �������� �������)

    queue operator * (int m) const {queue r(*this); return r *= m;} // �������� *

    friend queue operator * (int m, const queue& s) {return s * m;} // �������� * � ������ �������

    queue operator /= (int m) // �������� /= (��������� �� ������� ������ 1/m �����)
    {if (m < 0) this->reverse(), m = -m; if(!m) return this->clean(); size_t len = this->size(); return this->subqueue(0, len / m - 1);}

    queue operator / (int m) const {queue r(*this); return r /= m;} // �������� /

    bool operator > (const queue& b) const; // �������� > (�� ���������� ���������)

    bool operator < (const queue& b) const {return (b > *this);} // �������� < (�� ���������� ���������)
    
    bool operator >= (const queue& b) const; // �������� > (�� ���������� ���������)

    bool operator <= (const queue& b) const {return (b >= *this);} // �������� < (�� ���������� ���������)

    bool operator == (const queue& b) const; /// �������� == �� ���������� ���������

    bool is_empty () {if (head) return false; return true;} // �������� �� �������

    bool is_not_empty () {if (head) return true; return false;} // !is_empty

    int& get_front () {return head->element;} // ��������� �������� �� �������

    int get_front () const {return head->element;} // ��������� �������� �� ������� (const)

    queue& push(int e); // ���������� ��������

    queue& pop(); // �������� ��������

    queue& pop(int& e) {e = head->element; return this->pop();} // �������� � ��������� ��������

    size_t size () const {size_t i = 0; for (node *n = head; n; n = n->next) ++i; return i;} // ���������� ��������� � �������

    bool comp (const queue& q) const; // ���������� �������� == �� ���� ���������

    queue& reverse (); // ��������� �������

    queue& mix(); // ������������� ����� � ��������� �������

     /** ������ � ���������. ������ head --- 0 */

    int& operator [] (size_t i) {node *n = head; for (size_t j = 0; j < i; ++j) n = n->next; return n->element;} // ������ � �������� �� �������

    int operator [] (size_t i) const {node *n = head; for (size_t j = 0; j < i; ++j) n = n->next; return n->element;} // ������ � �������� �� ������� (const)

    int& operator () () {node *n = head, *tmp; while ((tmp = n -> next)) n = tmp; return n->element;} // ��������� ���������� ��������

    int operator () () const {node *n = head, *tmp; while ((tmp = n -> next)) n = tmp; return n->element;} // ��������� ���������� �������� (const)

    /* ������ � �������� �� ������� c ��������� (���� ������ ������� �� ����� �����, �� ������� ��������� �������) */
    int& operator () (size_t i) {node *n = head, *tmp = n; for (size_t j = 0; (tmp = n -> next) && (j < i); ++j) n = tmp; return n->element;}

    int operator () (size_t i) const {node *n = head, *tmp = n; for (size_t j = 0; (tmp = n -> next) && (j < i); ++j) n = tmp; return n->element;}

    queue& insert (int e, size_t i); // ������� �������� �� ������� (����������� ������� ����� ����� ���� ������)

    queue& insert (int e); // ������� �������� � head

    queue& insert_safe (int e, size_t i); // ������� �������� �� ������� � ��������� (���� ������ ������� �� ����� �������, �� ������� ��������� � �����)

    queue& remove () {return this->rclean(1);} // �������� tail

    queue& remove (int& e) {if (tail) e = tail->element; return this->rclean(1);} // �������� � ��������� �������� �� tail

    queue& remove (size_t i); // �������� �������� �� �������

    queue& remove (size_t i, int& e); // �������� �������� �� ������� � ���������� ��������

    queue& remove_safe (size_t i); // �������� �������� �� ������� � ��������� (���� ������ ������� �� ����� �����, �� �������� ��������� �������)

    queue& remove_safe (size_t i, int& e); // ���������� �������� �������� �� ������� � ���������� ��������

    queue& subqueue (size_t beg, size_t end, size_t step = 1); // ��������� ��������

    /* ������������� ���������� � ������ ������� (-1 --- ������ ���������� �������� �������)
     * ������������� ��� --- ���������� �������� ��������� � ����� � �������� �������
     * ���� ������ end ����� beg, �� ��� �������� �������
     * ���� beg ��������� �� ������, �� ��������� ���������� � ������� �������
     * ���� end ��������� �� ����� �������, �� ������� ��������� �� �����
     * ���� step = 0, �� ������� ���������
     */
    queue& subqueue_safe (long long beg, long long end, long long step = 1); // ��������� �������� � ����������

private:
    class node
    {
    public:
        node (): next(NULL) {};
        node *next;
        int element;
    };

    node *head, *tail;
};


/* beg, end, step --- ��������� ������ subqueue_safe
 * x --- �������, ��� �������� ���������� subqueue_safe
 * y --- std::vector � ����������, ������� ������ ���� � ����������
 */
#define TEST(beg, end, step, x, y)                                     \
{                                                                      \
   queue copy_s(x), yes;                                               \
   for (auto& i: y)                                                    \
        yes.push(i);                                                   \
                                                                       \
   if (!yes.comp(copy_s.subqueue_safe(beg, end, step)))                \
   {                                                                   \
        std::cout << copy_s << "   instead of   " << yes               \
        << " (line: " <<__LINE__<<")" << std::endl;                    \
        exit (-1);                                                     \
   }                                                                   \
}

#endif // QUEUE_H_INCLUDED
