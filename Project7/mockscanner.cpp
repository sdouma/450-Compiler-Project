#include "mockscanner.h"

#include <iostream>
#include <assert.h>

#include <list>

class MockScanner : public Scanner
{
public:
  std::list <TokenSP> tokens;
  TokenSP next() {
    if (tokens.empty()) eof();
    TokenSP ans = tokens.front();
    std::cout << "next: " << *ans << std::endl;
    tokens.pop_front();
    return ans;
  }

  void add(int type, const std::wstring &value=L"") {
    tokens.push_back(TokenSP(new Token(type,value,0)));
  }

  void eof() {
    add(Token::END_OF_FILE);
  }

  void eol() {
    add(Token::END_OF_LINE);
  }

  void text(const std::wstring &value) {
    add(Token::TEXT,value);
  }

  void markup(const std::wstring &value) {
    add(Token::MARKUP,value);
  }

  void bold_open(const std::wstring &value) {
    add(Token::BOLD_OPEN_MARK,value);
  }

  void bold_close(const std::wstring &value) {
    add(Token::BOLD_CLOSE_MARK,value);
  }
  
  void italic_open(const std::wstring &value) {
    add(Token::ITALIC_OPEN_MARK,value);
  }

  void italic_close(const std::wstring &value) {
    add(Token::ITALIC_CLOSE_MARK,value);
  }
  
  void underline_open(const std::wstring &value) {
    add(Token::UNDERLINE_OPEN_MARK,value);
  }

  void underline_close(const std::wstring &value) {
    add(Token::UNDERLINE_CLOSE_MARK,value);
  }

  void bold1()
  {
    bold_open(L"[*");
    text(L" shout ");
    bold_close(L"*]");
    eol();
  }

  void bold2()
  {
    text(L"Can you ");
    bold_open(L"[*");
    text(L"hear");
    bold_close(L"*]");
    text(L" me?");
    eol();
  }

  void bold3()
  {
    text(L"This is ");
    bold_open(L"[*");
    text(L"shout");
    underline_open(L"[_");
    text(L"ing");
    underline_close(L"_]");
    bold_close(L"*]");
    text(L"!!");
    eol();
  }

  MockScanner(const std::string &mockFile)
  {
    if (mockFile == "bold1-ms.md") {
      bold1();
    } else if (mockFile == "bold2-ms.md") {
      bold2();
    } else if (mockFile == "bold3-ms.md") {
      bold3();
    } else {
      std::cout << "unmocked source file " << mockFile << std::endl;
      assert(false);
    }
  }
};

ScannerSP CreateMockScanner(const std::string &mockFile)
{
  return ScannerSP(new MockScanner(mockFile));
}
