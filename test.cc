#include <iostream>
#include <optional>
#include <ostream>
#include <unistd.h>
#include <vector>

using std::vector;
using std::swap;
using std::cout;
using std::endl;

class Solution {
public:
    /**
    * @param numbers int整型vector 
    * @return int整型
    */

    vector<int> duplicate(vector<int>& numbers) {
        int n = numbers.size();
        vector<int> result;

        int i = 0;
        while (i < n) {
            if (numbers[i] == i + 1) {
                ++i;
            } else if (numbers[i] == numbers[numbers[i] - 1]) {
                ++i;
            } else {
                swap(numbers[i], numbers[numbers[i] - 1]);
            }
        }

        for (int i = 0; i < n; ++i) {
            if (numbers[i] != i + 1) {
                result.push_back(numbers[i]);
            }
        }

        return result;
    }
};

int main() {
    // vector<int> tmp = {2, 3, 5, 2, 1, 3};
    vector<int> tmp = {4, 3, 2, 6, 8, 2, 3, 1};

    Solution s;
    vector<int> result = s.duplicate(tmp);

    for (auto& elem : result) {
        cout << elem << endl;
    }

    return 0;
}