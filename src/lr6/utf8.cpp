#include "common/utf8.h"

std::ostream &lr6::operator<<(std::ostream &stream, CodePoint code_point) {
  static_assert(sizeof(code_point.get()) / sizeof(char) == 4);
  auto bytes = reinterpret_cast<char(*)[4]>(&code_point.get());
  for (auto c : *bytes) {
    if (c == '\0') {
      break;
    }
    stream << c;
  }
  return stream;
}