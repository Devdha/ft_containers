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

template <typename _Tp, typename _Alloc>
class _Rb_tree_alloc_base {
 public:
  typedef _Alloc                                allocator_type;
  typedef std::allocator_traits<allocator_type> _Alloc_traits;

  allocator_type get_allocator() const { return allocator_type(); }

  _Rb_tree_alloc_base(const allocator_type& __a) : __alloc_type_(__a) {}

 protected:
  allocator_type __alloc_type_;

  _Rb_tree_node_base _M_header;

  _Rb_tree_node<_Tp>* _M_get_node() { return __alloc_type_.allocate(1); }

  void _M_put_node(_Rb_tree_node<_Tp>* __p) {
    __alloc_type_.deallocate(__p, 1);
  }
};

template <typename _Tp, typename _Alloc>
struct _Rb_tree_base : public _Rb_tree_alloc_base<_Tp, _Alloc> {
  typedef _Rb_tree_alloc_base<_Tp, _Alloc> _Base;
  typedef typename _Base::allocator_type   allocator_type;

  _Rb_tree_base(const allocator_type& __a) : _Base(__a) {}
};

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc = std::allocator<_Val> >
class _Rb_tree : protected _Rb_tree_base<_Val, _Alloc> {
  typedef _Rb_tree_base<_Val, _Alloc> _Base;

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

  _Link_type _M_copy(_Link_type __x, _Link_type __p);

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
    if (__x._M_root() == 0)
      _M_empty_initialize();
    else {
      _S_color(&this->_M_header) = _S_red;
      _M_root() = _M_copy(__x._M_root(), _M_end());
      _M_leftmost() = _S_minimum(_M_root());
      _M_rightmost() = _S_maximum(_M_root());
    }
    _M_node_count = __x._M_node_count;
  }

  ~_Rb_tree() { clear(); }

  _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& operator=(
      const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x);

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
  const_iterator end() const { return &_M_header; }

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
  size_type max_size() const { return size_type(-1); }

  void swap(_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __t);

  pair<iterator, bool> insert_unique(const value_type& __x);

  iterator insert_equal(const value_type& __x);

  iterator insert_unique(iterator __position, const value_type& __x);

  iterator insert_equal(iterator __position, const value_type& __x);

  template <typename _InputIterator>
  void insert_unique(_InputIterator __first, _InputIterator __last);

  template <typename _InputIterator>
  void insert_equal(_InputIterator __first, _InputIterator __last);

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

  pair<iterator, iterator>             equal_range(const key_type& __x);
  pair<const_iterator, const_iterator> equal_range(const key_type& __x) const;
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

}  // namespace ft

#endif  // RBTREE_HPP