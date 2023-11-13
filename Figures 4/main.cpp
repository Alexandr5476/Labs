#include <iostream>
#include "figures.h"

int main()
{
    setlocale (LC_CTYPE, "Russian");

    circle c(3);
    std::cout << std::endl << c << "; �������� = " << c.perimeter() << "; ������� = " << c.area() << std::endl;
    c.set_radius(5.167);
    std::cout << c << "; �������� = " << c.perimeter() << "; ������� = " << c.area() << std::endl << std::endl;

    square s(7);
    std::cout << s << "; �������� = " << s.perimeter() << "; ������� = " << s.area() << std::endl;
    s.set_side(9.673);
    std::cout << s << "; �������� = " << s.perimeter() << "; ������� = " << s.area() << std::endl << std::endl;

    rectangle r(4, 8);
    std::cout << r << "; �������� = " << r.perimeter() << "; ������� = " << r.area() << std::endl;
    r.set_width(12.5); r.set_height (7.23);
    std::cout << r << "; �������� = " << r.perimeter() << "; ������� = " << r.area() << std::endl << std::endl;

    ellipse e(4, 4);
    std::cout << e << "; �������� = " << e.perimeter() << "; ������� = " << e.area() << std::endl;
    e.set_a(2); e.set_b (5);
    std::cout << e << "; �������� = " << e.perimeter() << "; ������� = " << e.area() << std::endl << std::endl;

    square s2(3), s3(2);
    std::cout << s2 << "; �������� = " << s2.perimeter() << "; ������� = " << s2.area() << std::endl;
    std::cout << s3 << "; �������� = " << s3.perimeter() << "; ������� = " << s3.area() << std::endl;

    figures &f1 = s2;
    s3 = f1;
    std::cout << s3 << "; �������� = " << s3.perimeter() << "; ������� = " << s3.area() << std::endl;

    figures &f2 = s3;
    f2 = s;
    std::cout << s3 << "; �������� = " << s3.perimeter() << "; ������� = " << s3.area() << std::endl;

    return 0;
}