#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::vector<int> v;
  v.push_back(1);

  std::vector<int>::iterator       a(v.begin());
  std::vector<int>::const_iterator b(v.end() - 1);

  if (a == b) std::cout << "1111" << std::endl;

  const int* c = NULL;
  int*       d = NULL;
  if (c == d) std::cout << "2222" << std::endl;
}
