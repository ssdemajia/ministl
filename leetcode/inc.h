#ifndef _INC_H
#define _INC_H
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <climits>
//#include <map>
//#include <stack>
using namespace std;
template <typename T>
void displayVec(std::vector<T> v, string sep = " ")
{
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << sep;
    }
    cout << endl;
}
template <typename T>
void displayVec2d(std::vector<std::vector<T> > v,string sep = " ")
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[0].size(); j++)
        {
            cout << v[i][j] << sep;
        }
        cout << endl;
    }
}
#endif
