#include <cstddef>
#include <cstdlib>
#include <new>
typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = true;
const __rb_tree_color_type __rb_tree_black = false;

struct __rb_tree_node_base 
{
    typedef __rb_tree_color_type color_type;
    typedef __rb_tree_node_base* base_ptr;
    color_type color;
    base_ptr parent;//指向父节点
    base_ptr left;//指向左孩子
    base_ptr right;//指向右孩子

    static base_ptr minimum(base_ptr x) //返回节点中最小值
    {
        while (x->left) x = x->left;       
        return x;
    }
    static base_ptr maximum(base_ptr x) {//返回最大值
        while (x->right) x = x->right; 
        return x;
    }
};

template <class Value>
struct __rb_tree_node: public __rb_tree_node_base
{
    typedef __rb_tree_node<Value>* link_type;//指向结点的指针
    Value value_field;
};

//基层迭代器
struct __rb_tree_base_iterator
{
    typedef __rb_tree_node_base::base_ptr base_ptr;
    //typedef bidirectional_iterator_tag iterator_category;//迭代器类型是双向访问的
    typedef ptrdiff_t difference_type;
    base_ptr node;

    void increment()
    {
        if (node->right != 0) {//如果当前的结点有右子树，直接到右子树的最小结点处
            node = node->right;
            while (node->left != 0) node = node->left;
        }
        else {
            base_ptr y = node->parent;//如果没有右子树，那么需要往上走直到找到一个父节点是祖父结点左子树
            while (node == y->right) {//往上走
                node = y;
                y = y->parent;
            }
            if (y->parent == node) {//此时y是header结点，这个头结点的parent指针指向根
                node = y;
            }
        }
    }

    void decrement()
    {
        if (node->color == __rb_tree_red && node->parent->parent == node) {
            node = node->parent;//当node是头节点，根节点的父节点是头结点，头结点的父节点是根节点，所以会出现node->parent->parent == node
        }//头结点是红色的
        else if (node->left != 0) {
            node = node->left;
            while (node->right != 0) node = node->right;
        } else {
            base_ptr y = node->parent;
            while (node == y->left) {
                node = y;
                y = y->parent;
            }
            node = y;
        }
    }
};



//RB-tree 迭代器
template <class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator {
    typedef Value value_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef __rb_tree_iterator<Value, Ref, Ptr> self;
    typedef __rb_tree_iterator<Value, Value&, Value*> iterator;
    typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
    typedef __rb_tree_node<Value>* link_type;
    __rb_tree_iterator(){}//默认构造函数
    __rb_tree_iterator(link_type x) { node = x; }//用结点指针构造
    __rb_tree_iterator(const iterator& it) { node = it.node; }//复制构造函数

    reference operator*() const {return link_type(node)->value_field; }
    pointer operator->() const {return &operator*();}

    self& operator++(){
        increment();
        return *this;
    }
    self operator++(int) {
        self temp = *this;
        increment();
        return temp;
    }
    self& operator--(){
        decrement();
        return *this;
    }
    self operator--(int) {
        self temp = *this;
        decrement();
        return temp;
    }
};



template <class Key, class Value, class KeyOfValue, class Compare>
class rb_tree {
protected:
    typedef void* void_pointer;
    typedef __rb_tree_node_base* base_ptr;
    typedef __rb_tree_node<Value> rb_tree_node;
    //typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator
    typedef __rb_tree_color_type color_type;
public:
    typedef Key key_type;
    typedef Value value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef rb_tree_node* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
protected:
    link_type get_node() {//获得一个节点
        return malloc(sizeof(rb_tree_node));
    }
    void put_node(link_type p) {//释放节点
        free(p);
    }
    link_type create_node(const value_type& x) {
        link_type y = get_node();
        new(y) value_type(x);//在y指针指向的地方构造x
        return y;
    }
    link_type clone_node(link_type x) {//复制一个节点的值和颜色
        link_type temp = create_node(x->value_field);
        temp->color = x->color;
        temp->left = 0;
        temp->right = 0;
        return temp;
    }
    void destroy_node(link_type p) {
        p->value_field.~value_type();//调用value的析构函数
        put_node(p);
    }
protected:
    size_type node_count; // 节点数量
    link_type header;//rb-tree的头结点
    Compare key_compare;//比较节点键值大小的准则

    link_type& root() const { return (link_type&)header->parent; }//header的父节点是rbtree的根节点
    link_type& leftmost() const { return (link_type&)header->left; }//header的左子节点是整个rbtree最小的
    link_type& rightmost() const { return (link_type&)header->right; }//右子节点是真个rbtree最大的

    static link_type& left(link_type x) {return (link_type&)(x->left); }
    static link_type& right(link_type x) {return (link_type&)(x->right); }
    static link_type& parent(link_type x) {return (link_type&)(x->parent); }
    static reference value(link_type x) {return (link_type&)(x->value_field); }
    //todo static const Key& key(link_type x) {return }
    static color_type& color(link_type x) {
        return (color_type&)(x->color);
    }
    static link_type& left(base_ptr x) {return (link_type&)(x->left); }
    static link_type& right(base_ptr x) {return (link_type&)(x->right); }
    static link_type& parent(base_ptr x) {return (link_type&)(x->parent); }
    static reference value(base_ptr x) {return ((link_type)x)->value_field; }
    //todo static const Key& key(base_ptr x) {return }
    static color_type& color(base_ptr x) {
        return (color_type&)(x->color);
    }
    static link_type minimum(link_type x) {
        return (link_type)__rb_tree_node_base::minimum(x);
    }
    static link_type maximum(link_type x) {
        return (link_type)__rb_tree_node_base::maximum(x);
    }
public:
    typedef __rb_tree_iterator<value_type, reference, pointer> iterator;
private:
    iterator __insert(base_ptr x, base_ptr y, const value_type& v);
    link_type __copy(link_type x, link_type p);
    void __erase(link_type x);
    void init() {
        header = get_node();//创建头结点
        color(header) = __rb_tree_red;//将头结点颜色设为红色
        root() = 0;
        leftmost() = header;
        rightmost() = header;//一开始header最小节点指向header自己
    }
public:
    rb_tree(const Compare& comp = Compare()):node_count(0),key_compare(comp){}
    ~rb_tree(){
        clear();//清除节点
        put_node(header);//将头结点清除
    }
    rb_tree<Key, Value, KeyOfValue, Compare>&
    operator=(const rb_tree<Key, Value, KeyOfValue, Compare>& x);
public:
    Compare key_comp() const {return key_compare; }
    iterator begin() {return leftmost();}//起点是最小的点
    iterator end() {return header;}//终点是头结点
    bool empty() const { return node_count==0; }
    void clear();
    size_type size() const { return node_count;}
    size_type max_size() const { return size_type(-1); }

public:
    //pair<iterator, bool> insert_unique(const value_type& x);
    iterator insert_equal(const value_type& x);
};
template<class Key, class Value, class KeyOfValue, class Compare>
typename rb_tree<Key, Value, KeyOfValue, Compare>::iterator
rb_tree<Key, Value, KeyOfValue, Compare>::insert_equal(const Value& v) {
    link_type y = header;
    link_type x = root();
    while (x != 0) {
        y = x;
        x = key_compare(KeyOfValue(v, key(v))) ? left(x) : right(x);
    }
    return __insert(x, y, v);
}
template<class Key, class Value, class KeyOfValue, class Compare>
typename rb_tree<Key, Value, KeyOfValue, Compare>::iterator//真正的插入操作，其中x是y的子节点
rb_tree<Key, Value, KeyOfValue, Compare>::__insert(base_ptr _x, base_ptr _y, const Value& v) 
{
    link_type x = (link_type)_x;
    link_type y = (link_type)_y;
    link_type z;
    //key_compare(a,b)返回true表示a<b,a是b的左子节点
    if (y == header || x!= 0 || key_compare(KeyOfValue(v), key(y))) {
        z = create_node(v);
        left(y) = z;
        if (y == header) {//当y是头结点时，x是根节点，而且root为空，需要将root变为z所指向的节点
            root() = z;
            rightmost() = z;//同时右边的最大节点也是根节点
        }else if (y == leftmost()) {
            leftmost() = z;//y是最小结点，x比y更小，需要维护header的left指向z
        }
    }else {//x>y的情况，新加入的x大于父节点
        z = create_node(v);
        right(y) = z;
        if (y == rightmost()) {
            rightmost() = z;
        }
    }
    parent(z) = y;
    left(z) = 0;
    right(z) = 0;
    __rb_tree_rebalance(z, header->parent);
    ++node_count;
    return iterator(z);
}

void __rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root);
void __rb_tree_rotate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root);

inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root)
{
    x->color = __rb_tree_red;
    while (x!= root && x->parent->color == __rb_tree_red) {//如果x的颜色是红色，而且x的父节点也是红色
        if (x->parent == x->parent->parent->left) {//1.父节点是祖父节点的左子节点
            __rb_tree_node_base* y = x->parent->parent->right;//叔节点
            if (y && y->color == __rb_tree_red) {//1.1.叔节点存在且是红色
                x->parent->color = __rb_tree_black;
                y->color = __rb_tree_black;
                y->parent->color = __rb_tree_red;
                x = y->parent;//因为祖父节点的父节点有可能也是红色的，所以还要继续往上走
            } else {//1.2.没有叔节点，或者叔节点是黑色
                if (x == x->parent->right) {//1.2.1.新节点是父节点的右子节点，需要将它掰直
                    x = x->parent;
                    __rb_tree_rotate_left(x, root);
                }
                x->parent->color = __rb_tree_black;
                x->parent->parent->color = __rb_tree_red;
                __rb_tree_rotate_right(x->parent->parent, root);
            }
        }
        else {//2.父节点是祖父节点的右子节点
            __rb_tree_node_base* y = x->parent->parent->right;//叔节点
            if (y && y->color == __rb_tree_red) {//2.1.叔节点存在且是红色
                x->parent->color = __rb_tree_black;
                y->color = __rb_tree_black;
                y->parent->color = __rb_tree_red;
                x = y->parent;//因为祖父节点的父节点有可能也是红色的，所以还要继续往上走
            } else {//2.2.没有叔节点，或者叔节点是黑色
                if (x == x->parent->left) {//2.2.1.新节点是父节点的左子节点，需要将它掰直
                    x = x->parent;
                    __rb_tree_rotate_right(x, root);
                }
                x->parent->color = __rb_tree_black;
                x->parent->parent->color = __rb_tree_red;
                __rb_tree_rotate_left(x->parent->parent, root);
            }
        }
    }
    root->color = __rb_tree_black;
}
//x必须是红色节点
inline void __rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root) 
{
    __rb_tree_node_base* y = x->parent;//y是x的父节点
    x->right = y->left;
    if (y->left != 0) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (root == x) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }else {
        x->parent->right = y;
    }
    y->left = x;
    y->parent = x->parent;
}
inline void __rb_tree_rotate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root) {
    __rb_tree_node_base* y = x->parent;
    x->left = y->right;
    if (y->right != 0) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x == root) {
        root = y;
    } else if (x == x->parent->left) {
        y = x->parent->left;
    }
    else {
        y = x->parent->right;
    }
    x->parent = y;
    y->right = x;
}
