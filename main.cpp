#include <iostream>

#include "test.hpp"

int main() {
  vector_test();
  map_test();
  set_test();
  stack_test();
  // util_test();

#ifdef STD
  std::cout << "It's STD version" << std::endl;
#else
  std::cout << "It's FT version" << std::endl;
#endif
  // const char *leak_check;

  // #ifdef STD
  //   leak_check = "leaks std";
  // #else
  //   leak_check = "leaks ft";
  // #endif
  //   system(leak_check);
  return (0);
}
