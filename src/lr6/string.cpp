#include "common/string.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include "common/utf8.h"

namespace lr6 {
const char *String::AsCString() const {
  return (char *)this->buffer_;
}

char *String::ToCString() const {
  char *c_str = new char[length_ + /* null terminator*/ 1]{};
  // It is actually perfectly valid to have a NUL char8_t in the middle of utf-8.
  // sadly, C functions are not aware of this fact. So, we use memcpy() instead of strcpy.
  std::memcpy(c_str, (void *)buffer_, length_ * sizeof(char));
  c_str[length_] = '\0';

  return c_str;
}

void String::Reserve(size_t count) {
  if (count <= capcity_) {
    return;
  }

  while (count > capcity_) {
    capcity_ *= 2;  // preserving exponential growth
  }

  auto *new_buffer = new char[capcity_ + 1]{};
  memcpy(new_buffer, buffer_, length_);
  delete[] buffer_;
  buffer_ = new_buffer;
}

void String::ReserveExact(size_t count) {
  if (count <= capcity_) {
    return;
  }

  capcity_ = count;

  auto *new_buffer = new char[capcity_ + 1]{};
  memcpy(new_buffer, buffer_, length_);
  delete[] buffer_;
  buffer_ = new_buffer;
}

String &String::Append(char c) {
  if (c == '\0') {
    return *this;
  }

  if (length_ + 1 >= capcity_) {
    Grow();
  }

  buffer_[length_] = c;
  ++length_;
  return *this;
}

String &String::Append(CodePoint code_point) {
  uint32_t value = code_point.get();
  auto array = *reinterpret_cast<char(*)[4]>(&value);
  if ((array[0] & 0b1000'0000) == 0) {
    Append(array[0]);
    return *this;
  } else if ((array[0] & 0b1110'0000) == 0b1100'0000) {
    Append(array[0]);
    Append(array[1]);
    return *this;
  } else if ((array[0] & 0b1111'0000) == 0b1110'0000) {
    Append(array[0]);
    Append(array[1]);
    Append(array[2]);
    return *this;
  } else {
    Append(array[0]);
    Append(array[1]);
    Append(array[2]);
    Append(array[3]);
    return *this;
  }
}

String::String(char8_t *buffer, size_t length) {
  length_ = length;
  capcity_ = length + 1;
  buffer_ = new char[length_ + 1]{};

  memcpy(buffer_, buffer, length_);
}

String::String(char *buffer) {
  length_ = strlen(buffer);
  capcity_ = length_ + 1;
  buffer_ = new char[length_ + 1]{};

  memcpy(buffer_, buffer, length_ + 1);
}

String::String(const char *buffer) {
  length_ = strlen(buffer);
  capcity_ = length_ + 1;
  buffer_ = new char[length_ + 1]{};

  memcpy(buffer_, buffer, length_ + 1);
}

String::String(size_t capcity) {
  length_ = 0;
  capcity_ = capcity;
  buffer_ = new char[capcity_]{};
}

String::String(const String &other) {
  buffer_ = new char[other.capcity_]{};
  capcity_ = other.capcity_;
  memcpy(buffer_, other.buffer_, other.length_);
  length_ = other.length_;
}

String::String(String &&other) noexcept {
  buffer_ = other.buffer_;
  capcity_ = other.capcity_;
  length_ = other.length_;

  other.buffer_ = nullptr;
  other.capcity_ = 0;
  other.length_ = 0;
}

String::~String() {
  Free();
}

String &String::operator=(const String &other) {
  if (this == &other) {
    return *this;
  }
  delete[] buffer_;
  buffer_ = new char[other.capcity_]{};
  capcity_ = other.capcity_;
  memcpy(buffer_, other.buffer_, other.length_);
  length_ = other.length_;

  return *this;
}

String &String::operator=(String &&other) noexcept {
  delete[] buffer_;

  buffer_ = other.buffer_;
  capcity_ = other.capcity_;
  length_ = other.length_;

  other.buffer_ = nullptr;
  other.length_ = 0;
  other.capcity_ = 0;

  return *this;
}

void String::Grow() {
  capcity_ *= 2;
  auto *new_buffer = new char[capcity_ + 1]{};
  memcpy(new_buffer, buffer_, length_);
  delete[] buffer_;
  buffer_ = new_buffer;
}

void String::Free() {
  delete[] buffer_;
  buffer_ = nullptr;
  capcity_ = 0;
  length_ = 0;
}

std::ostream &operator<<(std::ostream &stream, const String &string) {
  // TODO: maybe its better to print chars one by one?
  stream << string.AsCString();

  return stream;
}

String::CharsIterator String::Chars() const {
  return String::CharsIterator(*this);
}

// #region CharsIterator
String::CharsIterator::CharsIterator(const String &str) {
  buffer_ptr_ = str.buffer_;
  length_ = str.length_;
}

String::CharsIterator::CharsIterator(const char *buffer, size_t length) {
  buffer_ptr_ = buffer;
  length_ = length;
}

String::CharsIterator &String::CharsIterator::operator++() {
  assert(length_ > 0);

  auto first = *buffer_ptr_;
  if ((first & 0b1000'0000) == 0) {
    buffer_ptr_ += 1;
    length_ -= 1;
    return *this;
  } else if ((first & 0b1111'0000) == 0b1111'0000) {
    buffer_ptr_ += 4;
    length_ -= 4;
    return *this;
  } else if ((first & 0b1110'0000) == 0b1110'0000) {
    buffer_ptr_ += 3;
    length_ -= 3;
    return *this;
  } else if ((first & 0b1100'0000) == 0b1100'0000) {
    buffer_ptr_ += 2;
    length_ -= 2;
    return *this;
  } else {
    assert(false);
  }
}

String::CharsIterator String::CharsIterator::begin() {
  return *this;
}

String::CharsIterator String::CharsIterator::end() {
  return {this->buffer_ptr_ + this->length_, 0};
}

CodePoint String::CharsIterator::operator*() const {
  uint32_t array[4]{};
  array[0] = (unsigned char)buffer_ptr_[0];

  // TODO: validation
  if ((array[0] & 0b1000'0000) == 0) {
    return CodePoint::FromBytes(array);
  } else if ((array[0] & 0b1111'0000u) == 0b1111'0000u) {
    array[1] = (unsigned char)buffer_ptr_[1];
    array[2] = (unsigned char)buffer_ptr_[2];
    array[3] = (unsigned char)buffer_ptr_[3];
    return CodePoint::FromBytes(array);
  } else if ((array[0] & 0b1110'0000) == 0b1110'0000) {
    array[1] = (unsigned char)buffer_ptr_[1];
    array[2] = (unsigned char)buffer_ptr_[2];
    return CodePoint::FromBytes(array);
  } else if ((array[0] & 0b1100'0000) == 0b1100'0000) {
    array[1] = (unsigned char)buffer_ptr_[1];
    return CodePoint::FromBytes(array);
  } else {
    assert(false);
  }
}

bool String::CharsIterator::operator!=(const String::CharsIterator &other) {
  return this->buffer_ptr_ != other.buffer_ptr_;
}

// #endregion

}  // namespace lr6