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
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;
  typedef typename Iter::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T *> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef typename std::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T *> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef typename std::random_access_iterator_tag iterator_category;
};

template <class _Iterator>
class reverse_iterator
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
                      typename iterator_traits<_Iterator>::value_type
                      typename iterator_traits<_Iterator>::difference_type,
                      typename iterator_traits<_Iterator>::pointer,
                      typename iterator_traits<_Iterator>::reference> {
 protected:
  _Iterator current;

  typedef iterator_traits<_Iterator> __traits_type;

 public:
  typedef _Iterator iterator_type;
  typedef typename __traits_type::pointer pointer;
  typedef typename __traits_type::difference_type difference_type;
  typedef typename __traits_type::reference reference;
};
}  // namespace ft

#endif  // ITERATOR_HPP
