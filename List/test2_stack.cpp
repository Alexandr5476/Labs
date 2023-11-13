#include <iostream>
#include <algorithm>

#include "list.h"

using namespace std;

template <class T> class numerate
{
public:
    numerate(T start = 0, T _shift = 1): seed(start), shift(_shift) {};
    T operator () () {T old = seed; seed += shift; return old; }
private:
    T seed, shift;    
};

template <class T, class C> T sum (const C& c)
{
    T res = 0;
    for (typename C::const_iterator i = c.begin(); i != c.end(); ++i)
       res += *i;
    return res;
}

int main()
{
    stack<int> s1, s2;
    numerate f(100);

    s1.push(1);
    s1.push(2);
    s1.push(3);
    
    s2.push(5);
    s2 = s1;
    s2.push(4);
    
    cout << s1 << endl;          // 3->2->1
    cout << s1.size() << endl;
    
    cout << s2 << endl;          // 4->3->2->1
    cout << s2.size() << endl;
    
    swap(s1, s2);
    
    cout << s1 << endl;          // 4->3->2->1
    cout << s1.size() << endl;
    
    cout << s2 << endl;          // 3->2->1
    cout << s2.size() << endl;
    
    generate(s1.begin(), s1.end(), f);

    cout << s1 << endl;          // 100->101->102->103
    cout << s1.size() << endl;
    
    cout << sum<int,list<int>>(s2) << endl;     // 6

    return 0;
}
