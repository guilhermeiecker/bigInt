#include <stdint.h>     // uint64_t
#include <string.h>     // memset
#include <math.h>       /* ceil */
#include <stdio.h>      /* printf */
#include <algorithm>
#include <string>

typedef unsigned __int128 uint128_t;

using namespace std;

class BigInt
{
public:
  BigInt();
  BigInt(uint64_t);
  BigInt(uint128_t);
  BigInt(BigInt&);

  void print128(uint128_t);
  
  uint128_t get_msb();
  uint128_t get_lsb();

  void set_msb(uint128_t);
  void set_lsb(uint128_t);

  BigInt& operator=(const uint64_t&);
  BigInt& operator=(const uint128_t&);
  
  BigInt& operator++();
  BigInt operator++(int);
  
  BigInt& operator--();
  BigInt operator--(int);

  BigInt operator~();

  BigInt& operator&=(BigInt&);
  BigInt& operator&=(uint128_t&);
  BigInt& operator&=(uint64_t&);

  BigInt& operator+=(BigInt&);
  BigInt& operator+=(uint128_t&);
  BigInt& operator+=(uint64_t&);

  BigInt& operator>>(const int&);
  BigInt& operator<<(const int&);

  friend std::ostream& operator<<(std::ostream& os, const BigInt& obj)
  {
    int bits[256] = {0};
    uint128_t p, q;
    int idx;

    p = obj.lsb;
    idx = 0;
    do {
      q = p / 2;
      bits[idx] = (p%2);
      p = q;
      idx++;
    } while (q > 0);

    p = obj.msb;
    idx = 128;
    do {
      q = p / 2;
      bits[idx] = (p%2);
      p = q;
      idx++;
    } while (q > 0);

    for(int i = 255; i >=0; i--)
      os << bits[i];

    return os;
  } 

  friend BigInt operator&(BigInt lhs, BigInt& rhs) // otherwise, both parameters may be const references
  {
    lhs &= rhs; // reuse compound assignment
    return lhs; // return the result by value (uses move constructor)
  }

  friend BigInt operator&(BigInt lhs, uint128_t& rhs) // otherwise, both parameters may be const references
  {
    lhs &= rhs; // reuse compound assignment
    return lhs; // return the result by value (uses move constructor)
  }

  friend BigInt operator&(BigInt lhs, uint64_t& rhs) // otherwise, both parameters may be const references
  {
    lhs &= rhs; // reuse compound assignment
    return lhs; // return the result by value (uses move constructor)
  }

  friend bool operator<(const BigInt& l, const BigInt& r)
  {
    if (l.msb < r.msb)
      return true;
    else
    if (l.msb > r.msb)
      return false;
    if (l.lsb < r.lsb)
       return true;
    return false;
  }

  friend bool operator<(const BigInt& l, const uint64_t& r)
  {
    if (l.msb > 0)
      return false;
    if (l.lsb < (uint128_t)r)
      return true;
    return false;
  }

  friend bool operator<(const BigInt& l, const uint128_t& r)
  {  
    if (l.msb > 0)
      return false;
    if (l.lsb < r)
      return true;
    return false;
  }

  friend bool operator==(const BigInt& l, const BigInt& r)
  {
    if(l.msb != r.msb)
      return false;
    if(l.lsb != r.lsb)
      return false;
    return true;
  }

  friend bool operator==(const BigInt& l, const uint64_t& r)
  {
    if(l.msb > 0)
      return false;
    if(l.lsb != (uint128_t)r)
      return false;
    return true;
  }

  friend bool operator==(const BigInt& l, const uint128_t& r)
  {
    if (l.msb > 0)
      return false;
    if (l.lsb != r)
      return false;
    return true;
  }

  friend BigInt operator+(BigInt lhs, BigInt& rhs) // otherwise, both parameters may be const references
  {
    lhs += rhs; // reuse compound assignment
    return lhs; // return the result by value (uses move constructor)
  }

private:  
  uint128_t msb;
  uint128_t lsb;
};

BigInt::BigInt()
{
  msb = 0;
  lsb = 0;
}

BigInt::BigInt(uint64_t _n)
{
  msb = 0;
  lsb = (uint128_t)_n;
}

BigInt::BigInt(uint128_t _n)
{
  msb = 0;
  lsb = _n;
}

BigInt::BigInt( BigInt& _o )
{
  msb = _o.get_msb();
  lsb = _o.get_lsb();
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

uint128_t BigInt::get_msb()
{
  return msb;
}

uint128_t BigInt::get_lsb()
{
  return lsb;
}

void BigInt::set_msb(uint128_t _n)
{
  msb = _n;
}

void BigInt::set_lsb(uint128_t _n)
{
  lsb = _n;
}

BigInt& BigInt::operator=(const uint64_t& _x) // copy assignment
{
    lsb = (uint128_t)_x;
    return *this;
}

BigInt& BigInt::operator=(const uint128_t& _x) // copy assignment
{
    lsb = _x;
    return *this;
}

BigInt& BigInt::operator++()
{
  uint128_t current = lsb;
  lsb++;
  msb = msb + (current > lsb) ? 1 : 0; 
  
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
  uint128_t current = lsb;
  lsb--;
  msb = msb - (current < lsb) ? 1 : 0;

  return *this;
}

BigInt BigInt::operator--(int)
{
  BigInt tmp(*this); // copy
  operator--(); // pre-increment

  return tmp;   // return old value
}

BigInt BigInt::operator~()
{ 
  BigInt aux(*this);
  aux.set_msb(~msb);
  aux.set_lsb(~lsb);

  return aux;
}

BigInt& BigInt::operator&=(BigInt& rhs)
{
  msb = msb & rhs.get_msb();
  lsb = lsb & rhs.get_lsb();

  return *this;
}

BigInt& BigInt::operator&=(uint128_t& rhs)
{
  msb = 0;
  lsb = lsb & rhs;

  return *this;
}

BigInt& BigInt::operator&=(uint64_t& rhs)
{
  msb = 0;
  lsb = lsb & (uint128_t)rhs;
  
  return *this;
}

BigInt& BigInt::operator+=(BigInt& rhs)
{
  uint128_t aux = lsb;
  lsb = lsb + rhs.get_lsb();
  msb = msb + rhs.get_msb() + ((aux >= lsb)? 1 : 0);

  return *this;
}

BigInt& BigInt::operator+=(uint128_t& rhs)
{
  uint128_t aux = lsb;
  lsb = lsb + rhs;
  msb = msb + ((aux >= lsb)? 1 : 0);

  return *this;
}

BigInt& BigInt::operator+=(uint64_t& rhs)
{
  uint128_t aux = lsb;
  lsb = lsb + (uint128_t)rhs;
  msb = msb + ((aux >= lsb)? 1 : 0);
  
  return *this;
}

BigInt& BigInt::operator>>(const int& rhs)
{
  if ((rhs > 255) || (rhs < 0))
  {
    msb = 0;
    lsb = 0;
  }
  else
  {
    uint128_t x = 0;

    x = msb << (128 - rhs);
    msb = msb >> rhs;
    lsb = lsb >> rhs;
    lsb = lsb | x;
  }
 
  return *this; // return the result by reference
}

BigInt& BigInt::operator<<(const int& rhs)
{
  if ((rhs > 255) || (rhs < 0))
  {
    msb = 0;
    lsb = 0;
  }
  else
  {
    uint128_t x = 0;

    x = lsb >> (128 - rhs);
    lsb = lsb << rhs;
    msb = msb << rhs;
    msb = msb | x;
  }
  
  return *this; // return the result by reference
}

uint64_t log2(BigInt n)
{
  uint64_t count = 0;
  while((n & 1) == 0)
  {
    n = n >> 1;
    count++;
  }
  return count;
}

BigInt pow2(uint64_t n)
{
  BigInt res(1);
  res = res << n;
  return res;
}
