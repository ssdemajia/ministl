#include "inc.h"
//leetcode 655
struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    vector<vector<string>> printTree(TreeNode* root) {
        int depth = deep(root);
        cout << "deep:"<<depth<<endl;
        vector<vector<string> > result (depth, vector<string>());
        std::cout << "/* message */" << '\n';
        helper(root, result, depth);
        return result;
    }
    int helper(TreeNode* root, vector<vector<string> > &result, int deep) {
        if (root->left == NULL && root->right == NULL) {
            result[deep].push_back(to_string(root->val));
            return 1;
        }
        int ls=0;
        int rs=0;
        if (root->right == NULL && root->left !=NULL) {
            ls = helper(root->left, result, deep+1);
            for (int i = 0; i < ls; i++) result[deep].push_back("");
            result[deep].push_back(to_string(root->val));
            for (int i = 0; i < ls; i++) result[deep].push_back("");
            return ls*2+1;
        }else if (root->right!=NULL && root->left == NULL) {
            rs = helper(root->right, result, deep+1);
            for (int i = 0; i < rs; i++) result[deep].push_back("");
            result[deep].push_back(to_string(root->val));
            for (int i = 0; i < ls; i++) result[deep].push_back("");
            return rs*2+1;
        }else {
            ls = helper(root->left, result , deep+1);
            for (int i = 0; i < ls; i++) result[deep].push_back("");
            result[deep].push_back(to_string(root->val));
            rs = helper(root->right, result, deep+1);
            for (int i = 0; i < rs; i++) result[deep].push_back("");
            return ls+rs+1;
        }
    }
    int deep(TreeNode *root) {
        if (!root) return 0;
        int ld = deep(root->left);
        int rd = deep(root->right);
        return ld>rd?ld+1:rd+1;
    }
};
int main(int argc, char const *argv[]) {
    Solution so;
    TreeNode *root = new TreeNode(1);
    TreeNode *p1 = new TreeNode(2);
    root->left = p1;
    displayVec2d(so.printTree(root));
    return 0;
}
