#include <iostream>

#include "vector.h"

int main(){
    Vector qwe;
    Vector asd(2);
    int q[] = {1,2,3,4,5};
    Vector a = Vector(q, 5);
    Vector b(a);

    if (a == b){
        std::cout << "Equal" << std::endl;
    }

    std::cout << "a: " << a.toString() << std::endl;
    a[1] = 1;
    std::cout << "a: " << a.toString() << std::endl;
    a.append(7);
    std::cout << "a: " << a.toString() << std::endl;
    a.remove(2);
    std::cout << "a: " << a.toString() << std::endl;
}