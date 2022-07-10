#pragma once

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

// ================================================================
// memset

// template <typename _T>
// void _fill(_T* __first, _T* __last, const _T& __c) {
//   unsigned char __tmp = __c;
//   memset(__first, __tmp, __last - __first);
// }

// ================================================================
// fill
inline void _fill(unsigned char* __first, unsigned char* __last,
                  const unsigned char& __c) {
  unsigned char __tmp = __c;
  memset(__first, __tmp, __last - __first);
}

inline void _fill(signed char* __first, signed char* __last,
                  const signed char& __c) {
  signed char __tmp = __c;
  memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
}

inline void _fill(char* __first, char* __last, const char& __c) {
  char __tmp = __c;
  memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
}

template <typename _ForwardIter, typename _T>
inline void _fill(_ForwardIter __first, _ForwardIter __last,
                  const _T& __value) {
  for (; __first != __last; ++__first) *__first = __value;
}

template <typename _T, typename _Size>
inline _T* _fill_n(_T* __first, _Size __n, const _T& __c) {
  for (_Size i = 0; i < __n; i++) *(__first + i) = __c;
  return __first + __n;
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

template <class _T>
void _Destroy(_T* __pointer) {
  __pointer->~_T();
}

template <class _ForwardIterator>
void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last,
                   __false_type) {
  for (; __first != __last; ++__first) _Destroy(&*__first);
}

template <class _ForwardIterator>
void __destroy_aux(_ForwardIterator, _ForwardIterator, __true_type) {}

template <class _ForwardIterator>
void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {
  typedef typename iterator_traits<_ForwardIterator>::value_type _Value_type;
  typedef typename __type_traits<_Value_type>::has_trivial_destructor
      _Has_trivial_destructor;
  __destroy_aux(__first, __last, _Has_trivial_destructor());
}

// ================================================================
// equal
template <typename _InputIter1, typename _InputIter2>
bool equal(_InputIter1 __first1, _InputIter1 __last1, _InputIter2 __first2) {
  for (; __first1 != __last1; ++__first1, ++__first2)
    if (!(*__first1 == *__first2)) return false;
  return true;
}

template <typename _InputIter1, typename _InputIter2, typename BinaryPredicate>
bool equal(_InputIter1 __first1, _InputIter1 __last1, _InputIter2 __first2,
           BinaryPredicate _predicate) {
  for (; __first1 != __last1; ++__first1, ++__first2)
    if (!_predicate(*__first1, *__first2)) return false;
  return true;
}

template <typename _InputIter1, typename _InputIter2>
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2) {
  for (; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2) {
    if (*__first1 < *__first2) return true;
    if (*__first2 < *__first1) return false;
  }
  return __first1 == __last1 && __first2 != __last2;
}

template <typename _InputIter1, typename _InputIter2, typename _Compare>
bool lexicographical_compare(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2,
                             _Compare _comp) {
  for (; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2) {
    if (_comp(*__first1, *__first2)) return true;
    if (_comp(*__first2, *__first1)) return false;
  }
  return __first1 == __last1 && __first2 != __last2;
}

template <typename _T>
void swap(_T& __a, _T& __b) {
  _T __tmp = __a;
  __a = __b;
  __b = __tmp;
}

// ================================================================
// min/max

template <typename _T>
_T min(const _T& __a, const _T& __b) {
  return __a < __b ? __a : __b;
}

template <typename _T>
_T max(const _T& __a, const _T& __b) {
  return __a > __b ? __a : __b;
}

}  // namespace ft
