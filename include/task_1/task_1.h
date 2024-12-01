#ifndef LR6_TASK_1_H_
#define LR6_TASK_1_H_
#include "common/task.h"

namespace lr6::task1 {
class Task1 : public lr6::Task {
 public:
  Task1()
      : Task("Задание 1", 4,
             "Вводит строку, состоящую из групп нулей и единиц. Выводит те "
             "группы, которые имею четную длину.") {}

  ~Task1() override = default;
  Result<std::monostate> Run() override;

  Result<String> CheckValid(const String &str);
};
}  // namespace lr6::task1

#endif  // LR6_TASK_1_H_