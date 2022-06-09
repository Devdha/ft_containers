#if !defined(ITERATOR_HPP)
#define ITERATOR_HPP

template <class Iterator>
class iterator_traits {};
template <class T>
class iterator_traits<T *> {};
template <class T>
class iterator_traits<const T *> {};

#endif  // ITERATOR_HPP
