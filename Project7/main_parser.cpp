#include <string>
#include <fstream>
#include "utf8sequence.h"
#include "token.h"
#include "markdownscanner.h"
#include "markdownparser.h"
/*
int main(int argc, const char *argv[])
{
	int paragraphs_count = 0;
  for (int i=1; i<argc; ++i) {
    std::string filename = argv[i];
    std::cout << "scanning " << filename << std::endl;
    std::ifstream is(filename.c_str());

    UTF8Sequence us(is);

    ScannerSP scanner = CreateMarkdownScanner(us);
    ParserSP parser = CreateMarkdownParser(*scanner);
    NodeSP dom = parser->parse();
	std::cout<<"in main parser "<<std::endl;
	std::cin.get();
    if (!!dom) {
      dom->print(std::cout);
    } else {
      std::cout << "syntax error." << std::endl;
    }
  }
  return 0;
  */