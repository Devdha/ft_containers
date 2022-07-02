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
};

#endif  // MAP_HPP
