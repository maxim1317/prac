#include <iostream>
#include <stdexcept>

#include "queueonarray.h"

int main(){
    QueueOnArray a = QueueOnArray(5);
    std::cout << a.toString() << std::endl;
    a.push(7);
    std::cout << a.toString() << std::endl;
    a.push(2);
    std::cout << a.toString() << std::endl;
    a.pop();
    std::cout << a.toString() << std::endl;

    std::cout << sizeof(a) << std::endl;    

    QueueOnArray b = QueueOnArray(5);
    std::cout << "b: " << b.toString() << std::endl;
    for (int i = 0; i < 5; i++){
        b.push(1);
        std::cout << b.toString() << std::endl;
    }
    b.pop();
    std::cout << b.toString() << std::endl;
    b.push(2);
    std::cout << b.toString() << std::endl;
    b.resize(7);
    std::cout << b.toString() << std::endl;
    a = b;

    QueueOnArray c = QueueOnArray(2);
    c.push(1);
    c.push(1);
    try {
        c.resize(1);
        std::cout << c.toString() << std::endl;
        c.push(1);
    } catch(std::bad_array_new_length e){
        std::cerr << e.what() << std::endl;
    } catch (std::invalid_argument e){
        std::cerr << e.what() << std::endl;
    }

    QueueOnArray qwe = QueueOnArray(5);
    qwe.push(1);
    qwe.push(2);
    qwe.push(3);
    qwe.push(4);
    qwe.push(5);
    std::cout << qwe << std::endl;
    return 0;
}