//TODO: which functions are inline
//TODO: operator ~ may be mistakenly implemented
//TODO: Default constructor is nos working properly when no arguments are passed
#include <iostream>

#ifndef _BIGINT_H
#define _BIGINT_H

typedef unsigned __int128 uint128_t;

using namespace std;

class BigInt
{
private:
  uint128_t msb, lsb;

public:
  //BigInt();
  BigInt(int _lsb = 0); //Default constructor with default argument
  BigInt(const BigInt&);      //Copy constructor
  BigInt(uint128_t _msb, uint128_t _lsb);
  ~BigInt();            //Destructor

  uint128_t get_msb() const;
  uint128_t get_lsb() const;

  void set_msb(uint128_t);
  void set_lsb(uint128_t);

  void operator=(const BigInt&);

  BigInt operator~();     // Logical not operator
  BigInt operator++();    // Prefix increment operator
  BigInt operator++(int); // Postfix increment operator
  BigInt operator--();    // Prefix decrement operator
  BigInt operator--(int); // Postfix decrement operator

  //TODO: static int log2(BigInt);
  //TODO: static BigInt pow2(int);

  friend std::ostream& operator<<(std::ostream& os, const BigInt& obj) {
    int bits[256] = {0};
    uint128_t p, q;
    int idx;

    p = obj.get_lsb();
    idx = 0;
    do {
      q = p / 2;
      bits[idx] = (p%2);
      p = q;
      idx++;
    } while (q > 0);

    p = obj.get_msb();
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
};

/*
BigInt::BigInt(){
  set_msb(0);
  set_lsb(0);
}
*/

BigInt::BigInt(int _lsb) {
  set_msb(0);
  set_lsb((uint128_t)_lsb);
}

BigInt::BigInt(const BigInt& _x) {
  set_msb(_x.get_msb());
  set_lsb(_x.get_lsb());
}

BigInt::BigInt(uint128_t _msb, uint128_t _lsb) : msb(_msb), lsb(_lsb) {}

BigInt::~BigInt() {}

uint128_t BigInt::get_msb() const {
  return msb;
}

uint128_t BigInt::get_lsb() const {
  return lsb;
}

void BigInt::set_msb(uint128_t _msb) {
  msb = _msb;
}

void BigInt::set_lsb(uint128_t _lsb) {
  lsb = _lsb;
}

void BigInt::operator=(const BigInt& obj) {
  set_msb(obj.get_msb());
  set_lsb(obj.get_lsb());
}

BigInt BigInt::operator~() {
  msb = ~msb;
  lsb = ~lsb;
  return *this;
}

BigInt BigInt::operator++() {
  uint128_t current = lsb;
  lsb++;
  msb = msb + (current > lsb) ? 1 : 0;
  return *this;
}

BigInt BigInt::operator++(int) {
  operator++();
  return *this;
}

BigInt BigInt::operator--(){
  uint128_t current = lsb;
  lsb--;
  msb = msb - (current < lsb) ? 1 : 0;
  return *this;
}

BigInt BigInt::operator--(int) {
  operator--();
  return *this;
}

#endif
