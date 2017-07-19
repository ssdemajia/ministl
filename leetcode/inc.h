#ifndef _INC_H
#define _INC_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
//#include <map>
//#include <stack>
using namespace std;
void displayVec(std::vector<int> v)
{
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}
template <typename T>
void displayVec2d(std::vector<std::vector<T> > v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[0].size(); j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}
#endif
