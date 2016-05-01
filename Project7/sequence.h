#pragma once

#include "stddef.h"
#include <memory>

class Sequence
{
 public:
  virtual int peek(unsigned delta=0)=0; /* abstract */
  virtual size_t at()=0; /* abstract */
  virtual void shift(unsigned delta=1)=0; /* abstract */
  virtual int get();
  virtual ~Sequence();
};

typedef std::shared_ptr < Sequence > SequenceSP;
