#ifndef LR6_COMMON_RESULT_H_
#define LR6_COMMON_RESULT_H_

#include <variant>
#include "common/box.h"
#include "common/error.h"

namespace lr6 {
using ErrorType = Box<BasicError>;

template <typename T>
using Result = std::variant<ErrorType, T>;

template <typename T>
Result<T> Err(ErrorType e) {
  return Result<T>{e};
}

template <typename T>
Result<T> Ok(T t) {
  return Result<T>{t};
}

template <typename T>
bool IsOk(const Result<T> &result) {
  return std::holds_alternative<T>(result);
}

template <typename T>
bool IsErr(const Result<T> &result) {
  return std::holds_alternative<ErrorType>(result);
}

template <typename T>
T &Unwrap(Result<T> &result) {
  return std::get<T>(result);
}

template <typename T>
T &&Unwrap(Result<T> &&result) {
  return std::get<T>(std::move(result));
}

template <typename T>
ErrorType &UnwrapErr(Result<T> &result) {
  return std::get<ErrorType>(result);
}

template <typename T>
ErrorType &&UnwrapErr(Result<T> &&result) {
  return std::get<ErrorType>(std::move(result));
}

template <typename T, typename FOk, typename FErr>
auto Match(Result<T> &result, FOk &&if_ok, FErr &&if_err) {
  if (IsOk(result)) {
    return if_ok(Unwrap(result));
  } else {
    return if_err(UnwrapErr(result));
  }
}

template <typename T, typename F>
auto Transform(Result<T> result, F &&transformer) {
  if (IsOk(result)) {
    return Result<T>{transformer(Unwrap(result))};
  }

  return Result<T>{UnwrapErr(result)};
}

template <typename T, typename F>
auto Bind(Result<T> result, F &&transformer) {
  if (IsOk(result)) {
    return transformer(Unwrap(result));
  }

  return Result<T>{UnwrapErr(result)};
}
}  // namespace lr6

#endif  // LR6_COMMON_RESULT_H_