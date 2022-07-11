#include "test.hpp"

void stack_constructor() {
  // ===========================================================================
  print_testname("constructor");

#ifdef STD
  NAME_SPACE::deque<int> my_container(2, 200);  // _container with 2 elements
#else
  NAME_SPACE::vector<int> my_container(2, 200);  // _container with 2 elements
#endif

  NAME_SPACE::stack<int> first;  // empty stack
  NAME_SPACE::stack<int> second(my_container);

  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
}

void stack_capacity() {
  // ===========================================================================
  print_testname("empty()");

  NAME_SPACE::stack<int> mystack;
  int                    sum(0);

  for (int i = 1; i <= 10; i++) mystack.push(i);

  while (!mystack.empty()) {
    sum += mystack.top();
    mystack.pop();
  }

  std::cout << "total: " << sum << '\n';

  // ===========================================================================
  print_testname("size()");

  NAME_SPACE::stack<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i = 0; i < 5; i++) myints.push(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.pop();
  std::cout << "2. size: " << myints.size() << '\n';
}

void stack_accessors() {
  // ===========================================================================
  print_testname("top()");

  NAME_SPACE::stack<int> mystack;

  mystack.push(10);
  mystack.push(20);

  mystack.top() -= 5;

  std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

void stack_modifiers() {
  // ===========================================================================
  print_testname("push() and pop()");

  NAME_SPACE::stack<int> mystack;

  for (int i = 0; i < 5; ++i) mystack.push(i);

  std::cout << "Popping out elements...";
  while (!mystack.empty()) {
    std::cout << ' ' << mystack.top();
    mystack.pop();
  }
  std::cout << '\n';
}

void stack_test() {
  stack_constructor();
  stack_capacity();
  stack_accessors();
  stack_modifiers();
}
