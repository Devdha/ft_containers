#if !defined(ITERATOR_HPP)
#define ITERATOR_HPP

#include <cstddef>

namespace ft {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename Category, typename T, typename Distance = ptrdiff_t,
          typename Pointer = T*, typename Reference = T&>
class iterator {
  typedef Category  iterator_traits;
  typedef T         value_type;
  typedef Distance  difference_type;
  typedef Pointer   pointer;
  typedef Reference reference;
};

template <class Iter>
class iterator_traits {
  typedef typename Iter::difference_type   difference_type;
  typedef typename Iter::value_type        value_type;
  typedef typename Iter::pointer           pointer;
  typedef typename Iter::reference         reference;
  typedef typename Iter::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*> {
  typedef ptrdiff_t                  difference_type;
  typedef T                          value_type;
  typedef T*                         pointer;
  typedef T&                         reference;
  typedef random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*> {
  typedef ptrdiff_t                  difference_type;
  typedef T                          value_type;
  typedef const T*                   pointer;
  typedef const T&                   reference;
  typedef random_access_iterator_tag iterator_category;
};

template <class _Iter>
class reverse_iterator
    : public iterator<typename iterator_traits<_Iter>::iterator_category,
                      typename iterator_traits<_Iter>::value_type
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
inline bool operator==(const reverse_iterator<Iter>& __lhs,
                       const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() == __rhs.base();
}
template <class Iter>
inline bool operator!=(const reverse_iterator<Iter>& __lhs,
                       const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() != __rhs.base();
}
template <class Iter>
inline bool operator<(const reverse_iterator<Iter>& __lhs,
                      const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() < __rhs.base();
}
template <class Iter>
inline bool operator<=(const reverse_iterator<Iter>& __lhs,
                       const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() <= __rhs.base();
}
template <class Iter>
inline bool operator>(const reverse_iterator<Iter>& __lhs,
                      const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() > __rhs.base();
}
template <class Iter>
inline bool operator>=(const reverse_iterator<Iter>& __lhs,
                       const reverse_iterator<Iter>& __rhs) {
  return __lhs.base() >= __rhs.base();
}
template <class Iter>
inline typename reverse_iterator<Iter>::diffrence_type operator-(
    const reverse_iterator<Iter>& __lhs, const reverse_iterator<Iter>& __rhs) {
  return __rhs.base() - __lhs.base();
}
template <class Iter>
inline reverse_iterator<Iter> operator+(
    typename reverse_iterator<Iter>::difference_type __n,
    const reverse_iterator<Iter>&                    __rev_it) {
  return reverse_iterator<Iter>(__rev_it.base() - __n);
}

}  // namespace ft

#endif  // ITERATOR_HPP
