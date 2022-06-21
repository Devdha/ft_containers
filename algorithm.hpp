#if !defined(ALGORITHM_HPP)
#define ALGORITHM_HPP

namespace ft {

// ================================================================
// copy
template <typename _T>
_T* __copy_trivial(const _T* __first, const _T* __last, _T* __result) {
  memmove(__result, __first, sizeof(_T) * (__last - __first));
  return __result + (__last - __first);
}

// ================================================================
// Construct
template <class _T1, class _T2>
void _Construct(_T1* __p, const _T2& __value) {
  new (static_cast<void*>(__p)) _T1(__value);
}

template <class _T1>
void _Construct(_T1* __p) {
  new (static_cast<void*>(__p) _T1();)
}

}  // namespace ft

#endif  // ALGORITHM_HPP
