#include <iostream>
#include <fstream>
#include "matrix2d.h"

int main(){
    Matrix2d a = Matrix2d(3);
    Matrix2d b = a;

    int arr[] = {1,2,3,4,5,6,7,8,9};
    Matrix2d c = Matrix2d(arr, 3, 3);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;

    if (a == b){
        std::cout << "Equal" << std::endl;
    }

    std::cout << "Serialization test:" << std::endl;
    Matrix2d big_matrix = Matrix2d(5000);
    Matrix2d bm1 = big_matrix;

    std::ofstream os("test.txt");
    big_matrix.serialize(os);
    os.close();

    std::ifstream is("test.txt");
    big_matrix.deserialize(is);
    is.close();

    if(bm1 == big_matrix){
        std::cout << "Serialization is gooooood!" << std::endl;
    }

    return 0;
}