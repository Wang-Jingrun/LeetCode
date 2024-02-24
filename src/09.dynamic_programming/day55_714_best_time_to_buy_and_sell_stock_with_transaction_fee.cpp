/*
 * 714. 买卖股票的最佳时机含手续费		url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
 *
 * 题目描述：给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。
 * 你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
 * 返回获得利润的最大值。
 * 注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int maxProfit(vector<int>& prices, int fee)
	{
		int len = prices.size();
		vector<vector<int>> dp(len, vector<int>(2, 0));
		dp[0][0] -= prices[0];
		for (int i = 1; i < len; i++)
		{
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
		}
		return dp[len - 1][1];
	}
};

// 节省空间版本
class Solution2
{
 public:
	int maxProfit(vector<int>& prices, int fee)
	{
		int len = prices.size();
		vector<vector<int>> dp(2, vector<int>(2, 0));
		dp[0][0] -= prices[0];
		for (int i = 1; i < len; i++)
		{
			dp[i % 2][0] = max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][1] - prices[i]);
			dp[i % 2][1] = max(dp[(i - 1) % 2][1], dp[(i - 1) % 2][0] + prices[i] - fee);
		}
		return dp[(len - 1) % 2][1];
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		nums = { 1, 3, 2, 8, 4, 9 };
		cout << "exp1 (8): " << endl;
		cout << "result: " << solution.maxProfit(nums, 2) << endl;
	}
}
