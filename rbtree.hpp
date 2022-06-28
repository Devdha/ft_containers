#if !defined(RBTREE_HPP)
#define RBTREE_HPP

#include <memory>

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

void _Rb_tree_rotate_left(_Rb_tree_node_base*  __x,
                          _Rb_tree_node_base*& __root) {
  // set right node as __y
  _Rb_tree_node_base* __y = __x->_M_right;
  // connect __y's left child to __x's right child.
  __x->_M_right = __y->_M_left;
  if (__y->_M_left != 0) __y->_M_left->_M_parent = __x;
  __y->_M_parent = __x->_M_parent;

  // connect to it's parent or set as root.
  if (__x == __root)
    __root = __y;
  else if (__x == __x->_M_parent->_M_left)
    __x->_M_parent->_M_left = __y;
  else
    __x->_M_parent->_M_right = __y;
  __y->_M_left = __x;
  __x->_M_parent = __y;
}

void _Rb_tree_rotate_right(_Rb_tree_node_base*  __x,
                           _Rb_tree_node_base*& __root) {
  _Rb_tree_node_base* __y = __x->_M_left;
  __x->_M_left = __y->_M_right;
  if (__y->_M_right != 0) __y->_M_right->_M_parent = __x;
  __y->_M_parent = __x->_M_parent;

  if (__x == __root)
    __root = __y;
  else if (__x == __x->_M_parent->_M_right)
    __x->_M_parent->_M_right = __y;
  else
    __x->_M_parent->_M_left = __y;
  __y->_M_right = __x;
  __x->_M_parent = __y;
}

void _Rb_tree_rebalance(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root) {
  // set new node color red.
  __x->_M_color = _S_red;
  // while node isn't root and node's parent is red.
  // rebalance the tree.
  while (__x != __root && __x->_M_parent->_M_color == _S_red) {
    // if node's parent is a left child of its parent.
    if (__x->_M_parent == __x->_M_parent->_M_parent->_M_left) {
      _Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_right;
      // if uncle node is red.
      if (__y && __y->_M_color == _S_red) {
        // set parent and uncle node to black and grandparent to red.
        __x->_M_parent->_M_color = _S_black;
        __y->_M_color = _S_black;
        __x->_M_parent->_M_parent->_M_color = _S_red;
        // set grandparent as __x.
        __x = __x->_M_parent->_M_parent;
      } else {
        // if __x is a right child.
        if (__x == __x->_M_parent->_M_right) {
          // set left child to __x and rotate left.
          __x = __x->_M_parent;
          _Rb_tree_rotate_left(__x, __root);
        }
        // set parent to black and grandparent to red.
        __x->_M_parent->_M_color = _S_black;
        __x->_M_parent->_M_parent->_M_color = _S_red;
        // rotate right to set parent top.
        _Rb_tree_rotate_right(__x->_M_parent->_M_parent, __root);
      }
      // if node's parent is a right child of its parent.
    } else {
      _Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_left;
      if (__y && __y->_M_color == _S_red) {
        __x->_M_parent->_M_color = _S_black;
        __y->_M_color = _S_black;
        __x->_M_parent->_M_parent->_M_color = _S_red;
        __x = __x->_M_parent->_M_parent;
      } else {
        if (__x == __x->_M_parent->_M_left) {
          __x = __x->_M_parent;
          _Rb_tree_rotate_right(__x, __root);
        }
        __x->_M_parent->_M_color = _S_black;
        __x->_M_parent->_M_parent->_M_color = _S_red;
        _Rb_tree_rotate_left(__x->_M_parent->_M_parent, __root);
      }
    }
  }
  // root node always has to be black.
  __root->_M_color = _S_black;
}

_Rb_tree_node_base* _Rb_tree_rebalance_for_erase(
    _Rb_tree_node_base* __z, _Rb_tree_node_base*& __root,
    _Rb_tree_node_base*& __leftmost, _Rb_tree_node_base*& __rightmost) {}

template <typename _Tp, typename _Alloc, bool _S_instanceless>
class _Rb_tree_alloc_base {
 public:
  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type allocator_type;

  allocator_type get_allocator() const { return _M_node_allocator; }

  _Rb_tree_alloc_base(const allocator_type& __a) : _M_node_allocator(__a) {}

 protected:
  typename _Alloc_traits<_Rb_tree_node<_Tp>, _Alloc>::allocator_type
      _M_node_allocator;

  _Rb_tree_node_base _M_header;

  _Rb_tree_node<_Tp>* _M_get_node() { return _M_node_allocator.allocate(1); }

  void _M_put_node(_Rb_tree_node<_Tp>* __p) {
    _M_node_allocator.deallocate(__p, 1);
  }
};

template <typename _Tp, typename _Alloc>
class _Rb_tree_alloc_base<_Tp, _Alloc, true> {
 public:
  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type allocator_type;

  allocator_type get_allocator() const { return allocator_type(); }

  _Rb_tree_alloc_base(const allocator_type&) {}

 protected:
  _Rb_tree_node_base _M_header;

  typedef typename _Alloc_traits<_Rb_tree_node<_Tp>, _Alloc>::_Alloc_type
      _Alloc_type;

  _Rb_tree_node<_Tp>* _M_get_node() { return _Alloc_type::allocate(1); }

  void _M_put_node(_Rb_tree_node<_Tp>* __p) { _Alloc_type::deallocate(__p, 1); }
};

template <typename _Tp, typename _Alloc>
struct _Rb_tree_base
    : public _Rb_tree_alloc_base<_Tp, _Alloc,
                                 _Alloc_traits<_Tp, _Alloc>::_S_instanceless> {
  typedef _Rb_tree_alloc_base<_Tp, _Alloc,
                              _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
                                         _Base;
  typedef typename _Base::allocator_type allocator_type;

  _Rb_tree_base(const allocator_type& __a) : _Base(__a) {}
};

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc = std::allocator<_Val> >
class _Rb_tree : protected _Rb_tree_base<_Val, _Alloc> {};

}  // namespace ft

#endif  // RBTREE_HPP