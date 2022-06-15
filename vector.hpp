#if !defined(VECTOR_HPP)
#define VECTOR_HPP

#include <cstddef>
#include <memory>

#include "iterator.hpp"

#define _NOEXECPT throw()

namespace ft {

// vector_base
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

  pointer        __begin_;
  pointer        __end_;
  pointer        __end_cap_pointer_;
  allocator_type __end_cap_alloc_type_;

  __vector_base() _NOEXCEPT;
  __vector_base(const allocator_type& __a);
  ~__vector_base();

  allocator_type&       __alloc() _NOEXCEPT { return __end_cap_alloc_type_; }
  const allocator_type& __alloc() const _NOEXCEPT {
    return __end_cap_alloc_type_;
  }
  size_type capacity() const _NOEXCEPT {
    return static_cast<size_type>(__end_cap_pointer_ - __begin_);
  }
  void clear() _NOEXCEPT {
    pointer __tmp_end = __end_;
    while (__begin_ != __tmp_end)
      __alloc_traits::destroy(__alloc(), _VSTD::__to_address(--__tmp_end));
    __end_ = __begin_;
  }
};

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base() _NOEXCEPT
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_pointer_(nullptr),
      __end_cap_alloc_type_(__default_init_tag()) {}

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base(const allocator_type& __a)
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_pointer_(nullptr),
      __end_cap_alloc_type_(__a) {}

template <class _T, class _Allocator>
__vector_base<_T, _Allocator>::~__vector_base() {
  if (__begin_ != nullptr) {
    clear();
    __alloc_traits::deallocate(__alloc(), __begin_, capacity());
  }
}

}  // namespace ft

#endif  // VECTOR_HPP
