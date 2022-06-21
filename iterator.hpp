#if !defined(ITERATOR_HPP)
#define ITERATOR_HPP

#include <cstddef>

namespace ft {

// iterator_tags
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// iterator
template <typename Category, typename T, typename Distance = ptrdiff_t,
          typename Pointer = T*, typename Reference = T&>
struct iterator {
  typedef Category  iterator_traits;
  typedef T         value_type;
  typedef Distance  difference_type;
  typedef Pointer   pointer;
  typedef Reference reference;
};

// iterator_traits
template <class Iter>
struct iterator_traits {
  typedef typename Iter::difference_type   difference_type;
  typedef typename Iter::value_type        value_type;
  typedef typename Iter::pointer           pointer;
  typedef typename Iter::reference         reference;
  typedef typename Iter::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
  typedef ptrdiff_t                  difference_type;
  typedef T                          value_type;
  typedef T*                         pointer;
  typedef T&                         reference;
  typedef random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
  typedef ptrdiff_t                  difference_type;
  typedef T                          value_type;
  typedef const T*                   pointer;
  typedef const T&                   reference;
  typedef random_access_iterator_tag iterator_category;
};

// reverse_iterator
template <class _Iter>
class reverse_iterator
    : public iterator<typename iterator_traits<_Iter>::iterator_category,
                      typename iterator_traits<_Iter>::value_type,
                      typename iterator_traits<_Iter>::difference_type,
                      typename iterator_traits<_Iter>::pointer,
                      typename iterator_traits<_Iter>::reference> {
 protected:
  _Iter current;

 public:
  typedef _Iter                                            iterator_type;
  typedef typename iterator_traits<_Iter>::difference_type difference_type;
  typedef typename iterator_traits<_Iter>::reference       reference;
  typedef typename iterator_traits<_Iter>::pointer         pointer;

  reverse_iterator() : current() {}

  explicit reverse_iterator(iterator_type __i) : current(__i) {}

  reverse_iterator(const reverse_iterator& __ri) : current(__ri.current) {}

  template <typename _U>
  reverse_iterator(const reverse_iterator<_U>& __ri) : current(__ri.base()) {}

  template <typename _U>
  reverse_iterator<_Iter>& operator=(const reverse_iterator<_U>& __ri) {
    current = __ri.base();
    return *this;
  }

  iterator_type base() const { return current; }
  reference     operator*() const {
        iterator_type __i(current);
        return *--__i;
  }
  pointer           operator->() const { return &(operator*()); }
  reverse_iterator& operator++() {
    --current;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator __ri(*this);
    --current;
    return __ri;
  }
  reverse_iterator& operator--() {
    ++current;
    return *this;
  }
  reverse_iterator operator--(int) {
    reverse_iterator __ri(*this);
    ++current;
    return __ri;
  }
  reverse_iterator operator+(difference_type __n) const {
    return reverse_iterator(current - __n);
  }
  reverse_iterator& operator+=(difference_type __n) {
    current -= __n;
    return *this;
  }
  reverse_iterator operator-(difference_type __n) const {
    return reverse_iterator(current + __n);
  }
  reverse_iterator operator-=(difference_type __n) {
    current += __n;
    return *this;
  }
  reference operator[](difference_type __n) const { return current[-__n - 1]; }
};

template <class Iter>
bool operator==(const reverse_iterator<Iter>& __lhs,
                const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() == __rhs.base();
}
template <class Iter>
bool operator!=(const reverse_iterator<Iter>& __lhs,
                const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() != __rhs.base();
}
template <class Iter>
bool operator<(const reverse_iterator<Iter>& __lhs,
               const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() < __rhs.base();
}
template <class Iter>
bool operator<=(const reverse_iterator<Iter>& __lhs,
                const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() <= __rhs.base();
}
template <class Iter>
bool operator>(const reverse_iterator<Iter>& __lhs,
               const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() > __rhs.base();
}
template <class Iter>
bool operator>=(const reverse_iterator<Iter>& __lhs,
                const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() >= __rhs.base();
}
template <class Iter>
typename reverse_iterator<Iter>::diffrence_type operator-(
    const reverse_iterator<Iter>& __lhs, const reverse_iterator<Iter>& __rhs) {
  return __rhs.base() - __lhs.base();
}
template <class Iter>
reverse_iterator<Iter> operator+(
    typename reverse_iterator<Iter>::difference_type __n,
    const reverse_iterator<Iter>&                    __rev_it) {
  return reverse_iterator<Iter>(__rev_it.base() - __n);
}

template <typename _Iterator, typename _Container>
class __normal_iterator
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
                      typename iterator_traits<_Iterator>::value_type,
                      typename iterator_traits<_Iterator>::difference_type,
                      typename iterator_traits<_Iterator>::pointer,
                      typename iterator_traits<_Iterator>::reference> {
 protected:
  _Iterator _current;

 public:
  typedef typename iterator_traits<_Iterator>::difference_type difference_type;
  typedef typename iterator_traits<_Iterator>::reference       reference;
  typedef typename iterator_traits<_Iterator>::pointer         pointer;

  __normal_iterator() : _current(_Iterator()) {}

  explicit __normal_iterator(const _Iterator& __i) : _current(__i) {}

  template <typename _Iter>
  __normal_iterator(const __normal_iterator<_Iter, _Container>& __i)
      : _current(__i.base()) {}

  reference operator*() const { return *_current; }

  pointer operator->() const { return _current; }

  __normal_iterator& operator++() {
    ++_current;
    return *this;
  }

  __normal_iterator operator++(int) { return __normal_iterator(_current++); }

  // Bidirectional iterator requirements
  __normal_iterator& operator--() {
    --_current;
    return *this;
  }

  __normal_iterator operator--(int) { return __normal_iterator(_current--); }

  // Random access iterator requirements
  reference operator[](const difference_type& __n) const {
    return _current[__n];
  }

  __normal_iterator& operator+=(const difference_type& __n) {
    _current += __n;
    return *this;
  }

  __normal_iterator operator+(const difference_type& __n) const {
    return __normal_iterator(_current + __n);
  }

  __normal_iterator& operator-=(const difference_type& __n) {
    _current -= __n;
    return *this;
  }

  __normal_iterator operator-(const difference_type& __n) const {
    return __normal_iterator(_current - __n);
  }

  difference_type operator-(const __normal_iterator& __i) const {
    return _current - __i._current;
  }

  const _Iterator& base() const { return _current; }
};

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator==(const __normal_iterator<_IteratorL, _Container>& __lhs,
                       const __normal_iterator<_IteratorR, _Container>& __rhs) {
  return __lhs.base() == __rhs.base();
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs,
                       const __normal_iterator<_IteratorR, _Container>& __rhs) {
  return !(__lhs == __rhs);
}

// Random access iterator requirements
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator<(const __normal_iterator<_IteratorL, _Container>& __lhs,
                      const __normal_iterator<_IteratorR, _Container>& __rhs) {
  return __lhs.base() < __rhs.base();
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator>(const __normal_iterator<_IteratorL, _Container>& __lhs,
                      const __normal_iterator<_IteratorR, _Container>& __rhs) {
  return __rhs < __lhs;
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs,
                       const __normal_iterator<_IteratorR, _Container>& __rhs) {
  return !(__rhs < __lhs);
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs,
                       const __normal_iterator<_IteratorR, _Container>& __rhs) {
  return !(__lhs < __rhs);
}

template <typename _Iterator, typename _Container>
inline __normal_iterator<_Iterator, _Container> operator+(
    typename __normal_iterator<_Iterator, _Container>::difference_type __n,
    const __normal_iterator<_Iterator, _Container>&                    __i) {
  return __normal_iterator<_Iterator, _Container>(__i.base() + __n);
}

template <typename _T>
_T* __copy_trivial(const _T* __first, const _T* __last, _T* __result) {
  memmove(__result, __first, sizeof(_T) * (__last - __first));
  return __result + (__last - __first);
}

template <typename _InputIterator, typename _Distance>
void advance(_InputIterator& __i, _Distance __n) {
  while (__n--) ++__i;
}

}  // namespace ft

#endif  // ITERATOR_HPP
