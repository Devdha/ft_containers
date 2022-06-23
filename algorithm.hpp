#if !defined(ALGORITHM_HPP)
#define ALGORITHM_HPP

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

// ================================================================
// memset
void _fill(char* __first, char* __last, const char& __c) {
  char __tmp = __c;
  memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
}

// ================================================================
// copy
template <typename _T>
_T* __copy_trivial(const _T* __first, const _T* __last, _T* __result) {
  memmove(__result, __first, sizeof(_T) * (__last - __first));
  return __result + (__last - __first);
}

template <typename _InputIter, typename _OutputIter>
_OutputIter __copy_trivial(_InputIter __first, _InputIter __last,
                           _OutputIter __result) {
  for (; __first != __last; ++__result, ++__first) *__result = *__first;
  return __result;
}

template <typename _BidirectionalIter1, typename _BidirectionalIter2>
_BidirectionalIter2 __copy_backward(_BidirectionalIter1 __first,
                                    _BidirectionalIter1 __last,
                                    _BidirectionalIter2 __result) {
  while (__first != __last) *--__result = *--__last;
  return __result;
}

template <typename _T>
_T* __copy_backward(const _T* __first, const _T* __last, _T* __result) {
  const ptrdiff_t __n = __last - __first;
  memmove(__result - __n, __first, sizeof(_T) * __n);
  return __result - __n;
}

// ================================================================
// Construct
template <class _T1, class _T2>
void _Construct(_T1* __p, const _T2& __value) {
  new (static_cast<void*>(__p)) _T1(__value);
}

template <class _T1>
void _Construct(_T1* __p) {
  new (static_cast<void*>(__p)) _T1();
}

template <class _ForwardIterator>
void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last,
                   __false_type) {
  for (; __first != __last; ++__first) _Destroy(&*__first);
}

template <class _ForwardIterator>
void __destroy_aux(_ForwardIterator, _ForwardIterator, __true_type) {}

template <class _T>
void _Destroy(_T* __pointer) {
  __pointer->~_T();
}

template <class _ForwardIterator>
void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {
  typedef typename iterator_traits<_ForwardIterator>::value_type _Value_type;
  typedef typename __type_traits<_Value_type>::has_trivial_destructor
      _Has_trivial_destructor;
  __destroy_aux(__first, __last, _Has_trivial_destructor());
}

}  // namespace ft

#endif  // ALGORITHM_HPP
