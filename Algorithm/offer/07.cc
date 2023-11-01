/*
输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

例如，给出
前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]

返回如下的二叉树：
    3
   / \
  9  20
    /  \
   15   7

限制：0 <= 节点个数 <= 5000
*/


#include <algorithm>
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::find;
using std::unordered_map;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) 
    : val(x)
    , left(nullptr)
    , right(nullptr) {}
};

class Solution {
public:
    /**
     * @param preOrder int整型vector 
     * @param vinOrder int整型vector 
     * @return TreeNode类
     */

    TreeNode* reConstructBinaryTree(vector<int>& preOrder, vector<int>& vinOrder) {
        
        getInIndex(vinOrder);
        TreeNode* root = helper(preOrder, 0, 0, vinOrder.size()-1);

        return root;
    }


private:
    // 储存 中序遍历vector 中的 值:索引, 便于查找 根节点位置
    unordered_map<int, int> inIndex;

    void getInIndex(vector<int>& vinOrder) {
        for (int i = 0; i < vinOrder.size(); ++i) {
            inIndex.insert({vinOrder[i], i});
        }
    }


    TreeNode* helper(vector<int>& preOrder, int preRoot, int inLeft, int inRight) {

        if (inLeft > inRight) {
            return nullptr;
        }

        int rootVal = preOrder[preRoot];
        TreeNode* root = new TreeNode(rootVal);

        int inRoot = inIndex[rootVal];
        root->left = helper(preOrder, preRoot+1, inLeft, inRoot-1);
        root->right = helper(preOrder, preRoot + (inRoot-inLeft) + 1, inRoot+1, inRight);

        return root;
    }

};


