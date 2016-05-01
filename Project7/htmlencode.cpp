#include "htmlencode.h"

static bool special(int codepoint)
{
  if (codepoint < 32) return true;
  if (codepoint >= 128) return true;
  if (codepoint == '<') return true;
  if (codepoint == '>') return true;
  if (codepoint == '&') return true;    
  return false;
}

void htmlencode(std::ostream &out, const std::wstring &value)
{
  for (size_t i=0; i<value.length(); ++i) {
    if (special(value[i])) {
      out << "&#" << (int) value[i] << ";";
    } else {
      out << (char) value[i];
    }
  }
}
