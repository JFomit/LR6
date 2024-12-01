#include "tasks/task_1.h"
#include <cassert>
#include <cstring>
#include "common/error.h"
#include "common/input.h"
#include "common/print.h"
#include "common/result.h"
#include "common/utf8.h"

namespace lr6::task1 {

class InputWasTooLongError : public BasicError {
  ~InputWasTooLongError() override = default;

  String What() override {
    return u8"Введенная строка была слишком длинная - заняла более 80 байт.";
  }
};

class StupidlyLimitedString {
 public:
  static const size_t kMaxSize = 81;

  StupidlyLimitedString() {
    buffer_ = new char[kMaxSize]{};
    length_ = 0;
  }

  StupidlyLimitedString(char *ptr) {
    buffer_ = ptr;
    length_ = strlen(ptr);
  }

  ~StupidlyLimitedString() {
    delete[] buffer_;
    buffer_ = nullptr;
    length_ = 0;
  }

  StupidlyLimitedString(StupidlyLimitedString &&mv) noexcept {
    buffer_ = mv.buffer_;
    length_ = mv.length_;

    mv.buffer_ = nullptr;
    mv.length_ = 0;
  }

  bool Append(CodePoint code_point) {
    auto bytes = reinterpret_cast<char(*)[4]>(&code_point.get());

    size_t needs_to_write = 0;
    for (auto c : *bytes) {
      if (c == '\0') {
        break;
      }

      ++needs_to_write;
    }

    bool result = true;
    if (length_ + needs_to_write <= kMaxSize - 1) {
      for (size_t i = 0; i < needs_to_write; ++i) {
        result = result && Append(bytes[0][i]);
      }
      return result;
    }

    return false;
  }

  static Result<StupidlyLimitedString> ReadAString(int /*why?*/ = 1) {
    auto cp = NextChar();
    StupidlyLimitedString str;

    while (IsOk(cp) && Unwrap(cp).get() != '\n') {
      if (!str.Append(Unwrap(cp))) {
        return new InputWasTooLongError();
      }
      cp = NextChar();
    }

    if (IsErr(cp)) {
      return UnwrapErr(cp);
    }

    return str;
  }

  operator String() { return String(buffer_); }

 private:
  size_t length_;
  char *buffer_;

  bool Append(char c) {
    if (length_ < kMaxSize - 1) {
      buffer_[length_] = c;
      ++length_;
      return true;
    }
    return false;
  }
};

Result<std::monostate> Task1::Run() {
  lr6::PrintLine("Введите строку из 0 и 1:");
  auto str = StupidlyLimitedString::ReadAString();
  if (IsErr(str)) {
    return UnwrapErr(str);
  }

  auto real_str = CheckValid((String)Unwrap(str));
  if (IsErr(real_str)) {
    return UnwrapErr(real_str);
  }

  auto string = Unwrap(real_str).AsCString();

  size_t prev = 0;
  size_t curr = 0;
  while (string[curr] != '\0') {
    if (string[curr] == ' ') {
      if ((curr - prev) % 2 == 0) {
        while (prev <= curr) {
          std::cout << string[prev];
          ++prev;
        }
        std::cout << '\n';
      } else {
        prev = curr + 1;
      }
    }
    ++curr;
  }
  if ((curr - prev) % 2 == 0) {
    while (prev <= curr) {
      std::cout << string[prev];
      ++prev;
    }
    std::cout << '\n';
  }

  return Ok<std::monostate>({});
}

class InvalidCharError : public BasicError {
 public:
  explicit InvalidCharError(CodePoint code_point) : code_point_(code_point) {}

  ~InvalidCharError() override = default;

  String What() override {
    return String(u8"Встречен неожиданный символ - `")
        .Append(code_point_)
        .Append('\'');
  }

 private:
  CodePoint code_point_;
};

Result<String> Task1::CheckValid(const String &str) {
  for (auto cp : str.Chars()) {
    if (cp.get() == ' ' || cp.get() == '0' || cp.get() == '1') {
      continue;
    }

    return new InvalidCharError(cp);
  }

  return str;
}

}  // namespace lr6::task1
