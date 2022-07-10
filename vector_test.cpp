#include "test.hpp"

void vector_constructor() {
  // ===========================================================================
  print_testname("constructor");
  NAME_SPACE::vector<int> first;           // empty NAME_SPACE::vector of ints
  NAME_SPACE::vector<int> second(4, 100);  // four ints with value 100
  NAME_SPACE::vector<int> third(second.begin(),
                                second.end());  // iterating through second
  NAME_SPACE::vector<int> fourth(third);        // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int                     myints[] = {16, 2, 77, 29};
  NAME_SPACE::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

  std::cout << "The contents of fifth are:";
  for (NAME_SPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end();
       ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void vector_copy_operator() {
  // ===========================================================================
  print_testname("copy constructor");
  NAME_SPACE::vector<int> foo(3, 0);
  NAME_SPACE::vector<int> bar(5, 0);

  bar = foo;
  foo = NAME_SPACE::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void vector_iterators() {
  // ===========================================================================
  print_testname("begin() and end()");
  NAME_SPACE::vector<int> myvector;
  for (int i = 1; i <= 5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (NAME_SPACE::vector<int>::iterator it = myvector.begin();
       it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  // ===========================================================================
  print_testname("rbegin() and rend()");
  NAME_SPACE::vector<int> rmyvector(5);  // 5 default-constructed ints

  int i = 0;

  NAME_SPACE::vector<int>::reverse_iterator rit = rmyvector.rbegin();
  for (; rit != rmyvector.rend(); ++rit) *rit = ++i;

  std::cout << "rmyvector contains:";
  for (NAME_SPACE::vector<int>::iterator it = rmyvector.begin();
       it != rmyvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void vector_capacity() {
  // ===========================================================================
  print_testname("size(), max_size(), and capacity()");

  NAME_SPACE::vector<int> myvector;

  // set some content in the vector:
  for (int i = 0; i < 100; i++) myvector.push_back(i);

  std::cout << "size: " << myvector.size() << "\n";
  std::cout << "capacity: " << myvector.capacity() << "\n";
  std::cout << "max_size: " << myvector.max_size() << "\n";

  // ===========================================================================
  print_testname("resize()");
  NAME_SPACE::vector<int> myvector1;

  // set some initial content:
  for (int i = 1; i < 10; i++) myvector1.push_back(i);

  myvector1.resize(5);
  myvector1.resize(8, 100);
  myvector1.resize(12);

  std::cout << "myvector1 contains:";
  for (int i = 0; i < static_cast<int>(myvector1.size()); i++)
    std::cout << ' ' << myvector1[i];
  std::cout << '\n';

  // ===========================================================================
  print_testname("empty()");
  for (int i = 1; i <= 10; i++) myvector.push_back(i);

  while (!myvector.empty()) myvector.pop_back();

  std::cout << "myvector.empty() is " << (myvector.empty() ? "true" : "false")
            << '\n';
}

void vector_accessors() {
  NAME_SPACE::vector<int> myvector(10);  // 10 zero-initialized elements
  NAME_SPACE::vector<int>::size_type sz = myvector.size();

  // ===========================================================================
  print_testname("operator[]");
  // assign some values:
  for (unsigned i = 0; i < sz; i++) myvector[i] = i;

  // reverse vector using operator[]:
  for (unsigned i = 0; i < sz / 2; i++) {
    int temp;
    temp = myvector[sz - 1 - i];
    myvector[sz - 1 - i] = myvector[i];
    myvector[i] = temp;
  }

  std::cout << "myvector contains:";
  for (unsigned i = 0; i < sz; i++) std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.clear();

  // ===========================================================================
  print_testname("at()");
  for (unsigned i = 0; i < myvector.size(); i++) myvector.at(i) = i;

  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';

  myvector.clear();

  // ===========================================================================
  print_testname("front() and back()");
  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16

  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';
}

void vector_modifiers() {
  // ===========================================================================
  print_testname("assign()");
  NAME_SPACE::vector<int> first;
  NAME_SPACE::vector<int> second;
  NAME_SPACE::vector<int> third;

  first.assign(7, 100);  // 7 ints with a value of 100

  NAME_SPACE::vector<int>::iterator it;
  it = first.begin() + 1;

  second.assign(it, first.end() - 1);  // the 5 central values of first

  int myints[] = {1776, 7, 4};
  third.assign(myints, myints + 3);  // assigning from array.

  std::cout << "Size of first: " << int(first.size()) << '\n';
  std::cout << "Size of second: " << int(second.size()) << '\n';
  std::cout << "Size of third: " << int(third.size()) << '\n';

  // ===========================================================================
  print_testname("push_back() and pop_back()");
  NAME_SPACE::vector<int> myvector;
  for (int i = 10000; i > 0; i--) myvector.push_back(i);

  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

  int sum = 0;

  while (!myvector.empty()) {
    sum += myvector.back();
    myvector.pop_back();
  }

  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
  std::cout << "The elements of myvector add up to " << sum << '\n';

  myvector.clear();

  // ===========================================================================
  print_testname("insert()");

  it = myvector.begin();
  it = myvector.insert(it, 200);

  myvector.insert(it, 2, 300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  NAME_SPACE::vector<int> anothervector(2, 400);
  myvector.insert(it + 2, anothervector.begin(), anothervector.end());

  int myarray[] = {501, 502, 503};
  myvector.insert(myvector.begin(), myarray, myarray + 3);

  std::cout << "myvector contains:";
  for (it = myvector.begin(); it < myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  myvector.clear();

  // ===========================================================================
  print_testname("erase()");
  for (int i = 1; i <= 10; i++) myvector.push_back(i);

  // erase the 6th element
  myvector.erase(myvector.begin() + 5);

  // erase the first 3 elements:
  myvector.erase(myvector.begin(), myvector.begin() + 3);

  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  // ===========================================================================
  print_testname("swap()");
  NAME_SPACE::vector<int> foo(3, 100);  // three ints with a value of 100
  NAME_SPACE::vector<int> bar(5, 200);  // five ints with a value of 200

  foo.swap(bar);

  std::cout << "foo contains:";
  for (unsigned i = 0; i < foo.size(); i++) std::cout << ' ' << foo[i];
  std::cout << '\n';

  std::cout << "bar contains:";
  for (unsigned i = 0; i < bar.size(); i++) std::cout << ' ' << bar[i];
  std::cout << '\n';

  myvector.clear();

  // ===========================================================================
  print_testname("clear()");
  myvector.push_back(100);
  myvector.push_back(200);
  myvector.push_back(300);

  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.clear();
  myvector.push_back(1101);
  myvector.push_back(2202);

  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

void vector_allocator() {
  // ===========================================================================
  print_testname("get_allocator()");
  NAME_SPACE::vector<int> myvector;
  int*                    p;
  unsigned int            i;

  // allocate an array with space for 5 elements using vector's allocator:
  p = myvector.get_allocator().allocate(5);

  // construct values in-place on the array:
  for (i = 0; i < 5; i++) myvector.get_allocator().construct(&p[i], i);

  std::cout << "The allocated array contains:";
  for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

  // destroy and deallocate:
  for (i = 0; i < 5; i++) myvector.get_allocator().destroy(&p[i]);
  myvector.get_allocator().deallocate(p, 5);
}

void vector_test() {
  print_container_name("VECTOR");
  vector_constructor();
  vector_iterators();
  vector_capacity();
  vector_accessors();
  vector_modifiers();
  vector_allocator();
}
