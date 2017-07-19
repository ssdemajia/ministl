#include "inc.h"
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0||x%10 == 0) return false;
        int temp = x;
        int r=0;
        while(temp>r)
        {
            cout << temp << " , " << r << endl;
            r*=10;
            r+=temp%10;
            temp/=10;
        }
        cout << temp << " , " << r << endl;
        if (temp == r||temp == r/10)
        {
        }
        else
        {
            return false;
        }
    }
};
int main(int argc, char const *argv[]) {
    Solution so;
    //0 1 10 121 12321
    if (so.isPalindrome(10)) {
        cout << "YES!"<<endl;
    }
    return 0;
}
