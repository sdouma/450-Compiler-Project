#include "markdownscanner.h"
#include <iostream>

#define TRACE 0

class MarkdownScanner : public Scanner
{
public:
  Sequence &sequence;
  MarkdownScanner(Sequence &_sequence) : sequence(_sequence) {}
  bool isopen;
  TokenSP next()
  {
	  std::cout <<"isopen="<< isopen;
    if (sequence.peek() == -1) {
      return TokenSP(new Token(Token::END_OF_FILE,
                               L"",
                               sequence.at()));
    } else if (sequence.peek() == '\n') {
      sequence.shift(1);
      return TokenSP(new Token(Token::END_OF_LINE,
                               L"\n",
                               sequence.at()));
    } else if (sequence.peek() == '\r'
               && sequence.peek(1) == '\n') {
      sequence.shift(2);
      return TokenSP(new Token(Token::END_OF_LINE,
                               L"\r\n",
                               sequence.at()));
    } 
	else if (isopen != true && sequence.peek() == '\'') {
		int nextCode = sequence.peek(1);
		std::cout << "hit \n;";

#if TRACE == 1
		std::cout << "seq peek: " << sequence.peek(1) << "\n";
		std::cin.get();
#endif
		if (nextCode == '\'' && sequence.peek(2) != '\'') {
			sequence.shift(2);
			isopen = true;
			return TokenSP(new Token(Token::BOLD_OPEN_MARK, L"\'\'", sequence.at()));
		}
		else if (nextCode == '\'' && sequence.peek(2) == '\'') {
			sequence.shift(3);
			isopen = true;
			return TokenSP(new Token(Token::ITALIC_OPEN_MARK, L"\'\'\'", sequence.at()));
		}
	}
	else if (sequence.peek() == '<' && sequence.peek(1) == 'u' && sequence.peek(1)=='>') {
          sequence.shift(3);
		  return TokenSP(new Token(Token::UNDERLINE_OPEN_MARK,L"<u>",sequence.at()));
      } 
    
 /*start here if (peek * || _ || /)
  * and next peek == ]
  * ans
  * shift 2
  * return token 
  * */
  
	else if
		(isopen==true && sequence.peek() == '\'' && sequence.peek(1) == '\''){

		sequence.shift(2);
		return TokenSP(new Token(Token::BOLD_CLOSE_MARK, L"\'\'", sequence.at()));
		}
	else if (sequence.peek() == '/' && sequence.peek(1) == ']'){
		sequence.shift(2);
		return TokenSP(new Token(Token::ITALIC_CLOSE_MARK, L"/]", sequence.at()));
		}
	else if (sequence.peek() == '_' && sequence.peek(1) == ']'){
		sequence.shift(2);
		return TokenSP(new Token(Token::UNDERLINE_CLOSE_MARK, L"_]", sequence.at()));
		}		
    else {
      std::wstring ans;
      for (;;) {
        int nextCode = sequence.peek();
        if (nextCode == '\'' && sequence.peek(1) == '\'') break;
        if (nextCode == '_' && sequence.peek(1) == ']') break;
        if (nextCode == '/' && sequence.peek(1) == ']') break;       
        if (nextCode == '[' && sequence.peek(1) == '*') break;
        if (nextCode == '[' && sequence.peek(1) == '_') break;
        if (nextCode == '[' && sequence.peek(1) == '/') break;            
        if (nextCode != -1 && nextCode != '\n' && nextCode != '\r') {
          ans.append(1,(wchar_t)nextCode);
          sequence.shift();
        } else {
          break;
        }
      }
      return TokenSP(new Token(Token::TEXT,
                               ans,
                               sequence.at()));
      
    }
  }
};

ScannerSP CreateMarkdownScanner(Sequence &sequence) {
  return ScannerSP(new MarkdownScanner(sequence));
}
