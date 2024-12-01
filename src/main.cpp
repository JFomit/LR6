#include "common/error.h"
#include "common/format.h"
#include "common/print.h"
#include "common/result.h"
#include "tasks/task_2.h"

using lr6::IsErr;

int main() {
  lr6::task2::Task2 t1{};
  t1.Greet();

  auto result = t1.Run();
  if (IsErr(result)) {
    auto b = UnwrapErr(result);
    lr6::PrintLine("{}", Red(b->What()));
  }

  return 0;
}