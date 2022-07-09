#pragma once

#include "algorithm.hpp"
#include "rbtree.hpp"

namespace ft {
template <typename _Key, typename _Compare = std::less<_Key>,
          typename _Alloc = std::allocator<_Key> >
class set {
  typedef _Key     key_type;
  typedef _Key     value_type;
  typedef _Compare key_compare;
  typedef _Compare value_compare;

 private:
  template <typename _T>
  struct _Identity : public std::unary_function<_T, _T> {
    _T&       operator()(_T& __x) const { return __x; }
    const _T& operator()(const _T& __x) const { return __x; }
  };

  typedef _Rb_tree<key_type, value_type, _Identity<value_type>, key_compare,
                   _Alloc>
            _Rep_type;
  _Rep_type _M_t;

 public:
  typedef typename _Rep_type::const_pointer          pointer;
  typedef typename _Rep_type::const_pointer          const_pointer;
  typedef typename _Rep_type::const_reference        reference;
  typedef typename _Rep_type::const_reference        const_reference;
  typedef typename _Rep_type::const_iterator         iterator;
  typedef typename _Rep_type::const_iterator         const_iterator;
  typedef typename _Rep_type::const_reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;
  typedef typename _Rep_type::size_type              size_type;
  typedef typename _Rep_type::difference_type        difference_type;
  typedef typename _Rep_type::allocator_type         allocator_type;

  explicit set(const _Compare&       __comp = _Compare(),
               const allocator_type& __a = allocator_type())
      : _M_t(__comp, __a) {}
  template <class _InputIterator>
  set(_InputIterator __first, _InputIterator __last,
      const _Compare&       __comp = _Compare(),
      const allocator_type& __a = allocator_type())
      : _M_t(__comp, __a) {
    _M_t.insert_unique(__first, __last);
  }
  set(const set& __x) : _M_t(__x._M_t) {}

  set& operator=(const set& __x) {
    _M_t = __x._M_t;
    return *this;
  }

  iterator               begin() { return _M_t.begin(); }
  const_iterator         begin() const { return _M_t.begin(); }
  iterator               end() { return _M_t.end(); }
  const_iterator         end() const { return _M_t.end(); }
  reverse_iterator       rbegin() { return _M_t.rbegin(); }
  const_reverse_iterator rbegin() const { return _M_t.rbegin(); }
  reverse_iterator       rend() { return _M_t.rend(); }
  const_reverse_iterator rend() const { return _M_t.rend(); }

  bool      empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }
  size_type max_size() const { return _M_t.max_size(); }

  ft::pair<iterator, bool> insert(const value_type& __x) {
    return _M_t.insert_unique_each(__x);
  }
  iterator insert(iterator __position, const value_type& __x) {
    return _M_t.insert_unique((typename _Rep_type::iterator&)__position, __x);
  }
  template <class _InputIterator>
  void insert(_InputIterator __first, _InputIterator __last) {
    _M_t.insert_unique(__first, __last);
  }

  void erase(iterator __position) {
    typedef typename _Rep_type::iterator _Rep_iterator;
    _M_t.erase((_Rep_iterator&)__position);
  }
  size_type erase(const value_type& __x) { return _M_t.erase(__x); }
  void      erase(iterator __first, iterator __last) {
         typedef typename _Rep_type::iterator _Rep_iterator;
         _M_t.erase((_Rep_iterator&)__first, (_Rep_iterator&)__last);
  }
  void swap(set& __x) { _M_t.swap(__x._M_t); }
  void clear() { _M_t.clear(); }

  key_compare   key_comp() const { return _M_t.key_comp(); }
  value_compare value_comp() const { return _M_t.key_comp(); }

  iterator  find(const key_type& __x) const { return _M_t.find(__x); }
  size_type count(const value_type& __x) const { return _M_t.count(__x); }
  iterator  lower_bound(const key_type& __x) const {
     return _M_t.lower_bound(__x);
  }
  iterator upper_bound(const key_type& __x) const {
    return _M_t.upper_bound(__x);
  }
  ft::pair<iterator, iterator> equal_range(const key_type& __x) const {
    return _M_t.equal_range(__x);
  }

  allocator_type get_allocator() const { return _M_t.get_allocator(); }

  template <typename _Key1, typename _Compare1, typename _Alloc1>
  friend bool operator==(const set<_Key1, _Compare1, _Alloc1>&,
                         const set<_Key1, _Compare1, _Alloc1>&);
  template <typename _Key1, typename _Compare1, typename _Alloc1>
  friend bool operator<(const set<_Key1, _Compare1, _Alloc1>&,
                        const set<_Key1, _Compare1, _Alloc1>&);
};

template <typename _Key, typename _Compare, typename _Alloc>
bool operator==(const set<_Key, _Compare, _Alloc>& __x,
                const set<_Key, _Compare, _Alloc>& __y) {
  return __x._M_t == __y._M_t;
}

template <typename _Key, typename _Compare, typename _Alloc>
bool operator!=(const set<_Key, _Compare, _Alloc>& __x,
                const set<_Key, _Compare, _Alloc>& __y) {
  return !(__x == __y);
}

template <typename _Key, typename _Compare, typename _Alloc>
bool operator<(const set<_Key, _Compare, _Alloc>& __x,
               const set<_Key, _Compare, _Alloc>& __y) {
  return __x._M_t < __y._M_t;
}

template <typename _Key, typename _Compare, typename _Alloc>
bool operator>(const set<_Key, _Compare, _Alloc>& __x,
               const set<_Key, _Compare, _Alloc>& __y) {
  return __y < __x;
}

template <typename _Key, typename _Compare, typename _Alloc>
bool operator<=(const set<_Key, _Compare, _Alloc>& __x,
                const set<_Key, _Compare, _Alloc>& __y) {
  return !(__x > __y);
}

template <typename _Key, typename _Compare, typename _Alloc>
bool operator>=(const set<_Key, _Compare, _Alloc>& __x,
                const set<_Key, _Compare, _Alloc>& __y) {
  return !(__x < __y);
}

template <typename _Key, typename _Compare, typename _Alloc>
void swap(set<_Key, _Compare, _Alloc>& __x, set<_Key, _Compare, _Alloc>& __y) {
  __x.swap(__y);
}

}  // namespace ft
