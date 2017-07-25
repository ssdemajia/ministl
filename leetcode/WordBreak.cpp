#include "inc.h"
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<int> v(s.size()+1,0);
        v[0] = 1;
        for(int i = 1; i <= s.size(); i++)
        {
            for(int j = i-1; j >= 0; j--)
            {
                if (v[j])
                {
                    string sub = s.substr(j, i-j);
                    cout << "sub:"<<sub << ",i:"<<i<<",j:"<<j<<endl;
                    int hasfind = 0;
                    for (int k = 0; k < wordDict.size(); k++)
                    {
                        if (sub == wordDict[k])
                        {
                            hasfind = 1;
                        }
                    }
                    if (hasfind)
                    {
                        //cout << "i:"<<i<<endl;
                        v[i] = 1;
                    }
                }

            }
        }
        displayVec(v);
        return v[s.size()];
    }
};
int main(int argc, char const *argv[]) {
    vector<string> wordDict = {"et","code","le"};
    string s = "leetcode";
    Solution so;
    if (so.wordBreak(s, wordDict))
    {
        cout << "YES" << endl;
    }else{
        std::cout << "NO!" << '\n';
    }
    return 0;
}
