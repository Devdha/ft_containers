#if !defined(MAP_HPP)
#define MAP_HPP

#include "rbtree.hpp"

template <typename _Key, typename _T, typename _Compare = std::less<_Key>,
          typename _Alloc = std::allocator<ft::pair<const _Key, _T> > >
class map {
 public:
  typedef _Key                     key_type;
  typedef _T                       mapped_type;
  typedef ft::pair<const _Key, _T> value_type;
  typedef _Compare                 key_compare;

 private:
  typedef ft::_Rb_tree<key_type, value_type, typename value_type::first_type,
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
    _M_t._M_insert_unique(__first, __last);
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
    return _M_t._M_insert(_M_t._M_begin(), __k, mapped_type()).first->second;
  }
};

#endif  // MAP_HPP
