#pragma once

#include <stddef.h>
#include <string>
#include <memory>

class Token
{
 public:

  enum { MARKUP, BOLD_OPEN_MARK, MARK_CLOSE,ITALIC_OPEN_MARK, UNDERLINE_OPEN_MARK,
		BOLD_CLOSE_MARK,ITALIC_CLOSE_MARK, UNDERLINE_CLOSE_MARK,
		TEXT, STRIKE_THROUGH_OPEN_MARK, STRIKE_THROUGH_CLOSE_MARK, END_OF_LINE, END_OF_FILE = -1
  };
  int type; 
  std::wstring value;
  size_t at;
  bool isopen;
  void print(std::ostream &out) const;
  Token(int type_,
        const std::wstring &value_, size_t at_=0);
};

bool operator==(const Token &a, const Token &b);

typedef std::shared_ptr < Token > TokenSP;

std::ostream& operator<<(std::ostream &out,
                         const Token &token);
