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

  explicit reverse_iterator(iterator_type i) : current(i) {}

  reverse_iterator(const reverse_iterator& ri) : current(ri.current) {}

  template <typename _U>
  reverse_iterator(const reverse_iterator<_U>& ri) : current(ri.base()) {}

  template <typename _U>
  reverse_iterator<_Iter>& operator=(const reverse_iterator<_U>& ri) {
    current = ri.base();
    return *this;
  }

  iterator_type base() const { return current; }
  reference     operator*() const {
    iterator_type i(current);
    return *--i;
  }
  pointer           operator->() const { return &(operator*()); }
  reverse_iterator& operator++() {
    --current;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator ri(*this);
    --current;
    return ri;
  }
  reverse_iterator& operator--() {
    ++current;
    return *this;
  }
  reverse_iterator operator--(int) {
    reverse_iterator ri(*this);
    ++current;
    return *this;
  }
  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(current - n);
  }
  reverse_iterator& operator+=(difference_type n) {
    current -= n;
    return *this;
  }
  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(current + n);
  }
  reverse_iterator operator-=(difference_type n) {
    current += n;
    return *this;
  }
  reference operator[](difference_type n) const { return current[-n - 1]; }
};

template <class Iter>
inline bool operator==(const reverse_iterator<Iter>& lhs,
                       const reverse_iterator<Iter>& rhs) {
  return lhs.base() == rhs.base();
}
template <class Iter>
inline bool operator!=(const reverse_iterator<Iter>& lhs,
                       const reverse_iterator<Iter>& rhs) {
  return lhs.base() != rhs.base();
}
template <class Iter>
inline bool operator<(const reverse_iterator<Iter>& lhs,
                      const reverse_iterator<Iter>& rhs) {
  return lhs.base() < rhs.base();
}
template <class Iter>
inline bool operator<=(const reverse_iterator<Iter>& lhs,
                       const reverse_iterator<Iter>& rhs) {
  return lhs.base() <= rhs.base();
}
template <class Iter>
inline bool operator>(const reverse_iterator<Iter>& lhs,
                      const reverse_iterator<Iter>& rhs) {
  return lhs.base() > rhs.base();
}
template <class Iter>
inline bool operator>=(const reverse_iterator<Iter>& lhs,
                       const reverse_iterator<Iter>& rhs) {
  return lhs.base() >= rhs.base();
}
template <class Iter>
inline typename reverse_iterator<Iter>::diffrence_type operator-(
    const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
  return rhs.base() - lhs.base();
}
template <class Iter>
inline reverse_iterator<Iter> operator+(
    typename reverse_iterator<Iter>::difference_type n,
    const reverse_iterator<Iter>&                    rev_it) {
  return reverse_iterator<Iter>(rev_it.base() - n);
}

}  // namespace ft

#endif  // ITERATOR_HPP
