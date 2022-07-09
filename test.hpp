#pragma once

#if defined(STD)
#include <map>
#include <set>
#include <stack>
#include <vector>
using namespace std;
#else
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "vector.hpp"
using namespace ft;
#endif

#include <ctime>
#include <iostream>

void vector_test();
void map_test();
void stack_test();
void set_test();
void util_test();
