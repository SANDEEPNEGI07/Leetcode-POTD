// 865. Smallest Subtree with all the Deepest Nodes

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    int maxDepth = 0;
    TreeNode* lca = NULL;
    int dfs(TreeNode* root, int depth){
        maxDepth = max(maxDepth, depth);
        if(!root) return depth;

        int left = dfs(root->left, depth + 1);
        int right = dfs(root->right, depth + 1);

        if(left == maxDepth && right == maxDepth){
            lca = root;
        }

        return max(left, right);
    }

    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        dfs(root, 0);

        return lca;
    }
};