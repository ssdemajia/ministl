#include "leetcode/inc.h"

int main(int argc, char const *argv[]) {
    unordered_map<int,int>m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[3] = 3-m[3];
    for_each(m.cbegin(), m.cend(), [](const pair<int,int> &a){cout<<"["<<a.first<<"]:"<<a.second<< " ";});
    cout << endl;
    m.erase(3);
    for_each(m.cbegin(), m.cend(), [](const pair<int,int> &a){cout<<"["<<a.first<<"]:"<<a.second<< " ";});
    cout << endl;
    return 0;
}
