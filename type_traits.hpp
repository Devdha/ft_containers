#pragma once

namespace ft {

template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

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
struct is_integral {
  typedef __false_type _Integral;
};

template <>
struct is_integral<bool> {
  typedef __true_type _Integral;
};

template <>
struct is_integral<char> {
  typedef __true_type _Integral;
};

template <>
struct is_integral<signed char> {
  typedef __true_type _Integral;
};

template <>
struct is_integral<unsigned char> {
  typedef __true_type _Integral;
};

template <>
struct is_integral<wchar_t> {
  typedef __true_type _Integral;
};

template <>
struct is_integral<short> {
  typedef __true_type _Integral;
};

template <>
struct is_integral<unsigned short> {
  typedef __true_type _Integral;
};

template <>
struct is_integral<int> {
  typedef __true_type _Integral;
};

template <>
struct is_integral<unsigned int> {
  typedef __true_type _Integral;
};

template <>
struct is_integral<long> {
  typedef __true_type _Integral;
};

template <>
struct is_integral<unsigned long> {
  typedef __true_type _Integral;
};

}  // namespace ft
