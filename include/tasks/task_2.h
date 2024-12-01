#ifndef LR6_TASK_2_H_
#define LR6_TASK_2_H_

#include "common/task.h"

namespace lr6::task2 {
class Task2 : public Task {
 public:
  ~Task2() override = default;

  Task2()
      : Task("Задание 2", 4,
             "Вводит строку текста; в указанное место вставляет подстроку.") {}

  Result<std::monostate> Run() override;
};
}  // namespace lr6::task2

#endif  // LR6_TASK_2_H_