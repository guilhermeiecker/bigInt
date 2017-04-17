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
  
  void print128(uint128_t);
  void print();

  BigInt& operator=(const uint64_t&);
  BigInt& operator=(const uint128_t&);

  BigInt& operator++();
  BigInt  operator++(int);

  BigInt& operator--();
  BigInt  operator--(int);

  BigInt& operator&=(const BigInt&);
  BigInt& operator&=(const uint128_t&);
  BigInt& operator&=(const uint64_t&);

  BigInt operator~(const BigInt);

  friend BigInt operator&(BigInt lhs, const BigInt& rhs) // otherwise, both parameters may be const references
  {
    lhs &= rhs; // reuse compound assignment
    return lhs; // return the result by value (uses move constructor)
  }

  friend BigInt operator&(BigInt lhs, const uint128_t& rhs) // otherwise, both parameters may be const references
  {
    lhs &= rhs; // reuse compound assignment
    return lhs; // return the result by value (uses move constructor)
  }

  friend BigInt operator&(BigInt lhs, const uint64_t& rhs) // otherwise, both parameters may be const references
  {
    lhs &= rhs; // reuse compound assignment
    return lhs; // return the result by value (uses move constructor)
  }

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

BigInt::BigInt( const BigInt& other )
{
  size = other.size;
  nblocks = other.nblocks;
  blocks = new uint128_t[nblocks];
  copy(other.blocks, other.blocks + nblocks, blocks);
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

BigInt& BigInt::operator=(const uint64_t& _x) // copy assignment
{
    memset(blocks, 0, nblocks*sizeof(*blocks));
    blocks[0] = _x;

    return *this;
}

BigInt& BigInt::operator=(const uint128_t& _x) // copy assignment
{
    memset(blocks, 0, nblocks*sizeof(*blocks));
    blocks[0] = _x;

    return *this;
}

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

BigInt& BigInt::operator--()
{
  uint128_t block;

  for(uint64_t i = 0; i < nblocks; i++)
  {
    block = blocks[i];
    block--;
    if(block > blocks[i])
      blocks[i] = block;
    else
    {
      blocks[i] = block;
      return *this;
    }
  }
  return *this;
}

BigInt BigInt::operator--(int)
{
  BigInt tmp(*this); // copy
  operator--(); // pre-increment

  return tmp;   // return old value
}

BigInt& BigInt::operator&=(const BigInt& rhs)
{
  for(uint64_t i = 0; i < nblocks; i++)
    blocks[i] = blocks[i] & rhs.blocks[i];
  return *this; 
}

BigInt& BigInt::operator&=(const uint128_t& rhs)
{
  blocks[0] = blocks[0] & rhs;
  memset(blocks + 1, 0, (nblocks - 1)*sizeof(*blocks));

  return *this; 
}

BigInt& BigInt::operator&=(const uint64_t& rhs)
{
  blocks[0] = blocks[0] & (uint128_t)rhs;
  memset(blocks + 1, 0, (nblocks - 1)*sizeof(*blocks));

  return *this;
}

BigInt BigInt::operator~(const BigInt )
{
  
}

//TODO: ~ BigInt

//TODO: >> uint64_t

//TODO: << uint64_t

//TODO: / uint64_t

//TODO: / uint128_t

//TODO: / BigInt

//TODO: < uint64_t

//TODO: < uint128_t

//TODO: < BigInt

//TODO: - uint64_t

//TODO: - uint128_t

//TODO: - BigInt

//TODO: + uint64_t

//TODO: + uint128_t

//TODO: + BigInt
