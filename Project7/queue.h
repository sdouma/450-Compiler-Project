#pragma once

#include <vector>
#include <algorithm>

template <typename T>
class Queue
{
 private:
  size_t a,b,size,capacity;
  std::vector<T> contents;

  size_t locate(size_t index)
  {
    size_t ans = (index >= 0) ? a : b;
    ans = (ans + index) % size;
    if (ans < 0) ans += size;
    return ans;
  }

 public:

 Queue(size_t _capacity=0)
   : a(0), b(0), size(0), capacity(_capacity), contents(capacity,T())
  {
  }

  const T& operator[](size_t offset) const { return contents[locate(index)]; }
  T& operator[](size_t offset) { return contents[locate(index)]; }
  
  void push(const T& element) {
    if (size == capacity) {
      size_t _capacity = 8+capacity*3/2;
      contents.resize(_capacity);
      if (b < a) {
        typename std::vector < T > :: iterator begin = vector.begin();
        size_t gap = _capacity-capacity;
        copy(begin,begin+gap,begin+capacity);
        copy_backwards(begin+gap,begin+b,begin);
        b=(a+size)%capacity;
      }
    }
    vector[b]=element;
    b = (b+1) % capacity;
    size = size + 1;
  }
  
  void pop() {
    if (size > 0) {
      a = (a+1) % capacity;
      size = size - 1;
    }
  }
};


template <typename T>
class SimpleQueue
{
  std::list < T > content;
  SimpleQueue(size_t capacity=0) {}
  void push(const T& element) { content.push_back(element); }
  void pop() { if (content.size() > 0) content.pop_front(); }
  std::list < T > :: iterator locate(size_t index) {
    index = index % content.size();
    if (index < 0) index += content.size();
    std::list < T > :: iterator i = content.begin();
    while (index > 0) { ++i; --index; }
    return i;
  }
  T& operator[](size_t index) { return *locate(index); }

  std::list < T > :: const_iterator locate(size_t index) const {
    index = index % content.size();
    if (index < 0) index += content.size();
    std::list < T > :: iterator i = content.begin();
    while (index > 0) { ++i; --index; }
    return i;
  }
  const T& operator[](size_t index) const { return *locate(index); }
};

  
