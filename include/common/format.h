#ifndef LR6_COMMON_FORMAT_H_H
#define LR6_COMMON_FORMAT_H_H

#include <format>
#include <utility>
#include "common/string.h"

namespace lr6 {
template <typename T>
struct Colored {
  T value;
  String format;

  Colored(T value, String format) : value(value), format(std::move(format)) {}

  Colored<T> Bold() {
    format.Append(u8";1");
    return Colored<T>(std::move(value), format);
  }

  Colored<T> Italic() {
    format.Append(u8";3");
    return Colored<T>(std::move(value), format);
  }

  Colored<T> Underline() {
    format.Append(u8";4");
    return Colored<T>(std::move(value), format);
  }
};

template <typename T>
Colored<T> Black(T value) {
  return Colored<T>(value, String(u8"30"));
}

template <typename T>
Colored<T> Red(T value) {
  return Colored<T>(value, String(u8"31"));
}

template <typename T>
Colored<T> Green(T value) {
  return Colored<T>(value, String(u8"32"));
}

template <typename T>
Colored<T> Yellow(T value) {
  return Colored<T>(value, String(u8"33"));
}

template <typename T>
Colored<T> Blue(T value) {
  return Colored<T>(value, String(u8"34"));
}

template <typename T>
Colored<T> Magenta(T value) {
  return Colored<T>(value, String(u8"35"));
}

template <typename T>
Colored<T> Cyan(T value) {
  return Colored<T>(value, String(u8"36"));
}

template <typename T>
Colored<T> White(T value) {
  return Colored<T>(value, String(u8"37"));
}

}  // namespace lr6

template <typename T>
// NOLINTNEXTLINE : this is the official way to add formatting for custom types.
struct std::formatter<lr6::Colored<T>> : std::formatter<T> {
  auto format(const lr6::Colored<T> &obj, std::format_context &ctx) const {
    std::format_to(ctx.out(), "\033[0;{}m", obj.format.AsCString());
    ctx.advance_to(std::formatter<T>::format(obj.value, ctx));
    std::format_to(ctx.out(), "{}", "\033[0m");
    return ctx.out();
  }
};

template <>
struct std::formatter<lr6::String> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const lr6::String &obj, std::format_context &ctx) const {
    return std::format_to(ctx.out(), "{}", obj.AsCString());
  }
};

#endif  // LR6_COMMON_FORMAT_H_H