/* Given an array of integers and target, return the indices of two element whose sum is equal to target.
For every array there will be one and exactly one solution present.

TC1:
    Input: nums = [2,7,11,15], target = 9
    Output: [0,1]
    Explanation: Because nums[0] + nums[1] == 9, we return [0, 1]

TC2:
    Input: nums = [3,2,4], target = 6
    Output: [1,2]

TC3:
    Input: nums = [3,3], target = 6
    Output: [0,1]
*/


// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        map<int, int> mp;

        for(int i=0; i<nums.size(); i++) {
            if(mp.find(target - nums[i]) != mp.end()) {
                ans = {mp[target - nums[i]], i};
                return ans;
            }

            mp[nums[i]] = i;
        }
        return ans;
}

int main() {
    vector<int> tc = {2,7,11,15};
    int target = 9;
    vector<int> ans = twoSum(tc, target);

    cout << "Index of elements with target sum of " << target << endl;

    for(auto x: ans) {
        cout << x << " "
    }

    return 0;
}

/* Explanation:

- We need two elements whose sum is equal to target.
- We want to find the pair in one iteration.
- For every element we visit, we can store the element and its index in a map
- And for an element a, if we find target - a in the map, then we found a pair with sum target.

Most optimal solution
TC: O(N) - iterating the array once.
SC: O(N) - storing the map

*.