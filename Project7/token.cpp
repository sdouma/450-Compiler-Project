#include "token.h"
#include <iostream>

Token::Token(int type_, const std::wstring &value_, size_t at_)
  : type(type_), value(value_), at(at_)
{

}

bool operator==(const Token &a, const Token &b)
{
  return a.type == b.type && a.value == b.value && a.at == b.at;
}

void Token::print(std::ostream &out) const
{
  int rule = 0;	
  if (type == Token::END_OF_FILE) {
    out << "[EOF]";
  } else if (type == Token::END_OF_LINE) {
    out << "[EOL]" << std::endl;
  } else if (type == Token::BOLD_OPEN_MARK) 
    {
    out << "[*";
    for (size_t i=0; i<value.length(); ++i) {
      out << "&#" << (int) value[i] << ";";
    }
    out << "*]";
  } else if (type == Token::ITALIC_OPEN_MARK) 
    {
    out << "[/";
    for (size_t i=0; i<value.length(); ++i) {
      out << "&#" << (int) value[i] << ";";
    }
    out << "/]";
    } else if (type == Token::UNDERLINE_OPEN_MARK) 
    {
    out << "[_";
    for (size_t i=0; i<value.length(); ++i) {
      out << "&#" << (int) value[i] << ";";
    }
    out << "_]";
    } 
    else if (type == Token::BOLD_CLOSE_MARK) 
    {
    out << "*]";
  } else if (type == Token::ITALIC_CLOSE_MARK) 
    {
    out << "/]";
    } else if (type == Token::UNDERLINE_CLOSE_MARK) 
    {
    out << "_]";
    } else if (type == Token::TEXT) {
    out << "'";
    for (size_t i=0; i<value.length(); ++i) {
      out << "&#" << (int) value[i] << ";";
    }
    out << "'";
  } else {
    out << "? type=" << type << " value=?";
  }
}

std::ostream& operator<<(std::ostream &out, const Token &token)
{
  token.print(out);
  return out;
}




