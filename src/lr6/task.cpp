#include "common/task.h"
#include "common/format.h"
#include "common/print.h"

void lr6::Task::Greet() {
  lr6::PrintLine("{:*^80}", std::format("{}", Green(task_).Bold()));
  if (option_.has_value()) {
    lr6::PrintLine("*{:^78}*",
                   std::format("Вариант {}", Green(option_.value()).Bold()));
  }
  lr6::PrintLine("{:*^80}", std::format("{}", Green("Описание").Bold()));
  lr6::PrintLine(description_);
  lr6::PrintLine(
      "{}", Cyan("Выполнил Забережный Тимофей Алексеевич, ст. группы 453501"));
}