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
      __end_cap_alloc_type_(__default_init_tag()) {}

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base(const allocator_type &__a)
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

template <class _T, class _Allocator>
class vector : private __vector_base<_T, _Allocator> {
 private:
  typedef __vector_base<_T, _Allocator> _base;
  typedef vector<_T, _Allocator>        vector_type;

  iterator       __make_iter(pointer __p) { return iterator(__p); }
  const_iterator __make_iter(const_pointer __p) { return const_iterator(__p); }

 public:
  typedef _T                                            value_type;
  typedef value_type                                   *pointer;
  typedef const value_type                             *const_pointer;
  typedef __normal_iterator<pointer, vector_type>       iterator;
  typedef __normal_iterator<const_pointer, vector_type> const_iterator;
  typedef value_type                                   &reference;
  typedef const value_type                             &const_reference;
  typedef size_t                                        size_type;
  typedef ptrdiff_t                                     difference_type;
  typedef typename _base::allocator_type                allocator_type;
  typedef reverse_iterator<const_iterator>              const_reverse_iterator;
  typedef reverse_iterator<iterator>                    reverse_iterator;

  explicit vector(const allocator_type &alloc = allocator_type());
  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type());
  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type());
  vector(const vector &x);

  ~vector();

  vector &operator=(const vector &x);

  iterator       begin();
  const_iterator begin() const;
  iterator       end();
  const_iterator end() const;

  reverse_iterator       rbegin();
  const_reverse_iterator rbegin() const;
  reverse_iterator       rend();
  const_reverse_iterator rend() const;

  size_type size() const;
  void      resize(size_type n, value_type val = value_type());
  size_type max_size() const;
  size_type capacity() const;
  bool      empty() const;
  void      reserve(size_type n);

  reference       operator[](size_type n);
  const_reference operator[](size_type n) const;
  reference       at(size_type n);
  const_reference at(size_type n) const;

  reference       front();
  const_reference front() const;
  reference       back();
  const_reference back() const;

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
  void     clear() noexcept;

  allocator_type get_allocator() const { return _base::__alloc(); }
};

}  // namespace ft

#endif  // VECTOR_HPP
