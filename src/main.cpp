#include <iostream>
#include "common/error.h"
#include "common/format.h"
#include "common/input.h"
#include "common/print.h"
#include "common/result.h"
#include "task_1/task_1.h"

using lr6::IsErr;

int main() {
  lr6::task1::Task1 t1{};
  t1.Greet();

  auto result = t1.Run();
  if (IsErr(result)) {
    auto b = UnwrapErr(result);
    lr6::PrintLine("{}", b->What());
  }

  return 0;
}