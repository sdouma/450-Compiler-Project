/* 
#include "nodes.h"
#include "postprocessor.h"
#include <iostream>
#include <fstream>
#include <sstream>

NodeSP dom1()
{
  auto root = new StatementsNode();
  auto hello = new ParagraphNode();
  hello->content = L"hello";
  root->children.push_back(NodeSP(hello));
  return NodeSP(root);
}

NodeSP dom2()
{
  auto root = new StatementsNode();
  auto markshout = new MarkupNode();
  auto shout = new ParagraphNode();
  auto test = new ParagraphNode();

  markshout->markup = L"#";
  shout->content = L"Shout Here!";
  test->content = L"This is a test of H1..H6";

  markshout->children.push_back(NodeSP(shout));
  root->children.push_back(NodeSP(markshout));
  root->children.push_back(NodeSP(test));

  return NodeSP(root);
}

NodeSP doms(int id)
{
  switch(id) {
  case 1: return dom1();
  case 2: return dom2();
  }
  return NodeSP();
}

void test(int id)
{
  std::ostringstream filename;
  filename << "test" << id << ".html";
  std::ofstream file(filename.str().c_str());
  NodeSP dom = doms(id);
  CreateHTMLPostProcessor(dom,file)->process();
}

int main(int argc, char *argv[])
{

  
  test(1);
  test(2);

  return 0;
}
*/