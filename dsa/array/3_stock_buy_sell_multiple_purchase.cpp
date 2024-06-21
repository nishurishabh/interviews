/*
LEETCODE PROBLEM: (122. Best Time to Buy and Sell Stock II)

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by trading stocks multiple times. You can buy and sell as much as you want.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

*/


/*
- Max profit can be achieved by buying at lower and selling at higher.
- Since you can buy and sell multiple times, you can just keep adding your profit, if the stock price is higher the next day.
- O(N), O(1)
*/





#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfit=0;
        for(int i=1; i<prices.size(); i++)
        {
            if(prices[i] > prices[i-1])
                maxProfit+=(prices[i]-prices[i-1]);
        }
        return maxProfit;
    }
};

int main() {
    Solution *sol = new Solution();
    vector<int> prices = {7,1,5,3,6,4};

    cout << "max Profit: " << sol->maxProfit(prices);
}