#if !defined(VECTOR_HPP)
#define VECTOR_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

#define _NOEXCEPT throw()

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
  allocator_type __alloc_type_;

  __vector_base() _NOEXCEPT;
  __vector_base(const allocator_type &__a);
  __vector_base(size_t __n, const allocator_type &__a);
  ~__vector_base();

  allocator_type       &__alloc() _NOEXCEPT { return __alloc_type_; }
  const allocator_type &__alloc() const _NOEXCEPT { return __alloc_type_; }
  size_type             capacity() const _NOEXCEPT {
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
      __alloc_type_(std::__default_init_tag()) {}

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base(const allocator_type &__a)
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_pointer_(nullptr),
      __alloc_type_(__a) {}

template <typename _T, typename _Allocator>
__vector_base<_T, _Allocator>::__vector_base(size_t                __n,
                                             const allocator_type &__a) {
  __begin_ = __alloc_traits::allocator(__n);
  __end_ = __begin_;
  __end_cap_pointer_ = __begin_ + __n;
  __alloc_type_ = __a;
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
  using _base::__alloc_type_;
  using _base::__begin_;
  using _base::__end_;
  using _base::__end_cap_pointer_;

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

 private:
  // ================================================================
  // make iter functions
  iterator       __make_iter(pointer __p) { return iterator(__p); }
  const_iterator __make_iter(const_pointer __p) const {
    return const_iterator(__p);
  }

  // allocate functions
  _T  *_allocate(size_t __n) { return __alloc_type_.allocate(__n); }
  void _deallocate(_T *__p, size_t __n) { __alloc_type_.deallocate(__p, __n); }

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
  void __fill_assign(size_t __n, const value_type &__val);
  template <class _InputIter>
  void __assign_aux(_InputIter __first, _InputIter __last, input_iterator_tag);
  template <class _ForwardIterator>
  void __assign_aux(_ForwardIterator __first, _ForwardIterator __last,
                    forward_iterator_tag);
  template <class _Integer>
  void __assign_dispatch(_Integer __n, _Integer __val, __true_type);
  template <class _InputIter>
  void __assign_dispatch(_InputIter __first, _InputIter __last, __false_type);

  // ================================================================
  // insert_aux functions
  void __insert_aux(iterator __position, const _T &__val);
  void __insert_aux(iterator __position);

  template <class _Integer>
  void __insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
                         __true_type) {
    __fill_insert(__pos, static_cast<size_type>(__n), static_cast<_T>(__val));
  }

  template <class _InputIterator>
  void __insert_dispatch(iterator __pos, _InputIterator __first,
                         _InputIterator __last, __false_type) {
    __range_insert(__pos, __first, __last);
  }

  void __fill_insert(iterator __pos, size_type __n, const _T &__val);

  template <class _InputIterator>
  void __range_insert(iterator __pos, _InputIterator __first,
                      _InputIterator __last);

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
      __alloc_type_.deallocate(__begin_, this->capacity());
      __begin_ = __end_ = __end_cap_pointer_ = NULL;
    }
  }

  // ================================================================
  vector &operator=(const vector &__x) {
    if (&__x != this) {
      const size_type __xlen = __x.size();
      if (__xlen > capacity()) {
        pointer __tmp = __allocate_and_copy(__xlen, __x.begin(), __x.end());
        _Destroy(__begin_, __end_);
        _deallocate(__begin_, __end_cap_pointer_ - __begin_);
        __begin_ = __tmp;
        __end_ = __begin_ + __xlen;
      } else if (size() >= __xlen) {
        iterator __i(__copy_trivial(__x.begin(), __x.end(), begin()));
        _Destroy(__i, end());
      } else {
        __copy_trivial(__x.begin(), __x.begin() + size(), __begin_);
        std::uninitialized_copy(__x.begin() + size(), __x.end(), __end_);
      }
      __end_ = __begin_ + __xlen;
    }
    return *this;
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
    return size_type(const_iterator(__end_cap_pointer_) - begin());
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
    __assign_dispatch(__first, __last, _Integral());
  }

  void assign(size_type __n, const value_type &__val) {
    __fill_assign(__n, __val);
  }

  void push_back(const value_type &__val) {
    if (__end_ != __end_cap_pointer_) {
      _Construct(__end_, __val);
      ++__end_;
    } else {
      __insert_aux(end(), __val);
    }
  }

  template <class InputIterator>
  void insert(iterator __position, InputIterator __first,
              InputIterator __last) {
    typedef typename _Is_integer<InputIterator>::_Integral _Integral;
    __insert_dispatch(__position, __first, __last, _Integral());
  }

  iterator insert(iterator __position, const value_type &__val) {
    size_type __n = __position - begin();  // 벡터 내 몇 번째 위치인지
    // end가 할당 끝이 아니고, 포지션이 엔드일 때
    if (__end_ != __end_cap_pointer_ && __position == end()) {
      _Construct(__end_, __val);
      ++__end_;
    } else
      __insert_aux(iterator(__position), __val);
    return begin() + __n;
  }

  void insert(iterator __position, size_type __n, const value_type &__val) {
    __fill_insert(__position, __n, __val);
  }

  iterator erase(iterator __position) {
    if (__position + 1 != end())
      __copy_trivial(__position + 1, end(), __position);
    --__end_();
    _Destroy(__end_);
    return __position;
  }

  iterator erase(iterator __first, iterator __last) {
    iterator __i(__copy_trivial(__last, end(), __first));
    _Destroy(__i, end());
    // __end_ =
    return __i;
  }

  void swap(vector &__x) {
    std::swap(__begin_, __x.__begin_);
    std::swap(__end_, __x.__end_);
    std::swap(__end_cap_pointer_, __x.__end_cap_pointer_);
  }

  void clear() { erase(begin(), end()); }

  allocator_type get_allocator() const { return _base::__alloc(); }
};

// ================================================================
// vector: Private functions implement

template <class _T, class _Allocator>
void vector<_T, _Allocator>::__range_check(size_type __n) const {
  if (__n >= this->size()) std::__throw_out_of_range("vector");
}

// ================================================================

template <class _T, class _Allocator>
void vector<_T, _Allocator>::__fill_assign(size_t            __n,
                                           const value_type &__val) {
  if (__n > capacity()) {
    vector<_T, _Allocator> __tmp(__n, __val, get_allocator());
    __tmp.swap(*this);
  } else if (__n > size()) {
    // fill(begin(), end(), __val);
    __end_ = uninitialized_fill_n(__end_, __n - size(), __val);
  }
  // else
  // erase(std::fill_n(begin(), __n, __val), end());
}

template <class _T, class _Allocator>
template <class _InputIter>
void vector<_T, _Allocator>::__assign_aux(_InputIter __first, _InputIter __last,
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
void vector<_T, _Allocator>::__assign_aux(_ForwardIterator __first,
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
void vector<_T, _Allocator>::__assign_dispatch(_Integer __n, _Integer __val,
                                               __true_type) {
  __fill_assign((size_type)__n, (_T)__val);
}

template <class _T, class _Allocator>
template <class _InputIter>
void vector<_T, _Allocator>::__assign_dispatch(_InputIter __first,
                                               _InputIter __last,
                                               __false_type) {
  typedef typename iterator_traits<_InputIter>::iterator_category _IterCategory;
  __assign_aux(__first, __last, _IterCategory());
}

template <class _T, class _Allocator>
void vector<_T, _Allocator>::__insert_aux(iterator  __position,
                                          const _T &__val) {
  if (__end_ != __end_cap_pointer_) {
    _Construct(__end_, *(__end_ - 1));
    ++__end_;
    _T __val_copy = __val;
    __copy_backward(__position, iterator(__end_ - 2), iterator(__end_ - 1));
    *__position = __val_copy;
  } else {
    const size_type __old_size = size();
    const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
    iterator        __new_start(_allocate(__len));
    iterator        __new_finish(__new_start);
    try {
      __new_finish = std::uninitialized_copy(begin(), __position, __new_start);
      _Construct(__new_finish.base(), __val);
      ++__new_finish;
      __new_finish = std::uninitialized_copy(__position, end(), __new_finish);
    } catch (...) {
      _Destroy(__new_start, __new_finish);
      _deallocate(__new_start.base(), __len);
      throw;
    }
    _Destroy(begin(), end());
    _deallocate(__begin_, __end_cap_pointer_ - __begin_);
    __begin_ = __new_start.base();
    __end_ = __new_finish.base();
    __end_cap_pointer_ = __new_start.base() + __len;
  }
}

template <class _T, class _Allocator>
void vector<_T, _Allocator>::__insert_aux(iterator __position) {
  if (__end_ != __end_cap_pointer_) {
    _Construct(__end_, *(__end_ - 1));
    ++__end_;
    __copy_backward(__position, iterator(__end_ - 2), iterator(__end_ - 1));
    *__position = _T();
  } else {
    const size_type __old_size = size();
    const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
    iterator        __new_start = _allocate(__len);
    iterator        __new_finish(__new_start);
    try {
      __new_finish = std::uninitialized_copy(begin(), __position, __new_start);
      _Construct(__new_finish);
      ++__new_finish;
      __new_finish = std::uninitialized_copy(__position, end(), __new_finish);
    } catch (...) {
      _Destroy(__new_start, __new_finish);
      _deallocate(__new_start.base(), __len);
      throw;
    }
    _Destroy(begin(), end());
    _deallocate(__begin_, __end_cap_pointer_ - __begin_);
    __begin_ = __new_start.base();
    __end_ = __new_finish.base();
    __end_cap_pointer_ = __new_start.base() + __len;
  }
}

template <class _T, class _Allocator>
void vector<_T, _Allocator>::__fill_insert(iterator __pos, size_type __n,
                                           const _T &__val) {
  if (__n != 0) {
    if (size_type(__end_cap_pointer_ - __end_) >= __n) {
      _T              __val_copy = __val;
      const size_type __elems_after = end() - __pos;
      iterator        __old_end(__end_);

      if (__elems_after > __n) {
        std::uninitialized_copy(__end_ - __n, __end_, __end_);
        __end_ += __n;
        __copy_backward(__pos, __old_end - __n, __old_end);
        _fill(__pos, __pos + __n, __val_copy);
      } else {
        std::uninitialized_copy_n(__end_, __n - __elems_after, __val_copy);
        __end_ += __n - __elems_after;
        std::uninitialized_copy(__pos, __old_end, __end_);
        __end_ += __elems_after;
        fill(__pos, __old_end, __val_copy);
      }
    } else {
      const size_type __old_size = size();
      const size_type __len =
          __old_size + (__old_size >= __n ? __old_size : __n);
      iterator __new_begin(_allocate(__len));
      iterator __new_end(__new_begin);

      try {
        __new_end = std::uninitialized_copy(begin(), __pos, __new_begin);
        __new_end = std::uninitialized_fill_n(__new_end, __n, __val);
        __new_end = std::uninitialized_copy(__pos, end(), __new_end);
      } catch (...) {
        _Destroy(__new_begin, __new_end);
        _deallocate(__new_begin.base(), __len);
        throw;
      }
      _Destroy(__begin_, __end_);
      _deallocate(__begin_, __end_cap_pointer_ - __begin_);
      __begin_ = __new_begin.base();
      __end_ = __new_end.base();
      __end_cap_pointer_ = __new_begin.base() + __len;
    }
  }
}

template <class _T, class _Allocator>
template <class _InputIterator>
void vector<_T, _Allocator>::__range_insert(iterator       __pos,
                                            _InputIterator __first,
                                            _InputIterator __last) {
  for (; __first != __last; ++__first) {
    __pos = insert(__pos, *__first);
    ++__pos;
  }
}

}  // namespace ft

#endif  // VECTOR_HPP
