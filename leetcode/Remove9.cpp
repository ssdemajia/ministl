#include "inc.h"
//660. Remove 9
//思路相当于将n转化为九进制下的数
class Solution {
public:
    int newInteger(int n) {
        int result = 0;
        int mod;
        while(n > 0) {

            mod = n%9;
            result+=mod;
            result *=10;
            n/=9;
        } 
        return result;
    }
};
int main(int argc, char const *argv[]) {
    Solution so;
    cout << so.newInteger(10) << endl;
    return 0;
}
