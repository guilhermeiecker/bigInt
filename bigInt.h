#include <stdint.h>     // uint64_t
#include <string.h>     // memset
#include <math.h>       /* ceil */
#include <stdio.h>      /* printf */
#include <algorithm>    // std::swap
#include <vector>
#include <string>

typedef unsigned __int128 uint128_t;

using namespace std;

class BigInt
{
public:
  BigInt();
  BigInt(uint64_t);
  ~BigInt();

  uint128_t* get_blocks();
  uint64_t get_size();
  uint64_t get_nblocks();

  void set_blocks();
  void set_blocks(uint128_t*);
  void set_size(uint64_t);
  void set_nblocks(uint64_t);

  void print128(uint128_t);
  void print();

  BigInt& operator=(BigInt);
  BigInt& operator=(uint64_t);

private:
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

BigInt::~BigInt()
{
  delete[] blocks;
}

uint128_t* BigInt::get_blocks()
{
  return blocks;
}

uint64_t BigInt::get_size()
{
  return size;
}

uint64_t BigInt::get_nblocks()
{
  return nblocks;
}

void BigInt::set_blocks(uint128_t* _blocks)
{
  blocks = _blocks;
}

void BigInt::set_size(uint64_t _size)
{
  size = _size;
}

void BigInt::set_nblocks(uint64_t _nblocks)
{
  nblocks = _nblocks;
}

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

BigInt& BigInt::operator=(BigInt rhs)
{
  if(size != rhs.get_size())
  {
    delete[] blocks;
    nblocks = 0;
    size = 0;
   
    size = rhs.get_size();
    nblocks = rhs.get_nblocks();
    blocks = new uint128_t[nblocks];
  } else
    copy(rhs.get_blocks(), rhs.get_blocks() + nblocks, blocks);
  return *this;
}

BigInt& BigInt::operator=(uint64_t rhs)
{
  memset(blocks, 0, nblocks*sizeof(*blocks));
  blocks[0] = rhs;
  
  return *this;
}

