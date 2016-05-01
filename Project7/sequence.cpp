#include "sequence.h"

int Sequence::get()
{
  int ans = peek();
  shift();
  return ans;
}

Sequence::~Sequence() 
{
  // empty
}
