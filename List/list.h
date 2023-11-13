#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <ostream>
#include <istream>
#include <iostream>
#include <exception>

template<class T>
class list
{
public:

    virtual ~list() {} // ����������

    virtual list& push (T e) = 0; // ���������� ��������

    virtual list& pop () = 0; // �������� ��������

    virtual T& get_front() = 0; // ��������� ��������
    
    virtual const T& get_front() const = 0; // ��������� �������� (const)

    virtual bool is_empty() const = 0; // �������� �� �������

    virtual size_t size() const = 0; // ������ ������

    class iterator
    {
    public:
        typedef typename list<T>::node node;
        iterator (node *p = NULL): cur(p) {} // �����������
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        iterator operator ++ () {return cur = cur->next;}
        iterator operator ++ (int) {node *p = cur; cur = cur->next; return p;}
        reference operator * () const {return cur->element;}
        pointer operator -> () const {return &(cur->element);}

        bool operator == (const iterator& i) const {return cur == i.cur;}
        bool operator == (const list<T>::const_iterator& i) const {return cur == i.cur;}

    private:
        node *cur;
    };

    class const_iterator
    {
    public:
        typedef typename list<T>::node node;
        const_iterator (node *p = NULL): cur(p) {} // �����������
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator operator ++ () {return cur = cur->next;}
        const_iterator operator ++ (int) {node *p = cur; cur = cur->next; return p;}
        reference operator * () const {return cur->element;}
        pointer operator -> () const {return &(cur->element);}

        bool operator == (const const_iterator& i) const {return cur == i.cur;}
        bool operator == (const iterator& i) const {return cur == i.cur;}

        const_iterator operator = (const iterator i) {return cur = i.cur;}


    private:
        node *cur;
    };

    virtual iterator begin () = 0;
    virtual iterator end () = 0;
    virtual const_iterator begin () const {return cbegin();};
    virtual const_iterator end () const {return cend();};
    virtual const_iterator cbegin () const = 0;
    virtual const_iterator cend () const = 0;

    template<class M>
    friend std::ostream& operator << (std::ostream& stream, const list<M>& l) //{for (typename list<M>::const_iterator i = l.cbegin(); i != l.cend(); ++i) stream << *i << " "; return stream;} // �����
    {for (const auto &i: l) stream << i << " "; return stream;} // �����
    template<class M>
    friend std::istream& operator >> (std::istream& stream, list<M>& l) {M e; stream >> e; l.push(e); return stream;} // ����

protected:

    class node
    {
    public:
        node (): next(NULL) {}; // ����������� �� ���������
        node *next;
        T element;
    };
};

/*template <class T>
inline bool list<T>::iterator::operator == (const const_iterator& i) const {return cur == i.cur;}
*/

template<class T>
class stack : public list<T>
{
public:
    typedef typename list<T>::iterator iterator;
    typedef typename list<T>::const_iterator const_iterator;
    iterator begin () override {return iterator(top);}
    iterator end () override {return iterator();}
    const_iterator cbegin () const override {return const_iterator(top);}
    const_iterator cend () const override {return const_iterator();}

    stack (): top(NULL) {} // ����������� �� ���������

    stack (std::initializer_list<T> list); // ����������� � ���������������� �������

    stack (const stack& orig); // ����������� �����������

    stack (stack&& orig): top(orig.top) {orig.top = NULL;} // ����������� �����������

   stack& operator = (stack&& orig); // �������� ������������ �� �����������

    ~stack () {this->clean();} // ����������

    stack& push (T e) override; // ���������� ��������

    stack& pop () override; // �������� ��������

    T& get_front () override {if (!top) throw std::runtime_error("������: ��������� �������� �� ������� �����"); return top->element;} // ��������� �������� �� �������

    const T& get_front () const override {if (!top) throw std::runtime_error("������: ��������� �������� �� ������� �����"); return top->element;} // ��������� �������� �� ������� (const)

    bool is_empty () const override {if (top) return false; return true;} // �������� �� �������

    size_t size () const override{size_t i = 0; for (node *n = top; n; n = n->next) ++i; return i;} // ��������� ��������� � �����

    stack& operator = (const stack& orig); // �������� ������������

    stack& clean (); // ������� �����

private:
    typedef typename list<T>::node node;
    node *top; // ��������� �� �������
};


template<class T>
class queue : public list<T>
{
public:
    typedef typename list<T>::iterator iterator;
    typedef typename list<T>::const_iterator const_iterator;
    iterator begin () override {return iterator(head);}
    iterator end () override {return iterator();}
    const_iterator cbegin () const override {return const_iterator(head);}
    const_iterator cend () const override {return const_iterator();}

    queue (): head(NULL), tail(NULL) {} // ����������� �� ���������

    queue (std::initializer_list<T> list): head(NULL), tail(NULL) {for (auto &i: list) this->push(i);} // ����������� � ���������������� �������

    queue (const queue& orig); // ����������� �����������

    queue (queue&& orig): head(orig.head), tail(orig.tail) {orig.head = NULL; orig.tail = NULL;} // ����������� �����������

   queue& operator = (queue&& orig); // �������� ������������ �� �����������

    ~queue () {this->clean();} // ����������

    queue& push (T e) override; // ���������� ��������

    queue& pop () override; // �������� ��������

    T& get_front () override {if (!head) throw std::runtime_error("������: ��������� �������� �� ������ �������"); return head->element;} // ��������� �������� �� �������

    const T& get_front () const override {if (!head) throw std::runtime_error("������: ��������� �������� �� ������ �������"); return head->element;} // ��������� �������� �� ������� (const)

    bool is_empty () const override {if (head) return false; return true;} // �������� �� �������

    size_t size () const override{size_t i = 0; for (node *n = head; n; n = n->next) ++i; return i;} // ��������� ��������� �������

    queue& operator = (const queue& orig); // �������� ������������

    queue& clean (); // ������� �������

private:
    typedef typename list<T>::node node;
    node *head, *tail; // ��������� �� �������
};

template<class T>
queue<T>::queue (const queue<T>& orig): head(NULL), tail(NULL) /// ����������� �����������
{
    for (node *n = orig.head; n; n = n->next)
        this->push(n->element);
}

template<class T>
queue<T>& queue<T>::operator = (queue<T>&& orig) /// �������� ������������ �� �����������
{
    this->clean();

    tail = orig.tail;
    head = orig.head;

    orig.tail = orig.head = NULL;
    return *this;
}

template<class T>
queue<T>& queue<T>::push(T e) /// ���������� ��������
{
    node *n = new node;

    n->element = e;
    if (!head) head = n;
    else tail->next = n;
    tail = n;
    
    return *this;
}

template<class T>
queue<T>& queue<T>::pop() /// �������� ��������
{
    if (!head) return *this;

    node *del = head;

    if(!(head = head->next)) tail = NULL;
    delete del;
    return *this;
}

template<class T>
queue<T>& queue<T>::operator = (const queue<T>& orig) /// �������� ������������
{
    if (&orig == this) return *this;
    this->clean();

    for (node *n = orig.head; n; n = n->next)
        this->push(n->element);

    return *this;
}

template<class T>
queue<T>& queue<T>::clean () /// ������� �������
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

/* _______________________________________________________________����________________________________________________________________________________*/

template<class T>
stack<T>::stack (const stack<T>& orig): top(NULL) /// ����������� �����������
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

template<class T>
stack<T>::stack (std::initializer_list<T> list): top(NULL) /// ����������� � ���������������� �������
{
    node **in = &top;
     for (auto &i: list)
     {
         *in = new node;
         (*in)->element = i;
         in = &((*in)->next);   
     }
}

template<class T>
stack<T>& stack<T>::operator = (stack<T>&& orig) /// �������� ������������ �� �����������
{
    this->clean(); // �������� ���� �����

    top = orig.top;
    orig.top = NULL;

    return *this;
}

template<class T>
stack<T>& stack<T>::operator = (const stack<T>& orig) /// �������� ������������
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

    return *this;
}

template<class T>
stack<T>& stack<T>::push (T e) /// ���������� ��������
{
    node *n = new node;
    n->element = e;
    n->next = top; // ���� ���� ��� ������, �� n->next ��������� NULL
    top = n;
    return *this;
}

template<class T>
stack<T>& stack<T>::pop() /// �������� ��������
{
    if (!top) return *this; // ���� ���� ������

    node *del = top;
    top = del->next; // ���� � ����� ��� ���� �������, �� top ������ NULL
    delete del;
    return *this;
}

template<class T>
stack<T>& stack<T>::clean () /// ������� �����
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

#endif // LIST_H_INCLUDED
