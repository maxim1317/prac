#include "rational.h"

int main(){
    Rational a = Rational(1, 2);
    Rational b = Rational(2, 4);
    if (a == b){
        std::cout << "Equal" << std::endl;
    } else if (a != b){
        std::cout << "Not equal" << std::endl;
    }
    std::cout << a.toString() << " + " << b.toString() << " = " << (a + b).toString() << std::endl;
    std::cout << a.toString() << " - " << b.toString() << " = " << (a - b).toString() << std::endl;
    try
    {Rational div_zero = Rational(1, 0);}
    catch (const char * c){
        std::cout << c << std::endl;
    }
    return 0;
}
