#include <iostream>
#include "list.h"

int main()
{
    setlocale (LC_CTYPE, "Russian");

try
{
    stack<int> s({12, 4, 7, -9, 2});
    std::cout << s << std::endl;

    queue<int> q({12, 4, 7, -9, 2});
    std::cout << q << std::endl;

    for (stack<int>::iterator i = s.begin(); i != s.end(); ++i)
    {
        std::cout << *i << "_";
    }

    q.clean();
    q.get_front() = 5; 

    q.push(3); // Не будет выполняться
    std::cout << q << std::endl; // Не будет выполняться
}
catch(std::exception const & e)
{
    std::cerr << e.what();
}

    return 0;
}