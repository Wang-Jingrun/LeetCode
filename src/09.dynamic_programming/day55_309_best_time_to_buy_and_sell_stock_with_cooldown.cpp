/*
 * 309. 买卖股票的最佳时机含冷冻期		url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/
 *
 * 题目描述：给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格 。
 * 设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
 * 		卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
 * 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int maxProfit(vector<int>& prices)
	{
		int len = prices.size();
		vector<vector<int>> dp(len, vector<int>(4, 0));
		dp[0][0] -= prices[0];
		for (int i = 1; i < len; i++)
		{
			dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][3]) - prices[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
			dp[i][2] = dp[i - 1][0] + prices[i];
			dp[i][3] = dp[i - 1][2];
		}

		return max(max(dp[len - 1][1], dp[len - 1][2]), dp[len - 1][3]);
	}
};

// 节省空间版本
class Solution2
{
 public:
	int maxProfit(vector<int>& prices)
	{
		int len = prices.size();
		vector<vector<int>> dp(2, vector<int>(4, 0));
		dp[0][0] -= prices[0];
		for (int i = 1; i < len; i++)
		{
			dp[i % 2][0] = max(dp[(i - 1) % 2][0], max(dp[(i - 1) % 2][1], dp[(i - 1) % 2][3]) - prices[i]);
			dp[i % 2][1] = max(dp[(i - 1) % 2][1], dp[(i - 1) % 2][3]);
			dp[i % 2][2] = dp[(i - 1) % 2][0] + prices[i];
			dp[i % 2][3] = dp[(i - 1) % 2][2];
		}

		return max(max(dp[(len - 1) % 2][1], dp[(len - 1) % 2][2]), dp[(len - 1) % 2][3]);
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		nums = { 1, 2, 3, 0, 2 };
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.maxProfit(nums) << endl;
	}
}
