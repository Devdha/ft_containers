#if !defined(VECTOR_HPP)
#define VECTOR_HPP

#include <cstddef>
#include <memory>

#include "iterator.hpp"

namespace ft {

template <typename _T, typename _Allocator>
class __vector_base {
 public:
  typedef _Allocator                         allocator_type;
  typedef allocator_traits<allocator_type>   __alloc_traits;
  typedef typename __alloc_traits::size_type size_type;

 protected:
  typedef _T                                       value_type;
  typedef value_type&                              reference;
  typedef const value_type&                        const_reference;
  typedef typename __alloc_traits::difference_type difference_type;
  typedef typename __alloc_traits::pointer         pointer;
  typedef typename __alloc_traits::const_pointer   const_pointer;
  typedef pointer                                  iterator;
  typedef const_pointer                            const_iterator;

  pointer                                    __begin_;
  pointer                                    __end_;
  __compressed_pair<pointer, allocator_type> __end_cap_;
};
}  // namespace ft

#endif  // VECTOR_HPP
