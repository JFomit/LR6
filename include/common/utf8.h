#ifndef LR6_COMMON_UTF_8_H_
#define LR6_COMMON_UTF_8_H_

#include <cstdint>
#include "common/abilities.h"
#include "common/strong_alias.h"

namespace lr6 {
// using CodePoint = uint32_t;

using CodePoint = StrongAlias<uint32_t, class CodePoint_t, BinaryNumber>;

// auto chars = reinterpret_cast<char(*)[4]>(&c);

//     for (size_t i = 0; i < 4; ++i) {
//       char a_char = chars[0][i];
//       if (a_char == '\0') {
//         break;
//       }

//       std::cout << a_char;
// }

// std::ostream &operator<<(std::ostream &stream, CodePoint code_point) {}
}  // namespace lr6

#endif  // LR6_COMMON_UTF_8_H_