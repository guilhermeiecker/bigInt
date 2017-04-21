#include <iostream>
#include "bigInt.h"

using namespace std;

int main(int argc, char** argv)
{
  BigInt x(atol(argv[1]));
  BigInt y(0);

  cout << "x=" << x << endl;
  y = ~x;
  cout << "y=" << y << endl;

  cout << "x=" << x++ << endl;
  cout << "y=" << y-- << endl;

  //cout << "x=" << x++ << endl;
  //cout << "y=" << y-- << endl;

  return 0;
}
