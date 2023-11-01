/*
给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。
注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
*/


struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;

    TreeLinkNode(int x) 
    : val(x)
    , left(nullptr)
    , right(nullptr)
    , next(nullptr) { }
};


class Solution {
public:

    // 1. 有右子树: 右子树最左节点
    // 2. 无右子树: 父节点


    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        TreeLinkNode* right = pNode->right;
        if (right) {
            while (right->left) {
                right = right->left;
            }

            return right;
        }

        TreeLinkNode* root = pNode->next;
        TreeLinkNode* child = pNode;
        while (root) {
            if (root->left == child) {
                return root;
            } 

            child = root;
            root =  root->next;
        }

        return nullptr;
    }

};
