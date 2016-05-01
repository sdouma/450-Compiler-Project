#pragma once

#include <list>

template <typename T, typename Sequence>
class Buffered
{
 private:
  Sequence &sequence;
  size_t offset;
  std::list < T > ahead;

 public: Buffered(Sequence &_sequence)
    : sequence(_sequence), offset(0)
    {
      // empty
    }

 public: T next()
  {
    T ans = peek();
    shift();
    return ans;
  }

 public: T peek(unsigned delta=0)
  {
    while (ahead.size() <= delta) {
      ahead.push_back(sequence.next());
      ++offset;
    }
    typename std::list < T > :: iterator  i = ahead.begin();
    while (delta > 0) { ++i; --delta; }
    return *i;
  }

 public: size_t at()
  {
    return offset-ahead.size();
  }

 public: void shift(unsigned delta = 1)
  {
    while (ahead.size() < delta) {
      ahead.push_back(sequence.next());
      ++offset;
    }
    while (delta > 0) {
      ahead.pop_front();
      --delta;
    }
  }
};
