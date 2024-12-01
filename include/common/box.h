#ifndef LR6_COMMON_BOX_H_
#define LR6_COMMON_BOX_H_

namespace lr6 {
/**
   * @brief Aka `lame' std::unique_ptr<T>
   * 
   * @tparam T 
   */
template <typename T>
class Box {
 public:
  Box(T *pointer) { pointer_ = pointer; }

  Box(const Box &) = delete;

  Box(Box &&other) noexcept { pointer_ = other.pointer_; }

  Box &operator=(const Box &) = delete;

  Box &operator=(Box &&other) noexcept {
    pointer_ = other.pointer_;
    other.pointer_ = nullptr;
  }

  ~Box() { delete pointer_; }

  T &operator*() { return *pointer_; }

  const T *operator->() const { return pointer_; }

  T *operator->() { return pointer_; }

  const T &operator*() const { return *pointer_; }

 private:
  T *pointer_;
};
}  // namespace lr6

#endif  // LR6_COMMON_BOX_H_