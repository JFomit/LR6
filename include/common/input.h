#ifndef LR6_COMMON_INPUT_H_
#define LR6_COMMON_INPUT_H_

#include "common/result.h"
#include "common/utf8.h"

namespace lr6 {
Result<CodePoint> NextChar();
}

#endif  // LR6_COMMON_INPUT_H_