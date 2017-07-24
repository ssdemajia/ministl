#include "algorithm.h"
using namespace std;
template <typename T>
struct Node{
    Node(T val):val(val),left(NULL),right(NULL){}
    T val;
    Node *left;
    Node *right;
};

template <typename T>
class Tree
{

public:
    Tree(vector<T>&v):size(v.size()),tree(this->createTree(0,v)){

    }
    Node<T> *createTree(int i, vector<T> &v);
    void printTree();
private:
    int size;
    Node<T> *tree;

};

template <typename T>
Node<T> *Tree<T>::createTree(int i, vector<T> &v)
{
    Node<T> * root = new Node<T>(v[i]);
    queue<Node<T>* > q;
    q.push(root);
    i++;
    while(i <= v.size()/2)
    {
        cout << "i:"<<i<<endl;
        Node<T>* temp = q.front();
        q.pop();

        if (2 * i <= v.size()){
            Node<T>* leftchild = new Node<T>(v[2*i-1]);
            temp->left = leftchild;
            q.push(leftchild);

        }
        if (2*i+1 <= v.size()){
            Node<T>* rightchild = new Node<T>(v[2*i]);
            temp->right = rightchild;
            q.push(rightchild);
        }
        i++;
    }
    return root;
}
template <typename T>
void Tree<T>::printTree()
{
    Node<T> *ptr = this->tree;
    queue<Node<T>* > q;
    q.push(ptr);
    //int i = 0;
    while(!q.empty())
    {
        Node<T>*temp = q.front();
        //cout << "val="<<temp->val << ",i= "<<i++<<" "<<endl;
        cout << temp->val << " ";
        q.pop();
        if (temp->left)
        {
            q.push(temp->left);
        }
        if (temp->right)
        {
            q.push(temp->right);
        }
    }
}
int main(int argc, char const *argv[]) {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    Tree<int> *tree = new Tree<int>(v);
    tree->printTree();
    return 0;
}
