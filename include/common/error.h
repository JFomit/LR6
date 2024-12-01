#ifndef LR6_COMMON_ERROR_H_
#define LR6_COMMON_ERROR_H_

#include "common/string.h"

namespace lr6 {
class BasicError {
 public:
  virtual ~BasicError() = default;

  virtual String What() = 0;
};
}  // namespace lr6

#endif  // LR6_COMMON_ERROR_H_