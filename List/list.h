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

    virtual ~list() {} // Деструктор

    virtual list& push (T e) = 0; // Добавление элемента

    virtual list& pop () = 0; // Удаление элемента

    virtual T& get_front() = 0; // Получение элемента
    
    virtual const T& get_front() const = 0; // Получение элемента (const)

    virtual bool is_empty() const = 0; // Проверка на пустоту

    virtual size_t size() const = 0; // Размер списка

    class iterator
    {
    public:
        typedef typename list<T>::node node;
        iterator (node *p = NULL): cur(p) {} // Конструктор
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
        const_iterator (node *p = NULL): cur(p) {} // Конструктор
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
    friend std::ostream& operator << (std::ostream& stream, const list<M>& l) //{for (typename list<M>::const_iterator i = l.cbegin(); i != l.cend(); ++i) stream << *i << " "; return stream;} // Вывод
    {for (const auto &i: l) stream << i << " "; return stream;} // Вывод
    template<class M>
    friend std::istream& operator >> (std::istream& stream, list<M>& l) {M e; stream >> e; l.push(e); return stream;} // Ввод

protected:

    class node
    {
    public:
        node (): next(NULL) {}; // Конструктор по умолчанию
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

    stack (): top(NULL) {} // Конструктор по умолчанию

    stack (std::initializer_list<T> list); // Конструктор с инициализаторным списком

    stack (const stack& orig); // Конструктор копирования

    stack (stack&& orig): top(orig.top) {orig.top = NULL;} // Конструктор перемещения

   stack& operator = (stack&& orig); // Операция присваивания по перемещению

    ~stack () {this->clean();} // Деструктор

    stack& push (T e) override; // Добавление элемента

    stack& pop () override; // Удаление элемента

    T& get_front () override {if (!top) throw std::runtime_error("Ошибка: получение элемента из пустого стека"); return top->element;} // Получение элемента из вершины

    const T& get_front () const override {if (!top) throw std::runtime_error("Ошибка: получение элемента из пустого стека"); return top->element;} // Получение элемента из вершины (const)

    bool is_empty () const override {if (top) return false; return true;} // Проверка на пустоту

    size_t size () const override{size_t i = 0; for (node *n = top; n; n = n->next) ++i; return i;} // Количесво элементов в стеке

    stack& operator = (const stack& orig); // Операция присваивания

    stack& clean (); // Очистка стека

private:
    typedef typename list<T>::node node;
    node *top; // Указатель на вершину
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

    queue (): head(NULL), tail(NULL) {} // Конструктор по умолчанию

    queue (std::initializer_list<T> list): head(NULL), tail(NULL) {for (auto &i: list) this->push(i);} // Конструктор с инициализаторным списком

    queue (const queue& orig); // Конструктор копирования

    queue (queue&& orig): head(orig.head), tail(orig.tail) {orig.head = NULL; orig.tail = NULL;} // Конструктор перемещения

   queue& operator = (queue&& orig); // Операция присваивания по перемещению

    ~queue () {this->clean();} // Деструктор

    queue& push (T e) override; // Добавление элемента

    queue& pop () override; // Удаление элемента

    T& get_front () override {if (!head) throw std::runtime_error("Ошибка: получение элемента из пустой очереди"); return head->element;} // Получение элемента из вершины

    const T& get_front () const override {if (!head) throw std::runtime_error("Ошибка: получение элемента из пустой очереди"); return head->element;} // Получение элемента из вершины (const)

    bool is_empty () const override {if (head) return false; return true;} // Проверка на пустоту

    size_t size () const override{size_t i = 0; for (node *n = head; n; n = n->next) ++i; return i;} // Количесво элементов очереди

    queue& operator = (const queue& orig); // Операция присваивания

    queue& clean (); // Очистка очереди

private:
    typedef typename list<T>::node node;
    node *head, *tail; // Указатель на вершину
};

template<class T>
queue<T>::queue (const queue<T>& orig): head(NULL), tail(NULL) /// Конструктор копирования
{
    for (node *n = orig.head; n; n = n->next)
        this->push(n->element);
}

template<class T>
queue<T>& queue<T>::operator = (queue<T>&& orig) /// Операция присваивания по перемещению
{
    this->clean();

    tail = orig.tail;
    head = orig.head;

    orig.tail = orig.head = NULL;
    return *this;
}

template<class T>
queue<T>& queue<T>::push(T e) /// Добавление элемента
{
    node *n = new node;

    n->element = e;
    if (!head) head = n;
    else tail->next = n;
    tail = n;
    
    return *this;
}

template<class T>
queue<T>& queue<T>::pop() /// Удаление элемента
{
    if (!head) return *this;

    node *del = head;

    if(!(head = head->next)) tail = NULL;
    delete del;
    return *this;
}

template<class T>
queue<T>& queue<T>::operator = (const queue<T>& orig) /// Операция присваивания
{
    if (&orig == this) return *this;
    this->clean();

    for (node *n = orig.head; n; n = n->next)
        this->push(n->element);

    return *this;
}

template<class T>
queue<T>& queue<T>::clean () /// Очистка очереди
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

/* _______________________________________________________________Стек________________________________________________________________________________*/

template<class T>
stack<T>::stack (const stack<T>& orig): top(NULL) /// Конструктор копирования
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

template<class T>
stack<T>::stack (std::initializer_list<T> list): top(NULL) /// Конструктор с инициализаторным списком
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
stack<T>& stack<T>::operator = (stack<T>&& orig) /// Операция присваивания по перемещению
{
    this->clean(); // Удаление всех узлов

    top = orig.top;
    orig.top = NULL;

    return *this;
}

template<class T>
stack<T>& stack<T>::operator = (const stack<T>& orig) /// Операция присваивания
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

    return *this;
}

template<class T>
stack<T>& stack<T>::push (T e) /// Добавление элемента
{
    node *n = new node;
    n->element = e;
    n->next = top; // Если стек был пустым, то n->next останется NULL
    top = n;
    return *this;
}

template<class T>
stack<T>& stack<T>::pop() /// Удаление элемента
{
    if (!top) return *this; // Если стек пустой

    node *del = top;
    top = del->next; // Если в стеке был один элемент, то top станет NULL
    delete del;
    return *this;
}

template<class T>
stack<T>& stack<T>::clean () /// Очистка стека
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
