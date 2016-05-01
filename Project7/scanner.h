#pragma once

#include "token.h"

class Scanner
{
 public:
  virtual TokenSP next() = 0;
  virtual  ~Scanner();
};

typedef std::shared_ptr < Scanner > ScannerSP;
