#include "common/input.h"
#include <cstdint>
#include <cstdio>
#include "common/error.h"
#include "common/utf8.h"

namespace lr6 {

class BadSymbol : public BasicError {
  ~BadSymbol() override = default;

  String What() override { return u8"DIE"; }
};

Result<CodePoint> NextChar() {
  uint32_t array[4]{};
  array[0] = (char8_t)getchar();

  // TODO: validation
  if ((array[0] & 0b1000'0000) == 0) {
    return CodePoint::FromBytes(array);
  } else if ((array[0] & 0b1110'0000) == 0b1100'0000) {
    array[1] = (char8_t)getchar();
    return CodePoint::FromBytes(array);
  } else if ((array[0] & 0b1111'0000) == 0b1110'0000) {
    array[1] = (char8_t)getchar();
    array[2] = (char8_t)getchar();
    return CodePoint::FromBytes(array);
  } else {
    array[1] = (char8_t)getchar();
    array[2] = (char8_t)getchar();
    array[3] = (char8_t)getchar();
    return CodePoint::FromBytes(array);
  }
}
}  // namespace lr6