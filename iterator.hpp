#if !defined(ITERATOR_HPP)
#define ITERATOR_HPP

namespace ft {

struct input_iterator_tag;
struct output_iterator_tag;
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;

template <class Iter>
class iterator_traits {
  typedef typename Iter::difference_type   difference_type;
  typedef typename Iter::value_type        value_type;
  typedef typename Iter::pointer           pointer;
  typedef typename Iter::reference         reference;
  typedef typename Iter::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T *> {
  typedef ptrdiff_t                           difference_type;
  typedef T                                   value_type;
  typedef T *                                 pointer;
  typedef T &                                 reference;
  typedef typename random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T *> {
  typedef ptrdiff_t                           difference_type;
  typedef T                                   value_type;
  typedef const T *                           pointer;
  typedef const T &                           reference;
  typedef typename random_access_iterator_tag iterator_category;
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
  reverse_iterator(const reverse_iterator &ri) : current(ri.current) {}
};
}  // namespace ft

#endif  // ITERATOR_HPP
