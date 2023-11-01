/*
给定一个二维数组，其每一行从左到右递增排序，从上到下也是递增排序。
给定一个数，判断这个数是否在该二维数组中。

Consider the following matrix:
[   [1,   4,  7, 11, 15],
    [2,   5,  8, 12, 19],
    [3,   6,  9, 16, 22],
    [10, 13, 14, 17, 24],
    [18, 21, 23, 26, 30]    ]

Given target = 5, return true.
Given target = 20, return false.
*/

#include <iostream>
#include <ostream>
#include <unistd.h>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    /**
     * @param target int整型 
     * @param array int整型vector<vector<>> 
     * @return bool布尔型
     */
    
    bool Find(int target, vector<vector<int> >& array) {

        if (array.size() == 0) {
            return false;
        }

        int i = 0;
        int j = array[0].size() - 1;

        while (i < array.size() && j >= 0) {
            int val = array[i][j];

            if (target == val) {
                return true;
            } else if (target > val) {
                ++i;
            } else {
                --j;
            }

            cout << "(" << i << ", " << j << ")" << endl;
            sleep(1);
        }

        return false;
    }
};

int main() {
    vector<vector<int>> nums = {{1,   4,  7, 11, 15},
                                {2,   5,  8, 12, 19},
                                {3,   6,  9, 16, 22},
                                {10, 13, 14, 17, 24},
                                {18, 21, 23, 26, 30} };

    Solution s;
    s.Find(1, nums);
}