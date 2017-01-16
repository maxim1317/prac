#include <iostream>

#include "stackonlist.h"

int main(){
    Node<int> n1 = Node<int>(5);
    Node<int> n2 = Node<int>(6);
    StackOnlist<int> sol;
    StackOnlist<int> sol2 = sol;

    sol.push(n1);
    std::cout << sol << std::endl;
    sol.push(n2);
    std::cout << sol << std::endl;
    sol.push(n2);
    std::cout << sol << std::endl;
    sol.pop();
    std::cout << sol << std::endl;

    std::cout << "n1.prev" << std::endl;
    std::cout << n1.prev << std::endl;

    std::cout << "n2.prev" << std::endl;
    std::cout << n2.prev << std::endl;

    std::cout << "n1" << std::endl;
    std::cout << &n1 << std::endl;
    std::cout << "n2" << std::endl;
    std::cout << &n2 << std::endl;
    return 0;
}