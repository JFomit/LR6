#include <utility>

#include "common/error.h"
#include "common/input.h"
#include "common/print.h"
#include "common/result.h"
#include "tasks/task_2.h"

namespace lr6::task2 {
class WrongPositionError : public BasicError {
 public:
  WrongPositionError(String str) : message_(std::move(str)) {}

  ~WrongPositionError() override = default;

  String What() override { return message_; }

 private:
  String message_;
};

Result<std::monostate> Task2::Run() {
  lr6::PrintLine("Введите строку:");
  auto res = NextString();
  if (IsErr(res)) {
    return UnwrapErr(res);
  }
  auto string = Unwrap(res);

  lr6::PrintLine("Введите подстроку:");
  auto res2 = NextString();
  if (IsErr(res2)) {
    return UnwrapErr(res2);
  }
  auto substring = Unwrap(res2);

  lr6::PrintLine("Введите позицию вставки:");
  auto res3 =
      Bind(Next<long>("Введено не число."), [](long l) -> Result<size_t> {
        if (l < 0) {
          return new WrongPositionError(
              u8"Позиция для вставки не может быть отрицательной.");
        }

        return (size_t)l;
      });

  if (IsErr(res3)) {
    return UnwrapErr(res3);
  }
  auto position = Unwrap(res3);
  auto result = string.Insert(substring, position);

  if (!result) {
    return new WrongPositionError(
        u8"Позиция для вставки не может превышать длину строки.");
  }

  lr6::PrintLine("Итого:\n{}", string.AsCString());

  return Ok<std::monostate>({});
}
}  // namespace lr6::task2