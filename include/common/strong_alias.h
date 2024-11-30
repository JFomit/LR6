#ifndef LR6_COMMON_STRONG_ALIAS_H_
#define LR6_COMMON_STRONG_ALIAS_H_

namespace lr6 {
template <typename T, typename Tag, template <typename> class... Abilities>
class StrongAlias : public Abilities<StrongAlias<T, Tag, Abilities...>>... {
 public:
  explicit StrongAlias(T const &value) : value_(value) {}

  ~StrongAlias() = default;

  T &get() { return value_; }

  T const &get() const { return value_; }

 private:
  T value_;
};
}  // namespace lr6

#endif  // LR6_COMMON_STRONG_ALIAS_H_