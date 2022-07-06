#if !defined(SET_HPP)
#define SET_HPP

#include "rbtree.hpp"

namespace ft {
template <class _Key, class _Compare = std::less<_Key>,
          class _Alloc = std::allocator<_Key> >
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

  _Rb_tree<key_type, value_type, _Identity<value_type>, key_compare,
           allocator_type>
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
};

}  // namespace ft

#endif  // SET_HPP