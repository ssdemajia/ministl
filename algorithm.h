#ifndef ALGORITHM
#define ALGORITHM
#include <iostream>
#include <vector>
#include <string>
#include <queue>
//using iter = std::vector<int>::iterator;
using iter = std::vector<std::string>::iterator;//描述算法所对应的数据类型

class RadixSort;//基数排序
class FastSort;//快速排序
void swap(iter a, iter b)//交换两个元素
{//不能用交换迭代器，因为迭代器是值传递进入的，应该交换两个迭代器指向的值
    auto temp = *a;
    *a = *b;
    *b = temp;
}
bool compfunc(iter a, iter b)//默认的比较算法
{
    if (*a <= *b)
    {
        return true;
    }
    return false;
}
void display(iter begin, iter end)
{
    for (auto i = begin; i != end; i++)
    {
        std::cout << *i << " " ;
    }
    std::cout << std::endl;
}

#endif
