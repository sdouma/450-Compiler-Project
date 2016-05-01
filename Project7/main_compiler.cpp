#include <string>
#include <fstream>
#include "utf8sequence.h"
#include "token.h"
#include "scanner.h"
#include "mockscanner.h"
#include "markdownscanner.h"
#include "parser.h"
#include "mockparser.h"
#include "markdownparser.h"
#include "postprocessor.h"

// main program for markdown compiler

int main(int argc, const char *argv[])
{
  bool mockScan = false;
  bool mockParse = false;

  for (int i=1; i<argc; ++i) {
    std::string mdfilename=argv[i];
    if (mdfilename == "--mockScan") {
      mockScan = true;
      continue;
    }
    if (mdfilename == "--mockParse") {
      mockParse = true;
      continue;
    }
    std::shared_ptr < std::ifstream > is;
    SequenceSP sequence;

    if (mdfilename.substr(mdfilename.size()-3) != ".md") {
      std::cout << "invalid markdown input file " << mdfilename << std::endl;
      continue;
    }
    
    std::cout << "scanning " << mdfilename << std::endl;

    ScannerSP scanner;
    if (!mockScan) {
      is = std::shared_ptr < std::ifstream >
        (new std::ifstream(mdfilename.c_str()));
      sequence = SequenceSP(new UTF8Sequence(*is));
      scanner = CreateMarkdownScanner(*sequence);
    } else {
      scanner = CreateMockScanner(mdfilename);
    }

    ParserSP parser;
    if (!mockParse) {
      parser = CreateMarkdownParser(*scanner);
    } else {
      parser = CreateMockParser(*scanner);
    }

    NodeSP dom = parser->parse();
    if (!!dom) {
      std::string htmlfilename=
        mdfilename.substr(0,mdfilename.length()-3)+".html";
      
      std::ofstream os(htmlfilename.c_str());
      CreateHTMLPostProcessor(dom,os)->process();
    } else {
      std::cout << "syntax error." << std::endl;
    }
  }
  return 0;
}
