#pragma once

#include "pair.hpp"
#include "rbtree.hpp"

namespace ft {

template <typename _Key, typename _T, typename _Compare = std::less<_Key>,
          typename _Alloc = std::allocator<ft::pair<const _Key, _T> > >
class map {
 public:
  typedef _Key                     key_type;
  typedef _T                       mapped_type;
  typedef ft::pair<const _Key, _T> value_type;
  typedef _Compare                 key_compare;

 private:
  template <class _Pair>
  struct _get_First
      : public std::unary_function<_Pair, typename _Pair::first_type> {
    typename _Pair::first_type& operator()(_Pair& __x) const {
      return __x.first;
    }
    const typename _Pair::first_type& operator()(const _Pair& __x) const {
      return __x.first;
    }
  };

  typedef ft::_Rb_tree<key_type, value_type, _get_First<value_type>,
                       key_compare, _Alloc>
            _Rep_type;
  _Rep_type _M_t;

 public:
  typedef typename _Rep_type::allocator_type         allocator_type;
  typedef typename _Rep_type::reference              reference;
  typedef typename _Rep_type::const_reference        const_reference;
  typedef typename _Rep_type::pointer                pointer;
  typedef typename _Rep_type::const_pointer          const_pointer;
  typedef typename _Rep_type::iterator               iterator;
  typedef typename _Rep_type::const_iterator         const_iterator;
  typedef typename _Rep_type::size_type              size_type;
  typedef typename _Rep_type::difference_type        difference_type;
  typedef typename _Rep_type::reverse_iterator       reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;

  class value_compare {
    friend class map<_Key, _T, _Compare, _Alloc>;

   private:
    _Compare comp;
    value_compare(_Compare __c) : comp(__c) {}

   public:
    bool operator()(const value_type& __x, const value_type& __y) const {
      return comp(__x.first, __y.first);
    }
  };

  explicit map(const key_compare&    __comp = key_compare(),
               const allocator_type& __alloc = allocator_type())
      : _M_t(__comp, __alloc) {}

  template <typename _InputIterator>
  map(_InputIterator __first, _InputIterator __last,
      const key_compare&    __comp = key_compare(),
      const allocator_type& __alloc = allocator_type())
      : _M_t(__comp, __alloc) {
    _M_t.insert_unique(__first, __last);
  }

  map(const map& __x) : _M_t(__x._M_t) {}

  map& operator=(const map& __x) {
    _M_t = __x._M_t;
    return *this;
  }

  iterator       begin() { return _M_t.begin(); }
  const_iterator begin() const { return _M_t.begin(); }
  iterator       end() { return _M_t.end(); }
  const_iterator end() const { return _M_t.end(); }

  reverse_iterator       rbegin() { return _M_t.rbegin(); }
  const_reverse_iterator rbegin() const { return _M_t.rbegin(); }
  reverse_iterator       rend() { return _M_t.rend(); }
  const_reverse_iterator rend() const { return _M_t.rend(); }

  bool      empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }
  size_type max_size() const { return _M_t.max_size(); }

  mapped_type& operator[](const key_type& __k) {
    iterator __i = lower_bound(__k);

    if (__i == end() || key_comp()(__k, (*__i).first))
      __i = this->insert(__i, value_type(__k, mapped_type()));
    return (*__i).second;
  }

  ft::pair<iterator, bool> insert(const value_type& __x) {
    return _M_t.insert_unique_each(__x);
  }
  iterator insert(iterator __pos, const value_type& __x) {
    return _M_t.insert_unique(__pos, __x);
  }
  template <typename _InputIterator>
  void insert(_InputIterator __first, _InputIterator __last) {
    _M_t.insert_unique(__first, __last);
  }

  void      erase(iterator __pos) { _M_t.erase(__pos); }
  size_type erase(const _Key& k) { return _M_t.erase(k); }
  void erase(iterator __first, iterator __last) { _M_t.erase(__first, __last); }

  void swap(map& __x) { _M_t.swap(__x._M_t); }
  void clear() { _M_t.clear(); }

  key_compare   key_comp() const { return _M_t.key_comp(); }
  value_compare value_comp() const { return value_compare(_M_t.key_comp()); }

  iterator       find(const key_type& __k) { return _M_t.find(__k); }
  const_iterator find(const key_type& __k) const { return _M_t.find(__k); }

  size_type count(const key_type& __k) const { return _M_t.count(__k); }

  iterator lower_bound(const key_type& __k) { return _M_t.lower_bound(__k); }
  const_iterator lower_bound(const key_type& __k) const {
    return _M_t.lower_bound(__k);
  }

  iterator upper_bound(const key_type& __k) { return _M_t.upper_bound(__k); }
  const_iterator upper_bound(const key_type& __k) const {
    return _M_t.upper_bound(__k);
  }

  pair<iterator, iterator> equal_range(const key_type& __k) {
    return _M_t.equal_range(__k);
  }
  pair<const_iterator, const_iterator> equal_range(const key_type& __k) const {
    return _M_t.equal_range(__k);
  }

  allocator_type get_allocator() const { return allocator_type(); }

  template <typename _Key1, typename _Val1, typename _Compare1,
            typename _Alloc1>
  friend bool operator==(const map<_Key1, _Val1, _Compare1, _Alloc1>&,
                         const map<_Key1, _Val1, _Compare1, _Alloc1>&);
  template <typename _Key1, typename _Val1, typename _Compare1,
            typename _Alloc1>
  friend bool operator<(const map<_Key1, _Val1, _Compare1, _Alloc1>&,
                        const map<_Key1, _Val1, _Compare1, _Alloc1>&);
};

template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
bool operator==(const map<_Key, _Tp, _Compare, _Alloc>& __x,
                const map<_Key, _Tp, _Compare, _Alloc>& __y) {
  return __x._M_t == __y._M_t;
}

template <typename _Key, typename _Val, typename _Compare, typename _Alloc>
bool operator!=(const map<_Key, _Val, _Compare, _Alloc>& __x,
                const map<_Key, _Val, _Compare, _Alloc>& __y) {
  return !(__x == __y);
}

template <typename _Key, typename _Val, typename _Compare, typename _Alloc>
bool operator<(const map<_Key, _Val, _Compare, _Alloc>& __x,
               const map<_Key, _Val, _Compare, _Alloc>& __y) {
  return __x._M_t < __y._M_t;
}

template <typename _Key, typename _Val, typename _Compare, typename _Alloc>
bool operator>(const map<_Key, _Val, _Compare, _Alloc>& __x,
               const map<_Key, _Val, _Compare, _Alloc>& __y) {
  return __y < __x;
}

template <typename _Key, typename _Val, typename _Compare, typename _Alloc>
bool operator<=(const map<_Key, _Val, _Compare, _Alloc>& __x,
                const map<_Key, _Val, _Compare, _Alloc>& __y) {
  return !(__x > __y);
}

template <typename _Key, typename _Val, typename _Compare, typename _Alloc>
bool operator>=(const map<_Key, _Val, _Compare, _Alloc>& __x,
                const map<_Key, _Val, _Compare, _Alloc>& __y) {
  return !(__x < __y);
}

template <typename _Key, typename _Val, typename _Compare, typename _Alloc>
void swap(map<_Key, _Val, _Compare, _Alloc>& __x,
          map<_Key, _Val, _Compare, _Alloc>& __y) {
  __x.swap(__y);
}

}  // namespace ft
