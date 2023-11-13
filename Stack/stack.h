#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <initializer_list>
#include <ostream>
#include <istream>

class stack
{
public:
    stack (): top(NULL) {} // Конструктор по умолчанию

    stack (std::initializer_list<int> list); // Конструктор с инициализаторным списком

    stack (const stack& orig); // Конструктор копирования

    stack (stack&& orig): top(orig.top) {orig.top = NULL;} // Конструктор перемещения

    ~stack () {this->clean();} // Деструктор

    stack& clean (); // Очистка стека

    stack& clean (size_t len); // Удаление первых len узлов (len должно быть не больше длины стека)

    stack& clean_safe (size_t len); // Удаление первых len узлов с проверкой (если lеn больше длины стека, то удалится все узлы)

    stack& rclean (size_t len); // Удаление последних len узлов (если len больше длины стека, то удалятся все узлы)

    stack& operator = (const stack& orig); // Операция присваивания

    stack& operator = (stack&& orig); // Операция присваивания по перемещению

    friend std::ostream& operator << (std::ostream& stream, const stack& s); // Вывод

    friend std::istream& operator >> (std::istream& stream, stack& s); // Ввод
    
    stack& operator += (stack& b); // Добавить к стеку стек b (следующий узел после последнего будет вершина стека b)

    stack operator + (const stack& b) const; // Соединение стеков (у стека a + b вершиной будет вершина a, и последний узел --- послденнйи узел b)
    
    stack operator *= (int m); // Умножение на число (добавить стек к себе m раз; если m < 0, то перевёрнутый стек; если m = 0, то очистить стек)

    stack operator * (int m) const {stack r(*this); return r *= m;} // Операция *

    friend stack operator * (int m, const stack& s) {return s * m;} // Операция * с другой стороны

    stack operator /= (int m) // Операция /= (оставляет от стека первую 1/m часть)
    {if (m < 0) this->reverse(), m = -m; if(!m) return this->clean(); size_t len = this->size(); return this->substack(0, len / m - 1);}

    stack operator / (int m) const {stack r(*this); return r /= m;} // Операция 

    bool operator > (const stack& s) const; // Операция > (по количеству элементов в стеке)

    bool operator < (const stack& s) const {return (s > *this);} // Операция < (по количеству элементов в стеке)

    bool operator >= (const stack& s) const; // Операция >= (по количеству элементов в стеке)
    
    bool operator <= (const stack& s) const {return (s >= *this);} // Операция <= (по количеству элементов в стеке)

    bool operator == (const stack& s) const; // Операция == (по количеству элементов в стеке)

    bool is_empty () const {if (top) return false; return true;} // Проверка на пустоту

    bool is_not_empty () const {if (top) return true; return false;} // !is_empty

    int& get_front () {if (!top) throw -1; return top->element;} // Получение элемента из вершины

    int get_front () const {if (!top) throw 1; return top->element;} // Получение элемента из вершины (const)

    stack& push (int e); // Добавление элемента

    stack& push (std::initializer_list<int> list) {for (auto &i: list) this->push(i); return *this;} // push для нескольких элементов

    stack& pop (); // Удаление элемента

    stack& pop (int& e) {if (top) e = top->element; return this->pop();} // Получение и удаление элемента

    size_t size () const {size_t i = 0; for (node *n = top; n; n = n->next) ++i; return i;} // Количесво элементов в стеке

    bool comp (const stack& s) const; // Применение операции == ко всем элементам

    stack& reverse (); // Переворот стека

    stack& mix (); // Перемешивание узлов в случайном порядке

    /** Методы с индексами. Индекс вершины --- 0 */

    int& operator [] (size_t i) {node *n = top; for (size_t j = 0; j < i; ++j) n = n->next; return n->element;} // Доступ к элементу по индексу

    int operator [] (size_t i) const {node *n = top; for (size_t j = 0; j < i; ++j) n = n->next; return n->element;} // Доступ к элементу по индексу (const)

    int& operator () () {node *n = top, *tmp; while ((tmp = n -> next)) n = tmp; return n->element;} // Получение последнего элемента

    int operator () () const {node *n = top, *tmp; while ((tmp = n -> next)) n = tmp; return n->element;} // Получение последнего элемента (const)

    /* Доступ к элементу по индексу c проверкой (если индекс выходит за конец стека, то вернётся последний элемент) */
    int& operator () (size_t i) {node *n = top, *tmp = top; for (size_t j = 0; (tmp = n -> next) && (j < i); ++j) n = tmp; return n->element;}

    int operator () (size_t i) const {node *n = top, *tmp = top; for (size_t j = 0; (tmp = n -> next) && (j < i); ++j) n = tmp; return n->element;}

    stack& insert (int e, size_t i); // Вставка элемента по индексу (вставляемый элемент будет иметь этот индекс)

    stack& insert (int e); // Вставка элемента в конец

    stack& insert_safe (int e, size_t i); // Вставка элемента по индексу с проверкой (если индекс выходит за конец стека, то элемент вставится в конец)

    stack& remove () {return this->rclean(1);}; // Удаление элемента из конца

    stack& remove (int& e); // Удаление и получение элемента из конца

    stack& remove (size_t i); // Удаление элемента по индексу

    stack& remove (size_t i, int& e); // Удаление элемента по индексу с получением элемента

    stack& remove_safe (size_t i); // Удаление элемента по индексу с проверкой (если индекс выходит за конец стека, то удалится последний элемент)

    stack& remove_safe (size_t i, int& e); // Безопасное удаление элемента по индексу с получением элемента

    stack& substack (size_t beg, size_t end, size_t step = 1); // Выделение подстека (индексы beg и end должны быть внутри стека)

    /* отрицательная индексация с другой стороны (-1 --- индекс последнего элемента стека)
     * отрицательный шаг --- подстек начинает выделятся с конца в обратную сторону
     * если индекс end левее beg, то они меняются местами
     * если beg указывает за начало, то выделение начинается с вершины стека
     * если end указывает за конец стека, то стек выделятся до конца
     * если step = 0, то стек очищается
     */
    stack& substack_safe (long long beg, long long end, long long step = 1); // Выделение подстека с проверками

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
   if (!yes.comp(copy_s.substack_safe(beg, end, step)))                \
   {                                                                   \
        std::cout << copy_s << "   instead of   " << yes << std::endl; \
        exit (-1);                                                     \
   }                                                                   \
} 


#endif // STACK_H_INCLUDED
