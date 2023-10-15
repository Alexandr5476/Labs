#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <ostream>
#include <istream>

class queue
{
public:
    queue (): head(NULL), tail(NULL) {} // Конструктор по умолчанию

    queue (const queue& orig); // Конструктор копирования

    queue (queue&& orig): head(orig.head),  tail(orig.tail) {orig.head = NULL; orig.tail = NULL;} // Конструктор перемещения

    ~queue () {this->clean();} // Деструктор

    queue& clean (); // Очистка очереди

    queue& clean (size_t len); // Удаление len узлов из очереди (len должно быть не больше длины очереди)

    queue& clean_safe (size_t len); // Удаление len узлов из очереди c проверкой (если len больше длины очереди, то удалятся все узлы)

    queue& rclean (size_t len); // Удаление последних len узлов (если len больше длины очереди, то удалятся все узлы)

    queue& operator = (queue& orig); // Операция присваивания

    queue& operator = (queue&& orig); // Операция присваивания по перемещению

    friend std::ostream& operator << (std::ostream& stream, queue q); // Вывод

    friend std::istream& operator >> (std::istream& stream, queue q); // Ввод

    queue& operator += (queue& b); // Добавление очереди b (head останется тем же, tail будет тот, который у очереди b)

    queue operator + (const queue& b) const; // Соединение очередей (у очереди a + b head будет как у очереди а, tail как b)
    
    queue operator *= (int m); // Умножение на число (добавить очередь к себе m раз; если m < 0, то перевёрнутую очередь; если m = 0, то очистить очередь)

    queue operator * (int m) const {queue r(*this); return r *= m;} // Операция *

    friend queue operator * (int m, const queue& s) {return s * m;} // Операция * с другой стороны

    queue operator /= (int m) // Операция /= (оставляет от очереди первую 1/m часть)
    {if (m < 0) this->reverse(), m = -m; if(!m) return this->clean(); size_t len = this->size(); return this->subqueue(0, len / m - 1);}

    queue operator / (int m) const {queue r(*this); return r /= m;} // Операция /

    bool operator > (const queue& b) const; // Операция > (по количеству элементов)

    bool operator < (const queue& b) const {return (b > *this);} // Операция < (по количеству элементов)
    
    bool operator >= (const queue& b) const; // Операция > (по количеству элементов)

    bool operator <= (const queue& b) const {return (b >= *this);} // Операция < (по количеству элементов)

    bool operator == (const queue& b) const; /// Операция == по количеству элементов

    bool is_empty () {if (head) return false; return true;} // Проверка на пустоту

    bool is_not_empty () {if (head) return true; return false;} // !is_empty

    int& get_front () {return head->element;} // Получение элемента из вершины

    int get_front () const {return head->element;} // Получение элемента из вершины (const)

    queue& push(int e); // Добавление элемента

    queue& pop(); // Удаление элемента

    queue& pop(int& e) {e = head->element; return this->pop();} // Удаление и получение элемента

    size_t size () const {size_t i = 0; for (node *n = head; n; n = n->next) ++i; return i;} // Количество элементов в очереди

    bool comp (const queue& q) const; // Применение операции == ко всем элементам

    queue& reverse (); // Переворот очереди

    queue& mix(); // Перемешивание узлов в случайном порядке

     /** Методы с индексами. Индекс head --- 0 */

    int& operator [] (size_t i) {node *n = head; for (size_t j = 0; j < i; ++j) n = n->next; return n->element;} // Доступ к элементу по индексу

    int operator [] (size_t i) const {node *n = head; for (size_t j = 0; j < i; ++j) n = n->next; return n->element;} // Доступ к элементу по индексу (const)

    int& operator () () {node *n = head, *tmp; while ((tmp = n -> next)) n = tmp; return n->element;} // Получение последнего элемента

    int operator () () const {node *n = head, *tmp; while ((tmp = n -> next)) n = tmp; return n->element;} // Получение последнего элемента (const)

    /* Доступ к элементу по индексу c проверкой (если индекс выходит за конец стека, то вернётся последний элемент) */
    int& operator () (size_t i) {node *n = head, *tmp = n; for (size_t j = 0; (tmp = n -> next) && (j < i); ++j) n = tmp; return n->element;}

    int operator () (size_t i) const {node *n = head, *tmp = n; for (size_t j = 0; (tmp = n -> next) && (j < i); ++j) n = tmp; return n->element;}

    queue& insert (int e, size_t i); // Вставка элемента по индексу (вставляемый элемент будет иметь этот индекс)

    queue& insert (int e); // Вставка элемента в head

    queue& insert_safe (int e, size_t i); // Вставка элемента по индексу с проверкой (если индекс выходит за конец очереди, то элемент вставится в конец)

    queue& remove () {return this->rclean(1);} // Удаление tail

    queue& remove (int& e) {if (tail) e = tail->element; return this->rclean(1);} // Удаление и получение элемента из tail

    queue& remove (size_t i); // Удаление элемента по индексу

    queue& remove (size_t i, int& e); // Удаление элемента по индексу с получением элемента

    queue& remove_safe (size_t i); // Удаление элемента по индексу с проверкой (если индекс выходит за конец стека, то удалится последний элемент)

    queue& remove_safe (size_t i, int& e); // Безопасное удаление элемента по индексу с получением элемента

    queue& subqueue (size_t beg, size_t end, size_t step = 1); // Выделение подстека

    /* отрицательная индексация с другой стороны (-1 --- индекс последнего элемента очереди)
     * отрицательный шаг --- подочередь начинает выделятся с конца в обратную сторону
     * если индекс end левее beg, то они меняются местами
     * если beg указывает за начало, то выделение начинается с вершины очереди
     * если end указывает за конец очереди, то очередь выделятся до конца
     * если step = 0, то очередь очищается
     */
    queue& subqueue_safe (long long beg, long long end, long long step = 1); // Выделение подстека с проверками

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


/* beg, end, step --- аргументы метода subqueue_safe
 * x --- очередь, для которого вызывается subqueue_safe
 * y --- std::vector с элементами, которые должны быть в подочереди
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
