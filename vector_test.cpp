#include "vector.hpp"

#include <iostream>

int main() {
  ft::vector<int, std::allocator<int> > v;
  v.push_back(1);
  std::cout << *(v.begin()) << std::endl;

  ft::vector<int, std::allocator<int> > first;
  ft::vector<int, std::allocator<int> > second;
  ft::vector<int, std::allocator<int> > third;

  first.assign(7, 100);  // 7 ints with a value of 100

  ft::vector<int, std::allocator<int> >::iterator it;
  it = first.begin() + 1;

  second.assign(it, first.end() - 1);  // the 5 central values of first

  int myInts[] = {1776, 7, 4};
  third.assign(myInts, myInts + 3);  // assigning from array.

  std::cout << "Size of first: " << int(first.size()) << '\n';
  std::cout << "Size of second: " << int(second.size()) << '\n';
  std::cout << "Size of third: " << int(third.size()) << '\n';
}