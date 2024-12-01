#ifndef LR6_COMMON_TASK_H_
#define LR6_COMMON_TASK_H_

#include <optional>
#include <variant>
#include "common/result.h"

namespace lr6 {
class Task {
 public:
  Task(const char *task, std::optional<int> option, const char *description)
      : task_(task), description_(description), option_(option) {}

  virtual ~Task() = default;
  virtual Result<std::monostate> Run() = 0;

  virtual void Greet();

 protected:
  const char *task_;
  const char *description_;
  std::optional<int> option_;
};
}  // namespace lr6

#endif  // LR6_COMMON_TASK_H_