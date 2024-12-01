#ifndef LR6_COMMON_UTF_8_H_
#define LR6_COMMON_UTF_8_H_

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include "common/abilities.h"
#include "common/strong_alias.h"

namespace lr6 {

template <typename T>
struct FromByteable {
  static T FromBytes(uint32_t (&arr)[4]) {
    return T((arr[0]) | arr[1] << 8 | arr[2] << 16 | arr[3] << 24);
  }
};

using CodePoint = StrongAlias<uint32_t, struct CodePoint_t, FromByteable>;

std::ostream &operator<<(std::ostream &stream, CodePoint code_point);
}  // namespace lr6

#endif  // LR6_COMMON_UTF_8_H_