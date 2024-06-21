/*

LEETCODE Problem 105
Given a preorder and inorder traversal of a tree, create the tree and return the node.

Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

*/

/*
Two facts to remember:
- preorder first element is going to be the root of the tree;
- In Inorder, root element will bisect the array into two parts. Left part will have all elements from left subtree and right part will have elements from right subtree.
- Recursively build the tree.


O(N), O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class TreeNode {
    public:
        int val;
        TreeNode* left;
        TreeNode* right;

    TreeNode(int rootval) {
        val = rootval;
        left = nullptr;
        right = nullptr;
    }
};

int indexRootInInorder(vector<int> &inorder, int rootval) {
    for(int i=0; i < inorder.size(); i++) {
        if(inorder[i] == rootval) {
            return i;
        }
    }
    return -1;

}

TreeNode* helper(
        vector<int> &preorder,
        vector<int> &inorder,
        int start,
        int end,
        int &preIndex
     ) {
         if(start > end) return nullptr;
         int rootVal = preorder[preIndex++];
         int rootIndex = indexRootInInorder(inorder, rootVal);
         TreeNode* root = new TreeNode(rootVal);
         root->left = helper(preorder, inorder, start, rootIndex-1, preIndex);
         root->right = helper(preorder, inorder, rootIndex+1, end, preIndex);
         return root;
     }

TreeNode* buildTree(vector<int>&preorder, vector<int>&inorder) {
    int preIndex = 0;
    return helper(preorder, inorder, 0, preorder.size()-1, preIndex);
}

void levelOrder(TreeNode* root) {
    if(root == nullptr) return;

    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int n = q.size();
        for(int i=0; i < n; i++) {
            TreeNode* curNode = q.front();
            q.pop();
            cout << curNode->val << " ";
            if(curNode->left != nullptr) q.push(curNode->left);
            if(curNode->right != nullptr) q.push(curNode->right);
        }
    }
}

int main() {
    vector<int> preorder = {3,9,20,15,7};
    vector<int> inorder = {9,3,15,20,7};
    TreeNode* root;
    root = buildTree(preorder, inorder);
    levelOrder(root);
    return 0;

}