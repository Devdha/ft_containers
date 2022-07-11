#include <iostream>

#include "test.hpp"

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename ft::enable_if<ft::is_integral<T>::value, bool>::type is_odd(T i) {
  return bool(i % 2);
}

template <class T>
typename ft::enable_if<ft::is_integral<T>::value, bool>::type is_even(T i) {
  return bool(i % 2 == 0);
}

void test_enable_if() {
  short int i = 1;  // code does not compile if type of i is not integral

  std::cout << "i is odd: " << is_odd(i) << std::endl;
  std::cout << "i is even: " << is_even(i) << std::endl;

  // int*      a = NULL;
  // std::cout << "a is odd: " << is_odd(a) << std::endl;
  // std::cout << "a is even: " << is_even(a) << std::endl;
}

void util_test() {
  print_container_name("UTIL");
  test_enable_if();
  //   NAME_SPACE::pair<int, int> p = NAME_SPACE::make_pair(1, 2);
}