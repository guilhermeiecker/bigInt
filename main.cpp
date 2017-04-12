#include <iostream>
#include "bigInt.h"

using namespace std;

int main()
{
  BigInt n1(1280);
  n1 = 4;
  n1.print();

  BigInt n2 = n1;
  n2.print();

  cout << "uhuuul" << endl;  
  return 0;
}
