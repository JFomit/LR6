#ifndef LR6_COMMON_SKILLS_H_
#define LR6_COMMON_SKILLS_H_

namespace lr6 {

template <typename T, template <typename> class crtpType>
struct BasicAbility {
  T &get() { return static_cast<T &>(*this); }

  T const &get() const { return static_cast<T const &>(*this); }
};

template <typename T>
struct Addable : BasicAbility<T, Addable> {
  T operator+(const T &other) { return T(this->get().get() + other.get()); }
};

template <typename T>
struct Subable : BasicAbility<T, Subable> {
  T operator-(const T &other) { return T(this->get().get() - other.get()); }
};

template <typename T>
struct Mulable : BasicAbility<T, Mulable> {
  T operator*(const T &other) { return T(this->get().get() * other.get()); }
};

template <typename T>
struct Divable : BasicAbility<T, Divable> {
  T operator/(const T &other) { return T(this->get().get() / other.get()); }
};

template <typename T>
struct Modable : BasicAbility<T, Modable> {
  T operator%(const T &other) { return T(this->get().get() % other.get()); }
};

/**
 * @brief Represnts a generic number.
 * 
 * @tparam T 
 */
template <typename T>
struct Number : Addable<T>, Subable<T>, Mulable<T>, Divable<T>, Modable<T> {};

template <typename T>
struct LeftShiftable : BasicAbility<T, LeftShiftable> {
  T operator<<(const T &other) { return T(this->get().get() << other.get()); }
};

template <typename T>
struct RightShiftable : BasicAbility<T, RightShiftable> {
  T operator>>(const T &other) { return T(this->get().get() >> other.get()); }
};

/**
 * @brief Represnt a type that you can shift left & right
 * 
 * @tparam T 
 */
template <typename T>
struct Shiftable : RightShiftable<T>, LeftShiftable<T> {};

template <typename T>
struct Orable : BasicAbility<T, Orable> {
  T operator|(const T &other) { return T(this->get().get() | other.get()); }
};

template <typename T>
struct Andable : BasicAbility<T, Andable> {
  T operator&(const T &other) { return T(this->get().get() & other.get()); }
};

template <typename T>
struct Xorable : BasicAbility<T, Orable> {
  T operator^(const T &other) { return T(this->get().get() ^ other.get()); }
};

template <typename T>
struct Logic : Orable<T>, Andable<T>, Xorable<T> {};

/**
 * @brief Represent a binary integer number (e. g. like an int)
 * 
 * @tparam T 
 */
template <typename T>
struct BinaryNumber : Number<T>, Shiftable<T>, Logic<T> {};

}  // namespace lr6

#endif  // LR6_COMMON_SKILLS_H_