#pragma once
#include <memory>
#include <iostream>
#include "nodes.h"

class PostProcessor
{
 public:
  std::ostream &out;
  NodeSP dom;
  PostProcessor(NodeSP &_dom, std::ostream &_out);
  virtual void process() = 0;
  virtual ~PostProcessor();
};

typedef std::shared_ptr < PostProcessor > PostProcessorSP;

PostProcessorSP CreateSimplePostProcessor(NodeSP &dom,
                                          std::ostream &out=std::cout);

PostProcessorSP CreateHTMLPostProcessor(NodeSP &dom,
                                          std::ostream &out=std::cout);
