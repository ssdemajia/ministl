#include "algorithm.h"

template <typename KEY_TYPE, typename VALUE_TYPE>
struct elem{//输入的数据元素
    KEY_TYPE _key;//关键词
    VALUE_TYPE _value;//对应的值
    elem():_key(0),_value(0){}
    elem(KEY_TYPE key, VALUE_TYPE value):_key(key),_value(value){}
    elem(const elem<KEY_TYPE, VALUE_TYPE> &r)
    {
        this->_key = r._key;
        this->_value = r._value;
    }
};

template <typename KEY_TYPE, typename VALUE_TYPE>
struct node{//树节点，保存了一个用于放置key和value的结点
    elem<KEY_TYPE, VALUE_TYPE> _e;

    node(elem<KEY_TYPE, VALUE_TYPE> e):left(NULL),right(NULL){
        _e = e;
    }
    node<KEY_TYPE, VALUE_TYPE> * left;
    node<KEY_TYPE, VALUE_TYPE> * right;
};
template <typename KEY_TYPE, typename VALUE_TYPE>
class SearchTree
{
public:
    SearchTree(std::vector<elem<KEY_TYPE, VALUE_TYPE> > v);
    void print();
    void insert(elem<KEY_TYPE, VALUE_TYPE> z);

private:
    node<KEY_TYPE, VALUE_TYPE> *n;
    void traverse(node<KEY_TYPE,VALUE_TYPE> *root);
};
template <typename KEY_TYPE, typename VALUE_TYPE>
SearchTree<KEY_TYPE, VALUE_TYPE>::SearchTree(std::vector<elem<KEY_TYPE, VALUE_TYPE> > v)
:n(NULL)
{
    for (int i = 0; i < v.size(); i++)
    {
        insert(v[i]);//对数组内每个元素插入到树中
    }
}
template <typename KEY_TYPE, typename VALUE_TYPE>
void SearchTree<KEY_TYPE, VALUE_TYPE>::insert(elem<KEY_TYPE, VALUE_TYPE> z)
{
    node<KEY_TYPE, VALUE_TYPE> *x = n;//保存当前结点
    node<KEY_TYPE, VALUE_TYPE> *y = NULL;//y保存上一个结点
    while(x!=NULL)//按照二叉搜索树的规则遍历到根结点
    {
        y = x;
        if (z._key < x->_e._key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    node<KEY_TYPE, VALUE_TYPE>* temp = new node<KEY_TYPE, VALUE_TYPE>(z);
    if (y == NULL) {n = temp;}
    else if (z._key < y->_e._key)
    {
        y->left = temp;
    }
    else
    {
        y->right = temp;
    }
}
template <typename KEY_TYPE, typename VALUE_TYPE>
void SearchTree<KEY_TYPE, VALUE_TYPE>::print()
{
    traverse(this->n);
}
template <typename KEY_TYPE, typename VALUE_TYPE>
void SearchTree<KEY_TYPE, VALUE_TYPE>::traverse(node<KEY_TYPE,VALUE_TYPE> *root)
{
    if (root)
    {
        traverse(root->left);
        std::cout << root->_e._value<<" ";
        traverse(root->right);
    }
}
int main(int argc, char const *argv[]) {
    std::vector<elem<int, int> > v = {
        elem<int, int>(1,2),
        elem<int, int>(5,1),
        elem<int, int>(2,4),
        elem<int, int>(4,6)                            };
    SearchTree<int, int> tree(v);
    tree.print();
    return 0;
}
