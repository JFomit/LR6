#include <sys/types.h>
#include <exception>
#include "common/error.h"
#include "common/format.h"
#include "common/input.h"
#include "common/print.h"
#include "common/result.h"
#include "common/task.h"
#include "tasks/task_1.h"
#include "tasks/task_2.h"
#include "tasks/task_3.h"

using lr6::IsErr;

void PrintHelp(int /*why*/ = 1) {
  lr6::PrintLine("{0: ^80}", lr6::Green("Лабораторная работа 7").Bold());
  lr6::PrintLine("{0:-^80}", lr6::Blue("Справка").Bold());
  lr6::PrintLine("Доступны опции:");

  lr6::PrintLine("{0} - {1}", lr6::Magenta('q'), lr6::Red("Выход"));
  lr6::PrintLine("{0} - {1}", lr6::Magenta('h'), lr6::Blue("Эта справка"));
  lr6::PrintLine("{0} - {1}", lr6::Magenta('1'), "Задание 1");
  lr6::PrintLine("{0} - {1}", lr6::Magenta('2'), "Задание 2");
  lr6::PrintLine("{0} - {1}", lr6::Magenta('2'), "Задание 3");

  lr6::PrintLine("{0:-^80}", lr6::Blue("Справка").Bold());
}

int main() {
  lr6::task1::Task1 t1{};
  lr6::task2::Task2 t2{};
  lr6::task3::Task3 t3{};

  bool should_exit = false;
  lr6::Task *task;

  PrintHelp();
  while (!should_exit) {
    auto opt = lr6::Next<char>();
    if (IsErr(opt)) {
      auto err = lr6::UnwrapErr(opt);
      lr6::PrintLine("{}", Red(err->What()));
      continue;
    }
    auto option = lr6::Unwrap(opt);
    switch (option) {
      case 'h':
        PrintHelp();
        continue;
      case '1':
        task = &t1;
        break;
      case '2':
        task = &t2;
        break;
      case '3':
        task = &t3;
        break;
      case 'q':
        should_exit = true;
        continue;
      default:
        lr6::PrintLine("{}",
                       lr6::Red("Неизветсная опция. Введите h для справки."));
        continue;
    }

    task->Greet();

    try {
      auto result = task->Run();
      if (IsErr(result)) {
        lr6::PrintLine("{}", lr6::Red(lr6::UnwrapErr(result)->What()));
      }
    } catch (std::exception &e) {
      lr6::PrintLine("{}", lr6::Red(e.what()));
    }
  }

  return 0;
}