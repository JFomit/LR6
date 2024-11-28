#include "common/string.h"
#include <cstring>

namespace lr6 {
const char *String::AsCString() const {
  return (char *)this->buffer_;
}

char *String::ToCString() const {
  char *c_str = new char[length_ + /* null terminator*/ 1]{};
  // It is actually perfectly valid to have a NUL char in the middle of utf-8.
  // sadly, C functions are not aware of that. So, we use memcpy() instead of strcpy.
  std::memcpy(c_str, (void *)buffer_, length_ * sizeof(char8_t));
  c_str[length_] = '\0';

  return c_str;
}

CharEnumerator String::EnumerateChars() {
  return CharEnumerator();
}

char32_t *CharEnumerator::begin() {}

String::~String() {
  delete[] buffer_;
}
}  // namespace lr6