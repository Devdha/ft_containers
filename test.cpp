#include <iostream>

void print_container_name(const char* container_name) {
  std::cout << "\n\n::" << container_name << "::\n" << std::endl;
}

void print_testname(const char* testname) {
  std::cout << "\n=============================================" << std::endl;
  std::cout << "Test: " << testname << std::endl << std::endl;
}