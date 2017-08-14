#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
    int bit = 13;
    cout << (((bit) + 9) & ~(9)) << endl;
    return 0;
}
