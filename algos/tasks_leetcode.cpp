#include <iostream>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());  // sort STL-совместим и работает на итераторах

        int closest = INT_MAX / 2;  // возьмем изначально очень большим
        size_t size = nums.size();

        for (size_t i = 0; i < size - 2; ++i) {
            // возьмем i за самый левый, а дальше 2 индекса откуда-то дальше
            int l = i + 1;
            int r = size - 1;
            while (l < r) {  // пока у нас там отрезок, где l < r
                int curr = nums[i] + nums[l] + nums[r];
                if (abs(curr - target) < abs(closest - target)) {
                    closest = curr;
                }
                // двигаем границы
                if (curr < target) { 
                    ++l;
                } else if (curr > target) {
                    --r;
                } else {
                    return closest;
                }
            }
        }
        return closest;

    }
};
