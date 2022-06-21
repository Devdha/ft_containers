#if !defined(VECTOR_HPP)
#define VECTOR_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

#define _NOEXECPT throw()

namespace ft {

// ================================================================
// vector_base
// ================================================================
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

// ================================================================
// vector
// ================================================================

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
  typedef _T                                             value_type;
  typedef value_type                                    *pointer;
  typedef const value_type                              *const_pointer;
  typedef __normal_iterator<pointer, vector_type>        iterator;
  typedef __normal_iterator<const_pointer, vector_type> *const_iterator;
  typedef value_type                                    &reference;
  typedef const value_type                              &const_reference;
  typedef size_t                                         size_type;
  typedef ptrdiff_t                                      difference_type;
  typedef typename _base::allocator_type                 allocator_type;
  typedef reverse_iterator<const_iterator>               const_reverse_iterator;
  typedef reverse_iterator<iterator>                     reverse_iterator;

 private:
  void _insert_aux(iterator __position, const _T &__val);
  // ================================================================
  // make iter functions
  iterator       __make_iter(pointer __p) { return iterator(__p); }
  const_iterator __make_iter(const_pointer __p) const {
    return const_iterator(__p);
  }

  // ================================================================
  // range check function
  void __range_check(size_type __n) const;

  template <typename _InputIterator>
  typename iterator_traits<_InputIterator>::difference_type __distance(
      _InputIterator __first, _InputIterator __last) {
    typename iterator_traits<_InputIterator>::difference_type __n = 0;
    while (__first != __last) {
      ++__first;
      ++__n;
    }
    return __n;
  }

  // ================================================================
  // assign_aux functions
  template <class _ForwardIterator>
  void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last,
                     __false_type);
  template <class _ForwardIterator>
  void __destroy_aux(_ForwardIterator, _ForwardIterator, __true_type);
  void _Destroy(pointer *__pointer);
  template <class _ForwardIterator>
  void _Destroy(_ForwardIterator __first, _ForwardIterator __last);

  void _fill_assign(size_t __n, const value_type &__val);
  template <class _InputIter>
  void _assign_aux(_InputIter __first, _InputIter __last, input_iterator_tag);
  template <class _ForwardIterator>
  void _assign_aux(_ForwardIterator __first, _ForwardIterator __last,
                   forward_iterator_tag);
  template <class _Integer>
  void _assign_dispatch(_Integer __n, _Integer __val, __true_type);
  template <class _InputIter>
  void _assign_dispatch(_InputIter __first, _InputIter __last, __false_type);

  // ================================================================
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
    size_type __n = __distance(__first, __last);
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

  // ================================================================
  vector &operator=(const vector &__x) {
    if (&__x != this) {
      const size_type __xlen = __x.size();
      if (__xlen > capacity()) {
      }
    }
  }

  // ================================================================
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

  // ================================================================
  size_type size() const { return size_type(end() - begin()); }
  void      resize(size_type n, value_type val = value_type());
  size_type max_size() const { return size_type(-1) / sizeof(_T); }
  size_type capacity() const {
    return size_type(const_iterator(__end_cap_pointer_ - __begin_));
  }
  bool empty() const { return begin() == end(); }

  // ================================================================
  void reserve(size_type n);

  reference       operator[](size_type __n) { return this->__begin_[__n]; }
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

  // ================================================================
  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
    typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
    _assign_dispatch(__first, __last, _Integral());
  }

  void assign(size_type __n, const value_type &__val) {
    _fill_assign(__n, __val);
  }

  void push_back(const value_type &val);
  template <class InputIterator>
  void insert(iterator __position, InputIterator __first,
              InputIterator __last) {}

  iterator insert(iterator __position, const value_type &__val) {
    size_type __n = __position - begin();  // 벡터 내 몇 번째 위치인지
    // end가 할당 끝이 아니고, 포지션이 엔드일 때
    if (__end_ != __end_cap_pointer_ && __position == end()) {
      _Construct(__end_, __val);
      ++__end_;
    } else
      _insert_aux(iterator(__position), __x);
    return begin() + __n;
  }

  void insert(iterator __position, size_type __n, const value_type &__val) {}

  iterator erase(const_iterator __position) {}

  iterator erase(const_iterator __first, const_iterator __last) {}

  void swap(vector &__x) {
    std::swap(__begin_, __x.__begin_);
    std::swap(__end_, __x.__end_);
    std::swap(__end_cap_pointer_, __x.__end_cap_pointer_);
  }

  void clear() throw() {}

  allocator_type get_allocator() const { return _base::__alloc(); }
};

// ================================================================
// Private functions implement

template <class _T, class _Allocator>
void vector<_T, _Allocator>::__range_check(size_type __n) const {
  if (__n >= this->size()) std::__throw_out_of_range("vector");
}

template <class _T, class _Allocator>
void vector<_T, _Allocator>::_Destroy(pointer *__pointer) {
  __pointer->~_T();
}

template <class _T, class _Allocator>
template <class _ForwardIterator>
void vector<_T, _Allocator>::_Destroy(_ForwardIterator __first,
                                      _ForwardIterator __last) {
  typedef typename iterator_traits<_ForwardIterator>::value_type _Value_type;
  typedef typename __type_traits<_Value_type>::has_trivial_destructor
      _Has_trivial_destructor;
  __destory_aux(__first, __last, _Has_trivial_destructor());
}

template <class _T, class _Allocator>
void vector<_T, _Allocator>::_fill_assign(size_t __n, const value_type &__val) {
  if (__n > capacity()) {
    vector<_T, _Allocator> __tmp(__n, __val, get_allocator());
    __tmp.swap(*this);
  } else if (__n > size()) {
    fill(begin(), end(), __val);
    __end_ = uninitialized_fill_n(__end_, __n - size(), __val);
  } else
    erase(fill_n(begin(), __n, __val), end());
}

template <class _T, class _Allocator>
template <class _InputIter>
void vector<_T, _Allocator>::_assign_aux(_InputIter __first, _InputIter __last,
                                         input_iterator_tag) {
  iterator __cur(begin());
  for (; __first != __last && __cur != end(); ++__cur, ++__first)
    *__cur = *__first;
  if (__first == __last)
    erase(__cur, end());
  else
    insert(end(), __first, __last);
}

template <class _T, class _Allocator>
template <class _ForwardIterator>
void vector<_T, _Allocator>::_assign_aux(_ForwardIterator __first,
                                         _ForwardIterator __last,
                                         forward_iterator_tag) {
  size_type __len = __distance(__first, __last);

  if (__len > capacity()) {
    pointer __tmp = allocator_type::allocate(__len);
    try {
      std::uninitialized_copy(__first, __last, __tmp);
    } catch (...) {
      allocator_type::deallocate(__tmp, __len);
    }
    _Destroy(__begin_, __end_);
    allocator_type::deallocate(__begin_, __end_cap_pointer_ - __begin_);
    __begin_ = __tmp;
    __end_cap_pointer_ = __end_ = __begin_ + __len;
  } else if (size() >= __len) {
    iterator __new_end(ft::__copy_trivial(__first, __last, __begin_));
    _Destroy(__new_end, end());
    __end_ = __new_end.base();
  } else {
    _ForwardIterator __mid = __first;
    ft::advance(__mid, size());
    __copy_trivial(__first, __mid, __begin_);
    __end_ = std::uninitialized_copy(__mid, __last, __end_);
  }
}

template <class _T, class _Allocator>
template <class _Integer>
void vector<_T, _Allocator>::_assign_dispatch(_Integer __n, _Integer __val,
                                              __true_type) {
  _fill_assign((size_type)__n, (_T)__val);
}

template <class _T, class _Allocator>
template <class _InputIter>
void vector<_T, _Allocator>::_assign_dispatch(_InputIter __first,
                                              _InputIter __last, __false_type) {
  typedef typename iterator_traits<_InputIter>::iterator_category _IterCategory;
  _assign_aux(__first, __last, _IterCategory());
}

template <class _T, class _Allocator>
template <class _ForwardIterator>
void vector<_T, _Allocator>::__destroy_aux(_ForwardIterator __first,
                                           _ForwardIterator __last,
                                           __false_type) {
  for (; __first != __last; ++__first) _Destroy(&*__first);
}

template <class _T, class _Allocator>
template <class _ForwardIterator>
void vector<_T, _Allocator>::__destroy_aux(_ForwardIterator, _ForwardIterator,
                                           __true_type) {}

template <class _T, class _Allocator>
void vector<_T, _Allocator>::_insert_aux(iterator __position, const _T &__val) {
  if (__end_ != __end_cap_pointer_) {
    _Construct(__end_, *(__end_ - 1));
    ++__end_;
    _T __val_copy = __val;
  }
}

}  // namespace ft

#endif  // VECTOR_HPP
