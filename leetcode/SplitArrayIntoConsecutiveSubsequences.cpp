#include "inc.h"
//659. Split Array into Consecutive Subsequences
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> uni;
        uni.push_back(nums[0]);
        vector<int> dup;
        if (nums.size() < 3) return false;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != uni.back()) {
                uni.push_back(nums[i]);
            }
            else {
                dup.push_back(nums[i]);
            }
        }
        displayVec(uni);
        displayVec(dup);

        return false;
    }
};
int main(int argc, char const *argv[]) {
    Solution so;
    std::vector<int> v = {1,2,3,3,3,4,4,5,5};

    so.isPossible(v);
    return 0;
}
