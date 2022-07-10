#pragma once

#include <memory>

#include "algorithm.hpp"
#include "pair.hpp"

namespace ft {
enum _Rb_tree_color { _S_red = false, _S_black = true };

struct _Rb_tree_node_base {
  typedef _Rb_tree_node_base* _Base_ptr;

  _Rb_tree_color _M_color;
  _Base_ptr      _M_parent;
  _Base_ptr      _M_left;
  _Base_ptr      _M_right;

  static _Base_ptr _S_minimum(_Base_ptr __x) {
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
bool operator==(const _Rb_tree_iterator<_Val, _Ref, _Ptr>& __x,
                const _Rb_tree_iterator<_Val, _Ref, _Ptr>& __y) {
  return __x._M_node == __y._M_node;
}

template <typename _Val>
bool operator==(const _Rb_tree_iterator<_Val, const _Val&, const _Val*>& __x,
                const _Rb_tree_iterator<_Val, _Val&, _Val*>&             __y) {
  return __x._M_node == __y._M_node;
}

template <typename _Val>
bool operator==(const _Rb_tree_iterator<_Val, _Val&, _Val*>&             __x,
                const _Rb_tree_iterator<_Val, const _Val&, const _Val*>& __y) {
  return __x._M_node == __y._M_node;
}

template <typename _Val, typename _Ref, typename _Ptr>
bool operator!=(const _Rb_tree_iterator<_Val, _Ref, _Ptr>& __x,
                const _Rb_tree_iterator<_Val, _Ref, _Ptr>& __y) {
  return __x._M_node != __y._M_node;
}

template <typename _Val>
bool operator!=(const _Rb_tree_iterator<_Val, const _Val&, const _Val*>& __x,
                const _Rb_tree_iterator<_Val, _Val&, _Val*>&             __y) {
  return __x._M_node != __y._M_node;
}

template <typename _Val>
bool operator!=(const _Rb_tree_iterator<_Val, _Val&, _Val*>&             __x,
                const _Rb_tree_iterator<_Val, const _Val&, const _Val*>& __y) {
  return __x._M_node != __y._M_node;
}

inline void _Rb_tree_rotate_left(_Rb_tree_node_base*  __x,
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

inline void _Rb_tree_rotate_right(_Rb_tree_node_base*  __x,
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

inline void _Rb_tree_rebalance(_Rb_tree_node_base*  __x,
                               _Rb_tree_node_base*& __root) {
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

inline _Rb_tree_node_base* _Rb_tree_rebalance_for_erase(
    _Rb_tree_node_base* __z, _Rb_tree_node_base*& __root,
    _Rb_tree_node_base*& __leftmost, _Rb_tree_node_base*& __rightmost) {
  _Rb_tree_node_base* __y = __z;
  _Rb_tree_node_base* __x = 0;
  _Rb_tree_node_base* __x_parent = 0;

  // Binary search tree erase algorithm.
  if (__y->_M_left == 0)  // __y has at most one child.
    __x = __y->_M_right;
  else if (__y->_M_right == 0)  // __y has only one child.
    __x = __y->_M_left;
  else {  // __y has two children.
    // set __y as __z's successor(larger and the closest value of __z).
    __y = __y->_M_right;
    while (__y->_M_left != 0) __y = __y->_M_left;
    __x = __y->_M_right;
  }

  if (__y != __z) {                 // __y is __z's successor.
    __z->_M_left->_M_parent = __y;  // connect __z's left node to __y.
    __y->_M_left = __z->_M_left;
    if (__y != __z->_M_right) {  // __y is not __z's right child.
      __x_parent = __y->_M_parent;
      if (__x) __x->_M_parent = __y->_M_parent;  // __x is not null.
      __y->_M_parent->_M_left = __x;             // connect __y's parent to __x.
      __y->_M_right = __z->_M_right;  // connect __z's right node to __y.
      __z->_M_right->_M_parent = __y;
    } else
      __x_parent = __y;  // if __y is __z's right child, __x_parent is __y.

    if (__root == __z)  // when __z is root.
      __root = __y;
    else if (__z->_M_parent->_M_left == __z)  // when __z is left child.
      __z->_M_parent->_M_left = __y;
    else  // when __z is right child.
      __z->_M_parent->_M_right = __y;
    __y->_M_parent = __z->_M_parent;
    ft::swap(__y->_M_color, __z->_M_color);
    __y = __z;
  } else {  // __y == __z
    __x_parent = __y->_M_parent;
    if (__x) __x->_M_parent = __y->_M_parent;  // connect __y's parent to __x.
    if (__root == __z)
      __root = __x;
    else if (__z->_M_parent->_M_left == __z)
      __z->_M_parent->_M_left = __x;
    else
      __z->_M_parent->_M_right = __x;

    if (__leftmost == __z) {   // when __z is leftmost.
      if (__z->_M_right == 0)  // __z->_M_left is also null.
        __leftmost = __z->_M_parent;
      else
        __leftmost = _Rb_tree_node_base::_S_minimum(__x);
    }
    if (__rightmost == __z) {  // when __z is rightmost.
      if (__z->_M_left == 0)
        __rightmost = __z->_M_parent;
      else
        __rightmost = _Rb_tree_node_base::_S_maximum(__x);
    }
  }

  // Red-black tree erase rebalance algorithm.
  if (__y->_M_color == _S_black) {
    while (__x != __root && (__x == 0 || __x->_M_color == _S_black)) {
      if (__x == __x_parent->_M_left) {  // __x is left child.
        _Rb_tree_node_base* __w = __x_parent->_M_right;
        // case 1: __w(sibling node) is red.
        if (__w->_M_color == _S_red) {
          __w->_M_color = _S_black;
          __x_parent->_M_color = _S_red;
          _Rb_tree_rotate_left(__x_parent, __root);
          __w = __x_parent->_M_right;
        }
        // case 2: __w(sibling node) is black and __w->_M_left and __w->_M_right
        // are black.
        if ((__w->_M_right == 0 || __w->_M_right->_M_color == _S_black) &&
            (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black)) {
          __w->_M_color = _S_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        } else {
          // case 3: __w(sibling node) is black and __w->_M_left is black.
          if (__w->_M_right == 0 || __w->_M_right->_M_color == _S_black) {
            __w->_M_left->_M_color = _S_black;
            __w->_M_color = _S_red;
            _Rb_tree_rotate_right(__w, __root);
            __w = __x_parent->_M_right;
          }
          // case 4: __w(sibling node) is black and __w->_M_right is red.
          __w->_M_color = __x_parent->_M_color;
          __x_parent->_M_color = _S_black;
          if (__w->_M_right) __w->_M_right->_M_color = _S_black;
          _Rb_tree_rotate_left(__x_parent, __root);
          break;
        }
      } else {  // __x is right child.
                // same as above, only left and right are exchanged.
        _Rb_tree_node_base* __w = __x_parent->_M_left;
        if (__w->_M_color == _S_red) {
          __w->_M_color = _S_black;
          __x_parent->_M_color = _S_red;
          _Rb_tree_rotate_right(__x_parent, __root);
          __w = __x_parent->_M_left;
        }
        if ((__w->_M_left == 0 || __w->_M_left->_M_color == _S_black) &&
            (__w->_M_right == 0 || __w->_M_right->_M_color == _S_black)) {
          __w->_M_color = _S_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        } else {
          if (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black) {
            __w->_M_right->_M_color = _S_black;
            __w->_M_color = _S_red;
            _Rb_tree_rotate_left(__w, __root);
            __w = __x_parent->_M_left;
          }
          __w->_M_color = __x_parent->_M_color;
          __x_parent->_M_color = _S_black;
          if (__w->_M_left) __w->_M_left->_M_color = _S_black;
          _Rb_tree_rotate_right(__x_parent, __root);
          break;
        }
      }
    }
    if (__x) __x->_M_color = _S_black;
  }
  return __y;
}

template <typename _Tp, typename _Alloc>
class _Rb_tree_alloc_base {
 public:
  typedef _Alloc                                allocator_type;
  typedef std::allocator_traits<allocator_type> _Alloc_traits;
  typedef typename _Alloc::template rebind<_Rb_tree_node<_Tp> >::other
      _Node_alloc_type;

  allocator_type get_allocator() const { return allocator_type(); }

  _Rb_tree_alloc_base(const allocator_type& __a) : __alloc_type_(__a) {}

 protected:
  allocator_type   __alloc_type_;
  _Node_alloc_type __node_alloc_;

  _Rb_tree_node_base _M_header;

  _Rb_tree_node<_Tp>* _M_get_node() { return __node_alloc_.allocate(1); }

  void _M_put_node(_Rb_tree_node<_Tp>* __p) {
    __node_alloc_.deallocate(__p, 1);
  }
};

template <typename _Tp, typename _Alloc>
struct _Rb_tree_base : public _Rb_tree_alloc_base<_Tp, _Alloc> {
  typedef _Rb_tree_alloc_base<_Tp, _Alloc> _Base;
  typedef typename _Base::allocator_type   allocator_type;
  typedef typename _Base::_Node_alloc_type _Node_alloc_type;

  _Rb_tree_base(const allocator_type& __a) : _Base(__a) {}
};

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc = std::allocator<_Val> >
class _Rb_tree : protected _Rb_tree_base<_Val, _Alloc> {
  typedef _Rb_tree_base<_Val, _Alloc>      _Base;
  typedef typename _Base::_Node_alloc_type _Node_alloc_type;

 protected:
  typedef _Rb_tree_node_base* _Base_ptr;
  typedef _Rb_tree_node<_Val> _Rb_tree_node;

 public:
  typedef _Key              key_type;
  typedef _Val              value_type;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef _Rb_tree_node*    _Link_type;
  typedef size_t            size_type;
  typedef ptrdiff_t         difference_type;

  typedef typename _Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return _Base::get_allocator(); }

 protected:
  using _Base::_M_get_node;
  using _Base::_M_header;
  using _Base::_M_put_node;

  _Link_type _M_create_node(const value_type& __x) {
    _Link_type __tmp = _M_get_node();
    try {
      _Construct(&__tmp->_M_value_field, __x);
    } catch (...) {
      _M_put_node(__tmp);
      throw;
    }
    return __tmp;
  }

  _Link_type _M_clone_node(_Link_type __x) {
    _Link_type __tmp = _M_create_node(__x->_M_value_field);
    __tmp->_M_color = __x->_M_color;
    __tmp->_M_left = 0;
    __tmp->_M_right = 0;
    return __tmp;
  }

  void destroy_node(_Link_type __p) {
    _Destroy(&__p->_M_value_field);
    _M_put_node(__p);
  }

  size_type _M_node_count;
  _Compare  _M_key_compare;

  _Link_type& _M_root() const { return (_Link_type&)_M_header._M_parent; }
  _Link_type& _M_leftmost() const { return (_Link_type&)_M_header._M_left; }
  _Link_type& _M_rightmost() const { return (_Link_type&)_M_header._M_right; }
  _Link_type  _M_end() const { return (_Link_type)&_M_header; }
  static _Link_type& _S_left(_Link_type __x) {
    return (_Link_type&)(__x->_M_left);
  }
  static _Link_type& _S_right(_Link_type __x) {
    return (_Link_type&)(__x->_M_right);
  }
  static _Link_type& _S_parent(_Link_type __x) {
    return (_Link_type&)(__x->_M_parent);
  }
  static reference   _S_value(_Link_type __x) { return __x->_M_value_field; }
  static const _Key& _S_key(_Link_type __x) {
    return _KeyOfValue()(__x->_M_value_field);
  }
  static _Link_type& _S_left(_Base_ptr __x) {
    return (_Link_type&)(__x->_M_left);
  }
  static _Link_type& _S_right(_Base_ptr __x) {
    return (_Link_type&)(__x->_M_right);
  }
  static _Link_type& _S_parent(_Base_ptr __x) {
    return (_Link_type&)(__x->_M_parent);
  }
  static reference _S_value(_Base_ptr __x) {
    return ((_Link_type)__x)->_M_value_field;
  }
  static const _Key& _S_key(_Base_ptr __x) {
    return _KeyOfValue()(_S_value(_Link_type(__x)));
  }
  static _Rb_tree_color& _S_color(_Base_ptr __x) { return __x->_M_color; }
  static _Link_type      _S_minimum(_Link_type __x) {
         return (_Link_type)_Rb_tree_node_base::_S_minimum(__x);
  }
  static _Link_type _S_maximum(_Link_type __x) {
    return (_Link_type)_Rb_tree_node_base::_S_maximum(__x);
  }

 public:
  typedef _Rb_tree_iterator<value_type, reference, pointer> iterator;
  typedef _Rb_tree_iterator<value_type, const_reference, const_pointer>
      const_iterator;

  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ft::reverse_iterator<iterator>       reverse_iterator;

 private:
  iterator _M_insert(_Base_ptr __x, _Base_ptr __y, const value_type& __v);

  void _M_erase(_Link_type __x);

 public:
  _Rb_tree() : _Base(allocator_type()), _M_node_count(0) {
    _M_empty_initialize();
  }

  _Rb_tree(const _Compare& __comp)
      : _Base(allocator_type()), _M_node_count(0), _M_key_compare(__comp) {
    _M_empty_initialize();
  }

  _Rb_tree(const _Compare& __comp, const allocator_type& __a)
      : _Base(__a), _M_node_count(0), _M_key_compare(__comp) {
    _M_empty_initialize();
  }

  _Rb_tree(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x)
      : _Base(__x.get_allocator()),
        _M_node_count(0),
        _M_key_compare(__x._M_key_compare) {
    _M_empty_initialize();
    if (__x._M_root() == 0)
      _M_empty_initialize();
    else
      insert_unique(__x.begin(), __x.end());
    _M_node_count = __x._M_node_count;
  }

  ~_Rb_tree() { clear(); }

  _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& operator=(
      const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x) {
    if (this != &__x) {
      clear();
      _M_node_count = 0;
      _M_key_compare = __x._M_key_compare;
      if (__x._M_root() == 0) {
        _M_root() = 0;
        _M_leftmost() = _M_end();
        _M_rightmost() = _M_end();
      } else {
        insert_unique(__x.begin(), __x.end());
        _M_node_count = __x._M_node_count;
      }
    }
    return *this;
  }

 private:
  void _M_empty_initialize() {
    _S_color(&this->_M_header) = _S_red;
    _M_root() = 0;
    _M_leftmost() = _M_end();
    _M_rightmost() = _M_end();
  }

 public:
  _Compare key_comp() const { return _M_key_compare; }

  iterator       begin() { return _M_leftmost(); }
  const_iterator begin() const { return _M_leftmost(); }
  iterator       end() { return &_M_header; }
  const_iterator end() const { return const_cast<_Base_ptr>(&_M_header); }

  reverse_iterator       rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator       rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  bool      empty() const { return _M_node_count == 0; }
  size_type size() const { return _M_node_count; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(_Rb_tree_node);
  }

  void swap(_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __t);

  ft::pair<iterator, bool> insert_unique_each(const _Val& __x);

  iterator insert_unique(iterator __position, const _Val& __x);

  template <typename _InputIterator>
  void insert_unique(_InputIterator __first, _InputIterator __last);

  void erase(iterator __position);

  size_type erase(const key_type& __x);

  void erase(iterator __first, iterator __last);

  void erase(const key_type* __first, const key_type* __last);

  void clear() {
    if (_M_node_count != 0) {
      _M_erase(_M_root());
      _M_leftmost() = _M_end();
      _M_root() = 0;
      _M_rightmost() = _M_end();
      _M_node_count = 0;
    }
  }

  iterator       find(const key_type& __x);
  const_iterator find(const key_type& __x) const;
  size_type      count(const key_type& __x) const;

  iterator       lower_bound(const key_type& __x);
  const_iterator lower_bound(const key_type& __x) const;
  iterator       upper_bound(const key_type& __x);
  const_iterator upper_bound(const key_type& __x) const;

  ft::pair<iterator, iterator>             equal_range(const key_type& __x);
  ft::pair<const_iterator, const_iterator> equal_range(
      const key_type& __x) const;
};

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
bool operator==(
    const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
    const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y) {
  return __x.size() == __y.size() && equal(__x.begin(), __x.end(), __y.begin());
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
bool operator!=(
    const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
    const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y) {
  return __x.size() != __y.size() ||
         !equal(__x.begin(), __x.end(), __y.begin());
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
bool operator<(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
               const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y) {
  return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(),
                                     __y.end());
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
bool operator>(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
               const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y) {
  return __y < __x;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
bool operator<=(
    const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
    const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y) {
  return !(__y < __x);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
bool operator>=(
    const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
    const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y) {
  return !(__x < __y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void swap(_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
          _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y) {
  __x.swap(__y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_M_insert(
    _Base_ptr __x_, _Base_ptr __y_, const _Val& __v) {
  _Link_type __x = (_Link_type)__x_;
  _Link_type __y = (_Link_type)__y_;
  _Link_type __z;

  // When parent == header || __v's key is less than parent's key.
  // What is __x's role?
  if (__y == &_M_header || __x != 0 ||
      _M_key_compare(_KeyOfValue()(__v), _S_key(__y))) {
    __z = _M_create_node(__v);
    _S_left(__y) = __z;
    if (__y == &_M_header) {
      _M_root() = __z;
      _M_rightmost() = __z;
    } else if (__y == _M_leftmost())
      _M_leftmost() = __z;
  } else {
    __z = _M_create_node(__v);
    _S_right(__y) = __z;
    if (__y == _M_rightmost()) _M_rightmost() = __z;
  }
  _S_parent(__z) = __y;
  _S_left(__z) = 0;
  _S_right(__z) = 0;
  _Rb_tree_rebalance(__z, _M_header._M_parent);
  ++_M_node_count;
  return iterator(__z);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::swap(
    _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __t) {
  if (_M_root() == 0) {
    if (__t._M_root() != 0) {
      _M_root() = __t._M_root();
      _M_leftmost() = __t._M_leftmost();
      _M_rightmost() = __t._M_rightmost();
      _M_root()->_M_parent = __t._M_end();

      __t._M_root() = 0;
      __t._M_leftmost() = __t._M_end();
      __t._M_rightmost() = __t._M_end();
    }
  } else if (__t._M_root() == 0) {
    __t._M_root() = _M_root();
    __t._M_leftmost() = _M_leftmost();
    __t._M_rightmost() = _M_rightmost();
    __t._M_root()->_M_parent = __t._M_end();

    _M_root() = 0;
    _M_leftmost() = _M_end();
    _M_rightmost() = _M_end();
  } else {
    ft::swap(_M_root(), __t._M_root());
    ft::swap(_M_leftmost(), __t._M_leftmost());
    ft::swap(_M_rightmost(), __t._M_rightmost());
    ft::swap(_M_root()->_M_parent, __t._M_root()->_M_parent);
  }

  ft::swap(_M_node_count, __t._M_node_count);
  ft::swap(_M_key_compare, __t._M_key_compare);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
ft::pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator,
         bool>
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::insert_unique_each(
    const _Val& __v) {
  _Link_type __y = _M_end();
  _Link_type __x = _M_root();
  bool       __comp = true;

  while (__x != 0) {
    __y = __x;
    __comp = _M_key_compare(_KeyOfValue()(__v), _S_key(__x));
    __x = __comp ? _S_left(__x) : _S_right(__x);
  }

  iterator __j = iterator(__y);
  // what is right order? if {if} else OR if {if else}
  // if __x is left side of __y, insert __v on left side of __y.
  if (__comp) {
    if (__j == begin())
      return pair<iterator, bool>(_M_insert(__x, __y, __v), true);
    else  // go back to parent.
      --__j;
  }
  // if __x is right side of parent, insert __v on right side of its parent.
  if (_M_key_compare(_S_key(__j._M_node), _KeyOfValue()(__v)))
    return pair<iterator, bool>(_M_insert(__x, __y, __v), true);
  // it means equal. so return fail.
  return pair<iterator, bool>(__j, false);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::insert_unique(
    iterator __position, const _Val& __v) {
  // if __position is leftmost.
  if (__position._M_node == _M_header._M_left) {
    if (size() > 0 &&
        _M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node)))
      return _M_insert(__position._M_node, __position._M_node, __v);
    else
      return insert_unique_each(__v).first;
    // if __postion is end.
  } else if (__position._M_node == &_M_header) {
    if (_M_key_compare(_S_key(_M_rightmost()), _KeyOfValue()(__v)))
      return _M_insert(0, _M_rightmost(), __v);
    else
      return insert_unique_each(__v).first;
  } else {
    iterator __before = __position;
    --__before;
    // if value is between __before and __position.
    if (_M_key_compare(_S_key(__before._M_node), _KeyOfValue()(__v)) &&
        _M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node))) {
      // if x.right is null.
      if (_S_right(__before._M_node) == 0)
        return _M_insert(0, __before._M_node, __v);
      else
        return _M_insert(__position._M_node, __position._M_node, __v);
    } else {
      return insert_unique_each(__v).first;
    }
  }
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
template <class _Iterator>
void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::insert_unique(
    _Iterator __first, _Iterator __last) {
  for (; __first != __last; ++__first) insert_unique_each(*__first);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::erase(
    iterator __position) {
  _Link_type __y = (_Link_type)_Rb_tree_rebalance_for_erase(
      __position._M_node, _M_header._M_parent, _M_header._M_left,
      _M_header._M_right);
  destroy_node(__y);
  --_M_node_count;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::erase(const _Key& __x) {
  iterator  __i = find(__x);
  size_type __n = __i == end() ? 0 : 1;
  if (__n) erase(__i);
  return __n;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_M_erase(
    _Link_type __x) {
  while (__x != 0) {
    _M_erase(_S_right(__x));
    _Link_type __y = _S_left(__x);
    destroy_node(__x);
    __x = __y;
  }
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::erase(
    iterator __first, iterator __last) {
  if (__first == begin() && __last == end())
    clear();
  else
    while (__first != __last) erase(__first++);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
void _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::erase(
    const _Key* __first, const _Key* __last) {
  while (__first != __last) erase(*__first++);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::find(const _Key& __k) {
  _Link_type __y = _M_end();
  _Link_type __x = _M_root();

  while (__x != 0) {
    if (!_M_key_compare(_S_key(__x), __k)) {
      __y = __x;
      __x = _S_left(__x);
    } else
      __x = _S_right(__x);
  }

  iterator __j = iterator(__y);
  return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ? end()
                                                                    : __j;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::find(
    const _Key& __k) const {
  _Link_type __y = _M_end();
  _Link_type __x = _M_root();

  while (__x != 0) {
    if (!_M_key_compare(_S_key(__x), __k)) {
      __y = __x;
      __x = _S_left(__x);
    } else
      __x = _S_right(__x);
  }

  iterator __j = iterator(__y);
  return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ? end()
                                                                    : __j;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::size_type
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::count(
    const _Key& __k) const {
  const_iterator __p = find(__k);
  size_type      __n = __p == end() ? 0 : 1;
  return __n;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::lower_bound(
    const _Key& __k) {
  _Link_type __y = _M_end();
  _Link_type __x = _M_root();

  while (__x != 0) {
    if (!_M_key_compare(_S_key(__x), __k)) {
      __y = __x;
      __x = _S_left(__x);
    } else
      __x = _S_right(__x);
  }

  return iterator(__y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::lower_bound(
    const _Key& __k) const {
  _Link_type __y = _M_end();
  _Link_type __x = _M_root();

  while (__x != 0) {
    if (!_M_key_compare(_S_key(__x), __k)) {
      __y = __x;
      __x = _S_left(__x);
    } else
      __x = _S_right(__x);
  }

  return const_iterator(__y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::upper_bound(
    const _Key& __k) {
  _Link_type __y = _M_end();
  _Link_type __x = _M_root();

  while (__x != 0)
    if (_M_key_compare(__k, _S_key(__x))) {
      __y = __x;
      __x = _S_left(__x);
    } else
      __x = _S_right(__x);

  return iterator(__y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::upper_bound(
    const _Key& __k) const {
  _Link_type __y = _M_end();
  _Link_type __x = _M_root();

  while (__x != 0)
    if (_M_key_compare(__k, _S_key(__x))) {
      __y = __x;
      __x = _S_left(__x);
    } else
      __x = _S_right(__x);

  return const_iterator(__y);
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc>
pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator,
     typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator>
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::equal_range(
    const _Key& __k) {
  return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
}

template <typename _Key, typename _Val, typename _KoV, typename _Compare,
          typename _Alloc>
pair<typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::const_iterator,
     typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::const_iterator>
_Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::equal_range(
    const _Key& __k) const {
  return pair<const_iterator, const_iterator>(lower_bound(__k),
                                              upper_bound(__k));
}

}  // namespace ft