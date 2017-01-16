#include <iostream>
#include <cmath>

using namespace std;

int nod(int A, int B) {
  // checkers
  int a = abs(A);
  int b = abs(B);
  if (a == 0 && b == 0){
    return 0;
  } else if ( a == 0) {
    return b;
  } else if (b == 0 ){
    return a;
  }

  // algorithm
  int t;
  while (b != 0) {
    t = b;
    b = a % b;
    a = t;
  }
  return a;
}

void test_nod(int a, int b, int expectation) {
  cout << "Nod of " << a << " and " << b << " : " << nod(a, b) << ". Expectation was " << expectation << endl;
  nod(a, b) == expectation ? cout << "True" : cout << "False";
  cout << endl;
}

int main(){
  test_nod(10, 15, 5);
  test_nod(10, 0, 10);
  test_nod(0, 10, 10);
  test_nod(10, -100, 10);
  test_nod(-10, 100, 10);
  test_nod(-15, 0, 15);
  return 0;
}
