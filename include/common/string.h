#ifndef LR6_COMMON_STRING_H_
#define LR6_COMMON_STRING_H_

#include <cstddef>
#include <cstring>

namespace lr6 {

class CharEnumerator {
  char32_t *begin();
  char32_t *end();

 private:
  char8_t *str_;
  size_t current_offset_;
};

/**
 * @brief A mutable growable owned utf-8 ready string.
 * 
 */
class String {
 public:
  String(char *buffer, size_t length);
  explicit String(char *buffer);
  explicit String(size_t capcity);
  String(const String &other);
  String(String &&other) noexcept;

  ~String();

  String &operator=(const String &other);
  String &operator=(String &&other) noexcept;

  String &Append(char8_t c);
  String &Append(char32_t c);

  /**
   * @brief Get a pointer to the string's internal buffer.
   * @warning If this string is modified in *any* way,
   * the pointer returned from this method might become invalid. Also,
   * as per utf-8 spec, the NUL byte is a valid part of the string, so the C str*
   * functions might not be able to operate on the whole charachter buffer.
   * @return A const char *, pointing to the internal charachter buffer.
   */
  [[nodiscard]] const char *AsCString() const;

  /**
   * @brief Get a pointer to the copy of string's internal buffer.
   * @warning as per utf-8 spec, the NUL byte is a valid part of the string, so the C str*
   * functions might not be able to operate on the whole charachter buffer.
   * @return A char *, pointing to the charachter array, holding the copy of this String's buffer.
   */
  [[nodiscard]] char *ToCString() const;

  friend class CharEnumerator;
  CharEnumerator EnumerateChars();

 private:
  char8_t *buffer_;
  size_t length_;
  size_t capcity_;

  void Grow();
  void Free();
};

}  // namespace lr6

#endif  // LR6_COMMON_STRING_H_