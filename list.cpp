#include "list.h"

List::List(std::vector<int> source)
{
    //displayVec(source);
    ListNode * root = new ListNode(0);
    ListNode * p = root;
    int i = 0;
    for (;i<source.size();i++)
    {
        ListNode *temp = new ListNode(source[i]);
        p->next = temp;
        p = p->next;
    }
    std::shared_ptr<ListNode> sp (root->next);
    list = sp;
    delete root;
}
ListNode* List::getHead() const
{
    return list.get();
}
void List::displayList() const
{
    ListNode * p= getHead();
    cout << p->next->next->val << endl;
}
void List::setHead(ListNode*& x)
{
    list.reset(x);
}
