#pragma once

#include <memory>

#include "scanner.h"
#include "nodes.h"

class Parser
{
 public:
  virtual NodeSP parse()=0;
  virtual ~Parser();
};

typedef std::shared_ptr < Parser > ParserSP;

ParserSP CreateMarkdownParser(Scanner &scanner);

