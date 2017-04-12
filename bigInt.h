#include <stdint.h>     // uint64_t
#include <string.h>     // memset
#include <math.h>       /* ceil */
#include <stdio.h>      /* printf */

typedef unsigned __int128 uint128_t;

using namespace std;

class BigInt
{
public:
  BigInt();
  BigInt(uint64_t);
  BigInt(const BigInt&);
  //~BigInt();

  void print128(uint128_t);
  void print();

  BigInt& operator=(const uint64_t&);
  //BigInt& operator++();
  //BigInt  operator++(int);
  uint128_t* blocks;
  uint64_t   size;
  uint64_t   nblocks;
};

BigInt::BigInt()
{
  size = 128;
  nblocks = 1;
  blocks = new uint128_t[nblocks];
  memset(blocks, 0, nblocks*sizeof(*blocks));
}

BigInt::BigInt(uint64_t _size)
{
  size = _size;
  nblocks = ceil(((float)size) / 128.0);
  blocks = new uint128_t[nblocks];
  memset(blocks, 0, nblocks*sizeof(*blocks));
}

BigInt::BigInt( const BigInt& other ) :
     blocks( other.blocks ), size( other.size ), nblocks( other.nblocks )
  {}

/*
BigInt::~BigInt()
{
  delete[] blocks;
}
*/
void BigInt::print()
{
  for(uint64_t i = 0; i < nblocks; i++)
  {
    print128(blocks[i]);
    printf(".");
  }
  printf("\n");
}

void BigInt::print128(uint128_t n)
{
  uint128_t p, q;
  int r;

  p = n;
  do {
    q = p / 2;
    r = p % 2;
    printf("%d", r);
    p = q;
  } while (q > 0); 
}

BigInt& BigInt::operator=(const uint64_t& _x) // copy assignment
{
    memset(blocks, 0, nblocks*sizeof(*blocks));
    blocks[0] = _x;

    return *this;
}




/*
BigInt& BigInt::operator++()
{
  uint128_t block;

  for(uint64_t i = 0; i < nblocks; i++)
  {
    block = blocks[i];
    block++;
    if(block < blocks[i])
      blocks[i] = block;
    else
    {
      blocks[i] = block;
      return *this;
    }
  }
  return *this;
}

BigInt BigInt::operator++(int)
{
  BigInt tmp(*this); // copy
  operator++(); // pre-increment
  
  return tmp;   // return old value
}
*/
