#ifndef LR6_COMMON_RC_H_
#define LR6_COMMON_RC_H_

#include <cstddef>

namespace lr6 {
template <typename T>
class Rc {
 public:
  Rc(const Rc &other) {
    pointer_ = other.pointer_;
    count_ = other.count_;
    Aquire();
  }

  Rc(Rc &&) = delete;

  Rc &operator=(const Rc &other) {
    if (this != &other) {
      return *this;
    }

    Release();
    pointer_ = other.pointer_;
    count_ = other.count_;
    Aquire();

    return *this;
  }

  Rc &operator=(Rc &&) = delete;

  Rc(T *pointer) {
    count_ = new size_t(0);
    pointer_ = pointer;
    Aquire();
  }

  ~Rc() { Release(); }

  T &operator*() { return *pointer_; }

  const T &operator*() const { return *pointer_; }

  T *operator->() { return pointer_; }

  const T *operator->() const { return pointer_; }

 private:
  size_t *count_;
  T *pointer_;

  Rc(T *pointer, size_t *count) {
    pointer_ = pointer;
    count_ = count;
  }

  void Release() {
    if (count_ == nullptr) {
      return;
    }

    *count_ -= 1;
    if (*count_ == 0) {
      delete pointer_;
      delete count_;

      pointer_ = nullptr;
      count_ = nullptr;
    }
  }

  void Aquire() { *count_ += 1; }
};
}  // namespace lr6

#endif  // LR6_COMMON_RC_H_