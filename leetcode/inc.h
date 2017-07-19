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
#endif
