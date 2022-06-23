#include <iostream>

#include "vector.hpp"

int main() {
  ft::vector<int, std::allocator<int> > v;
  v.push_back(1);
  std::cout << *(v.begin()) << std::endl;
}