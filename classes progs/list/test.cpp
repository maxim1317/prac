#include <iostream>

#include "list.h"

int main(){
    List list = 5;//List<int>(5);

    std::cout << "list to string" << std::endl;
    std::cout << list.toString() << std::endl;

    std::cout << "list adresses" << std::endl;
    list.adresses();

    Node a = Node(1);
    std::cout << "a adress" << std::endl;
    std::cout << &a << std::endl;
    std::cout << "a value" << std::endl;
    std::cout << a.toString() << std::endl;
    list.addNode(2, &a);
    std::cout << "list adresses" << std::endl;
    list.adresses();
    std::cout << "list to string" << std::endl;
    std::cout << list.toString() << std::endl;
    std::cout << "list adresses" << std::endl;
    list.adresses();

    return 0;
}