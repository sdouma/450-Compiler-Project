#include <string>
#include <fstream>
#include "utf8sequence.h"
#include "token.h"
#include "scanner.h"
#include "markdownscanner.h"
/*int main(int argc, const char *argv[])
{
  for (int i=1; i<argc; ++i) {
    std::string filename = argv[i];
    std::cout << "scanning " << filename << std::endl;
    std::ifstream is(filename.c_str());

    UTF8Sequence us(is);

    ScannerSP scanner = CreateMarkdownScanner(us);

    for (;;) {
      TokenSP token = scanner->next();
      std::cout << "<br/>" << *token << "@" << token->at << std::endl;
      if (token->type == Token::END_OF_FILE) break;
    }
  }
  return 0;
}*/
