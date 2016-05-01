
#include "istreamsequence.h"
#include "stringsequence.h"
#include "utf8sequence.h"

#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>

using namespace std;
/*
void test()
{
  for (int t=0; t<100; ++t) {

    // random letter string
    string s;
    int n = rand() % 100;
    for (int i=0; i<n; ++i) {
      s.push_back('a'+rand()%('z'-'a'+1));
    }

    istringstream isa(s); // std::istream 
    IStreamSequence a(isa);
    StringSequence b(s);
    istringstream isc(s); // std::istream 
    UTF8Sequence c(isc);
    
    for (int i=0; i<1000; ++i) {
      int delta = rand()%4;
      switch(rand() % 3) {
      case 0:
        if (a.at() != b.at()) {
          cout << "(a.at()==" << a.at() << ") != (b.at()==" << b.at() << ")";
          assert(false);
        }
        if (b.at() != c.at()) {
          cout << "(a.at()==" << a.at() << ") != (b.at()==" << b.at() << ")";
          assert(false);
        }
        break;
      case 1:
        if (a.peek(delta) != b.peek(delta)) {
          cout << "(a.peek(" << delta << ")==" << a.peek(delta) << ") != (b.peek(" << delta << ")==" << b.peek(delta) << ")";
          assert(false);
        }
        if (a.peek(delta) != c.peek(delta)) {
          cout << "(a.peek(" << delta << ")==" << a.peek(delta) << ") != (c.peek(" << delta << ")==" << c.peek(delta) << ")";
          assert(false);
        }
        break; 
      case 2:
        a.shift(delta);
        b.shift(delta);
        c.shift(delta);
        break;
      }
    }
  }
}

void testutf8()
{
  std::ifstream raw("hello.txt");
  UTF8Sequence us(raw);

  assert(us.peek(0)=='h');
  assert(us.peek(1)==601);
  assert(us.peek(2)=='l');
  assert(us.peek(3)=='l');
  assert(us.peek(4)=='o');
  assert(us.peek(5)==-1);
}

int main()
{
  test();
  testutf8();
  cout << "ok" << endl;
  return 0;
}

*/
