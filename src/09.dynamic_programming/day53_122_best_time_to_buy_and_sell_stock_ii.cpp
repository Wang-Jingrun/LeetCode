/*
 * 122. 买卖股票的最佳时机 II		url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
 *
 * 题目描述：给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
 * 在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。
 * 返回 你能获得的 最大 利润 。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 动态规划 版本一
class Solution
{
 public:
	int maxProfit(vector<int>& prices)
	{
		vector<vector<int>> dp(prices.size(), vector<int>(2));
		dp[0][0] -= prices[0];
		dp[0][1] = 0;
		for (int i = 1; i < prices.size(); i++)
		{
			// 注意这里是和121. 买卖股票的最佳时机唯一不同的地方。
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
		}

		return dp[prices.size() - 1][1];
	}
};

// 动态规划 版本二
class Solution2
{
 public:
	int maxProfit(vector<int>& prices)
	{
		int len = prices.size();
		vector<vector<int>> dp(2, vector<int>(2));
		dp[0][0] -= prices[0];
		dp[0][1] = 0;
		for (int i = 1; i < len; i++)
		{
			dp[i % 2][0] = max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][1] - prices[i]);
			dp[i % 2][1] = max(dp[(i - 1) % 2][1], dp[(i - 1) % 2][0] + prices[i]);
		}

		return dp[(len - 1) % 2][1];
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		nums = { 7, 1, 5, 3, 6, 4 };
		cout << "exp1 (7): " << endl;
		cout << "result: " << solution.maxProfit(nums) << endl;
	}
}
