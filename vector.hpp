#if !defined(VECTOR_HPP)
#define VECTOR_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>

#include "iterator.hpp"

#define _NOEXECPT throw()

namespace ft {

// vector_base
template <typename _T, typename _Allocator>
class __vector_base {
 public:
  typedef _Allocator                            allocator_type;
  typedef std::allocator_traits<allocator_type> __alloc_traits;
  typedef typename __alloc_traits::size_type    size_type;

 protected:
  typedef _T                                       value_type;
  typedef value_type                              &reference;
  typedef const value_type                        &const_reference;
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
  __vector_base(const allocator_type &__a);
  __vector_base(size_t __n, const allocator_type &__a);
  ~__vector_base();

  allocator_type       &__alloc() _NOEXCEPT { return __end_cap_alloc_type_; }
  const allocator_type &__alloc() const _NOEXCEPT {
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
      __end_cap_alloc_type_(std::__default_init_tag()) {}

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base(const allocator_type &__a)
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_pointer_(nullptr),
      __end_cap_alloc_type_(__a) {}

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base(size_t                __n,
                                             const allocator_type &__a) {
  __begin_ = __alloc_traits::allocator(__n);
  __end_ = __begin_;
  __end_cap_pointer_ = __begin_ + __n;
  __end_cap_alloc_type_ = __a;
}

template <class _T, class _Allocator>
__vector_base<_T, _Allocator>::~__vector_base() {
  if (__begin_ != nullptr) {
    clear();
    __alloc_traits::deallocate(__alloc(), __begin_, capacity());
  }
}

/* ####################################################
#########               vector             ############
#################################################### */

template <class _T, class _Allocator>
class vector : private __vector_base<_T, _Allocator> {
 private:
  typedef __vector_base<_T, _Allocator> _base;
  typedef vector<_T, _Allocator>        vector_type;

 protected:
  using _base::__begin_;
  using _base::__end_;
  using _base::__end_cap_alloc_type_;
  using _base::__end_cap_pointer_;

 public:
  typedef _T                               value_type;
  typedef value_type                      *pointer;
  typedef const value_type                *const_pointer;
  typedef _T                              *iterator;
  typedef const _T                        *const_iterator;
  typedef value_type                      &reference;
  typedef const value_type                &const_reference;
  typedef size_t                           size_type;
  typedef ptrdiff_t                        difference_type;
  typedef typename _base::allocator_type   allocator_type;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator>       reverse_iterator;

 private:
  iterator       __make_iter(pointer __p) { return iterator(__p); }
  const_iterator __make_iter(const_pointer __p) const {
    return const_iterator(__p);
  }
  void __range_check(size_type __n) const {
    if (__n >= this->size()) std::__throw_out_of_range("vector");
  }

 public:
  explicit vector(const allocator_type &__a = allocator_type()) : _base(__a) {}

  explicit vector(size_type __n, const _T &__value,
                  const allocator_type &__a = allocator_type())
      : _base(__n, __a) {
    __end_ = uninitialized_fill_n(__begin_, __n, __value);
  }

  template <class InputIterator>
  vector(InputIterator __first, InputIterator __last,
         const allocator_type &__a = allocator_type())
      : _base(__a) {
    size_type __n = distance(__first, __last);
    __begin_ = _base::__alloc_traits::allocator(__n);
    __end_ = __begin_ + __n;
    __end_cap_pointer_ = __begin_ + __n;
    for (; __first != __last; ++__first) push_back(*__first);
  }

  vector(const vector<_T, _Allocator> &__x)
      : _base(__x.size(), __x.get_allocator()) {
    __end_ = uninitialized_copy(__x.begin(), __x.end(), __begin_);
  }

  ~vector() {
    if (this->__begin_) {
      clear();
      __end_cap_alloc_type_.deallocate(__begin_, this->capacity());
      __begin_ = __end_ = __end_cap_pointer_ = NULL;
    }
  }

  vector &operator=(const vector &__x) {
    if (&__x != this) {
      const size_type __xlen = __x.size();
      if (__xlen > capacity()) {
      }
    }
  }

  iterator       begin() { return __make_iter(this->__begin_); }
  const_iterator begin() const { return __make_iter(this->__begin_); }
  iterator       end() { return __make_iter(this->__end_); }
  const_iterator end() const { return __make_iter(this->__end_); }

  reverse_iterator       rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator       rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  size_type size() const { return size_type(end() - begin()); }
  void      resize(size_type n, value_type val = value_type());
  size_type max_size() const { return size_type(-1) / sizeof(_T); }
  size_type capacity() const {
    return size_type(const_iterator(__end_cap_pointer_ - begin()));
  }
  bool empty() const { return begin() == end(); }
  void reserve(size_type n);

  reference operator[](size_type __n) {
    if (__n >= size()) this->__throw_out_of_range();
    return this->__begin_[__n];
  }
  const_reference operator[](size_type __n) const {
    return this->__begin_[__n];
  }
  reference at(size_type __n) {
    __range_check(__n);
    return (*this)[__n];
  }
  const_reference at(size_type __n) const {
    __range_check(__n);
    return (*this)[__n];
  }

  reference       front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference       back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }

  template <class InputIterator>
  void assign(InputIterator first, InputIterator last);
  void assign(size_type n, const value_type &val);
  void push_back(const value_type &val);
  template <class InputIterator>
  void     insert(iterator position, InputIterator first, InputIterator last);
  iterator insert(iterator position, const value_type &val);
  void     insert(iterator position, size_type n, const value_type &val);
  iterator erase(const_iterator position);
  iterator erase(const_iterator first, const_iterator last);
  void     swap(vector &x);
  void     clear() throw() {}

  allocator_type get_allocator() const { return _base::__alloc(); }
};

}  // namespace ft

#endif  // VECTOR_HPP
