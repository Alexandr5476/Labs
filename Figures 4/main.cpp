#include <iostream>
#include "figures.h"

int main()
{
    setlocale (LC_CTYPE, "Russian");

    circle c(3);
    std::cout << std::endl << c << "; периметр = " << c.perimeter() << "; площадь = " << c.area() << std::endl;
    c.set_radius(5.167);
    std::cout << c << "; периметр = " << c.perimeter() << "; площадь = " << c.area() << std::endl << std::endl;

    square s(7);
    std::cout << s << "; периметр = " << s.perimeter() << "; площадь = " << s.area() << std::endl;
    s.set_side(9.673);
    std::cout << s << "; периметр = " << s.perimeter() << "; площадь = " << s.area() << std::endl << std::endl;

    rectangle r(4, 8);
    std::cout << r << "; периметр = " << r.perimeter() << "; площадь = " << r.area() << std::endl;
    r.set_width(12.5); r.set_height (7.23);
    std::cout << r << "; периметр = " << r.perimeter() << "; площадь = " << r.area() << std::endl << std::endl;

    ellipse e(4, 4);
    std::cout << e << "; периметр = " << e.perimeter() << "; площадь = " << e.area() << std::endl;
    e.set_a(2); e.set_b (5);
    std::cout << e << "; периметр = " << e.perimeter() << "; площадь = " << e.area() << std::endl << std::endl;

    square s2(3), s3(2);
    std::cout << s2 << "; периметр = " << s2.perimeter() << "; площадь = " << s2.area() << std::endl;
    std::cout << s3 << "; периметр = " << s3.perimeter() << "; площадь = " << s3.area() << std::endl;

    figures &f1 = s2;
    s3 = f1;
    std::cout << s3 << "; периметр = " << s3.perimeter() << "; площадь = " << s3.area() << std::endl;

    figures &f2 = s3;
    f2 = s;
    std::cout << s3 << "; периметр = " << s3.perimeter() << "; площадь = " << s3.area() << std::endl;

    return 0;
}