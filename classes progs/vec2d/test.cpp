#include <iostream>
#include "vec2d.h"

int main(){
    Vec2d a = Vec2d(1, 2);
    Vec2d b = Vec2d(1, 2, 2, 4);
    std::cout << a[0] << std::endl;
    std::cout << a.toString() << std::endl;

    std::cout << b.toString() << std::endl;

    std::cout << (a + b).toString() << std::endl;

    std::cout << a.length() << std::endl;
    std::cout << a << std::endl;

}