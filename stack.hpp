#pragma once

#include "vector.hpp"

namespace ft {

template <typename _T, typename _Container = ft::vector<_T> >
class stack {
 private:
  _Container _M_t;

 public:
  typedef typename _Container::value_type      value_type;
  typedef typename _Container::reference       reference;
  typedef typename _Container::const_reference const_reference;
  typedef typename _Container::size_type       size_type;
  typedef _Container                           container_type;

  explicit stack(const container_type& __c = container_type()) : _M_t(__c) {}

  bool      empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }

  value_type&       top() { return _M_t.back(); }
  const value_type& top() const { return _M_t.back(); }

  void push(const value_type& __x) { _M_t.push_back(__x); }
  void pop() { _M_t.pop_back(); }

  template <typename _T1, typename _Container1>
  friend bool operator==(const stack<_T1, _Container1>& __x,
                         const stack<_T1, _Container1>& __y);

  template <typename _T1, typename _Container1>
  friend bool operator<(const stack<_T1, _Container1>& __x,
                        const stack<_T1, _Container1>& __y);
};

template <typename _T, typename _Container>
bool operator==(const stack<_T, _Container>& __x,
                const stack<_T, _Container>& __y) {
  return __x._M_t == __y._M_t;
}

template <typename _T, typename _Container>
bool operator<(const stack<_T, _Container>& __x,
               const stack<_T, _Container>& __y) {
  return __x._M_t < __y._M_t;
}

template <typename _T, typename _Container>
bool operator!=(const stack<_T, _Container>& __x,
                const stack<_T, _Container>& __y) {
  return !(__x == __y);
}

template <typename _T, typename _Container>
bool operator>(const stack<_T, _Container>& __x,
               const stack<_T, _Container>& __y) {
  return __y < __x;
}

template <typename _T, typename _Container>
bool operator>=(const stack<_T, _Container>& __x,
                const stack<_T, _Container>& __y) {
  return !(__x < __y);
}

template <typename _T, typename _Container>
bool operator<=(const stack<_T, _Container>& __x,
                const stack<_T, _Container>& __y) {
  return !(__y < __x);
}

}  // namespace ft
