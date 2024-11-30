#include <iostream>
#include "common/string.h"

int main() {
  lr6::String str = u8"Ой";

  for (auto c : str.Chars()) {
    auto chars = reinterpret_cast<char(*)[4]>(&c);

    for (size_t i = 0; i < 4; ++i) {
      char a_char = chars[0][i];
      if (a_char == '\0') {
        break;
      }

      std::cout << a_char;
    }
  }
  std::cout << '\n';

  return 0;
}