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

using lr6::IsErr, lr6::Unwrap, lr6::UnwrapErr;
using lr6::Magenta, lr6::Red, lr6::Blue, lr6::Cyan, lr6::Green;

void PrintHelp(int /*why*/ = 1) {
  lr6::PrintLine("{0: ^80}", Green("Лабораторная работа 7").Bold());
  lr6::PrintLine(
      "{}", Cyan("Выполнил Забережный Тимофей Алексеевич, ст. группы 453501"));
  lr6::PrintLine("{0:-^80}", Blue("Справка").Bold());
  lr6::PrintLine("Доступны опции:");

  lr6::PrintLine("{0} - {1}", Magenta('q'), Red("Выход"));
  lr6::PrintLine("{0} - {1}", Magenta('h'), Blue("Эта справка"));
  lr6::PrintLine("{0} - {1}", Magenta('1'), "Задание 1");
  lr6::PrintLine("{0} - {1}", Magenta('2'), "Задание 2");
  lr6::PrintLine("{0} - {1}", Magenta('2'), "Задание 3");

  lr6::PrintLine("{0:-^80}", Blue("Справка").Bold());
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
      auto err = UnwrapErr(opt);
      lr6::PrintLine("{}", Red(err->What()));
      continue;
    }
    auto option = Unwrap(opt);
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
        lr6::PrintLine("{}", Red("Неизветсная опция. Введите h для справки."));
        continue;
    }

    task->Greet();

    try {
      auto result = task->Run();
      if (IsErr(result)) {
        lr6::PrintLine("{}", Red(UnwrapErr(result)->What()));
      }
    } catch (std::exception &e) {
      lr6::PrintLine("{}", Red(e.what()));
    }
  }

  return 0;
}