/*
LEETCODE PROBLEM: (121. Best Time to Buy and Sell Stock)

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

*/


/*
- Max profit can be achieved by buying at lowest and selling at highest.
- O(N), O(1)
*/





#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int minPrice = INT_MAX;
            int maxProfit = 0;

            for(int i=0; i < prices.size(); i++) {
                minPrice = min(minPrice, prices[i]);
                maxProfit = max(maxProfit, prices[i]-minPrice);
            }

            return maxProfit;
        }
};

int main() {
    Solution *sol = new Solution();
    vector<int> prices = {7,1,5,3,6,4};

    cout << "max Profit: " << sol->maxProfit(prices);
}