#include <iostream>




template<typename T>
struct plus {
    T operator() (const T &x, const T& y) const {return x+y;}
};
// struct plus {
//     int operator() (const int &x, const int& y) const {
//         return x+y;
//     }
// };
// template <class T>
// struct minus {
//     T operator() (const T &x, const T& y) const {return x-y;}
// };
int main(int argc, char const *argv[]) {
    //plus p;
    plus<int> p;
    //minus<int> m;
    std::cout << p(1,2) << std::endl;
    //cout << m(5,1) << endl;
    return 0;
}
