#include "common/input.h"
#include <cstdint>
#include <cstdio>
#include "common/error.h"
#include "common/result.h"
#include "common/utf8.h"

namespace lr6 {

class EofError : public BasicError {
 public:
  ~EofError() override = default;

  String What() override { return u8"EOF? В терминале??"; }
};

Result<CodePoint> NextChar() {
  uint32_t array[4]{};
  array[0] = (char8_t)getchar();

  if ((char)array[0] == EOF) {
    return new EofError();
  }

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

Result<String> NextString() {
  String str(8);

  Result<CodePoint> cp = NextChar();
  if (IsErr(cp)) {
    return UnwrapErr(cp);
  }

  while (IsOk(cp) && Unwrap(cp).get() != '\n') {
    str.Append(Unwrap(cp));
    cp = NextChar();
  }

  return IsErr(cp) ? UnwrapErr(cp) : Ok<String>(str);
}
}  // namespace lr6