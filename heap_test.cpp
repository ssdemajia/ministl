#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//this file test the header of heap

int main() {
    int ia[9] = {0,1,2,3,4,8,9,3,5};
    vector<int> ivec(ia, ia+9);

    make_heap(ivec.begin(), ivec.end());
    for (int i = 0; i < ivec.size(); i++) {
        cout << ivec[i] << ' ';
    }
    cout << endl;

    ivec.push_back(7);
    push_heap(ivec.begin(), ivec.end());
    for (int i = 0; i < ivec.size(); i++) {
        cout << ivec[i] << ' ';
    }
    cout << endl;
    make_heap(ia, ia+9);
    sort_heap(ia, ia+9);
    for (int i = 0; i < 9; i++) {
        cout << ia[i] << ' ';
    }
    cout << endl;

    sort_heap(ivec.begin(), ivec.end());
    for (int i = 0; i < ivec.size(); i++) {
        cout << ivec[i] << ' ';
    }
}
