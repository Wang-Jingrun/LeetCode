/*
 * 188. 买卖股票的最佳时机 IV		url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/
 *
 * 题目描述：给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i 天的价格。
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。也就是说，你最多可以买 k 次，卖 k 次。
 * 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int maxProfit(int k, vector<int>& prices)
	{

		if (prices.size() == 0) return 0;
		vector<vector<int>> dp(prices.size(), vector<int>(2 * k + 1, 0));
		for (int j = 1; j < 2 * k; j += 2)
		{
			dp[0][j] = -prices[0];
		}
		for (int i = 1; i < prices.size(); i++)
		{
			for (int j = 0; j < 2 * k - 1; j += 2)
			{
				dp[i][j + 1] = max(dp[i - 1][j + 1], dp[i - 1][j] - prices[i]);
				dp[i][j + 2] = max(dp[i - 1][j + 2], dp[i - 1][j + 1] + prices[i]);
			}
		}
		return dp[prices.size() - 1][2 * k];
	}
};

// 版本二 空间优化写法
class Solution2
{
 public:
	int maxProfit(int k, vector<int>& prices)
	{
		int len = prices.size();
		vector<int> dp(2 * k + 1, 0);

		// 初始化
		for (int i = 1; i < 2 * k + 1; i++)
		{
			if (i % 2 == 1) dp[i] -= prices[0];
		}

		for (int i = 1; i < len; i++)
		{
			for (int j = 1; j < 2 * k + 1; j += 2)
			{
				dp[j] = max(dp[j], dp[j - 1] - prices[i]);
				dp[j + 1] = max(dp[j + 1], dp[j] + prices[i]);
			}
		}

		return dp[2 * k];
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		nums = { 3, 2, 6, 5, 0, 3 };
		cout << "exp1 (7): " << endl;
		cout << "result: " << solution.maxProfit(2, nums) << endl;
	}
}
