/*
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。
例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  

示例1:
输入：[3,4,5,1,2]
输出：1

示例2:
输入：[2,2,2,0,1]
输出：0
*/

#include <vector>
using std::vector;

class Solution {
public:
    /**
     * @param nums int整型vector 
     * @return int整型
     */

    int minNumberInRotateArray(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = (right - left) / 2 + left;
            int val = nums[mid];

            if (val > nums[right]) {
                left = mid + 1;
            } else if (val < nums[right]) {
                right = mid;
            } else {
                // NOTE: 重点
                --right;
            }
        }

        return nums[right];
    }

};
