#ifndef LR6_COMMON_INPUT_H_
#define LR6_COMMON_INPUT_H_

#include <iostream>
#include <limits>
#include <optional>
#include "common/error.h"
#include "common/result.h"
#include "common/utf8.h"

namespace lr6 {
Result<CodePoint> NextChar();
Result<String> NextString();

template <typename T>
class ReadTError : public BasicError {
 public:
  ReadTError(const char *message) { message_ = message; }

  ~ReadTError() override = default;

  String What() override { return String(message_); }

 private:
  const char *message_;
};

template <typename T>
Result<T> Next(std::optional<const char *> message = std::nullopt) {
  T value{};

  std::cin >> value;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return new ReadTError<T>(
        message.value_or("Не удалось прочитать значение."));
  }

  if (!std::cin.eof() && std::cin.peek() != '\n') {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return new ReadTError<T>(
        message.value_or("Не удалось прочитать значение."));
  }

  return value;
}
}  // namespace lr6

#endif  // LR6_COMMON_INPUT_H_