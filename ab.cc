
#include <vector>
using std::vector;

class Solution {
public:
    bool findTargetIn2DPlants(vector<vector<int>>& plants, int target) {

        if (plants.size() == 0) {
            return false;
        }

        int x = plants.size();
        int y = plants[0].size();

        int i = 0;
        int j = y - 1;
        while (i >= 0 && i < x && j >= 0 && j < y) {
            int val = plants[i][j];
            if (val == target) {
                return true;
            } else if (val > target) {
                --j;
            } else {
                ++i;
            }
        }
        return false;
    }
};