#include "list.h"

List::List(std::vector<int> source)
{
    ListNode * root = new ListNode(0);
    ListNode * p = root;
    for (int i = 0;i<source.size();i++)
    {
        ListNode *temp = new ListNode(source[i]);
        p->next = temp;
        p = p->next;
    }
    list = root->next;
    delete root;
}
ListNode* List::getHead() const
{
    return list;
}
void List::displayList() const
{
    ListNode * p= list;
    while (p) {
        cout << p->val<<" ";
        p = p->next;
    }
}
void List::setHead(ListNode* x)
{
    list = x;
}
List::~List()
{
    ListNode *p = list;
    ListNode *temp;
    while(p) {
        temp = p->next;
        delete p;
        p = temp;
    }
}
