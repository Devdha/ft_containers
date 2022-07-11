#include "test.hpp"

bool fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp {
  bool operator()(const int& lhs, const int& rhs) const { return lhs < rhs; }
};

void set_constructor() {
  // ===========================================================================
  print_testname("constructor");

  NAME_SPACE::set<int> first;  // empty set of ints

  int                  myints[] = {10, 20, 30, 40, 50};
  NAME_SPACE::set<int> second(myints, myints + 5);  // range

  NAME_SPACE::set<int> third(second);  // a copy of second

  NAME_SPACE::set<int> fourth(second.begin(), second.end());  // iterator ctor.

  NAME_SPACE::set<int, classcomp> fifth;  // class as Compare

  bool (*fn_pt)(int, int) = fncomp;
  NAME_SPACE::set<int, bool (*)(int, int)> sixth(
      fn_pt);  // function pointer as Compare
}

void set_copy_operator() {
  // ===========================================================================
  print_testname("copy operator");

  int                  myints[] = {12, 82, 37, 64, 15};
  NAME_SPACE::set<int> first(myints, myints + 5);  // set with 5 ints
  NAME_SPACE::set<int> second;                     // empty set

  second = first;                  // now second contains the 5 ints
  first = NAME_SPACE::set<int>();  // and first is empty

  std::cout << "Size of first: " << int(first.size()) << '\n';
  std::cout << "Size of second: " << int(second.size()) << '\n';
}

void set_iterators() {
  // ===========================================================================
  print_testname("begin() and end()");

  int                  myints[] = {75, 23, 65, 42, 13};
  NAME_SPACE::set<int> myset(myints, myints + 5);

  std::cout << "myset contains:";
  for (NAME_SPACE::set<int>::iterator it = myset.begin(); it != myset.end();
       ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  NAME_SPACE::set<int>::reverse_iterator rit;

  std::cout << "myset contains:";
  for (rit = myset.rbegin(); rit != myset.rend(); ++rit)
    std::cout << ' ' << *rit;

  std::cout << '\n';

  // ===========================================================================
  print_testname("rbegin() and rend()");
}

void set_capacity() {
  // ===========================================================================
  print_testname("empty()");

  NAME_SPACE::set<int> myset;

  myset.insert(20);
  myset.insert(30);
  myset.insert(10);

  std::cout << "myset contains:";
  while (!myset.empty()) {
    std::cout << ' ' << *myset.begin();
    myset.erase(myset.begin());
  }
  std::cout << '\n';

  // ===========================================================================
  print_testname("size()");

  NAME_SPACE::set<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i = 0; i < 10; ++i) myints.insert(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.insert(100);
  std::cout << "2. size: " << myints.size() << '\n';

  myints.erase(5);
  std::cout << "3. size: " << myints.size() << '\n';

  // ===========================================================================
  print_testname("max_size()");

  if (myset.max_size() > 1000) {
    for (int i = 0; i < 1000; i++) myset.insert(i);
    std::cout << "The set contains 1000 elements.\n";
  } else
    std::cout << "The set could not hold 1000 elements.\n";
}

void set_modifiers() {
  // ===========================================================================
  print_testname("insert()");

  NAME_SPACE::set<int>                                   myset;
  NAME_SPACE::set<int>::iterator                         it;
  NAME_SPACE::pair<NAME_SPACE::set<int>::iterator, bool> ret;

  // set some initial values:
  for (int i = 1; i <= 5; ++i) myset.insert(i * 10);  // set: 10 20 30 40 50

  ret = myset.insert(20);  // no new element inserted

  if (ret.second == false) it = ret.first;  // "it" now points to element 20

  myset.insert(it, 25);  // max efficiency inserting
  myset.insert(it, 24);  // max efficiency inserting
  myset.insert(it, 26);  // no max efficiency inserting

  int myints0[] = {5, 10, 15};  // 10 already in set, not inserted
  myset.insert(myints0, myints0 + 3);

  std::cout << "myset contains:";
  for (it = myset.begin(); it != myset.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';

  myset.clear();

  // ===========================================================================
  print_testname("erase()");

  for (int i = 1; i < 10; i++)
    myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90

  it = myset.begin();
  ++it;  // "it" points now to 20

  myset.erase(it);

  myset.erase(40);

  it = myset.find(60);
  myset.erase(it, myset.end());

  std::cout << "myset contains:";
  for (it = myset.begin(); it != myset.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';

  // ===========================================================================
  print_testname("swap()");

  int                  myints[] = {12, 75, 10, 32, 20, 25};
  NAME_SPACE::set<int> first(myints, myints + 3);       // 10,12,75
  NAME_SPACE::set<int> second(myints + 3, myints + 6);  // 20,25,32

  first.swap(second);

  std::cout << "first contains:";
  for (NAME_SPACE::set<int>::iterator it = first.begin(); it != first.end();
       ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "second contains:";
  for (NAME_SPACE::set<int>::iterator it = second.begin(); it != second.end();
       ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  // ===========================================================================
  print_testname("clear()");

  myset.insert(100);
  myset.insert(200);
  myset.insert(300);

  std::cout << "myset contains:";
  for (NAME_SPACE::set<int>::iterator it = myset.begin(); it != myset.end();
       ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  myset.clear();
  myset.insert(1101);
  myset.insert(2202);

  std::cout << "myset contains:";
  for (NAME_SPACE::set<int>::iterator it = myset.begin(); it != myset.end();
       ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}
void set_observers() {
  // ===========================================================================
  print_testname("key_comp()");

  NAME_SPACE::set<int> myset;
  int                  highest;

  NAME_SPACE::set<int>::key_compare key_comp = myset.key_comp();

  for (int i = 0; i <= 5; i++) myset.insert(i);

  std::cout << "myset contains:";

  highest = *myset.rbegin();
  NAME_SPACE::set<int>::iterator it = myset.begin();
  do {
    std::cout << ' ' << *it;
  } while (key_comp(*(++it), highest));

  std::cout << '\n';
  myset.clear();

  // ===========================================================================
  print_testname("value_comp()");

  NAME_SPACE::set<int>::value_compare value_comp = myset.value_comp();

  for (int i = 0; i <= 5; i++) myset.insert(i);

  std::cout << "myset contains:";

  int val_highest = *myset.rbegin();
  it = myset.begin();
  do {
    std::cout << ' ' << *it;
  } while (value_comp(*(++it), val_highest));

  std::cout << '\n';
}

void set_operations() {
  // ===========================================================================
  print_testname("find()");
  NAME_SPACE::set<int>           myset;
  NAME_SPACE::set<int>::iterator it;

  // set some initial values:
  for (int i = 1; i <= 5; i++) myset.insert(i * 10);  // set: 10 20 30 40 50

  it = myset.find(20);
  myset.erase(it);
  myset.erase(myset.find(40));

  std::cout << "myset contains:";
  for (it = myset.begin(); it != myset.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';

  myset.clear();

  // ===========================================================================
  print_testname("count()");

  for (int i = 1; i < 5; ++i) myset.insert(i * 3);  // set: 3 6 9 12

  for (int i = 0; i < 10; ++i) {
    std::cout << i;
    if (myset.count(i) != 0)
      std::cout << " is an element of myset.\n";
    else
      std::cout << " is not an element of myset.\n";
  }

  // ===========================================================================
  print_testname("lower_bound() and upper_bound()");

  NAME_SPACE::set<int>::iterator itlow, itup;

  for (int i = 1; i < 10; i++)
    myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90

  itlow = myset.lower_bound(30);  //       ^
  itup = myset.upper_bound(60);   //                   ^

  myset.erase(itlow, itup);  // 10 20 70 80 90

  std::cout << "myset contains:";
  for (NAME_SPACE::set<int>::iterator it = myset.begin(); it != myset.end();
       ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  // ===========================================================================
  print_testname("equal_range()");

  NAME_SPACE::pair<NAME_SPACE::set<int>::const_iterator,
                   NAME_SPACE::set<int>::const_iterator>
      ret;
  ret = myset.equal_range(30);

  std::cout << "the lower bound points to: " << *ret.first << '\n';
  std::cout << "the upper bound points to: " << *ret.second << '\n';
}

void set_allocator() {
  // ===========================================================================
  print_testname("get_allocator()");

  NAME_SPACE::set<int> myset;
  int*                 p;
  unsigned int         i;

  // allocate an array of 5 elements using myset's allocator:
  p = myset.get_allocator().allocate(5);

  // assign some values to array
  for (i = 0; i < 5; i++) p[i] = (i + 1) * 10;

  std::cout << "The allocated array contains:";
  for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

  myset.get_allocator().deallocate(p, 5);
}

void set_test() {
  print_container_name("SET");
  set_constructor();
  set_copy_operator();
  set_iterators();
  set_capacity();
  set_modifiers();
  set_observers();
  set_operations();
  set_allocator();
}