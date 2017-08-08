#ifndef _LIST_H
#define _LIST_H
#include "leetcode/inc.h"
#include <iostream>
#include <vector>
#include <memory>
struct ListNode{
    int val;
    ListNode * next;
    ListNode(int x):val(x),next(NULL){}
};
class List
{
public:
    List(std::vector<int> source);
    ~List();
    ListNode * getHead() const;
    void setHead(ListNode* x);
    void displayList() const;
private:
    ListNode* list;
};

#endif
