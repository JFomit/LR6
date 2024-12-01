#ifndef LR6_COMMON_STRING_H_
#define LR6_COMMON_STRING_H_

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ostream>
#include "common/utf8.h"

namespace lr6 {

/**
 * @brief A mutable growable owned utf-8 ready string.
 * 
 */
class String {
  static_assert(sizeof(char) == sizeof(char8_t) == sizeof(uint8_t));

 public:
  /**
  * @brief Construct a new String object
  * 
  * @tparam N length of the const char[] array
  */
  template <size_t N>
  String(char8_t const (&array)[N]) {
    buffer_ = new char[N]{};
    memcpy(buffer_, &array[0], N);
    length_ = N - 1;
    capcity_ = N;
  }

  /**
 * @brief Construct a new String object
 * 
 * @param buffer buffer to read chars from
 * @param length length of the buffer 
 */
  String(char8_t *buffer, size_t length);
  /**
   * @brief Construct a new String object
   * 
   * @param buffer C-string
   */
  explicit String(char *buffer);
  /**
   * @brief Construct a new String object
   * 
   * @param buffer C-string
   */
  explicit String(const char *buffer);
  /**
   * @brief Construct a new empty String object
   * 
   * @param capcity number of bytes to initially reserve, 8 by default.
   */
  explicit String(size_t capacity = 8);
  String(const String &other);
  String(String &&other) noexcept;

  ~String();

  String &operator=(const String &other);
  String &operator=(String &&other) noexcept;

  /**
   * @brief Reserves the specified number of chars, preserving exponential growth
   * 
   * @param count number of bytes to ensure that the String will accomodate w/o a reallocation
   */
  void Reserve(size_t count);

  /**
   * @brief Reserves the specified number of chars. Doesn't exponentially scale
   * 
   * @param count number of bytes to ensure that the String will accomodate w/o a reallocation
   */
  void ReserveExact(size_t count);

  /**
   * @brief Appends a utf8 ascii charachter at the end of the string
   * 
   * @param c a char to append
   * @return String& this
   */
  String &Append(char c);

  /**
   * @brief Appends another string to the end of this one
   * 
   * @param other a String to append
   * @return String& this
   */
  String &Append(const String &other);

  /**
   * @brief Appends a u8 string literal at the end of the string
   * 
   * @tparam N length of the string
   * @return String& this
   */
  template <size_t N>
  String &Append(const char (&c)[N]) {
    for (size_t i = 0; i < N; ++i) {
      Append(c[i]);
    }
    return *this;
  }

  String &Append(const char *c);

  /**
   * @brief Appends a unicode code point at the end of the string
   * 
   * @param code_point to append
   * @return String& this
   */
  String &Append(CodePoint code_point);

  bool Insert(const String &other, size_t pos);

  void PopBack();

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

  /**
   * @brief Gets the *byte* length of the string.
   * Be advised: this method doesn't return the number of characthers in
   * the string; only the mere number of bytes it occupies (w/o null terminator)
   * @return size_t *byte* length of the string
   */
  size_t length();

  class CharsIterator {
   public:
    CodePoint operator*() const;
    CharsIterator begin();
    CharsIterator end();

    explicit CharsIterator(const String &string);
    ~CharsIterator() = default;

    bool operator!=(const CharsIterator &other);
    CharsIterator &operator++();

   private:
    CharsIterator(const char *buffer, size_t length);
    const char *buffer_ptr_;
    size_t length_;
  };

  /**
   * @brief Gets a const iterator to this string
   * 
   * @return CharsIterator 
   */
  [[nodiscard]] CharsIterator Chars() const;

  /**
   * @brief Manually deallocates a string. Not recommended.
   * 
   */
  void Free();

 private:
  char *buffer_;
  size_t length_;
  size_t capcity_;

  void Grow();
};

std::ostream &operator<<(std::ostream &stream, const String &string);

}  // namespace lr6

#endif  // LR6_COMMON_STRING_H_