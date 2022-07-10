#pragma once

#if defined(STD)
#include <map>
#include <set>
#include <stack>
#include <vector>
#define NAME_SPACE std
#else
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "vector.hpp"
#define NAME_SPACE ft
#endif

#include <ctime>
#include <iostream>

void print_testname(const char* testname);

void vector_test();
void map_test();
void stack_test();
void set_test();
void util_test();
