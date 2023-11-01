/*
输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

示例:

输入：head = [1,3,2]
输出：[2,3,1]

限制：
0 <= 链表长度 <= 10000
*/

struct ListNode {
    int val;
    struct ListNode *next;

    ListNode(int x) 
    : val(x)
    , next(nullptr) { }
};


#include <vector>
using std::vector;

class Solution {
public:

    void helper(ListNode* node, vector<int>& vec) {
        if (!node) {
            return;
        }

        helper(node->next, vec);
        vec.push_back(node->val);
    }


    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> result;

        helper(head, result);

        return result;
    }
};
