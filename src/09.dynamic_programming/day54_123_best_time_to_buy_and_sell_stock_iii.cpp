/*
 * 123. 买卖股票的最佳时机 III		url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/
 *
 * 题目描述：给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
 * 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 * */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	int maxProfit(vector<int>& prices)
	{
		int len = prices.size();
		// 不操作 第一次持有 第一次卖出 第二次持有 第二次卖出
		vector<vector<int>> dp(len, vector<int>(5));
		dp[0][1] -= prices[0];
		dp[0][3] -= prices[0];
		for (int i = 1; i < len; i++)
		{
			dp[i][0] = dp[i - 1][0];
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
			dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
			dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
			dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
		}
		return dp[len - 1][4];
	}
};

// 版本二 空间优化写法
class Solution2
{
 public:
	int maxProfit(vector<int>& prices)
	{
		if (prices.size() == 0) return 0;
		vector<int> dp(5, 0);
		dp[1] = -prices[0];
		dp[3] = -prices[0];
		for (int i = 1; i < prices.size(); i++)
		{
			dp[1] = max(dp[1], dp[0] - prices[i]);
			dp[2] = max(dp[2], dp[1] + prices[i]);
			dp[3] = max(dp[3], dp[2] - prices[i]);
			dp[4] = max(dp[4], dp[3] + prices[i]);
		}
		return dp[4];
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		nums = { 3, 3, 5, 0, 0, 3, 1, 4 };
		cout << "exp1 (6): " << endl;
		cout << "result: " << solution.maxProfit(nums) << endl;
	}
}
