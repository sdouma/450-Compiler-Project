#pragma once

#include "sequence.h"

#include <iostream>
#include <list>

class UTF8Sequence : public Sequence
{
 private:
  std::istream &is;
  std::list<int> ahead;
  size_t offset;
  int next();
 public:
  UTF8Sequence(std::istream &is_);
  virtual int peek(unsigned delta=0);
  virtual size_t at();
  virtual void shift(unsigned delta=1);
};
