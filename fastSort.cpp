#include "algorithm.h"

class FastSort
{
private:
    iter partition(iter begin, iter end, bool func(iter a, iter b))
    {
        iter x = end - 1;//x指向数组的最后一个
        iter i = begin - 1;//i指向比x小的片段的最后一个
        for (auto j = begin; j != x; j++)
        {
            if (*j < *x) {//将比x小的片段换到前面来，那么剩下的就是小的
                i++;
                swap(i, j);
            }
        }
        swap(x, i+1);
        return i+1;
    }
public:
    void sort(iter begin, iter end, bool func(iter a, iter b) = compfunc)
    {
        if (end-1 > begin)
        {
            iter mid = partition(begin, end, func);
            sort(begin, mid, func);
            sort(mid+1, end, func);
        }
    }
};
// using namespace std;
// bool comp(iter a, iter b)
// {
//     if ((*a)[0] <= (*b)[0])
//     {
//         return true;
//     }
//     return false;
// }
// int main(int argc, char const *argv[]) {
//     FastSort s;
//     vector<string> vec{"ac", "cx","bb","ss","ds","jb"};
//     //vector<int> vec{1,6,3,5};
//     s.sort(vec.begin(), vec.end(), comp);
//     display(vec.begin(), vec.end());
//     return 0;
// }
