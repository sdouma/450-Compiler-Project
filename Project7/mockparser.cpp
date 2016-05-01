#include "mockparser.h"

#include <iostream>


class MockParser : public Parser
{
public:
  Scanner &scanner;
  MockParser(Scanner &_scanner) : scanner(_scanner) {};
  NodeSP parse()
  {
    for (;;) {
      TokenSP token = scanner.next();
      std::cout << "<br/>" << *token << "@" << token->at << std::endl;
      if (token->type == Token::END_OF_FILE) break;
    }
    return NodeSP(0);
  }
};

ParserSP CreateMockParser(Scanner &scanner) {
  return ParserSP(new MockParser(scanner));
}
