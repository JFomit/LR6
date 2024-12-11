#include "tasks/task_3.h"
#include "common/error.h"
#include "common/input.h"
#include "common/print.h"
#include "common/result.h"

namespace lr6::task3 {

class WrongLengthError : public BasicError {
  ~WrongLengthError() override = default;

  String What() override {
    return u8"Длина массива строк должна быть положительным числом.";
  }
};

Result<std::monostate> Task3::Run() {
  lr6::PrintLine("Введите длину массива N");
  auto res1 =
      Bind(Next<long>("Введено не число."), [](long l) -> Result<size_t> {
        if (l <= 0) {
          return new WrongLengthError();
        }

        return (size_t)l;
      });
  if (IsErr(res1)) {
    return UnwrapErr(res1);
  }
  auto n = Unwrap(res1);

  String all_at_once = String();
  for (size_t i = 0; i < n; ++i) {
    auto res2 = NextString();
    if (IsErr(res2)) {
      return UnwrapErr(res2);
    }
    all_at_once.Append(Unwrap(res2)).Append('\n');
  }
  all_at_once.PopBack();
  lr6::PrintLine("Результат:");

  MagicSwap(all_at_once);
  lr6::PrintLine("{}", all_at_once.AsCString());

  return Ok<std::monostate>({});
}

struct Span {
  char *begin;
  char *end;
};

void Reverse(Span span) {
  while (span.begin < span.end) {
    std::swap(*span.begin, *span.end);
    ++span.begin;
    --span.end;
  }
}

void ReverseWords(char *buffer) {
  char *word_begin = buffer;
  char *word_end = word_begin;
  while (*word_begin != '\0') {
    while (*word_begin == ' ' || *word_begin == '\n') {
      ++word_begin;
    }
    word_end = word_begin;
    while (*word_end != ' ' && *word_end != '\n' && *word_end != '\0') {
      ++word_end;
    }
    --word_end;

    Reverse(Span{.begin = word_begin, .end = word_end});
    word_begin = word_end + 1;
  }
}

void Task3::MagicSwap(String &str) {
  auto buffer = (char *)str.AsCString();

  // Reverse the string
  Reverse(Span{.begin = buffer, .end = buffer + str.length() - 1});

  // Reverse each word
  ReverseWords(buffer);
}
}  // namespace lr6::task3