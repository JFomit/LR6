#include "task_1/task_1.h"
#include "common/input.h"
#include "common/print.h"
#include "common/result.h"

namespace lr6::task1 {
Result<std::monostate> Task1::Run() {
  auto str = NextString();
  if (IsErr(str)) {
    return UnwrapErr(str);
  }

  lr6::PrintLine("{}", Unwrap(str));

  return Ok<std::monostate>({});
}
}  // namespace lr6::task1
