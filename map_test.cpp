#include "test.hpp"

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp {
  bool operator()(const char& lhs, const char& rhs) const { return lhs < rhs; }
};

void map_constructor() {
  // ===========================================================================
  print_testname("constructor");

  NAME_SPACE::map<char, int> first;

  first['a'] = 10;
  first['b'] = 30;
  first['c'] = 50;
  first['d'] = 70;

  NAME_SPACE::map<char, int> second(first.begin(), first.end());

  NAME_SPACE::map<char, int> third(second);

  NAME_SPACE::map<char, int, classcomp> fourth;  // class as Compare

  bool (*fn_pt)(char, char) = fncomp;
  NAME_SPACE::map<char, int, bool (*)(char, char)> fifth(
      fn_pt);  // function pointer as Compare
  for (int i = 0; i < 4; i++) {
    std::cout << "first: " << first['a' + i] << std::endl;
    std::cout << "second: " << second['a' + i] << std::endl;
    std::cout << "third: " << third['a' + i] << std::endl;
  }
}

void map_copy_operator() {
  // ===========================================================================
  print_testname("copy operator");

  NAME_SPACE::map<char, int> first;
  NAME_SPACE::map<char, int> second;

  first['x'] = 8;
  first['y'] = 16;
  first['z'] = 32;

  second = first;                        // second now contains 3 ints
  first = NAME_SPACE::map<char, int>();  // and first is now empty

  std::cout << "Size of first: " << first.size() << '\n';
  std::cout << "Size of second: " << second.size() << '\n';
}

void map_iterators() {
  // ===========================================================================
  print_testname("begin() and end()");

  NAME_SPACE::map<char, int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (NAME_SPACE::map<char, int>::iterator it = mymap.begin();
       it != mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
  // ===========================================================================
  print_testname("rbegin() and rend()");

  NAME_SPACE::map<char, int>::reverse_iterator rit;
  for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
    std::cout << rit->first << " => " << rit->second << '\n';
}
void map_capacity() {
  // ===========================================================================
  print_testname("empty()");

  NAME_SPACE::map<char, int> mymap;

  mymap['a'] = 10;
  mymap['b'] = 20;
  mymap['c'] = 30;

  while (!mymap.empty()) {
    std::cout << mymap.begin()->first << " => " << mymap.begin()->second
              << '\n';
    mymap.erase(mymap.begin());
  }
  // ===========================================================================
  print_testname("size()");

  mymap['a'] = 101;
  mymap['b'] = 202;
  mymap['c'] = 302;

  std::cout << "mymap.size() is " << mymap.size() << '\n';

  mymap.clear();
  // ===========================================================================
  print_testname("max_size()");

  if (mymap.max_size() > 1000) {
    for (int i = 0; i < 1000; i++) mymap[i] = 0;
    std::cout << "The map contains 1000 elements.\n";
  } else
    std::cout << "The map could not hold 1000 elements.\n";
}

void map_accessors() {
  // ===========================================================================
  print_testname("operator[]");
  NAME_SPACE::map<char, std::string> mymap;

  mymap['a'] = "an element";
  mymap['b'] = "another element";
  mymap['c'] = mymap['b'];

  std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  std::cout << "mymap['d'] is " << mymap['d'] << '\n';

  std::cout << "mymap now contains " << mymap.size() << " elements.\n";
}

void map_modifiers() {
  // ===========================================================================
  print_testname("insert()");

  NAME_SPACE::map<char, int> mymap;

  // first insert function version (single parameter):
  mymap.insert(NAME_SPACE::pair<char, int>('a', 100));
  mymap.insert(NAME_SPACE::pair<char, int>('z', 200));

  NAME_SPACE::pair<NAME_SPACE::map<char, int>::iterator, bool> ret;
  ret = mymap.insert(NAME_SPACE::pair<char, int>('z', 500));
  if (ret.second == false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  // second insert function version (with hint position):
  NAME_SPACE::map<char, int>::iterator it = mymap.begin();
  mymap.insert(
      it, NAME_SPACE::pair<char, int>('b', 300));  // max efficiency inserting
  mymap.insert(it, NAME_SPACE::pair<char, int>(
                       'c', 400));  // no max efficiency inserting

  // third insert function version (range insertion):
  NAME_SPACE::map<char, int> anothermap;
  anothermap.insert(mymap.begin(), mymap.find('c'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it = mymap.begin(); it != mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (it = anothermap.begin(); it != anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  mymap.clear();

  // ===========================================================================
  print_testname("erase()");

  mymap['a'] = 10;
  mymap['b'] = 20;
  mymap['c'] = 30;
  mymap['d'] = 40;
  mymap['e'] = 50;
  mymap['f'] = 60;

  it = mymap.find('b');
  mymap.erase(it);  // erasing by iterator

  mymap.erase('c');  // erasing by key

  it = mymap.find('e');
  mymap.erase(it, mymap.end());  // erasing by range

  // show content:
  for (it = mymap.begin(); it != mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  // ===========================================================================
  print_testname("swap()");

  NAME_SPACE::map<char, int> foo, bar;

  foo['x'] = 100;
  foo['y'] = 200;

  bar['a'] = 11;
  bar['b'] = 22;
  bar['c'] = 33;

  foo.swap(bar);

  std::cout << "foo contains:\n";
  for (NAME_SPACE::map<char, int>::iterator it = foo.begin(); it != foo.end();
       ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (NAME_SPACE::map<char, int>::iterator it = bar.begin(); it != bar.end();
       ++it)
    std::cout << it->first << " => " << it->second << '\n';

  // ===========================================================================
  print_testname("clear()");

  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;

  std::cout << "mymap contains:\n";
  for (NAME_SPACE::map<char, int>::iterator it = mymap.begin();
       it != mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  mymap.clear();
  mymap['a'] = 1101;
  mymap['b'] = 2202;

  std::cout << "mymap contains:\n";
  for (NAME_SPACE::map<char, int>::iterator it = mymap.begin();
       it != mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}

void map_observers() {
  // ===========================================================================
  print_testname("key_comp()");

  NAME_SPACE::map<char, int> mymap;

  NAME_SPACE::map<char, int>::key_compare mycomp = mymap.key_comp();

  mymap['a'] = 100;
  mymap['b'] = 200;
  mymap['c'] = 300;

  std::cout << "mymap contains:\n";

  char highest_key = mymap.rbegin()->first;  // key value of last element

  NAME_SPACE::map<char, int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while (mycomp((*it++).first, highest_key));

  std::cout << '\n';

  mymap.clear();

  // ===========================================================================
  print_testname("value_comp()");

  mymap['x'] = 1001;
  mymap['y'] = 2002;
  mymap['z'] = 3003;

  std::cout << "mymap contains:\n";

  NAME_SPACE::pair<char, int> highest = *mymap.rbegin();  // last element

  it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while (mymap.value_comp()(*it++, highest));
}

void map_operations() {
  // ===========================================================================
  print_testname("find()");

  NAME_SPACE::map<char, int>           mymap;
  NAME_SPACE::map<char, int>::iterator it;

  mymap['a'] = 50;
  mymap['b'] = 100;
  mymap['c'] = 150;
  mymap['d'] = 200;

  it = mymap.find('b');
  if (it != mymap.end()) mymap.erase(it);

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';

  mymap.clear();

  // ===========================================================================
  print_testname("count()");

  char c;

  mymap['a'] = 101;
  mymap['c'] = 202;
  mymap['f'] = 303;

  for (c = 'a'; c < 'h'; c++) {
    std::cout << c;
    if (mymap.count(c) > 0)
      std::cout << " is an element of mymap.\n";
    else
      std::cout << " is not an element of mymap.\n";
  }

  mymap.clear();

  // ===========================================================================
  print_testname("lower_bound() and upper_bound()");

  NAME_SPACE::map<char, int>::iterator itlow, itup;

  mymap['a'] = 20;
  mymap['b'] = 40;
  mymap['c'] = 60;
  mymap['d'] = 80;
  mymap['e'] = 100;

  itlow = mymap.lower_bound('b');  // itlow points to b
  itup = mymap.upper_bound('d');   // itup points to e (not d!)

  mymap.erase(itlow, itup);  // erases [itlow,itup)

  // print content:
  for (NAME_SPACE::map<char, int>::iterator it = mymap.begin();
       it != mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  // ===========================================================================
  print_testname("equal_range()");

  NAME_SPACE::pair<NAME_SPACE::map<char, int>::iterator,
                   NAME_SPACE::map<char, int>::iterator>
      ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

void map_allocator() {
  // ===========================================================================
  print_testname("get_allocator()");

  int                                psize;
  NAME_SPACE::map<char, int>         mymap;
  NAME_SPACE::pair<const char, int>* p;

  // allocate an array of 5 elements using mymap's allocator:
  p = mymap.get_allocator().allocate(5);

  // assign some values to array
  psize = sizeof(NAME_SPACE::map<char, int>::value_type) * 5;

  std::cout << "The allocated array has a size of " << psize << " bytes.\n";

  mymap.get_allocator().deallocate(p, 5);
}

void map_test() {
  print_container_name("MAP");
  map_constructor();
  map_copy_operator();
  map_iterators();
  map_capacity();
  map_accessors();
  map_modifiers();
  map_observers();
  map_operations();
  map_allocator();
}