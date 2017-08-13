#include "inc.h"
//Leetcode 43
class Solution {
public:
    string mutiply(string num1, string num2) {
        int len1 = num1.size();
        int len2 = num2.size();
        string result(len1+len2, '0');
        int plus_carry = 0;//加法进位
        int multi_carry = 0;//乘法进位
        int i,j;
        for (i = len1-1; i>=0; i--) {
            int a = num1[i] - '0';//乘数当前位
            for (j = len2-1; j>=0; j--) {
                int b = num2[i] - '0';
                int temp = a*b+multi_carry;
                int c = temp%10 + result[i+j+1] - '0' + plus_carry;
                multi_carry = temp/10;
                plus_carry = c/10;
                result[i+j+1] = '0'+c%10;
            }
            if (plus_carry > 0 || multi_carry>0) {
                result[i+j+1] = multi_carry+'0'+plus_carry;
                multi_carry=plus_carry=0;
            }
        }
        int k = 0;
        while(result[k] == '0') {
            k++;
            if (k == result.size()) {
                return "0";
            }
        }
        result = string(result, k);
        return result;
    }
};
