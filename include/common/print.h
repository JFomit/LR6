#ifndef LR6_COMMON_PRINT_H_
#define LR6_COMMON_PRINT_H_

#include <format>
#include <iostream>

namespace lr6 {
template <typename... Args>
void Print(std::format_string<Args...> &&format, Args &&...args) {
  auto result = std::format(std::forward<std::format_string<Args...>>(format),
                            std::forward<Args &&>(args)...);
  std::cout << result;
}

template <typename... Args>
void PrintLine(std::format_string<Args...> &&format, Args &&...args) {
  auto result = std::format(std::forward<std::format_string<Args...>>(format),
                            std::forward<Args &&>(args)...);
  std::cout << result << '\n';
}

void Print(const char *str);
void PrintLine(const char *str);
}  // namespace lr6

#endif  // LR6_COMMON_PRINT_H_