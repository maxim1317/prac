#include <iostream>
#include "complex.h"

void test_binary_operations(){
    Complex a = Complex(5, 3);
    Complex b = Complex(7, 1);
    Complex add = a + b;
    Complex sub = a - b;
    Complex mul = a * b;
    Complex div = a / b;
    std::cout << "Addition: " << add.toString() << ". Must be 12 + 4i" << std::endl;
    std::cout << "Subtraction: " << sub.toString() << ". Must be -2 + 2i" << std::endl;
    std::cout << "Multiplication: " << mul.toString() << ". Must be 32 + 26i" << std::endl;
    std::cout << "Division: " << div.toString() << ". Must be 0.76 - 0.32i" << std::endl;

    Complex c = Complex(0.1, 2);
    Complex d = Complex(0.2, 2);
    if (c == d){
        std::cout << "Equal" << std::endl;
    } else if (c != d) {
        std::cout << "Not equal" << std::endl;
    }
}

int main(){
    test_binary_operations();
    Complex a = Complex(1, 2);
    std::cout << a << std::endl;
}