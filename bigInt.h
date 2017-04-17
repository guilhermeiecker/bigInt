#include <stdint.h>     // uint64_t
#include <string.h>     // memset
#include <math.h>       /* ceil */
#include <stdio.h>      /* printf */
#include <algorithm>

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

  BigInt operator~();

  BigInt& operator>>(const uint64_t&);
  BigInt& operator<<(const uint64_t&);

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

  friend bool operator<(const BigInt& l, const BigInt& r)
  {
    uint64_t i;
    if(l.nblocks >= r.nblocks)
    {
      for (i = l.nblocks - 1; i > r.nblocks - 1; i-- )
      {
        if(l.blocks[i] > 0) 
          return false;
      }
      for (i = r.nblocks; i-- > 0; )
      {
        if(l.blocks[i] < r.blocks[i])
          return true;
        if(l.blocks[i] > r.blocks[i])
          return false;
      }
    }else
    {
      for (i = r.nblocks - 1; i > l.nblocks - 1; i-- )
      {
        if(r.blocks[i] > 0)
          return true;
      }
      for (i = l.nblocks; i-- > 0; )
      {
        if(l.blocks[i] < r.blocks[i])
          return true;
        if(l.blocks[i] > r.blocks[i])
          return false;
      }
    }
    return false;
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

BigInt BigInt::operator~()
{
  BigInt aux(size);
  for(uint64_t i = 0; i < nblocks; i++)
    aux.blocks[i] = ~(blocks[i]);

  return aux;
}

BigInt& BigInt::operator>>(const uint64_t& rhs)
{
  uint128_t aux1, aux2;
  aux1 = aux2 = 0;
  
  if (rhs < 128)
  { 
    for (uint64_t i = nblocks; i-- > 0; )
    {
      aux1 = blocks[i] << (128 - rhs);
      blocks[i] = blocks[i] >> rhs;
      blocks[i] = blocks[i] | aux2;
      aux2 = aux1; 
    }
  } else
  {
    printf("error\n");
  }  
  return *this; // return the result by reference
}

BigInt& BigInt::operator<<(const uint64_t& rhs)
{
  uint128_t aux1, aux2;
  aux1 = aux2 = 0;
  
  if (rhs < 128)
  {
    for (uint64_t i = 0; i < nblocks; i++)
    {
      aux1 = blocks[i] >> (128 - rhs);
      blocks[i] = blocks[i] << rhs;
      blocks[i] = blocks[i] | aux2;
      aux2 = aux1;
    }
  } else
  {
    printf("error\n");
  }	
  return *this; // return the result by reference
}



//TODO: < uint64_t

//TODO: < uint128_t

//TODO: < BigInt

//TODO: - uint64_t

//TODO: - uint128_t

//TODO: - BigInt

//TODO: + uint64_t

//TODO: + uint128_t

//TODO: + BigInt
