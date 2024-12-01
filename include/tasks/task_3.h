#ifndef LR6_TASK_3_H_
#define LR6_TASK_3_H_

#include "common/task.h"

namespace lr6::task3 {
class Task3 : public Task {
 public:
  Task3()
      : Task("Задача 3", 4,
             "Вводит массив строк. In-pace меняет слова строк местами.") {}

  ~Task3() override = default;
  Result<std::monostate> Run() override;

  void MagicSwap(String &str);
};
}  // namespace lr6::task3

#endif  // LR6_TASK_3_H_