#pragma once

namespace ft {

template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

template <typename T, T v>
struct integral_constant {
  typedef integral_constant<T, v> type;
  typedef T                       value_type;
  static const T                  value = v;
                                  operator value_type() const { return value; }
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <typename T>
struct _is_integral : public false_type {};
template <>
struct _is_integral<bool> : public true_type {};
template <>
struct _is_integral<char> : public true_type {};
template <>
struct _is_integral<unsigned char> : public true_type {};
template <>
struct _is_integral<signed char> : public true_type {};
template <>
struct _is_integral<wchar_t> : public true_type {};
template <>
struct _is_integral<short> : public true_type {};
template <>
struct _is_integral<unsigned short> : public true_type {};
template <>
struct _is_integral<int> : public true_type {};
template <>
struct _is_integral<unsigned int> : public true_type {};
template <>
struct _is_integral<long> : public true_type {};
template <>
struct _is_integral<unsigned long> : public true_type {};

struct __true_type {};
struct __false_type {};

template <class _T>
struct __type_traits {
  typedef __true_type  this_dummy_member_must_be_first;
  typedef __false_type has_trivial_default_constructor;
  typedef __false_type has_trivial_copy_constructor;
  typedef __false_type has_trivial_assignment_operator;
  typedef __false_type has_trivial_destructor;
  typedef __false_type is_POD_type;
};

template <>
struct __type_traits<bool> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<char> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<signed char> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<unsigned char> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<wchar_t> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<short> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<unsigned short> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<int> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<unsigned int> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<long> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<unsigned long> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<float> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<double> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <>
struct __type_traits<long double> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <class _T>
struct __type_traits<_T*> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};

template <class _T>
struct is_integer {
  typedef __false_type _Integral;
};

template <>
struct is_integer<bool> {
  typedef __true_type _Integral;
};

template <>
struct is_integer<char> {
  typedef __true_type _Integral;
};

template <>
struct is_integer<signed char> {
  typedef __true_type _Integral;
};

template <>
struct is_integer<unsigned char> {
  typedef __true_type _Integral;
};

template <>
struct is_integer<wchar_t> {
  typedef __true_type _Integral;
};

template <>
struct is_integer<short> {
  typedef __true_type _Integral;
};

template <>
struct is_integer<unsigned short> {
  typedef __true_type _Integral;
};

template <>
struct is_integer<int> {
  typedef __true_type _Integral;
};

template <>
struct is_integer<unsigned int> {
  typedef __true_type _Integral;
};

template <>
struct is_integer<long> {
  typedef __true_type _Integral;
};

template <>
struct is_integer<unsigned long> {
  typedef __true_type _Integral;
};

}  // namespace ft
