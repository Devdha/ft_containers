#if !defined(RBTREE_HPP)
#define RBTREE_HPP

#include "algorithm.hpp"

namespace ft {
enum _Rb_tree_color { _S_red = false, _S_black = true };

struct _Rb_tree_node_base {
  typedef _Rb_tree_node_base* _Base_ptr;

  _Rb_tree_color _M_color;
  _Base_ptr      _M_parent;
  _Base_ptr      _M_left;
  _Base_ptr      _M_right;

  static _Base_ptr _S_minumum(_Base_ptr __x) {
    while (__x->_M_left != 0) __x = __x->_M_left;
    return __x;
  }

  static _Base_ptr _S_maximum(_Base_ptr __x) {
    while (__x->_M_right != 0) __x = __x->_M_right;
    return __x;
  }
};

template <typename _Val>
struct _Rb_tree_node : public _Rb_tree_node_base {
  typedef _Rb_tree_node<_Val>* _Link_type;
  _Val                         _M_value_field;
};

struct _Rb_tree_base_iterator {
  typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
  typedef bidirectional_iterator_tag    iterator_category;
  typedef ptrdiff_t                     difference_type;

  _Base_ptr _M_node;

  void _M_increase() {
    // When node has right child, go to right child.
    if (_M_node->_M_right != 0) {
      _M_node = _M_node->_M_right;
      // go to leftmost child.
      while (_M_node->_M_left != 0) _M_node = _M_node->_M_left;
    } else {  // when there's no right child, go to parent.
      _Base_ptr __y = _M_node->_M_parent;
      // while current node is a right child, go to parent.
      // if current node is a left child, it means parent is the incremented
      // value.
      while (_M_node == __y->_M_right) {
        _M_node = __y;
        __y = __y->_M_parent;
      }
      // if _M_node is a rightmost child, go to header(end()).
      if (_M_node->_M_right != __y) _M_node = __y;
    }
  }
  void _M_decrease() {
    // Condition, node is header
    if (_M_node->_M_color == _S_red && _M_node->_M_parent->_M_parent == _M_node)
      _M_node = _M_node->_M_right;
    // Condition, node has left child
    else if (_M_node->_M_left != 0) {
      _Base_ptr __y = _M_node->_M_left;
      while (__y->_M_right != 0) __y = __y->_M_right;
      _M_node = __y;
      // Condition, not an header and has no left child
    } else {
      _Base_ptr __y = _M_node->_M_parent;
      while (_M_node == __y->_M_left) {
        _M_node = __y;
        __y = __y->_M_parent;
      }
      _M_node = __y;
    }
  }
};

template <typename _Val, typename _Ref, typename _Ptr>
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
  typedef _Val                                              value_type;
  typedef _Ref                                              reference;
  typedef _Ptr                                              pointer;
  typedef _Rb_tree_iterator<_Val, _Val&, _Val*>             iterator;
  typedef _Rb_tree_iterator<_Val, const _Val&, const _Val*> const_iterator;
  typedef _Rb_tree_iterator<_Val, _Ref, _Ptr>               _Self;
  typedef _Rb_tree_node<_Val>*                              _Link_type;

  _Rb_tree_iterator() {}
  _Rb_tree_iterator(_Rb_tree_node_base* __x) { _M_node = __x; }
  _Rb_tree_iterator(const iterator& __x) { _M_node = __x._M_node; }

  reference operator*() const { return _Link_type(_M_node)->_M_value_field; }
  pointer   operator->() const { return &(operator*()); }
  _Self&    operator++() {
       _M_increase();
       return *this;
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    _M_increase();
    return __tmp;
  }
  _Self& operator--() {
    _M_decrease();
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    _M_decrease();
    return __tmp;
  }
};

template <typename _Val, typename _Ref, typename _Ptr>
inline bool operator==(const _Rb_tree_iterator<_Val, _Ref, _Ptr>& __x,
                       const _Rb_tree_iterator<_Val, _Ref, _Ptr>& __y) {
  return __x._M_node == __y._M_node;
}

template <typename _Val>
inline bool operator==(
    const _Rb_tree_iterator<_Val, const _Val&, const _Val*>& __x,
    const _Rb_tree_iterator<_Val, _Val&, _Val*>&             __y) {
  return __x._M_node == __y._M_node;
}

template <typename _Val>
inline bool operator==(
    const _Rb_tree_iterator<_Val, _Val&, _Val*>&             __x,
    const _Rb_tree_iterator<_Val, const _Val&, const _Val*>& __y) {
  return __x._M_node == __y._M_node;
}

template <typename _Val, typename _Ref, typename _Ptr>
inline bool operator!=(const _Rb_tree_iterator<_Val, _Ref, _Ptr>& __x,
                       const _Rb_tree_iterator<_Val, _Ref, _Ptr>& __y) {
  return __x._M_node != __y._M_node;
}

template <typename _Val>
inline bool operator!=(
    const _Rb_tree_iterator<_Val, const _Val&, const _Val*>& __x,
    const _Rb_tree_iterator<_Val, _Val&, _Val*>&             __y) {
  return __x._M_node != __y._M_node;
}

template <typename _Val>
inline bool operator!=(
    const _Rb_tree_iterator<_Val, _Val&, _Val*>&             __x,
    const _Rb_tree_iterator<_Val, const _Val&, const _Val*>& __y) {
  return __x._M_node != __y._M_node;
}

}  // namespace ft

#endif  // RBTREE_HPP