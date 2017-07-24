#include "ss_alloctor.h"
#include <vector>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[]) {
    int ia[5]={1,2,3,4,5};

    vector<int, SS::allocator<int> > iv(ia,ia+5);
    for(auto i : iv)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
